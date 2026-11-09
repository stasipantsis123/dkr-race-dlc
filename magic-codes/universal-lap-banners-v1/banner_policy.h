#ifndef UNIVERSAL_BANNER_POLICY_H
#define UNIVERSAL_BANNER_POLICY_H
/* DKRPC: native LAP 68x39, HUD digit 16x16 enlarged to 38x38, 6px gap,
 * alpha 160/255, slide 13 logical units/tick, exit after 60 logical units.
 * Never reads native lap_times: extended-lap mods can redirect that storage. */
typedef struct BannerLayout {float lap_x,digit_x,first_offset,digit_advance;unsigned digit,two_digits;} BannerLayout;
typedef struct BannerClock {unsigned valid,scene,map,racer,total,lap,tick,age;} BannerClock;
static unsigned banner_clock(BannerClock* c,unsigned scene,unsigned map,unsigned racer,unsigned total,unsigned lap,unsigned tick,unsigned update,unsigned paused) {
    if(!c->valid||c->scene!=scene||c->map!=map||c->racer!=racer||c->total!=total){
        *c=(BannerClock){1,scene,map,racer,total,lap,tick,75};return 75;
    }
    if(lap!=c->lap){c->lap=lap;c->tick=tick;c->age=0;return 0;}
    unsigned delta=tick-c->tick;c->tick=tick;
    if(!paused&&c->age<75&&delta){
        if(update<1||update>4||delta>75)c->age=75;
        else {c->age+=delta*update;if(c->age>75)c->age=75;}
    }
    return c->age;
}
static int banner_layout(unsigned total,unsigned lap,unsigned count_lap,unsigned age,BannerLayout* out) {
    /* Native Final Lap always wins, including four- and nine-lap races. */
    if(total<=3||total>99||lap<2||lap>97||lap+1>=total||count_lap!=lap||age>=75)return 0;
    unsigned two=lap+1>=10;
    float group_width=38.0f,first_offset=-19.0f,advance=0.0f;
    if(two){
        /* Alpha bounds of the original 16x16 HUD glyphs, not tile widths.
         * Leave one logical pixel between visible glyph bounds. This keeps
         * narrow 1s compact without squashing or changing the original art. */
        static const unsigned left[]={1,3,1,1,1,1,2,2,1,2};
        static const unsigned right[]={14,13,14,14,14,13,14,14,14,14};
        unsigned tens=(lap+1)/10,ones=(lap+1)%10;
        group_width=(float)(right[tens]-left[tens]+right[ones]-left[ones])*2.375f+1.0f;
        first_offset=-group_width/2.0f-(float)left[tens]*2.375f;
        advance=(float)(right[tens]-left[ones])*2.375f+1.0f;
    }
    float target_left=-(group_width+6.0f)/2.0f;
    float left=-200.0f+13.0f*age,right=210.0f-13.0f*age;
    if(left>target_left)left=target_left;
    if(right<37.0f)right=37.0f;
    if(age>=60){left=target_left-13.0f*(age-60);right=37.0f+13.0f*(age-60);}
    out->lap_x=left;out->digit_x=right;out->first_offset=first_offset;
    out->digit_advance=advance;out->digit=lap+1;out->two_digits=two;return 1;
}
#endif
