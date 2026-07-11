# State 5 — Logo 1 (Softnyx publisher splash)

**Corrected: not the normal boot entry.** `WinMain`'s primary path
(`InitGame` returns `0`) calls `ChangeGameState(6)` — **Logo 2** — directly;
this screen is only reached via a secondary `WinMain` branch that re-runs
`InitGame` after a specific non-zero return code (`0x17`) and then calls
`ChangeGameState(5)` instead (see `06_logo2.md`'s "In" section). So on a
normal launch this screen is skipped entirely. About as simple as a screen
gets otherwise: show a full-screen logo, play a jingle, auto-advance after
~2 seconds.

## Identity
- **State ID**: 5
- **vtable**: `vtable_State05_Logo1` (`0x555590`)
- **Object size**: 8 bytes (vtable ptr + one `int` frame counter)
- **ProcessPacket**: none (no networking)

## Resources
- **Image**: `logomode.img` (full-screen Softnyx logo, sprite index 0)
- **Audio**: `logo.mp3`

## State object fields
| Offset | Field |
|---|---|
| +0x00 | vtable ptr |
| +0x04 | frame counter (`int`), incremented each tick |

## OnEnter (`0x4433f0`) — 3 things
1. Preload resource/effect definitions `10000` and `0x2711` (`LoadSpriteSet`
   — **not** a timer despite the argument shapes; see the "resource preloader"
   note in ARCHITECTURE.md's lobby dispatcher section. Purpose of these two
   specific IDs on this screen not pinned down further).
2. Zero the frame counter (`+0x04`).
3. Play `logo.mp3` via `PlayMusicTrack(0)` (music-start helper).

No `CreateButtonWidget` calls — the 8-byte object has no widget-list field.

## Rendering
- Entirely the **shared slot-15 background blit** (`0x443570`): draws whatever
  background sprite is loaded (sprite index 0 = the logo) via
  `BlitSprite16bpp` / `BlitSpriteClipped`. Nothing else.

## Input
- None.

## Transitions
- **In**: from app start (initial `ChangeGameState(5)`).
- **Out**: **slot 9** tick hook (`0x443540`) increments the frame counter and,
  at count `0x28` (**40 ticks ≈ 2 s** at 50 ms/tick), calls
  `ChangeGameState(6)` → Logo 2.

## Reimplementation
1. On enter: load `logomode.img`, start playing `logo.mp3`, reset a frame counter.
2. Each frame: blit the logo full-screen; increment the counter.
3. At 40 frames, transition to Logo 2.
- No interactivity, no network, no widgets.
