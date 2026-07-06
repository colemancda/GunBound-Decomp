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
| `0x2111` | In | Checks two "team full"-style flags (`this+0xd`/`this+0xe`, dispatching to `FUN_00429fb0`/`FUN_00429f90`), then on `payload[0]==0` does a player-join-setup near-identical to `0x2121`'s but with different field offsets (`payload[1..3]`). Likely **invite-based room join** (as opposed to `0x2121`'s regular join). |
| `0x2121` | In | `payload[0]==0` path: increments a counter (`+0x4739c`), sets `this+0x115=2` (status/mode byte), copies this client's name into a persistent buffer, resets weapon-slot fields to sentinel `0xff` — **"you joined/were assigned to a game" confirmation**, full player-slot initialization. |
| `0x21f0` | In | `payload[1]` (byte, length) + string data → same **0x80-byte per-slot display buffer** as `0x2105` (companion write path), gated on a find-my-slot check. |
| `0x21f1` | In | `*payload` (id): searches the room's player-ID array; on match, clears that slot; if it's this client's own slot, resets a "my slot index" field to -1. **Player left the room**. |
| `0x21f2` | In | Writes `payload[1..]` (variable length, `payloadLen-2` bytes) into the **same `0x80`-byte per-slot display buffer** as `0x2105`/`0x21f0`, for whichever slot `FUN_0041c290()` (find-my-slot) resolves to. Individual-field companion to `0x2103`'s bulk update. |
| `0x21f3` | In | Writes `payload[1]` (byte) into per-slot array `+0x4497c` — same field `0x2103` populates in bulk. |
| `0x21f4` | In | Writes `payload[1]` (uint) into per-slot array `+0x44984` — same field `0x2103` populates in bulk. |
| `0x21f5` | In | Writes `payload[1]` (byte) into per-slot array `+0x4499c`. |
| `0x21f6` | In | Writes `payload[1]` (byte) into per-slot array `+0x449a2`. |
| `0x21f7` | In | Writes `payload[1]` (byte) into per-slot array `+0x449a8`. |

`0x21f2`-`0x21f7` are a clean, systematic family: **individual per-field update
opcodes**, one per stat field that `0x2103`'s bulk player-list update
populates all at once. All six resolve the target slot the same way
(`FUN_0041c290()`) and clear the "my slot" cache field identically before
writing. This confirms the per-slot player record layout has (at least) six
independently-syncable fields beyond the display-name buffer.
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
| `0x3400` | In | Iterates all **16 slots** (not just the 8 player slots — likely includes reserved/spectator slots), logging a replay event `0xc302` with each slot's stat value (`+0xeba98`); slot 14 gets an extra field via `FUN_0045d360`. Also force-advances the turn if a "match over" flag is already set. Plausibly **end-of-match scoreboard/ranking sync**. |
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

Now fully mapped. This channel handles per-slot **visual/status sync** for
everyone in the ready room — character models, ready flags, map selection,
kicks.

