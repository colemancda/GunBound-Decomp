# GunBound Network Protocol — Reverse-Engineered Packet Reference

Consolidated reference for every opcode/action confirmed via static analysis
in Ghidra. Complements [ARCHITECTURE.md](ARCHITECTURE.md) (which covers the
*architecture* the protocol runs on — the state machine, the dispatch
mechanism, the replay system) with a flat, lookup-friendly packet list.

**Scope note**: this covers every opcode branch found in the five confirmed
`ProcessPacket` screen handlers and the three confirmed `ProcessBattleAction`
real-time handlers — i.e. every packet-shaped code path reachable from the
`CGameState` object model. It does **not** claim to be the literal complete
protocol; opcodes handled by not-yet-located code (e.g. any handler outside
the `CGameState` hierarchy, if one exists) aren't included. See "Known gaps"
at the end.

## How the protocol is structured

Two independent dispatch channels exist per game state, both **virtual
methods on the same `CGameState`-derived object** (see ARCHITECTURE.md's
vtable table):

- **Channel 1 — `ProcessPacket(int payloadLen, ushort opcode, ushort *payload)`**
  (vtable slot 1). The reliable, screen-scoped protocol. Each screen has its
  own opcode range and its own handler function; opcode values are reused
  across screens with different meanings since only one screen is ever active.
- **Channel 2 — `ProcessBattleAction(void *packetBuf, int packetLen)`**
  (vtable slot 2). A second protocol, present only on Loading/ReadyRoom/
  InBattle, with a different **fixed 33-byte header** (see below) instead of
  the simple `(len, opcode, payload)` triple. Working theory: this is the
  real-time/P2P channel, separate from the server-relayed Channel 1.

All packets are pushed through a lightweight **XOR-based
encode/checksum** on the way out (see `EncodeOutgoingPacketField` in
ARCHITECTURE.md) — not encryption in a cryptographic sense, more an
anti-tamper/integrity measure.

### Channel 1 header
Just the three parameters: `payloadLen` (int), `opcode` (ushort), `payload`
(ushort* — treat as a raw byte/ushort-mixed buffer; individual handlers cast
sub-fields to `byte`/`ushort`/`int` freely at fixed offsets).

### Channel 2 header
```
offset  type    field
+0x00   ?       unidentified (2 bytes, not yet decoded)
+0x02   ushort  action type
+0x04   ?       unidentified (1 byte)
+0x05   byte    source player slot (validated 0-7)
+0x06.. ?       unidentified, up to +0x21
+0x21   ...     payload start
```

---

## Channel 1 — `ProcessPacket` opcodes, by screen

### State 1 — Title screen
No packet handler (vtable slot 1 is the shared no-op). Title screen doesn't
process network data.

### State 2 — Server/Channel Select (`State02_ServerSelect_ProcessPacket`, `0x4e02b0`)

| Opcode | Direction | Payload / Behavior |
|---|---|---|
| `0x1001` | **Outgoing**, triggered locally | Builds reply opcode `0x1010`: this client's own name/info, then **two `getsockname()` calls** appending the local socket's bound `IP:port`. This is the **P2P NAT-traversal handshake** — reporting local address back to the server for relay to prospective peers. |
| `0x101f` | In | `payload[0]` (uint), `payload[2]` (uint) → stored to session globals (login/session-handoff flags flip to 1). Likely post-channel-selection session token / server address handoff. |
| `0x1012` | In | `*payload` is a server error code, one of `0x5001`/`0x5011`/`0x5012`/`0x5013`, mapped to internal reason codes `0x1d`/`0x1e`/`0x1f`/`0x20` — drives a "can't join: `<reason>`" error dialog. |
| `0x1102` | In | Zeroes a 4 KB buffer, then parses a list of variable-length entries: `ushort` + `byte` + length-prefixed string, into a table — the **server/channel list** shown on the choose-server screen. |

### State 3 — Game Room List / channel lobby (`State03_GameRoomList_ProcessPacket`, `0x426ad0`)

