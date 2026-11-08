# DKR Race DLC

Unofficial custom race packages for DKR-R.

## Current package set: Wizpig Races r5

Unofficial ordinary-race conversions of the Wizpig I and Wizpig II courses for **DKR-R 1.0.14**, using **US Rev A / v1.1 (`us.v80`)** game data.

**Release candidate: import tested; r5 gameplay testing pending.** Use offline in a separate profile containing only these two custom maps. This is not a general custom-track loader fix.

## Packages

| Track | File | Bytes |
| --- | --- | ---: |
| Wizpig I | [Wizpig-I-1.0.14-USRevA-Pickup-Fix-r5.zip](packages/Wizpig-I-1.0.14-USRevA-Pickup-Fix-r5.zip?raw=1) | 2,350 |
| Wizpig II | [Wizpig-II-1.0.14-USRevA-Pickup-Fix-r5.zip](packages/Wizpig-II-1.0.14-USRevA-Pickup-Fix-r5.zip?raw=1) | 3,524 |

Download the individual ZIPs above and import them directly. Do not rename the archives to `.dkrmap`. The repository-wide **Code > Download ZIP** is a bundle of this repository, not an importable track.

See the [r5 release notes](RELEASE-NOTES.md) for the revision summary.

Each race has an eight-racer grid, a stationary start, three laps, bananas and all five balloon colors. Wizpig I has 12 balloons and 36 bananas; Wizpig II has 34 balloons and 36 bananas.

## Changes from r4

- **Wizpig I:** all 12 balloons lowered by 38 game units and all 36 bananas by 18, putting pickup anchors on the driving surface. X/Z positions are unchanged. The sprite artwork supplies the visible lift.
- **Wizpig II:** five newly added balloons repositioned to reduce tight clusters. Minimum red/blue anchor separation increased from 509.51 to 806.68 game units, including the existing structure balloons. Every banana record, original balloon, hazard and scenery record is unchanged.
- **Race settings:** stationary starts, eight-racer grids and three laps remain unchanged from r4.
- **Archive correction:** the individual files use the `.zip` extension required by the 1.0.14 importer. Their inner files are byte-for-byte identical to the previous r5 candidate.

## Installation

1. Close DKR-R and back up your working track revisions and saves.
2. Use a separate DKR-R 1.0.14 profile with no other custom maps and your own US Rev A/v1.1 game data.
3. Import the two individual ZIPs through the custom-track importer.
4. Replace only the matching Wizpig IDs. Never enable duplicate revisions together. Turn Session mods ON.
5. Check pickup reachability, balloon spacing, race starts, laps and complete races before treating this candidate as gameplay validated.

The importer also accepts extracted `.dkrmap` directories. It does not accept ZIP files simply renamed to `.dkrmap`.

## Compatibility limits

These packages use four empty legacy language strings per track to fit 1.0.14's original name-section padding. Manifest titles remain visible in Custom Tracks, but legacy captions can be blank.

Other custom maps can exceed the padding budget or misalign the header/name tables. Mixed-custom-track compatibility is not supported by this workaround. No replacement executable is provided.

## Validation

- Both corrected individual ZIPs were accepted and parsed by the official 1.0.14 host importer in a fresh isolated cloud directory.
- Installed payloads matched the candidate files byte-for-byte.
- Item counts, permitted coordinate edits, unchanged data, upward-facing driving surfaces, stock pickup-anchor conventions and compression roundtrip were checked during package preparation.
- **r5 gameplay and complete-race behavior have not yet been confirmed.** Import success is not a gameplay test.

See [package checks](validation/PACKAGE-CHECKS.json), [importer results](validation/IMPORTER-VALIDATION.json), and [SHA-256 checksums](SHA256SUMS.txt). Run `python3 verify_packages.py` to check the supplied archives locally (or `cd packages && sha256sum -c ../SHA256SUMS.txt` for archive checksums only); this does not launch DKR-R or reproduce the importer/gameplay tests.

## Credits and rights

Based on the Wizpig courses in *Diddy Kong Racing*, developed by Rare and published by Nintendo. This is an unofficial community adaptation for DKR-R, with no claim of official affiliation or endorsement.

The current package manifests identify the preparation author as **“Local preparation.”** No other author attribution is asserted here. Repository ownership must not be read as authorship of the original game or its courses.

The packages contain track headers, names, object maps and manifests. No full ROM, game executable, source game models, textures or music is included. Original game content remains subject to its existing rights. No license to original game content is granted by this repository.

This repository is a **package release and validation record**, not a complete build-source distribution. It does not contain the original game source, a decompilation checkout, or a reproducible r5 build pipeline. No open-source license has been declared for the track packages.
