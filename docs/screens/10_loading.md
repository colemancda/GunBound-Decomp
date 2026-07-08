# State 10 — Loading

The inter-match loading screen. Not a static "please wait" splash — a **live
per-player ready display** that updates as each player's load/checksum packet
arrives.

## Identity
- **State ID**: 10
- **vtable**: `vtable_State10_Loading` (`0x554018`)
- **Object size**: 0x150 bytes
- **ProcessPacket**: `State10_Loading_ProcessBattleAction` handling exists;
  see PROTOCOL.md.
- **OnEnter**: `0x43e840` · **OnExit**: `0x43eff0`
- **Chat/keyboard input**: `State10_Loading_HandleChatInput` (`0x43e720`)
- **Render slot**: slot 15 = `FUN_00442280` (2,750 bytes). Slots 11–14/16/17
  all point at the shared 1-byte `RET` stub (`0x429800`).

## Resources / images
- `loadmode.img` (background), `loadstage.img`.
- Preloads the full battle texture set (same list as Ready Room, `0x4d7b20`
  analogue) so assets are hot before In-Battle.

## Rendering — `FUN_00442280` (slot 15)
1. Draw background sprite; then (gated on `DAT_00e55a34 == -1`) a "waiting"
   overlay; then a couple of fixed decorative icons — layered compositing via
   `BlitSprite16bpp` / `BlitSpriteClipped`.
2. **Row of up to 16 per-player "ready" icons** (loop stride `0x2c`=44 px;
   per-player record `0x224` bytes): for each slot, check that player's bit in
   `PeekPacketChecksumState()` and pick a different sprite frame — each icon
   **flips from "waiting" to "ready"** the moment that player's checksum/ready
   packet arrives.
3. **Second loop** (same `0x224` stride): draw each connected player's
   mobile/avatar icon (frames `0x18`/`0x19`/`0x1a`); frame `0x19` is a
   **blinking** frame selected for the player currently matching the
   checksum-state slot, toggled by a `(tickCounter/10) & 1` parity — i.e. the
   still-loading player's icon blinks.
- Slot 10 (`FUN_00442240`, 58 bytes) is a string-forwarding helper (label-text
  setter), not a render call.

## Input
- **Keyboard/chat** (`0x43e720`): Win32 handler (`WM_KEYDOWN`/Enter), same shape
  as Ready Room's — non-command text logged to the replay stream. Same
  chat-send open item as Ready Room (see [09_ready_room.md](09_ready_room.md)).

## Transitions
- **In**: from Ready Room (match start).
- **Out**: → In-Battle (state 11) once all players' ready/checksum states arrive.

## Reimplementation checklist
1. Load `loadmode.img` / `loadstage.img`; preload the battle texture set.
2. Track a per-player array (16 × `0x224`) and a checksum/ready bitfield.
3. Render: background + waiting overlay + a 16-slot ready-icon row (flip on
   ready bit) + a mobile-icon row (blink the still-loading player).
4. Advance to In-Battle when all expected players are ready.
