#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TAJ_TEST
#include "../main.c"
static unsigned char ram[0x800000],snapshot[0x224+59*32];
static DkrGameCall ctx;static unsigned repeats,rendered,online,revision=80,tick,scene=1;
static const DkrU32 base=0x80001000,header=0x80010000,hud=0x80011000,racer=0x80012000,dlbase=0x80020000;
static const char* names[]={"gGameMode","gMapId","gCurrentLevelHeader","gIsTimeTrial","gIsPaused","gCurrentHud","gHUDNumPlayers","gHudDL","gHudColour"};
static unsigned catalogue_duplicate,catalogue_bad,catalogue_other;
DkrU32 test_read(DkrU32 a,unsigned n){assert(range(a,n,1));unsigned o=a-0x80000000U,v=0;for(unsigned i=0;i<n;++i)v=v*256+ram[o+i];return v;}
void test_write(DkrU32 a,unsigned n,DkrU32 v){assert(range(a,n,1));unsigned o=a-0x80000000U;for(unsigned i=0;i<n;++i){ram[o+n-1-i]=v&255;v>>=8;}}
void* dkr_game_symbol(const char* name){for(unsigned i=0;i<9;++i)if(!strcmp(name,names[i]))return(void*)(uintptr_t)(base+i*4);return 0;}
DkrU32 dkr_game_symbol_size(const char* name){return dkr_game_symbol(name)?4:0;}
int dkr2_session(Dkr2Session* s){s->revision=revision;s->online=online;s->tick=tick;s->scene_generation=scene;return 0;}
int dkr2_catalogue(const char* type,unsigned index,char* out,unsigned cap){assert(!strcmp(type,"courses"));if(index>(catalogue_duplicate?1U:0U))return 1;const char* s=catalogue_bad?"bad":catalogue_other?"{\"id\":\"dkrmap:unrelated\",\"carrier\":81}":"{\"id\":\"dkrmap:taj1-five-lap-car-race-us-v80\",\"carrier\":81}";assert(strlen(s)+1<cap);strcpy(out,s);return(int)strlen(s)+1;}
void dkr_log(const char* p){(void)p;}
DkrU32 dkr_game_context_read(DkrGameCall* c){*c=ctx;return 1;}
DkrU32 dkr_game_context_write(const DkrGameCall* c){ctx=*c;return 1;}
DkrU32 dkr_game_repeat_original(void){++repeats;return 1;}
static void setup(unsigned lap,unsigned age){memset(ram,0,sizeof ram);online=0;revision=80;tick=0;scene=1;banner_boot();assert(enabled);test_write(s_map,4,81);test_write(s_header,4,header);test_write(s_hud,4,hud);test_write(s_dl,4,dlbase);test_write(s_colour,4,0xFFFFFFFE);test_write(header+0x4b,1,99);test_write(racer+0x193,1,lap);test_write(racer+0x194,1,lap);clock=(BannerClock){1,scene,81,racer,99,lap,0,age};}
static void draw(void){unsigned left=0;rendered=repeats=0;do{ctx=(DkrGameCall){0};ctx.r[7]=hud+3*32;banner_draw_before(0,0,0,hud+3*32);++rendered;banner_draw_after(0,0,0,hud+3*32);left++;assert(left<=4);}while(repeats>=left);}
static void preserved(void){memcpy(snapshot,ram+(racer-0x80000000),0x224);memcpy(snapshot+0x224,ram+(hud-0x80000000),59*32);banner_lap_begin(racer,2);draw();banner_lap_end();assert(!memcmp(snapshot,ram+(racer-0x80000000),0x224));assert(!memcmp(snapshot+0x224,ram+(hud-0x80000000),59*32));assert(test_read(s_colour,4)==0xFFFFFFFE);assert(!inside&&!stage&&!colour_saved);}
int main(void){
 BannerLayout b;
 for(unsigned total=1;total<=99;total++)for(unsigned lap=0;lap<102;lap++)for(unsigned age=0;age<100;age++){
  int ok=banner_layout(total,lap,lap,age,&b);assert(ok==(total>3&&lap>=2&&lap<=97&&lap+1<total&&age<75));if(ok)assert(b.digit==lap+1);
 }
 assert(banner_layout(10,2,2,30,&b)&&b.lap_x==-22&&b.digit_x==37);assert(!banner_layout(4,3,3,20,&b));assert(!banner_layout(9,8,8,20,&b));assert(banner_layout(10,8,8,30,&b)&&b.digit==9);
 for(unsigned lap=0;lap<102;lap++){setup(lap,30);preserved();assert(rendered==((lap>=2&&lap<=97)?(lap>=9?4U:3U):1U));}
 setup(2,30);banner_lap_begin(racer,2);assert(inside&&number_element.frame==3&&number_element.scale==2.375f&&number_element.x==178&&number_element.y==71);draw();assert(rendered==3&&repeats==2);draw();assert(rendered==1);banner_lap_end();
 setup(97,30);banner_lap_begin(racer,2);assert(inside&&number_element.frame==9&&second_number.frame==8&&two_digits&&number_element.x==162.0625f&&second_number.x==193.9375f);banner_unload();assert(!inside&&!clock.valid);
 /* Every two-digit value uses the visible glyph bounds, with exactly one
  * logical pixel between digits and a centered combined word/number group. */
 const unsigned left[]={1,3,1,1,1,1,2,2,1,2},right[]={14,13,14,14,14,13,14,14,14,14};
 for(unsigned value=10;value<=98;value++){
  unsigned tens=value/10,ones=value%10;setup(value-1,30);banner_lap_begin(racer,2);
  float a=number_element.x+left[tens]*2.375f,b=number_element.x+right[tens]*2.375f;
  float c=second_number.x+left[ones]*2.375f,d=second_number.x+right[ones]*2.375f;
  assert(inside&&two_digits&&c-b==1.0f&&(a+d)/2.0f==197.0f);
  assert(a-(160.0f+lap_element.x+34.0f)==6.0f);
  assert((160.0f+lap_element.x-34.0f+d)/2.0f==160.0f);
 }
 for(unsigned age=75;age<100;age++){setup(2,age);preserved();assert(rendered==1);}
 const DkrU32 gates[]={base,base+16,base+24,racer,racer+0x1d8,racer+0x194};
 const unsigned sizes[]={4,1,4,2,1,1}; const unsigned values[]={1,1,1,1,1,1};
 for(unsigned i=0;i<sizeof gates/sizeof *gates;++i){setup(2,30);test_write(gates[i],sizes[i],values[i]);banner_lap_begin(racer,2);assert(!inside);}
 setup(2,30);online=1;banner_lap_begin(racer,2);assert(!inside);setup(2,30);revision=77;banner_lap_begin(racer,2);assert(inside);setup(2,30);revision=78;banner_lap_begin(racer,2);assert(!inside);
 /* A track-independent hook: every byte-sized map ID and supported total.
  * This checks the policy, not a claim to have driven these courses. */
 setup(2,30);
 for(unsigned map=0;map<256;map++)for(unsigned total=4;total<=99;total++){
  test_write(s_map,4,map);test_write(header+0x4b,1,total);
  const unsigned laps[]={2,total-2,total-1};
  for(unsigned i=0;i<3;i++){
   unsigned lap=laps[i];test_write(racer+0x193,1,lap);test_write(racer+0x194,1,lap);
   clock=(BannerClock){1,scene,map,racer,total,lap,tick,30};
   banner_lap_begin(racer,2);assert(inside==(i<2));banner_lap_end();
  }
 }
 setup(2,30);test_write(base+12,4,1);banner_lap_begin(racer,2);assert(inside);banner_lap_end(); /* Time Trial is not excluded. */
 setup(2,30);test_write(s_dl,4,0);banner_lap_begin(racer,2);draw();assert(rendered==1&&!colour_saved&&test_read(s_colour,4)==0xFFFFFFFE);
 BannerClock c={0};assert(banner_clock(&c,1,5,100,10,0,0,2,0)==75);assert(banner_clock(&c,1,5,100,10,2,1,2,0)==0);assert(banner_clock(&c,1,5,100,10,2,16,2,0)==30);assert(banner_clock(&c,1,5,100,10,2,16,2,0)==30);assert(banner_clock(&c,1,5,100,10,2,50,2,1)==30);assert(banner_clock(&c,1,5,100,10,2,51,2,0)==32);assert(banner_clock(&c,1,5,100,10,2,100,2,0)==75);assert(banner_clock(&c,1,5,100,10,3,101,2,0)==0);assert(banner_clock(&c,2,5,100,10,3,102,2,0)==75);
 setup(2,30);test_write(racer+0x128+2*4,4,0xFFFFFFFF);preserved();assert(rendered==3); /* relocated or invalid native timer is irrelevant */
 puts("PASS: 1009800 total/lap/age combinations; LAP3-98; final precedence; relocated timers; pause/resume; restart; revision/mode gates; bounded repeats; racer/HUD preservation; colour restore");
}
