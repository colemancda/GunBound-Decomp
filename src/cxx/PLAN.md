# Plan: generating all the C++ we can currently infer

Status snapshot (2026-07-09): the raw C tree is fully green (syntax **and**
codegen sweeps 1781/1781), `src/cxx/` exists with the `CGameState` and
`CWidget` hierarchies layout-asserted against real MSVC 7.1, and ten methods
are promoted and byte-compared. This document is the roadmap for the rest —
ordered so every phase only depends on things already confirmed, and every
item names its evidence source.

**Ground rules** (from README.md, restated): MSVC 7.1 C++ mode; vtable order =
declaration order; every documented size/offset becomes a `GB_STATIC_ASSERT`;
every promotion is byte-compared with `tools/score.sh` where the function's VA
range is known; one commit per promoted unit; raw C ports stay in place until
their C++ replacement is byte-verified (the C tree is the reference, not dead
code).

---

## Phase 1 — finish the widget system (evidence: docs/widgets.md, named ports)

**Status update (2026-07-11): items 1-5 below turned out to already be
written** (`AtlArray.h`, `Widget.cpp`/`.h`, `ScrollBar.cpp`, `Label.cpp`,
`EditBox.cpp`, `Panel.cpp` — the last has all nine `Build*Panel` factories
plus `CWorldListPanel::OnMouseDown`/`OnCommand`), just never checked off
here. The whole tree (`cxx_selftest.cpp` + every `.cpp`) compiles clean
under real MSVC 7.1 via `tools/msvc-env` (`gb-msvc` docker image). What's
*not* yet done for 1-5 is the byte-compare pass this doc's ground rules
call for (`tools/score.sh` per function) — no `tools/promote.sh` exists yet
(see Tooling section) and no per-function score has been recorded in
comments, so "promoted" here means "written and layout-asserted," not yet
"byte-verified." Treat that gap as the real remaining Phase 1 work before
moving to Phase 2, rather than rewriting 1-5 from scratch.

1. ~~The checked child container~~ — **done**: `AtlArray.h`'s
   `CAtlArray<E>` (bounds-guard `operator[]`, `GrowBuffer` matching
   `0x50ed30` exactly, `Add` matching the `AddChild` throw-on-OOM shape).
   `CWidget::m_children` is `CAtlArray<CWidget *>`.
2. ~~Base leaf behavior~~ — **done**: `ResetPressState` (`0x50e2f0`),
   `OnDragMove` (`0x50e3a0`), leaf `OnCommand` default (`0x50eb10`),
   `SetFocus`/slot-10 (`0x50e860`), `CLabel::Draw` (`0x50e350`) are all in
   `Widget.cpp`/`Label.cpp`.
3. **Scrollbar remainder**: mostly done (`ScrollBar.cpp`, 217 lines,
   includes the arrow-stepper `0x50f7c0`) — spot-check against
   `FUN_0050f660`'s ±1 cousin and `OnMouseMove` drag tracking before
   considering this fully closed.
4. ~~Constructors~~ — **done**: `CreateLabelWidget`, `CreateTextEntryWidget`,
   `CreateScrollListWidget` all exist with the base `CWidget()` ctor.
5. ~~Panel subclasses~~ — **done**: `Panel.cpp` has `CWorldListPanel` (full
   `OnMouseDown`/`OnCommand`/factory) plus `BuildChannelUserListPanel`,
   `BuildReadyRoomChatPanel`, `BuildLobbyChatPanel`, `BuildAvatarStorePanel`,
   `BuildCreateRoomDialog`, `BuildBuddyPanel`, `BuildEnterRoomNumberDialog`.
