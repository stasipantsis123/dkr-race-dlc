UNIVERSAL SILENT LAP 3-98 BANNERS v1.0.0
A Custom Magic Code for DKR-R 1.0.15 or later

Adds a sliding LAP plus number on intermediate laps 3 through 98, using
the original LAP artwork and native yellow/orange HUD digits. Two-digit
numbers use compact glyph-aware spacing. No new voice or sound is added.

SUPPORTED SCOPE
Offline single-player lap races with 4-99 laps, without a track-name or
vehicle restriction. This includes ordinary races, boss races, Taj races
and Time Trial when they use the game's standard lap HUD. The package is
declared for US v77 and US v80. Runtime testing used US v80 on Linux 1.0.15.

Native Lap 2 and Final Lap are preserved. The actual final lap takes
priority: a four-lap race shows LAP 3 then FINAL LAP; a 99-lap race shows
intermediate numbers through LAP 98 then uses native FINAL LAP.

Online, split-screen and non-lap challenge/hub modes are not supported.
Other code mods that replace the lap HUD or its draw hooks may conflict.
This is not a guarantee for arbitrary combinations of other mods.

This code does not change race length. The official Custom Trophies Creator
1.0.2 can set 1-99 laps per cup round and has been tested alongside it. The
banner code uses its own presentation clock and never accesses the trophy
code's extended lap timing table or replaces its two-digit lap counter.

INSTALL (DKR-R 1.0.15)
1. Extract the ZIP and locate dkr_universal_lap_banners.nrm.
2. Open Installed Mods, expand MY MODS, then select CUSTOM MAGIC CODES.
3. Choose Import mods and select that NRM file. Set Status to All and clear
   any search text. A new import appears with Needs approval.
4. Open its Details, tick I trust this code mod, then choose Approve code.
5. Tick Enabled for next game and close Details. Start a fresh game with
   Session mods on, using an eligible race with more than three laps.
6. To disable, clear Enabled for next game and relaunch.

The separate MAGIC CODES panel contains the stock cheats. Imported NRM
codes appear under MY MODS > CUSTOM MAGIC CODES. The Status: On filter
hides a newly imported code until it is approved and enabled.

Import only the NRM, not the source/evidence ZIP. No test fixture, ROM,
original game assets, executable, save or personal profile is distributed.
The package reads its artwork from your own configured game data.

VALIDATION
See TEST-REPORT.txt for exact build, automated test and runtime evidence,
including remaining test limits. Windows, full-race completion, trophy
results and every individual course have not been tested. The common HUD
hook has no track-name allowlist; source coverage is not a claim that every
course has been driven. Native audio was not auditioned (dummy audio).

CREDITS
Prepared by stasipantsis123. Based on Diddy Kong Racing by Rare/Nintendo.
Original artwork remains in the user's game data. This unofficial code is
not affiliated with or endorsed by Rare or Nintendo. No license to the
original game content is granted.
