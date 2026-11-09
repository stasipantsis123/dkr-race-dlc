# Bubbler and Smokey v1

Two ordinary-race conversions for official DKR-R 1.0.15 with your own US Rev A/v1.1 (`us.v80`) game data.

- **Bubbler - Lagoon Race v1:** hovercraft race, 9 bananas in six stations, with three singles and three pairs.
- **Smokey - Mountain Race v1:** plane race, 9 bananas in six stations, with three singles and three pairs.

The v1 packages are byte-identical to the banana-thinning candidates. Each removes nine ordinary banana objects from its prior private edition. Every surviving object stays at its original position, and each station retains its middle banana. Balloons, hazards, scenery records, checkpoints, starts, race headers and course IDs are unchanged by this thinning. No game engine or vehicle physics changes are included.

## Install

1. Use the complete official DKR-R 1.0.15 release and your own US Rev A/v1.1 ROM.
2. Download each individual course ZIP from `packages`, not this entire repository ZIP.
3. Back up the matching older track, then use **Import mods > DKR-R tracks**.
4. Replace only the matching track ID. Do not keep duplicate revisions enabled. Preserve your saves and unrelated mods.
5. Enable session mods and select the course in Custom Tracks.

Bubbler and Smokey require no companion code mod or replacement executable. To roll back, restore your previous matching track ZIP.

## Verification

Archive integrity, exact hashes, six preserved banana stations, deletion-only object comparison and unchanged non-banana records passed. The runtime-profile course files match every archive member. The upstream DKR-R pattern guard reported zero new problems.

Both exact v1 course payloads entered their races on official Linux DKR-R 1.0.15 in separate 120-second smoke tests. Human acceleration moved each vehicle. Both processes exited 0 and logged clean shutdown. The Bubbler run recorded all seven CPUs finishing three laps. The Smokey run recorded 4 of seven CPU finishes before the time limit. These were software-Vulkan tests with dummy audio and the read-only diagnostic observer; no gameplay companion was enabled. Course files remained byte-exact after testing.

An earlier Bubbler attempt in a non-desktop shell failed at SDL/UDEV initialization before graphics; the subsequent desktop-terminal run above completed successfully.

Full human-race completion, every pickup, Windows, multiplayer, audio and arbitrary combinations with other mods are not qualified by this release check.

## Screenshots

The supplied gameplay screenshots show earlier private editions before banana thinning. They illustrate the courses and are not evidence of v1 banana counts or runtime testing.

## Credits and rights

Based on the Bubbler and Smokey courses in *Diddy Kong Racing* by Rare/Nintendo. Unofficial community adaptations for DKR-R; no official affiliation or endorsement is claimed. The package preparation credit remains **Local preparation**. No ROM, executable, source models, textures or music are included. No license to original game content is granted.
