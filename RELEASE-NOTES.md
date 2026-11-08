# Wizpig mixed-track compatibility preview

DKR-R 1.0.14, US Rev A/v1.1 (`us.v80`). Current package filenames contain `Catalogue-Naming-Test`.

## Compatibility change

Both packages now use manifest/catalogue names rather than appending legacy `LEVEL_NAMES` data. This avoids the combined-name loader fault for these packages and allows the tested maps to coexist in one normal profile. No replacement executable or companion is required.

The three race payload files, track IDs and existing credit are unchanged from r5. The only removed file is the unnecessary four-byte `name.bin`; its manifest entry was also removed.

## Actual mixed-game validation

Official Linux DKR-R 1.0.14 booted with Wizpig I, Wizpig II, Splashdown Pass, Strangled Shrine and both community HD packs enabled together. Wizpig I, Wizpig II and Strangled Shrine entered races with AI. Wizpig I accepted acceleration. Correct captions were observed for all four maps. Splashdown Pass's race was not entered.

No asset-bounds error, map-load failure or crash occurred in the successful session. Full races, all pickups/checkpoints, audio, Windows and multiplayer remain untested in this pass. Arbitrary other mods are not covered. See [validation](validation/MIXED-GAME-VALIDATION.md).

## Retained r5 pickup changes

- Wizpig I: all 12 balloon anchors were lowered by 38 units and all 36 banana anchors by 18 units. X/Z positions were unchanged.
- Wizpig II: five added balloons were repositioned; minimum red/blue anchor separation increased from 509.51 to 806.68 units. Bananas, original balloons, hazards and scenery were unchanged.
- Eight-racer grids, stationary starts and three laps remain unchanged.

## Upgrade and rollback

Import the two new individual ZIPs into your existing profile and replace only the matching Wizpig IDs. Keep unrelated mods and saves. Do not enable duplicate revisions. Old r5 archives are retained only for rollback; their separate-profile limitation does not apply to the current preview's tested combination.

Based on *Diddy Kong Racing* by Rare/Nintendo. Preparation credit remains “Local preparation.” No official affiliation, endorsement or license to original game content is claimed.
