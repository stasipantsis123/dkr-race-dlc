# Universal Lap 3–98 Banners + Swish 1.1.1

Extra lap banners with the original swish as they slide in and out. Uses DKR's own LAP artwork and HUD digits, including compact two-digit numbers. The Lap 3 crash in the earlier swish test build is fixed.

[Download the NRM](dkr_universal_lap_banners.nrm?raw=1) · [Changes](CHANGELOG.md) · [Test notes](TEST-REPORT.md) · [Build from source](BUILDING.txt)

## What it supports

- DKR-R **1.0.15 or later**, offline single-player.
- Standard lap races with **4–99 total laps**, including ordinary, boss, Taj and Time Trial paths that use the normal lap HUD.
- Intermediate banners **LAP 3–98**. Native Lap 2 and the actual Final Lap keep their original presentation and audio.
- One native swish on entry and one when the exit starts. No new voice or center ding.

This code does **not** change race length. Use a separate compatible lap-count mod if needed. Online, split-screen and non-lap modes are unsupported. Mods replacing the same HUD hooks may conflict.

## Install or update

Import **dkr_universal_lap_banners.nrm** under **Installed Mods → My Mods → Custom Magic Codes**. Set Status to **All** if it is hidden. Open Details, approve the code, enable it for the next game and restart with Session mods on. Check that the selected version is **1.1.1**.

This is an update to the same mod, not an extra code to enable alongside it. Keep a backup of your previous package. [Silent v1.0.0 remains available unchanged](../universal-lap-banners-v1/README.md). Do not use the withdrawn swish test version 1.1.0.

## Testing

1.1.1 was successfully tested in-game after the fix. Automated tests also cover timing, pause/resume, final-lap exclusions and the exact compiled stack-alignment fault that broke 1.1.0. This is not a claim that every course, vehicle, mod combination or full 99-lap race has been tested. See [the test notes](TEST-REPORT.md).

The package contains code only. Artwork and sound come from your own configured game data. No ROM, game audio, executable, save, profile or test fixture is included.

Prepared by stasipantsis123. Unofficial; not affiliated with Rare or Nintendo.
