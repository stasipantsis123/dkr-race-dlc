# DKR Race DLC

## Bubbler and Smokey v1

New ordinary-race conversions for **DKR-R 1.0.15**, **US Rev A / v1.1 (`us.v80`)**:

- [Bubbler - Lagoon Race v1](packages/Bubbler-Lagoon-Race-v1.zip?raw=1), hovercraft.
- [Smokey - Mountain Race v1](packages/Smokey-Mountain-Race-v1.zip?raw=1), plane.

Each has 9 bananas at six unchanged stations: three singles and three pairs. No game-engine, vehicle-physics or other course-payload changes are included in this thinning. Neither needs a gameplay companion.

**Verified:** both exact ZIPs passed package checks and 120-second Linux race-entry/acceleration smoke tests with clean exits. Bubbler logged all seven CPU finishes; Smokey logged four before the time limit. Full human races, Windows, multiplayer and audio remain unqualified. [Installation and complete limits](BUBBLER-SMOKEY-V1.md).

User-supplied previews: [Bubbler](screenshots/bubbler-race-user-preview.png) and [Smokey](screenshots/smokey-race-user-preview.png). These images show earlier private editions before banana thinning.


Unofficial custom race packages for DKR-R.

## Taj I, II and III v1

Standalone eight-racer courses for **DKR-R 1.0.15 / US Rev A (`us.v80`)**, with the latest pickup rows, all four world-entry gates frozen closed, and the native stone Wizpig head restored as inert scenery.

- [Taj I - Five-Lap Car Race v1](packages/Taj-I-Five-Lap-Car-Race-v1.zip?raw=1)
- [Taj II - Hovercraft Race v1](packages/Taj-II-Hovercraft-Race-v1.zip?raw=1)
- [Taj III - Plane Race v1](packages/Taj-III-Plane-Race-v1.zip?raw=1)

The exact downloads passed ordinary Linux race checks with all seven CPUs finishing each course. No companion mod is required. [Installation, screenshots, validation and limits](TAJ-I-II-III-V1.md).

## Latest Wizpig preview updates

For **DKR-R 1.0.15 / US Rev A (us.v80)**:

- [Wizpig I: bananas and local AI clearance](packages/Wizpig-I-USRevA-Banana-AI-Clearance-Preview-r1.zip?raw=1).
- [Wizpig II: banana balance](packages/Wizpig-II-USRevA-Banana-Balance-Preview-r1.zip?raw=1).

Both now have 18 bananas at the same 12 stations: six singles and six pairs. Wizpig I also has a small start/finish-area AI lane-height adjustment. IDs, headers, grids and balloons are retained; replace the matching course rather than enabling duplicates.

**Playtest preview:** exact candidate bytes passed fresh static checks and earlier bounded Linux CPU-finish tests. Full human races, Windows, audio and multiplayer remain unqualified. Wizpig II's earlier intermittent CPU stall remains unresolved, and **its sky is unchanged**. [Changes, installation, evidence and limitations](WIZPIG-PREVIEW-UPDATE.md).

## Retained Wizpig compatibility baseline

The following section records the older catalogue-compatible packages and their 1.0.14 tests. Use the latest preview links above for the 1.0.15 banana/AI updates; these older ZIPs remain available for rollback.

Ordinary-race conversions of Wizpig I and Wizpig II for **DKR-R 1.0.14** with **US Rev A / v1.1 (`us.v80`)** game data. These updated packages are intended to run in the **same profile as your other custom tracks**. No replacement executable or companion code mod is required.

**Preview status:** real Linux race entry passed with both Wizpig maps, Splashdown Pass, Strangled Shrine and both community HD texture packs enabled together. Windows, full-race completion and multiplayer testing remain pending. This is evidence for that specific combination, not a guarantee for every mod.

## Baseline downloads

Download and import each individual ZIP:

- [Wizpig I compatibility preview](packages/Wizpig-I-USRevA-Catalogue-Naming-Test.zip?raw=1) (2,239 bytes)
- [Wizpig II compatibility preview](packages/Wizpig-II-USRevA-Catalogue-Naming-Test.zip?raw=1) (3,414 bytes)
- [SHA-256 checksums](SHA256SUMS.txt)

