/* Experimental post-line control. Never skips native code, restores XYZ,
 * edits native result fields, or changes Y movement/collision results. */
typedef union FloatBits { DkrU32 bits; float real; } FloatBits;
typedef struct ParkedCpu {
    DkrU32 object, racer, map, scene, index, track, finish;
    unsigned active, tick, last_sample, seen_ai_tick, frames;
    unsigned suppressed, accepted, samples;
    float origin[3];
} ParkedCpu;
static ParkedCpu parked[8];
static DkrU32 input_symbols[5], paused_symbol, audio_symbols[8];
static unsigned parking_ready, parking_scene, ai_depth, ai_active;
static DkrU32 ai_object, ai_racer;
static unsigned ai_index, ai_track, vehicle_depth, vehicle_active, vehicle_tag;
static DkrU32 saved_inputs[5];
static unsigned music_started, music_logs, music_seq, music_tempo, music_latch;
static const float terminal_xyz[2][3] = {{-70,4893,871},{-15719,-6766,6884}};

static float real_at(DkrU32 address) { FloatBits v = {.bits = read_native(address,4)}; return v.real; }
static int finite_real(float value) { FloatBits v = {.real=value}; return (v.bits & 0x7f800000U) != 0x7f800000U; }
static void store_native(DkrU32 address, DkrU32 value, unsigned bytes) {
#ifdef SPRINT_FINISH_TEST
    sprint_test_write_native(address,value,bytes);
#else
    if (bytes == 1) *(volatile U8*)address = (U8)value;
    else *(volatile DkrU32*)address = value;
#endif
}
static void restore_inputs(void) {
    /* Cleanup precedes every admission guard, including mismatched exits. */
    if (vehicle_active) for (unsigned i=0;i<5;++i) store_native(input_symbols[i],saved_inputs[i],4);
    vehicle_active=0;
}
static void clear_parking_records(void) {
    for (unsigned i=0;i<8;++i) parked[i]=(ParkedCpu){0};
    music_started=music_logs=0;
}
static void parking_unload(void) {
    normal_music_unload();
    restore_inputs(); clear_parking_records();
    ai_depth=ai_active=vehicle_depth=0; parking_scene=0;
}
static void parking_boot(void) {
    static const char* const inputs[5] = {"gCurrentRacerInput","gCurrentButtonsPressed","gCurrentButtonsReleased","gCurrentStickX","gCurrentStickY"};
    static const char* const audio[8] = {"gCurrentSequenceID","sMusicTempo","gSeqSoundTable","gSeqSoundCount","gSeqSoundTableSize","D_8011D580","gMusicNextSeqID","gMusicPlaying"};
    static const unsigned widths[8] = {1,2,4,4,4,1,1,1};
    /* Fresh VM boot has no active native scope from an earlier session. */
    vehicle_active=ai_active=ai_depth=vehicle_depth=0; parking_scene=0;
    clear_parking_records(); parking_ready=1;
    for (unsigned i=0;i<5;++i) { input_symbols[i]=symbol(inputs[i],4,4); if(!input_symbols[i])parking_ready=0; }
    paused_symbol=symbol("gIsPaused",1,1); if(!paused_symbol)parking_ready=0;
    for (unsigned i=0;i<8;++i) audio_symbols[i]=symbol(audio[i],widths[i],widths[i]);
    if (!parking_ready) dkr_log("Experimental sprint activation: stopping inputs unavailable; music guard remains independent.");
    if (!audio_symbols[5]) dkr_log("Experimental sprint activation: music guard unavailable, final-lap gameplay latch symbol missing.");
}
/* Course identity/shape is independent of the stopping input symbols.
 * Music needs only its own gameplay latch, never a parking readiness flag. */
