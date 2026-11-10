/* Gameplay policy only. No audio function hooks, calls, skips or tempo writes.
 * update_player_racer(Object*, s32) receives object in r4 and updateRate in r5.
 * The original one-byte speedup latch is restored on every scope exit. */
static unsigned normal_depth, normal_active, normal_logs, normal_fast_logged, normal_early_logged, normal_identity_logged, normal_wait_logged, normal_reject_mask;
static DkrU32 normal_latch, normal_saved, normal_object, normal_racer, normal_scene;
static unsigned normal_track, normal_tick, normal_cp_before, normal_progress_before, normal_timer_before, normal_countdown_before;
static int normal_lap_before;
static void normal_restore(void) {
    if(normal_active)store_native(normal_latch,normal_saved,1);
    normal_active=0;
}
static void normal_music_unload(void) {
    normal_restore();normal_depth=0;normal_logs=normal_fast_logged=normal_early_logged=normal_identity_logged=normal_wait_logged=normal_reject_mask=0;
}
/* The only native effect here is suppressing the final-lap REQUEST in an
 * already validated sprint. It must not wait for audio initialization or
 * unrelated parking inputs. No sequence, tempo or audio player is changed. */
static int normal_human(DkrU32 object,DkrU32 racer,unsigned track) {
    return guest_range(object,0x80,4)&&guest_range(racer,0x224,4)&&
        read_native(object+0x48,2)==1&&read_native(object+0x64,4)==racer&&
        read_native(racer,2)<=3&&read_native(racer+2,1)<8&&
        read_native(racer+0x1d6,1)==vehicles[track]&&!read_native(racer+0x1d8,1);
}
/* Optional evidence for the already-fast warning only, never an admission
 * dependency. Custom music may legitimately have a different authored tempo. */
static int normal_stock_baseline(void) {
    if(!audio_symbols[2]||!audio_symbols[3]||!audio_symbols[4])return 0;
    const DkrU32 table=read_native(audio_symbols[2],4);
    const unsigned count=read_native(audio_symbols[3],4),bytes=read_native(audio_symbols[4],4);
    return count>57&&bytes>=174&&bytes<=100000&&guest_range(table,bytes,1)&&read_native(table+172,1)==132;
}
static void normal_reject(unsigned bit,const char* reason) {
    if(!(normal_reject_mask&bit)){normal_reject_mask|=bit;dkr_log(reason);}
}
/* Read-only diagnostics, not an alternative admission path. Report only an
 * identified sprint carrier; ordinary races are intentionally silent. */
