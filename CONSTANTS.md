# GunBound — Consolidated Enum/Constant/Opcode Reference

A single compiled index of every confirmed enum value, magic number, opcode,
struct offset, and named constant found across
[ARCHITECTURE.md](ARCHITECTURE.md), [PROTOCOL.md](PROTOCOL.md),
[FILEFORMATS.md](FILEFORMATS.md), and [STRINGS.md](STRINGS.md). This document
doesn't re-derive anything — it's a synthesis/index. For the reasoning behind
any entry (how it was confirmed, what function it came from), follow the
cross-reference to the source document.

Values marked **tentative** in the source docs are kept marked tentative
here too — this index doesn't upgrade confidence levels.

---

## 1. Game state IDs (`CGameState`)

16-element vtable array, `g_gameStateVTableArray` (`0x5b33f8`). See
ARCHITECTURE.md's state-machine section for full detail.

| ID | Screen | Object size | Identifying resources |
|---|---|---|---|
| 0 | Null/pre-init | 4 | shared trivial vtable `0x553fb0` |
| 1 | **Title** | 8 | `titlemode.img`, `title.mp3` |
| 2 | **Server/Channel Select** | `0x6c` | `server_list.img`, `channel.mp3` |
| 3 | **Game Room List** (lobby) | `0x294` | `gamelist_back.img`, `b_gamelist_*` |
| 4 | (unused/reserved) | — | none |
| 5 | **Logo screen 1** | 8 | `logomode.img`, `logo.mp3` |
| 6 | **Logo screen 2** | 8 | `logomode2.img`, `logo2.mp3` |
| 7 | **Avatar Store/Shop** | `0x34818` (215 KB) | `store_*.img`, `b_store_*.img` |
| 8 | (unused/reserved) | — | none |
| 9 | **Ready Room** (pre-battle) | `0x78c` | `ready_selectmap.img`, `b_ready_startgame.img` |
| 10 | **Loading** | `0x150` | `loadmode.img`, `loadstage.img` |
| 11 | **In-Battle** | `0x2408` (9 KB) | `stage%d.mp3`, `b_play_*` |
| 12-14 | (unused/reserved) | — | none constructed |
| 15 (`0xf`) | **Quit** | 4 | shares null vtable; calls `PostQuitMessage(0)` |

Flow: Logo1(5) → Logo2(6) → Title(1) → ServerSelect(2) → GameRoomList(3) ⇄
AvatarStore(7); GameRoomList(3) → ReadyRoom(9) → Loading(10) → InBattle(11).

Related globals: `g_currentGameState` (`0x7934d0`), `g_pendingGameState`
(`0x5b33ec`), `g_stateChangeRequested` (`0x7934d4`),
`g_stateChangeInProgress` (`0x793508`).

---

## 2. Vtable slot indices

### `CGameState` base vtable (common across states 1-11)

| Slot | Offset | Role |
|---|---|---|
| 0 | `+0x00` | scalar-deleting destructor |
| 1 | `+0x04` | **`ProcessPacket(int payloadLen, ushort opcode, ushort *payload)`** — Channel 1 |
| 2 | `+0x08` | **`ProcessBattleAction(void *packetBuf, int packetLen)`** — Channel 2 (no-op except Loading/ReadyRoom/InBattle) |
| 3-4 | `+0x0c`/`+0x10` | other per-state virtuals, usually no-op |
| 5 | `+0x14` | Keyboard/chat-input dispatcher |
| 6 | `+0x18` | Mouse-input dispatcher |
| 7 | `+0x1c` | **OnEnter** |
| 8 | `+0x20` | **OnExit** |
| 9 | `+0x24` | per-state tick/cursor/update (no fixed meaning across states) |

### State 11 (In-Battle) full 18-slot vtable (`vtable_State11_InBattle`, `0x5566d8`)