The ZIPs are the exact files used in the Linux mixed-track test. Do not rename them to `.dkrmap`. **Code > Download ZIP** downloads this whole repository, not an importable course.

The older `Pickup-Fix-r5.zip` files also remain in `packages` for historical rollback. They have the earlier naming workaround and are not the catalogue-compatible baseline. Never enable old and new revisions of the same Wizpig course together.

## Baseline compatibility change

The new packages take their visible course names from the manifest and DKR-R's Custom Tracks catalogue, matching the naming approach used by Splashdown Pass and Strangled Shrine. The unnecessary legacy `LEVEL_NAMES` addition and four-byte `name.bin` were removed to avoid the combined-name loader fault.

The track IDs, preparation credit, race headers and both object-map files are otherwise unchanged from r5. This naming change does not alter pickups, checkpoints, starts, laps, scenery or race behavior.

Each course retains an eight-racer grid, a stationary start, three laps, bananas and all five balloon colors. Wizpig I has 12 balloons and 36 bananas; Wizpig II has 34 balloons and 36 bananas. See [release notes](RELEASE-NOTES.md).

## Baseline installation

1. Use the complete official **DKR-R 1.0.14** package and your own US Rev A/v1.1 ROM. A new custom game build is not needed for this fix.
2. Close the game and back up the two existing Wizpig packages and your saves.
3. In your normal profile, import the two individual preview ZIPs through the Custom Tracks importer. Replace only the matching IDs, `wizpig1-ordinary-race-us-v80` and `wizpig2-ordinary-race-us-v80`. If a duplicate is shown, keep only the new revision enabled.
4. Keep Splashdown Pass, Strangled Shrine, textures and other unrelated installed content in place. Turn Session mods ON.
5. Playtest both Wizpig courses with the other maps enabled. Check pickup reachability, checkpoint/lap progression, AI and complete races. Windows is still a playtest target for this preview.

No separate final profile is required. The isolated Linux profile was used only for safe validation. Do not overwrite saves or remove unrelated mods. To roll back, restore the previous two Wizpig packages.

## Baseline verified scope

On unmodified official **Linux DKR-R 1.0.14**, with all four maps and both community HD packs enabled:

- The game booted and displayed all four correct course captions.
- Wizpig I entered a car race with AI, geometry and bananas visible. Acceleration moved Diddy forward.
- Wizpig II entered a plane race with AI, geometry and bananas visible.
- Strangled Shrine entered a hovercraft race with AI, scenery and item balloons visible.
- Splashdown Pass was enabled with resolved assets and menu preview; its race was not entered in this test.
- No asset-bounds failure, map-load failure or crash occurred in the successful session. The game shut down normally.

Full-race completion, every pickup/checkpoint, audio, Windows, arbitrary code mods and multiplayer have not been qualified in this pass. The test used software Vulkan and dummy audio, so it does not establish target-machine performance or audio behavior. See [the validation summary](validation/MIXED-GAME-VALIDATION.md) for limitations and nonfatal warnings.

Eight additional official-importer/asset-bank/catalogue tests passed for four-map, Wizpig-only, community-only and re-enabled selections. Name-bank checks covered both US revisions, including texture-augmented banks. **The actual course payloads still require v80; those name-bank checks do not make them v77-compatible.**

Run `python3 verify_packages.py` to verify the supplied archive and payload hashes. This script does not launch the game or reproduce gameplay tests. [Package checks](validation/PACKAGE-CHECKS.json) and [importer results](validation/IMPORTER-VALIDATION.json) describe the catalogue-compatible baseline. Newer packages have separately scoped validation in their release notes. Historical r5 checks are retained under `validation/r5`.

## Credits and rights

Based on the Wizpig courses in *Diddy Kong Racing*, developed by Rare and published by Nintendo. This is an unofficial community adaptation for DKR-R, with no claim of official affiliation or endorsement.

The manifests retain the existing preparation author, **“Local preparation.”** Repository ownership does not imply authorship of the original game or courses.

The Wizpig preview packages contain manifests, modified track headers and object maps. The Taj v1 packages also include adapted native level geometry with restored gate and head meshes. No full ROM, executable, external texture pack or music is included. Original game content remains subject to its existing rights; this repository grants no license to that content.

This repository is a package release and validation record, not a complete build-source distribution. No open-source license has been declared for the track packages.
