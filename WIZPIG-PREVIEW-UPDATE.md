# Wizpig I and Wizpig II preview updates

Published for community playtesting on 2026-11-09. Use official **DKR-R 1.0.15** with your own **US Rev A / v1.1 (us.v80)** game data.

These are the latest reviewed candidates, not a claim of full gameplay qualification. Both course ZIPs are byte-for-byte copies of the exact tested candidates; only their download filenames were made suitable for a public preview. Neither requires a companion.

## Download

- [Wizpig I banana and AI-clearance preview r1](packages/Wizpig-I-USRevA-Banana-AI-Clearance-Preview-r1.zip?raw=1), 2,149 bytes.
- [Wizpig II banana-balance preview r1](packages/Wizpig-II-USRevA-Banana-Balance-Preview-r1.zip?raw=1), 3,295 bytes.
- [Exact archive and payload checks](validation/wizpig-preview-r1/PACKAGE-CHECKS.json).

Import each individual course ZIP, not the repository ZIP. Close the game, back up the previous matching package and saves, then replace only the matching Wizpig course. Keep exactly one enabled revision per ID. Keep unrelated maps, mods and saves. Original catalogue-compatible archives remain in packages for rollback.

IDs remain wizpig1-ordinary-race-us-v80 and wizpig2-ordinary-race-us-v80. Visible names remain Wizpig I - Race and Wizpig II - Race. Manifests, credits, eight-racer grids, stationary starts and three-lap race headers are unchanged.

## Wizpig I changes

- 36 bananas reduced to 18 across the same 12 stations: six singles and six pairs. This is a fixed varied layout, not new randomness each race. Surviving pickup records and positions are unchanged.
- All 12 balloons remain unchanged.
- Local AI lane-height adjustment at six flat start/finish-area checkpoint controls: 24 signed bytes changed from 0 to 5, adding 10 world units at those controls. Neighboring spline sections are also affected by interpolation.
- Human checkpoint planes, start grid and road geometry are unchanged.

Recorded official Linux 1.0.15 testing found all seven CPUs completed three laps in an idle-grid test. A fresh matched banana-only control reproduced seven below-road stalls, with only the 24 lane-height bytes differing among the controlled inputs. A later moved-then-no-input nearby-player test also had seven finishes.

These bounded cloud runs used uncontrolled random state. They support the local change under those tested conditions, not deterministic causality or a general AI fix. Nearby-player movement timing and endpoint differed from the historical failure, and later human drift occurred. Other unchanged low/airborne route sections, physical versus distant AI, collisions and lane transitions remain unqualified.

## Wizpig II changes

- 36 bananas reduced to 18 across the same 12 stations: six singles and six pairs.
- Only banana records were deleted. Surviving positions and records, all 34 balloons, other objects, header, checkpoints, starting grid, geometry and sky are unchanged.
- **There is no skybox-speed fix in this update.** Logged animation rates were essentially stock in a matched study; rendered/perceived sky speed remains open.

Recorded official Linux 1.0.15 testing included a fresh idle-start run with seven native three-lap CPU finishes. A separate mixed run also had seven finishes with ten courses admitted and both community HD packs loaded. The other nine courses were not all raced. An experimental sprint companion was enabled in that mixed run, but no scoped finish/parking/music intervention was observed; that is not a trace of every native write.

**An earlier revised idle-start run stalled CPU 6 at lap 2/checkpoint 4. That intermittent failure remains unresolved.** Later successful runs do not prove it fixed. Random state was not controlled, so no failure-rate claim is made.

## Validation and remaining playtests

Fresh publication checks passed ZIP integrity, exact source archive identity, payload hashes, unchanged IDs and manifests, banana deletion-only preservation, six single/six pair station counts, balloon preservation, and the precise Wizpig I structure-byte change. Every archive contains exactly four files: manifest, header and two object maps. No ROM, executable, private profile, save, observer, companion, model, texture or music file is included.

No new runtime test was performed solely for publication. Prior runtime evidence applies to the exact unchanged candidate bytes, as summarized above. No full human-driven race, all-pickup/balloon-upgrade qualification, Windows acceptance, audio, multiplayer or universal mod compatibility is claimed.

Please test:
1. Replacement and exactly one listing per course.
2. A full three-lap human race, checkpoint/lap counting, finish and restart.
3. All banana stations and balloon upgrades.
4. Seven CPU finishes across fresh starts and restarts, including idle starts.
5. Wizpig I AI road contact near the changed approaches and neighboring sections.
6. Windows behavior and Wizpig II perceived sky motion against stock under matched conditions.

Report game version, operating system, enabled mods, course, lap and checkpoint/landmark. Roll back to the retained original if behavior is unsuitable.

## Integrity

Wizpig I SHA-256: 4d7942d3582a0242bbc9312c02aac073c631caa65e0a67dddc9e6b49892b3636

Wizpig II SHA-256: aca4c47d423d11bc5a44853aec44a066b8964b0d6fa19404dd763fcc878e5184

Based on Diddy Kong Racing by Rare/Nintendo. Existing preparation credit remains "Local preparation." Unofficial; no affiliation, endorsement or license to original game content is claimed.
