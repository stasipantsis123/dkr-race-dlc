/* Additive, silent universal intermediate-lap banners. Native Lap 2 / Final
 * Lap code and audio are never replaced, skipped, or called artificially.
 * Rendering uses the engine's bounded repeat mechanism, outside the VM lease.
 * No arbitrary native function, ROM address or external asset is required. */
#ifdef TAJ_TEST
#include "tests/sdk_shim.h"
#else
#include <dkr/development.h>
#endif
#include "banner_policy.h"
typedef unsigned char U8;
typedef unsigned short U16;
typedef struct HudElement {
    short rotation[3]; short sprite;
    float scale, x, y, z;
    short frame; U8 state[6];
} HudElement;
_Static_assert(sizeof(HudElement) == 32, "Native HUD element ABI");
static DkrU32 s_mode,s_map,s_header,s_pause,s_hud,s_players,s_dl,s_colour;
static unsigned enabled;
static unsigned report_pending,report_lap,report_total;
static BannerClock clock;
static unsigned inside,stage,used,colour_saved,two_digits;
static DkrU32 trigger_hud,saved_colour;
static HudElement lap_element,number_element,second_number;
static int range(DkrU32 a,unsigned n,unsigned align) {
    return a >= 0x80000400U && a <= 0x80800000U && n <= 0x80800000U-a && !(a&(align-1));
}
static DkrU32 read_native(DkrU32 a,unsigned n) {
#ifdef TAJ_TEST
    return test_read(a,n);
#else
    if(n==1)return *(const volatile U8*)a;
    if(n==2)return *(const volatile U16*)a;
    return *(const volatile DkrU32*)a;
#endif
}
static void write_native(DkrU32 a,unsigned n,DkrU32 v) {
#ifdef TAJ_TEST
    test_write(a,n,v);
#else
    if(n==1)*(volatile U8*)a=(U8)v;
    else if(n==2)*(volatile U16*)a=(U16)v;
    else *(volatile DkrU32*)a=v;
#endif
}
static DkrU32 symbol(const char* name,unsigned n,unsigned align) {
    DkrU32 a=(DkrU32)(unsigned long)dkr_game_symbol(name);
    return dkr_game_symbol_size(name)>=n && range(a,n,align)?a:0;
}
static void copy_element(HudElement* out,DkrU32 src) {
    U8* bytes=(U8*)out;
    for(unsigned i=0;i<32;++i)bytes[i]=(U8)read_native(src+i,1);
}
static void restore_colour(void) {
    if(colour_saved){write_native(s_colour,4,saved_colour);colour_saved=0;}
}
/* The valid existing HUD display-list owner, not an invented DL pointer.
 * This is the same G_SETPRIMCOLOR command emitted by native hud_lap_count. */
