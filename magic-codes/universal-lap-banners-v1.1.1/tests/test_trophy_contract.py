"""Static coexistence checks, not a substitute for a combined native run."""
from pathlib import Path
import json,zipfile,argparse
root=Path(__file__).resolve().parents[1]
parser=argparse.ArgumentParser()
parser.add_argument('--dkr-repo',required=True,type=Path)
parser.add_argument('--trophy-nrm',required=True,type=Path)
args=parser.parse_args()
repo=args.dkr_repo
source=(repo/'modding/examples/custom-trophy-races/main.c').read_text()
ours=(root/'main.c').read_text()
metadata=json.loads((root/'dkr.json').read_text())
with zipfile.ZipFile(args.trophy_nrm) as z:
    stock=json.loads(z.read('dkr.json'));manifest=json.loads(z.read('mod.json'))
assert manifest['id']=='dkr_custom_trophies' and manifest['version']=='1.0.2'
assert not set(metadata['systems'])&set(stock['systems'])
assert 'static DkrU32 lap_times[8][100]' in source
assert 'element!=*current_hud+4*32&&element!=*current_hud+6*32' in source
assert 'trigger_hud+3*32' in ours
for forbidden in ['0x128','dkr_race_laps(', 'dkr_racer_set(', 'dkr_game_skip_original(']:
    assert forbidden not in ours,forbidden
assert metadata['requires']['audio']==1
assert 'dkr_audio_command(DKR_AUDIO_SOUND,BANNER_WHOOSH1)' in ours
assert 'lap+1>=total' in (root/'banner_policy.h').read_text()
assert 'MaxLaps=99' in (repo/'runtime-recomp/src/game/mods/magic_code_trophy_definition.hpp').read_text()
print('PASS: bundled trophy1.0.2; disjoint systems and draw triggers; separate timing; actual-final priority; no lap-count/racer edits in banner code. Static only.')
