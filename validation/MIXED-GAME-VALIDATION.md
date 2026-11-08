# Mixed-track validation, 8 November 2026

## Tested release

- Official, unmodified Linux x86_64 DKR-R 1.0.14 AppImage.
- AppImage SHA-256: `a799285856ecae9ef531bc6bcd03c3d00b356291b0541397809cc48fdb5b78df`.
- Owned US Rev A/v1.1 (`us.v80`) ROM.
- Current two catalogue-naming Wizpig ZIPs, with the hashes in [PACKAGE-CHECKS.json](PACKAGE-CHECKS.json).
- Public Splashdown Pass ZIP SHA-256: `2d1a04a9c37b1288c0120112d7d99bcdfac82821f63216dbbdaa18850e9576a6`.
- Public Strangled Shrine ZIP SHA-256: `af5f75bd8fbd8e74546d988262a98500e3744eaead64c3cc84989b83260f2084`.
- Both associated community HD texture packs enabled.
- No companion or other user code mod installed.

## Direct game observations

All four course packages were enabled in one session. Character Select was responsive and all four custom course captions displayed correctly.

Wizpig I entered a car race with Diddy, AI racers, geometry, start line, rain and bananas visible. Holding acceleration moved Diddy forward. Wizpig II entered a plane race with Diddy, AI planes, cave geometry, start line and bananas visible. Strangled Shrine entered a hovercraft race with Diddy, AI, shrine scenery and item balloons visible. Splashdown Pass had resolved assets and a visible menu preview, but its race was not entered.

No asset-bounds error, failed map load or crash occurred in the successful session. Normal shutdown reported zero fallback, mismatch and overflow counters.

## Test limits and warnings

This was a race-entry/coexistence test, not full-race qualification. Complete races, checkpoint/lap progression, every pickup, finish conditions, audible audio, Windows, arbitrary code mods and multiplayer were not tested. Software Vulkan was used, with dummy audio; performance and audio conclusions must not be drawn from this run.

The successful session had nonfatal warnings: empty launcher-created support directories lacked `mod.json`; an initial display-list/fullSync stall recovered; the update check encountered a TLS failure; the fresh test-save route reported no checksum-valid Adventure image. No update was installed. An earlier unmodded launch with a different software renderer crashed before this successful session, so that baseline renderer failure is not attributed to the track combination.

## Automated package/importer checks

The official importer installed all four actual course packages. Eight asset-bank/catalogue cases checked the four-map set, Wizpig-only set, community-only set and all re-enabled, against both US name banks with texture-augmented banks. Stock names remained unchanged and all enabled catalogue captions matched the manifests. These are importer/name-bank tests, not v77 gameplay support.

The current Wizpig ZIPs were checked against r5: `header.bin`, `objects_structure.bin` and `objects_collectables.bin` are byte-for-byte identical. IDs and existing preparation credit remain unchanged. No legacy names addition or `name.bin` remains in the current packages.

`verify_packages.py` verifies repository archive sizes, SHA-256 hashes and every listed payload. It does not recreate the importer or game session. No ROM, private profile, game executable or third-party community package is distributed in this repository.
