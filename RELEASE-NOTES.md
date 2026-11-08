# Wizpig Races r5: pickup correction

**Prerelease / release candidate.** DKR-R 1.0.14, US Rev A/v1.1 (`us.v80`), offline, separate profile containing only these two custom maps.

## Downloads

Download these individual archives from this repository:

- [Wizpig I r5](packages/Wizpig-I-1.0.14-USRevA-Pickup-Fix-r5.zip?raw=1)
- [Wizpig II r5](packages/Wizpig-II-1.0.14-USRevA-Pickup-Fix-r5.zip?raw=1)
- [SHA-256 checksums](SHA256SUMS.txt)

Import each ZIP directly. Do not rename it to `.dkrmap`.

## Changes

- Wizpig I pickup anchors lowered to the driving surface: balloons by 38 units, bananas by 18. X/Z positions unchanged.
- Wizpig II: five new balloons repositioned; minimum red/blue anchor separation increased from 509.51 to 806.68 units. Bananas, original balloons, hazards and scenery unchanged.
- Eight-racer grids, stationary starts, three laps and item counts preserved from r4.
- Corrected individual ZIP format accepted by the official 1.0.14 importer. Inner files unchanged from the previous r5 candidate.

## Tested and untested

Both ZIPs passed isolated official host-importer installation/parsing and installed-payload checks. **r5 gameplay testing remains pending.** Check reachable pickups, spacing and complete races before relying on this revision.

## Known limits

Session mods must be ON. Use a separate profile with only these two maps. Legacy captions can be blank, and other custom maps can exceed the name-section padding or misalign tables. Never enable duplicate revisions together. Back up working tracks and saves.

Based on *Diddy Kong Racing* by Rare/Nintendo. Current package preparation credit: “Local preparation.” No full ROM, executable, source game models, textures or music is included. No official affiliation or endorsement is claimed.
