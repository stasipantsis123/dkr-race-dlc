# Tricky - Mountain Race v1

An eight-racer, one-lap car sprint based on the original Tricky course. This release keeps the approved inner-cliff invisible guardrail, reduces the bananas from 18 to 9 across the original six stations, and restores both native boulder activation triggers. The original route, start grid and checkpoints are unchanged.

## Downloads and requirements

- Course: [Tricky-Mountain-Race-v1.zip](../packages/Tricky-Mountain-Race-v1.zip?raw=1)
- Matching companion: [Tricky-Sprint-Companion-0.3.5.nrm](../packages/Tricky-Sprint-Companion-0.3.5.nrm?raw=1)
- DKR-R 1.0.15 (the tested release; companion minimum 1.0.15) and the player's own US Rev A / v1.1 (`us.v80`) game data.
- Offline play only. Online and multiplayer behavior are not qualified.

The companion supports native CPU finishing, post-line stopping and normal-speed sprint music for the exact public v1 package. Older companion 0.3.4 does not recognize this public manifest. If the companion is absent or disabled, racers may continue driving after finishing; the guardrail is not a substitute for the companion. The course binaries are identical to the approved r12 course; only descriptive manifest wording changed for publication.

## Install

1. Close DKR-R and back up the existing Tricky course and saves.
2. Import the course ZIP using Custom Tracks. Replace only the existing `tricky-standalone-race-us-v80` course, keeping one revision enabled. Do not rename the ZIP to `.dkrmap`.
3. Open **Installed Mods → MY MODS → CUSTOM MAGIC CODES** and import the NRM, replacing the earlier `dkr_standalone_sprint_finish_experimental` companion. Use the **All** filter: **On** hides a newly imported, disabled code. Open **Details**, select **I trust this code mod**, then **Approve code** and enable it for the next game. Set its numeric option to **1** and turn Session mods ON. The separate **MAGIC CODES** panel is for stock cheats, not imported NRM files.
4. Restart the game after changing the code. Keep unrelated courses and saves in place.

Do not import a combined repository ZIP as a course. The course and companion are separate imports. To roll back, close the game and restore the previous Tricky course and matching companion. Do not keep both versions of the same logical course enabled.

## Validation and limitations

See [the exact-byte validation record](../validation/TRICKY-V1.json). The matching companion passed 1,551 host regression cases with AddressSanitizer and UndefinedBehaviorSanitizer and two byte-identical builds. This includes repeated prior regression suites, not 1,551 distinct unique behaviors. Content checks reject changed hashes and invalid model allocations while retaining the original identity, node, terminal, actor and native-result guards.

Targeted Linux 1.0.15 testing observed all seven native CPU finishes, post-line stop samples for all seven at 120, 360 and 900 active frames, and normal sequence-57 tempo 132 on human start-line crossings before and after a native restart; the game closed cleanly. The exact public course and companion bytes were used in that run. Prior exact r12/0.3.4 cloud checks observed all seven native CPU finishes and stop samples at 120, 360 and 900 active frames, plus normal music tempo before and after a native restart. The independent r12 boulder check exercised both original activation paths. The first public-pair attempt was interrupted with exit 137 before CPU finishes; no cause was established. The unchanged fresh-profile retry completed the stated checks and exited normally. The publication screenshot was supplied by the player; it does not prove a finished Windows race.

No full Windows gameplay test is claimed. Cloud checks use software rendering and dummy audio; tempo diagnostics do not establish audible quality. Close-up crowding, every wall approach, full human completion, arbitrary mod combinations and multiplayer remain unqualified. Parking retains native collision pushes and vertical settling, so a stop sample does not promise zero visible overlap.

## Credits and rights

Based on Diddy Kong Racing by Rare and Nintendo. Unofficial community adaptation with no official affiliation. The existing preparation author remains “Local preparation.” This modified course includes source-derived level geometry and object data; no full ROM, game executable, textures or music is supplied. Original game content remains subject to its existing rights. No license to that original content is granted here.