| Slot | Address | Role |
|---|---|---|
| 0 | `0x4b4060` | destructor |
| 1 | `0x4b4100` | `State11_InBattle_ProcessPacket` |
| 2 | `0x4b5460` | `State11_InBattle_ProcessBattleAction` |
| 3, 4 | `0x4fdef0` | shared no-op |
| 5 | `0x4b82b0` | Keyboard/chat-input dispatcher |
| 6 | `0x4b97d0` | Mouse-input dispatcher (`WM_LBUTTONUP`/`WM_RBUTTONDOWN`/`WM_RBUTTONUP`) |
| 7 | `0x4bb730` | `State11_InBattle_OnEnter` |
| 8 | `0x4bcd00` | `State11_InBattle_OnExit` |
| 9 | `0x4bd8b0` | cursor/per-frame update |
| 10 | `0x4c1b90` | Chat character-input helper (emoticon remap) |
| 11 | `0x4c1c90` | per-tick counter/update helper |
| 12 | `0x4c1d10` | one-line delegate |
| 13 | `0x4c1d30` | special-weapon-effect render (`SpecialTexture1/2`) |
| 14 | `0x4c3020` | `State11_InBattle_Render` |
| 15 | `0x4c8890` | chat-message finalize/send |
| 16 | `0x4caed0` | `State11_InBattle_RenderModeIcons` |
| 17 | `0x429800` | genuine no-op |

### `vtable_ButtonWidget` (`0x551e44`, 5 slots)

| Slot | Role |
|---|---|
| 0 | scalar-deleting destructor |
| 1 | animation/timing fields |
| 2, 3 | render (generic texture-cache lookup, `FUN_004f30c0`) |
| 4 | bare `RET` no-op |

### `IDirect3DDevice7` vtable offsets used

| Offset | Method |
|---|---|
| `+0x10` | EnumTextureFormats |
| `+0x14` | BeginScene |
| `+0x18` | EndScene |
| `+0x20` | SetRenderTarget |
| `+0x28` | Clear |
| `+0x34` | SetViewport |
| `+0x50` | SetRenderState |
| `+0x64` | DrawPrimitive |
| `+0x8c` | SetTexture |
| `+0x94` | SetTextureStageState |

Generic COM `Release` at vtable `+8` (used to tear down all 6 D3D/DDraw COM
objects).

---

## 3. Channel 1 (`ProcessPacket`) opcodes

Full detail and confirmed behavior in PROTOCOL.md; summarized here by state.

### State 2 — Server/Channel Select (`0x4e02b0`)

| Opcode | Meaning |
|---|---|
| `0x1001` | Outgoing: P2P NAT-traversal handshake; replies `0x1010` |
| `0x101f` | Session/server handoff |
| `0x1012` | Server error code translation (see below) |
| `0x1102` | Server/channel list population |

Error-code mapping (`0x1012`): server `0x5001`→internal `0x1d`; `0x5011`→`0x1e`;
`0x5012`→`0x1f`; `0x5013`→`0x20`.

### State 3 — Game Room List (`0x426ad0`)

| Opcode | Meaning |
|---|---|
| `0x2001` | Generic session cleanup/ack |
| `0x201f` | Per-slot record lookup/insert |
| `0x2103` | Room player list bulk update |
| `0x2105` | Player info/profile broadcast (0x80-byte name buffer) |
| `0x2111` | Invite-based room join (tentative) |
| `0x2121` | Room join confirmation / player-slot init (weapon slots reset to `0xff`) |
| `0x21f0` | Player display buffer companion write |
| `0x21f1` | Player left the room |
| `0x21f2`-`0x21f7` | Per-field room-slot updates (name, byte flags, uint) |
| `0x6001` | Room → Avatar Store (`ChangeGameState(7)`) |
| *(no dedicated opcode — shared fallthrough)* | Room → Ready Room (`ChangeGameState(9)`) — confirmed there is genuinely no single opcode for this; it's whatever doesn't match the above |

### State 7 — Avatar Store (`0x4440c0`)

| Opcode | Meaning |
|---|---|
| `0x2001` | Room-to-store transition unpack |
| `0x600f` | Outgoing: request inventory (`0x6000`) |
| `0x6002` | Owned-item inventory list (`InventoryItem`, 0x9c/156 bytes) |
| `0x6005` | Store init/price-list population |
| `0x6017` | Purchase confirmation dialog / response (branches on `*payload`) |
| `0x6027` | No-op scheduling checkpoint |
| `0x6037` | Purchase commit |