| Opcode | Direction | Payload / Behavior |
|---|---|---|
| `0x2001` | In | `payload[0]` (bool-ish): branches to one of two cleanup/notify helpers, then `FUN_00507cc0(1, sessionField)`. Generic session cleanup/ack. |
| `0x201f` | In | `payload[0]` (byte, slot id): looks up a slot; on miss, inserts a per-slot record via `FUN_0041b8c0` — a chat-line or item-record insert (unconfirmed which). |
| `0x2103` | In | `payload[0]` (byte = player count), then per-player entries (name + flags/stats) up to that count — **room player list update**. |
| `0x2105` | In | `payload[1]` (byte, length) + string + several small fields → copied into a per-slot **0x80-byte display buffer** (`base+slot*0x80`) and mirrored to local fields; target slot from `this+0x124`. **Player info/profile broadcast**. |
| `0x2111` | In | Same `0x21xx` cluster as `0x2103`/`0x21f0`/`0x21f1`; branch present but body not yet decompiled. |
| `0x2121` | In | `payload[0]==0` path: increments a counter (`+0x4739c`), sets `this+0x115=2` (status/mode byte), copies this client's name into a persistent buffer — **"you joined/were assigned to a game" confirmation**. |
| `0x21f0` | In | `payload[1]` (byte, length) + string data → same **0x80-byte per-slot display buffer** as `0x2105` (companion write path), gated on a find-my-slot check. |
| `0x21f1` | In | `*payload` (id): searches the room's player-ID array; on match, clears that slot; if it's this client's own slot, resets a "my slot index" field to -1. **Player left the room**. |
| `0x6001` | In | `payload[1..5]` (4 uint fields) + variable per-"player" 3-byte tuples (with `rand()`-derived values) → then `ChangeGameState(7)` = **enter Avatar Store**. |
| (unlabeled opcode) | In | Sums per-slot equipped-item stat bonuses across a 20-element × `0x224`-byte array, resets the viewport to `(0,0,799,599)`, then `ChangeGameState(9)` = **enter Ready Room**. |

### State 7 — Avatar Store / Shop (`State07_AvatarStore_ProcessPacket`, `0x4440c0`)

