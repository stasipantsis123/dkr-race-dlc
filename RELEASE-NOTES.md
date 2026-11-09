# Tricky - Mountain Race v1

An eight-racer, one-lap car sprint with the approved inner-cliff guardrail, 9 bananas across the original six stations, and restored native rolling-boulder triggers. All four course binary assets are identical to the approved r12 edition.

Use the tested **DKR-R 1.0.15**, your own **US Rev A / v1.1 (`us.v80`)** game data, and offline play. Import both the [course ZIP](packages/Tricky-Mountain-Race-v1.zip?raw=1) and the separate [matching sprint companion 0.3.5](packages/Tricky-Sprint-Companion-0.3.5.nrm?raw=1). Enable the code, set its option to 1, and restart. Older companion 0.3.4 does not recognize the public v1 manifest.

Targeted Linux 1.0.15 testing observed all seven native CPU finishes, post-line stop samples for all seven at 120, 360 and 900 active frames, and normal sequence-57 tempo 132 on human start-line crossings before and after a native restart; the game closed cleanly. Full human completion, close-up crowding, Windows gameplay, arbitrary mod combinations and multiplayer remain unqualified. Audio tempo checks do not establish audible sound quality. See [installation, rollback and complete limits](docs/TRICKY-V1.md) and [exact-byte validation](validation/TRICKY-V1.json).

# Wizpig banana and AI-clearance preview updates

2026-11-09: latest candidates for official DKR-R 1.0.15, US Rev A/v1.1 (us.v80). Both courses reduce 36 bananas to 18 at the same twelve stations, retaining six singles and six pairs. Wizpig I also adjusts 24 AI lane-height bytes at six start/finish-area controls. Other retained objects, balloons, headers, IDs and credits are unchanged.

Fresh static checks pass and exact candidate bytes have prior bounded Linux CPU-finish evidence. Full human races and Windows acceptance remain pending. Wizpig II's earlier intermittent CPU stall is unresolved; its sky is unchanged. No companion is required. [Complete changes, install/rollback instructions and limits](WIZPIG-PREVIEW-UPDATE.md).

# Bubbler and Smokey v1

Published as individual native track ZIPs for official DKR-R 1.0.15, US Rev A/v1.1 (`us.v80`). Each preserves six banana stations but reduces the total from 18 to 9 (three singles, three pairs). Other course payloads, IDs and preparation credits remain unchanged.

Both exact archives passed static checks and 120-second Linux smoke tests. Acceleration worked and both games shut down cleanly. Bubbler logged seven CPU finishes; Smokey logged four before the cutoff. Full human races, Windows, multiplayer and audio were not qualified. Supplied screenshots predate thinning. See [full notes](BUBBLER-SMOKEY-V1.md).

# Retained Wizpig mixed-track compatibility baseline

DKR-R 1.0.14, US Rev A/v1.1 (`us.v80`). These historical baseline package filenames contain `Catalogue-Naming-Test`; newer 1.0.15 preview updates are described above.

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