| Action | Payload / Behavior |
|---|---|
| `1` | Copies up to 255 bytes of packet payload into a per-slot buffer, sets a "loaded"-style flag (`this+slot*8+0x700+0x8c8=1`). |
| `3` | `ShowMessage` virtual call — generic toast (same pattern as every other handler). |
| `0x8000` (two overlapping branches — `uVar2>0x8000` general case, and `uVar2==0x8000` exact case with extra work) | **Full player-info sync**: reads a per-room byte (`+0x45124`), applies via `FUN_004daa60`; the exact-match case additionally copies weapon-slot bytes, viewport-adjacent fields (`+0x457a1`/`+0x457a5`), and this client's own name string, then calls `FUN_004db920`/`FUN_004dbd50(this,1)` (UI refresh). Ready-room counterpart to Channel 1's `0x2121` "you joined" sync. |
| `0x8003` | Copies a string (payload, up to packetLen-1 bytes) into a shared name/chat buffer at `+0x44e64`. |
| `0x8004` | Just calls `FUN_004dbd50(this,1)` — a UI refresh trigger. |
| `0x8100` | **Character/mobile model sync.** Reads a per-slot mobile-type byte (`+0x458fc`); if invalid, applies the "rider" (unselected) texture; otherwise formats `tank_%d` and applies it to **two sub-objects per slot** (`this+slot*8+0x6fc` and `+0x700` — likely body + weapon/turret sprites). |
| `0x8101` | **Map selection sync.** Writes a byte (`this+0x25b`) into the current-map global (`DAT_..3b6c0`, `-1`→`0` sentinel-normalized), confirms ready status, re-initializes map-dependent state (`FUN_00415ce0`/`FUN_004db570`/`FUN_004db720`). |
| `0x8102` | Sets an "all-players-ready"-style bool (`this+0x4cc = (payload[0]==3)`), confirms ready status. |
| `0x8200` | **Kick from room.** If the target slot (`payload[0]`) is this client, sends the leave packet (`0x2000`/`0xffff`); otherwise shows a "player X was kicked/left" `ShowMessage`. |
| `0x8400` | Same **character/mobile model sync** as `0x8100` but triggered via a different path (calls `FUN_004dc5c0` first) — likely the "vehicle type changed" event vs `0x8100`'s "sync on join." |
| `0x9002` | Gated on the all-ready flag being false and a countdown field being unset (`-1`): if the room-owner check passes, sets the countdown field to `0x31` (49) — **game-start countdown initiation**, room owner triggering the transition to Loading. |

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
| `0x4005` | Gated on turn ownership (skips if sender IS this client) and a UI-busy-state check (`≠5,6,8,10`); relays a bool flag + a byte comparison. Likely an **emote or typing-indicator** relay, same family as `0x4002`-`0x4004`. |
| `0x4006` | Gated on turn ownership only; relays a single short field. Simplest of the chat/status-relay family — possibly a ping value or camera-sync field. |
| `0x8005` | Relay: forwards 2 fields, gated on turn-ownership and a UI-mode check (`≠5`, `≠6`). |
| `0x8006` | **Weapon-fire feedback sound**: plays one of `bifire`/`bfire1`/`bfire2`/`bsfire` based on a fire-mode byte and special-weapon check. |
| `0x8402`, `0x8406` | Relay 2 fields + a bool flag — likely **aim/angle+power update** forwarded to other clients. |
| `0x8403` | **Fire.** Richest payload: 2 fields, 2 bool flags, 2 more fields, then **8 sequential shorts** (`+0x2c`..`+0x3a`) — likely trajectory waypoints. Forwarded via the encode helpers; plays `ifire`. |
| `0x8404` | Appends to a third parallel-array set (`+0x27`/`+0xa7`/`+0x127`/`+0x1a7`, stride `0x80`) — 4 fields (value/id/byte/byte); plausible hit/damage log entry, triggers a UI update. |
| `0x8405` | Plays one of `b_play_weapon1/2/3` based on selected weapon slot — **weapon selection sound**. |
| `0x8407` | `payload[0]` (1/2/3) selects one of 3 global tables (`DAT_00e9ba40`/`DAT_00e9b818`/`DAT_00796aa0`), reads a value from it, and relays it via `AddToPacketChecksum`. `DAT_00796aa0` recurs elsewhere as what looks like an item/slot-count constant table — plausibly a **game-constant sync** (max HP/fuel/item-count class lookups), exact semantics per table not resolved. |
| `0x8408` | **Player spawn into battle**: appends to the primary parallel-array set (`+0x228`/`+0x2a8`/`+0x328`/`+0x3a8`), increments player count. Same arrays `0x3020` shifts down on disconnect. |
| `0xc300` | **Turn/round start.** Posts the scheduled chain: `0x8005`→`0x8006`→`0xc306`→`0xc400`→`0xc401`→`0x8403`→`0x8405`→`0xc409`. |
| `0xc301` | Same turn-timer/setup write as State 10's handler (shared code path). |
| `0xc303` (sub-switch on a byte) | `0`/`1`/`2`: set turn-phase field (`+0x42e`) to `3`/`4`/`0`. `0xe`/`0xf`: full turn-advance (viewport data, sound) then re-post the `0xc300` chain — two slightly different "next turn" triggers. |
| `0xc304` | **Movement.** Sub-cases on a direction nibble (1/2/3 + a running flag): per-player name-buffer lookup (`0x1120`-byte stride), directional movement sound, calls a cursor/sound-effect object (`FUN_004368f0`) — **not velocity application**, contrary to an earlier hypothesis; the actual position delta wasn't isolated. |
| `0xc305` | Turn timeout/expiry: resets phase byte, sets a duration constant (`0x11`/`0x10`/`0xb5`, difficulty-dependent) into a countdown, shows a "turn's up" message. |
| `0xc306` | Aim/direction confirm: reads a final field into the turn-timer slot, clears a per-slot cooldown. |
| `0xc308` | Reads **8 sequential shorts** from the payload directly into the same `+0x2302` setup array that `0xc301` initializes — a **mid-turn wind/spawn-data update** (e.g. wind direction changing between turns without a full turn-timer reset). |
| `0xc400` | **No handler** — pure scheduling checkpoint. |
| `0xc401` | Delegates to `HandleTurnTimeoutSlot` (`0x4cc1e0`, was `FUN_004cc1e0`): if `payload` belongs to a slot other than this client, relays 4 fields (offsets `+1,+2,+3,+5,+7` in the header) through the outgoing-encode helpers, then triggers a `b_play_weapon3` selection sound/visual. Part of the turn-start weapon-select flow (posted right after `0xc400` in `0xc300`'s chain). |
| `0xc409` | Same payload shape as `0x8403` Fire, but plays `sfire` (different sound) and resets flight-state flags (`DAT_005f3768=1`, `DAT_005f376c=0`) — reads as "fire confirmed/committed" following the initial Fire action. |
| `0xc40a` | Writes two raw ints per-slot directly from the packet — plausible final-position sync. |
| `0xc40b` | Iterates all 8 slots doing turn-timeout/notification bookkeeping. |
| `0xc801` | Builds outgoing `0x4100` with fields from a status struct (`+0xb0b0`/`+0xb0ac`); replay-logs event `0x8304`-adjacent movement data. Periodic status relay. |
| `0xf008` | **Quit/disconnect.** Sets `g_pendingGameState=0xf` directly — a second, more direct quit trigger alongside the `0x2001`/`0x3fff`-style leave packets. |
| `0xf009` | Delegates to `FUN_004d0fd0(slotOffset, payload[0])` — a per-slot single-byte value setter, target field not yet identified. |
| `0xf00a` | Relays a value read from the current player's record at field `+0x6744` through the outgoing-encode helpers — a simple query/relay, field purpose unconfirmed. |
| `0xf00b` | **Terrain deformation.** Delegates to `LoadTerrainDeformationFrame` (`0x4d1500`, was `FUN_004d1500`), which builds and loads numbered map-frame image filenames (`mf%05d.img` plus colored-channel variants `%cb/%cg/%ch%05d.img`, and `l`-suffixed second-layer versions) into a large local buffer. This is the classic GunBound **post-explosion terrain crater** mechanic — the server tells clients which pre-baked deformed-terrain frame to display. |

---

## Confirmed recurring structures

| Struct | Size | Evidence |
|---|---|---|
| Player game slot | `0x224` (548 bytes) | 8-element array in the In-Battle object; 20-element accumulation loop in room-list's stat-sum opcode; `0x8404`'s parallel arrays' implicit stride. |
| Room player display slot | `0x80` (128 bytes) | Room-list opcodes `0x2105`/`0x21f0`/`0x21f2`. |
| Room player stat fields (per-slot, individually syncable) | 1 byte / 1 byte / 4 bytes / 1 byte / 1 byte / 1 byte, at fixed offsets `+0x4497c`/`+0x4499c`/`+0x44984`/`+0x449a2`/`+0x449a8`/`+0x449ae` from a per-room base | `0x2103` (bulk) and `0x21f3`-`0x21f7` (individual) both populate this exact same set of fields. |
| In-Battle turn-setup array | 8 shorts (16 bytes) at `+0x2302` | `0xc301` (init) and `0xc308` (update) both target it. |
| Inventory item | `0x9c` (156 bytes) | Avatar store opcode `0x6002`; id fields + `time_t` expiry + variable blob. |
| Player name/label buffer | `0x1120` (4384 bytes) | In-Battle `0xc304` movement branch. |

## Known gaps

- **DONE this pass**: `0x2111`, `0x4005`/`0x4006`, state 11's `0x3400`
  (Channel 1), `0xc401`'s target `HandleTurnTimeoutSlot`, `0xf00b`'s target
  `LoadTerrainDeformationFrame`, and `0x8407`'s three lookup tables are all
  now documented above.
- **DONE**: State 9's `ProcessBattleAction` (Channel 2) is now fully mapped
  (see above) — character/mobile sync, ready flags, map selection, kicks,
  countdown initiation.
- `0x8407`'s three table semantics (what `DAT_00e9ba40`/`DAT_00e9b818`/
  `DAT_00796aa0` actually represent) are still unresolved beyond "some
  per-mode game constant."
- `0x8404`'s exact purpose (parallel-array append, distinct from `0x8408`'s
  spawn) is still a guess ("hit/damage log entry").
- The exact byte-level field boundaries within each payload are inferred from
  decompiled access patterns (`*(ushort*)(payload+N)` etc.), not from a
  formal struct definition — treat offsets as "confirmed observed," not "the
  only possible layout."
- No opcodes for continuous position/velocity sync during flight were found;
  see ARCHITECTURE.md's physics conclusion (server-authoritative, likely).