static int scene_matches_track(unsigned* track_out, DkrU32* route_out, unsigned allow_countdown) {
    if(!enabled||failed||!catalogue_done||read_native(game_mode,4)!=0||read_native(time_trial,1)||(!allow_countdown&&read_native(start_timer,4)))return 0;
    const DkrU32 map=read_native(map_id,4),header=read_native(level_header,4),route=read_native(nodes,4);
    unsigned track; for(track=0;track<2;++track)if(found[track]&&carriers[track]==map)break;
    if(track==2||!guest_range(header,0xc4,4))return 0;
    const unsigned count=read_native(main_count,4),total=read_native(total_count,4);
    if(count!=main_counts[track]||total<count||total>127||!guest_range(route,total*NODE_BYTES,4)||
       read_native(header+0x4b,1)!=1||read_native(header+0x4c,1)!=0||
       read_native(header+0x4d,1)!=vehicles[track]||!geometry_matches(track,read_native(header+0x34,2)))return 0;
    *track_out=track;*route_out=route;return 1;
}
static int scene_matches_policy(unsigned* track_out,DkrU32* route_out,unsigned allow_countdown) {
    return parking_ready&&scene_matches_track(track_out,route_out,allow_countdown);
}
static int scene_matches(unsigned* track_out,DkrU32* route_out) { return scene_matches_policy(track_out,route_out,0); }
static int actor_matches(DkrU32 object,DkrU32 racer,unsigned track,unsigned index) {
    return index<8&&guest_range(object,0x80,4)&&guest_range(racer,0x224,4)&&
        read_native(object+0x48,2)==1&&read_native(object+0x64,4)==racer&&
        read_native(racer,2)==0xffffU&&read_native(racer+2,1)==index&&
        read_native(racer+0x1d6,1)==vehicles[track]&&read_native(racer+0x1d8,1)==1&&
        read_native(racer+0x1ac,2)>=1&&read_native(racer+0x1ac,2)<=8&&
        !read_native(racer+0x108,4)&&!read_native(racer+0x148,4);
}
static int parked_matches(ParkedCpu* p,unsigned track,unsigned scene) {
    return p->active&&p->track==track&&p->scene==scene&&p->map==read_native(map_id,4)&&
        actor_matches(p->object,p->racer,track,p->index)&&read_native(p->racer+0x1ac,2)==p->finish;
}
static char* append_signed(char* at,int value) {
    unsigned magnitude=(unsigned)value;
    if(value<0){*at++='-';magnitude=0U-magnitude;}
    return append_number(at,magnitude);
}
static int pose(DkrU32 object,float out[3]) {
    for(unsigned i=0;i<3;++i) {out[i]=real_at(object+0x0c+4*i);if(!finite_real(out[i])||out[i]<-100000||out[i]>100000)return 0;}
    return 1;
}
static char* append_pose(char* at,const float xyz[3]) {
    static const char* const names[3]={" x10="," y10="," z10="};
    for(unsigned i=0;i<3;++i){at=append_text(at,names[i]);at=append_signed(at,(int)(xyz[i]*10));}return at;
}
static int passed_terminal(DkrU32 object,DkrU32 racer,unsigned track,DkrU32 route,float* clearance) {
    const int next=signed_byte(racer+0x192),lane=signed_byte(racer+0x1ca);
    if(next<=(int)terminal_nodes[track]||next>=(int)main_counts[track]||lane<0||lane>3||signed_byte(racer+0x193)<1)return 0;
    const DkrU32 node=route+terminal_nodes[track]*NODE_BYTES,prev=node-NODE_BYTES;
    if(signed_byte(node+0x3a)!=-1||read_native(node+0x36+(unsigned)lane,1)!=6)return 0;
    float xyz[3],normal[3],center[3],direction=0,norm=0,plane_center=real_at(node+0x0c),distance=plane_center,extent=0;
    if(!pose(object,xyz)||!finite_real(plane_center))return 0;
    for(unsigned i=0;i<3;++i) {
        normal[i]=real_at(node+4*i);center[i]=real_at(node+0x10+4*i);const float prior=real_at(prev+0x10+4*i);
        if(!finite_real(normal[i])||!finite_real(center[i])||!finite_real(prior)||center[i]!=terminal_xyz[track][i]||prior<-100000||prior>100000)return 0;
        norm+=normal[i]*normal[i];direction+=normal[i]*(center[i]-prior);
        plane_center+=normal[i]*center[i];distance+=normal[i]*xyz[i];
        const float delta=xyz[i]-center[i];extent+=delta*delta;
    }
    if(!finite_real(norm)||norm<0.95f||norm>1.05f||plane_center<-2||plane_center>2||
       !finite_real(direction)||(direction>-10&&direction<10)||extent>4000000)return 0;
    if(direction<0)distance=-distance;
    if(!finite_real(distance)||distance<120)return 0;
    *clearance=distance;return 1;
}
DKR_CALLBACK(before_update_AI_racer) void parking_ai_enter(void) {
    if(ai_depth){restore_inputs();ai_active=0;++ai_depth;return;}
    ai_depth=1;ai_active=0;
    DkrGameCall call; Dkr2Session session={.size=sizeof(session)}; unsigned track;DkrU32 route;
    if(!scene_matches(&track,&route)||!dkr_game_context_read(&call)||dkr2_session(&session)!=DKR2_OK)return;
    if(parking_scene!=session.scene_generation){clear_parking_records();parking_scene=session.scene_generation;}
    const DkrU32 object=(DkrU32)call.r[4],racer=(DkrU32)call.r[5];
    if(!guest_range(racer,0x224,4))return;
    const unsigned index=read_native(racer+2,1);if(index>=8)return;
    ParkedCpu* p=&parked[index];
    if(p->active&&!parked_matches(p,track,session.scene_generation)){*p=(ParkedCpu){0};return;}
    if(!actor_matches(object,racer,track,index))return;
    if(p->active&&(p->object!=object||p->racer!=racer)){*p=(ParkedCpu){0};return;}
    if(!p->active) {
        float clearance;if(!passed_terminal(object,racer,track,route,&clearance))return;
        *p=(ParkedCpu){.object=object,.racer=racer,.map=read_native(map_id,4),.scene=session.scene_generation,.index=index,.track=track,
            .finish=read_native(racer+0x1ac,2),.active=1,.tick=session.tick,.last_sample=session.tick};
        if(!pose(object,p->origin)){*p=(ParkedCpu){0};return;}
        char line[256];char* at=append_text(line,"Experimental sprint stop: armed racer=");at=append_number(at,index);
        at=append_text(at," clearance10=");at=append_signed(at,(int)(clearance*10));at=append_pose(at,p->origin);*at=0;dkr_log(line);
    }
    ai_object=object;ai_racer=racer;ai_index=index;ai_track=track;ai_active=1;p->seen_ai_tick=session.tick;
    /* Native nearby physics, renewed before this actor's AI update every tick.
     * No protected function is skipped. Collision pushes can still move it. */
    store_native(racer+0x201,30,1);
}
DKR_CALLBACK(after_update_AI_racer) void parking_ai_leave(void) {
    restore_inputs();vehicle_depth=0;ai_active=0;
    if(ai_depth) --ai_depth;
}
static void vehicle_enter(unsigned tag) {
    if(vehicle_depth){restore_inputs();ai_active=0;++vehicle_depth;return;}
    vehicle_depth=1;
    if(!ai_active||ai_depth!=1||tag!=ai_track)return;
    DkrGameCall call;Dkr2Session session={.size=sizeof(session)};unsigned track;DkrU32 route;
    if(!scene_matches(&track,&route)||track!=ai_track||!dkr_game_context_read(&call)||
       (DkrU32)call.r[6]!=ai_object||(DkrU32)call.r[7]!=ai_racer||dkr2_session(&session)!=DKR2_OK||
       !parked_matches(&parked[ai_index],track,session.scene_generation))return;
    for(unsigned i=0;i<5;++i)saved_inputs[i]=read_native(input_symbols[i],4);
    vehicle_active=1;vehicle_tag=tag;
    store_native(input_symbols[0],0x4000,4); /* B held, never A or reverse stick. */
    for(unsigned i=1;i<5;++i)store_native(input_symbols[i],0,4);
    store_native(ai_racer+0xb4,0,4); /* Remove residual throttle, not velocity. */
    /* Do not seed hover brake: a constant positive value produces reverse thrust. */
}
static void vehicle_leave(unsigned tag) {
    const unsigned mismatch=vehicle_active&&vehicle_tag!=tag;
    restore_inputs();if(vehicle_depth)--vehicle_depth;if(mismatch)ai_active=0;
}
DKR_CALLBACK(before_func_8004F7F4) void parking_car_enter(void){vehicle_enter(0);}
DKR_CALLBACK(after_func_8004F7F4) void parking_car_leave(void){vehicle_leave(0);}
DKR_CALLBACK(before_func_80046524) void parking_hover_enter(void){vehicle_enter(1);}
DKR_CALLBACK(after_func_80046524) void parking_hover_leave(void){vehicle_leave(1);}
DKR_CALLBACK(before_move_object) void parking_move_request(void) {
    if(!vehicle_active||vehicle_depth!=1||!ai_active||ai_depth!=1)return;
    DkrGameCall call;Dkr2Session session={.size=sizeof(session)};unsigned track;DkrU32 route;
    if(!scene_matches(&track,&route)||track!=ai_track||!dkr_game_context_read(&call)||
       (DkrU32)call.r[4]!=ai_object||dkr2_session(&session)!=DKR2_OK||
       !parked_matches(&parked[ai_index],track,session.scene_generation))return;
    FloatBits x={.bits=(DkrU32)call.r[5]},z={.bits=(DkrU32)call.r[7]};
    if(!finite_real(x.real)||!finite_real(z.real))return;
    ParkedCpu* p=&parked[ai_index];
    if(x.real==0&&z.real==0){++p->accepted;return;}
    /* Original move_object still executes. Its Y argument, object, other
     * registers, native return, bounds and segment ownership are untouched.
     * Reviewed collision closures do not call this mover; direct separation
     * writes and global object interactions therefore remain native. */
    call.r[5]=0;call.r[7]=0;
    if(dkr_game_context_write(&call))++p->suppressed;
}
static void music_observe(void) {
    for(unsigned i=0;i<8;++i)if(!audio_symbols[i])return;
    if(read_native(audio_symbols[6],1)||!read_native(audio_symbols[7],1))return;
    const unsigned seq=read_native(audio_symbols[0],1),tempo=read_native(audio_symbols[1],2),latch=read_native(audio_symbols[5],1);
    const DkrU32 table=read_native(audio_symbols[2],4);const unsigned count=read_native(audio_symbols[3],4),bytes=read_native(audio_symbols[4],4);
    if(count<=57||bytes<174||bytes>100000||!guest_range(table,bytes,1))return;
    if(!music_started&&seq!=57)return;
    if(music_started&&seq==music_seq&&tempo==music_tempo&&latch==music_latch)return;
    music_started=1;music_seq=seq;music_tempo=tempo;music_latch=latch;
    if(music_logs++>=8)return;
    char line[192];char* at=append_text(line,"Experimental sprint audio: sequence=");at=append_number(at,seq);
    at=append_text(at," tempo=");at=append_number(at,tempo);at=append_text(at," boss_baseline=");at=append_number(at,read_native(table+57*3+1,1));
    at=append_text(at," speedup_latch=");at=append_number(at,latch);*at=0;dkr_log(line);
}
DKR_CALLBACK(on_frame_end) void parking_observe_frame(void) {
    unsigned track;DkrU32 route;Dkr2Session session={.size=sizeof(session)};
    if(!scene_matches(&track,&route)||read_native(paused_symbol,1)||dkr2_session(&session)!=DKR2_OK)return;
    music_observe();
    for(unsigned i=0;i<8;++i) {
        ParkedCpu* p=&parked[i];if(!p->active)continue;
        if(!parked_matches(p,track,session.scene_generation)){*p=(ParkedCpu){0};continue;}
        if(p->seen_ai_tick!=session.tick||p->last_sample==session.tick)continue;
        p->last_sample=session.tick;++p->frames;
        if(p->frames!=120&&p->frames!=360&&p->frames!=900)continue;
        float xyz[3];if(!pose(p->object,xyz))continue;
        char line[448];char* at=append_text(line,"Experimental sprint stop: sample racer=");at=append_number(at,i);
        at=append_text(at," active_frames=");at=append_number(at,p->frames);at=append_text(at," elapsed_ticks=");at=append_number(at,session.tick-p->tick);
        at=append_pose(at,xyz);static const char* const delta_names[3]={" dx10="," dy10="," dz10="};
        for(unsigned a=0;a<3;++a){at=append_text(at,delta_names[a]);at=append_signed(at,(int)((xyz[a]-p->origin[a])*10));}
        at=append_text(at," suppressed=");at=append_number(at,p->suppressed);at=append_text(at," accepted_zero=");at=append_number(at,p->accepted);
        at=append_text(at," finished=");at=append_number(at,read_native(p->racer+0x1d8,1));at=append_text(at," finish_position=");at=append_number(at,read_native(p->racer+0x1ac,2));
        *at=0;dkr_log(line);++p->samples;
    }
}
