# States 0 & 15 — Null / Quit

These two aren't real screens; they exist so the state array is total and the
transition machinery has valid targets.

## State 0 — Null / pre-init
- **Object**: 4 bytes (vtable ptr only), shared null-object vtable `0x553fb0`.
- **Vtable**: every slot is a shared no-op stub (`NoOpMethod`, a bare `RET`,
  for slots 7/8 = OnEnter/OnExit). Nothing loads, nothing renders.
- **Purpose**: the initial/idle slot before the boot flow begins; also the
  "poisoned" vtable a destroyed state object is re-pointed at (see
  `CGameState_BaseDestructor`).

## State 15 (0xf) — Quit
- **Object**: 4 bytes, shares the same null vtable `0x553fb0`.
- **Special-cased in `ChangeGameState`**: `newStateId == 0xf` calls
  `PostQuitMessage(0)` directly (begins app shutdown) rather than doing a
  normal enter/exit into a screen.

## Reimplementation
- Represent both as sentinel states. State 0 = "no active screen." State 15 =
  "request application exit" (post a quit to the main loop).
- No resources, rendering, input, or networking.
