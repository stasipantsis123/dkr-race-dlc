# Wizpig mixed-track test, 8 November 2026

This test checked whether the older Wizpig compatibility previews could load alongside Splashdown Pass, Strangled Shrine and both community HD texture packs in one profile. It covered race entry, not complete races.

## Test setup

- Official, unmodified Linux x86_64 DKR-R 1.0.14 AppImage.
- AppImage SHA-256: `a799285856ecae9ef531bc6bcd03c3d00b356291b0541397809cc48fdb5b78df`.
- Owned US Rev A/v1.1 (`us.v80`) ROM.
- The two catalogue-naming Wizpig ZIPs listed in [PACKAGE-CHECKS.json](PACKAGE-CHECKS.json).
- Public Splashdown Pass ZIP SHA-256: `2d1a04a9c37b1288c0120112d7d99bcdfac82821f63216dbbdaa18850e9576a6`.
- Public Strangled Shrine ZIP SHA-256: `af5f75bd8fbd8e74546d988262a98500e3744eaead64c3cc84989b83260f2084`.
- Both associated community HD texture packs enabled.
- No companion or other user code mod installed.

## What happened in the game?

All four course packages were enabled together. Character Select responded, and all four course names displayed correctly.

Wizpig I loaded a car race with Diddy, AI racers, geometry, the start line, rain and bananas visible. Holding acceleration moved Diddy forward. Wizpig II loaded a plane race with Diddy, AI planes, cave geometry, the start line and bananas visible. Strangled Shrine loaded a hovercraft race with Diddy, AI, shrine scenery and item balloons visible.

Splashdown Pass had its assets loaded and its preview visible in the menu. Its race wasn't entered.

There was no asset-bounds error, failed map load or crash in the successful session. The game closed normally with zero fallback, mismatch and overflow counters.

## What wasn't tested?

Complete races, checkpoint and lap counting, every pickup, finishes, audible audio, Windows, arbitrary code mods and multiplayer weren't tested. The run used software Vulkan and dummy audio, so it doesn't establish performance on your machine or audible sound quality.

The successful session still logged some nonfatal warnings:

- Empty support directories created by the launcher didn't have `mod.json` files.
- An initial display-list/fullSync stall recovered.
- The update check hit a TLS failure. No update was installed.
- The fresh test-save route reported no checksum-valid Adventure image.

An earlier unmodded launch with a different software renderer crashed before this successful session. That earlier renderer failure isn't being attributed to the track combination.

## Package and importer checks

The official importer installed all four course packages. Eight asset-bank and catalogue cases covered the four-map set, Wizpig only, community maps only and all maps re-enabled. They checked both US name banks, including banks with the texture packs loaded. Stock names stayed unchanged, and every enabled course name matched its manifest.

Those are importer and name-bank results, not v77 gameplay support. The course data still requires v80.

Compared with r5, the Wizpig ZIPs have identical `header.bin`, `objects_structure.bin` and `objects_collectables.bin` files. Their IDs and preparation credit are unchanged. The legacy name addition and `name.bin` have been removed.

`verify_packages.py` checks repository archive sizes, SHA-256 hashes and every listed file inside the packages. It doesn't repeat the importer tests or the game session. No ROM, private profile, game executable or third-party community package is distributed in this repository.