### State 9 — Ready Room (`0x4d38c0`)

| Opcode | Meaning |
|---|---|
| `0x2001` | Leave ready room |
| `0x3010` | Match-start replay snapshot + team-based spawn setup (**corrected** from an earlier "character/team selection" guess) |
| `0x3020` | Ready/unready toggle |
| `0x3105` | Player joined ready room |
| `0x3151` | Team change (tentative) |
| `0x3201` | Weapon/character selection change (tentative) |
| `0x3211` | Map vote/selection (tentative) |
| `0x3231` | Ready-status toggle |
| `0x3233` | Match/session status change |
| `0x3400` | Ready-status button refresh |
| `0x3431` | Ready confirmation |
| `0x3432` | Stop replay recording |
| `0x3fff` | Outgoing: leave/cancel |
| `0x4410` | Server keepalive/ping (reply `0x3232`) |

### State 11 — In-Battle (`0x4b4100`)

| Opcode | Meaning |
|---|---|
| `0x2001` | Leave battle |
| `0x3020` | Player disconnected mid-match |
| `0x3233` | Match ends → Ready Room |
| `0x3400` | End-of-match scoreboard/ranking sync (tentative) |
| `0x3fff` | Outgoing leave/cancel |
| `0x4102` | Companion disconnect notification |
| `0x4410` | Fallthrough into `0x4413` check |
| `0x4413` | End of match / show results |

---

## 4. Channel 2 (`ProcessBattleAction`) action codes

Fixed 33-byte (`0x21`) header: `+0x02` ushort action type, `+0x05` byte
source slot (0-7), `+0x21` payload start.

### State 10 — Loading (`0x43e440`)

| Action | Meaning |
|---|---|
| `3` | Generic notification toast |
| `0xc301` | Turn-timer + battle setup write (cross-state, into In-Battle object) |

### State 9 — Ready Room (`0x4d4ea0`)

| Action | Meaning |
|---|---|
| `1` | Player data buffer load |
| `3` | Generic notification toast |
| `0x8000` | Full player-info sync |
| `0x8003` | Chat/name buffer update |
| `0x8004` | UI refresh trigger |
| `0x8100` | Character/mobile model sync |
| `0x8101` | Map selection sync |
| `0x8102` | All-players-ready flag |
| `0x8104` | Show match-result confirm button |
| `0x8200` | Kick from room |
| `0x8400` | Character/mobile model sync (alternate trigger) |
| `0x9002` | Game-start countdown initiation (sets countdown to `0x31`=49) |

### State 11 — In-Battle (`0x4b5460`, 11,718 bytes — largest function in the binary)