6. **The flat `ButtonWidget`** — **done** (2026-07-11): `ButtonWidget.h`/
   `.cpp`, `CButtonWidget` (80-byte object, 5-slot vtable). Two of its five
   vtable slots turned out to be shared with unrelated classes and were
   already named (`DeletePoisonedBaseObject` slot 0, `NoOpMethod` slot 4);
   the other three were newly named this pass: `TickButtonAnimation`
   (slot 2, `0x405e90`), `DrawButtonWidget` (slot 3, `0x405ea0`), and
   `ResolveNamedState` (slot 1, `0x461c60` — corrects a prior misnaming
   as "ResolveObjectHandle"/a generic resource-handle resolver; it's
   actually a generic named-state string lookup, confirmed here as this
   class's `SetState(name)`, and cross-referenced as the same function
   Ready Room's base infra uses at vtable slot 19). `RegisterActiveObject`
   itself (`0x4f2fb0`, the sorted active-object list insert) is still an
   extern call, not reconstructed — same "own unit of work" scope note as
   the checked-container item above; it shares its node structure with the
   turn-event scheduler per ARCHITECTURE.md's "PostTurnEvent" note.
   `LoadButtonDefinitionFromXFS` (the XFS-backed button-definition loader,
   0x401440) is also still unreconstructed — a distinct, self-contained
   follow-up, evidence in docs/screens/README.md.

**Actual remaining Phase 1 work**: the byte-compare pass (build
`tools/promote.sh`, run `score.sh` per promoted method, record results),
`RegisterActiveObject`'s sorted-container reconstruction, and
`LoadButtonDefinitionFromXFS`'s promotion.

## Phase 2 — the state machine spine (evidence: ARCHITECTURE.md §CGameState)

1. **Shared plumbing**: `CGameState_BaseDestructor` (`0x426ac0`, the
   vtable-poisoning idiom), `_ScalarDeletingDestructor` (`0x4e5320`),
   `_NoOpVirtual_A/B` — as the base-class dtor and default virtual bodies.
2. **`ChangeGameState`** (`0x4122f0`) as a free function over
   `CGameState *g_gameStates[16]` — the deferred-transition globals are all
   named already. `InitGame`'s 16-object construction loop follows once the
   per-state ctors exist.
3. **Small states first**: `CState05Logo1`/`CState06Logo2`/`CState01Title`
   (all 8 bytes, OnEnter/OnExit ports exist), then `CState10Loading` (0x150,
   4 ports exist including its `ProcessBattleAction` at `0x43e440`).
4. **Blocker to clear early**: `FUN_004f1790` (active-object container prep)
   — every state's `OnEnter` calls it with unexplained EAX/EDI register
   arguments. Decompile + byte-compare it once; that unlocks exact matches
   for all nine `OnEnter`s.

## Phase 3 — per-screen field maps and dispatchers (evidence: docs/screens/*.md + PROTOCOL.md)

For each state, in this order (rising size): 02 ServerSelect (0x6c), 03
GameRoomList (0x294), 09 ReadyRoom (0x78c), 11 InBattle (0x2408), 07
AvatarStore (0x34818):

- Replace the opaque `m_raw` tail with real fields as each screen's doc pins
  offsets (each doc has a "state fields" section; State11's chat buffers are
  already offset-documented — note they hang off `g_clientContext`, so part
  of this is reconstructing the **per-connection client context** blob, which
  deserves its own header and is shared by many systems).
- Promote each state's `OnEnter`/`OnExit`/`OnCommand`/`ProcessPacket`/
  `ProcessBattleAction` (all named ports for 01/02/03/05/06/07/09/10/11).
  **Ordering caveat (learned on State02):** the big `ProcessPacket`
  handlers (State02's is 575 lines) touch several *other* `g_clientContext`
  sub-arenas beyond the one documented for that screen — State02's alone
  reaches `+0x23330` (peer-address block), `+0x3ae2c` and `+0xebee4`
  (checksum-state region), none of which are typed yet. Transcribing those
  as raw `*(u32*)(ctx+N)` pointer math gains nothing over the existing C
  raw port and risks transcription error, so promote a screen's
  `ProcessPacket` **after** its `ClientContext.h` slices exist, not before.
  The reconstructable-today part of State02's is the 0x1102 SoA populator
  (now readable via `ServerListSoA`); it lands with the arena work.
  **Update (arena work done):** `ClientContext.h` now types every
  data region State02's `ProcessPacket` touches — server-list SoA,
  room grid/player/inventory accessors, the `PeerEndpoint` record
  (+0x23330) and the per-player checksum-state array (+0xebef4). With
  the data model in place the remaining barrier is purely the size of
  the transcription (569 lines of packet arithmetic across ~6 opcodes);
  it's now a mechanical, unblocked promotion rather than a
  blocked-on-data one. Same applies to the other big handlers: type
  their screen's arena slice first (room-list slices already exist),
  then the handler is mechanical.
- The 15 not-yet-dumped state vtables: dump each `vtable_StateNN_*` in Ghidra
  the way State11 was done, so slots past 9 get declared before their
  bodies are promoted (Ready Room is known to have 20 slots).

## Phase 4 — protocol structures (evidence: PROTOCOL.md, no code needed)

A `Protocol.h` with the wire structs that are already fully documented:
channel-1/channel-2 packet headers, `RoomPlayerSlot` (opcode 0x2105),
`InventoryItem` (opcode 0x6002), the Fire (0x8403) battle-action payload, and
the per-opcode payload layouts in PROTOCOL.md's tables. All POD structs with
size asserts — zero behavioral risk, immediately useful to every
`ProcessPacket` promotion in Phase 3. Can be done any time, in parallel.

## Phase 5 — supporting subsystems (evidence: ARCHITECTURE.md sections)

Ordered by how confirmed their docs are:

1. **Active-object container** (`RegisterActiveObject`, the `FUN_004f3100`
   GC, the bucket walk already visible in `CState01Title::OnExit`) — small
   key→intrusive-list registry; unlocks cleaner OnExit promotions everywhere.
2. **Connection subsystem** (`CCommP2P`: the notify-window + thread-backed
   broker connect, §"Connection subsystem"; several named `src/network/`
   ports) — a real class with its vtable at `PTR_LAB_00557654`-family.
3. **Match recorder + peer broadcast** (`WriteReplayEventRecord` for the local
   `.sv` file; `QueueBroadcastEvent`/`BroadcastQueuedEvent`/`AppendBroadcastString`/
   `BroadcastBattleSnapshot` for the separate UDP peer-broadcast channel —
   two distinct systems, see ARCHITECTURE.md).
4. **XFS archive reader** (`src/fileformat/` — 8 named ports, format fully
   documented in FILEFORMATS.md) — likely a plain struct + free functions,
   possibly not a class at all; decide from the ctor pattern.
5. **Renderer objects** (texture cache entries, sprite frame headers —
   FILEFORMATS.md has the layouts; the D3D device chain stays C-style COM).

## Tooling (do alongside Phase 1)

- Extend the sweep to `src/cxx`: a `cxx_check` target compiling
  `cxx_selftest.cpp` + every `.cpp` under src/cxx with real MSVC (the current
  `*.c` sweeps skip the tree entirely). Wire it into
  `tools/msvc-env/_msvc_check_inner.sh` as a third mode.
- A tiny `tools/promote.sh` wrapping the compile + `score.sh` loop
  (symbol-mangling lookup included) to make the per-method byte-diff cheap.

## Known cross-cutting blockers

| Blocker | Blocks | Approach |
|---|---|---|
| `FUN_004f1790` register args (EAX/EDI) | exact-match of all OnEnters | **RESOLVED**: EAX = .img sprite-set name, EDI = .mp3 name; callee-cleans its two stack args (container, key). Residual is only the register loads themselves. |
| custom register conventions (`ThumbHeight` this-in-EAX, `IsOverThumb` y-in-EBX) | exact-match of a few widget helpers | likely compiler-internal/inlined-sibling artifacts; revisit after the container class lands |
| `__thiscall` C ports can't byte-match | everything not yet promoted | that's this whole plan |
| `g_clientContext` blob layout | State09/11 field maps, chat pipeline | reconstruct incrementally per-screen (Phase 3) |
| 15 undumped state vtables | slots >9 of those states | mechanical Ghidra pass, same as State11's |

## Effort shape

Phases 1–2 are days of steady promote-verify-commit work with today's
tooling. Phase 3 is the long tail (it *is* the game); each screen is
self-contained once Phases 1–2 land. Phases 4–5 are parallelizable filler.
The end state of this plan is NOT a linkable executable — it's every
*understood* function existing as byte-verified C++ with real class layouts,
which is exactly the input the eventual linker-script/full-image milestone
needs.