static int prim_colour(unsigned rgba) {
    DkrU32 dl=read_native(s_dl,4);
    if(!range(dl,8,8))return 0;
    write_native(dl,4,0xFA000000U);write_native(dl+4,4,rgba);write_native(s_dl,4,dl+8);
    return 1;
}
static void log_rendered(void) {
    if(!report_pending)return;
    char message[]="Lap banner rendered: 00 of 00 (no new audio).";
    message[21]=(char)('0'+report_lap/10);message[22]=(char)('0'+report_lap%10);
    message[27]=(char)('0'+report_total/10);message[28]=(char)('0'+report_total%10);
    dkr_log(message);report_pending=0;
}
DKR_CALLBACK(on_boot) void banner_boot(void) {
    enabled=inside=stage=used=colour_saved=report_pending=0;clock=(BannerClock){0};
    Dkr2Session s={.size=sizeof(s)};
    if(dkr2_session(&s)!=DKR2_OK||s.online||(s.revision!=77&&s.revision!=80))return;
    s_mode=symbol("gGameMode",4,4);s_map=symbol("gMapId",4,4);
    s_header=symbol("gCurrentLevelHeader",4,4);
    s_pause=symbol("gIsPaused",1,1);s_hud=symbol("gCurrentHud",4,4);
    s_players=symbol("gHUDNumPlayers",4,4);s_dl=symbol("gHudDL",4,4);
    s_colour=symbol("gHudColour",4,4);
    if(!s_mode||!s_map||!s_header||!s_pause||!s_hud||!s_players||!s_dl||!s_colour)return;
    enabled=1;dkr_log("Universal lap banners r2: compact silent LAP 3-98; final lap stays native; offline single-player.");
}
DKR_CALLBACK(on_scene_unload) void banner_unload(void) {
    restore_colour();inside=stage=used=report_pending=0;clock=(BannerClock){0};
}
DKR_CALLBACK(before_hud_lap_count) void banner_lap_begin(DkrU32 racer,DkrU32 update_rate) {
    restore_colour();inside=stage=used=0;
    if(!enabled||!range(racer,0x224,4))return;
    Dkr2Session s={.size=sizeof(s)};
    if(dkr2_session(&s)!=DKR2_OK||s.online||(s.revision!=77&&s.revision!=80)||read_native(s_mode,4)!=0||read_native(s_players,4)!=0)return;
    DkrU32 header=read_native(s_header,4),hud=read_native(s_hud,4);
    if(!range(header,0xc4,4)||!range(hud,59*32,4))return;
    if(read_native(racer,2)!=0||read_native(racer+0x1d8,1))return;
    unsigned lap=read_native(racer+0x193,1),total=read_native(header+0x4b,1);
    unsigned paused=read_native(s_pause,1);
    unsigned changed=clock.valid&&clock.lap!=lap;
    unsigned age=banner_clock(&clock,s.scene_generation,read_native(s_map,4),racer,total,lap,s.tick,update_rate,paused);
    if(paused)return;
    BannerLayout layout;
    if(!banner_layout(total,lap,read_native(racer+0x194,1),age,&layout))return;
    copy_element(&lap_element,hud+30*32);copy_element(&number_element,hud+4*32);
    /* LAP is a centred orthographic sprite. Numbers are top-left textures. */
    lap_element.rotation[0]=lap_element.rotation[1]=lap_element.rotation[2]=0;
    lap_element.scale=1.0f;lap_element.x=layout.lap_x;lap_element.y=30.0f;lap_element.z=0;lap_element.frame=0;
    number_element.rotation[0]=number_element.rotation[1]=number_element.rotation[2]=0;
    number_element.sprite=9;number_element.scale=2.375f;
    two_digits=layout.two_digits;
    number_element.x=160.0f+layout.digit_x+layout.first_offset;
    number_element.y=71.0f;number_element.z=0;number_element.frame=(short)(two_digits?layout.digit/10:layout.digit);
    second_number=number_element;second_number.x+=layout.digit_advance;second_number.frame=(short)(layout.digit%10);
    if(changed){report_pending=1;report_lap=lap+1;report_total=total;}
    trigger_hud=hud;inside=1;
}
DKR_CALLBACK(after_hud_lap_count) void banner_lap_end(void) {
    restore_colour();inside=stage=used=0;
}
DKR_CALLBACK(before_hud_element_render) void banner_draw_before(DkrU32 dl,DkrU32 mtx,DkrU32 vertex,DkrU32 element) {
    (void)dl;(void)mtx;(void)vertex;
    if(!inside||!stage||element!=trigger_hud+3*32)return;
    DkrGameCall call;
    if(!dkr_game_context_read(&call))return;
    call.r[7]=(DkrU64)(long long)(DkrS32)(DkrU32)(unsigned long)(stage==1?&lap_element:stage==2?&number_element:&second_number);
    dkr_game_context_write(&call);
}
DKR_CALLBACK(after_hud_element_render) void banner_draw_after(DkrU32 dl,DkrU32 mtx,DkrU32 vertex,DkrU32 element) {
    (void)dl;(void)mtx;(void)vertex;
    if(!inside||element!=trigger_hud+3*32)return;
    if(!stage){
        if(used)return;
        used=1;
        saved_colour=read_native(s_colour,4);colour_saved=1;
        if(!prim_colour(0xFFFFFFA0U)){restore_colour();return;}
        write_native(s_colour,4,0xFFFFFFA0U);stage=1;dkr_game_repeat_original();
    }else if(stage==1){stage=2;dkr_game_repeat_original();}
    else if(stage==2&&two_digits){stage=3;dkr_game_repeat_original();}
    else {prim_colour(0xFFFFFFFFU);restore_colour();stage=0;log_rendered();}
}