| Action | Meaning |
|---|---|
| `3` | Generic notification toast |
| `0x4001` | Status flag toggle |
| `0x4002` | **Proximity chat** (~150 unit distance filter) |
| `0x4003`, `0x4004` | Chat/notification variants |
| `0x4005` | Emote/typing-indicator relay (tentative) |
| `0x4006` | Simple status/value relay (tentative) |
| `0x8005` | Field relay (turn-gated) |
| `0x8006` | Weapon-fire feedback sound |
| `0x8402`, `0x8406` | Aim/angle+power relay (**confirmed** — both read the same `+0x243`/`+0x2cc` struct offsets already confirmed as angle/power in Fire's own payload) |
| `0x8403` | **Fire** — payload confirmed: a lead field + angle `u16` + two flag bytes + two `u16` + a byte, then **8 sequential `u16`s** (payload `+0x2c`…`+0x3a`), then a trailing flag + more. All fields are re-queued (relayed) and the `"ifire"` animation is triggered. The **8 shorts are the server-resolved shot data** (the client sends only angle+power with *no local physics* — see the fire builder — so the server computes the shot and broadcasts the result here); the exact per-short meaning (impact coords for up to 4 sub-projectiles vs. trajectory samples) is still open |
| `0x8404` | Hit/damage log entry (tentative — likely feeds a live damage/score ranking sort, see PROTOCOL.md) |
| `0x8405` | Weapon selection sound |
| `0x8407` | Packet-checksum keepalive — **corrected**: not a real per-mode table lookup, the shared accessor ignores its argument |
| `0x8408` | **Player spawn into battle** |
| `0x8500` | Player-position/status relay (also a replay-event code) |
| `0xc300` | **Turn/round start** — posts chain `0x8005→0x8006→0xc306→0xc400→0xc401→0x8403→0x8405→0xc409` |
| `0xc301` | Turn-timer + wind/spawn setup write |
| `0xc303` | Turn-phase sub-switch |
| `0xc304` | Movement (4-bit direction + `0x10` running flag) |
| `0xc305` | Turn timeout/expiry |
| `0xc306` | Aim/direction confirmation |
| `0xc308` | Mid-turn wind/spawn-data update |
| `0xc400` | No-op scheduling checkpoint |
| `0xc401` | Turn-timeout weapon-select relay |
| `0xc409` | Fire confirmed/committed |
| `0xc40a` | Final position sync (tentative) |
| `0xc40b` | Turn-timeout bookkeeping across all 8 slots |
| `0xc801` | Periodic status relay |
| `0xf008` | Direct quit/disconnect |
| `0xf009` | Per-slot byte value set |
| `0xf00a` | Player record field query/relay |
| `0xf00b` | Terrain deformation (crater frame swap) |

**Confirmed never implemented** (fall to default no-op): `0xc302`, `0xc307`,
`0xc309`, `0xc402`-`0xc408`.

---

## 5. File format magic numbers and constants

| Constant | Value | Meaning |
|---|---|---|
| XFS magic | `"XFS2"` | Archive container magic |
| LZHUF `N` (window) | 4096 (`0xfff` mask) | Ring buffer size |
| LZHUF `F` (max match) | 60 | max copy length |
| LZHUF `THRESHOLD` | 2 | min match length encoded specially |
| LZHUF `N_CHAR` | 314 (`0x13a`) | `256 - THRESHOLD + F` |
| LZHUF `T` | 627 (`0x273`) | `2*N_CHAR - 1` |
| LZHUF `MAX_FREQ` | 32768 (`0x8000`) | triggers tree rebuild (`reconst`) |
| Ring buffer fill byte | `0x20` (space) | initial contents |

Per-file LZHUF target decompressed sizes:

| File | Target size | Decimal |
|---|---|---|
| XFS TOC header | `0x40` | 64 bytes |
| XFS TOC chunk (1024 entries) | `0x20000` | 131,072 bytes |
| XFS individual entry decode window | `0x1000` | 4,096 bytes |
| `characterdata.dat` | `0x14c0` | 5,312 bytes |
| `stage.dat` | `0x3c80` | 15,488 bytes |
| `itemdata.dat` | `0x7850` | 30,800 bytes |
| `specialdata.dat` | — | not loaded by client at all |

Record sizes/counts:

| Struct/format | Size | Count |
|---|---|---|
| XFS TOC record | `0x80`/128 bytes | variable, 1024/chunk |
| `characterdata.dat` record | `0x14c`/332 bytes | 16 (`16×332=5312`) |
| `itemdata.dat` record | `0x134`/308 bytes | 100 (`100×308=30800`) |
| `stage.dat` record | `0x1e4`/484 bytes | 32 (`32×484=15488`) |
| `InventoryItem` | `0x9c`/156 bytes | array |
| `.img` header | 48 bytes (client) / 40 bytes (independent `InsideGB.exe` reimpl of the per-frame record) | — |
| `.xes` header | 16 bytes | PCM fmt block |
| Channel 2 header | `0x21`/33 bytes | fixed |
| XFS entry block header | 8 bytes | `compressedSize`(4)+`checksum`(4) |

Checksum algorithms:

| Context | Algorithm |
|---|---|
| XFS entry | sum of `piVar2[-2]+piVar2[-1]+piVar2[1]+*piVar2` over 256 iterations = sum of every 32-bit LE word in first 4096 bytes, mod 2^32 |
| `.dat` files | validated via shared `PeekPacketChecksumState()` |
| `Asuka.exe` editor tool | `'M' + sum of all bytes mod 256` |

### Key struct field offsets

**XFS TOC 128-byte record:**

| Offset | Size | Field |
|---|---|---|
| `0x00` | ~0x70 | Filename (NUL-terminated) |
| `0x70` | 4 | Storage-mode flag (`1`=raw, else LZHUF) |
| `0x74` | 4 | Base file offset |
| `0x78` | 4 | Decompressed size |
| `0x7c` | 4 | Compressed size on disk |

**`.img` header (frame 0):**

| Offset | Size | Field |
|---|---|---|
| `0x00` | 4 | Unknown/flags |
| `0x04` | 4 | Frame count |
| `0x08` | 4 | Unknown |
| `0x0c` | 4 | Width |
| `0x10` | 4 | Height |
| `0x14` | 4 | Hotspot X (signed) |
| `0x18` | 4 | Hotspot Y (signed) |
| `0x1c`-`0x2b` | 16 | Unidentified |
| `0x2c` | 4 | Total pixel-run byte count |
| `0x30`+ | var | Pixel data (ARGB4444) |

**`itemdata.dat` record (308 bytes):**

| Offset | Size | Field |
|---|---|---|
| `0x00` | 32 | Item name |
| `0x20` | 4 | uint32 field (checksummed) |
| `0x24` | 4 | Price/value |
| `0x28` | 4 | Item type/index ID |
| `0x2c` | 1 | Boolean flag 1 (obfuscated: `Shot?`) |
| `0x2d` | 1 | Boolean flag 2 (obfuscated: `Skip`) |
| `0x2e` | 1 | Boolean flag 3 (obfuscated: `2 Slots`) |
| `0x30` | 2 | ushort field |
| `0x32`+ | var | Localized description |

Obfuscation formula: `checksum_byte = encoded_byte + encoded_flag - 0x34`.

**In-Battle object key offsets:**

| Offset | Meaning |
|---|---|
| `+0x10a4` | turn-timer field (checked vs `60000`/`0xffff`) |
| `+0x2302` | 8-element wind/spawn setup array |
| `+0x228`/`+0x2a8`/`+0x328`/`+0x3a8` | spawn parallel-array indices |
| `+0x227` | active-slot counter |
| `+0x42e` | turn-phase field |
| `+0x429` | aim/direction confirm ushort |
| `+0x27`/`+0xa7`/`+0x127`/`+0x1a7` | hit/damage-log parallel arrays (0x80 stride) |
| `+0x9c`/`+0x29c`/`+0x49c`/`+0x69c` | sorted-ranking parallel arrays (0x200 stride) |
| `playerId*0x224 + 0xebef4` | per-player packet-checksum-state array |

**Replay event record**: `uint8 reserved(0)`, `uint32 sequenceOrTime`,
`uint32 payloadLength`, `uint16 eventCode`, `byte payload[payloadLength]`.
Event codes seen: `0x307`, `0x8000`, `0x8100`-`0x8103`, `0x8200`, `0x8500`,
`0x9000`, `0xf00e`, `1` (chat).

**Widget-definition binary format** (`LoadButtonDefinitionFromXFS`):
```
uint32 count
count × {
  uint32 nameLen
  char   name[nameLen]   // no NUL on disk
  uint8  typeByte
  uint32 subCount
  uint32 arrayA[subCount]
  uint32 arrayB[subCount]
}
```

**`ChooseEvent.txt`** (full content, tab-delimited):
```
0	off
1	christmas
2	event2
3	event3
```

---

## 6. Pixel formats / graphics constants

| Constant | Value | Meaning |
|---|---|---|
| Pixel format | **ARGB4444** | confirmed (RGB565, RGB555 both ruled out) |
| `InsideGB.exe` reimpl sub-formats | `0`=RGB565 flat, `1`=sparse run-list, `2`=ARGB4444 flat | 3-way switch, low byte of first Int16 |
| FVF | `0x244` | `D3DFVF_XYZRHW(0x004) \| D3DFVF_DIFFUSE(0x040) \| D3DFVF_TEX2(0x200)` |
| D3DPT_TRIANGLELIST | `4` | primitive type passed to `DrawPrimitive` |
| Vertex layout | 9 dwords/36 bytes | `[X,Y,Z,RHW,Diffuse,U0,V0,U1,V1]` |
| "Vertex work record" | 27 dwords/108 bytes | = 3 vertices (1 triangle) |
| Diffuse constant | `0xffffffff` | opaque white, no per-sprite tint |
| Viewport | `(0,0,799,599)` | fixed 800×600 play area |
| `DDERR_SURFACELOST` | `0x887601C2` | matched exactly in `PresentFrame` |
| `IID_IDirect3D7` | `{F5049E77-4861-11D2-A407-00A0C90629A8}` | QueryInterface target |
| `g_sineTable360` | 360-entry table @ `0x54c240` | `angle % 360`; cosine via `(angle+90)%360` |
| Sprite-sheet grid divisors | 2×N(`&1`), 3×3(`%3`/`/3`), 4×N(`&3`/`>>2`), 8×N(`&7`) | frame-index decomposition |

Audio format (`.xes`): PCM, 2 channels, 22050 Hz, 16-bit (uniform across all
85 files).

---

## 7. Win32 / networking constants

| Constant | Value | Meaning |
|---|---|---|
| `WM_LBUTTONUP` | `0x202` | State 11 mouse dispatcher |
| `WM_RBUTTONDOWN` | `0x204` | mouse dispatcher |
| `WM_RBUTTONUP` | `0x205` | mouse dispatcher |
| `WM_KEYDOWN` | `0x100` | chat-input handlers |
| Enter key | `0xd` | chat-input handlers |
| `E_INVALIDARG` (HRESULT) | `0x80070057` | used as fatal-error code |
| `DDERR_SURFACELOST` | `0x887601C2` | DirectDraw surface-lost |
| Turn timer / sentinel | `60000` / `0xffff` | 60-second turn limit |
| Packet validity check | `(len & 0x8000000f) == 0` | UDP packet must be multiple of 16 past fixed prefix |
| Channel 2 header size | `0x21`/33 bytes | fixed |
| Reliable-UDP queue stride | `0x206` | per-slot queue insert stride |
| Weapon-slot "empty" sentinel | `0xff` | byte value meaning unequipped |
| Price-filter reset sentinels | `0x80000000`/`0x7fffffff` | min/max "no filter" |

8-player cap validated as `slot <= 7` in both channels. `getsockname()`
called twice for the P2P NAT handshake. `WSAStartup` in `WinMain`.

---

## 8. Timing / gameplay constants

| Constant | Value | Meaning |
|---|---|---|
| Game tick rate | **50 ms** (20 Hz) | `(now - lastTick) / 50` |
| Turn timer | **60,000 ms** (60 sec) | field `+0x10a4` |
| Proximity chat distance | **~150 units** | action `0x4002` |
| Title-screen auto-transition | ~60 ticks (~3 sec) | State 1 slot-9 tick counter |
| Countdown-start value | `0x31` (49) | action `0x9002` |
| Turn-timeout duration (difficulty-dependent) | `0x11`/`0x10`/`0xb5` | action `0xc305` |
| 8-player battle cap | 8 (slots 0-7) | |
| 16-slot end-of-match iteration | 16 | opcode `0x3400` |

---

## 9. Named state-string constants (informal enums)

| String | Usage |
|---|---|
| `"active"` | ButtonWidget initial visual state |
| `"disable"` | ButtonWidget initial visual state |
| `"ready"` | ButtonWidget initial visual state |
| `"normal"` | character audio profile |
| `"wnormal"` | character audio profile (weighted/heavy variant) |
| `"tnormal"` | sound-profile name (t-prefix variant of `normal`) |
| `"twnormal"` | sound-profile name (t-prefix variant of `wnormal`) |
| `"rider"` | default/unselected-character texture |
| `tank_%d` | character model texture naming convention |

---

## 10. Third-party / library constants

Values confirmed via the companion tools found alongside `GunBound.gme`
(`InsideGB.exe`, `Asuka.exe`, `mishato_English.exe`, `Shinji.exe`, `XFS2.exe`
— see FILEFORMATS.md's "field semantics recovered from" sections), not
derivable from the client alone:

| Constant | Value | Source | Meaning |
|---|---|---|---|
| `.img` sub-format selector | `0`/`1`/`2` | `InsideGB.exe`'s `ImageDecoder.LoadFrames` | RGB565 flat / sparse run-list / ARGB4444 flat |
| `.img` per-frame header size | 40 bytes | same | 2×Int16 + 9×Int32, last = pixel byte count |
| Archive checksum window | first 4096 bytes | `DecodeXFSEntryBlock` (client) + cross-verified via `verify_checksum.py` | sum of all 32-bit words, mod 2^32 |
| `characterdata.dat` checksum | `'M' + sum mod 256` | `Asuka.exe` | matches client-side conclusion independently |
| `itemdata.dat` boolean flags | 3 checkboxes: `Shot?`/`Skip`/`2 Slots` | `mishato_English.exe` dialog | identifies the 3 obfuscated flags at `0x2c`/`0x2d`/`0x2e` |
| `stage.dat` gimmick flags | `포스`/`돌풍`/`전기`/`바람`/`귀환`/`치료`/`무지`/`버젼` | `Shinji.exe` dialog | Force/Gust/Electric/Wind/Return/Heal/Fog/Version |

---

## 11. Other named constants and formats

**Registry paths**: `Software\Softnyx\GunBound`, `Software\Softnyx\GameBuddy`,
`System\CurrentControlSet\Services\Class\%s`.

**Client version**: two distinct values (see ARCHITECTURE.md "Connection
subsystem").
- **Binary build stamp** — PE `VS_VERSION_INFO` FileVersion `0.0.2.40`
  (= version **240**), ProductName "Softnyx GunBound Project", CompanyName
  "Softnyx" (`GunBound.gme` file offset `0x1a868a`). Static, informational.
- **Protocol version** — the `Version` DWORD under
  `HKCU\Software\Softnyx\GunBound`, read by `LoadClientSettingsFromRegistry`
  and relayed to the server in the login handshake (mismatch → error dialog id
  220). Not compiled in; provisioned by the launcher (jglim
  `Launcher.ini` = `280`). The 236 / 240 / 252 / 280 series is a
  registry/launcher value, not a `.gme` constant.

**Filename/format strings**:
- `%s%s - %s.sv` — replay filename template
- `%Y%m%d %H%M` — replay filename timestamp
- `%s%s%07d.bmp` — screenshot filename generator
- `%s[%3d/%3d]` — scoreboard/room-label bitmap-font format
- `%04d-%02d-%02d` — date format
- `%d.%d.%d.%d` — IP address format
- Illegal filename chars stripped: `\ / : * ? " < > |`

**Developer/GM chat commands** (full `/`-command parser, `FUN_004218c0`):
- Staff credits: `comsik`, `CozY`, `enddream`, `yesoori`, `oorusa`,
  `jaeyong`, `yaong2`, `jchlee75`, `reddragon`, `designer`, `johnny5`,
  `loserii`, `scjang`, `chuko`, `pirania`, `blash45`, `knights`
- Hidden debug commands: `noack` (sets `DAT_00e9b1d8=1`), `clear`/`logging`
  (push replay events `0x9000`/`0xf00e`)
- Korean-keyboard-romanized hidden commands (2-beolsik layout obfuscation):
  `shrduatlwkr`, `shrduarhkswjs`, `shrduaakstpakstpaksakstp` — gated on
  `g_currentGameState==9`

**Control-character emoticon remap table** (State 11 chat input):
`'@'`→`0x0a`, `'#'`→`0x0b`, `'$'`→`0x0c`, `'%'`→`0x0d`, `'^'`→`0x0e`,
`'&'`→`0x0f`, `'*'`→`0x10`.

**Texture symbolic identifiers**: `ThorTexture1/2`, `YesooriTexture`,
`TagTexture`, `AvataTexture1/2`, `AvataEffectTexture1/2`,
`CharacterTexture1/2`, `CharEffectTexture1/2`, `BulletTexture1/2`,
`FlameTexture1-4`, `RayonTexture1/2`, `SpecialTexture1/2`, `CrashTexture`,
`FirewallTexture`, `JewelTexture`, `LightningTexture`, `RiderTexture`,
`TornadoTexture`, `WeaterTexture`.

**Windows DLLs referenced** (15 total): `advapi32.dll`, `ddraw.dll`,
`dinput8.dll`, `dsound.dll`, `gdi32.dll`, `imm32.dll`, `kernel32.dll`,
`mscoree.dll` (launcher stub only), `ntdll.dll`, `ole32.dll`,
`oleaut32.dll`, `shell32.dll`, `user32.dll`, `winmm.dll`, `ws2_32.dll`.

**`teleport1`**: not a chat command (a previous pass misread its position
in the data segment) — it's the sound effect played at both endpoints when
`stage.dat`'s `귀환`/"Return" gimmick swaps two players' positions. See
FILEFORMATS.md/STRINGS.md for the correction.

## 12. Room settings bitmasks

Two distinct bitmasks describe a room. **Bit *positions* below are confirmed
from the decompile; where a value's *meaning* is inferred rather than read from
the binary, it is marked (inferred).**

### 12a. Per-room `info` dword — room-list response (`0x2103`, `+0x44984`)

The `u32` broadcast per room in the bulk room-grid list. Only two fields are
decoded by the client (`RenderRoomCard` / `FUN_0042a680`); the other bits are
never read and their meaning is unknown.

| Bits | Field | Values |
|---|---|---|
| 16-17 | **game mode** | `0`-`3`, one of GunBound's four modes (Solo / Score / Tag / Jewel). **Value `3` = Jewel is confirmed**: `State11_InBattle_Render` reads the checksum-guarded mode value via `PeekPacketChecksumState` and draws the `JewelTexture` layer only when it equals `3` (this is the in-battle mode field; the room-list bits almost certainly share the same enum). Values `0`/`1`/`2` (among Solo/Score/Tag) are not yet individually mapped |
| 18-19 | **fullness level** | `0`-`3`, drives the population-gauge sprite on the card |
| 0-15, 20-31 | (not read by this client) | unknown |

The card's mode/map icon is `spriteIndex = ((info >> 16) & 3) * 11 + mapByte`,
where `mapByte` is the separate per-room map field (`+0x4497c`, up to 11 maps).

### 12b. Room-options dword — host config (Ready Room, `0x3101`)

Set by the host and sent via opcode `0x3101` (read from the state object at
`this+0x26c`, packed with `QueueOutgoingPacketField`). Confirmed radio-group
bit ranges; **which group is turn-time vs. game-type vs. item/tank limit is NOT
decoded** (needs the room-config panel's localized strings, which this project
can't read — only the numeric message IDs).

| Bits | Mask | Control group | Dispatcher cases (`State09_ReadyRoom_OnCommand`) |
|---|---|---|---|
| 0-3 | `0x0000000f` | group A (inferred: a 3-value radio) | `0x28`-`0x2a` |
| 8-11 | `0x00000f00` | group B (inferred: a 4-value radio) | `0x1e`-`0x21` |
| 12-13 | `0x00003000` | group C (2-value radio) | `0x32`-`0x35` |
| 14-15 | `0x0000c000` | group D (2-value radio; `0x3c` also commits) | `0x3c`-`0x3e` |
| ~18-23 | `0x00fc0000` | group E | `0xb`-`0xd` |

Separately, opcode `0x3103` sets **room player capacity** (a byte = 4 / 6 / 8,
not part of this dword). See [docs/screens/09_ready_room.md](docs/screens/09_ready_room.md).
