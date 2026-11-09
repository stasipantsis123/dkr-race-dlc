# Tricky - Mountain Race v1

One lap up Tricky's mountain, with seven other racers and the original rolling boulders to deal with. This car sprint keeps the original route, starting grid and checkpoints, adds an invisible guardrail along the inner cliff, and has 9 bananas across the same six spots instead of 18.

## Get both downloads

- [Tricky course ZIP](../packages/Tricky-Mountain-Race-v1.zip?raw=1)
- [Sprint companion 0.3.5](../packages/Tricky-Sprint-Companion-0.3.5.nrm?raw=1)

Use **DKR-R 1.0.15** and your own **US Rev A / v1.1 (`us.v80`)** game data. That's the tested game version and the companion's minimum requirement. **Play offline**; online and multiplayer haven't been verified.

The companion lets CPUs finish and stop after the line, and keeps the sprint music at normal speed. **Version 0.3.4 won't recognise this public course.** Without the matching companion enabled, racers may carry on driving after finishing. The guardrail doesn't replace it.

## Install

1. Close DKR-R and back up your existing Tricky course and saves.
2. Start DKR-R and import the course ZIP through Custom Tracks. Replace only `tricky-standalone-race-us-v80`, and keep one version enabled. Leave the file as a ZIP; don't rename it to `.dkrmap`.
3. Open **Installed Mods → MY MODS → CUSTOM MAGIC CODES** and import the companion NRM. Replace the earlier `dkr_standalone_sprint_finish_experimental` companion.
4. Choose the **All** filter. The **On** filter hides newly imported codes because they start disabled. Open **Details**, select **I trust this code mod**, choose **Approve code**, then enable it for the next game.
5. Set the companion's numeric option to **1**, turn Session mods ON, and restart the game.

The separate **MAGIC CODES** panel is for stock cheats, not imported NRM files. The course and companion need separate imports, and GitHub's whole-repository ZIP won't work as a course.

Keep your other courses and saves in place. To go back, close the game and restore the previous Tricky course **and its matching companion**. Don't leave two versions of the same course enabled.

## What was tested?

In the Linux 1.0.15 run, all seven CPUs finished. Checks after the finish line found all seven stopped at 120, 360 and 900 active frames. Music tempo stayed normal when the human racer crossed the start line, both before and after a native restart. The game closed cleanly.

Full human completion, close-up crowding, every wall approach, Windows gameplay, other mod combinations and multiplayer still need testing. Racers can still push against each other and settle vertically after parking, so those stop checks don't promise that you'll never see overlap. The audio checks measured tempo, not how it sounds.

<details>
<summary>Package checks and test details</summary>

All four course binary assets are identical to the approved r12 course. Only the descriptive wording in the manifest changed for publication. Both original boulder activation paths were exercised in the independent r12 check.

The companion passed 1,551 host regression cases with AddressSanitizer and UndefinedBehaviorSanitizer, and two builds produced identical files. That count includes repeated regression suites, not 1,551 different behaviours. Checks reject changed content hashes and invalid model allocations while keeping the original identity, node, terminal, actor and native-result guards.

The Linux run above used the exact public course and companion files. The music diagnostic recorded sequence 57 at tempo 132 on human start-line crossings before and after the restart. Earlier r12/0.3.4 cloud checks also recorded seven native CPU finishes, stop samples at 120, 360 and 900 active frames, and normal music tempo before and after a native restart.

The first public-pair attempt ended with exit 137 before any CPU finishes; the cause wasn't established. An unchanged retry in a fresh profile completed the checks and exited normally. Cloud tests used software rendering and dummy audio, so they don't establish audible quality. The player-supplied publication screenshot doesn't prove a completed Windows race.

[Exact-file validation record](../validation/TRICKY-V1.json)

</details>

## Credits and rights

Based on Diddy Kong Racing by Rare and Nintendo. Unofficial community adaptation with no official affiliation. The existing preparation author remains “Local preparation.” This modified course includes source-derived level geometry and object data; no full ROM, game executable, textures or music is supplied. Original game content remains subject to its existing rights. No license to that original content is granted here.
