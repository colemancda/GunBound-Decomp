# State 6 — Logo 2

Second publisher/branding splash, structurally identical to
[Logo 1](05_logo1.md). Auto-advances to the Title screen.

## Identity
- **State ID**: 6
- **vtable**: `vtable_State06_Logo2` (`0x555528`)
- **Object size**: 8 bytes (vtable ptr + `int` frame counter)
- **ProcessPacket**: none
- **OnEnter**: `0x443280` · **OnExit**: `0x4432c0`

## Resources
- **Image**: `logomode2.img`
- **Audio**: `logo2.mp3`

## Rendering
- Uses a shared background-blit function (`0x443360` — a near-twin of Logo 1's
  `0x443570`, differing only slightly). Draws the loaded background sprite;
  no other content.

## OnEnter / tick / transitions
- Same idiom as Logo 1: OnEnter starts the timeout, resets the counter, plays
  `logo2.mp3`; a per-tick slot-9 hook counts frames and calls
  `ChangeGameState(1)` → Title after the splash duration elapses.
- **In**: **the normal boot path enters here directly** — `WinMain` calls
  `InitGame` then `ChangeGameState(6)` unconditionally on success (return
  `0`). Logo 1 is *not* on this path (corrects `05_logo1.md`'s "first screen
  in the boot flow" framing). Logo 1 is only reached via a separate `WinMain`
  branch that re-runs `InitGame` after a specific non-zero return code
  (`0x17`, meaning/trigger not yet traced — plausibly a display-mode retry,
  given the surrounding registry logic that reads/writes a saved
  bit-depth/mode `Template` value) and then calls `ChangeGameState(5)`
  instead. So Logo 1 → Logo 2 → Title is the *fallback* ordering, not the
  default one.
- **Out**: to Title (state 1).

## Input / network
- None.

## Reimplementation
- Copy the Logo 1 implementation with `logomode2.img` / `logo2.mp3` and a
  transition target of Title (state 1). (Exact frame threshold not separately
  captured here — mirror Logo 1's counter-at-threshold pattern; ~2–3 s.)
