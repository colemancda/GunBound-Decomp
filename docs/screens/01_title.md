# State 1 — Title

The title/splash screen. Plays title music and auto-advances to Server Select.
No interactive UI at all.

## Identity
- **State ID**: 1
- **vtable**: `vtable_State01_Title` (`0x557278`)
- **Object size**: 8 bytes (vtable ptr + `int` frame counter)
- **ProcessPacket**: none
- **OnEnter**: `State01_Title_OnEnter` (`0x4e5370`) · **OnExit**: `0x4e53b0`

## Resources
- **Image**: `titlemode.img`
- **Audio**: `title.mp3`

## OnEnter (`0x4e5370`)
- Audio setup only — starts title music via `FUN_004f1790(&DAT_00ea0e18, 10000)`.
- **No blit calls, no `CreateButtonWidget`** — Title has no widgets (confirmed
  exception to "every OnEnter builds buttons").

## Rendering
- Uses the shared slot-15 background blit (`0x443570`, same as Logo1/ServerSelect):
  draws the loaded `titlemode.img` background sprite. No other content.

## Input
- None. (Any keypress advancing the title, if present, is not a widget path;
  the primary advance is the timer below.)

## Transitions
- **In**: from Logo 2 (`ChangeGameState(1)`).
- **Out**: **slot 9** tick hook (`0x4e5400`) is a pure frame counter — at count
  `0x3c` (**60 ticks ≈ 3 s**) calls `ChangeGameState(2)` → Server Select.

## Reimplementation
1. On enter: load `titlemode.img`, start `title.mp3`, reset a frame counter.
2. Each frame: blit the background; increment the counter.
3. At 60 frames, transition to Server Select (state 2).
- No network, no widgets, no interactivity.
