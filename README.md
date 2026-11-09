# DKR Race DLC

## Universal Silent Lap 3–98 Banners v1

[Download the Custom Magic Code](magic-codes/universal-lap-banners-v1/dkr_universal_lap_banners.nrm?raw=1) for **DKR-R 1.0.15**. Adds original LAP artwork and compact native HUD digits on intermediate laps of **4–99-lap offline single-player races**, without a track-name restriction or added voice. Native Lap 2 and the actual Final Lap stay unchanged. This code does not change the lap count.

Designed for ordinary, boss, Taj and Time Trial races using the standard lap HUD. Tested with official Custom Trophies Creator 1.0.2. Online, split-screen and non-lap modes are unsupported; every course and Windows gameplay have not been qualified. Corrected 10, 11 and 20 were visually checked; 98 has automated and native draw-log evidence, but no corrected screenshot. [Installation, source, screenshots and exact test limits](magic-codes/universal-lap-banners-v1/README.md).

More places to race in **Diddy Kong Racing Recompiled**. These mods turn the boss courses and Taj's challenges into races with a full eight-racer grid.

Pick a mountain sprint, a hovercraft race through Bubbler's lagoon, a flight around Smokey's course, or a few laps around Timber's Island. Each course is a separate download, so just grab the ones you want.

You'll need **DKR-R 1.0.15** and your own **US Rev A / v1.1 (`us.v80`)** game data for the current downloads.

## Pick a race

### Tricky: one lap up the mountain

Tricky's course becomes an eight-racer car sprint. It's one lap, with the original rolling boulders back in action, 9 bananas along the route and an invisible guardrail along the inner cliff. The original route, grid and checkpoints stay the same.

[Download Tricky](packages/Tricky-Mountain-Race-v1.zip?raw=1) · [Download the required sprint companion](packages/Tricky-Sprint-Companion-0.3.5.nrm?raw=1) · [Setup and course notes](docs/TRICKY-V1.md)

**Tricky needs both downloads.** The companion handles CPU finishing, stopping after the line and normal-speed sprint music. Use version **0.3.5**, set its option to **1**, then restart. Play offline.

### Bubbler: take the hovercraft

Race Bubbler's lagoon as a regular hovercraft course. This version has 9 bananas spread across six spots, with a mix of singles and pairs.

[Download Bubbler](packages/Bubbler-Lagoon-Race-v1.zip?raw=1) · [Preview](screenshots/bubbler-race-user-preview.png)

### Smokey: take to the air

Smokey's mountain course gets a regular plane race. Like Bubbler, it has 9 bananas across six spots. These two updates thin out the bananas without changing the vehicle physics, balloons or hazards.

[Download Smokey](packages/Smokey-Mountain-Race-v1.zip?raw=1) · [Preview](screenshots/smokey-race-user-preview.png) · [Bubbler and Smokey setup](BUBBLER-SMOKEY-V1.md)

Neither needs a companion mod. The previews show earlier versions with more bananas.

### Taj: three ways around Timber's Island

Taj's routes now have seven other racers to go up against. The stone Wizpig head is back, along with all four world entrances. The gates stay closed, so the scenery is there without sending you into Adventure mode.

- [Taj I: five-lap car race](packages/Taj-I-Five-Lap-Car-Race-v1.zip?raw=1). The longer race, with four rows of balloon choices and 17 bananas.
- [Taj II: hovercraft race](packages/Taj-II-Hovercraft-Race-v1.zip?raw=1). Three laps, six rows of balloon choices and 9 bananas.
- [Taj III: plane race](packages/Taj-III-Plane-Race-v1.zip?raw=1). Three laps, six rows of balloon choices and 9 bananas.

No companion needed. [Setup, screenshots and course notes](TAJ-I-II-III-V1.md).

### Wizpig I and II: bring a full grid

Play Wizpig I in the car or Wizpig II in the plane, now as three-lap races with eight racers, stationary starts and all five balloon colours. The latest previews have 18 bananas each, down from 36. Wizpig I also has a small AI route-height adjustment near the start and finish.

[Download Wizpig I](packages/Wizpig-I-USRevA-Banana-AI-Clearance-Preview-r1.zip?raw=1) · [Download Wizpig II](packages/Wizpig-II-USRevA-Banana-Balance-Preview-r1.zip?raw=1) · [Setup and preview notes](WIZPIG-PREVIEW-UPDATE.md)

No companion needed. **These are still playtest previews.** Wizpig II can occasionally leave a CPU stuck, and its sky hasn't been changed.

## Get playing

1. Close DKR-R and back up your saves and any older version of the course you're replacing.
2. Download the individual course ZIP you want. Keep it as a ZIP. GitHub's **Code > Download ZIP** gives you the whole repository, which isn't an importable course.
3. Start DKR-R, open **Mods / Hacks > Import mods > DKR-R tracks** and import it.
4. Keep just one version of each course enabled. Leave your other tracks and saves in place, turn Session mods ON, then choose the course in Custom Tracks.
5. For Tricky, also follow the [companion setup](docs/TRICKY-V1.md#install). The course ZIP alone isn't enough.

To go back to an older version, close the game and restore that course's previous ZIP. For Tricky, restore its matching companion too.

## A quick heads-up

The downloads have passed package checks and Linux race tests, but the amount of testing varies by course. Full human races, Windows gameplay, audio, multiplayer and every possible mod combination still need checking. Each course's notes explain what was tested and what's left.

Looking for an older Wizpig download? The [1.0.14 versions and setup](docs/WIZPIG-1.0.14.md) are still here for rollback. There's also a [change log](RELEASE-NOTES.md), [checksums](SHA256SUMS.txt) and the detailed records in [validation](validation).

## Credits and rights

Based on *Diddy Kong Racing*, developed by Rare and published by Nintendo. These are unofficial community adaptations for DKR-R, with no claim of official affiliation or endorsement.

The manifests retain the existing preparation author, **“Local preparation.”** Repository ownership does not imply authorship of the original game or courses.

No full ROM, executable, external texture pack or music is included. Some courses include adapted native level geometry; the individual notes list what's in each download. Original game content remains subject to its existing rights; this repository grants no license to that content.

This repository contains released packages and their test records, not a complete build-source distribution. No open-source license has been declared for the track packages.
