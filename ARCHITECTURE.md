# GunBound Client — Reverse-Engineered Architecture Notes

Findings from static analysis in Ghidra (`ghidra_proj/`), confirmed via decompiled
pseudocode, cross-referenced call sites, and data-layout inspection — not guesses.
Confidence is noted per finding. This complements [PROGRESS.csv](PROGRESS.csv)
(the flat function worklist) with structural/behavioral understanding.

## Dependencies

Everything the client links against or vendors internally, gathered from
the import table, the string table ([STRINGS.md](STRINGS.md)'s "Windows
DLLs referenced" section), and decompiled subsystem-init code.

### Windows system DLLs (dynamically linked)

| DLL | Used for | Confirmed via |
|---|---|---|
| `ddraw.dll` | DirectDraw7 **and** Direct3D7 — DirectX 7 packages D3D inside `ddraw.dll`, obtained by `QueryInterface`-ing the DirectDraw7 object for `IID_IDirect3D7` rather than loading a separate D3D DLL | `InitDirectDraw` (`0x4efaa0`): `LoadLibraryA("ddraw.dll")` + `DirectDrawCreateEx`; GUID-decoded `QueryInterface` chain confirmed in the rendering section below |
| `dsound.dll` | DirectSound8 audio | `InitDirectSound` (`0x4ee5b0`): `LoadLibraryA("dsound.dll")` + `DirectSoundCreate8` |
| `dinput8.dll` | DirectInput8 (keyboard/controller input) | `InitDirectInput` (`0x4edc50`): `LoadLibraryA("dinput8.dll")` + `DirectInput8Create` |
| `ws2_32.dll` | Winsock — UDP networking (`recvfrom`/`sendto`), the entire game protocol described in [PROTOCOL.md](PROTOCOL.md) | `WSAStartup` call in `WinMain`, `CCommP2P<>` notify window (`InitCommP2PNotifyWindow`, `0x4fdf00`) |
| `winmm.dll` | Windows multimedia — timing-related, specific API not isolated | Import table only |
| `gdi32.dll` | GDI — window/menu chrome outside the D3D-owned client area | Import table only |
| `user32.dll` | Window management, message loop (`WndProc` at `0x410040`) | `WinMain` |
| `advapi32.dll` | Registry access — display-mode persistence (`Software\Softnyx\GunBound`) and the hardware-fingerprint/anti-cheat registry reads found while investigating the replay `fopen` call site | `ReadRegistryDword`/`WriteRegistryDword`/`GetDisplayConfigFromRegistry` (`0x40c470`/`0x40c550`/`0x40c620`); registry-scanning functions at `0x5207d0`/`0x523530`/`0x524bb0` |
| `imm32.dll` | IME (Input Method Editor) — Korean text input in chat | Import table only |
| `shell32.dll` | Shell utility calls | Import table only, specific calls not isolated |
| `ole32.dll` / `oleaut32.dll` | COM infrastructure underlying the DirectX7 COM interfaces (`IDirectDraw7`, `IDirect3D7`, `IDirect3DDevice7`, etc.) | Import table, consistent with the confirmed COM vtable chain in the rendering section |
| `kernel32.dll` / `ntdll.dll` | Core Win32/NT — process/thread management, critical sections, file I/O (`CreateFileA`, `fopen` chain) | Throughout; e.g. `__tsopen_lk`/`__openfile`/`__fsopen` CRT chain traced during the replay-file investigation |
| `mscoree.dll` | .NET CLR | **Not used by `GunBound.gme`** — this dependency belongs to the separate **`GunBound.exe` launcher stub** (a small .NET assembly, source `GunBound.cs`) that decrypts/injects and starts the real native game; it is not linked into the decompilation target itself |

No other DLLs (no `d3d8.dll`/`d3d9.dll`, no `xinput`, no third-party
middleware DLLs) were found in the import table or string table.

### Vendored/embedded open-source code

Unlike the DLLs above (dynamically linked at runtime), this is code **compiled
directly into `GunBound.gme`** — no separate library file, just functions
living in `.text` alongside the game's own code.

- **LZHUF (`LZHUF.C`)** — a public-domain LZSS+adaptive-Huffman compression
  codec written by Haruhiko Okumura and Haruyasu Yoshizaki (released ~1988,
  the same lineage used by LHA `.lzh` archives), copied wholesale into the
  engine to compress `.xfs` archives (both the table of contents and
  individual entries) and `.dat` game-data files — see
  [FILEFORMATS.md](FILEFORMATS.md) for the full algorithm confirmation.
  Identified via an exact constants/structure match rather than just a
  family resemblance: `InitLZHUFTree` (`0x4ea300`) initializes `N_CHAR=314`
  symbols and a `T=627`-node tree (`2*N_CHAR-1`, the reference formula), and
  `DecodeLZHUFBlock`/`FUN_004ea670`/`FUN_004ea6e0` (`0x4eaba0`/`0x4ea670`/
  `0x4ea6e0`) are structurally identical to the reference source's
  `Decode`/`DecodeChar`/`DecodePosition` functions, right down to the
  4096-byte sliding window and space-initialized ring buffer. Being
  public-domain, its inclusion here carries no licensing complication for
  this decompilation project — only the surrounding game-specific code
  calling it is proprietary.
- No other vendored open-source code (no zlib, no libpng, no Boost, no
  scripting-language runtime) has been found anywhere in the binary.

### Compiler/runtime

Statically-linked **Visual C++ 2003 (linker version 7.10)** CRT — confirmed
by the full set of `R6002`-`R6029` runtime-error strings, `TLOSS`/`SING`/
`DOMAIN` math-error messages, and the CRT internals traced during the
replay-file investigation (`__fsopen`→`__openfile`→`__sopen`→`__tsopen_lk`,
the fopen implementation at `FUN_00525fac`). See
[STRINGS.md](STRINGS.md#systemcrt-boilerplate-summarized-not-itemized) for
the full boilerplate-string inventory.

## Entry point and top-level flow

`WinMain` (`0x40d8e0`) — registry checks, single-instance mutex, window
registration/creation (`WndProc` at `0x410040`), `WSAStartup`, then:
- `InitGame` (`0x40eaa0`, hWnd, hInstance) — sets up DirectDraw/DirectSound/
  DirectInput and constructs the 16-slot game-state object array (see below).
- Standard Win32 message loop: `PeekMessage` when idle calls `GameTick`
  (`0x413130`) every idle cycle (the per-frame update/render tick);
  `GetMessage`/`DispatchMessage` otherwise.
- `Shutdown` (`0x40f400`) tears down sockets/DirectX on exit.

## The game-state machine

**High confidence**, fully evidence-backed:

- `g_gameStateVTableArray` (a.k.a. `g_gameStateObjects`, base `0x5b33f8`) is a
  **16-element array of pointers to heap-allocated C++-style objects**, one per
  game state. Confirmed by: `ChangeGameState`'s special-case
  `newStateId == 0xf` (15, quit) landing exactly on array element 15
  (`0x5b33f8 + 15*4 = 0x5b3434`), and that element sharing the *same* trivial
  vtable (`0x553fb0`) as element 0 — a null-object pattern for the two states
  that need no real enter/exit behavior (pre-init and quit).
- `ChangeGameState(int newStateId)` (`0x4122f0`) is the state transition
  function. It calls `object[oldState]->vtable[+0x20]()` (exit hook) then
  `object[newState]->vtable[+0x1c]()` (enter hook), and updates
  `g_currentGameState`. Originally took its argument via the **ESI register**
  (a custom calling convention Ghidra didn't infer) — this has been fixed in
  the Ghidra project so the parameter now shows as a normal `int`.
  - Two call patterns exist: **immediate** (`WinMain`, some `GameTick` paths
    call it directly) and **deferred** (scattered game-logic code sets
    `g_pendingGameState` + `g_stateChangeRequested`, and `GameTick` polls and
    dispatches it next frame).
- Related globals: `g_currentGameState` (`0x7934d0`), `g_pendingGameState`
  (`0x5b33ec`), `g_stateChangeRequested` (`0x7934d4`),
  `g_stateChangeInProgress` (`0x793508`).

### The 16 game states — CONFIRMED by resource strings

Each state's `OnEnter` hook (vtable slot 7, offset `+0x1c`) loads a named
`.img`/`.mp3` resource set that identifies the screen unambiguously. Names in
the Ghidra project follow `StateNN_Name_OnEnter/OnExit`; vtables are
`vtable_StateNN_Name`.

| Id | Screen | Identifying resources | Object size / ctor |
|---|---|---|---|
| 0 | Null/pre-init | (shared trivial vtable `0x553fb0`) | 4 |
| 1 | **Title** | `titlemode.img`, `title.mp3` | 8 |
| 2 | **Server / Channel select** | `server_list.img`, `b_server_choiceserver.img`, `channel.mp3` | 0x6c |
| 3 | **Game Room List** (channel lobby) | `gamelist_back.img`, `gamelist_create.img`, `b_gamelist_join/ranking/avatar/buddy.img` | 0x294 — **owns `ProcessPacket`** (see below) |
| 5 | **Logo screen 1** | `logomode.img`, `logo.mp3` | 8 |
| 6 | **Logo screen 2** | `logomode2.img`, `logo2.mp3` | 8 |
| 7 | **Avatar Store / Shop** | `store_*.img`, `b_store_buy/cap/cloth/glasse/flag.img` | 0x34818 (215 KB); ctor `FUN_00443c20` builds an 8×0x224-byte array (per-avatar slots) |
| 9 | **Ready Room** (pre-battle) | `ready_selectmap.img`, `ready_selectcharacter.img`, `b_ready_startgame.img` | 0x78c; ctor `State09_ReadyRoom_Construct` |
| 10 | **Loading** | `loadmode.img`, `loadstage.img` | 0x150 |
| 11 | **In-Battle / Playing** | `stage%d.mp3`, `b_play_weapon2/weapon3/skip/tag/all` | 0x2408 (9 KB); ctor `FUN_004b3f90` |
| 12–14 | (unused/reserved) | none constructed | — |
| 15 | **Quit** | shares null vtable `0x553fb0`; `ChangeGameState(0xf)` calls `PostQuitMessage(0)` directly | 4 |

**Screen flow** (from `ChangeGameState` targets): **the normal boot path is
`InitGame` → `ChangeGameState(6)` = Logo2(6) → Title(1) → ServerSelect(2)**
directly — Logo1(5) is *not* on this path. `WinMain` only routes through
Logo1(5) → Logo2(6) as a fallback, when a first `InitGame` call returns a
specific non-zero code (`0x17`) and a second `InitGame` call is made before
`ChangeGameState(5)` (see `docs/screens/06_logo2.md`). From Title(1) the flow
continues ServerSelect(2) → GameRoomList(3) ⇄ AvatarStore(7), and
GameRoomList(3) → ReadyRoom(9) → InBattle(11), with Loading(10) interstitial.
States 0 and 15 use a shared trivial "null object" vtable — the null-object
pattern for states needing no enter/exit behavior.

> **Per-screen reimplementation docs**: [docs/screens/](docs/screens/README.md)
> has one build-oriented document per screen (identity, resources, state
> fields, rendering, input, network, transitions, and a reimplementation
> checklist), distilled from this file and PROTOCOL.md.

## The `CGameState` base class and virtual dispatch

**High confidence.** Every state object shares a common base class whose vtable
layout (confirmed across states 1–11) is:

| Slot | Offset | Role | Evidence |
|---|---|---|---|
| 0 | +0x00 | scalar-deleting destructor | `CGameState_ScalarDeletingDestructor` (`0x4e5320`) on every state; calls `CGameState_BaseDestructor` (`0x426ac0`), which resets the vtable ptr to the shared null-object vtable (`0x553fb0`) — a "poisoned after destroy" idiom. |
| 1 | +0x04 | **`ProcessPacket(int payloadLen, ushort opcode, ushort *payload)`** | Virtual, overridden per state. No-op in states that don't need network handling (`CGameState_NoOpVirtual_A`, `0x448430`). Real overrides confirmed for state 2 (`State02_ServerSelect_ProcessPacket`, `0x4e02b0`), state 3 (`State03_GameRoomList_ProcessPacket`, `0x426ad0`), state 7 (`State07_AvatarStore_ProcessPacket`, `0x4440c0`) — all three share the identical `(this,int,ushort,ushort*)` signature, confirmed via decompiler param commit. |
| 2–4 | +0x08..+0x10 | other per-state virtuals, usually no-op (`CGameState_NoOpVirtual_B`, `0x4fdef0`) except where overridden (e.g. state 3 slots 5–6 at `0x4285c0`/`0x428b90`) | input handlers? (untested) |
| 5 | +0x14 | **Keyboard/chat-input dispatcher** (confirmed for state 11 — see dedicated section below) | dispatches on a message-code-like first parameter (3-arg signature), handles chat-buffer state |
| 6 | +0x18 | **Mouse-input dispatcher** (confirmed for state 11) | dispatches directly on **Win32 mouse message codes** (`0x202`=`WM_LBUTTONUP`, `0x204`=`WM_RBUTTONDOWN`, etc.) — this is the input-routing virtual the original "input handlers? (untested)" note was hypothesizing |
| 7 | +0x1c | **OnEnter** | confirmed for all named states — loads that screen's `.img`/`.mp3` resources |
| 8 | +0x20 | **OnExit** | confirmed for all named states |
| 9 | +0x24 | another per-state virtual, present past OnExit — **for state 11 specifically, a large (17KB decompiled) cursor/update function** using `HCURSOR`, consistent with earlier notes elsewhere in this document about "camera-scroll cursor logic" living in this slot for some states | confirmed present, not fully mapped |

Each screen effectively has its **own protocol dispatcher** — decompiling
state N's slot-1 override is the way to find that screen's opcode handling
(server list ops live in state 2's handler, avatar-store purchases in state
7's, etc.), not just the room-list one.

### Speculative C++ reconstruction

**This block is an educated guess.** That screens are polymorphic C++ classes
is confirmed (the `operator_new` + vtable-install in `InitGame`, the shared
slot layout above, the `CGameState_ScalarDeletingDestructor`/`_BaseDestructor`/
`_NoOpVirtual_A/B` helpers, the null-object vtable). The class/method *names*
below are invented, and slot semantics past slot 9 are per-subclass.

```cpp
// Abstract base; each screen is a subclass. Objects heap-allocated in InitGame
// (or a per-state ctor) and installed into g_gameStateVTableArray[16].
class CGameState {
public:
    virtual ~CGameState();                                     // slot 0  CGameState_ScalarDeletingDestructor (0x4e5320)
                                                               //         -> BaseDestructor resets vtable to the null-object vtable (0x553fb0)
    virtual void ProcessPacket(int len, u16 op, u16* payload); // slot 1  per-screen protocol handler (NoOp_A default)
    virtual void v2();                                         // slot 2  (NoOp_B default)
    virtual void v3();                                         // slot 3
    virtual void v4();                                         // slot 4
    virtual void OnKeyInput(int msg, int a, int b);            // slot 5  keyboard/chat/command dispatcher
    virtual void OnMouseInput(int msg, int x, int y);          // slot 6  mouse (Win32 message codes)
    virtual void OnEnter();                                    // slot 7  load .img/.mp3, build widget tree
    virtual void OnExit();                                     // slot 8
    virtual void OnTick();                                     // slot 9  per-state (render/timer); free virtuals beyond here
    // vtable at +0x00; remaining members are per-subclass.
};
```

Subclass object sizes vary widely because each adds its own state:
`State01_Title` 8 B (a frame counter), `State02_ServerSelect` 0x6c,
`State03_GameRoomList` 0x294, `State09_ReadyRoom` 0x78c, `State11_InBattle`
0x2408, `State07_AvatarStore` 0x34818. Slots 0–9 are the shared interface;
subclasses extend the vtable freely past slot 9 (In-Battle has 18 slots, Ready
Room 20). This mirrors the parallel `CWidget` hierarchy (see
[docs/widgets.md](docs/widgets.md)) — a screen's `OnEnter` builds a tree of
`CWidget`s whose `OnCommand` callbacks feed back into the screen's own
dispatcher.

**Guessed**: every name; that it's single-inheritance; the exact slot-2/3/4
roles (only confirmed as usually-no-op). **Solid**: the construction pattern,
slots 0/1/5/6/7/8/9, the destructor/null-object behavior, and object sizes.

### State 11 (In-Battle) full vtable map — confirmed

Dumped `vtable_State11_InBattle` (`0x5566d8`) directly — an 18-entry
vtable (confirmed by the array running into non-code data immediately
after slot 17) — and decompiled every previously-unnamed slot to identify
its role:

| Slot | Address | Role |
|---|---|---|
| 0 | `0x4b4060` | destructor (`FUN_004b4060`, not yet separately confirmed as the standard scalar-deleting pattern) |
| 1 | `0x4b4100` | `State11_InBattle_ProcessPacket` |
| 2 | `0x4b5460` | `State11_InBattle_ProcessBattleAction` |
| 3, 4 | `0x4fdef0` | shared no-op (`CGameState_NoOpVirtual_B`) |
| 5 | `0x4b82b0` | **Keyboard/chat-input dispatcher** — 3-parameter signature, dispatches on the first parameter as a message/command code (confirmed cases `0x1d`, `0x39`, `0x32`-prefixed sub-switch); touches per-connection chat-state byte arrays |
| 6 | `0x4b97d0` | **Mouse-input dispatcher** — dispatches directly on literal Win32 mouse message values (`> 0x202`, `== 0x204`, `!= 0x205` branches are visible — i.e. `WM_LBUTTONUP`/`WM_RBUTTONDOWN`/`WM_RBUTTONUP` territory) |
| 7 | `0x4bb730` | `State11_InBattle_OnEnter` |
| 8 | `0x4bcd00` | `State11_InBattle_OnExit` |
| 9 | `0x4bd8b0` | Large (17KB decompiled, ~2,070 lines) function — this is the **same function** already documented elsewhere as `GameTick`'s unconditional per-tick hook (8-directional screen-edge cursor/camera-scroll bitmask, confirmed during the physics investigation). Only the first ~370 lines are the cursor/camera logic; the remaining ~1,700 lines (not previously read) include outgoing-packet field encoding, broadcast-event logging, an unconditional per-tick call to the active-object container's flagged-entry garbage collector (`FUN_004f3100`, see the generic-container note below), and what looks like turn-phase-adjacent bookkeeping (`0xc303` referenced as a literal). Still not fully mapped end to end — genuinely large and multi-purpose. |
| 10 | `0x4c1b90` | **Chat character-input helper**: appends a typed character into a per-message buffer at `+0x58b64` (9-byte stride) and a secondary buffer at `+0x58c4a` (14-byte stride), with a literal control-character remap table (`'@'→0x0a`, `'#'→0x0b`, `'$'→0x0c`, `'%'→0x0d`, `'^'→0x0e`, `'&'→0x0f`, `'*'→0x10`) — almost certainly the mechanism behind GunBound's in-chat emoticon/special-character shortcuts (typing `^` or `&` inserting a small icon rather than the literal character) |
| 11 | `0x4c1c90` | Small per-tick-looking helper (increments a counter at `this+8`, conditionally calls a couple of update functions) |
| 12 | `0x4c1d10` | One-line delegate — calls `RenderWeatherHazards` on a fixed per-connection offset (`+0x6a7f88`), nothing else |
| 13 | `0x4c1d30` | **Corrected — not a "special-weapon-effect render function."** Fully decompiled (was previously only skimmed for its string references): this is a **per-frame dynamic-texture clear pass**. It resolves ~24 named dynamic textures via `FindTextureCacheEntryByName` — not just `SpecialTexture1/2`, but the *entire* effect-texture roster (`AvataTexture1/2`, `AvataEffectTexture1/2`, `CharacterTexture1/2`, `TagTexture`, `CharEffectTexture1/2`, `BulletTexture1/2`, `FlameTexture1-4`, `RayonTexture1/2`, `SpecialTexture1/2`, `RiderTexture`, `YesooriTexture`, `JewelTexture`, `ThorTexture1/2`) — and for each one present, does a confirmed **`IDirectDrawSurface7::Lock` (vtable `+0x64`, `DDSURFACEDESC2` size `0x7c`=124 bytes) → zero-fill the entire locked surface → `Unlock` (vtable `+0x80`)** cycle. This clears every dynamic effect render-target to transparent/black once per frame, presumably right before that frame's actual sprite effects get composited into them elsewhere in the render pipeline. |
| 14 | `0x4c3020` | `State11_InBattle_Render` |
| 15 | `0x4c8890` | **Corrected — not a "finalize/send" function.** Fully decompiled: this is the **in-battle chat log display renderer**, not a network-send path (searched the whole 1,360-line decompile for any outgoing-packet-encode call — none exist; every effect is a draw call). Confirms this is `State11`'s software-blit render slot (matches `GameTick`'s dispatch of vtable slot 15 to the software path — see the rendering section below), drawing the in-battle HUD chat overlay each frame alongside the D3D battle scene from slot 14. Loops up to **10 visible chat history lines**, each with: a sender-name field (`+0x58b64`, 9-byte stride), a message-text field (`+0x58bbe`, 14-byte stride), a length (`+0x5917c`, `ushort` array), and a **per-line message-type byte** (`+0x58c4a`) that selects one of several distinct `RGB565` text colors via a `switch` (confirmed values include pure green `0x7e0`, pure blue `0x1f`, white `0xffff`, and others) — i.e. **different chat channels/message types (team chat, system messages, etc.) are color-coded**, not just plain text. Message types `0`/`1`/`7` get an extra double-draw outline pass for legibility; other types use a single `DrawFontString`-prepped draw (the same text-prep helper already seen in the lobby's room-number rendering). All text drawn via the confirmed bitmap-font renderer, `BlitRLESprite`. |
| 16 | `0x4caed0` | `State11_InBattle_RenderModeIcons` |
| 17 | `0x429800` | Confirmed genuine no-op (function body is a single `return;`, distinct from the shared `CGameState_NoOpVirtual_B`) — a state-specific empty override rather than reuse of the common stub |

This substantially resolves the original "input handlers? (untested)"
open question for at least one state: slots 5/6 are confirmed input
dispatchers (chat/keyboard and mouse respectively), slots 10/15 are a
confirmed chat-input-append/display pair (**correction**: slot 15 is a
display renderer, not a "finalize" step — see the dedicated chat pipeline
writeup immediately below), and slot 13 is a per-frame
dynamic-effect-texture clear pass (Lock/zero-fill/Unlock across the full
effect-texture roster). The same technique (dump the vtable via its
named `vtable_StateNN_Name` symbol, decompile each unnamed slot) would
work for the other 15 states, but wasn't repeated for all of them this
pass — In-Battle was chosen as the highest-value target given its
gameplay centrality.

### In-battle chat pipeline — traced from keystroke to history buffer

Investigating chat functionality end to end (going beyond slot 10's
already-documented character-append/emoticon-remap and slot 15's now-
corrected display-renderer role) found the actual **chat message
queue/history functions**, located by searching the whole binary for
every direct reference to the chat buffer offsets — only 5 functions
touch them at all, so this is a complete picture, not a sample:

- **`FUN_0041ef90`** — the real **"add chat line" function**. Takes a
  message-type byte (the same value slot 15 later reads to pick a text
  color), a player-slot index (0-7), an implicit message-text source, and
  a sound-cue parameter. Copies the sender's name from a **persistent
  per-slot name table** (`param_1 + slot*8 + 0x457a9`), with a special
  case: if that name matches a specific fixed string (compared byte-for-
  byte against `&DAT_00551e24`), the message type is **forced to `5`**
  regardless of what was passed in — i.e. messages attributed to one
  particular reserved name (almost certainly a `"SYSTEM"`-style sender)
  always render in that type's color, overriding the caller. Word-wraps
  the message text into a large scratch stack buffer before storing it,
  and returns `2` (vs. the normal `1`) when the message had to be split
  across two history lines — the caller uses this to know whether a
  second `AddChatLine`-style call is needed for the wrapped remainder
  (confirmed: `FUN_0041ef90` recursively re-invokes its own tail logic
  when this happens, at line ~165-174 of its decompile).
- **`FUN_0041ee10`** — the **ring-buffer scroll/dequeue function**,
  called automatically once the history exceeds **8 lines**
  (`*(int*)(param_1+0x58b60) > 8`, checked at the top of
  `FUN_0041ef90` before appending) — shifts every parallel array (name,
  text, type byte, length, and a per-line `0x80`-dword/512-byte scratch
  buffer at `+0x58c54`, likely a pre-word-wrapped/pre-rendered cache of
  that line) down by one slot, discarding the oldest line. This is a
  classic **fixed 8-line rotating chat history buffer**, separate from
  (and feeding) the up-to-10-line draw loop in slot 15's renderer — the
  render loop's higher iteration count likely just walks a few extra
  always-empty slots harmlessly rather than indicating a 10-line buffer.
- **Neither function sends anything over the network** — both are purely
  local history/state management. This means `AddChatLine` is used both
  for **displaying messages received from the network** (the `0x4001`-
  `0x4006` battle-action cluster in PROTOCOL.md) and, presumably, for
  **local echo of what the player themselves just typed and sent** — but
  the actual "player pressed Enter, send the composed text as an outgoing
  packet" trigger for the *in-battle* chat box wasn't located in this
  pass (State 9/10's non-battle chat-Enter handlers are already
  documented above; the in-battle equivalent — likely inside slot 5's
  keyboard dispatcher, which does handle raw scancodes for movement/aim
  controls but wasn't found touching the chat buffer offsets directly —
  remains a genuine open item for a future pass).

## Connection subsystem — broker/server connect (async, thread-backed)

Traced how the client actually opens its TCP connection (to the server-list
"broker" first, then to a chosen game server). All the functions below were
named this pass; the connection object is the large per-connection struct at
`DAT_007934e8`/`DAT_007934ec` (fields cited are offsets into it).

- **The broker address is not hardcoded — it comes from the registry.**
  `LoadClientSettingsFromRegistry` (`0x40d370`), called from `WinMain`,
  reads `HKCU\Software\Softnyx\GunBound` and pulls the `"IP"` value into
  `DAT_005b2ad0` (128-byte hostname string) and `"Port"` into `DAT_005b33e8`,
  alongside ~20 other prefs (LastServer, Version, volumes, Language,
  BuddyIP/BuddyPort default `0x20a0`, ShopURL default
  `http://shop.gunbound.com/avatar/`, and a GameBuddy Executable path). The
  native binary provisions no address itself — presumably the installer or
  the `.NET` launcher stub writes these keys.

- **Client version is provisioned, not hardcoded — with a subtlety.** There
  are two distinct "versions":
  - **The binary's build stamp**: `GunBound.gme`'s PE `VS_VERSION_INFO`
    resource (at file offset `0x1a868a`) reads **FileVersion `0.0.2.40`**
    (= client version **240**), ProductName "Softnyx GunBound Project",
    CompanyName "Softnyx". This is a static build stamp in the binary.
  - **The version reported to the server** (the one the login handshake sends
    and the server checks — a mismatch yields the "Version Error" dialog, id
    220). This is **not** the PE stamp and **not** a compiled-in constant:
    `LoadClientSettingsFromRegistry` reads the `"Version"` DWORD from
    `HKCU\Software\Softnyx\GunBound` and immediately relays it via
    `EncodeOutgoingPacketField` (wrapped in the anti-tamper value guard) — with
    **no client-side comparison against any baked-in number**. The game is
    version-agnostic and forwards whatever the registry says; the launcher
    provisions it (the jglim/gunbound-launcher `Launcher.ini` sets
    `VERSION=280`). So this exact binary is *stamped* 240 but *runs as* 280 —
    the version series (…236 / 240 / 252 / 280…) lives in the registry/launcher,
    not the `.gme`.

- **`BeginServerConnect` (`0x4d2480`)** is the public "connect to host:port"
  entry. It resets outgoing packet-field state, then calls
  **`SignalConnectRequest` (`0x4e5a50`)**, which stores the target port
  (conn+0x228) and hostname (register arg, into conn+0x28), sets the
  connection state to `3` ("dial requested"), and `SetEvent`s the worker
  thread's event (conn+0x10). The hostname is passed in a register the
  decompiler doesn't model, so it's invisible in the C signature.

- **The actual socket work runs on a background worker thread**, not inline.
  The worker's dispatch is **`HandleSocketEvent` (`0x4e57c0`)**, keyed on an
  op selector: op 2 = **`ConnectSocketToTarget` (`0x4e59b0`)** (`socket()` +
  `connect()`, sets connected flag conn+0x22a on success); op 1 = drain WSA
  events (`WSAEnumNetworkEvents`) — FD_READ → **`ReceiveFramedPackets`
  (`0x4e5610`)**, FD_WRITE → flush the send queue, FD_CLOSE →
  **`CloseConnectionSocket` (`0x4e5a20`)**; op 0 = detach. Teardown is
  **`ShutdownConnectionThread` (`0x4e5c00`)** (signal stop, join worker, close
  4 handles). Connection state values: `0`=failed, `1`=idle/reset,
  `2`=connected, `3`=dial-requested.

- **`ReceiveFramedPackets`** splits the TCP stream into 2-byte-length-prefixed
  frames (length at conn+0x230) and copies each complete frame into a ring of
  slot descriptors for the packet dispatcher; returns true to keep reading,
  false (+ enqueues error `0x65`) on a fatal framing/overflow condition.

- **Nothing is shown on screen while a connect is pending.** Because the work
  is on the worker thread, the render loop keeps running unchanged — Server
  Select displays only its static background + 3 buttons (choice-server
  disabled). Success/failure are pushed as status codes (`100`/`0x65`) into a
  generic bounded event-queue (`FUN_004f2da0`, a 0x200-entry ring — left
  unnamed, it's used by input/mouse/network alike, not connection-specific)
  targeting the connection's owning UI object (conn+0x1c); where that queue is
  drained/displayed on failure wasn't traced this pass (open item).

- **Broker and game-server connections reuse one connection object.** Picking
  a server (`ConnectToSelectedServer`) calls the same `BeginServerConnect` with the list
  entry's IP:port; since `SignalConnectRequest` closes any existing socket
  first, this **retargets** the same object from the broker to the game server
  — there is no separate broker-vs-game connection.

See [docs/screens/02_server_select.md](docs/screens/02_server_select.md) for
the screen-level view.

## Network protocol — `State03_GameRoomList_ProcessPacket` (`0x426ad0`)

This is the channel-lobby/room-list screen's packet handler — the most fully
mapped of the three known `ProcessPacket` overrides. Confirmed opcodes:

| Opcode | Behavior |
|---|---|
| `0x2001` | Branches on `*payload==0`; calls one of two cleanup/notify helpers, then `FUN_00507cc0(1, ...)`. |
| `0x201f` | Looks up a slot via `FUN_004259d0`; on miss, calls `AppendChatLogEntry` with derived offsets — looks like a per-slot record insert (chat line? item?). |
| `0x2103` | Populates a per-player-slot array (name/flags/stats) up to `playerCount` slots — **room player list update**. |
| `0x2105` | Copies a string + several small fields into a per-slot 0x80-byte display buffer at `+0x4467c` (slot stride 0x80), then mirrors it into `this+300`/`this+0x1ac`/`this+0x1b0` — **player info/profile broadcast for a target slot** (`this+0x124` holds the target slot index, set by a prior packet). |
| `0x2111` | separate branch, not yet decompiled |
| `0x2121` | `*payload==0` path: increments a counter at `+0x4739c`, sets `this+0x115=2` (a status/mode byte), copies this client's name into a persistent buffer — looks like **"you joined/were assigned to a game" confirmation**. |
| `0x21f0` | Writes into the same per-slot 0x80-byte display buffer as `0x2105`, gated on `FUN_0041c290() != -1` (find-my-slot helper) — companion write path to `0x2105`. |
| `0x21f1` | Searches the room's player-ID array (`+0x44664`) for `*payload`; on match, clears that slot (`+0x4464c + idx*4 = 0`), and if it's this client's own slot, resets `this+4` to -1 — **player left the room**. |
| `0x6001` | Unpacks 4 uint fields, builds an array of per-"player" 3-byte tuples using `rand()` (seed/roll generation?), then `ChangeGameState(7)` = **enter Avatar Store**. |
| (unlabeled, reaches `ChangeGameState(9)`) | Large per-slot stat-accumulation loop (20 elements × 0x224 bytes) summing what look like equipped-item stat bonuses per player/team slot, resets viewport to `(0,0,799,599)`, then `ChangeGameState(9)` = **enter Ready Room**. |

### `RoomPlayerSlot` — confirmed structure (opcode `0x2105`)

Decompiled the `0x2105` handler in full to nail this down. The per-slot
data is **not one contiguous struct** — it's split across a name buffer
plus several separate parallel arrays, all indexed by the same slot index
(`this+0x124`, set by a prior packet):

| Storage | Stride | Base offset | Contents |
|---|---|---|---|
| Name buffer | 0x80 bytes/slot | `DAT_005b3484 + 0x4467c` | Variable-length name copied from the packet (length given by a length-prefix byte), NUL-terminated. Also mirrored into `this+300` for the "currently viewed" slot. |
| Ready/ID byte | 1 byte/slot | `+0x4497c` | Single byte (also mirrored to `this+0x1ac`) |
| A 4-byte value | 4 bytes/slot | `+0x44984` | Mirrored to `this+0x1b0` |
| Byte flag | 1 byte/slot | `+0x4499c` | Mirrored to `this+0x1b4` — **also doubles as the equipped-item count** (see below) |
| Byte flag | 1 byte/slot | `+0x449a2` | Mirrored to `this+0x1b5` |
| Byte flag | 1 byte/slot | `+0x449a8` | Mirrored to `this+0x1b6` |
| Byte flag | 1 byte/slot | `+0x449ae` | Mirrored to `this+0x1b7` |

Immediately following these 9 bytes in the packet is a **variable-length
equipped-item list**, present only when the `+0x1b4`/`+0x4499c` byte
(reused as a count) is non-zero. Each item entry is **32 bytes** in the
wire format, decomposed on receipt into two separate destination arrays
(13-byte stride and 9-byte stride respectively — i.e. this is a "struct of
arrays" layout matching the top-level slot fields, not a flat per-item
struct). Per entry, the code reads: two NUL-terminated string-like fields
(up to ~4 raw bytes each, likely short item/mobile codes), a masked
24-or-32-bit bitfield (`& 0xffffff` applied conditionally based on its top
bits — possibly a signed/special-value sentinel check), and two more raw
4-byte values. The exact field-level meaning of each of these 8 dwords
wasn't decoded further in this pass (would need cross-referencing against
`itemdata.dat`'s record layout, once that's independently reconstructed),
but the container shape (32 bytes/entry, count-prefixed, split into two
parallel destination arrays) is confirmed directly from the decompiled
loop.

This resolves the earlier vaguer note ("0x80-byte display buffer, name +
a handful of stat bytes") — the `0x80`-byte buffer is actually **just the
name**, with all other per-slot state living in separate same-indexed
arrays rather than one packed struct.

**Confirmed opcode-range-per-screen pattern**: state 3 (room list) uses
`0x20xx`/`0x21xx`, state 2 (server select) uses `0x10xx`/`0x11xx`, state 7
(avatar store) uses `0x60xx`. Opcode value `0x2001` is reused verbatim between
state 3 and state 7's dispatchers with the same generic-cleanup meaning, and
`0x6001` is reused between the room-list and store dispatchers with different
meanings — the opcode namespace is scoped by which screen is active, matching
how the server tracks each client's current context.

## Network protocol — `State02_ServerSelect_ProcessPacket` (`0x4e02b0`)

| Opcode | Behavior |
|---|---|
| `0x1001` | **Outgoing packet builder** (not a received-opcode branch in the usual sense — triggered by the server's request). Writes opcode `0x1010` into the send buffer at `DAT_007934ec+0x4d4`, appends this client's own info via `FUN_004d2570`, then calls `getsockname()` **twice** to grab the local socket's bound address, appending both into the outgoing packet, then finalizes/sends via `FUN_004d25e0`/`FUN_004d2680`. **This is the P2P NAT-traversal handshake** — the client reports its own local `IP:port` back to the server (ties to the `CCommP2P<>` notify window found in Phase 1; GunBound uses server-mediated P2P for actual battle traffic). |
| `0x101f` | Sets `DAT_00e55e3c=1`, `DAT_007934f8=1` (login/session flags), stores `*payload` and `payload[2]` into globals `DAT_005b2b54`/`DAT_005b343c` — likely session ID / server address handoff after channel selection. |
| `0x1012` | Error-code translator: maps server error codes `0x5001/0x5011/0x5012/0x5013` to sequential internal reason codes `0x1d..0x20` stored per-slot, then calls `PeekPacketChecksumBool()` (room-membership check) — likely drives a "can't join: <reason>" error dialog. |
| `0x1102` | Zeros a 4 KB buffer then parses a list of variable-length entries (2-byte + 1-byte + length-prefixed string) into a table at `+0x3f84a` — **server/channel list population** for the "choiceserver" screen. |

## Network protocol — `State07_AvatarStore_ProcessPacket` (`0x4440c0`)

| Opcode | Behavior |
|---|---|
| `0x600f` | Builds and sends an outgoing `0x6000` request (empty payload) — likely "give me my inventory," triggered on entering the store. |
| `0x6002` | Parses a list of **owned-item entries**: each has a timestamp (parsed via `_localtime` → day/month/year, i.e. an **expiration date**), item-id fields, and a variable-length blob, stored into a per-item array at `+0x44be8` with a **confirmed 0x9c (156)-byte stride**. This is the **inventory/purchased-items list**. Full struct layout confirmed by mapping the decompiled stack-local offsets — see below. |
| `0x6017` (`*payload==0`) | Builds a **purchase confirmation dialog**: loads localized strings by resource ID (`GetLocalizedString(&g_localizedStringTable, 0xea6a..0xea6d)`), formats item name/price via `sprintf`, shows the `b_storewindow_confirm` popup image. |
| `0x6017` (`*payload==0x6003`) | Sends a `0x6000` reply packet — likely the purchase confirmation's "yes" response. |
| `0x6037` (`*payload==0`) | Guards on a slot-count check (`FUN_004010c0(0x80070057)` fatal-errors if out of range) then calls `FUN_0044c370()` — a purchase-commit path, not fully traced. |

### `InventoryItem` — confirmed structure (opcode `0x6002`, resolves the size-only note in ARCHITECTURE.md's earlier struct list)

The wire format (per item, read sequentially from the packet payload) and
the in-memory destination struct (0x9c/156 bytes, array at
`DAT_005b3484+0x44be8`) were both traced from the decompiled `0x6002`
handler. The destination offsets were recovered by mapping each
decompiler-assigned stack-local's address back to its position relative to
the local array's base (e.g. `local_4f0` sits `0x508-0x4f0 = 0x18 = 24`
bytes into the destination struct, since the struct's base local is
`local_508`):

| Dest offset | Size | Field | Wire source |
|---|---|---|---|
| `0x00` | 4 | id field 0 | `payload[0..3]` — also fed to `EncodeOutgoingPacketField` (part of the outgoing-packet checksum) and tracked as a running min/max (`this+0x32f98`/`this+0x32f94`) — likely an item ID or price |
| `0x04` | 4 | id field 1 | `payload[4..7]` |
| `0x08` | 4 | id field 2 | `payload[8..11]` |
| `0x0C` | 4 | id field 3 | `payload[12..15]` |
| `0x10`-`0x11` | 2 | unaccounted (likely padding — the raw `time_t` used to derive the date fields below isn't itself stored, only its parsed components) | `payload[16..19]` is the wire `time_t` (4 bytes), consumed by `_localtime()` but not copied into the struct directly |
| `0x12`-`0x13` | 2 | expiration year (`tm_year + 1900`) | derived from the same wire `time_t` above |
| `0x14` | 1 | expiration month (`tm_mon + 1`) | derived |
| `0x15` | 1 | expiration day (`tm_mday`) | derived |
| `0x16`-`0x17` | 2 | unaccounted (padding) | — |
| `0x18` | 4 | id field 4 | `payload[20..23]` — also fed to `EncodeOutgoingPacketField` alongside id field 0, suggesting these two together form some kind of transaction/verification pair |
| `0x1C` onward | up to ~124 bytes | variable-length blob | length-prefixed: a single byte at wire offset 24 gives the blob length, blob bytes follow at wire offset 25 onward, copied into the struct starting at `0x1C` |

The variable blob's internal field-level meaning (item name string? serialized
equip-slot/color data?) wasn't decoded further in this pass — only its
existence, length-prefix mechanism, and destination offset are confirmed.

## Network protocol — `State09_ReadyRoom_ProcessPacket` (`0x4d38c0`)

Opcodes `0x30xx`/`0x31xx`/`0x32xx`/`0x34xx`/`0x44xx`. This handler is also where
the **replay-recording system** (see below) is driven from — most branches
call `QueueBroadcastEvent` with a distinct event-type code.

| Opcode | Behavior |
|---|---|
| `0x2001` | **Leave ready room.** If a flag (`g_bBattleSessionActive`) is set, force-exits state 11 (In-Battle) via its own vtable exit-hook (`g_gameStateObjects[0xb]+0x20`) — i.e. this can tear down an in-progress battle. Then `g_pendingGameState = 3` (back to Game Room List). |
| `0x3010` | **Corrected — not character/team selection.** Calls `ComputeTurnOrder()` (shared ready-toggle, same as `0x3020` below) then `BroadcastBattleSnapshot(*payload)`/`LoadRoomSlotAvatar()` — a **match-start state broadcast** (event `0x8400`, reusing the same 20-element/`0x224`-stride loop found in the Room→Ready-Room transition; see "Two separate systems previously conflated as 'replay'") plus **(re)loading each slot's worn avatar** (`LoadRoomSlotAvatar` reads the `avatarEquipped` record at `+0x458bc+slot*8` — the per-slot high bit is **gender**, not team side — and composites the parts via `LoadAvatarSprites`). See PROTOCOL.md's corrected writeup and FILEFORMATS.md "Avatar.xfs". |
| `0x3020` | Calls `ComputeTurnOrder()` only — simpler ready/unready toggle. |
| `0x3105` | Queues broadcast event `0x8102` (self) or `0x8000`+player-id+position fields (others), and sends `WM_USER+...` (`0xc5`) UI notification — **player joined ready room**. |
| `0x3151` | Queues broadcast event `0x8200` with `payload[2]` — likely **team change**. |
| `0x3201` | Queues broadcast event `0x8100` with two fields from `this` — likely **weapon/character selection change**. |
| `0x3211` | Queues broadcast event `0x8101` — likely **map vote/selection**. |
| `0x3231` | Queues broadcast event `0x8102` — **ready-status toggle**. |
| `0x3fff` | Sends outgoing packet opcode `0x2000` with payload `0xffff` — **leave/cancel notification to server**. |
| `0x3432` | Closes the open `.sv` match-record file (`fclose`) if one is open — **match/session end, stop recording**. |
| `0x4410` (only if not already leaving) | Replies with outgoing opcode `0x3232` — looks like a **server keepalive/ping ack**. |

## Network protocol — `State11_InBattle_ProcessPacket` (`0x4b4100`)

Opcodes shared with the ready room (`0x2001`, `0x3020`, `0x3233`, `0x3400`,
`0x3fff`, `0x4410`) plus battle-specific ones (`0x4102`, `0x4413`).

| Opcode | Behavior |
|---|---|
| `0x2001` | **Leave battle** → `g_pendingGameState = 3` (Game Room List). |
| `0x3020` | **Player disconnected mid-match**: shift-compacts three of the four small per-slot spawn arrays (see action `0x8408`'s row below — **not** a `0x224`-byte stride, corrected from an earlier pass), separately reads that player's **packet-checksum state** from a per-player array at `playerId*0x224 + 0xebef4` (confirmed via `PeekPacketChecksumState`, see the packet-checksum utility section below), records broadcast event `0x307` with the departed player's stats, and — if the departed player held the active turn — reassigns it (`FUN_00413bf0`, likely `AdvanceTurn`). Full writeup in [PROTOCOL.md](PROTOCOL.md). |
| `0x3233` | **Match ends** → `g_pendingGameState = 9` (back to Ready Room). Writes a terminator byte (`2`) to the replay file and closes it — matches state 9's `0x3432` as the recording bookend. |
| `0x3400` | separate branch, not fully traced |
| `0x3fff` | Same "leave/cancel" outgoing `0x2000`/`0xffff` packet as the ready room. |

## Battle action protocol — `State11_InBattle_ProcessBattleAction` (`0x4b5460`)

**Answers the open question from the previous round**: the actual move/aim/
fire/damage traffic is *not* handled by `State11_InBattle_ProcessPacket`
(`0x4b4100`) — it's a **separate `CGameState` virtual method, vtable slot 2**
(`+0x08`, right after `ProcessPacket` at slot 1). Confirmed via decompile +
`bsfire`/`bfire1`/`bfire2`/`bifire`/`ifire`/`sfire` (weapon-firing cursor
images) and `sudden.mp3` (sudden-death music) string references — this is
unambiguously the core battle simulation, and the largest function in the
binary (11,718 bytes).

**This is a real, second protocol channel, not an isolated one-off.** Slot 2
is the shared `CGameState_NoOpVirtual_B` no-op for every state *except*
Loading (`0x43e440`), Ready Room (`0x4d4ea0`), and In-Battle (`0x4b5460`) —
exactly the three states where P2P connection setup and real-time sync would
matter. All three share the *identical* packet header format and an
overlapping action-code namespace (confirmed: action `3` = `ShowMessage` in
both Loading and In-Battle; action `0x8100` in Ready Room matches a replay
event code also used elsewhere). Working theory: **slot 1 (`ProcessPacket`)
is the reliable server-relayed protocol; slot 2 is the real-time P2P channel**
(`recvfrom`/`sendto`, the `CCommP2P<>` notify window from Phase 1) — not
proven at the socket-receive level, but the state-coverage pattern alone is
strong evidence.

A striking confirmation of the cross-state design: Loading's slot 2 handles
action `0xc301` by writing directly into the **In-Battle object's fields**
(`g_gameStateVTableArray[0xb]`, i.e. state 11, `+0x10a4` and `+0x2302`)
*before* state 11 is even the active state — pre-populating battle setup data
(a turn-timer value, checked against `60000`/`0xffff` — 60000 ms matches
GunBound's classic 60-second turn limit — and an 8-element array, likely
wind/spawn data) while still on the loading screen.

**Packet header** (`packetBuf`, `packetLen`):
- `+0x02` (ushort): action type — families seen: `0x3`, `0x40xx`, `0x84xx`,
  `0x85xx`, `0xc4xx`, `0xc801`.
- `+0x05` (byte): source player slot, **validated `<= 7`** (confirms the
  8-player cap independently again).
- `+0x21` (33): payload start.

Action `0x8500` matches a `QueueBroadcastEvent` code exactly (see "Two separate
systems previously conflated as 'replay'" below) — strong evidence this
function processes **both server-relayed packets and incoming peer-broadcast
events** through the same code path, i.e. a `0x8xxx` event arriving over the
UDP peer-broadcast channel is fed into this same action dispatcher rather than
having a separate receive path (corrected from an earlier "replay playback"
guess — this is live peer traffic, not logged-event playback).

| Action | Behavior |
|---|---|
| `3` | Calls the `ShowMessage`-style virtual at `this vtable +0x28` with a formatted string — a generic in-battle notification/toast. |
| `0x4001` | Single-byte flag toggle (only when the acting slot isn't this client) — cheap status flag, not yet identified precisely. |
| `0x4002` | **Chat message with spatial proximity filtering**: computes the distance between the sender and each of the 8 player slots, delivering the message only within ~150 units — positional/proximity chat during battle. |
| `0x4003`, `0x4004` | Similar per-player text-record lookups/inserts (`FUN_004259d0`/`AppendChatLogEntry`, the same helpers seen in the room-list handler) — likely other chat/notification variants (team chat? system message?). |
| `0x8402`, `0x8406` | Relay two ushort fields + a boolean flag from the packet, re-encoding them into an outgoing packet via `QueueOutgoingPacketField`/`EncodeOutgoingPacketField` — **confirmed** (not just "likely") aim/angle+power broadcast: tracing the send side (`FUN_00461ca0`) shows both opcodes are sent right after reading `this+0x243`/`this+0x2cc`, the exact same fields already confirmed as angle/power in Fire's own payload. See PROTOCOL.md for the full cross-reference. |
| `0x8403` | **Fire.** The richest payload: 2 fields, 2 bool flags, 2 more fields, then **8 sequential shorts** (`+0x2c`..`+0x3a`, 16 bytes — likely trajectory waypoints or arc sample points), forwarded via the same outgoing-encode helpers, then plays the `ifire` sound effect. This is the confirmed weapon-fire action; exact waypoint semantics not yet decoded. |
| `0x8404` | Appends a new entry across four parallel per-slot arrays at `+0x27`/`+0xa7`/`+0x127`/`+0x1a7` (a *different*, smaller set of parallel arrays than `0x8408`'s) — some other per-shot or per-projectile record, calls `FUN_004ccbb0`. |
| `0x8405` | Plays one of three weapon-select sounds (`b_play_weapon1/2/3`) based on which weapon slot was chosen — **weapon selection**. |
| `0x8407` | **Corrected from the previous pass — not a table selector.** All three mode-byte cases (1/2/3) call `FUN_0040a4d0(<address>)` then `AddToPacketChecksum(result)`. Decompiling `FUN_0040a4d0` shows it takes **no parameters at all** — it just enters the critical section, calls `PeekPacketChecksumState()`, and returns; the `DAT_00e9ba40`/`DAT_00e9b818`/`DAT_00796aa0` addresses pushed right before each call are never read by the callee. Raw disassembly confirms the `PUSH <address>; CALL FUN_0040a4d0` pair really is emitted with no stack cleanup consuming that value inside the callee — most likely a compiler/SEH-frame artifact or genuinely dead code (this codebase's exception-handling prologues push similar-looking constants elsewhere), not a meaningful per-mode table lookup. The net real effect of all three cases is identical: peek the current packet-checksum state and fold it back into itself via `AddToPacketChecksum` — likely a no-op-shaped integrity/keepalive step rather than gameplay data. |
| `0x8408` | **Player spawn into battle**: appends a new entry across four parallel per-slot `uint` arrays at `+0x228`/`+0x2a8`/`+0x328`/`+0x3a8`, indexed by a shared active-slot counter (`+0x227`). Confirmed sources: `+0x228` = current packet parse cursor value (position-dependent, no fixed payload offset), `+0x2a8` = fixed payload offset `0x23` (ushort), `+0x3a8` = fixed payload offset `0x25` (full 32-bit value), `+0x328` = the team/slot byte read once at the start of `ProcessBattleAction` (`payload+5`). Calls `FUN_004ccc60` (spawn visual?), increments the player count. Opcode `0x3020`'s disconnect handler shifts down three of these four arrays (`+0x228`/`+0x2a8`/`+0x328` — notably *not* `+0x3a8`) — confirms a structure-of-arrays layout for the active battle slots, distinct from the unrelated, genuinely `0x224`-byte, player-ID-indexed array also touched by `0x3020` (see that row above). |
| `0xc300` | **Turn start** (best guess): posts three chained sub-events via `PostTurnEvent(&DAT_00e55ce0, code)` — `0xc300` (self), `0xc306`, `0xc40b` — a genuine turn/round event-dispatch mechanism. The `0xc306`/`0xc40b` handlers are the natural next lead for finding the actual physics tick. |
| `0xc301` | **Turn timer/setup** — shared verbatim with `State10_Loading_ProcessBattleAction`: writes the turn-timer field (`+0x10a4`, checked against `60000`ms) and copies an 8-element setup array (`+0x2302`, likely wind/spawn data). |

**On `QueueOutgoingPacketField`/`EncodeOutgoingPacketField`** (`0x40a470`/
`0x40a380`, renamed from `FUN_0040a470`/`FUN_0040a380`): initially mistaken for
a physics event queue. Decompiling in full showed it's a **critical-section-
protected packet encoder that XORs each field against a rolling 16-byte table**
indexed by a counter — i.e. GunBound lightly **obfuscates/checksums its
outgoing packets**. So actions like `0x8403`/`0x8406` that call this are
re-encoding received data into a *new outgoing packet* (relay/forward/ack),
not feeding a local simulation queue.

**Rendering vs. physics, disambiguated.** `GameTick` calls a sequence of
In-Battle-specific vtable slots every simulation tick (fixed **50 ms / 20 Hz**,
confirmed via `(now - lastTick) / 50`). Traced all of them: slots 9, 11–17
(`+0x24` through `+0x44`) resolve to texture loading, the main render function
(confirmed via `ThorTexture`/`BulletTexture`/`LaserEffect` strings — this is
literally the sprite renderer, not physics), a post-match slot-machine
minigame, and a results-scoreboard formatter. **None of them contain the
gravity/trajectory integration** — that logic is not in this per-frame vtable
pipeline. Also ruled out: the game's `sin`/`cos` CRT calls (only 4 tiny
generic-math callers, not game code) and a very FPU-dense function cluster at
`0x51xxxx` (almost certainly compiler-generated C++ `<complex>` arithmetic,
sitting among confirmed CRT/exception-handling functions).

**Confirmed real finding along the way**: `g_sineTable360` (`0x54c240`) is a
360-entry precomputed sine lookup table, indexed via `angle % 360` (cosine via
`(angle+90) % 360`) — the classic technique for this era. Used by the render
function for sprite rotation/orientation (turret angle, etc.) — confirmed
caller is the render pipeline, not a physics function, but the same table is
almost certainly reused by whatever function does compute trajectories.

## The turn state machine (inside `ProcessBattleAction`)

Fully read through this function's remaining branches this round. `param_1[0x42e]`
is a **turn-phase field** (values 0/3/4 seen). `PostTurnEvent` (`0x4e7d30`,
delegating to `0x4e86f0`) inserts into a **sorted STL-style tree keyed by
trigger time** — a scheduled/delayed event queue, not a direct dispatch. This
confirms turn progression is driven by a chain of timed sub-events, not a
single function call:

| Action | Behavior |
|---|---|
| `0xc300` | **Turn/round start.** Posts a long chain of scheduled sub-events: `0x8005`, `0x8006`, `0xc306`, `0xc400`, `0xc401`, `0x8403` (Fire), `0x8405` (weapon sound), `0xc409`. |
| `0xc303` (sub-switch on a byte) | `0`/`1`/`2` set the turn-phase field to `3`/`4`/`0`. `0xe`/`0xf` (near-identical bodies) do full turn-setup (viewport data, sound) then post the *same* `0xc300` event chain — i.e. these are two slightly different "advance to next turn" triggers (normal end vs. timeout/surrender, unconfirmed which). |
| `0xc304` | **Movement.** Sub-cases on a 4-bit direction value (1/2/3, and a `&0x10` "running" flag) each: look up a per-player name/label buffer (confirmed **0x1120-byte stride**, a second parallel per-player array distinct from the 0x224-byte one), play a directional movement sound, call `FUN_004368f0` with a magnitude (`1`/`-4`/`0xffffffff`) — **this turned out to be a sound/cursor-effect trigger, not velocity application** (its object's vtable calls the same cursor-set function used elsewhere for `normal`/`wnormal` cursors). The actual position delta write wasn't isolated in this branch. |
| `0xc305` | Turn timeout/expiry: resets the turn-phase-related byte, sets a duration constant (`0x11`/`0x10`/`0xb5` depending on a difficulty flag) into a countdown global, shows a "turn's up" style message. |
| `0xc306` | Aim/direction confirm — reads a final ushort field into the turn-timer slot (`+0x429`), clears a per-slot cooldown field. |

**`ProcessBattleAction` now fully read, end to end** (all ~1,290 lines). The
remaining branches:
- `0xc400`: **no handler at all** in this switch — a pure scheduling
  checkpoint with zero payload logic (its only role is being a named point in
  the `0xc300` event chain, presumably for timing/ordering).
- `0xc401`: one-line delegation to `FUN_004cc1e0(this, param)` — not yet
  decompiled, small.
- `0xc409`: **same payload shape as `0x8403` Fire** (2 fields, 2 flags, 2
  fields, 8 shorts) but plays a *different* sound (`sfire` vs `ifire`) and
  resets two flags (`DAT_005f3768=1`, `DAT_005f376c=0`) plus a per-player flag
  — reads as "fire confirmed/committed" following the initial `0x8403`, not a
  new computation.
- `0x8404`: appends an entry to a **third** parallel-array set (`+0x27`/
  `+0xa7`/`+0x127`/`+0x1a7`, stride `0x80`) distinct from `0x8408`'s spawn
  arrays — plausibly a hit/damage event log (4 fields: value, id, byte, byte),
  feeding a UI update (`FUN_004ccbb0`) — a kill-feed/combat-log candidate, not
  physics.
- `0xc40a`: writes two raw ints per-slot from the packet directly — plausibly
  a final-position sync, not a live simulation step.
- `0xc40b`: iterates all 8 player slots doing turn-timeout/notification
  bookkeeping — administrative, not physics.

**No gravity/velocity integration exists anywhere in this function.**

**Followed the thread to the send side instead.** Found and decompiled
`State11_InBattle_HandleFireInput` (`0x45f910`, was `FUN_0045f910`) — the
*local* handler that decides a fire attempt's outcome and sends the resulting
action code. Confirmed: `this+0x243` and `this+0x2cc` are the first two
payload fields sent (matching `ProcessBattleAction`'s Fire field order) —
almost certainly **angle and power**. Critically: **this function also has no
floating-point instructions**, and rather than computing a trajectory, it
**selects between pre-existing outcome codes** (`0x8403`/`0xc400`/`0xc409`)
based on turn-state conditions.

**Ran the systematic `operator_new` sweep** (hypothesis (c) above) to check
for a standalone per-shot projectile object: found and resolved a duplicate
symbol issue (the compiler emitted a thunk at `0x520228` pointing to the real
`operator_new` at `0x52022d`; naive xref search on just one missed most call
sites) and collected all 270 allocation call sites across the binary with
their sizes and calling functions. **Neither `HandleFireInput` nor
`ProcessBattleAction` appears anywhere in that list** — no object is
allocated anywhere in the fire pathway. This rules out hypothesis (c): there
is no standalone projectile/shot class instantiated per-fire.

(Side finding from the sweep: a run of ~40 near-identical ~16 KB allocations
across addresses `0x42bbb0`–`0x4b1810`, confirmed via strings as per-character
weapon effect/bullet sprite-name tables — e.g. `bullet1n`/`bullet1s`,
`bullet1p`..`bullet15p`, `flame%d%d`. This is the character/weapon visual
asset table system, useful context for the render side later, not physics.)

**Also fully decompiled `GameTick`'s unconditional per-tick hook**
(`State11_InBattle_OnTick`, called every 50 ms regardless of network activity for
Ready Room/Store/In-Battle — the most plausible place for local, tick-driven
physics if it existed). 2,071 lines, zero floating-point instructions. Its
actual logic (not just its strings) is confirmed to be an **8-directional
screen-edge cursor/camera-scroll system**, now traced end to end (globals
named this pass):

- Cursor position (`DAT_0056d10c`/`DAT_0056d110`) is compared against the
  800×600 screen edges (`<5` / `>0x31b`=795 for X, `<5` / `>0x253`=595 for Y)
  to build a 4-bit direction bitmask (left/right/up/down). The bitmask
  (0/1/2/4/5/6/8/9/10 — the 8 diagonal+cardinal combos, plus 0 for center)
  selects one of 9 `HCURSOR` handles via `SetCursor` (tracked in `DAT_00793510`,
  0–8) and, separately, a per-direction scroll-speed pair from the table at
  `DAT_005f2f44`.
- That speed feeds two accumulators: **`g_nCameraScrollX`/`g_nCameraScrollY`**
  (`0x6a7718`/`0x6a771c`), incremented by `(perDirectionSpeed * sign)/10` each
  tick, then clamped to `[g_nCameraBoundX±400]` (X) and
  `[g_nCameraBoundY-0x104, g_nCameraBoundY-0x14]` (Y, asymmetric — matches the
  stage top/bottom asymmetry seen elsewhere). `State11_InBattle_HandleMouseInput`
  also writes these two directly (presumably drag-scroll).
- **`g_nCameraX`/`g_nCameraY`** (`0x6a7710`/`0x6a7714`) are the values the
  renderer actually reads (`State11_InBattle_Render`, `RenderMobile`: world
  position minus camX/camY, biased +400/+0x12a). These are a **separate pair**
  from the scroll accumulator above — read broadly, but not written anywhere
  in `State11_InBattle_OnTick` itself. The exact update path from
  `g_nCameraScrollX/Y` into `g_nCameraX/Y` (smoothing? direct copy elsewhere?)
  is not yet traced.
- **`g_nCameraBoundX`/`g_nCameraBoundY`** (`0x6a7720`/`0x6a7724`) are the clamp
  center the scroll accumulator is kept within; also read as a generic
  position-bound check across dozens of per-type projectile/mobile functions
  (likely derived from the stage/terrain extents at match start — compare
  `ComputeShotViewBounds`'s similar terrain-derived per-shot bounds, `0x4e51f0`).

The slot-machine minigame strings found earlier are a different branch of
this same function. No trajectory code here either.

**Conclusion, now reasonably well-supported rather than speculative**: across
every angle checked — the packet receive handler, the local fire-input
handler, the unconditional per-tick hook, an FPU-density scan of all 2,300+
functions, and a complete `operator_new` audit — **no client-side
gravity/trajectory integration was found, and no standalone shot object is
ever allocated.** The remaining live hypothesis is that **trajectory
resolution is server-authoritative**: the client sends angle/power (and
possibly receives back either resolved final positions or a precomputed
waypoint sequence to animate through, matching the Fire payload's 8 shorts).
Confirming this with certainty would require either the server binary (not
available) or dynamic analysis (attach a debugger to the running client while
firing a shot and watch what actually executes) — both out of reach for
further static analysis of this client binary alone. I'm treating this
physics thread as closed for static analysis purposes unless new evidence
surfaces elsewhere.

## Terrain: the collision mask and the crater-carving pipeline

**High confidence, fully traced.** The battle terrain is a per-column occupancy
bitmap (a byte array, non-zero = solid ground) on a terrain object with fields:
`+0x18` row stride, `+0x1c` column count/scan bound, `+0x34` the mask buffer
base, `+0x51` a "row already processed" flag array, `+0x854`/`+0x858` the
excavated-column min/max range.

- **`FindGroundHeightAtColumn`** (`0x4e4340`) — the read side: scans the mask
  buffer down a column from a starting row until it finds the first non-zero
  (solid) byte, returning that row as the ground height (`10000` = no ground
  found / off the terrain). Called by `ComputeMobileGroundY` and every mobile's
  fall/landing check.
- **`CarveTerrainCrater(radius, centerX, centerY, aspectParam, ...)`** (`0x4e4450`)
  — the write side: a **Bresenham midpoint-circle rasterizer** that zeroes the
  mask buffer within an ellipse (the circle math is squashed by an aspect-ratio
  parameter, giving GunBound's characteristic non-circular craters). For each
  carved row it also calls **`DarkenTerrainScorchRow`** (`0x4e4bc0`) on a
  slightly wider ring — that function walks the terrain's **visual** RLE sprite
  pixel data (the same `.img` run-length format documented in FILEFORMATS.md:
  `[stride][run_count]` then `[x_offset][length][pixels]` spans) and darkens
  each pixel via `(pixel & 0xe79c) >> 2` (a per-channel divide-by-~4), producing
  the scorch-mark ring around a fresh crater. Rows are marked processed via the
  `+0x51` flag array so the darken pass only runs once per row per impact.
- **`SpawnCraterDebris`** (`0x439600`) — spawns a handful of `ani_%02d`
  animated-sprite debris/explosion particle objects with randomized position,
  velocity, and simulated gravity (a `0x3c - iVar5` term) — the flying-dirt-clod
  visual that accompanies a crater.
- **`ApplyCraterExcavation`** (`0x4e4970`) — the per-impact orchestrator, called
  from `CProjectile::DetonateProjectile` (`0x4572b0`): calls
  `CarveTerrainCrater`, sets the excavated-column range (`+0x854`/`+0x858`) so
  the next step only touches changed columns, calls `SpawnCraterDebris`, and
  (gated on `DAT_0079352a`) broadcasts event `0xf004` (impact position) via
  `QueueBroadcastEvent`/`BroadcastQueuedEvent` (see "Two separate systems
  previously conflated as 'replay'").
- **`RebuildTerrainColumnCache`** (`0x4e4d00`) — called right after
  `ApplyCraterExcavation` in `DetonateProjectile`. For each column, if it falls
  outside the excavated range it copies the previous cached column data
  straight through (a ping-pong buffer swap between `terrainObj+0x34` and
  `terrainObj+0x3c`); if it falls inside the excavated range it re-runs an
  RLE-style zero-run compaction over the mask to rebuild that column's cached
  representation from the now-carved mask. This is what keeps whatever consumes
  the terrain mask (rendering, ground-height queries) consistent after a crater
  without recomputing every column every impact.

Together this is the complete crater pipeline: **impact → carve circular hole in
the collision mask → darken the scorch ring in the visual sprite → spawn debris
particles → broadcast the impact → rebuild the per-column cache for only the
changed columns.**

## Packet-checksum utility family (broadly recurring)

A cluster of tiny functions, called from nearly every packet handler decompiled
so far, all wrapping the same critical-section-protected state (accessed via
an implicit register "this", not a normal parameter — same custom-calling-
convention pattern as `ChangeGameState`):
- `PeekPacketChecksumState` (`0x40a2e0`) — read current value.
- `AddToPacketChecksum` / `SubFromPacketChecksum` (`0x40aab0`/`0x40aaf0`) —
  read, add/subtract, re-encode.
- `PacketChecksumEquals` / `PacketChecksumNotEquals` (`0x40b270`/`0x40b2a0`) —
  equality checks against the same state (previously mis-characterized in
  earlier notes as generic "flag checks").
- `EncodeChecksumState` / `EncodeChecksumStateXored` (`0x40a4a0`/`0x40a440`) —
  push the current or XOR-mixed value through `EncodeOutgoingPacketField`.

**Per-player instances confirmed.** Most call sites use the implicit/default
state, but `PeekPacketChecksumState` is also called with an **explicit
pointer argument** at several sites — a whole-binary scan for every
instruction referencing the constant `0xebef4` (34 hits across ~15
functions, including `0x3020`'s disconnect handler and
`State11_InBattle_ProcessBattleAction`) found a consistent pattern:
`playerId * 0x224 + 0xebef4` computes a pointer into an **array of
per-player packet-checksum-state objects** (0x224/548 bytes each),
passed directly into `PeekPacketChecksumState` (sometimes via the thin
wrapper `PeekChecksumStateUnderLock` (`0x40a4d0`), which is just
`EnterCriticalSection` + `PeekPacketChecksumState` + `LeaveCriticalSection`).
This resolves what
several earlier passes had flagged as an unidentified `0x224`-byte
"`PlayerGameSlot`" struct spawned by action `0x8408` — that was a
conflation; `0x8408` never touches this array at all (it populates four
separate small `uint` arrays instead, see [PROTOCOL.md](PROTOCOL.md)'s
action `0x8408` writeup). Whether the *other* `0x224`-byte sightings
elsewhere (the room-list's 20-element loop, the Avatar Store's 8-element
array) are this same checksum-state struct, or an unrelated struct that
happens to share the size, is still unresolved.

Also named this round: `GetPlayerRecordBySlot` (`0x4206f0`) — a per-slot
player-record accessor called throughout the battle/room code.

**Two-state comparator siblings of `CompareChecksumPair`.** `CompareChecksumPair`
(`0x40b490`, `a<b`) turned out to have a small family of siblings — same
no-argument, peek-two-live-states shape, one op each: `CompareChecksumMatch`
(`0x40b390`, `a==b`), `CompareChecksumExceeds` (`0x40b410`, `a>b`),
`CompareChecksumAtMost` (`0x40b4d0`, `a<=b`). These are distinct from the
`PacketChecksumEquals`/`PacketChecksumGreaterThan`/etc. family, which compares
one peeked state against a **literal parameter** rather than two live states.

**Two more `EncodeChecksumDelta*` lightweight siblings**: `EncodeDecrementedChecksum`
(`0x40b060`, re-encodes `state - 1`) and `EncodeDividedChecksum` (`0x40ab20`,
re-encodes `state / divisor`, zero-divisor guarded) — both skip the
guard-buffer/scrub ceremony the `EncodeChecksumDelta*` family uses, re-encoding
directly.

## Two separate systems previously conflated as "replay"

An earlier pass named a cluster of functions under a `Replay_*`/`g_replayEvent*`
family, on the assumption they were all one local match-recording system. Fully
decompiling the two key functions (`WriteReplayEventRecord` and
`BroadcastQueuedEvent`, formerly `Replay_FlushEvent`) this pass showed **these
are two unrelated mechanisms that happen to run side by side** — one genuinely
writes a local file, the other never touches a file at all. They are documented
separately below; the second family was renamed off "Replay" accordingly.

### 1. The local `.sv` match-record file — genuine, file-based

**High confidence, directly observed via `_fwrite`.** `WriteReplayEventRecord`
(`0x4104f0`) writes a local file unconditionally whenever the file handle is
open — no relation to the broadcast system below:

- File handle: a global `FILE*` at `DAT_006a9b68` (not yet given a clean name —
  it's accessed via `&DAT_006a9b68 + DAT_005b3484`, an odd indexing pattern
  worth double-checking), opened somewhere in the Ready Room's entry flow
  (filename format confirmed as `%s%s - %s.sv`, `%Y%m%d %H%M` timestamp style,
  found in state 9's string references).
- `WriteReplayEventRecord(size, type, body)` (`0x4104f0`) — if
  `g_replayFileHandle != NULL`, writes a fixed record header (a `0` tag byte,
  a 4-byte value from `DAT_005b3424+4`, the `size`, the `type`) followed by the
  raw `body` bytes, via direct `_fwrite` calls. `PumpBattleActions` (`0x412a20`)
  does the same thing inline for battle-action packets (tag byte `1` instead of
  `0`). This is the actual, confirmed local match-record writer.
- The file is closed with a small terminator byte (`2`) written first — seen
  at both `State09`'s `0x3432` (session end) and `State11`'s `0x3233` (match
  end back to ready room), i.e. **recording spans from ready-room entry
  through match end**, not just the battle itself.
- Reconstructing the `.sv` file format (event-code table + per-event payload
  layouts, now that the true writer is pinned down) is still a good standalone
  follow-up — a replay parser/viewer independent of the rest of the game.

### 2. The peer-broadcast event channel — renamed off "Replay"

**High confidence, directly observed via `sendto`/cipher calls.** This is a
**separate, UDP-based, peer-to-peer event broadcast** — not a file writer at
all. Renamed this pass (was `Replay_*`/`g_replayEvent*`):

- Event buffer: `g_abBroadcastEventBuffer` (`0xe9aacc`) is a flat byte buffer;
  `g_dwBroadcastEventCursor` (`0xe9accc`) is the write cursor.
- `QueueBroadcastEvent(code)` (`0x4e6c90`, was `Replay_AppendEvent`) appends a
  known event-type code (a ushort, values seen: `0x307`, `0x8000`, `0x8100`,
  `0x8101`, `0x8102`, `0x8103`, `0x8200`, `0x8500`) — callers then manually
  append the event's payload bytes to the same buffer before calling...
- `BroadcastQueuedEvent()` (`0x4e6fc0`, was `Replay_FlushEvent`) — fully
  decompiled: `EncryptEventBroadcast` (`0x4e6df0`) checksums the pending event
  body and encrypts it in place via `EncodeCipherBlock` (the same transport
  cipher used for regular packets — see "Packet transport crypto" below), then
  `BroadcastQueuedEvent` loops the **8 room slots**, and for each slot with a
  pending-event bit set, calls `SendUdpDatagram` (`0x4e72d0`) **twice** — once
  to that slot's primary `(ip, port)` and once to a secondary `(ip, port)` pair
  if present — i.e. it **directly broadcasts the encrypted event to every other
  connected peer over UDP**, bypassing the main client-server socket entirely.
  This is a peer-to-peer action-relay channel, likely for low-latency shot/move
  sync alongside (not instead of) the authoritative server relay — a fourth
  transport alongside the documented channel 1/2/3.
- `AppendBroadcastString(str)` (`0x4e6db0`, was `Replay_AppendString`) — a
  string variant of the same append pattern (used for name fields).
- `BroadcastBattleSnapshot(flushFlag)` (`0x4dc200`, was `Replay_WriteBattleSnapshot`)
  — the **full-state snapshot record** (event `0x8400`). Fired from
  `State09_ReadyRoom_OnEnter` at session start (and the `0x3010`/`0x3020` packet
  handlers): appends `0x8400`, then serializes the battle-scene header
  (`ctx+0x2331c..0x23338`) followed by **both** 20-element `0x224`-stride guarded
  per-slot arrays (8 bytes/element via `PeekPacketChecksumState`, bound
  `20*0x224 = 0x2ad0`) — the full seeded state broadcast to a newly-joined or
  resyncing peer. `flushFlag == -1` flushes; otherwise it chains to `FUN_004e7140`.

### The capture gate and the battle frame loop

The whole recording path is gated by one byte flag, **`g_bBattleSessionActive`**
(`0x793522`, was `DAT_00793522`): `1` while an active recorded match session is
running, `0` when idle/exited. It is set to `1` by `State09_ReadyRoom_ProcessPacket`
(`0x4d46ca`, on the match-start packet) and cleared to `0` by
`State09_ReadyRoom_OnExit` (`0x4d7ae8`) — matching the "recording spans ready-room
entry through match end" observation above. `WriteReplayEventRecord` (`0x411240`)
captures a per-slot record **only when `g_bBattleSessionActive == 1` and
`g_currentGameState == 9`**, which is what fixes the direction: `1` is the
**capture/live** mode, not replay playback.

The same flag selects the per-frame work in the battle main loop:

- **`State09_ReadyRoom_OnTick`** (`0x4d7b20`, was `FUN_004d7b20`) runs every frame on the
  battle-world object. It decrements the AFK/round timers, runs the item-icon
  cursor logic, the 300-frame idle timeout (auto-sends the `0x2000` packet), the
  active-object GC (`0x4f3100`), and updates all 8×2 scene objects through their
  vtables. Then: **if `g_bBattleSessionActive == 0`** it just emits a `0xa000`
  broadcast heartbeat every 200 frames; **if `!= 0`** it delegates the frame to…
- **`ProcessBattleFrame`** (`0x4dcbe0`, was `FUN_004dcbe0`, ~12 KB — the 2nd
  largest function in the binary). This is the live per-frame battle processor:
  it advances the world frame counter (`+0x740`), works through guard-protected
  state on `g_clientContext` (`+0x475c4`/`+0x475c8`), and holds a very large
  content-id → sprite-name switch covering the *entire* in-battle sprite roster
  (`bullet1-16` in n/p/s/l variants, `flame`/`ssflame`/`jflame` 1-16, `tank1-16`,
  jewel, thor, teleport, rayonmine, crystal, the `b_play_*` HUD buttons, …),
  instantiating each via `LoadSpriteSet` / `FindPreloadedTextureByName` /
  `LoadRoomSlotAvatar`, playing sounds, and appending broadcast events.

This is a strong, self-contained subsystem — reconstructing the `.sv` file
format (event-code table + per-event payload layouts) would be a good
standalone follow-up, and is probably the most "shippable" single feature to
fully decompile (a replay parser/viewer) independent of the rest of the game.

## Recurring structure sizes (useful anchors for further work)

- **0x9c (156) bytes** — **fully confirmed** `InventoryItem` struct (4 id
  fields, expiration date parsed from a wire timestamp, a variable-length
  trailing blob), array at `DAT_005b3484+0x44be8` — full field-offset
  layout now documented in the Avatar Store section above.
- **0x224 (548) bytes** — **confirmed to be (at least) two unrelated things
  that happen to share a size.** (1) An array of per-player
  **packet-checksum-state** objects at `+0xebef4` (see the packet-checksum
  utility section above) — not a gameplay struct. (2) The state-7 Avatar
  Store's 8-element array uses a *different*, much more minimal
  constructor/destructor pair (`InitGuardSlot`/`ScrubChecksumGuard`, size 24/53
  bytes) — decompiled this pass: the constructor just zeroes a byte at
  `+0x220` and a dword at `+0x14`, then calls `EncodeOutgoingPacketField(0)`;
  the destructor conditionally frees whatever the `+0x14` field points to.
  This is a **generic lightweight container** (an optional owned pointer +
  an active/flag byte + checksum-encoding participation), not obviously
  gameplay-specific — likely a reusable engine primitive for "a slot that
  may or may not own a heap sub-object," used here for per-avatar-slot data
  but probably reused elsewhere too (this exact ctor/dtor pair, with the
  same `0x224` stride, also appears in `FUN_00415d40`'s huge object-init
  function from earlier session work). A related, larger initializer,
  **`InitGuardedChecksumSlot`** (`0x40ada0`, 248 bytes), does the same
  `+0x220`/`+0x14` zero-init plus an extra `EncodeChecksumDeltaMul`-seeded
  checksum step inside an SEH scaffold; called from `WriteReplayEventRecord`
  and a cluster of per-type projectile constructors — likely the guard-slot
  initializer used when the owning object also needs an initial checksum
  contribution seeded at construction time. (3) The room-list's 20-element
  loop **doesn't cleanly match either identity** — checked this pass: its
  loop counter increments by `0x224` up to `0x2ad0` (confirming 20
  iterations, `20*0x224 = 0x2ad0`), but the actual per-element field
  reads/writes inside the loop use a completely different stride
  (`index*0x14`, i.e. a 20-multiplier, not `0x224`), and repeatedly call
  `PeekPacketChecksumState` on a **fixed, non-array-indexed** address
  rather than walking anything at `counter`'s stride. This reads like
  `iVar24`'s `0x224` increment is tracking consumption of a conceptual
  20-record-of-0x224-bytes-each *wire/source* buffer (similar to the
  wire-vs-destination split already confirmed for `InventoryItem` and
  `RoomPlayerSlot`'s equipped-item list) rather than indexing a real
  in-memory `0x224`-byte struct array here. Inconclusive — not resolved
  either way this pass.
- **0x80 (128) bytes** — per-room-slot player **name buffer only** (not a
  combined name+stats struct as originally thought — the other per-slot
  fields live in separate same-indexed parallel arrays), confirmed via
  opcode `0x2105` in the room-list handler — see the dedicated
  `RoomPlayerSlot` section above.
- **0x17e4 (6,116) bytes** — two large arrays (9 and 21 elements) inside the
  state-7 object, constructor `FUN_00425350` / destructor `FUN_004254a0`.
  Purpose unknown; possibly per-round history, per-map-tile, or animation data.
- **0xd1d4 (53,716) bytes** — **the battle mobile object** (one per in-play
  tank). Created by the factory **`CreateMobile`** (`0x42b0b0`,
  `src/battle/CreateMobile.c`): a 16-way `switch(mobileType)` over ids `0..0xF`,
  each branch `operator_new(0xd1d4)` + shared base ctor **`InitMobile`**
  (`0x458b80`, sets the base vtable `0x555c68`) + a **per-type vtable** override.
  `default` falls back to type 0. So the 16 mobiles are 16 C++ subclasses of a
  common base, distinguished only by vtable — the GunBound mobile roster. After
  construction `CreateMobile` loads the mobile's `avata`/`tank%d` textures
  (`FindPreloadedTextureByName`), copies the player name into the object, primes
  its animation state, sets sprite-id fields (`obj[6] = type+5000`,
  `obj[0x241] = type+0x13ec`), then registers it into the client context
  (`FUN_0041c360`) and the global active-object list (`RegisterActiveObject`) —
  i.e. it constructs **and** spawns into the running battle.
  `State11_InBattle_OnEnter` calls it once per active room slot (the
  `Ctx_roomSlotActive`/`+0x45914` gate); interleaved `EncodeOutgoingPacketField`
  calls thread each spawn through the lockstep/replay sync stream.

  **type → vtable table** (from CreateMobile's cases):

  | type | vtable      | notes |
  |------|-------------|-------|
  | 0    | `0x555af8`  | also the `default` fallback |
  | 1    | `0x556230`  | |
  | 2    | `0x5562a8`  | |
  | 3    | `0x5566a0`  | |
  | 4    | `0x556264`  | |
  | 5    | `0x555c14`  | |
  | 6    | `0x556448`  | |
  | 7    | `0x5561ec`  | |
  | 8    | `0x555d34`  | |
  | 9    | `0x5560f0`  | extra ctor step `FUN_00437f70` when arg13 set |
  | 10   | `0x555f7c`  | |
  | 11   | `0x556640`  | |
  | 12   | `0x555f18`  | |
  | 13   | `0x555e54`  | **dedicated ctor** `FUN_0046cb60` (sets `obj[0x2ffc]=2`) |
  | 14   | `0x556038`  | extra ctor step `FUN_00438100` when arg13 set |
  | 15   | `0x555d54`  | |

  Types 9, 13, and 14 are structurally special (dedicated ctor / extra
  construction step); the rest just swap the vtable inline. **The canonical
  mobile NAME for each type id is not yet mapped** — the subclasses are
  differentiated by behavior (vtable methods), and the string constants
  clustered near the vtables (`LightningTexture`, `FirewallTexture`,
  `TornadoTexture`, `jflame%d`, …) are *shared effect/animation* textures, not a
  type→name table. Naming the 16 mobiles needs per-vtable method disassembly,
  cross-referencing the `type+5000` sprite ids against the asset archives, or
  matching the **type-indexed stat records** in `characterdata.dat` (16 ×
  332-byte records, now decoded — see FILEFORMATS.md) against a known-good
  GunBound mobile stat reference — none done yet, so no names are asserted here.

  The class hierarchy is reconstructed in **`src/cxx/Mobile.h`** (`CMobile`
  base + the 16-entry type→vtable table), with the object size and confirmed
  field offsets machine-checked in `cxx_selftest.cpp`. The base vtable
  (`0x555c68`) is **8 slots**: `[0]` scalar-deleting dtor (per-type), `[1]`
  handle-acquire, `[2]/[3]` update/serialize, `[4]` no-op, `[5]` update
  (type 13 overrides), `[6]` `HandleFireInput` (`0x45f910`, shared), `[7]` the
  per-type main action (base is a no-op — every subclass overrides it). Each
  subclass overrides only slots 0 and 7 (type 13 also slot 5) and adds no data
  members, so all 16 share the identical `0xd1d4` layout.

## Subsystem init functions (confirmed)

- `InitDirectDraw` (`0x4efaa0`) — `LoadLibraryA("ddraw.dll")` + `DirectDrawCreateEx`.
- `InitDirectSound` (`0x4ee5b0`) — `LoadLibraryA("dsound.dll")` + `DirectSoundCreate8`.
- `InitDirectInput` (`0x4edc50`) — `LoadLibraryA("dinput8.dll")` + `DirectInput8Create`.
- `InitCommP2PNotifyWindow` (`0x4fdf00`) — hidden `STATIC` window
  ("CCommP2P<> Notify Window") used as a `WSAAsyncSelect`/event-notify target.
- `ReadRegistryDword` / `WriteRegistryDword` / `GetDisplayConfigFromRegistry`
  (`0x40c470`/`0x40c550`/`0x40c620`) — persist display bit-depth setting under
  `Software\Softnyx\GunBound`.

## Audio subsystem (DirectSound8, streamed)

Music and effects run through DirectSound8 on **dedicated worker threads** with
**double-buffered streaming** — the game does not use MCI/DirectShow/`PlaySound`
(none are imported), and imports **no external mp3 decoder** (only the 15 system
DLLs), so any `.mp3` decode is in-house/statically linked.

- **`InitDirectSound`** (`0x4ee5b0`): `LoadLibraryA("dsound.dll")` →
  `GetProcAddress("DirectSoundCreate8")` → creates the device, then constructs
  sound-manager objects via `FUN_004eebe0` and `FUN_004ef3a0`. **Both spawn a
  worker thread** (`__beginthread(FUN_004ef870, ...)`) — so there appear to be
  **two streaming sound objects** (most plausibly one for music, one for
  effects; the split isn't individually confirmed).
- **The streaming worker** (`FUN_004ef870` → `AudioStreamThreadProc`): a classic
  double-buffered loop — `WaitForMultipleObjects(2, &events, FALSE, 100)` on the
  object's **two DirectSound position-notification events** (at object `+0x8`);
  on a notify it calls the object's refill vtable method (`slot 0`, given the
  event index) to decode+fill the buffer half that just played, plus a periodic
  tick (`slot 1`) on the 100 ms timeout; loops while the running flag
  (object `+0x10`) is set, then `__endthread`.
- **`PlayMusicTrack` — music-track control** (called from most screens' `OnEnter`:
  `title.mp3`, `channel.mp3`, `logo.mp3`, `stage%d.mp3`). Takes a track name (in
  a register, not visible in the C signature), compares it against the
  currently-playing track name (`DAT_00793568`); if unchanged it returns early
  ("already playing"), otherwise it switches via the sound object's `vtable+0xc`.
- **Battle music** is `stage%d.mp3` where `%d` is the stage id
  (`g_clientContext+0x475c4`) or `rand()%6 + 1` — i.e. 6 in-battle tracks.
- **Volume/mode** come from the registry (`MusicVolume`, `EffectVolume`,
  `MidiMode`) via `LoadClientSettingsFromRegistry`.

**Resolved this pass: the in-house MPEG audio (mp3) decoder, found and
architecturally mapped.** The streaming worker's `slot 0` refill method is
**`DecodeSoundBufferChunk`** (`0x4eef80`): it locks the DirectSound buffer
(vtable `+0x2c`), decodes compressed audio straight into the locked region,
and unlocks (vtable `+0x4c`). The actual decode is a substantial, previously
entirely `FUN_`-named subsystem occupying roughly `0x50f8b0`-`0x517xxx` —
confirmed as genuine MPEG-1 Audio decode (not a generic LZHUF/compression
variant, despite superficially similar bitstream-reading code shape) from
unambiguous fingerprints:
- A `2^(x/12)`-style scalefactor power table and a sampling-rate reciprocal
  table (`_DAT_00544370 / *(int*)(&DAT_005637e8+i)`).
- Grouped-sample reconstruction tables built by base-3/5/9 digit
  decomposition — the classic MPEG-1 **Layer II** grouped-sample coding
  scheme for its 3-, 5-, and 9-level quantizers.
- A layer/mode dispatch (`DecodeMpegAudioFrame`, `0x512f80`) selecting one of
  several decode paths via a function-pointer table indexed by a mode field,
  zero-initializing a **2304-dword output buffer** — exactly `1152 samples ×
  2 channels`, the standard MPEG-1 frame sample count.
- **`InitMpegSynthesisTables`** (`0x5167c0`): builds `1/cos(...)` twiddle
  factors for a radix-2 butterfly (sizes 16/8/4/2/1) and zeroes two
  512-sample circular history buffers — the polyphase synthesis filterbank's
  classic IMDCT/windowing setup and V-buffer.
- **`DecodeMpegLayerIISamples`** (`0x50f8b0`): the actual bitstream-to-sample
  decode, walking the allocation-info/scalefactor tables via a
  variable-bit-length reader.

This is a **substantial, self-contained subsystem** (dozens of internal
functions across `0x50f8b0`-`0x517xxx`: bit allocation, scalefactor decode,
requantization, IMDCT, polyphase synthesis) — only the four functions above
were named and documented this pass; the deep internals (Huffman/allocation
codebooks, the actual IMDCT butterfly, per-subband synthesis) remain
`FUN_`-named. Two sibling frame-decode paths dispatched from
`DecodeMpegAudioFrame` (`0x5144e0`, `0x5163d0` — plausibly Layer I and Layer
III/III-with-Huffman) weren't traced this pass. A dedicated follow-up pass
could map this out fully; it's a well-bounded, independently interesting
target (confirming exact MPEG layer/bitrate/samplerate support) separate from
the rest of the game logic.

Still open: which of the two DirectSound objects is music vs. effects, and
the sound-effect trigger API (how a one-shot SFX is queued).

## The custom cursor system

The client hides the OS cursor and manages its own. Several cooperating pieces:

- **OS cursor hidden.** `WinMain` calls `ShowCursor(0)` right before the game
  loop (re-enabled only on exit). The window class registers `IDC_ARROW`, but
  it isn't used during play.
- **Custom cursor sprite — the visible pointer, drawn by `GameTick`.**
  `ChangeGameState` preloads `cursor.img` via
  `FindPreloadedTextureByName("cursor")` into `g_cursorTexture`; **`cursor.img`
  is a 102-frame, 22×22 sprite** (confirmed from the asset header — vs. 1 frame
  for `titlemode.img`, 5 for `bullet1n.img`). The **actual per-frame draw is in
  `GameTick` (`0x413130`)**, traced via Ghidra: each frame, if
  `g_cursorFrame >= 0` and the sprites are loaded, it resolves a sprite frame
  with `FindSpriteFrame` (`0x4f30c0`) and blits it **at the cursor anchor
  `(g_cursorAnchorX, g_cursorAnchorY)`** — `BlitSprite16bpp` on the hardware
  path, else `BlitSpriteClipped(g_cursorFrame)` (software). So:
  - **`g_cursorFrame` is effectively a constant 0, *not* an animation index.**
    A byte search shows the address `0x7a7674` occurs **exactly once in the
    whole binary** — the `mov esi,[0x7a7674]` read in `GameTick` — and it lives
    in the zero-initialized data region, so it is **never written and always
    `0`**. The `-1 < g_cursorFrame` test is therefore an always-true
    visibility gate (`-1` would mean "hidden", but nothing ever sets it), and
    `BlitSpriteClipped(g_cursorFrame)` always passes frame `0`. *(This corrects
    an earlier note that read `g_cursorFrame` as a 0…101 animation state — it
    isn't.)*
  - **The draw site.** Disassembling `0x4139c6` shows `FindSpriteFrame` is
    invoked with `eax = &DAT_00ea0e18` (the shared sprite container), `edx = 0`
    (the outer key = **sprite id 0**), and `esi = g_cursorFrame` (the inner
    frame key), and `esi` is passed on to `BlitSpriteClipped`. **Sprite id 0 is
    the cursor** — the last persistent sprite loaded in `InitGame`
    (`LoadSpriteSet(&DAT_00ea0e18, 0)`); the row blitter (`FUN_004eb940`) is a
    plain clipped memcpy.
  - **The cursor animates — a 17-frame loop, confirmed on the live client.** A
    debugger probe (`tools/debug/cursor-probe.sh`, logging at `0x4139dc`) shows
    `g_cursorFrame` **advances `0→1→…→16→0` one step per tick, in lockstep with
    `g_frameCounter`**, and each value resolves a distinct sprite-frame node. So
    the pointer really is a **17-frame animated sprite** (sprite id 0), not the
    static frame 0 an earlier static pass had concluded. *(That earlier
    conclusion was wrong — see next.)*
  - **The writer — `AdvanceSpriteAnimation` (`0x450730`), and why static missed
    it.** The "cursor globals" are actually **fields of one animated-cursor
    object at `0x7a7644`** (a singleton, 19 refs): `g_cursorFrame` is
    **`obj+0x30`**, so the per-tick advance is `mov [eax+0x30], …` — *no
    absolute reference to `0x7a7674`*, which is exactly why byte-search/xref
    found only the read and I wrongly called it "constant". GameTick's update
    loop calls `AdvanceSpriteAnimation(obj=0x7a7644)` **once per elapsed frame**
    (`0x413354`; the function is generic — ~10 other callers animate other
    objects the same way). It's a **keyframe player**:

    | `obj+` | meaning |
    |---|---|
    | `0x1c` | anim descriptor = `FindPreloadedTextureByName("cursor")` (tables at `+8` loop-flag, `+0xc` step-count, `+0x10` step→frame, `+0x14` step-duration) |
    | `0x20` | enabled |
    | `0x24` | current animation/state index |
    | `0x28` | sub-timer (ticks inside the current step) |
    | `0x2c` | current keyframe step |
    | `0x30` | **`g_cursorFrame`** — resolved sprite frame to draw |

    Each tick: `++subTimer`; if it reaches `step_duration[state][step]` advance
    the step; if the step passes `step_count[state]` loop back to 0; then
    `g_cursorFrame = step→frame[state][step]`. With ~17 one-tick steps mapping
    step→frame linearly, that produces the observed `0…16→0` loop.
  - **`g_cursorTexture` (`0x7a7660`) is the cursor's anim descriptor**
    (`obj+0x1c`), *not* write-only — it's read every tick by
    `AdvanceSpriteAnimation` as `[eax+0x1c]`. (My earlier "write-only" was the
    same byte-search artifact: the reads are object-relative, only
    `ChangeGameState`'s store is absolute.) `cursor.img`'s 102 frames are the
    pool the ~17-step animation draws from.
  - **Replay-playback variant:** a separate branch (guarded by the
    `PeekPacketChecksumBool` replay-mode read) **blinks** the cursor — visible
    on a `g_frameCounter % 0x14 < 10` schedule, i.e. **on for 10 of every 20
    frames (~50% duty)**. This blink is the one confirmed time-based cursor
    behaviour in the analyzable code.
- **No custom OS cursor.** The window class registers the **standard
  `IDC_ARROW`** (`LoadCursorA(NULL, MAKEINTRESOURCE(0x7f00))` — the only
  `LoadCursor`/`LoadImage`/`CreateCursor` call in the whole binary). The
  9-entry `g_edgeCursors[9]` array (meant to be per-direction cursors) is
  **never populated** — verified by byte search: every entry (`0x5b1c4c`…
  `0x5b1c6c`) sits in zero-initialized data and is **read but never written**
  anywhere, so all nine are **NULL**. `WndProc`'s `WM_SETCURSOR` therefore does
  `SetCursor(g_edgeCursors[g_cursorDirection])` = **`SetCursor(NULL)`**, which
  *hides* the OS cursor (it doesn't select a custom shape). So the directional-
  HCURSOR design is entirely vestigial; there is **no OS-cursor customization**.
- **In-battle edge-scroll drives the direction.** `State11_InBattle_OnTick` (State 11 slot
  9, per tick) tests the mouse against the 800×600 edges
  (`X > 0x31b` right, `Y < 5` top, `Y > 0x253` bottom, left), computes a
  direction 0–8, and — only when it changes (cached in
  **`g_lastCursorDirection`**) — sets **`g_cursorDirection`** and `SetCursor`s
  `g_edgeCursors[dir]` (which is `NULL`, so effectively a no-op / hide). The
  meaningful output is `g_cursorDirection`, which feeds the 8-directional
  camera scroll.
- **Relative-mouse capture** (`WndProc` mouse-move): when a mode flag
  (`DAT_00e53c3c`) is clear, it reads the movement delta, accumulates it into
  camera/aim globals (`DAT_00e536c0`/`c4`), then `SetCursorPos`-snaps the
  pointer back to a fixed anchor (`g_cursorAnchorX`/`g_cursorAnchorY`) — FPS-style
  relative mouse for camera/aim.
- **Cursor clamping** (`ClampCursorToRect`, `0x4ee200`) confines the pointer to
  a rect, e.g. snapping it onto a modal dialog.

**Resolved:** `ShowCursor(0)` (called once in `WinMain`, restored on exit)
hides the OS cursor for the whole session, and the visible pointer is the
**software-blitted `cursor.img` sprite drawn by `GameTick`** (above). The
`g_edgeCursors` `HCURSOR`s set by `SetCursor` are therefore **not the drawn
pointer** — with the OS cursor hidden they're effectively a *direction latch*:
`g_cursorDirection` (set by the same edge test) is what actually feeds the
8-directional camera scroll, and the `SetCursor` calls are a vestige of an
HCURSOR-based design. (`GetCursorPos` is never called; the pointer position
comes from `WndProc` mouse messages into the `g_cursorAnchorX/d110` anchor.)

## Open threads / good next targets

1. **DONE** — all 16 game states identified and named.
2. **DONE** — `CGameState` base class vtable layout confirmed (dtor, virtual
   `ProcessPacket`, OnEnter, OnExit); three per-state `ProcessPacket` overrides
   found and their opcode spaces mapped (room list, server select, avatar
   store).
3. **Substantially advanced for one state.** Confirmed the "input/update/
   render virtuals" hypothesis directly for state 11 (In-Battle) — dumped
   its full 18-entry vtable and decompiled every previously-unnamed slot:
   slot 5 is a keyboard/chat-input dispatcher, slot 6 dispatches on literal
   Win32 mouse message codes, slots 10/15 are a matched chat-character-
   append/message-finalize pair (with a confirmed control-character
   emoticon-shortcut remap table), slot 13 is a special-weapon-effect
   renderer, slot 9 is a large cursor/update function, and slot 17 is a
   genuine state-specific no-op. See the dedicated "State 11 full vtable
   map" section above. The same technique (find the state's
   `vtable_StateNN_Name` symbol, dump slots, decompile the unnamed ones)
   would work for the other 15 states but wasn't repeated for all of them
   this pass — still a good next target if more per-state input/render
   detail is wanted, now with a proven, fast methodology.
4. **DONE** — states 9 and 11's `ProcessPacket` overrides found, named, and
   mapped. Discovered the client-side **replay-recording system** as a
   byproduct (`.sv` files, typed event log, `QueueBroadcastEvent`/
   `BroadcastQueuedEvent`).
5. **DONE, and further advanced this pass** — found and mapped the second
   virtual channel: `CGameState` vtable slot 2 (`ProcessBattleAction`),
   overridden only by Loading, Ready Room, and In-Battle (every other state
   uses the shared no-op) — strong confirmation this is a real-time/
   P2P-adjacent protocol distinct from `ProcessPacket`. Found a concrete
   cross-state data handoff (Loading writes turn-timer + setup data
   directly into the In-Battle object before it's even active).

   **Socket-level proof, found by tracing `recvfrom` callers forward.**
   There are two, and they're architecturally distinct, not just two
   code paths to the same dispatcher:
   - `FUN_004ff770` — a simple, direct UDP handler: `recvfrom` a datagram,
     validate its embedded length field, decrypt/checksum it (a short
     block-based routine — packet size must be a multiple of 16 past a
     fixed prefix, checked via `(len & 0x8000000f) == 0`), then call
     **`(**(vtable+8))(...)` directly from the network callback** — vtable
     slot 2, i.e. **`ProcessBattleAction`**. Real-time battle actions are
     dispatched synchronously the instant they arrive, no queueing.
   - `FUN_004e6160` — a much larger (1,541-byte), full reliable-UDP peer
     layer: per-slot (0-7) sequence tracking, duplicate-datagram detection
     (comparing the new payload byte-for-byte against the last-received
     buffer for that slot), a summed checksum validation matching the
     style already documented for `.dat`/`.xfs` integrity checks, ack
     sending, and RTT measurement via `timeGetTime()`. On a valid new
     packet it does **not** call any vtable slot itself — it copies the
     payload into a per-slot buffer and calls `FUN_004e8f70`, which turns
     out to be a **queue insert** (append into a ring buffer, stride
     `0x206`), not a dispatch. This confirms Channel 1 (`ProcessPacket`)
     packets are queued on arrival and drained later (almost certainly
     once per `GameTick`, matching the polling architecture already
     documented elsewhere), while Channel 2 (`ProcessBattleAction`)
     bypasses the queue entirely for lower latency — exactly the
     asymmetry you'd want for a turn-based-but-real-time artillery game:
     guaranteed, ordered delivery for room/lobby state, fire-and-forget
     immediacy for in-battle actions. Two more action codes decompiled and
   documented this pass: `0x8104` (shows the end-of-match "confirm result"
   button) and `0x8500` (a player-position/status relay, also independently
   confirmed as a replay-event code logged elsewhere — see
   [PROTOCOL.md](PROTOCOL.md)). **All `0x84xx`/`0xc3xx`/`0xc4xx` action
   codes are now fully accounted for**: re-decompiled `ProcessBattleAction`'s
   actual `switch` statements directly (rather than a plain-text scan, which
   had missed jump-table-based cases) and confirmed `0xc302`/`0xc307`/
   `0xc309`/`0xc402`-`0xc408` **never appear as distinct `case` labels at
   all** — every one of them falls through to the shared default label,
   which is a plain no-op (`return`, no side effects). These codes are
   simply not specially handled by this client build; not an
   investigation gap, a confirmed negative. Also found and documented two
   more real codes this pass that a plain-text scan had missed: `0xc40a`
   (a small per-slot 2-`int` position-ish array write) and upgraded
   `0xc40b`'s writeup from "generic housekeeping" to its actual confirmed
   behavior (a filtered per-player sound-plus-notification broadcast).
   Remaining open item in this channel: the meaning of `+0x10a4`/`+0x2302`
   on the In-Battle object beyond "turn timer" / "8-element setup array."
6. **DONE** — all opcodes across every `ProcessPacket`/`ProcessBattleAction`
   handler mapped; see [PROTOCOL.md](PROTOCOL.md) for the full packet
   reference (this superseded the original opcode-mapping goal here).
7. Five `ChangeGameState` call sites (`0x443350`, `0x443561`, `0x4b9ebe`,
   `0x4e0c68`, `0x4e5421`) are switch/jump fragments *inside* larger functions
   whose auto-analysis was truncated — no standalone prologue nearby. They need
   manual function-boundary repair in the Ghidra GUI. Low priority.
8. Reconstruct concrete structs from confirmed strides. **`RoomPlayerSlot`
   and `InventoryItem` both resolved this pass** — see the dedicated
   sections above. `RoomPlayerSlot` turned out to be a "struct of arrays"
   rather than one packed struct (a 0x80-byte name buffer plus several
   separate same-indexed parallel arrays for stats, plus a count-prefixed
   variable-length equipped-item list); `InventoryItem` is a genuine packed
   0x9c/156-byte struct with a fully-mapped field layout (4 id fields,
   expiration date, variable blob), though the blob's internal contents and
   two of the "unaccounted" 2-byte gaps remain unresolved. **`PlayerGameSlot`
   turned out not to exist as originally framed**: traced actions
   `0x8408`/`0x3020` in full and found the active-battle-slot data is a
   struct-of-arrays (four small 4-byte-per-slot `uint` arrays, not one
   `0x224`-byte struct), and the `0x224`-byte, player-ID-indexed array at
   `+0xebef4` that a previous pass suspected was `PlayerGameSlot` is
   actually an array of **per-player packet-checksum-state** objects
   (confirmed via `PeekPacketChecksumState`, see the packet-checksum
   utility section above) — not gameplay data at all. What remains
   genuinely open: whether a *real* per-player gameplay struct (position,
   HP, weapon, etc.) exists as a single packed struct anywhere, or whether
   GunBound's engine simply always uses this struct-of-arrays style
   (consistent with what was found for both `RoomPlayerSlot` and the
   battle-spawn arrays). Followed up further this pass: the state-7
   8-element array turned out to be a **third, distinct** `0x224`-sized
   thing — a generic minimal container (owned-pointer-plus-flag, ctor/dtor
   `InitGuardSlot`/`ScrubChecksumGuard`), not obviously gameplay data either, and
   reused elsewhere in the engine (same ctor/dtor pair, same stride, seen in
   `FUN_00415d40`'s object-init too) — see the recurring-structures list
   above. The room-list's 20-element loop is **inconclusive**: its `0x224`
   loop-counter increment doesn't match either the checksum-state or the
   generic-container identity, and looks more like it's tracking a wire/
   source buffer's conceptual size than indexing a real struct array (see
   the dedicated note above). Net result after three rounds of digging:
   **no confirmed single packed "PlayerGameSlot" struct exists** — every
   `0x224`-sized thing found so far turned out to be something else
   (checksum state, a generic container, or an unresolved wire-format
   accumulator). This thread is likely exhausted for static analysis
   without a fresh, more targeted lead. Cross-referencing against
   `itemdata.dat`/`characterdata.dat` samples in `orig/` remains blocked on
   the LZHUF decoder bug (see [FILEFORMATS.md](FILEFORMATS.md)).

## Rendering — Direct3D 7 + software hybrid

**Key finding: GunBound is not a plain DirectDraw blitter — it's a hybrid
Direct3D 7 hardware renderer with a software (Lock/write) rasterizer layer.**
This corrects the earlier "DirectDraw Blt" assumption.

### The COM object chain (confirmed via GUID, not just call shape)

`InitDirectDraw` (`0x4efaa0`) builds this chain — vtable method identities
below are now **confirmed**, not inferred, because the `QueryInterface` GUID
argument at `0x5573e8` decodes to
`{F5049E77-4861-11D2-A407-00A0C90629A8}` = **`IID_IDirect3D7`**, which
anchors the whole interface identification:

| Global (renamed) | Interface | Created by |
|---|---|---|
| `g_hDDrawDll` (`0x79363c`) | `HMODULE` for `ddraw.dll` | `LoadLibraryA` |
| `g_pDirectDraw7` (`0x7935f0`) | `IDirectDraw7` | `GetProcAddress("DirectDrawCreateEx")` |
| `g_pDirect3D7` (`0x793600`) | `IDirect3D7` | `g_pDirectDraw7->QueryInterface(IID_IDirect3D7)` |
| `g_pPrimarySurface` (`0x7935f4`) | `IDirectDrawSurface7` (primary, + flip chain in fullscreen) | `CreateSurface` |
| `g_pBackBufferSurface` (`0x7935f8`) | `IDirectDrawSurface7` (back buffer / D3D render target) | `GetAttachedSurface` off the primary |
| `g_pD3DDevice7` (`0x793604`) | `IDirect3DDevice7` | `g_pDirect3D7->CreateDevice(guid, backBuffer, &device)` |
| `g_pClipper` (`0x6790b8`) | `IDirectDrawClipper` | `CreateClipper` (windowed present) |

`ShutdownDirectDraw` (`0x4eff90`, was `FUN_004eff90`) `Release`s all six COM
objects (vtable `+8`) then `FreeLibrary(g_hDDrawDll)` — this teardown function
is what let the whole chain be identified together.

The device's `IDirect3DDevice7` vtable is used throughout with textbook
offsets (all now confirmed against the standard vtable): `+0x10`
EnumTextureFormats (the callback `EnumTextureFormatsCallback`/`0x4ef8e0` that
was *wrongly* guessed as DirectInput last pass), `+0x14` BeginScene, `+0x18`
EndScene, `+0x20` SetRenderTarget, `+0x28` Clear (called as
`Clear(0,0,TARGET|ZBUFFER, color, z=1.0f, 0)`), `+0x34` SetViewport, `+0x50`
SetRenderState, `+0x64` DrawPrimitive, `+0x8c` SetTexture, `+0x94`
SetTextureStageState. `InitDirectDraw`'s tail sets up **alpha blending**:
`SetRenderState(SRCBLEND=SRCALPHA)`, `SetRenderState(DESTBLEND=INVSRCALPHA)`,
`SetRenderState(ALPHABLENDENABLE=1)` — i.e. sprites are drawn as alpha-blended
textured quads on the GPU.

**`State11_InBattle_Render` (`0x4c3020`, was `FUN_004c3020`) switches to
additive blending for effect textures.** This 22.5 KB function is the main
In-Battle render pass; scanning every `SetRenderState` call site in it
(vtable `+0x50`) shows two distinct blend-state pairs, both using
`SRCBLEND=SRCALPHA(5)` but differing in `DESTBLEND`:
- `DESTBLEND=INVSRCALPHA(6)` — the standard pair, used for ordinary sprites.
- `DESTBLEND=D3DBLEND_ONE(2)` — used at call sites that immediately follow a
  `Lock` (vtable `+0x64`) on a named effect texture: confirmed against the
  strings `CharEffectTexture1`, `LaserEffect`, and `AvataEffectTexture1`.
  `SRCALPHA`/`ONE` is the standard **additive-glow** formula
  (`final = srcAlpha*src + dest`, no darkening from the destination term),
  used for character glow, laser beams, and avatar special effects. Each
  site guards the `SetRenderState` calls behind a cached-state check
  (`CMP [0x793614/0x792194], <5 or 2>` then `JZ` skip) so the device isn't
  redundantly reprogrammed every frame the same blend mode stays active —
  those two globals are simply the last-set SRCBLEND/DESTBLEND cache, not
  meaningfully different per-effect values beyond the 5/6 vs 5/2 split.

**`InitDirectDraw`'s full call sequence, traced end to end this pass**:
`LoadLibraryA("ddraw.dll")` → `DirectDrawCreateEx` → `SetCooperativeLevel`
(fullscreen exclusive `DAT_00588f4c!=0`, or normal windowed) →
`SetDisplayMode(800,600,...)` (fullscreen only) → `CreateSurface` (primary +
flip chain fullscreen, or a single windowed surface) → `GetAttachedSurface`
(back buffer, fullscreen) or a second `CreateSurface` (windowed) →
`CreateClipper` + `Clipper->SetHWnd` + `Surface->SetClipper` (windowed) →
`QueryInterface(IID_IDirect3D7)` → `CreateDevice` (`g_pD3DDevice7`) →
`SetViewport` → `EnumTextureFormats(EnumTextureFormatsCallback)` →
`GetAvailableVidMem` → **`InitTextureCachePool`** (`0x4f3e40`) +
**`InitSpriteRegistryPool`** (`0x4f3a00`) — two pooled bump-allocator tables
zeroed and given their first block (128-byte elements via
`AllocTextureCacheNode`/`0x4f3dc0`, and 12-byte elements via
`AllocSpriteRegistryNode`/`0x4f3980` respectively; the 12-byte size matches
this codebase's small AVL-tree-node pattern, though the exact consumers of
both pools weren't confirmed via caller-graph — several call sites elsewhere
in this codebase are reached through a register-based calling convention the
decompiler doesn't surface) → texture-stage filter states (`SetTextureStageState`
×10, min/mag/mip filtering + texture-coordinate wrap modes) → `OpenXFSArchive`
(the startup graphics archive) → zero a third, larger `0x1000`-dword region
and set its screen-dimension fields (800×600) → **`SetupZBuffer`** (`0x4ef9a0`).

Fullscreen vs. windowed still branches on `DAT_00588f4c` (fullscreen =
hardcoded 800×600 exclusive; windowed = `GetClientRect`/`ClientToScreen`).

### Frame presentation (`PresentFrame`, `0x4f0070`)

Called once at the end of every `GameTick`. Confirmed:
`g_pPrimarySurface->SetClipper(g_pClipper)` then
`g_pPrimarySurface->Blt(&destRect, g_pBackBufferSurface, NULL, DDBLT_WAIT, NULL)`
— a **clipped Blt of the back buffer onto the primary** (windowed-mode
present). On `DDERR_SURFACELOST` (`0x887601C2`, matched exactly in the code)
it `Restore`s all three surfaces and re-`SetRenderTarget`s the device.

### The software rasterizer layer (hybrid rendering)

Alongside the D3D device, the game **locks the back buffer and writes pixels
directly** for a large class of content:

- **`LockBackBuffer`** (`0x4f02c0`, was `FUN_004f02c0`):
  `g_pBackBufferSurface->Lock(NULL, &ddsd, 0, 0)`, returns the surface
  **pitch** and **pixel pointer**. Paired with an `Unlock` (surface `+0x80`)
  at the end of each render layer in `GameTick`.
- **`BlitRLESprite`** (`0x4eb450`, was `FUN_004eb450`): **re-identified —
  not the `.img` sprite decoder.** Decompiled in full: it's a
  byte-oriented, table-lookup-driven renderer (a control byte's high bit
  selects between two fixed-size draw commands, indexing a lookup table
  at `&DAT_005b3628`), structurally nothing like a flat pixel/scanline
  format. Much more consistent with a **terrain/map tile renderer** —
  correcting an assumption ("this decodes `.img` sprites") carried since
  early in this project purely from its name resembling "RLE."
  **Fully decompiled its two draw commands this pass, which resolves what
  it actually renders**: each command (`FUN_004eafa0` for the plain
  6-byte-stride case, `FUN_004eaeb0` for the indexed 12-byte-stride case)
  is a **12-row, 12-bit-wide monochrome stencil blitter** — it walks a
  packed 1-bpp bitmap mask (12 rows × 12 bits, `FUN_004eaeb0`'s rows split
  across two bytes: high 7 bits of the first byte, low 4 bits used from
  the second) and, for every set bit, writes a single flat 16-bit color
  value (passed in as `param_2`/`param_3`) directly into the locked back
  buffer at `DAT_0079352c + (y * DAT_005b3620 + x) * 2` (pixel buffer base
  + `y*pitch+x`, both filled in from `LockBackBuffer`'s out-params by the
  caller). `&DAT_005b3628`'s 24-byte-stride records are therefore a
  **library of 12×12 stencil patterns**, each addressable by a 15-bit
  index (`(controlByte & 0x7f) << 8 | nextByte`) — i.e. a lookup table of
  shapes stamped in a solid color, not a table of sub-images. This is
  consistent with GunBound's destructible-terrain mechanic: an explosion
  crater (or any irregular soft-edged terrain shape) is drawn as a solid
  color through a pre-authored stencil mask rather than as a real sprite
  with its own pixel data — cheap to rasterize and easy to erase/redraw
  per-hit. The plain (non-indexed, `FUN_004eafa0`) command uses the same
  12×8 stencil approach but reads the mask directly from the tile stream
  instead of a table, likely for simpler/no-lookup fill shapes.

  **Re-characterization: `BlitRLESprite` is actually the bitmap-font text
  renderer, not primarily a terrain renderer.** Checking every caller
  (`getReferencesTo` on `0x4eb450`) turns up dozens of sites across nearly
  every UI/state-machine function in the binary, not just `GameTick`'s
  terrain layer — including `State03_GameRoomList_RenderRoomLabel`
  (`0x429810`), which `sprintf`s a formatted string (e.g. player name +
  checksum-state values) into a stack buffer and then calls
  `BlitRLESprite(x, color)` immediately after. The call-site disassembly
  confirms the implicit stream-pointer register is loaded via
  `LEA EAX,[ESP+0x30]` — the address of that same `sprintf` buffer. So
  `BlitRLESprite`'s "control byte" stream, for text calls, **is the ASCII
  (or DBCS/EUC-KR, given the high-bit-set path consumes two stream bytes —
  consistent with Korean text) string itself**, and `&DAT_005b3628`'s
  12×12 stencil table is functioning as a **bitmap font glyph table**
  indexed by character code, not (or not only) a terrain-crater shape
  library. The most accurate characterization: `BlitRLESprite` is a
  generic "stamp a solid color through a table of 12×12 monochrome
  stencils, selected byte-by-byte from an input stream" primitive, reused
  by the UI layer for text rendering and by the terrain layer (its
  original `GameTick` callers, still uncontradicted) for crater/damage
  decals — both are just different streams sharing the same glyph/stencil
  table.

  **Follow-up: the single-byte vs. two-byte codepoint indexing is now
  fully resolved from raw disassembly of `BlitRLESprite` itself** (not
  relying on the decompiler's register-attribution, which was unreliable
  for this hand-tuned calling convention). There are **two separate glyph
  tables**, not one shared table:
  - High-bit-set (two-byte/DBCS, likely EUC-KR Korean) control bytes index
    `&DAT_005b3628`, stride **24 bytes** (`(controlByte & 0x7f) << 8 |
    nextByte`, then `* 24`) — each entry is **12 rows × 12 bits**, packed
    2 bytes/row, drawn by `FUN_004eaeb0`.
  - Plain (high-bit-clear, single-byte ASCII/Latin, excluding `0x20`
    space) control bytes index a **different table at `0x673628`**,
    stride **12 bytes** (`asciiCode * 12`, direct linear index — no bit
    manipulation, since the whole 7-bit ASCII code fits) — each entry is
    **12 rows × 8 bits**, 1 byte/row, drawn by `FUN_004eafa0`. The color
    to stamp is threaded through as a fixed value from `BlitRLESprite`'s
    own color argument (confirmed: the same 16-bit color forwarded
    unchanged into every row-write in both helpers) — i.e. **flat,
    single-color bitmap-font glyphs**, no anti-aliasing.

  Both tables read as **all-zero** in the static binary — same
  "initialized=true but zero-filled" pattern already found for
  `g_spriteVertexBuffer` — confirming they are **runtime-populated glyph
  caches** (loaded from a font/bitmap resource at startup, not compiled-in
  literal data), rather than something bakeable/dumpable directly from
  the `.gme` file.

  This also revises the earlier "terrain crater" hypothesis: since
  `BlitRLESprite` is a single shared code path used identically regardless
  of caller — every caller's byte stream is interpreted the same way,
  through the same two glyph tables — the `GameTick`-side callers found
  earlier are much more likely drawing **text/number overlays onto the
  battlefield** (e.g. damage numbers, player name labels rendered over
  the terrain layer during the software-blit pass) rather than terrain
  deformation/crater graphics specifically. There's no separate
  "terrain-shape" table distinct from the font tables — it's the same
  bitmap-font renderer used everywhere text needs to be drawn, in menus
  and in the battle HUD alike. The original "terrain tile renderer" guess
  for this function should be considered superseded, not just extended.
- **`BlitSprite16bpp`** (`0x4ed6a0`, was `FUN_004ed6a0`): the function
  actually relevant to `.img` sprites. Operates on `unsigned short*`
  pixels → the surfaces are **16-bit color**, confirmed as **ARGB4444**
  (4 bits each alpha/red/green/blue) — reached after two rejected guesses
  (RGB565, then RGB555) by extracting real `.img` sprites and comparing
  decoded colors against a reference screenshot of the mobile-select
  screen; the correct format was confirmed by noticing every common
  decoded pixel value's top hex digit was `0xf` (the alpha nibble reading
  fully opaque, not a coincidental red-channel pattern). Internally, this
  function implements a **sparse per-scanline run-length format** (each
  row: `[stride][run_count]` then `run_count` spans of
  `[x_offset][length][pixels]`), not a flat pixel array — see
  [FILEFORMATS.md](FILEFORMATS.md)'s `.img` section and
  `tools/lzhuf/decode_img.py` for the full writeup and extraction tooling.
- **`BlitSpriteClipped`** (`0x4eb9c0`, was `FUN_004eb9c0`): clips against the
  active clip rect (`DAT_00793534`/`DAT_0056df34`) before blitting.

**The software-blitter primitive set** (all write `unsigned short` pixels to
`DAT_0079352c + (y*DAT_005b3620 + x)*2` and honour the clip rect):
- **`SetClipRect`** (`0x4eadb0`) — clamps and stores the clip rectangle
  (`DAT_00793530`/`0056df30` = left/right, `DAT_00793534`/`0056df34` = top/bottom;
  bounded to 800×600).
- **`FillPixels16`** (`0x4f26f0`) — the word-aligned 16bpp run fill (a `memset`
  for `u16`); **`DrawHLine`** (`0x4eb5d0`), **`DrawVLine`** (`0x4eb6b0`), and
  **`FillRect`** (`0x4eb800`, row-by-row) are the clipped single-colour
  primitives built on it.
- **`DrawSprite`** (`0x4eb890`) — the canonical "resolve frame via
  `FindSpriteFrame`, then pick `BlitSprite16bpp` (direct, flag `+0x18==1`) vs
  `BlitSpriteClipped`" dispatch; this exact `if`-chain is inlined all over the
  render slots.
- **Bitmap font**: **`DrawFontString`** (`0x4eb510`) walks a string and emits each
  glyph via **`DrawNarrowGlyph`** (`0x4eb290`, 6px ASCII / half-width) or
  **`DrawWideGlyph`** (`0x4eb020`, 14px full-width / Hangul, selected on the
  high bit). Both glyph drawers synthesise a 1px outline from the bitmap
  (`b>>2 | b | neighbor>>1`) and plot with the fg colour. This is distinct from
  `BlitSpriteText` (`0x4ed9f0`), which renders numbers/labels from *sprite*
  glyphs rather than the vector font.

### The span-based HUD compositor

**High confidence, fully traced.** Separate from the direct-blit primitives
above, a handful of HUD elements — currently confirmed: the in-battle wind
gauge (`DrawWindGauge`) and the two-layer stage-decoration parallax object
(`DrawStageDecorationBase`/`DrawStageDecorationParallax`, see
`LoadStageDecorationSet`), both driven from `RenderWindGaugeTick` (In-Battle
`OnTick` vtable slot 11) — are drawn through a **deferred, z-ordered span
compositor** instead of blitting straight to the back buffer:

- **`QueueCompositorSpan`** (`0x4e9130`) — inserts a horizontal pixel span
  into a per-scanline interval list (16-byte nodes: `x0, x1, priority-tag byte,
  next ptr, data ptr`) allocated from pooled `0x4000`-byte blocks, splitting/
  merging existing spans on that row as needed. This is the low-level insert;
  it never touches the real back buffer.
- **`QueueSpriteFrameSpans`** (`0x4ed870`) and **`QueueTextureRegionSpans`**
  (`0x4ebaf0`, row-by-row via **`QueueTextureRowSpan`** `0x4eba80`) are the two
  sprite-draw paths that feed spans into the compositor — the RLE-frame vs
  cached-atlas-region split mirrors `BlitSprite16bpp`/`BlitSpriteClipped`, but
  routed through `QueueCompositorSpan` instead of writing pixels directly.
- **`QueueSpriteSpansByContentId`** (`0x4eb8e0`) — looks up a sprite/texture
  by a two-level content-id tree key and dispatches to whichever of the two
  span-queuing paths applies (same `frame->+0x18==1` flag as `DrawSprite`).
- **`g_nCompositorLayer`** (`0x0f2465c`) — the active priority/z-tag; draw
  callers set it (values `1`/`2`/`3` seen) before queuing spans for that layer.
- **`FlushCompositorLayer(tag)`** (`0x4e93e0`) — walks every row's span list,
  copies only the spans matching `tag` into the real back buffer
  (`DAT_0079352c`), and marks each row's queue for that tag consumed.

**Why this exists (inferred, not confirmed):** both confirmed users draw
several overlapping pieces at (near-)the same screen position every frame —
the wind gauge's rotating vane + multi-digit number, and the stage
decoration's base + parallax-offset layers; queuing spans and flushing once
per priority tag avoids redundant overdraw/z-fighting between the pieces
compared to blitting each one directly. `g_nCompositorLayer` values seen are
`1`/`2` (stage decoration parallax/base) and `3` (wind gauge) — matching one
tag per composited element. Whether any other HUD element uses this
compositor is not yet checked.

**Stage decoration / parallax layer** (`LoadStageDecorationSet`, `0x4e3d60`):
a per-stage active-object (type key `60000`/`0xea60`) holding a named,
multi-frame sprite set (frames `"%s%d.img"`, loaded via `LoadSpriteSet`),
sized to the loaded background image's dimensions. Called from
`State10_Loading_PreloadAssets` (stage load) and `ProcessBattleFrame`. Two
sub-pieces are drawn from it each tick, gated on a per-difficulty/stage flag
(`DAT_005f2f55`):
- `DrawStageDecorationBase` (`0x4e3bd0`) — sub-object 0, offset directly by
  `(400-g_nCameraX, 0x12a-g_nCameraY)` (the same half-screen bias the main
  battle-scene camera transform uses).
- `DrawStageDecorationParallax` (`0x4e3aa0`) — sub-object 1, offset by a
  perspective-divide term `-((objX-800)*(g_nCameraX-400))/(g_nCameraBoundX-800)`
  — a genuine parallax formula, so this piece scrolls at a different rate than
  the base layer as the camera pans.

So the pipeline per frame is roughly: `Clear` (D3D) → Lock back buffer →
software-blit map/terrain/UI sprites (RLE, 16bpp) → Unlock → `BeginScene` /
draw hardware sprite quads / `EndScene` (D3D) → `PresentFrame` (Blt to
primary). The `GameTick` present loop runs at a fixed ~50 ms cadence with a
`Sleep`-based frame cap.

### Texture/asset system

Two distinct, confirmed lookup mechanisms:

- **`FindPreloadedTextureByName`** (`0x4017d0`): linear scan through a
  **fixed-size, pre-populated table** (case-insensitive `stricmp`, 24-byte
  records), returns null on miss with **no disk-load fallback**. This is why
  the Loading screen is its own game state: **`State10_Loading_PreloadAssets`**
  (`0x43f0e0`, 12,346 bytes) loads every character/weapon/effect texture
  (`tank1.img`, `bullet1n.img`, `flame11.img`, … hundreds of filenames) into
  this table up front, so **no texture load happens mid-battle**.
- **`FindTextureCacheEntryByName`** (`0x4f4650`): a string-keyed chain lookup
  (root at `+0x1b4`, `next` at `+0x98`), used by `State11_InBattle_Render` to
  resolve a sprite-effect name to a cache entry, then write computed sprite-
  sheet UV coordinates into it (`+0x80`/`+0x84`/`+0x88`) before drawing.

### Text localization

Every visible UI string — dialog titles/bodies, error popups, the
`MessageBoxA` prompts — is **data, not code**: the client ships no
hard-coded English/Portuguese text. Two functions make up the subsystem,
both keyed on numeric ids:

- **`LoadLocalizedStrings`** (`0x43da00`, was `FUN_0043da00`): the loader,
  called once from `InitGame`. It opens `graphics.xfs`, `FindXFSEntry`s the
  **`Language.txt`** entry (a plain text file *inside* the archive, not on
  disk — see [FILEFORMATS.md](FILEFORMATS.md)), reads it a byte at a time
  with `ReadXFSEntryByte`, and parses its `"<id>\t<message>\r\n"` lines into
  the **`g_localizedStringTable`** (`0x796eec`, was `DAT_00796eec`)
  id→string map. A `\n` within a message is a literal line break, so a
  multi-line error (title sentence, blank line, detail paragraph) is a
  single table entry.
- **`GetLocalizedString`** (`0x43dc70`): the reader. Every UI text site
  calls `GetLocalizedString(&g_localizedStringTable, id)` to resolve a
  string by id. (`DAT_005b1444` in its body is the ATL allocator vtable
  used to marshal the returned string object — *not* the string table.)
  It's a **real, documented Microsoft ATL library object**
  (`ATL::CAtlStringMgr`/`IAtlStringMgr`, VS2003 headers — confirmed via
  Ghidra's own function-signature matching on
  `src/unnamed/msvc_crt_atl/FUN_00520037.c`/`FUN_0052009c.c` against the
  real library), not game-specific code. When the id lookup misses (e.g.
  in the bring-up build, where `LoadLocalizedStrings` is skipped and the
  table is always empty), `GetLocalizedString` falls back to ATL's shared
  "nil string" singleton via the vtable's `GetNilString()` slot — a
  faithful reconstruction of that vtable + singleton lives in
  `src/cxx/crt_shims_msvc.c`'s `gb_init_atl_string_mgr` (MSVC-syntax-check
  build only; see that file's header for why `state`/`this` can be
  ignored in the reconstruction).

**How ids are chosen.** Error dialogs go through the shared
`ShowErrorDialog(closeSockets)`, which maps a per-screen error/reason code
to a message id via **`id = code + 0xc7`** (the error-dialog family starts
at id 199) and word-wraps the resolved string into the `error_back.img`
popup. Other prompts pass an id directly — e.g. the Avatar Store purchase
dialog resolves `GetLocalizedString(&g_localizedStringTable, 0xea6a..0xea6d)`,
and the packet pump surfaces some server error codes via a native
`MessageBoxA` from the same table.

**Locale = which `Language.txt` is packed.** The runtime language is
determined entirely by the `Language.txt` shipped in that server's
`graphics.xfs`; the code is locale-agnostic. The `orig/graphics.xfs` in this
repo is the **English** build (jglim/gunbound-launcher `TestClient`, whose
`GunBound.gme` is identical to our target), whose error-dialog family reads, at
the confirmed ids:

| id | code | message (verbatim) |
|---|---|---|
| 200 | 1 | Server Access Error — Can't access to server you required. |
| 201 | 2 | **Access time has expired.** — network/timeout; the connection will close automatically |
| 205 | 6 | Login Error — Wrong password. |
| 215 | 16 | Game Room Blocked — The room is in playing. You cannot enter. |
| 220 | 21 | Version Error — Different version. Connection closed. |

The **full table is extracted and documented** in
[docs/localized-strings.md](docs/localized-strings.md): all **48 defined ids
(200–247)**, verbatim English, pulled from `orig/graphics.xfs`'s `Language.txt`
and **checksum-verified** (`0x4441cd69`). A key finding from that extraction:
this build's table is **sparse — only the error/message-dialog family (200–247)
is defined**; every other id the code requests (loading, HUD, replay,
avatar-store, …) is *not present* in the shipped asset (those UI elements are
image-driven), and id 247 is truncated. A different-language server ships a
different `Language.txt` with the same ids (the previous Portuguese/Brazilian
build defined ids 200–240).

**Who calls it, and the id-block map.** `GetLocalizedString` is one of the
most-called functions in the client: **~256 call sites across 46 functions**
(`LoadLocalizedStrings`, by contrast, is called exactly once, from
`InitGame`). Almost every site passes a **literal** id, and the ids turn out
to be **partitioned into contiguous per-feature blocks** — each screen/
subsystem owns a numeric range, so the table is effectively a set of
per-feature string arrays addressed by a base id. (Round-decimal arguments in
the raw ports — `800`, `20000`, `30000`, `60000` — are just block-start ids
written in decimal: `0x320`, `0x4e20`, `0x7530`, `0xea60`.) The block owners,
from the call sites:

| Id range | Caller(s) | What the block is (semantics inferred from caller) |
|---|---|---|
| `code + 0xc7` (computed, ~199–260) | `ShowErrorDialog` / `ShowErrorDialogFmt` | the error-dialog family (confirmed; the only major *computed*-id site) |
| `0x12d`–`0x142`, `0x7530`–`0x753b` | `WinMain` | startup / window-title / version-&-update messages (also several `MessageBoxA` prompts) |
| `0x19a`–`0x19e` | `ProcessIncomingPackets` | server packet status / error notifications |
| `0x25c`–`0x274` | `State11_InBattle_ProcessBattleAction`, `State11_InBattle_OnTick` (State11 slot 9) | in-battle event / status messages |
| `0x27c`–`0x280`, `0x33e`–`0x340` | `State11_InBattle_RenderHud` (State11 slot 15 — the HUD/chat renderer) | HUD / scoreboard labels |
| `0x320`–`0x32f` | `State10_Loading_OnEnter` | loading-screen labels (16 contiguous) |
| `0x4e20`–`0x4e23` | `State03_GameRoomList_RenderRoomLabel` | room-list column headers |
| `0x1770`–`0x177f` | `WriteReplayEventRecord` | replay event-type descriptions (16 contiguous, one per event kind) |
| `0x2c3`–`0x2cb`, `0xea60`–`0xea69` | `FUN_00445450` (unnamed avatar-store UI builder) | avatar-store labels |
| `0xea6a`–`0xea6d`, `0xfa8` | `State07_AvatarStore_ProcessPacket` | avatar-store purchase-dialog strings (confirmed) |

A handful of sites pass a **computed/variable** id (`uVar…`, `iVar + N`)
rather than a literal — the error family (`code + 0xc7`) is the main one; the
rest are small per-caller offsets into the block above them. The takeaway for
a reimplementation: the localization table is not an opaque bag of strings but
a **block-addressed layout**, so a port can keep the same id scheme and load
the same `Language.txt` verbatim.

### The sprite keyframe-animation player (`AdvanceSpriteAnimation`)

A **generic per-object keyframe animator** drives most animated sprites in the
game — mobiles, effects, UI, and the software cursor. `AdvanceSpriteAnimation`
(`0x450730`, was `FUN_00450730`) advances one animation-player object per call
and is invoked **once per elapsed frame** from GameTick's update loop (and from
~10 other sites, each animating a different object). The cursor is the singleton
instance at `0x7a7644` (its `+0x30` output is `g_cursorFrame`).

**The player object** (fields relative to the object pointer, passed in EAX):

| off | field |
|---|---|
| `+0x1c` | **anim descriptor** pointer (nullable → no-op) |
| `+0x20` | enabled byte (0 → no-op) |
| `+0x24` | **current animation index** (the "state"; `< 0` → no-op) |
| `+0x28` | sub-timer — ticks elapsed within the current step |
| `+0x2c` | current keyframe **step** |
| `+0x30` | **output: the resolved sprite frame** to draw |
| `+0x34` | "finished" flag (set when a non-looping anim ends, or on reset) |

**The descriptor** is a shared, per-sprite set of parallel tables, each indexed
by the animation index (`state`), then by step:

| off | table |
|---|---|
| `+0x08` | loop flags — `byte[state]`: `0` = play-once/stop, nonzero = loop |
| `+0x0c` | step counts — `int[state]` |
| `+0x10` | step→frame — `int*[state]`, `[step]` = the sprite frame to draw |
| `+0x14` | step durations — `int*[state]`, `[step]` = ticks that step is held |

**Per tick** (when enabled, descriptor present, `state ≥ 0`): if the descriptor
isn't ready (`*descriptor == 0`) it resets (step/timer/frame = 0, finished = 1);
otherwise it `++`s the sub-timer, and when the timer reaches
`duration[state][step]` it advances the step and clears the timer. When the step
passes `stepCount[state]` it **loops** (step = 0) if `loop[state]` is set, else
**stops** on the last step and sets the finished flag. Finally it writes
`frame[state][step]` into `+0x30`. For the cursor that's a ~17-step,
one-tick-per-step looping animation → the `0…16→0` cycle observed on the live
client (see "The custom cursor system"). Confirmed by decompilation + a
debugger probe.

### Sprite-sheet frame selection

Seen dozens of times in `State11_InBattle_Render`:
```
entry->u = (frameIndex & mask) * cellSize;
entry->v = (frameIndex >> shift) * cellSize;
```
Standard sprite-sheet/atlas animation — sub-rect from a frame index. Grid
sizes seen: 2×N (`&1`), 3×3 (`%3`/`/3`), 4×N (`&3`/`>>2`), 8×N (`&7`).

### Turret/sprite rotation → hardware vertex pipeline (now connected end to end)

`g_sineTable360` (`0x54c240`) — 360-entry precomputed sine table indexed by
`angle % 360` (cosine via `(angle+90) % 360`) — feeds **`BuildRotatedSpriteQuad`**
(`0x4ebbc0`, was `FUN_004ebbc0`), which computes a rotated sprite's 4 corner
positions via `x' = x + sin(a)*A + cos(a)*B` and writes a **27-dword (108-byte)
"vertex work record"** — 4 rotated corners plus color/alpha fields — into
**`g_spriteVertexBuffer`** (`0x6ba190`) at index **`g_spriteVertexCount`**
(`0x793658`, an incrementing per-frame sprite counter, stride `0x1b` dwords).

This buffer is exactly what `IDirect3DDevice7::DrawPrimitive` consumes later
in the same frame:
```
DrawPrimitive(device, D3DPT_TRIANGLELIST /*4*/, FVF=0x244,
              &g_spriteVertexBuffer[...], vertexCount, flags)
```
confirmed via raw disassembly of the call site (the decompiler couldn't
recover these arguments — Ghidra showed empty parens — so this required
reading x86 `PUSH`/`CALL` sequences directly). This closes the loop: rotation
math → vertex buffer → GPU draw call, all inside `State11_InBattle_Render`.

**Per-vertex field layout — now fully decoded.** `FVF = 0x244` breaks down as
`D3DFVF_XYZRHW (0x004) | D3DFVF_DIFFUSE (0x040) | D3DFVF_TEX2 (0x200)` — i.e.
each vertex is **pre-transformed screen-space** (no full 3D transform,
consistent with 2D sprite quads) with one diffuse color and two UV pairs:
`[X, Y, Z, RHW, Diffuse, U0, V0, U1, V1]`, 9 dwords = 36 bytes. That means
the "108-byte work record" is actually **3 of these 36-byte vertices**, i.e.
one full triangle — and `BuildRotatedSpriteQuad` writes *two* 108-byte
records per call (confirmed: `g_spriteVertexCount += 2` at the end), which
is exactly a quad expressed as 2 triangles sharing a diagonal:
**triangle 1 = corners (A, B, C), triangle 2 = (C, D, A)**. Traced by mapping
every write in the function to its byte offset within the scratch staging
area (`0x00ea0e28`) before the two block-copies into `g_spriteVertexBuffer`
and `g_spriteVertexBuffer + 0x6c` (the two triangle slots), then confirming
the copy source/destination ranges overlap exactly where the shared C/A
vertices are reused.

Per call, only **X, Y, Diffuse, U0, V0** are written fresh for each of the 4
corners — `Z`, `RHW`, and the second UV pair (`U1`, `V1`) are never touched
by this function or any of the other 20 vertex-constructor functions
checked for the Z-buffer sweep (see below). **Confirmed, not just
guessed**: `g_spriteVertexBuffer` is a statically-allocated global (not
heap-allocated — checking its symbol found no `operator_new` call sized
for it anywhere), living in an *initialized* PE section whose actual
bytes are all zero. Combined with no per-call writes anywhere, this means
`Z`, `RHW`, `U1`, and `V1` are **literally always `0.0`** for every
sprite — correcting an earlier guess that `RHW` was "almost certainly 1",
the conventional value for a pre-transformed D3D vertex. Whether the D3D7
HAL/driver actually needs `RHW` to be `1.0` and silently tolerates `0`
here, or whether `0` is genuinely fine for this rendering path, isn't
something static analysis can settle — but the *value* itself is now
confirmed rather than assumed. `Diffuse`
is set to `0xffffffff` (opaque white) for all 4 corners on every call — no
per-sprite tint, so alpha blending is driven entirely by the texture's own
alpha channel. `U0`/`V0` come from a small per-call texture-rect struct at
`param_1+0x80`/`+0x84`/`+0x88`, and the function's 4th parameter acts as a
**horizontal-flip selector** — it swaps which struct field maps to which
screen corner, which is how a sprite gets mirrored for the opposite facing
direction without a second texture.

**The flush/present call site, fully confirmed** (`FlushSpriteBatch`, was
`FlushSpriteBatch`, 64 bytes): called once `g_spriteVertexCount != 0`, it issues
exactly `DrawPrimitive(g_pD3DDevice7, 4 /*D3DPT_TRIANGLELIST*/, 0x244,
&g_spriteVertexBuffer, g_spriteVertexCount*3, 1)` — the `*3` converts the
triangle-slot counter into a real vertex count, batching every sprite quad
queued that frame into a single draw call — then resets
`g_spriteVertexCount` to 0. It also accumulates a running counter
(`g_frameTriangleCounter += g_spriteVertexCount`), likely an internal perf/stats
counter for triangles drawn.

**Additive blending for effect textures is a general convention, not a
State11-specific one — cross-validated in `State09_ReadyRoom_RenderCharacterPreview`
(`0x4d90c0`).** This function (the character/avatar preview shown before a
battle starts) turned out to have its `SetRenderState`/`SetTexture`
arguments fully resolved by the decompiler (no raw disassembly needed,
unlike the State11 case) — and shows the exact same pattern found there:
normal sprite layers use the default `SRCALPHA`/`INVSRCALPHA` blend, but
right before compositing `AvataEffectTexture1`/`AvataEffectTexture2`, it
explicitly sets `SetRenderState(DESTBLEND, D3DBLEND_ONE /*2*/)` (guarded by
the same `g_currentBlendMode != 2` cached-state check seen in the battle
renderer). This independently confirms the additive-glow convention for
avatar/character effect textures applies across render functions, not just
the one investigated originally.

It also uses a **second, sibling vertex-quad builder, `BuildScaledSpriteQuad`**,
distinct from `BuildRotatedSpriteQuad` (`FUN_004ec430`): same rotated-quad
math and the same `g_sineTable360` lookup and scratch-vertex staging area
(`0x00ea0e28`), but with **independent X/Y scale constants**
(`_DAT_00557ff0`/`_DAT_0055800c`/`_DAT_00558008`/`_DAT_00558004`, 4 distinct
globals) where `BuildRotatedSpriteQuad` uses only 2 (uniform scale). Likely
exists to support the Ready Room preview's zoomed/non-1:1 avatar display,
whereas in-battle sprites are always drawn at native scale.

### The quad-emitter family and the in-battle scene composer

`BuildRotatedSpriteQuad` and `BuildScaledSpriteQuad` are two of a **family of ~7
quad-emitters** — small functions that all stage 4 corners into the same
scratch area (`0x00ea0e28`) and append two triangles to `g_spriteVertexBuffer`
(`g_spriteVertexCount += 2`), then get batch-flushed by `FlushSpriteBatch`. They
differ only in the transform they apply:
| Emitter | Sig (partial) | Distinction |
|---|---|---|
| `BuildRotatedSpriteQuad` (`0x4ec430`) | `(x, y, angle, flip, color)` | rotated, uniform scale — the standard in-battle sprite |
| `BuildScaledSpriteQuad` | `(x, y, angle, flip, scale, color)` | rotated, **independent X/Y scale** (Ready Room zoomed preview) |
| `BuildSizedSpriteQuad` | `(x, y, flip, w, h, color)` | rotated to an explicit w×h |
| `FUN_004ed300` / `FUN_004ed0c0` | larger | rotated variants with extra params (offset/pivot) |
| `FUN_004ecee0` | `(x, y, color)` | rotated, minimal params |
| **`BuildSpriteQuad`** | `(x, y)` | **axis-aligned — no `g_sineTable360` use at all**, the unrotated fast path |

All share the confirmed vertex format (`FVF 0x244`, 36-byte XYZRHW/DIFFUSE/TEX2
vertices, diffuse = opaque white, texture UVs from a `+0x80` rect) and route
into the one batched `DrawPrimitive`.

**`State11_InBattle_Render`** (slot 14, `0x4c3020`, **22.5 KB / ~2250 decompiled
lines**) is the scene composer that drives them. It is now mapped in full — the
overall shape, the per-layer order, and the two subsystems that make it big (a
blend-state cache and the anti-cheat value guard).

**Per-layer render pattern.** The body is ~20 near-identical phases, one per
drawable layer, each following the same five steps:

1. **Set blend mode if it changed** (see the blend-state cache below).
2. `FindTextureCacheEntryByName(name)` → a texture-cache entry, or 0.
3. **Instance loop**: for each object on this layer, cull it against the screen
   clip rect; if visible, write the atlas UV into the cache entry (`+0x80` = U,
   `+0x84` = V) and a Z/scale word (`+0x88`), then call the appropriate
   quad-emitter to append its triangles to `g_spriteVertexBuffer`.
4. `SetTexture(0, entry->tex)` — `entry+0x94` points at the D3D texture object
   whose `+0x110` field is the actual `IDirectDrawSurface7` texture handle.
5. **Flush**: if `g_spriteVertexCount != 0`, one `DrawPrimitive` and reset the
   count — so **each layer is its own draw call**, which is why the layer order
   below is also the back-to-front paint order.

The three device methods used are all raw vtable calls on `g_pD3DDevice7`, and
their offsets are now pinned from the recovered argument lists:

| Offset | `IDirect3DDevice7` method | Call shape in this function |
|---|---|---|
| `+0x50` | `SetRenderState` | `(dev, state, value)` — used only for blend setup |
| `+0x8c` | `SetTexture` | `(dev, 0, texHandle)` |
| `+0x64` | `DrawPrimitive` | `(dev, 4 /*TRIANGLELIST*/, 0x244 /*FVF*/, &g_spriteVertexBuffer, g_spriteVertexCount*3, 1)` |

**Blend-state cache (`g_currentBlendMode`, mirrored by `_DAT_00792194`).** Rather than
re-issue `SetRenderState` every layer, the function caches the current blend mode
and only reprograms it on a change:
- `1` = **normal alpha**: `SRCBLEND(0x13)=SRCALPHA(5)`, `DESTBLEND(0x14)=INVSRCALPHA(6)`.
- `2` = **additive glow**: `SRCBLEND=SRCALPHA`, `DESTBLEND=ONE(2)`.

Glow-style effects (the Jewel second pass, `SpecialTexture2`, etc.) flip to mode
`2`; everything else runs in mode `1`. (`g_currentBlendMode` was `DAT_00793614`.)

**Confirmed layer order** (each is a texture-lookup + cull + emit + flush phase):
background atlas (8-slot 3-column grid, per-player culled) → several
mobile/marker layers (the inner loop special-cases indices `0/4/6/7`) →
**animated flame** (`FlameTexture%d` via `sprintf`, plus `FlameTexture2/3/4`
as separate layers) → **`RayonTexture1/2`** (beam/ray effects, drawn with
`BuildRotatedSpriteQuad`) → **`JewelTexture`** — *only when the game mode word
equals 3*, which independently **confirms game mode 3 = Jewel** — drawn twice
(an alpha pass then an additive-glow pass with a V-offset) over 8 jewel slots →
**`SpecialTexture1/2`** (a single special object at `ctx+0x22d28`, alpha then
additive) → the **main mobile block** (`&DAT_00554060` texture) described next.

**World→screen and culling.** Every object's world position has the camera
scroll subtracted (`worldX - camX`, `camX` at `g_nCameraX`; `worldY - camY`
at `g_nCameraY`) and is then biased by `+400` / `+0x12a` (half of the 800×600
back buffer). Culling compares against the clip rect `DAT_00793530` (left) /
`DAT_0056df30` (right) / `DAT_00793534` (top) / `DAT_0056df34` (bottom).

**The anti-cheat value guard** (the tail block, `ctx+0x621e0` = the active
mobile) is why ~110 of the calls in this function are `PeekPacketChecksumState`
wrapped in `EnterCriticalSection(&DAT_005a9068)`. Gameplay-critical values are
**not stored in the clear**: each is a `(a, b, check)` byte triple where a valid
value satisfies `check == (a + b - 0x34) & 0xff`, and the decoded bit/value is
recovered as `(b >> (a & 7)) & 1`. A failed checksum sets the tamper flag
`g_valueGuardTamperFlag = 1` (was `DAT_00793514`; set across the whole value-guard
subsystem — `PeekPacketChecksumState`, `EncodeOutgoingPacketField`, the
`FUN_00406xxx` cluster). Immediately after each read, the
backing store (`DAT_0079376c`) is **refilled with `rand()` bytes** — the values
are re-scrambled every frame so a memory scanner (Cheat Engine et al.) can never
lock onto a stable address. This is GunBound's well-known in-client value
obfuscation, and the render path is where it is most densely exercised.

**Frame teardown** (after the last flush): reset the eight per-slot effect
handles at `ctx+0x1fe6c…` to `-1`, **advance two particle-trail history ring
buffers** (the two shift-loops copy each trail entry from the previous frame's,
so trails fade over 15 / 7 frames), clear the per-frame transient active flags
(player `+0x20b0c`, special `+0x22d24`, jewel `+0x23244`, …), and — if a flag is
set — draw one **full-screen 800×600 dim overlay** (`BuildColorQuad(0,0,799,…,599,…,
0x80000000)`, i.e. 50%-alpha black) used for fade/pause transitions.
`BuildColorQuad` (`0x4ed5a0`, was `FUN_004ed5a0`) is the plain-fill member of
the quad-emitter family — it appends an **untextured, vertex-coloured** quad
(4 corner positions + 6 ARGB vertex colours) to `g_spriteVertexBuffer`, unlike
`BuildSpriteQuad`/`BuildRotatedSpriteQuad` which carry texture UVs. **`GameTick`
draws this same dim under every modal dialog**, not just battle transitions:
when `g_stateChangeInProgress != 0` (a `ShowErrorDialog` popup is up) it fills
the whole 800×600 back buffer with the 50%-alpha-black quad before blitting the
dialog panel — the shade behind error/message dialogs.

`g_frameTriangleCounter` (was `DAT_0079365c`; incremented by `g_spriteVertexCount`
before every flush, reset to 0 once per frame in `GameTick`) is a per-frame
**triangle/vertex counter** — a rendering stat, not gameplay state.

### `DAT_007935fc` — resolved: the Z-buffer

Traced its creation in `SetupZBuffer` (`0x4ef9a0`, was `FUN_004ef9a0`):
`IDirect3D7::EnumZBufferFormats` finds a supported depth format, then
`IDirectDraw7::CreateSurface` builds `g_pZBufferSurface`, which gets
`AddAttachedSurface`'d onto the back buffer and the device's render target is
re-set. A Z-buffer for what's fundamentally 2D sprite rendering — plausibly
just a HAL-device requirement of this D3D7 code path, or used for
depth-sorted overlapping sprites (not confirmed which).

### `GameTick`'s exact per-frame render dispatch — now traced end to end

Investigating the game lobby's rendering (who actually drives
`State03_GameRoomList_RenderRoomLabel`, since nothing in the whole binary
calls it directly by address — it's pure virtual dispatch) led to
decompiling `GameTick` (`0x413130`)'s render section directly, which
resolves the full per-tick pipeline in one place:

1. If `IDirect3DDevice7::BeginScene` succeeds, call
   `g_gameStateVTableArray[g_currentGameState]->vtable[0x38]` — **vtable
   slot 14**, the hardware D3D render slot. Real content only exists here
   for In-Battle (see below); every other state's override is the shared
   no-op.
2. `LockBackBuffer`, then call
   `g_gameStateVTableArray[g_currentGameState]->vtable[0x3c]` — **vtable
   slot 15**, the software-blit render slot. This is what actually invokes
   `State03_GameRoomList_RenderRoomLabel` for the lobby (and
   `State10_Loading`'s render function, etc.) — confirming slot 15 is a
   real, generic "draw this state's bespoke content via the software
   blitter" hook, called unconditionally once per tick regardless of
   which state is active (most states' override is just the shared
   no-op, as already established).
3. **Immediately after slot 15**, `GameTick` walks a linked list rooted at
   `DAT_00e53c48` and calls **`node->object->vtable[0x24]`** on every
   entry — this is the generic **active-object registry**
   (`RegisterActiveObject`'s own list, already documented in the
   ButtonWidget section) being swept once per tick to draw every
   currently-registered UI object (buttons, dialogs, etc.), independent
   of which state is active. (`vtable[0x24]` doesn't match
   `vtable_ButtonWidget`'s own 5-slot/20-byte vtable, so this list holds
   a different, larger base-class type than the `ButtonWidget` objects
   themselves — most likely a shared active-object base/wrapper class
   with more virtual methods, of which one is "render"; not pinned down
   further this pass.)

**This explains the lobby's (and every simple UI screen's) rendering
completely**: the room list background/labels come from the state's own
slot-15 override (bespoke per state, often nothing), while every button,
popup, and other interactive widget on screen is drawn independently by
the generic active-object sweep that runs right after — two separate,
composable render paths converging every frame, which is also why states
like Server Select have "no bespoke render function" (per the earlier
finding) and still show real buttons: those buttons draw themselves via
the sweep, with no help needed from the state's own vtable at all.

### Hardware rendering is In-Battle-only — resolved

Checked every function in the binary that touches `g_pD3DDevice7` (17 total).
Fifteen are core D3D infrastructure (init/shutdown/present/z-buffer — all
already documented above). Of the remaining two, **both are In-Battle
content**: `State11_InBattle_Render` (the main render function) and
**`State11_InBattle_RenderModeIcons`** (`0x4caed0`, was `FUN_004caed0`,
944 bytes — draws special-mode indicator icons, confirmed via `TagTexture`/
`YesooriTexture` strings, i.e. Tag-mode and Yesoori-mode battle indicators).

**Conclusion: the Direct3D 7 hardware pipeline (rotated textured quads,
alpha blending, the vertex buffer) is used exclusively during In-Battle
rendering.** Every other screen — Title, Server Select, Room List, Avatar
Store, Ready Room, Loading, both Logo screens — renders entirely through the
**software blitter** (`LockBackBuffer`/`BlitRLESprite`/`BlitSprite16bpp`/
`BlitSpriteClipped`/`Unlock`), never touching the D3D device. This makes
sense architecturally: menus/lobbies are static-positioned 2D UI with no
rotation needs, while battle requires rotated, alpha-blended, numerous
dynamic sprites (tanks, projectiles, explosion effects) where GPU
acceleration earns its keep. This closes the "other states' render paths"
open thread — there isn't a separate hardware path to find for them.

### Software-blitter callers: non-battle states do have real render content

Checked who calls the four software blit primitives (`BlitRLESprite`,
`BlitSprite16bpp`, `BlitSpriteClipped`, ~29-30 callers each). Two confirmed,
concrete results:

- **`LockBackBuffer` is called only from `GameTick`** — the buffer lock is
  centralized; individual draw functions receive/operate on the already-
  locked pixel buffer rather than locking it themselves.
- **`State03_GameRoomList_RenderRoomLabel`** (`0x429810`, was `FUN_00429810`)
  — confirmed via vtable-offset arithmetic (`0x5536ac` − `0x553670` = `0x3c`
  = slot 15 on State 3's vtable) — draws room name/player-count labels using
  the **same `%s[%3d/%3d]` bitmap-font text format** as the In-Battle
  scoreboard (`State11...`'s slot-15 function, `0x408180`'s caller). This
  confirms non-battle screens **do** render real per-state content through
  the software path, using shared text-rendering infrastructure — they
  aren't merely static.

  **Fully decompiled — the lobby's actual room-card grid renderer, found
  by following its internal loop.** `RenderRoomLabel` doesn't just draw
  fixed labels; its tail is a loop over up to **6 room slots**
  (`0x4464c` to `0x44664`, 4-byte stride — skipping the current client's
  own room index) calling **`RenderRoomCard(roomIndex)`** once per occupied
  slot. That function is the real per-room "card" draw, and it's rich:
  - **Grid layout**: `roomIndex / 3` selects a column (X base `0x18` or
    `0x144` — a 2-column layout), `roomIndex % 3` selects a row (`* 0x3c`
    = 60px vertical spacing) — i.e. the classic **3-row × 2-column room
    browser grid**.
  - **3-state background**: base sprite index, `+1` if this room is the
    currently-hovered/selected one (`param_1+8`), `+2` if it's the room
    the client has actually joined (`param_1+4`) — a highlighted vs.
    normal vs. joined visual state per card.
  - A room-type/flag icon, two more small per-room byte-flag icons
    (offset `+10` into the sprite range — likely min/max level or
    team-count indicators), and a combined mode/map icon computed from
    `(flagByte & 3) * 11 + otherByte` (a small state-space icon lookup,
    map/weather-style).
  - A **status icon** (`waiting`/`in-progress`/`full`-style, 3 possible
    sprite indices 7/8/9) derived from a byte flag plus a same-value
    comparison between two other per-room fields.
  - A **conditional lock icon**, drawn only if a per-room byte flag is
    set — almost certainly the "private/password-protected room" padlock
    seen in the classic GunBound lobby UI.
  - The **room number** (`sprintf("%d", roomIndex+1)`, rendered via a
    different helper, `BlitSpriteText`, not `BlitRLESprite` directly — a
    distinct, not-yet-explored text-rendering path) and the **player
    count** (via `BlitRLESprite`, the bitmap-font renderer).
  - A final **"fullness" icon** (4 possible states, extracted from bits
    18-19 of a per-room info `dword`) — likely an empty/partial/nearly
    full/full indicator distinct from the status icon above.

  This fully explains the lobby's visual content end to end: `GameTick`
  calls State 3's slot 15 once per tick (see the dispatch trace below),
  which draws the static chrome then loops the room list calling this
  per-card renderer for every occupied slot — while every actual button
  (create room, refresh, etc.) draws itself separately via the generic
  active-object sweep (also below).

  **Room selection/joining, traced from the click side.** The room cards
  aren't `ButtonWidget` objects — clicks are handled directly by the
  state's own mouse-message vtable slot (`State03_GameRoomList_HandleMouseInput`), which hit-tests
  against the same 6-slot grid geometry via `RoomCardHitTest`. Left-click
  selects/highlights a room (driving the 3-state background above);
  right-click (not double-click) sends the actual join request — outgoing
  opcode `0x2104`, a new addition to PROTOCOL.md's Channel 1 opcode list.
  Full write-up, including why double-click isn't the join trigger and
  why there's no separate "change channel" mechanic inside this screen,
  is in PROTOCOL.md's opcode `0x2104` section.

However, checking the same vtable slot across other states (State 2's slot
15 is a distinct 62-byte function with no identifying strings; State 7's is
the shared no-op) confirms — consistent with the earlier finding for slot 9
— that **these vtable slots are generic per-state hooks with no fixed
semantic**; "slot 15 = UI label" is true for State 3 specifically, not a
universal rendering slot. Mapping each state's actual render entry point
would mean checking each vtable slot individually per state rather than
assuming a shared slot index — noted as future work, not completed here.

### The lobby command dispatcher — `State03_GameRoomList_OnCommand` (State 3 vtable slot 5)

Decompiled State 3's slot-5 virtual (`0x4285c0`) in full — it's the lobby's
central **command/action dispatcher**, the single funnel every lobby button,
menu item, and list event routes through. Signature `(this, eventType,
param_3, buttonId)`:

- **`eventType` (`param_2`)** selects the category:
  - `0` — a button was clicked; dispatch on `buttonId` (`param_4`).
  - `0xa` (10) — a confirm/commit event (e.g. a dialog's OK button); branches
    on the object's pending-op flags at `+0xc`/`+0xd`/`+0xe` and finalizes
    (create-room submit `0x2120`, join-selected, or join-by-number).
  - `0xb` (11) — a cancel/dismiss event; closes the active dialog
    (`PanelManager_Unregister`).

- **The `param_4` switch dispatches on button ID, not the widget's stored
  "action code."** Cross-checked against the lobby's real button-creation
  call, `State03_GameRoomList_CreateButtons` (previously not referenced by this doc — it's a
  separate function from the already-ported `OnEnter`, called once from it):

  ```c
  CreateButtonWidget(list, group, buttonId, actionCode, image, x, y, w, h, enabled, param11);
  CreateButtonWidget(&DAT_00e9be90, 0, 0, 1000, "b_gamelist_exit",    0x28,0x227, 0x6b,0x2d, 0,0);
  CreateButtonWidget(&DAT_00e9be90, 0, 1, 0x3e9,"b_gamelist_buddy",   0xa3,0x227, 0x6b,0x2d, 0,0);
  CreateButtonWidget(&DAT_00e9be90, 0, 2, 0x3ea,"b_gamelist_ranking", 0x11e,0x227,0x6b,0x2d, 0,0);
  CreateButtonWidget(&DAT_00e9be90, 0, 3, 0x3eb,"b_gamelist_avatar",  0x199,0x227,0x6b,0x2d, 0,0);
  CreateButtonWidget(&DAT_00e9be90, 0, 4, 0x3ec,"b_gamelist_create",  0x214,0x227,0x6b,0x2d, 0,0);
  CreateButtonWidget(&DAT_00e9be90, 0, 5, 0x3ed,"b_gamelist_join",    0x28f,0x227,0x6b,0x2d, 0,0);
  CreateButtonWidget(&DAT_00e9be90, 0, 0xa,0x44c,"b_gamelist_viewall",0x2a,0xf6,  0x51,0x21, 0,0);
  CreateButtonWidget(&DAT_00e9be90, 0, 0xb,0x44d,"b_gamelist_wait",   0x83,0xf6,  0x51,0x21, 0,0);
  CreateButtonWidget(&DAT_00e9be90, 0, 0xc,0x44e,"b_gamelist_prev",   0xf2,0xf6,  0x31,0x21, 0,0);
  CreateButtonWidget(&DAT_00e9be90, 0, 0xd,0x44f,"b_gamelist_next",   0x124,0xf6, 0x31,0x21, 0,0);
  CreateButtonWidget(&DAT_00e9be90, 0, 0xe,0x450,"b_gamelist_friend", 0x173,0xf6, 0x51,0x21, 0,0);
  CreateButtonWidget(&DAT_00e9be90, 0, 0xf,0x451,"b_gamelist_directgo",0x1cc,0xf6,0x51,0x21, 0,0);
  ```

  The switch's case values (`0`–`0xf`) line up exactly with `buttonId`
  (the 3rd argument), **not** the 1000-range `actionCode` (4th argument) —
  those larger values are consumed elsewhere (by `FUN_004f1790`, see below),
  not by this dispatcher. This is a naming correction from an earlier pass
  that assumed the switch dispatched on "action code."

- **Confirmed button map** (`buttonId` when `eventType==0`):

  | ID | Image | Action | How |
  |---|---|---|---|
  | 0 | `b_gamelist_exit` | **Exit lobby → Server Select** | `ChangeGameState(2)` |
  | 1 | `b_gamelist_buddy` | (re)build the buddy-list panel | `BuildBuddyPanel` (also run from `OnEnter`) |
  | 2 | `b_gamelist_ranking` | (no case — falls to default, no-op in this build) | — |
  | 3 | `b_gamelist_avatar` | **Enter Avatar Store** | sends outgoing `0x6000` (guarded on the inventory-loaded flag) |
  | 4 | `b_gamelist_create` | **Open the Create Room dialog** | `OpenCreateRoomDialog` → `BuildCreateRoomDialog`, dialog title msg `0x62b2`, fields for room name + password (msgs `0x514`–`0x51d`) |
  | 5 | `b_gamelist_join` | **Join the selected room** | `SendJoinRoomChecked` → `0x2110`, after an "already in that room" dedupe check |
  | 0xa | `b_gamelist_viewall` | Room-list filter **mode 1** ("view all") | re-request room list, `0x2100` (mode byte = 1) |
  | 0xb | `b_gamelist_wait` | Room-list filter **mode 2** ("waiting only") | re-request room list, `0x2100` (mode byte = 2) |
  | 0xc | `b_gamelist_prev` | Room-list page **prev** | decrements page (`+0x118`), sends `0x2100`/`0x2101` |
  | 0xd | `b_gamelist_next` | Room-list page **next** | increments page, sends `0x2100`/`0x2101` |
  | 0xe | `b_gamelist_friend` | **Find Friend** — locate a buddy's current room | `FindBuddyRoomsForServer` scans the active room list for a match (filter criterion passed via an uncaptured register, likely a buddy ID — not fully pinned down); if found, requests its record via `0x2101`; if not, clears a "found" flag at `+0x44648` |
  | 0xf | `b_gamelist_directgo` | **Open the "enter room by number" dialog** | `BuildEnterRoomNumberDialog` — separate dialog, msg `0x2715`, fields `0x578`/`0x579` |

  Dialog-internal actions (reached via `eventType==0xa`/`0xb` from a dialog's
  own OK/Cancel, not a top-level lobby button) use higher codes:
  `0x1e`/`0x20`/`0x28` are plain **Cancel** buttons (`PanelManager_Unregister`, dismiss
  the active dialog); `0x1f` and `0x21` are **Join-selected**/**Join-by-number**
  confirms (`SendJoinRoomSelected`/`SendJoinRoomByNumber`); `0x29` and the
  `eventType==0xa && flag@+0xc` path both reach **`SendCreateRoom`, the Create
  Room dialog's actual submit handler** (see below).

  This corrects an earlier draft that mislabeled `0xe` as a generic "channel
  selector" — it's specifically the Friend/buddy-locate button — and left
  `0x2120` as an unidentified "leave-room" guess.

- **`SendCreateRoom` — Create Room submission (was mis-flagged "leave-room").**
  Copies the dialog's room-name and password text fields into a local buffer,
  then sends **outgoing opcode `0x2120`**: room name (NUL-terminated string),
  password (NUL-terminated string), the dialog's message-id field (`0x62b2`),
  and a type byte (`8`). This is genuinely the room-creation request, not a
  leave/refresh action — corrected in PROTOCOL.md. It reads the final text
  from a separate results/snapshot object (`DAT_00e53c44`, walked by a
  `(+0x20==0 && +0x24==0)` match), not the live dialog widgets directly — the
  step that copies widget text into that snapshot on OK-press wasn't traced.

  **The dialog's full field layout — decompiled `BuildCreateRoomDialog` (the builder
  `OpenCreateRoomDialog` calls) in detail.** Ten widgets, created in this order, all
  using the message IDs `OnEnter` preloads (`0x514`–`0x51d`, confirming this
  *is* the complete, self-contained resource set for this one dialog):

  | Widget(s) | Type (by allocator) | Position (x,y) w×h | Msg ID(s) | Role |
  |---|---|---|---|---|
  | id 0 | large (0x140-byte, `CreateTextEntryWidget` — has an internal text buffer) | (0x60,0x2c) 0xbe×0xc | — | **Room name entry** (widest field, near the top) |
  | id 1 | large (0x140-byte, same allocator) | (0x60,0x46) 0xbe×0xc | — | **Password entry** (same width, directly below) |
  | ids 2–9 (8 boxes) | small (0x40-byte, `CreateLabelWidget`) | x = 0xad+32·i, y=**8** (top row) | `0x518`–`0x51f` | Likely a **player-limit picker** (8 boxes, GunBound rooms commonly cap at 2–8); the 4th box (`i==3`) is flagged specially (`+0x3a=1`) — plausibly "default selected," i.e. a default room limit of 4 |
  | ids 4–7 (2×2 grid) | small (0x40-byte) | (0x16,0x5f)/(0x45,0x5f)/(0x16,0x7a)/(0x45,0x7a), each 0x2d×0x18 | `0x514`–`0x517` | Unclear — a 2×2 grid of 4 small toggles, most plausibly a **room-mode selector** (e.g. solo/team); not confirmed, no click-handler for these was traced |
  | id 8 | small (0x40-byte) | (0xd5,0x99) 0x52×0x22 | `0x51d` | Bottom-right button — by position/size, one of **OK/Cancel** |
  | id 9 | small (0x40-byte) | (0x80,0x99) 0x52×0x22 | `0x51c` | Bottom-left button — the other of **OK/Cancel** |

  The room-mode-grid and OK/Cancel-vs-label assignments for msgs `0x514`–
  `0x51d` are not decoded (this project has no access to the localized
  string table's content, only IDs) — positions and structural roles are
  confirmed from the layout; exact captions are not.

  **Field offsets independently confirmed** by decompiling the "large"
  widget class's own vtable (`PTR_LAB_00557c84`, used by `CreateTextEntryWidget`).
  Its hit-test method (`Widget_HitTest`, one of 3 non-trivial slots — the
  other two, `0x50e870`/`0x50e950`, are near-identical child-broadcast
  helpers dispatching through a container's child list) reads position
  unconditionally from `+0x28`(x)/`+0x2c`(y)/`+0x30`(w)/`+0x34`(h) —
  exactly the byte offsets the constructor's `x,y,w,h` arguments land at
  (dword indices `0xa`/`0xb`/`0xc`/`0xd`). This validates the Create Room
  table above wasn't just positional guesswork.

  **Same widget class used for the "enter room by number" dialog**
  (`BuildEnterRoomNumberDialog`, opened by button `0xf`) shows a genuine anomaly worth
  flagging rather than silently resolving: its two large-class widgets
  (msgs `0x2bf`/`0x2bd`) get `x≈700`/`w=7` and `x≈700`/`w=39` — a 7–39px
  hit-box is implausible for real text entry (likely **static labels**,
  which don't need a generous click area, rather than the room-name/
  password-style entry fields Create Room uses). What's **not** ambiguous:
  this dialog's two small-class widgets (`CreateLabelWidget`, msgs `0x578` left
  at x=0x80/`0x579` right at x=0xd5, both `0x52×0x22`) are **identical in
  size and left/right ordering** to Create Room's own `0x51c`/`0x51d`
  button pair — confirming an **OK/Cancel button pair** here too, reused
  at the same visual size across both dialogs.

- **`FUN_004f1790` is not a "watchdog timer" (correcting the Logo1/Logo2
  docs).** `OnEnter` calls it ~40 times with values like `0x514`–`0x51d`,
  `0x578`/`0x579`, `0x2711`, etc. — and those exact values reappear as the
  Create Room and "enter room by number" dialogs' field message-IDs
  (`BuildCreateRoomDialog`/`BuildEnterRoomNumberDialog` above). Decompiling it shows it does **not**
  set any duration/timeout field: it loads an XFS-resourced definition
  (`FindXFSEntry`/`ReadXFSEntry`, resource name passed via an uncaptured
  register — the same "hidden EAX argument" class of issue already
  documented for `AppendPersistentButtonName`), allocates one or more 0x50-
  byte "active objects" per sub-entry, tags each with the passed-in ID, and
  registers them via `RegisterActiveObject()`. This is a **generic
  per-ID resource/effect preloader** (most likely dialog-panel chrome or
  button hover/press visuals, keyed by message/button ID) — not a timer.
  The Logo1/Logo2 screens' "10-second watchdog" framing (params `10000`/
  `0x2711`) should be read as "preload resource ID 10000/`0x2711`," not "wait
  10 seconds"; their actual auto-advance timing is driven by the separate,
  confirmed frame-counter tick hooks, which is unaffected by this correction.

- **`OnEnter` (`0x428d00`)** context that feeds this: registers ~40 button
  definitions (`FUN_004f1790`) and 12 persistent buttons, sends the initial
  **`0x2100`** room-list request (mode byte from `+0x115`, chosen `1` or `2`
  based on a checksum-state check), sets the window title, **closes any active
  replay file** (writes a final `0x03` byte then `fclose` — the lobby ends
  battle replay recording), and surfaces up to four carried-over status
  messages (localized ids `0xc351`–`0xc354`, gated on `PeekPacketChecksumState`
  bits `0x100000`–`0x800000` — most likely "you were kicked / disconnected /
  match ended"-style notices shown on returning from a battle).

New outgoing opcodes surfaced here (`0x2100`, `0x2101`, `0x2110`, and
`0x2120`, the last two now fully resolved — join-room and Create-Room
respectively) are written up in PROTOCOL.md; `0x2104` (right-click
join, from the mouse slot) and `0x6000` (avatar store) were already documented.

### Per-state vtable slot survey — Ready Room and Loading

Dumped every vtable slot for the remaining states and created/checked the
previously-unexamined ones. Findings:

- **Title, Logo1, ServerSelect share the identical slot-15 function**
  (`0x443570`) — confirms it's a lightweight shared utility, not a
  state-specific render override (Logo2 differs slightly, `0x443360`).
  Reinforces the earlier finding that vtable slots have no fixed meaning
  across states.

  **`State05_Logo1` (the Softnyx publisher splash screen — first screen
  in the confirmed boot flow, `Logo1(5) → Logo2(6) → Title(1) → ...`)
  fully mapped — it's about as simple as a screen gets.** Its object is
  only **8 bytes** (a vtable pointer plus one `int` field), and every
  vtable slot beyond destructor/enter/exit is a shared no-op except two:
  - `OnEnter` (`0x4433f0`): three lines — preloads resource/effect
    definitions `10000` and `0x2711` (`FUN_004f1790`; **corrected** — not a
    "watchdog timer" as earlier described here, see the lobby dispatcher
    section below for the real trace), zeroes the object's one `int` field
    (a frame counter), and plays `logo.mp3` (`PlayMusicTrack(0)`, the confirmed
    music-start helper).
  - **Slot 9** (`0x443540`, the per-tick hook): increments that same
    frame counter and, once it reaches **`0x28` (40 ticks ≈ 2 seconds** at
    the confirmed 50ms tick rate**)**, calls `ChangeGameState(6)` to
    advance to Logo2 — the same auto-transition idiom already confirmed
    for the Title screen (60 ticks ≈ 3 seconds there), just a shorter
    timer here.
  - **Rendering is entirely the shared slot-15 background blit**
    (`0x443570`, decompiled in full during the Server Select
    investigation): draws whatever background sprite is currently loaded
    (sprite index 0 — the Softnyx logo image, `logomode.img`) via
    `BlitSprite16bpp`/`BlitSpriteClipped`, nothing more.
  - **No buttons, no other UI at all** — no `CreateButtonWidget` calls
    exist anywhere for this state (consistent with its 8-byte object
    having no room for a widget-list field), matching what you'd expect
    for a pure, non-interactive publisher splash screen: load a
    full-screen logo image, play a jingle, wait ~2 seconds, move on.
- **`State09_ReadyRoom_RenderCharacterPreview`** (`0x4d90c0`, was
  `FUN_004d90c0`, 2,575 bytes) — loads `AvataTexture1/2`,
  `CharacterTexture1/2`, `AvataEffectTexture1/2`, `CharEffectTexture1/2` —
  the exact same texture families used by In-Battle rendering, confirming
  the Ready Room draws a live character/avatar preview before battle starts.

  **The rest of the Ready Room's UI panels — traced this pass.** Two more
  large vtable-13/15 functions (previously unexamined, but already flagged
  as `BlitRLESprite` callers back in the very first caller-scan of this
  project) turn out to render distinct panels:
  - **Slot 13** (`State09_ReadyRoom_RenderRosterAndItems`, `0x4d7db0`, was
    `FUN_004d7db0`, 4,854 bytes) is a **combined
    player-roster + item-selection renderer**, drawn top-to-bottom in one
    function:
    - An **8-player ready-roster row** (2 rows × 4 columns), using the
      exact same `PeekPacketChecksumState()`-bit-per-slot idiom already
      confirmed for the Loading screen's per-player ready icons — i.e.
      the same "which players have sent their ready/checksum state" check
      drives both screens' player-status displays.
    - A **paginated item-selection grid**: 9 slots per page (3×3,
      `(index%3)*0x46+0x210` / `(index/3)*0x2d+0x193` spacing), reading
      item IDs from a per-client array (`param_1+0x518`) and looking up
      each item's display sprite through a **global item-ID → sprite-index
      table** (`&g_awItemIconTable`) — with a label (via `BlitSpriteText`, the
      confirmed text-render/prep helper) drawn under each icon. The
      current page is tracked at `param_1+0x620`, total item count at
      `+0x61c` — this is the player's **inventory/item-loadout picker**,
      confirmed as a real paginated grid rather than a fixed short list.

      **`g_awItemIconTable`'s encoding — decoded directly from the real binary
      and its consumer code** (`State09_ReadyRoom_RenderRosterAndItems`,
      right after the lookup
      above). Table bounds confirmed empirically: it's exactly **40
      `uint16` entries** (`0x56dc40`-`0x56dc8f`) — entry 40 lands on an
      unrelated string (`"cosmik"` + what looks like a build GUID/stamp),
      confirming the real boundary rather than the reconstructed source's
      incidental "next declared global" gap. Each packed entry decodes as:
      - **low byte** — an icon-pair index. The consumer computes
        `frame = (entry & 0xff) * 2`, then blits frame `frame-2` normally
        or `frame-1` when the item is unowned/disabled (`*(itemID+0x4d8)
        == 0`) or a UI mode flag is set — i.e. **every item icon occupies
        two adjacent frames in its sheet, an enabled/disabled pair**, and
        the low byte selects which pair.
      - **high byte** — `0x00` or `0xff`, selects which of two icon-sheet
        textures to blit from: `((entry & 0xff00) != 0) + 0x2713`, i.e.
        texture id `0x2713` (0) or `0x2714` (1).

      **What indexes the table at runtime is still open.** `itemdata.dat`'s
      own on-disk `0x30` field (see FILEFORMATS.md) uses this *exact same*
      encoding — every populated record's `0x30` value appears verbatim
      somewhere in this 40-entry table — confirming both draw from one
      shared icon-ID vocabulary.

      **RESOLVED (2026) — the `+0x518` identifier is a compact item index
      0–63.** The loadout builder `FUN_004dbd50` scans an 8-byte (64-bit)
      **item-ownership bitmask** the server pushes to
      `g_clientContext + 0x457a1` (bit *i* = "player owns battle item *i*")
      and packs each *owned* index into `+0x518` (count in `+0x61c`, capped
      **11**). So the per-slot value is neither `itemdata.dat`'s type ID nor
      its on-disk slot — it's the item's ordinal in the 0–63 space that
      **also** indexes `g_awItemIconTable` (icon) and the ownership bitmask bit.
      Items 0–10 are the battle-usable set; their per-turn counts are
      `CValueGuard`-protected. `g_awItemIconTable[index]` gives the icon; the
      quantity drawn per cell comes from a 100-entry guarded lookup keyed by
      that icon value (`FUN_0041e9a0`). The bitmask arrives via the `0x2105`
      room packet (`+5`/`+9`) and battle actions `0x8004` / `0x8000` (see
      PROTOCOL.md "Item availability").

      **The 40-entry table and the ordinal→item identity are now both
      extracted** (`tools/lzhuf/decode_item.py`, values baked into
      `src/globals.c`). The runtime index question was the last gap, and it's
      closed: `g_awItemIconTable[ordinal]` is that ordinal's icon code, and matching
      each icon code to a record's `0x30` field in the decompressed
      `itemdata.dat` recovers the item — so the ordinal→item mapping is *not*
      server-only; it's derivable entirely from client data. Ordinals 0–10
      (the battle items) resolve to: **0 Dual, 1 Blood, 2 Energy up 2, 3 Energy
      up 1, 4 Dual+, 5 Change Wind, 6 Team Teleport, 7 Bunge shot, 8 Power up,
      9 Thunder, 10 Teleport**. Ordinals 11–39 are icon slots for items this
      build's `itemdata.dat` doesn't define (only 13 of 100 records populated).
    - This function also loads the full `AvataTexture`/`CharacterTexture`/
      effect-texture family again (same as `RenderCharacterPreview`),
      consistent with it sharing the screen with the live character
      preview rather than being a separate overlay.
  - **Slot 15** (`State09_ReadyRoom_RenderStatusOverlay`, 2,406 bytes) draws content at several
    **fixed, non-computed screen positions** (not a formula-driven grid
    like the item picker) — most plausibly **map-selection thumbnails**
    given the small, fixed count of distinct positions (six), though this
    wasn't cross-checked against `ready_selectmap.img`'s actual content to
    fully confirm; flagged as a strong inference, not a certainty.
  - **Mobile/character selection itself (the picker that chooses *which*
    of the 16 characters `RenderCharacterPreview` then shows) wasn't
    located in this pass** — `RenderCharacterPreview` clearly renders
    *whichever* character is currently selected, but the actual selection
    UI (a click-driven picker analogous to the room-list's hit-test
    function) wasn't found in either of the two functions above or
    tracked down elsewhere. A genuine open item, not resolved here.
- **`State09_ReadyRoom_HandleChatInput`** (`0x4d6210`, was `FUN_004d6210`)
  and its Loading-screen counterpart **`State10_Loading_HandleChatInput`**
  (`0x43e720`, was `FUN_0043e720`) — confirmed as **Win32 message handlers**
  (dispatch on `param_2==0x100`=`WM_KEYDOWN`, checking `param_3==0xd`=Enter),
  not render functions. On Enter, reads the chat textbox, and if the text
  isn't a recognized command, **logs it to the replay stream**
  (`QueueBroadcastEvent(1)` + `AppendBroadcastString`) — confirms replays
  capture chat messages, not just game actions.

  **Investigated how a typed chat message is actually sent over the
  network — genuinely didn't find it, worth recording precisely.** The
  normal-message success path in `State09_ReadyRoom_HandleChatInput` is
  exactly: `QueueBroadcastEvent(1)` → copy the text → `AppendBroadcastString`
  → `BroadcastQueuedEvent()` → clear the textbox (`SetWindowTextA`) → return.
  **No `QueueOutgoingPacketField`/`EncodeOutgoingPacketField` call (the
  confirmed outgoing-packet-field API used everywhere else in this
  project) appears anywhere in this function**, nor in its gatekeeper
  `FUN_00415230` (which turned out to be an unrelated check — some kind
  of formatted-local-time comparison via `FUN_0040d260`/`FUN_00525ea0`,
  not a network call; purpose not pinned down, doesn't look like a
  profanity filter or send routine from its shape). The only other calls
  on this path are `ParseChatSlashCommand` (the already-documented `/`-command
  parser, confirmed not a network function) and, for two special-case
  outcomes (link-detected/`0x202`, or `FUN_00415230`'s check failing/
  `0x205`), a `vtable+0x28` call that resolves and displays a localized
  status string — a "show a system message" UI call, not a send. This
  means either **the actual chat packet transmission happens through a
  mechanism not identified in this pass** (a raw Winsock `send()`/
  `sendto()` call bypassing the queued-packet-field API entirely is the
  most likely candidate, given this project has already confirmed the
  battle-action channel uses direct `recvfrom` handling outside the
  queued-field system too — see the two-channel network architecture
  above), or there's a call site this search missed. The equivalent
  in-battle chat-send trigger (a `State11`-specific chat handler) also
  wasn't located at all in this pass — no function named or shaped like
  `State11_InBattle_HandleChatInput` was found; `State11`'s slot 5
  keyboard dispatcher (`0x4b82b0`) and `State11_InBattle_HandleFireInput`
  (`0x45f910`) were both checked directly for the chat buffer offsets and
  neither touches them. **Both of these — the exact chat-send network
  call, and where in-battle chat input is handled at all — are open items
  for a future pass**, not resolved here.

  **Resolved for the Ready Room (correcting the "raw Winsock" guess above).**
  Ready-room chat is a **normal queued packet, opcode `0x3104`**, not a raw
  `send()`. The send lives in the Ready Room's command dispatcher
  `State09_ReadyRoom_OnCommand` (`0x4d54e0`), on its `eventType==10`
  chat-commit path: it copies the typed text and, if it isn't a slash-command
  (`CheckChatWordFilter`), sends it via the standard `FUN_004d2530`/`FUN_004d2680`
  queued-packet path. So `HandleChatInput` (`0x4d6210`) handles the keystrokes
  and replay logging, and the committed text is transmitted here. The
  in-battle equivalent remains open.

  **Update: found a real, fully-traced send call — but for a different
  category of message than plain room chat.** The `/message <player>
  <text>` whisper command's handler (`FUN_00402720`) sends over a genuine
  **third network channel**, a separate TCP connection distinct from the
  UDP socket used for the rest of the protocol — see PROTOCOL.md's new
  "Channel 3" section for the full trace (opcodes `0x1020`/`0xa110`, and
  the confirmed raw Winsock `send()` call). This doesn't resolve the
  normal-chat gap above (that's still open), but it does mean **not all
  GunBound chat traffic uses the same transport** — direct/whisper
  messages have their own dedicated connection, most likely to a
  companion "buddy"/messenger service (see the `GameBuddy` registry key
  in STRINGS.md).
  - **The developer-name easter egg — fully traced, and it's more than a
    credits screen.** Both chat handlers call a shared `/`-command parser
    (`ParseChatSlashCommand`, 5,693 bytes) that splits the typed text on `/`,
    extracts the first word, and `stricmp`s it (case-insensitive, and
    gated on `iVar3 == 1` — exactly one token, no extra arguments) against
    a long hardcoded list. Two genuinely distinct categories:
    - **A real staff-credits system**: typing e.g. `/comsik` prints
      "Game Programmer - comsik" via the same generic `ShowMessage`-style
      vtable call (`+0x28`) already established elsewhere in this project,
      each with its own short quote/role line. Confirmed staff list:
      `comsik`, `CozY`, `enddream`, `yesoori`, `oorusa`, `jaeyong`,
      `yaong2`, `jchlee75`, `reddragon`, `designer`, `johnny5`, `loserii`,
      `scjang`, `chuko`, `pirania`, `blash45`, `knights`, plus a couple
      more with mood-message-only responses ("Feel ethereal...",
      "Acks will not be sent..." for `noack`).
    - **Genuine hidden debug/GM commands, not just credits**: `noack` sets
      a global flag (`DAT_00e9b1d8 = 1`) — a real "stop sending
      acknowledgements" network-debug toggle; `clear`/`logging` push
      special replay-stream events (`0x9000`/`0xf00e`); and — the most
      interesting find — **three command names that are plain-ASCII
      strings but decode to real Korean words when typed as if on a
      2-beolsik (두벌식) Korean keyboard layout** (`shrduatlwkr`,
      `shrduarhkswjs`, `shrduaakstpakstpaksakstp`) — a well-known trick
      from Korean-developed software of this era for hiding GM/test
      commands from English-reading players (the Latin letters typed
      don't spell anything recognizable, but under the Korean IME they
      map to real jamo). These three are gated on `g_currentGameState==9`
      (Ready Room) and each build and send a distinct outgoing packet:
      one includes a `GetTickCount()` timestamp plus, conditionally, 6
      bytes of `rand()`-seeded data (reads like a client-side RNG-reseed
      or time-sync debug command); another sets a byte flag to `0xff` in
      the Ready Room state object; the third reads a numeric value via
      `atol` from the parsed chat text and threads it into a small
      per-slot byte array. None of the three were traced further into
      what the *server* does with these packets (would need server code),
      but their client-side triggering mechanism is now fully understood.
- Ready Room's remaining slots: a small (20-byte) ready-status check
  (`0x4d54c0`), a larger (3,167-byte) button enable/disable UI updater
  (`0x4d54e0`), and a texture-preload list identical to Loading's
  (`0x4d7b20`) — consistent with Ready Room needing the same battle assets
  available for its character preview.

### `State10_Loading`'s render slot — confirmed, and it's a real per-player ready screen

Dumped `vtable_State10_Loading` (`0x554018`) directly. Slot 15
(`FUN_00442280`, 2,750 bytes) is the render function; slots 11–14/16/17 all
point at the same 1-byte stub (`0x429800`, a bare `RET`) — confirming
(again) that vtable slot number alone carries no fixed meaning across
states, consistent with the earlier finding for slot 9/15 in other states.

Decompiling `FUN_00442280` in full shows the Loading screen is a genuine,
live status display, not a static "please wait" splash:

- Draws a background sprite, then (gated on `DAT_00e55a34 == -1`) a
  "waiting" overlay sprite, then a couple of fixed decorative icons —
  standard layered background compositing via `BlitSprite16bpp`/
  `BlitSpriteClipped` (branching on the same `DAT_0079352c`/frame-format
  check seen throughout the software-blit layer).
- **A row of up to 16 per-player "ready" icons**, one per potential game
  slot (loop stride `0x2c`=44px horizontally, `0x224` bytes per slot —
  the already-confirmed per-player record size): for each slot, it checks
  that player's bit in `PeekPacketChecksumState()` (the packet-checksum
  utility documented elsewhere in this file) and picks a different sprite
  frame depending on whether the bit is set — i.e. **each icon visually
  flips from "waiting" to "ready" the moment that player's checksum/ready
  packet arrives**, giving the classic "waiting for all players to load"
  screen with live per-player feedback, not a generic progress bar.
- A second loop (stride `0x224`, same per-player array) draws each
  connected player's mobile/avatar icon, picking between sprite frames
  `0x18`/`0x19`/`0x1a` — `0x19` (a distinct "blinking" frame) is selected
  specifically for whichever player currently matches the checksum-state
  slot, toggled on/off via a `(tickCounter/10) & 1`-style parity check —
  i.e. **the still-loading player's icon blinks** while everyone else's
  is static, confirmed by the same one-bit-parity blink idiom used
  elsewhere for turn-highlight-style UI.
- Slot 10 (`FUN_00442240`, 58 bytes) is not itself a render call — it's a
  small string-forwarding helper (computes a string's length then calls
  `AppendChatLogEntry`, a generic widget/label-text setter), consistent with
  the generic UI-widget system documented below.

### Slot 9 ("generic tick hook") is often just timer logic, not render

Ruled out one hypothesis and confirmed another. `WndProc` (`0x410040`) has
**no `WM_PAINT` handling at all** — the DirectDraw/D3D pipeline owns 100% of
presentation, so simple screens are *not* drawn via Windows' native paint
mechanism. But decompiling `State01_Title`'s slot-9 function (`0x4e5400`)
in full shows it's genuinely just a **frame counter**: increments a field
each tick, and at count `0x3c` (60 ticks ≈ 3 seconds at the confirmed 50 ms
tick rate) auto-transitions `ChangeGameState(2)` (Server Select). No drawing
at all. `State01_Title_OnEnter` likewise contains no blit calls — just audio
setup (starts title music via `FUN_004f1790(&DAT_00ea0e18, 10000)`).

### The generic UI-widget system — found and confirmed

Traced the `b_gamelist_buddyup`-style button-name strings back to their
actual reference: not a data table, but a genuine (if decompiler-obscured)
instruction — `MOV EAX, <string address>` immediately followed by a `CALL`,
inside `ChangeGameState` itself. Ghidra's decompiler failed to surface this
particular call's string argument (the value is passed via `EAX`, a register
the decompiler didn't associate with the callee's parameter list — the same
class of issue seen elsewhere in this codebase with custom/register-based
calling conventions), which is why a full prior decompile of `ChangeGameState`
never showed it. Reading the raw x86 disassembly directly resolved it.

**Confirmed architecture, three layers**:

1. **`AppendPersistentButtonName`** (`0x401740`, was `FUN_00401740`) appends
   a button name string into a growable, count-prefixed array (128-byte/
   `0x20`-dword records) at `&DAT_0067ec70 + <session offset>`. `ChangeGameState`
   calls this **9 times in a row on every single state transition**,
   registering a fixed set of persistent button names — the buddy-list
   scroll controls (`b_gamelist_buddyup/down`, `b_buddy_up/down/exit`) and a
   generic error-confirm button (`b_error_confirm`) — confirming these are
   **global, persistent UI elements available across virtually every
   screen**, not per-screen widgets. This same array (`DAT_0067ec70`) is also
   populated by nearly every individual state's own `OnEnter`/`OnExit`
   (547 total cross-references found), plus every per-character weapon-effect
   constructor function found during the earlier rendering pass — it's a
   single, shared, session-wide registry, not one array per screen.
2. **`LoadButtonDefinitionFromXFS`** (`0x401440`, was `FUN_00401440`) is
   called for each registered name and loads that button's actual definition
   from **a named entry inside `graphics.xfs`** (via `FindXFSEntry`/
   `ReadXFSEntryByte` — the exact same archive-reading primitives documented
   in [FILEFORMATS.md](FILEFORMATS.md)), parsing a small binary structure:
   a count, then that many sub-records each with a length-prefixed name
   string followed by several more fields and two dynamically-sized arrays
   — a genuine, distinct **widget-definition micro-format** living inside
   the XFS archive, parsed byte-by-byte like `ChooseEvent.txt` but binary
   rather than text.

   **Now decoded field-by-field**, from a full decompile of
   `LoadButtonDefinitionFromXFS` itself: the entry opens with a 4-byte
   `count`, then exactly `count` records of:
   ```
   uint32   nameLen
   char     name[nameLen]     // raw bytes, NOT null-terminated on disk —
                               // the loader allocates nameLen+1 and writes
                               // its own NUL terminator at name[nameLen]
   uint8    typeByte           // a per-record flag/type byte
   uint32   subCount
   uint32   arrayA[subCount]
   uint32   arrayB[subCount]
   ```
   confirmed by matching every `operator_new` call's size against which
   field it was sized from (`nameLen+1` for the name buffer, `subCount<<2`
   for both trailing arrays) and the read order/count in the loop body —
   the same "byte-by-byte via `ReadXFSEntryByte`" style already established
   for `.img` frame headers. `arrayA`/`arrayB`'s semantics (most likely
   per-state hit-region or offset data, given the button widget's own
   separate position/size/texture fields are supplied elsewhere by
   `CreateButtonWidget`) weren't pinned down further — the exact XFS entry
   name this reads from is also passed in via a register set by this
   function's own caller (not visible to the decompiler) rather than
   hardcoded here, so it wasn't traced to a specific archive filename in
   this pass. The byte-level record shape itself is fully confirmed
   regardless.
3. **`CreateButtonWidget`** (`0x406020`, was `FUN_00406020`) is the actual
   per-button object constructor — allocates an 80-byte heap object with a
   **shared vtable** (`vtable_ButtonWidget`, `0x551e44`), storing position/
   size, resolving its texture via `FindPreloadedTextureByName`, and setting
   an initial visual state (`"disable"`/`"active"`/`"ready"` — the same
   state-name strings recurring throughout the whole codebase). Confirmed
   called from nearly every state's `OnEnter` (Server Select, Room List,
   Avatar Store, Ready Room, Loading — Title is a notable exception, matching
   its earlier-confirmed lack of any UI beyond the splash timer).

   **`vtable_ButtonWidget`'s 5 slots, dumped and checked** while chasing the
   removal-flag question above: slot 0 is the confirmed MSVC "scalar
   deleting destructor" (real destructor + conditional `free`, exactly
   matching how the container's sweep functions call it); slot 1 manages
   animation/timing fields, not the removal flag; slots 2 and 3 both
   render via the same generic `FindSpriteFrame` texture-cache lookup already
   documented (confirming buttons draw via targeted lookup, consistent
   with there being no per-frame "draw everything" sweep — see the
   traversal-functions note below); slot 4 is a bare `RET`, a shared
   no-op like several other vtables in this codebase.

   **Slots 2 and 3, fully decompiled this pass:** slot 3 (`0x405ea0`) is
   the actual draw call — reads the button's stored frame index (`+0x30`,
   skipped entirely if negative, the standard hidden-widget sentinel) and
   position (`+0x38`/`+0x3c`), then dispatches through the same
   `FindTextureCacheEntryByName`-adjacent lookup (`FindSpriteFrame`) and
   `BlitSprite16bpp`/`BlitSpriteClipped` branch used everywhere else in
   the software-blit layer — nothing button-specific about the actual
   pixel path. Slot 2 (`0x405e90`) just forwards to `FUN_00450730`, which
   turns out to be a **generic, reusable sprite-animation ticker**, not
   render code at all: given a per-object animation-state block (enabled
   flag, current-frame index, frame timer, "finished" flag) and a pointer
   to a shared animation-definition table (per-animation arrays of
   per-frame duration, frame count, and a loop-or-clamp flag), it advances
   the frame timer each tick, rolls over to the next frame once the
   current frame's duration elapses, and either wraps to frame 0 (looping
   animations) or clamps at the last frame and sets the "finished" flag
   (one-shot animations) — writing the resolved sprite/texture value into
   the object's own frame-index field (`+0x30`, the same field slot 3
   reads to draw) each time. This is the mechanism behind every blinking/
   animated UI icon in the game (button hover states, the Loading
   screen's blinking still-loading icon, etc. likely all drive the same
   per-frame value through this one function), confirming the animation
   and draw responsibilities are cleanly split: slot 2 advances state,
   slot 3 just draws whatever frame index is currently stored. **None of the
   object's own 5 vtable slots set the removal flag** the sweep function
   checks — whatever marks a button "done" (a close-button click handler,
   a screen-transition teardown, or similar) lives outside the object
   itself and wasn't tracked down this pass; that would need a broader
   search across UI click-dispatch code rather than this object's own
   vtable.
   **Confirmed by checking `State02_ServerSelect`'s own vtable**
   (`vtable_State02_ServerSelect`, `0x5570f0`): every slot besides the
   destructor/`ProcessPacket`/`OnEnter`/`OnExit` turned out to be a
   connection-state machine tick (`FUN_004e1960`: advances a socket
   connect attempt, updates a button's label between `"active"`/`"ready"`
   strings, builds outgoing packets `0x1000`/`0x1100`) or an input
   handler (`FUN_004e1430`/`FUN_004e1170`: `WM_KEYDOWN`/click dispatch for
   picking a server slot) — **none of them draw anything**. Server Select
   has no bespoke render/tick-draw function at all; its entire visual
   content is whatever the generic `ButtonWidget`/label-widget objects
   created in `OnEnter` render through their own vtable slots (slot 3,
   documented above). This is a second confirmed instance of a state
   with no "draw everything" override, reinforcing the pattern already
   suspected from the traversal-functions note below.

   **Full render breakdown, since "how does Server Select actually get
   rendered" was investigated directly.** Three pieces, all generic:
   - **Background**: `State02_ServerSelect`'s slot 15 (`0x443570`) is the
     exact same trivial one-line function shared by Title and Logo1 (see
     the per-state vtable survey above) — decompiled in full this pass:
     it just calls the standard texture-cache lookup (`FindSpriteFrame`) and
     blits sprite index 0 at the origin via `BlitSprite16bpp`/
     `BlitSpriteClipped`. Not state-specific at all — "draw whatever
     background sprite is currently loaded," reused verbatim by three
     different screens.
   - **Buttons**: `OnEnter` (`0x4e14b0`) creates exactly **3** buttons via
     `CreateButtonWidget` — `b_server_exitgame`, `b_server_buddygame`, and
     `b_server_choiceserver` (the last one created **initially disabled**,
     `enabled=0` vs. `1` for the other two — it presumably enables once a
     server connection succeeds). These draw themselves through the
     already-documented generic active-object sweep, same as everywhere
     else.
   - **A real scroll-list server browser + select→connect state machine.**
     (Corrects an earlier draft here that claimed
     `this+0x68` is never written — the write lives in `ConnectToSelectedServer`, a
     *non-vtable* helper called by the input handlers, which was missed on
     the first address-range pass.) **Opcode `0x1102` populates a real,
     richly-structured, up-to-16-entry server list** (server ID, name,
     description, **packed IPv4 address**, port, current/max player counts,
     online flag — full wire format and field offsets in PROTOCOL.md).
     There are two selection fields on the state object:
     - `this+8` = **highlighted slot** (UI cursor), initialized to `-1`;
       the Enter-key handler (`FUN_004e1430`) auto-sets it to the **first
       online server** when nothing is highlighted.
     - `this+0x68` = **slot currently being connected to**, initialized to
       `-1` in `InitGame` (`g_gameStateVTableArray[2]+0x68 = 0xffffffff`),
       **not** `0`.

     Both the click handler (`FUN_004e1170`) and the Enter handler
     (`FUN_004e1430`), after checking the highlighted server is online and
     not full, call `ConnectToSelectedServer(this)`. That helper `sprintf`s the packed
     IP as `"%d.%d.%d.%d"`, opens a socket to `ip:port` via `BeginServerConnect`,
     and writes **`this+0x68 = <highlighted index>`**. When the server acks
     (opcode `0x2001`, `*payload==0`), the client reads the entry at
     `this+0x68`, copies its `serverId`/`name` into globals, and
     `ChangeGameState(3)` into that server's Game Room List. Opcode `0x1012`
     stores a per-slot error code at `this+(*(this+0x68))*4+0x28` on failure.

     So the client-side *data* and the *select→connect→confirm* protocol
     for a real multi-server browser are completely implemented and
     exercised.

     **Correction — there IS a scroll-list picker after all.** An earlier
     revision of this bullet claimed "the visual list picker is absent; no
     per-entry row widgets or list-viewport rendering exist." That was
     wrong. It only inspected the state's own vtable slots plus the three
     `CreateButtonWidget` calls in `OnEnter`, and missed that `OnEnter` also
     calls **`FUN_005099d0(&DAT_00e53c40)`** (called from nowhere else),
     which builds a full **scroll-list panel** via the generic UI-widget
     system:
     - `FUN_005099d0` creates a ~545×530 panel with two panel buttons (msgs
       `0x44c`/`0x44d`) and a **scroll-list widget** (`FUN_005080a0`, class
       vtable `0x557e90`, 0x58-byte object) that auto-creates its own
       **up/down scroll-arrow** child buttons.
     - The widget has a **draggable scrollbar thumb** (`FUN_0050f500`
       mouse-down grabs the thumb, `FUN_0050f460` drags it) and an
       arrow/step handler (`FUN_0050f7c0`, ±1 clamped to `total − page`);
       any scroll change fires a `0x2000`+position callback to the parent
       panel (`FUN_0050d810`), which writes the scroll offset into the
       ServerSelect state (`g_gameStateVTableArray[2]+0x14`/`+0x18`) and
       issues a paged server request (`0x1100`/`0x1101`).
     - So the server list is a genuine **scrollable, server-paginated
       list** — the client requests a page at the current scroll offset and
       the server returns 16 entries via `0x1102`. `OnEnter` seeds the
       initial scroll offset from the registry `LastServer` value ÷ 16.

     **Per-row draw and row-click selection are now both traced.** The
     **`WorldListPanel_Draw`** (`0x50dc40`) loops the server count calling
     `RenderWorldListRow` (`0x50dc80`) per row: a 2-column grid (247px column
     / 73px row pitch), a background sprite shaded by selection state
     (state 3 when the row index == the highlighted slot `state+8`), the
     server number (`sprintf`+`BlitRLESprite`), the name and two description
     lines (`BlitRLESprite`, colour `0xb77f`), and a population gauge
     (`currentPlayers·100/maxCapacity` bucketed via thresholds at
     `g_fullnessGaugeThresholds`). Row selection: the panel's mouse-down
     (`WorldListPanel_OnMouseDown`, `0x50d5a0`) calls `WorldListRowHitTest`
     (`0x50df40`) — same grid geometry, online rows only — and writes
     `g_gameStateVTableArray[2]+8 = <clicked row>`, enabling the connect
     button. So clicking a row selects it and clicking SERVER connects; the
     Enter key still auto-selects the first online server. The broader
     "smaller private-server build" framing does not apply to this screen —
     the multi-server browser UI is real and complete, not vestigial.
   - **Also touches the whisper-messaging TCP connection.** `OnEnter`
     checks `DAT_007934f4` (the same "direct connection" global from
     the newly-documented Channel 3/whisper investigation in
     PROTOCOL.md) and branches to different init calls (`FUN_00405ba0`
     vs. `FUN_00404410`) depending on whether it's already set — the
     first confirmed evidence of where that connection's lifecycle is
     managed, though the actual `connect()`/`socket()` call establishing
     it still wasn't located.
4. Every constructed button is registered via **`RegisterActiveObject`**
   (`0x4f2fb0`, was `FUN_004f2fb0`) into a **sorted tree/list structure**
   keyed by two levels (a layer/z-order value, then a secondary key) — and
   this insertion logic structurally matches the *exact same* sorted-
   container pattern already confirmed for `PostTurnEvent`'s underlying
   insert function (the turn-event scheduler). This is a genuinely elegant,
   unifying architectural finding: **the engine has one reusable generic
   sorted-container primitive, reused for both the time-keyed turn-event
   queue and this layer-keyed active-object/render registry** — not two
   independently-implemented data structures.

### The Widget base class's own mouse/draw dispatch (0x505-0x50f cluster)

Separate from `ButtonWidget` (the flat, non-hierarchical widget documented
above), the panel system (`Panel_BaseConstructor`, `Build*Panel` — chat logs,
world list, buddy list, avatar store) uses a genuine **tree-structured Widget
base class** with a child array and a much larger vtable. Named this pass:

- **Mouse dispatch, children-first.** `Widget_OnMouseDown` (`0x50e420`) and
  `Widget_OnMouseUp` (`0x50e4c0`) are the base class's own handlers: each
  first delegates to `Widget_MouseDownChildren`/`Widget_MouseUpChildren` (walk
  the child array), and only if no child consumed the event does it hit-test
  its own bounds (`+0x28..+0x30` x/width, `+0x2c..+0x34` y/height) and invoke
  its own click vtable slot (`vtable[0]`). `Widget_OnMouseDown` also tracks a
  drag-eligibility flag (`+0x39`) gated on a modal-lock field (`+0xe`).
- **Draw, two parallel recursion paths.** `Widget_DrawChildren` (`0x50e520`,
  named earlier) calls each child's vtable slot `0x20`. A second, structurally
  identical helper, **`Widget_DrawChildrenDeep`** (`0x50ecf0`), calls slot
  `0x24` instead — used by leaf/row-style widgets (`Widget_DrawSelf`
  `0x505430`→`0x5054b0`, `ScrollListWidget_DrawThumb` `0x50e090`) that paint
  their own content with raw `FindSpriteFrame`+blit calls first, then recurse
  into their own children via this second path. The two draw slots (`0x20`
  vs `0x24`) most likely correspond to `Draw` at different vtable indices in
  different subclasses (an intermediate class adding virtuals shifts the
  slot), rather than two semantically different draw passes — not fully
  confirmed.
- **`Widget_DrawSelf`** (`0x5054b0`) — draws a widget's own sprite frame
  (`+0x48` frame index, `+0x28`/`+0x2c` position, gated on the `+0x1e`
  hidden flag) then calls `Widget_DrawChildrenDeep`. Callers are exclusively
  list-row renderers (`RenderChannelUserRow`, `RenderReadyRoomChatRow`) —
  this is the shared "row background" draw helper.
- **`ScrollListWidget_DrawThumb`** (`0x50e090`) — draws the scrollbar thumb
  as three pieces (top cap frame 0, a tiled body of frame-1 segments sized by
  `ScrollListWidget_ThumbHeight`, bottom cap frame 2), then also recurses via
  `Widget_DrawChildrenDeep`.
- **`RadioGroup_OnMouseDown`** (`0x505430`) — a container click handler: hit-
  tests itself, then walks its children for type-`2` entries (radio buttons),
  invoking the first one whose "selected" flag is unset, or the currently-
  selected one if any is already set — the click-to-select behavior behind
  the room-option/settings radio groups.
- **`Widget_SetChildRange`** (`0x505520`) — finds a child by index
  (`Widget_FindChildIndex`), sets a `min`/`max`-shaped pair on it (`+0x38`/
  `+0x3c`), and enables/disables it based on the sign of the new value —
  matches a scrollbar or slider's range-update call.
- **`WidgetChildArray_Destroy`** (`0x50e560`) — a real MSVC destructor
  (installs its own vtable pointer at entry, the standard dtor pattern),
  recursively frees a nested array of child widget pointers.
- **`PanelManager_Unregister`** (`0x50ef10`) — the counterpart to
  `PanelManager_Register`: finds a panel by its `(x, y)` key in the manager's
  linked list, unlinks it, and — once the manager's registered-panel count
  hits zero — calls **`PanelManager_ReleasePool`** (`0x509fd0`), which drains
  a free-node pool and fully resets the manager (matches `PanelManager_Register`'s
  own node-allocator, `0x50f350`, being pool-backed).

**This answers the original open question**: Title/Logo/ServerSelect (and
every other screen) don't need bespoke per-state render code because their
buttons/dialogs are just objects registered into one shared active-object
list during `OnEnter`, and — while the exact function that *iterates* this
list once per frame to call each object's draw method wasn't isolated in
this pass — the architecture is now clear enough that this is a "find one
more function" task rather than an open architectural question. The
movement-related cursor/sound-effect object found earlier in the physics
investigation (`FUN_004368f0`) registers into this same list via the same
`RegisterActiveObject` call, confirming buttons, dialogs, and transient
sound/cursor effects are all instances of one common "active game object"
concept in this engine, not separate systems.

### Remaining open threads

1. ~~`g_spriteVertexBuffer`'s exact per-vertex field layout~~ — **resolved**,
   see the "Per-vertex field layout" writeup above: `FVF 0x244` = XYZRHW +
   Diffuse + TEX2, 9 dwords/vertex, quad = 2 triangles sharing a diagonal.
2. Whether the Z-buffer is actually used for depth-sorting (vs. just present
   because the HAL device requires one) — **now checked exhaustively
   across every function that references `g_spriteVertexBuffer`, not just
   a sample.** The original xref list had 24 functions; decompiling all of
   them showed only 21 actually **construct** vertices (write into the
   buffer via the `&DAT_00ea0e28`-based scratch-copy pattern) — the
   remaining 3 (`FUN_00450c20`, `State11_InBattle_RenderModeIcons`,
   `State09_ReadyRoom_RenderCharacterPreview`) turned out to be
   flush/dispatch sites that only call `DrawPrimitive`, not vertex writers
   (consistent with `FlushSpriteBatch`, the confirmed flush function). Checked
   every one of the 21 constructors' copy-source scratch region for a
   write to whatever address maps to the `Z` slot in its own layout,
   confirmed per-function rather than assumed. **Zero writes to any of the
   three per-vertex `Z` addresses across all 21** — every one of them
   writes position/diffuse/UV fields but leaves `Z` untouched every time
   (one function, at first glance, looked like a counter-example —
   `DAT_00ea0ea8 = 0x3b23d70a` — but mapping that address through its own
   copy layout showed it lands on a texture-U coordinate, not `Z`, once
   decoded: `0x3b23d70a` ≈ `0.0025`, a small UV offset, not a depth value).
   No explicit `SetRenderState(D3DRS_ZENABLE/ZWRITEENABLE, ...)` call was
   found either, for what it's worth. This is now a complete sweep of every
   function that touches `g_spriteVertexBuffer`, not a sample — as close
   to a settled "no" as static analysis alone can give. The one remaining
   gap is genuinely un-closeable without dynamic analysis: confirming
   whether the device's default `ZENABLE` state (never explicitly set
   either way in this code) resolves to on or off at runtime.
3. ~~The developer-name chat easter egg~~ — **resolved**, see the writeup
   above: a full `/`-command parser with a real staff-credits list plus
   several genuine hidden debug/GM commands, three obfuscated via
   Korean-keyboard-layout romanization. What the *server* does with the
   three debug commands' outgoing packets remains untraced (needs server
   code).
4. ~~The function that **iterates** the active-object registry once per
   frame~~ — **resolved (reframed then answered).** Traced `CreateButtonWidget`'s
   call site raw disassembly to see exactly what it passes as
   `RegisterActiveObject`'s registry argument: `MOV EDX,[ESP+8]` — one of
   `CreateButtonWidget`'s own stack parameters, not a hardcoded constant —
   and that value resolves to the same `&DAT_00ea0e18`-family global
   already documented elsewhere in this codebase as the root of a
   generic keyed-object tree used for texture/resource cache lookups (the
   tree-root formula, `*(int*)(*(int*)(root+4)+0x1c)`, is textually
   identical in both `RegisterActiveObject` and the texture-lookup helper
   `FindSpriteFrame`). That means "active render objects" and "cached
   resources looked up by ID" most likely live in **one shared generic
   container**, not two separate systems with their own insert/iterate
   pair — reinforcing the "one reusable sorted-container primitive" finding
   already made for the turn-event queue. Given that, a single dedicated
   "walk every active object and draw it" function may not exist as a
   distinct routine at all — every draw call site seen so far (including
   the many small per-icon `BlitSprite16bpp`/`BlitSpriteClipped` dispatches
   found throughout the UI code) does its own **targeted lookup by a known
   key**, not a full in-order sweep.

   **Follow-up done: yes, a full traversal exists — for lifecycle
   management, not rendering.** Decompiled the small cluster of functions
   sitting right next to `RegisterActiveObject`/`FindSpriteFrame`
   (`0x4f3020`-`0x4f3150`) and found the rest of this generic container's
   function suite. The structure turns out to be bucket-chained (each
   bucket reached via a `[7]`-indexed "next bucket" pointer, each bucket
   holding a linked chain of entries via `[4]`/`[3]` next/prev pointers) —
   closer to a hash table with chaining than a plain binary tree. Three
   full-sweep functions exist:
   - **`FUN_004f3100`** — walks every bucket and every chained entry; for
     any entry whose flag byte (`+5`) is set, **unlinks it from the chain
     and calls its vtable slot 0** (the classic MSVC "scalar deleting
     destructor" pattern, called with argument `1`). This is a **garbage
     collector for objects flagged for removal** — the real per-sweep
     consumer of whatever marks a button/widget as "done."
   - **`FUN_004f3020`** — walks every bucket, calls vtable slot 0 on
     *every* contained entry unconditionally, then empties each bucket's
     chain (resets its sentinel links) without freeing the buckets
     themselves — a **destroy-all-entries, keep-the-container** operation.
   - **`FUN_004f3060`** — near-identical to `FUN_004f3020` but also
     destroys each bucket header itself and resets the container's own
     head/tail pointers — the **full container teardown**, almost
     certainly called once at shutdown or state teardown.
   This resolves the reframed question: a real "walk everything" pass
   does exist for this shared container, but its job is destruction/
   cleanup of flagged or all entries, not per-frame drawing — consistent
   with every draw call site being a targeted lookup, as found above.
   Which specific event sets an entry's removal flag (a button being
   closed, a transient effect finishing, etc.) still wasn't traced, but
   **found where the flagged-entry sweep gets called from**: while fully
   decompiling State11's vtable slot 9 (see below — it turned out to be
   much more than just cursor logic), `FUN_004f3100()` shows up as a
   plain, unconditional call in the middle of that function's straight-line
   per-tick body. Since slot 9 is confirmed to run every `GameTick`
   (~50ms), this means **the flagged-object garbage collector runs once
   per tick, unconditionally** — not on some rarer lifecycle event as
   might have been assumed. The other two sweep functions'
   (`FUN_004f3020`/`FUN_004f3060`, the destroy-all and full-teardown
   variants) call sites weren't found in this same function and remain
   untraced.
5. ~~`LoadButtonDefinitionFromXFS`'s binary widget-definition format~~ —
   **resolved**, see the writeup above: `count`, then per-record
   `nameLen`/`name`/`typeByte`/`subCount`/two `subCount`-length dword
   arrays. Semantics of the two trailing arrays remain unconfirmed.
