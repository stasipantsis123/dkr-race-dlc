# Taj I, II and III v1

Three standalone, eight-racer Taj courses for official **DKR-R 1.0.15** and your own **US Rev A/v1.1 (`us.v80`)** game data. No companion code mod or replacement executable is required.

## Downloads

- [Taj I - Five-Lap Car Race v1](packages/Taj-I-Five-Lap-Car-Race-v1.zip?raw=1): five laps, four rows of four balloon choices in mixed color orders, and 17 bananas in five singles and six pairs.
- [Taj II - Hovercraft Race v1](packages/Taj-II-Hovercraft-Race-v1.zip?raw=1): three laps, six rows of four balloon choices, and 9 bananas in three singles and three pairs.
- [Taj III - Plane Race v1](packages/Taj-III-Plane-Race-v1.zip?raw=1): three laps, six rows of four balloon choices, and 9 bananas in three singles and three pairs.

All three restore the native stone Wizpig head and the four world entrances: Dino Domain, Snowflake Mountain, Sherbet Island and Dragon Forest. The gates stay closed with fixed native balloon numbers. The restored assets are inert course geometry, with no Adventure opening, unlock, dialogue, warp, cutscene or save-progress behavior. The closed gates retain solid collision.

The v1 downloads are byte-for-byte copies of the tested scenery/pickup candidates, with public download filenames. Course IDs, names and preparation credits are unchanged. Headers and both object maps match the preceding pickup-row builds exactly; the scenery addition preserves their starts, checkpoints, lap counts, vehicles and pickups.

## Install

1. Use the complete official DKR-R 1.0.15 package with your own compatible ROM.
2. Download each individual course ZIP above. Do not import the whole repository ZIP.
3. Close the game and keep a backup of any previous matching Taj package.
4. Import through **Mods / Hacks > Import mods > DKR-R tracks**.
5. Replace only the matching course ID. Keep one version of each enabled, preserve saves and unrelated mods, and enable session mods.

The IDs are `taj1-five-lap-car-race-us-v80`, `taj2-standalone-race-us-v80` and `taj3-standalone-race-us-v80`. Restore your previous matching ZIP to roll back.

## Verification and limits

The exact delivered files loaded eight racers in ordinary Linux races. All seven CPU racers finished each course at its intended lap count. All three stopped cleanly with no renderer handoff fallback, mismatch or overflow.

All four closed gates and the full stone head were visually inspected. The Sherbet beach entrance was independently viewed in both Taj II and Taj III. Dino gate/frame contact left the gate closed without Adventure text or a course transition. Snowflake's original raised ledge was left unchanged; its inspection was visual, not a claim about reaching the door.

Archive hashes, model layout/round trips, fixed gate-number frames, render passes, engine limits and original collision relationships passed checks. The model's conservative runtime arena estimate is 371,616 of 535,040 bytes. Added collision passed checks against the actual stored facets, and diagnostic checkpoint chords crossed no added solid face. See [package and runtime validation](validation/TAJ-I-II-III-V1.json).

These checks do not qualify every human driving line or balloon lane, human-finished results, restart flows, Windows, multiplayer, audio or arbitrary mod combinations. The scenery inspection used disposable start-position fixtures; those are not in the downloads. The runtime used software Vulkan and dummy audio, so it is not target-machine performance or audio evidence.

## Screenshots

The user-supplied images show the matching car, hovercraft and plane courses. They are gameplay illustrations, not proof of the exact package revision or every restored asset:

- [Taj I](screenshots/taj-i-race-v1.png)
- [Taj II](screenshots/taj-ii-race-v1.png)
- [Taj III](screenshots/taj-iii-race-v1.png)

## Credits and rights

Based on the Taj races and Timber's Island in *Diddy Kong Racing*, developed by Rare and published by Nintendo. These are unofficial community adaptations for DKR-R, with no official affiliation or endorsement. Package preparation credit remains **Local preparation**.

These packages contain manifests, track headers, object maps and adapted native level geometry, including the restored gate and head meshes. They contain no full ROM, executable, saves, diagnostic mod, external texture pack or music. Original game content retains its existing rights; no license to that content is granted here. No open-source license has been declared for the track packages.
