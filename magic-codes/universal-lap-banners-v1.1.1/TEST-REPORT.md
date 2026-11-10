# 1.1.1 test notes

**Package SHA-256:** `fa61bc1b0ea94b85483aad1328624b46af946d8a0e1df57ee3929a40e0e668a5`

## In-game confirmation

On 10 November 2026, stasipantsis123 tested the supplied 1.1.1 package, confirmed it worked and approved this update. This is a successful local playtest, not a complete course/revision/endurance matrix.

The original silent v1 had earlier native visual and trophy-mod tests. Those records remain in its unchanged folder; they are not new audio tests of 1.1.1.

## Automated checks

- 38,784 host callback transition sequences and 1,009,800 layout cases passed normally and with AddressSanitizer/UndefinedBehaviorSanitizer.
- Timing, duplicate callbacks, pause/resume, resets, expiry, unavailable-audio no-retry and native Lap 2 / Final Lap exclusions are covered.
- The unchanged official MIPS interpreter ran 85 corrected-version scenarios and 84 silent-v1 controls. The old 1.1.0 compiled code fails at its first LAP 3 audio request under the added native-stack guard; 1.1.1 passes with aligned calls and valid 64-byte stack spans.
- That interpreter harness models the SDK/native boundary and audio sink. It does not execute the full production GameWorld or audio engine. The successful user playtest is separate evidence.
- All 77 linked MIPS functions and 154 fixed stack adjustments preserve 16-byte alignment. The build runs this audit automatically.
- Three builds produced identical NRM bytes. Static coexistence checks passed with official Custom Trophies Creator 1.0.2.
- Layout/clock policy and the original v1 package are unchanged.

## Limits

Offline single-player only. US v77/v80 are declared and covered by automated gates, but every supported revision, track, vehicle and mod combination has not been played. There is no full 99-lap endurance/results qualification.

The broader source-tree tooling remains blocked by an existing hook-launcher permission error and missing host-build dependencies. Those suites are not claimed to pass. No online or split-screen support is implied.
