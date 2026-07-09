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

The most complete documentation, the smallest objects, and every function is
already a named port. Remaining work, in dependency order:

1. **The checked child container.** Every broadcast method inlines the same
   bounds-guard (`FUN_004010c0` = AtlThrow-style). Reconstruct the
   `ptr/size/cap` growable array (grow helper `0x50ed30`) as a small class
   (probably `CSimpleArray`-shaped) — this converts `ChildAt()` from a helper
   into the real `operator[]` and is what the remaining byte-diff deltas in
   HitTest/Draw hinge on.
2. **Base leaf behavior**: `MouseDownCommon` (`0x50e2f0`), `OnDragMove`
   (`0x50e3a0`), the leaf `OnCommand` default (`0x50eb10` — the
   focus-move/scroll bookkeeping), the shared dtor (`0x50e860`), label `Draw`
   (`0x50e350`, needs `FindSpriteFrame` extern only).
3. **Scrollbar remainder**: arrow-step handler family (`0x50f7c0`,
   `FUN_0050f660`'s ±1 stepping cousin), `OnMouseMove` drag tracking.
4. **Constructors**: `CreateLabelWidget`, `CreateTextEntryWidget`,
   `CreateScrollListWidget`, and the base `CWidget` ctor they all call.
   Requires (1). This is where `operator new` + vtable-install gets modeled,
   which unlocks…
5. **Panel subclasses**: `CWorldListPanel` first (it has `OnCommand`
   `0x50d810`, `OnMouseDown`, and the row renderer `RenderWorldListRow` all
   as named ports), then the other eight builders from the catalog. Each
   panel promotion carries its screen's widget-composition knowledge from
   docs/screens/*.md into a real constructor.
6. **The flat `ButtonWidget`** (separate 5-slot system, vtable `0x551e44`):
   `CreateButtonWidget`, `LoadButtonDefinitionFromXFS`,
   `RegisterActiveObject` — small, self-contained, evidence in
   docs/screens/README.md.

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
3. **Replay recorder** (`Replay_*` named ports + `WriteReplayEventRecord`).
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
