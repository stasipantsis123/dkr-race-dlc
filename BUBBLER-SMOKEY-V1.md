# Bubbler and Smokey v1

Two boss courses to race with a full grid: take the hovercraft around Bubbler's lagoon, or the plane around Smokey's mountain course.

- [Download Bubbler - Lagoon Race v1](packages/Bubbler-Lagoon-Race-v1.zip?raw=1)
- [Download Smokey - Mountain Race v1](packages/Smokey-Mountain-Race-v1.zip?raw=1)

You'll need official **DKR-R 1.0.15** and your own **US Rev A/v1.1 (`us.v80`)** game data. Neither course needs a companion code mod or a replacement executable.

## What's different in v1?

Both courses have fewer bananas: 9 instead of 18. They're still spread across the same six spots, as three singles and three pairs. Each spot keeps its middle banana.

The balloons, hazards, scenery, checkpoints, starts, race settings and course IDs haven't changed. Neither have the game engine or vehicle physics. These downloads are identical to the tested banana-reduction versions, with nine banana objects removed from each earlier private edition and every remaining object left where it was.

## Install

1. Use the complete official DKR-R 1.0.15 release and your own compatible ROM.
2. Download the individual course ZIP above, not the whole repository ZIP.
3. Back up the older version of the track, then use **Import mods > DKR-R tracks**.
4. Replace only the matching track. Keep one version of each enabled, and leave your saves and other mods alone.
5. Turn Session mods ON and choose the course in Custom Tracks.

To go back, restore the previous ZIP for that course.

## What was tested?

Both downloads loaded into races on official Linux DKR-R 1.0.15. Acceleration moved each vehicle, and both games closed normally after their two-minute tests. Bubbler recorded all seven CPUs finishing three laps. Smokey recorded four of seven CPU finishes before the time limit.

Full human races, every pickup, Windows, multiplayer, audio and other mod combinations still need testing.

<details>
<summary>Package checks and test details</summary>

Archive integrity and hashes passed, as did checks that all six banana spots remained and only banana objects had been deleted. All other object records were unchanged. The installed test files matched every archive member and were still identical after testing. The upstream DKR-R pattern guard found zero new problems.

The tests used software Vulkan, dummy audio and a read-only diagnostic observer. No gameplay companion was enabled. Both processes exited with code 0 and logged clean shutdowns, but these runs don't establish audible sound quality.

An earlier Bubbler launch from a non-desktop shell failed during SDL/UDEV initialisation, before graphics started. The later desktop-terminal run completed the checks above.

[Package checks](validation/BUBBLER-SMOKEY-V1-STATIC.json) · [Runtime results](validation/BUBBLER-SMOKEY-V1-RUNTIME.json)

</details>

## Screenshots

[Bubbler](screenshots/bubbler-race-user-preview.png) · [Smokey](screenshots/smokey-race-user-preview.png)

These supplied screenshots show earlier private versions with more bananas. They're a look at the courses, not a record of v1's banana counts or test results.

## Credits and rights

Based on the Bubbler and Smokey courses in *Diddy Kong Racing* by Rare/Nintendo. Unofficial community adaptations for DKR-R; no official affiliation or endorsement is claimed. The package preparation credit remains **Local preparation**. No ROM, executable, source models, textures or music are included. No license to original game content is granted.
