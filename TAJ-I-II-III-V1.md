# Taj I, II and III v1

Taj's routes around Timber's Island, now with a full eight-racer grid. Pick the car, hovercraft or plane, with rows of balloons giving you a choice of items along the way.

The stone Wizpig head and all four world entrances are back too. Dino Domain, Snowflake Mountain, Sherbet Island and Dragon Forest keep their closed gates and original balloon numbers. They're scenery here: the gates stay solid and won't open, warp you away or trigger Adventure dialogue, cutscenes, unlocks or save progress.

## Choose your race

- [Taj I - Five-Lap Car Race v1](packages/Taj-I-Five-Lap-Car-Race-v1.zip?raw=1): five laps, four rows of four balloons in mixed colour orders, and 17 bananas split into five singles and six pairs.
- [Taj II - Hovercraft Race v1](packages/Taj-II-Hovercraft-Race-v1.zip?raw=1): three laps, six rows of four balloons, and 9 bananas split into three singles and three pairs.
- [Taj III - Plane Race v1](packages/Taj-III-Plane-Race-v1.zip?raw=1): three laps, six rows of four balloons, and 9 bananas split into three singles and three pairs.

Use official **DKR-R 1.0.15** with your own **US Rev A/v1.1 (`us.v80`)** game data. No companion code mod or replacement executable is needed.

## Install

1. Use the complete official DKR-R 1.0.15 package with your own compatible ROM.
2. Download the individual ZIPs you want. Don't import the whole repository ZIP.
3. Close the game and back up any older version of the Taj course you're replacing.
4. Start DKR-R, open **Mods / Hacks > Import mods > DKR-R tracks** and import each ZIP.
5. Keep one version of each course enabled, leave your saves and unrelated mods in place, and turn Session mods ON.

The course IDs are `taj1-five-lap-car-race-us-v80`, `taj2-standalone-race-us-v80` and `taj3-standalone-race-us-v80`. To go back, restore the previous ZIP for the matching course.

## What was tested?

All three downloads loaded eight racers into ordinary Linux races, and all seven CPUs finished at the right lap count. Each test closed cleanly, with no renderer handoff fallback, mismatch or overflow.

The four closed gates and complete stone head were visually checked. Sherbet's beach entrance was checked separately in the hovercraft and plane courses. Contact with the Dino gate and frame left the gate shut, with no Adventure text or course transition. Snowflake's original raised ledge is unchanged; its door was checked visually, not tested for reachability.

Human finishes, every driving line and balloon lane, restarts, Windows, multiplayer, audio and other mod combinations still need testing.

<details>
<summary>Package checks and test details</summary>

The downloads are identical to the tested scenery and pickup versions, apart from their public download filenames. Course IDs, names and preparation credits are unchanged. The headers and both object maps match the preceding pickup-row builds exactly, so the scenery addition leaves their starts, checkpoints, lap counts, vehicles and pickups alone.

Checks passed for archive hashes, model layout and round trips, fixed gate-number frames, render passes, engine limits and original collision relationships. The conservative runtime arena estimate is 371,616 of 535,040 bytes. Added collision was checked against the stored facets, and the diagnostic checkpoint chords crossed no added solid face.

The scenery inspection used temporary start-position test files. Those aren't in the downloads. Runtime tests used software Vulkan and dummy audio, so they don't establish performance on your machine or audible sound quality.

[Package and runtime results](validation/TAJ-I-II-III-V1.json)

</details>

## Screenshots

- [Taj I: car](screenshots/taj-i-race-v1.png)
- [Taj II: hovercraft](screenshots/taj-ii-race-v1.png)
- [Taj III: plane](screenshots/taj-iii-race-v1.png)

These supplied gameplay images show the matching courses. They don't verify the exact package revision or every restored piece of scenery.

## Credits and rights

Based on the Taj races and Timber's Island in *Diddy Kong Racing*, developed by Rare and published by Nintendo. These are unofficial community adaptations for DKR-R, with no official affiliation or endorsement. Package preparation credit remains **Local preparation**.

These packages contain manifests, track headers, object maps and adapted native level geometry, including the restored gate and head meshes. They contain no full ROM, executable, saves, diagnostic mod, external texture pack or music. Original game content retains its existing rights; no license to that content is granted here. No open-source license has been declared for the track packages.