static void normal_scope_diagnostic(void) {
    if(!enabled||failed||!catalogue_done)return;
    const unsigned map=read_native(map_id,4);unsigned track;
    for(track=0;track<TRACKS;++track)if(found[track]&&carriers[track]==map)break;
    if(track==TRACKS)return;
    if(read_native(game_mode,4)!=0||read_native(time_trial,1)) {
        normal_reject(1,"Experimental sprint normal music: inactive target mode; ordinary offline race required.");return;
    }
    const DkrU32 header=read_native(level_header,4),route=read_native(nodes,4);
    if(!guest_range(header,0xc4,4)) {
        normal_reject(2,"Experimental sprint normal music: target header not yet available.");return;
    }
    const unsigned count=read_native(main_count,4),total=read_native(total_count,4);
    if(count!=main_counts[track]||total<count||total>127||!guest_range(route,total*NODE_BYTES,4)) {
        normal_reject(4,"Experimental sprint normal music: target checkpoint count or route does not match supported course.");return;
    }
    normal_reject(8,"Experimental sprint normal music: target laps, race type, vehicle or geometry does not match supported course.");
}
static void normal_log_context(const char* reason,DkrU32 object,DkrU32 racer,unsigned tick) {
    char line[512];char* at=append_text(line,"Experimental sprint normal music: ");at=append_text(at,reason);
    at=append_text(at," tick=");at=append_number(at,tick);
    at=append_text(at," human=");at=append_number(at,read_native(racer,2));
    at=append_text(at," cp_before=");at=append_number(at,normal_cp_before);
    at=append_text(at," cp_after=");at=append_signed(at,signed_byte(racer+0x192));
    at=append_text(at," lap_before=");at=append_signed(at,normal_lap_before);
    at=append_text(at," lap_after=");at=append_signed(at,signed_byte(racer+0x193));
    at=append_text(at," count_lap=");at=append_signed(at,signed_byte(racer+0x194));
    at=append_text(at," progress_before=");at=append_signed(at,(short)normal_progress_before);
    at=append_text(at," progress_after=");at=append_signed(at,(short)read_native(racer+0x190,2));
    at=append_text(at," countdown_before=");at=append_number(at,normal_countdown_before);
    at=append_text(at," lap0_ticks_before=");at=append_number(at,normal_timer_before);
    at=append_text(at," lap0_ticks_after=");at=append_number(at,read_native(racer+0x128,4));
    at=append_text(at," tempo=");if(audio_symbols[1])at=append_number(at,read_native(audio_symbols[1],2));else at=append_text(at,"unknown");
    static const char* const fields[3]={" sequence="," pending="," playing="};
    static const unsigned indexes[3]={0,6,7};
    for(unsigned i=0;i<3;++i){at=append_text(at,fields[i]);if(audio_symbols[indexes[i]])at=append_number(at,read_native(audio_symbols[indexes[i]],1));else at=append_text(at,"unknown");}
    float xyz[3];if(pose(object,xyz))at=append_pose(at,xyz);*at=0;dkr_log(line);
}
DKR_CALLBACK(before_update_player_racer) void normal_music_enter(void) {
    if(normal_depth){normal_restore();++normal_depth;return;}
    normal_depth=1;normal_active=0;
    if(enabled&&!catalogue_done&&!normal_identity_logged){normal_identity_logged=1;dkr_log("Experimental sprint normal music: course identity scan pending; policy not yet applied.");}
    DkrGameCall call;Dkr2Session session={.size=sizeof(session)};unsigned track;DkrU32 route;
    if(dkr2_session(&session)!=DKR2_OK||!supported_revision(session.revision)||session.online)return;
    if(normal_scene!=session.scene_generation){normal_scene=session.scene_generation;normal_logs=normal_fast_logged=normal_early_logged=normal_wait_logged=normal_reject_mask=0;}
    if(!scene_matches_track(&track,&route,1)){normal_scope_diagnostic();return;}
    if(!dkr_game_context_read(&call)) {
        normal_reject(16,"Experimental sprint normal music: target player callback context unavailable.");return;
    }
    const DkrU32 object=(DkrU32)call.r[4];if(!guest_range(object,0x80,4))return;
    const DkrU32 racer=read_native(object+0x64,4);if(!normal_human(object,racer,track)) {
        if(guest_range(racer,0x224,4)&&read_native(racer,2)<=3&&!read_native(racer+0x1d8,1))
            normal_reject(32,"Experimental sprint normal music: target human object or current vehicle does not match supported course.");
        return;
    }
    normal_cp_before=read_native(racer+0x192,1);normal_lap_before=signed_byte(racer+0x193);
    normal_progress_before=read_native(racer+0x190,2);normal_timer_before=read_native(racer+0x128,4);normal_countdown_before=read_native(start_timer,4);
    if(read_native(read_native(level_header,4)+0x52,1)!=57||!audio_symbols[5]) {
        if(!normal_early_logged){normal_early_logged=1;normal_log_context("inactive: expected music/header or gameplay latch unavailable",object,racer,session.tick);}
        return;
    }
    /* An already-fast scene is diagnosed, never silently forced back through
     * an audio call or a cosmetic sMusicTempo-only write. Restart remains
     * necessary for recovery. Prevent further requests while it is scoped. */
    if(normal_stock_baseline()&&audio_symbols[0]&&audio_symbols[1]&&read_native(audio_symbols[0],1)==57&&
       read_native(audio_symbols[1],2)!=132&&!normal_fast_logged) {
        normal_fast_logged=1;normal_log_context("already non-normal; fresh restart required; further speedup requests guarded",object,racer,session.tick);
    }
    if(read_native(audio_symbols[5],1)!=0) {
        if(!normal_wait_logged){normal_wait_logged=1;normal_log_context("existing speedup latch retained; no new request possible",object,racer,session.tick);}
        return;
    }
    normal_latch=audio_symbols[5];normal_saved=0;normal_object=object;normal_racer=racer;
    normal_track=track;normal_tick=session.tick;
    /* Fallible formatting/SDK logging must happen before the native write.
     * A full shared log journal can stop the VM without delivering our paired
     * exit. This ordering prevents that specific fault from leaking the latch.
     * It does NOT provide rollback for arbitrary VM faults or missing exits. */
    if(!normal_logs){++normal_logs;normal_log_context("scoped final-lap request guard ready; playback untouched",object,racer,session.tick);}
    normal_active=1;
    store_native(normal_latch,1,1);
}
DKR_CALLBACK(after_update_player_racer) void normal_music_leave(void) {
    const unsigned was_active=normal_active;
    normal_restore();if(normal_depth)--normal_depth;
    /* Cleanup never depends on exit registers, scene or actor validity. */
    if(!was_active)return;
    Dkr2Session session={.size=sizeof(session)};unsigned track;DkrU32 route;
    if(!scene_matches_track(&track,&route,1)||track!=normal_track||dkr2_session(&session)!=DKR2_OK||
       !supported_revision(session.revision)||session.online||session.scene_generation!=normal_scene||!normal_human(normal_object,normal_racer,track))return;
    /* Before/after checkpoint state identifies an eligible wrap context.
     * This is not a direct observation of tempVar or an audio request. */
    if(normal_cp_before==main_counts[track]-1&&signed_byte(normal_racer+0x192)==0&&
       signed_byte(normal_racer+0x193)==0&&normal_logs<5) {
        ++normal_logs;normal_log_context("eligible wrap observed under normal guard",normal_object,normal_racer,normal_tick);
    }
}
