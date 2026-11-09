# Older Wizpig downloads for DKR-R 1.0.14

These are the older Wizpig I and II compatibility previews, kept here for rollback. For the newer 1.0.15 versions with fewer bananas and the Wizpig I AI adjustment, use the [latest preview page](../WIZPIG-PREVIEW-UPDATE.md).

Both older courses turn the Wizpig tracks into regular races: eight racers, a stationary start, three laps, bananas and all five balloon colours. Wizpig I is a car race with 12 balloons and 36 bananas. Wizpig II is a plane race with 34 balloons and 36 bananas.

Use the complete official **DKR-R 1.0.14** release and your own **US Rev A / v1.1 (`us.v80`)** game data. No replacement executable, companion code mod or separate everyday profile is needed.

## Downloads

- [Wizpig I compatibility preview](../packages/Wizpig-I-USRevA-Catalogue-Naming-Test.zip?raw=1), 2,239 bytes.
- [Wizpig II compatibility preview](../packages/Wizpig-II-USRevA-Catalogue-Naming-Test.zip?raw=1), 3,414 bytes.
- [SHA-256 checksums](../SHA256SUMS.txt).

These are the exact files used in the mixed-track Linux test. Keep them as ZIPs; don't rename them to `.dkrmap`. GitHub's **Code > Download ZIP** gives you the whole repository, not an importable course.

The still older `Pickup-Fix-r5.zip` files remain in `packages` for historical rollback. They use the earlier naming workaround, so they aren't the same as these compatibility previews. Don't enable old and new versions of the same Wizpig course together.

## What did this version fix?

The courses now take their names from their manifests and DKR-R's Custom Tracks catalogue, like Splashdown Pass and Strangled Shrine. Removing the unnecessary legacy `LEVEL_NAMES` addition and four-byte `name.bin` avoids the combined-name loading fault.

The track IDs, preparation credit, race headers and both object maps are unchanged from r5. This was a naming fix, so it doesn't change pickups, checkpoints, starts, laps, scenery or race behaviour.

## Install

1. Use the complete official DKR-R 1.0.14 package and your own compatible ROM. You don't need a custom game build for this fix.
2. Close the game and back up your existing Wizpig packages and saves.
3. Start DKR-R and import the two individual ZIPs through Custom Tracks in your normal profile. Replace only `wizpig1-ordinary-race-us-v80` and `wizpig2-ordinary-race-us-v80`, with one version of each enabled.
4. Leave Splashdown Pass, Strangled Shrine, texture packs and other unrelated content in place. Turn Session mods ON.
5. Try both Wizpig races with your other maps enabled. Check pickup reachability, lap and checkpoint counting, AI and a complete race. Windows is still a playtest target for these previews.

The separate Linux test profile was only used to keep testing isolated. You don't need to move your normal setup into a new profile or remove other mods. Don't overwrite your saves. To go back, restore your previous Wizpig packages.

## What was tested together?

The unmodified official Linux 1.0.14 game ran with Wizpig I, Wizpig II, Splashdown Pass, Strangled Shrine and both community HD texture packs enabled in one profile.

- All four course names displayed correctly.
- Wizpig I loaded a car race with AI, geometry and bananas visible. Acceleration moved Diddy forward.
- Wizpig II loaded a plane race with AI, geometry and bananas visible.
- Strangled Shrine loaded a hovercraft race with AI, scenery and item balloons visible.
- Splashdown Pass loaded its assets and menu preview, but its race wasn't entered.
- The successful session had no asset-bounds failure, map-load failure or crash, and closed normally.

This shows that specific combination working at race entry. It doesn't guarantee every mod combination. Full races, every pickup and checkpoint, audio, Windows, arbitrary code mods and multiplayer weren't checked in this pass. Software Vulkan and dummy audio were used, so this doesn't establish performance on your machine or audible sound quality.

See the [full test record](../validation/MIXED-GAME-VALIDATION.md) for the nonfatal warnings and earlier renderer failure.

## Earlier r5 pickup changes

- **Wizpig I:** all 12 balloon anchors were lowered by 38 units and all 36 banana anchors by 18 units. Their X/Z positions stayed the same.
- **Wizpig II:** five added balloons were moved. Minimum red/blue anchor separation increased from 509.51 to 806.68 units. Bananas, original balloons, hazards and scenery stayed the same.
- Both kept their eight-racer grids, stationary starts and three laps.

The old r5 separate-profile limitation doesn't apply to the combination tested with these later compatibility previews.

## Package and importer checks

Eight official-importer, asset-bank and catalogue tests passed. They covered all four maps, Wizpig only, community maps only and all maps re-enabled. Name-bank checks covered both US revisions, including banks with the texture packs loaded. **The courses themselves still require v80. Those name checks don't add v77 gameplay support.**

Run `python3 verify_packages.py` to check the supplied archive and payload hashes. It doesn't launch the game or repeat the gameplay tests.

- [Package checks](../validation/PACKAGE-CHECKS.json)
- [Importer results](../validation/IMPORTER-VALIDATION.json)
- [Historical r5 checks](../validation/r5)

These records describe the older compatibility previews. Newer downloads have their own checks linked from their release notes.

## Credits and rights

Based on the Wizpig courses in *Diddy Kong Racing*, developed by Rare and published by Nintendo. This is an unofficial community adaptation for DKR-R, with no claim of official affiliation or endorsement.

The manifests retain the existing preparation author, **“Local preparation.”** Repository ownership does not imply authorship of the original game or courses.

These Wizpig packages contain manifests, modified track headers and object maps. No full ROM, executable, external texture pack or music is included. Original game content remains subject to its existing rights; this repository grants no license to that content. No open-source license has been declared for the track packages.