| Opcode | Direction | Payload / Behavior |
|---|---|---|
| `0x2001` | In | `*payload==0`: room->store transition unpack (4 uint fields via `FUN_0040a470`) then, if `payloadLen>0xe`, one more field — mirrors state 3's `0x6001` unpack pattern in reverse context. |
| `0x600f` | **Outgoing**, triggered locally | Sends `0x6000` (empty payload) — "give me my inventory," on entering the store. |
| `0x6002` | In | Per-entry: 4× uint id fields + a `time_t` (parsed via `localtime` → day/month/year = **expiration date**) + variable-length blob. Stored into a **confirmed 156-byte (`0x9c`) item struct array** at `+0x44be8`. **Owned-item inventory list.** |
| `0x6005` | In | `*payload==0`: populates a short array with per-item prices (stride `0x224`, ≤4 entries) from a global item-data table, unless flagged to send a leave (`0x2000`/`0xffff`) or quit (`g_pendingGameState=0xf`) instead. Also resets price-filter min/max fields to sentinel values. **Store init / price-list population.** |
| `0x6017` (`*payload==0`) | In | Builds a **purchase confirmation dialog**: loads 4 localized strings by resource id (`0xea6a`..`0xea6d`), formats item name/price via `sprintf`, shows `b_storewindow_confirm` popup. |
| `0x6017` (`*payload==0x6003`) | In | Sends `0x6000` reply — the confirmation dialog's "yes" response. |
| `0x6027` | — | **No handler** — falls through with zero logic. A scheduling checkpoint only (same pattern as Channel 2's `0xc400`). |
| `0x6037` (`*payload==0`) | In | **Purchase commit**: bounds-checks the target slot (fatal-errors via `FUN_004010c0(0x80070057)` if out of range), calls `FUN_0044c370()` (commit) then `FUN_0044c6a0` (refresh display), then dispatches a multi-case outcome selector (success/insufficient-funds/etc., cases not individually decoded). |

### State 9 — Ready Room (`State09_ReadyRoom_ProcessPacket`, `0x4d38c0`)

Opcodes `0x30xx`/`0x31xx`/`0x32xx`/`0x34xx`/`0x44xx`. Most branches record a
**replay event** via `Replay_AppendEvent` alongside their normal effect — see
ARCHITECTURE.md's replay system section for the event-code table.

| Opcode | Direction | Payload / Behavior |
|---|---|---|
| `0x2001` | In | `payload==0`: leave ready room. If `DAT_00793522` is set, force-exits state 11 (In-Battle) via its own exit-hook first. Sets `g_pendingGameState=3` (back to room list). |
| `0x3010` | In | `payload[0]` (byte): calls `FUN_004dc200` (character/team pick?) then finalizes via `FUN_004dc5c0`. |
| `0x3020` | In | Simpler ready/unready toggle (no payload processing beyond the call). |
| `0x3105` | In | Replay event `0x8102` (self) or `0x8000`+id+position (others); `SendMessageA(hwnd, 0xc5, ...)` UI notification. **Player joined ready room.** |
| `0x3151` | In | `payload[2]` (byte) → replay event `0x8200`. Likely **team change**. |
| `0x3201` | In | Two byte fields from `this` → replay event `0x8100`. Likely **weapon/character selection change**. |
| `0x3211` | In | Replay event `0x8101`. Likely **map vote/selection**. |
| `0x3231` | In | Replay event `0x8102`. **Ready-status toggle.** |
| `0x3233` | In | `*payload!=0`: sends leave (`0x2000`/`0xffff`). `*payload==0`: force-exits In-Battle's exit-hook, `g_pendingGameState=9` (stay in ready room), replay event `0x8103`. |
| `0x3400` | In | Ready-room UI: shows either `b_ready_ready` or `b_ready_startgame` button depending on room-owner check. **Ready-status button refresh.** |
| `0x3431` | In | Falls through to a shared "confirm-ready" call (same tail as `0x3151`/`0x3201`/`0x3211`). |
| `0x3432` | In | Closes the open replay file (`fclose`) if one is open. **Match/session end — stop recording.** |
| `0x3fff` | In | Sends outgoing `0x2000`/`0xffff` — leave/cancel notification. |
| `0x4410` (only if not already leaving) | In | Replies with outgoing opcode `0x3232` — server keepalive/ping ack. |

### State 11 — In-Battle (`State11_InBattle_ProcessPacket`, `0x4b4100`)

Mostly disconnect/leave/end-of-match administration — the actual gameplay
actions live on Channel 2 (below).

| Opcode | Direction | Payload / Behavior |
|---|---|---|
| `0x2001` | In | `payload==0`: leave battle → `g_pendingGameState=3` (Game Room List). |
| `0x3020` | In | **Player disconnected mid-match**: removes the player from the 8-slot array (shift down, `0x224`-byte stride), records replay event, reassigns active turn if the departed player held it (`FUN_00413bf0`). |
| `0x3233` | In | **Match ends** → `g_pendingGameState=9` (Ready Room). Writes a terminator byte (`2`) then closes the replay file. |
| `0x3400` | In | Not fully traced (branch present). |
| `0x3fff` | In | Same leave/cancel `0x2000`/`0xffff` as Ready Room. |
| `0x4102` | In | Companion disconnect-notification path: checks a slot mask (`&0xf000`); if set, logs replay event `0x8500` with player stats (position, cooldown flag) before cleanup. |
| `0x4410` | (fallthrough) | No distinct handling shown beyond the shared `0x4413` check below it. |
| `0x4413` | In | **End of match**: clears all 8 player slots (`FUN_00405fb0` ×8), sets `this+0x474=1` ("match over" flag), shows the `b_result_confirm` **results screen**. |

---

## Channel 2 — `ProcessBattleAction`, by screen

### State 10 — Loading (`State10_Loading_ProcessBattleAction`, `0x43e440`)

| Action | Payload / Behavior |
|---|---|
| `3` | `ShowMessage`-style virtual call (`this vtable+0x28`) with a formatted string — generic notification. |
| `0xc301` (`-0x3cff` as signed short) | Writes the **turn-timer field** (`+0x10a4` on the *In-Battle* object, `g_gameStateVTableArray[0xb]`, written cross-state before battle is active) — value checked against `60000`/`0xffff` (60-second turn limit). Copies an 8-element setup array (`+0x2302`, likely wind/spawn data) from the packet. Also does per-player sound-profile selection (`normal`/`wnormal`). |

### State 9 — Ready Room (`State09_ReadyRoom_ProcessBattleAction`, `0x4d4ea0`)

Confirmed real (non-no-op) override; not yet fully mapped beyond confirming
the shared header format and action `0x8100` appearing (same code as the
Channel 1 replay event of the same value).

### State 11 — In-Battle (`State11_InBattle_ProcessBattleAction`, `0x4b5460`)

The largest function in the binary (11,718 bytes). Confirmed via
`bsfire`/`bfire1`/`bfire2`/`bifire`/`ifire`/`sfire` (weapon cursor sounds) and
`sudden.mp3` strings. **No floating-point instructions anywhere in this
function** — see ARCHITECTURE.md's physics section for the full discussion
of what this implies about where trajectory resolution actually happens
(working conclusion: server-authoritative, not computed here).

| Action | Payload / Behavior |
|---|---|
| `3` | `ShowMessage` virtual call — generic toast. |
| `0x4001` | Single-byte flag toggle (only when acting slot ≠ this client). |
| `0x4002` | **Proximity chat**: computes distance from sender to each of the 8 slots, delivers the message only within ~150 units. |
| `0x4003`, `0x4004` | Similar per-player text-record lookup/insert as `0x4002` — other chat/notification variants (unconfirmed which). |
| `0x4005`, `0x4006` | Present, not decompiled in detail. |
| `0x8005` | Relay: forwards 2 fields, gated on turn-ownership and a UI-mode check (`≠5`, `≠6`). |
| `0x8006` | **Weapon-fire feedback sound**: plays one of `bifire`/`bfire1`/`bfire2`/`bsfire` based on a fire-mode byte and special-weapon check. |
| `0x8402`, `0x8406` | Relay 2 fields + a bool flag — likely **aim/angle+power update** forwarded to other clients. |
| `0x8403` | **Fire.** Richest payload: 2 fields, 2 bool flags, 2 more fields, then **8 sequential shorts** (`+0x2c`..`+0x3a`) — likely trajectory waypoints. Forwarded via the encode helpers; plays `ifire`. |
| `0x8404` | Appends to a third parallel-array set (`+0x27`/`+0xa7`/`+0x127`/`+0x1a7`, stride `0x80`) — 4 fields (value/id/byte/byte); plausible hit/damage log entry, triggers a UI update. |
| `0x8405` | Plays one of `b_play_weapon1/2/3` based on selected weapon slot — **weapon selection sound**. |
| `0x8407` | Selects one of 3 lookup tables by a mode byte — purpose unclear. |
| `0x8408` | **Player spawn into battle**: appends to the primary parallel-array set (`+0x228`/`+0x2a8`/`+0x328`/`+0x3a8`), increments player count. Same arrays `0x3020` shifts down on disconnect. |
| `0xc300` | **Turn/round start.** Posts the scheduled chain: `0x8005`→`0x8006`→`0xc306`→`0xc400`→`0xc401`→`0x8403`→`0x8405`→`0xc409`. |
| `0xc301` | Same turn-timer/setup write as State 10's handler (shared code path). |
| `0xc303` (sub-switch on a byte) | `0`/`1`/`2`: set turn-phase field (`+0x42e`) to `3`/`4`/`0`. `0xe`/`0xf`: full turn-advance (viewport data, sound) then re-post the `0xc300` chain — two slightly different "next turn" triggers. |
| `0xc304` | **Movement.** Sub-cases on a direction nibble (1/2/3 + a running flag): per-player name-buffer lookup (`0x1120`-byte stride), directional movement sound, calls a cursor/sound-effect object (`FUN_004368f0`) — **not velocity application**, contrary to an earlier hypothesis; the actual position delta wasn't isolated. |
| `0xc305` | Turn timeout/expiry: resets phase byte, sets a duration constant (`0x11`/`0x10`/`0xb5`, difficulty-dependent) into a countdown, shows a "turn's up" message. |
| `0xc306` | Aim/direction confirm: reads a final field into the turn-timer slot, clears a per-slot cooldown. |
| `0xc400` | **No handler** — pure scheduling checkpoint. |
| `0xc401` | Delegates to `HandleTurnTimeoutSlot` (`0x4cc1e0`), not fully traced. |
| `0xc409` | Same payload shape as `0x8403` Fire, but plays `sfire` (different sound) and resets flight-state flags (`DAT_005f3768=1`, `DAT_005f376c=0`) — reads as "fire confirmed/committed" following the initial Fire action. |
| `0xc40a` | Writes two raw ints per-slot directly from the packet — plausible final-position sync. |
| `0xc40b` | Iterates all 8 slots doing turn-timeout/notification bookkeeping. |
| `0xc801` | Builds outgoing `0x4100` with fields from a status struct (`+0xb0b0`/`+0xb0ac`); replay-logs event `0x8304`-adjacent movement data. Periodic status relay. |
| `0xf00b` | Delegates to `FUN_004d1500` with 4 fields from the packet — not traced. |

---

## Confirmed recurring structures

| Struct | Size | Evidence |
|---|---|---|
| Player game slot | `0x224` (548 bytes) | 8-element array in the In-Battle object; 20-element accumulation loop in room-list's stat-sum opcode; `0x8404`'s parallel arrays' implicit stride. |
| Room player display slot | `0x80` (128 bytes) | Room-list opcodes `0x2105`/`0x21f0`. |
| Inventory item | `0x9c` (156 bytes) | Avatar store opcode `0x6002`; id fields + `time_t` expiry + variable blob. |
| Player name/label buffer | `0x1120` (4384 bytes) | In-Battle `0xc304` movement branch. |

## Known gaps

- Opcodes present but not decompiled in detail: `0x2111` (state 3), `0x4005`/
  `0x4006` (state 11 Channel 2), `0x3400` (state 11 Channel 1), `0xc401`'s
  target `HandleTurnTimeoutSlot`, `0xf00b`'s target `FUN_004d1500`, `0x8407`'s
  three lookup tables.
- State 9's `ProcessBattleAction` (Channel 2) is confirmed real but not
  opcode-mapped beyond one shared action.
- The exact byte-level field boundaries within each payload are inferred from
  decompiled access patterns (`*(ushort*)(payload+N)` etc.), not from a
  formal struct definition — treat offsets as "confirmed observed," not "the
  only possible layout."
- No opcodes for continuous position/velocity sync during flight were found;
  see ARCHITECTURE.md's physics conclusion (server-authoritative, likely).
