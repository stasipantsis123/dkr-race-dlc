# Wizpig I and II preview updates

Wizpig's courses with a full racing grid: eight racers, three laps, a stationary start and all five balloon colours. Take the car through Wizpig I or the plane through Wizpig II.

These previews were published on **9 November 2026** for official **DKR-R 1.0.15** and your own **US Rev A / v1.1 (`us.v80`)** game data. Neither needs a companion mod.

## Download

- [Wizpig I preview r1](packages/Wizpig-I-USRevA-Banana-AI-Clearance-Preview-r1.zip?raw=1), 2,149 bytes.
- [Wizpig II preview r1](packages/Wizpig-II-USRevA-Banana-Balance-Preview-r1.zip?raw=1), 3,295 bytes.

Both now have 18 bananas instead of 36, at the same twelve spots: six singles and six pairs. That layout stays the same each race.

**Wizpig II still has an occasional stuck CPU, and this update doesn't change its sky.** These are playtest previews; full human races and Windows gameplay still need checking.

## What's changed?

### Wizpig I

Along with fewer bananas, there's a small AI route-height adjustment around six flat start/finish checkpoint controls. All 12 balloons stay in place, and the human checkpoint planes, starting grid and road geometry are unchanged.

Linux tests recorded all seven CPUs finishing three laps, both with the player idle at the grid and in a later run where the player moved nearby first. That supports this local adjustment in those tests, but it isn't a fix for every AI problem or every part of the route.

### Wizpig II

Only bananas were removed. All 34 balloons, the other objects, checkpoints, grid, geometry and sky stay as they were.

Linux tests recorded seven CPU finishes in a fresh idle-start run and in a separate mixed-mod run. **An earlier run still left CPU 6 stuck at lap 2, checkpoint 4.** The later successful runs don't mean that problem is fixed.

There's no skybox-speed fix here. A matched study logged animation rates close to stock, but how fast the sky looks in motion still needs checking.

## Install or update

1. Download each individual course ZIP, not the whole repository ZIP.
2. Close the game and back up the older matching package and your saves.
3. Start DKR-R, import the course through Custom Tracks and replace only the matching Wizpig course.
4. Keep one version of each course enabled and turn Session mods ON. Leave your other maps, mods and saves in place.

The IDs are still `wizpig1-ordinary-race-us-v80` and `wizpig2-ordinary-race-us-v80`. They'll appear as **Wizpig I - Race** and **Wizpig II - Race**. The manifests, credits, eight-racer grids, stationary starts and three-lap settings are unchanged.

The older catalogue-compatible ZIPs are still in `packages` if you need to go back. See the [older-version notes](docs/WIZPIG-1.0.14.md) for their setup.

## Giving them a playtest?

Check that each course appears once, then try a full three-lap race, a finish and a restart. Banana collection, balloon upgrades and checkpoint/lap counting all need a proper human playthrough.

It also helps to check whether all seven CPUs finish across fresh starts and restarts, including when you stay idle at the start. On Wizpig I, watch their contact with the road around the changed approaches and nearby sections. On Wizpig II, compare the sky's movement with stock under the same conditions.

If something goes wrong, include your game version, operating system, enabled mods, course, lap and checkpoint or nearby landmark. Restore the older course if this version isn't working for you.

Audio, multiplayer and every possible mod combination haven't been verified either.

<details>
<summary>Package checks and detailed test history</summary>

Both ZIPs are identical to the tested candidates; only the public download filenames changed. No new runtime test was done just for publication. The earlier runtime results below apply to these exact files.

Fresh checks passed for ZIP integrity, source archive identity, payload hashes, unchanged IDs and manifests, banana-only deletions, the six single/six pair layout, balloon preservation and the precise Wizpig I structure-byte change. Surviving pickup records and positions are unchanged. Each archive contains four files: a manifest, a header and two object maps. No ROM, executable, private profile, save, observer, companion, model, texture or music file is included.

For Wizpig I, 24 signed AI lane-height bytes changed from 0 to 5, adding 10 world units at six start/finish-area controls. Interpolation also affects neighbouring spline sections. A fresh banana-only comparison run reproduced seven below-road stalls; only those 24 bytes differed among the controlled inputs. Random state wasn't controlled, so this doesn't establish deterministic cause and effect. The later nearby-player run also differed from the historical failure in when and where the player moved, and the human racer drifted later. Other unchanged low or airborne sections, physical versus distant AI, collisions and lane transitions still need testing.

The mixed Wizpig II run had ten courses admitted and both community HD packs loaded. The other nine courses weren't all raced. An experimental sprint companion was enabled, but no scoped finish, parking or music intervention was observed. That observation isn't a trace of every native write. Random state wasn't controlled, so these runs don't establish a failure rate.

No full human-driven race, complete pickup/balloon-upgrade test, Windows acceptance, audio, multiplayer or universal mod compatibility has been established.

[Exact archive and payload checks](validation/wizpig-preview-r1/PACKAGE-CHECKS.json)

</details>

## File checksums

- Wizpig I SHA-256: `4d7942d3582a0242bbc9312c02aac073c631caa65e0a67dddc9e6b49892b3636`
- Wizpig II SHA-256: `aca4c47d423d11bc5a44853aec44a066b8964b0d6fa19404dd763fcc878e5184`

Based on Diddy Kong Racing by Rare/Nintendo. Existing preparation credit remains "Local preparation." Unofficial; no affiliation, endorsement or license to original game content is claimed.
