#include <stdint.h>
typedef uint32_t DkrU32;typedef uint64_t DkrU64;typedef int32_t DkrS32;
#define DKR_CALLBACK(event)
#define DKR2_OK 0
#define DKR2_END 1
typedef struct DkrGameCall{DkrU64 r[32],f[32],hi,lo;DkrU32 fcsr,padding;}DkrGameCall;
typedef struct Dkr2Session{unsigned size,api,revision,online,scene_generation,tick,entities,racers,development,phase,instruction_budget,native_budget;}Dkr2Session;
DkrU32 test_read(DkrU32,unsigned);void test_write(DkrU32,unsigned,DkrU32);
void* dkr_game_symbol(const char*);DkrU32 dkr_game_symbol_size(const char*);
int dkr2_session(Dkr2Session*);int dkr2_catalogue(const char*,unsigned,char*,unsigned);
void dkr_log(const char*);DkrU32 dkr_game_context_read(DkrGameCall*);DkrU32 dkr_game_context_write(const DkrGameCall*);
DkrU32 dkr_game_repeat_original(void);

enum { DKR_AUDIO_SOUND=0 };
DkrU32 dkr_audio_command(DkrU32,DkrS32);
