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
call for (`tools/score.sh` per function) — `tools/promote.sh` now exists
(see below) and three methods have recorded scores, but most of the tree
is still unverified, so "promoted" here mostly still means "written and
layout-asserted," not yet "byte-verified." Treat that gap as the real
remaining Phase 1 work before moving to Phase 2, rather than rewriting 1-5
from scratch.

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

**Byte-compare pass: started (2026-07-11).** `tools/promote.sh` now exists
(compile-one-file + `score.sh` in one command). First three `CWidget`
methods checked:
- `SetFocus` (`0x50e860`): **0/300 - perfect byte match**, the first
  confirmed in this tree.
- `Draw` (`0x50e520`): **105/2200**, effectively perfect - every
  instruction matches except the unresolvable AtlThrow call target (no
  relinked image exists to resolve cross-function call targets, see
  tools/README.md). Getting from an initial 850 down to 105 took two
  source-shape changes with no behavioral difference: caching
  `m_children.GetCount()` into a local before the branch, and declaring
  the loop index `i` outside the `if` rather than inside it - both changed
  MSVC 7.1's early-exit codegen even though the C++ semantics are
  identical. Documented inline in Widget.cpp since it's non-obvious and
  will recur for every other child-broadcast method in this file.
- `HitTest` (`0x50e9c0`): **645/5700**, same loop fix applied (905→645)
  but not fully closed - the remaining delta is in how the chained
  `a && b && c && d` rect-test expression accumulates into `hit` (register
  vs. stack temp), not yet chased down.

**Update (2026-07-11, later same day): Widget.cpp's byte-compare pass is
essentially done.** Applied the same loop-hoist fix to the remaining six
child-broadcast methods (all now effectively perfect - every instruction
matches, remaining score is purely unresolved call-target relocations):

| Method | Before | After |
|---|---|---|
| `DispatchKey` | 485/4500 | **105/4500** |
| `DispatchMouse` | 485/4000 | **105/4000** |
| `MouseMoveChildren` | 695/4400 | **105/4400** |
| `MouseDownChildren` | 695/4400 | **105/4400** |
| `MouseUpChildren` | 695/4400 | **105/4400** |
| `MoveBy` | 530/3500 | **210/3500** (2 unresolved call targets) |
| `SetEnabled` | 590/3000 | **210/3000** (2 unresolved call targets) |

Also rewrote `OnCommand`'s `evt==0x1100/0x1101/0x1102` dispatch from an
if/else-if chain to a real `switch`: MSVC 7.1 only emits the original's
dense subl-then-decrement jump sequence for an actual switch statement,
not sequential compares. **13120 → 8175/17900** - the dispatch prologue
and all three branches are now instruction-for-instruction identical;
remaining delta is register allocation (`ebx`/`ebp` vs `esi`/`edi`),
not chased further. `AddChild` (2380/3200, worst *ratio* in the file at
25.6%) is confirmed unfixable from portable C++: the original takes
`this` in EBX, not ECX.

**Update (2026-07-11, item 1-2 done): `HitTest`'s delta investigated
further, confirmed as a genuine dead end** - tried rewriting the chained
`a && b && c && d` as an explicit if/else instead of one expression;
MSVC 7.1 produces byte-identical output either way, so this is a
register-allocation heuristic difference (where `hit` lives during the
chain), not a source-shape issue like the loop-hoist fix. Everything
that matters (every branch, every vtable call, the full child loop) is
confirmed correct - not chased further.

**`Label.cpp`/`EditBox.cpp`/`ButtonWidget.cpp`: scored and fixed.**

| File | Method | Before | After |
|---|---|---|---|
| Label.cpp | `Draw` | (loop fix) | **105/3500** |
| Label.cpp | `OnMouseDown` | 2850 | **105/6900** |
| Label.cpp | `CreateLabelWidget` | — | 550/3600 (ctor scheduling, see below) |
| EditBox.cpp | `Draw` | 660 | **315/3800** |
| EditBox.cpp | `CreateTextEntryWidget` | — | 1780/4200 (ctor scheduling) |
| ButtonWidget.cpp | `CreateButtonWidget` | 4060 | 3520/7700 (see finding below) |

Two new fix patterns found, on top of the loop-hoist/switch ones:
- **Recomputed vs. cached boolean.** `CLabel::OnMouseDown` had a
  `bool inside = <rect test>;` cached and reused twice; the original
  recomputes the whole rect-test chain a second time for the final
  return instead of caching it. Caching costs real diff score. Combined
  with switching `if (ResetPressState(...)) return true; return inside;`
  to `return ResetPressState(...) || <rect test>;` (one shared epilogue,
  matching the idiom `ResetPressState`/`OnDragMove` already use) -
  2850 → 105/6900.
- **Address computed early vs. inline.** `CEditBox::Draw` computes
  `m_text`'s address inline at each of its two use sites; the original
  computes it once, early, and reuses it. Caching into a local pointer
  up front: 660 → 315/3800.

**A real bug found and fixed, not just a score improvement.**
`CButtonWidget` (`ButtonWidget.h`/`.cpp`) had no constructor - every
field got poked unconditionally in the factory after `new
CButtonWidget()`, with no null-guard. The original genuinely
null-guards this block (skips all the zero/-1 init if `operator new`
returns null), the same "guarded ctor + unguarded pokes" idiom already
documented for CLabel/CEditBox. Added a real `CButtonWidget(int layer,
int id)` constructor so the compiler's own new-then-construct-if-
non-null codegen reproduces this for free - 4060 → 3520/7700.

**Two confirmed-unfixable deltas, same category as `AddChild`'s EBX
`this` mismatch:**
- `CreateLabelWidget`/`CreateTextEntryWidget`/`CreateButtonWidget`'s
  remaining score is constructor field-write *scheduling* (the
  vtable-pointer write, and a couple of other field writes, land at
  different relative positions) - a compiler-internal heuristic, not
  reproducible from source-level reordering (member-initializer-list
  order is forced to declaration order in real C++, unlike the
  backend's store-scheduling freedom). Tried once for
  `CreateLabelWidget`, no source variant changed it; not chased further
  for the other two either.
- `CButtonWidget`'s `RegisterActiveObject` call site is structurally
  different from what's declared here: the original computes its first
  argument from a **global** (`*(int*)0x5b3484 + 0x67ec70`), not from
  `CreateButtonWidget`'s own `registry` parameter, and its calling
  convention isn't ordinary `__cdecl`/`__stdcall` (no stack cleanup
  after the call). The `registry`/`layer` parameter pair in the current
  signature may not be the real shape of the original's first two
  arguments at all - this needs `RegisterActiveObject`'s own
  reconstruction (item 5 below) to resolve properly, not a factory-level
  fix.

All six functions above are wired into `tools/gen_cxx_score_report.py`'s
`FUNCS` list (21 total now) for the CI artifact.

**`ScrollBar.cpp`: scored and partially fixed (2026-07-11).**

| Method | Before | After |
|---|---|---|
| `OnMouseUp` | — | **105/4300** (already effectively perfect) |
| `ThumbHeight` | 645 | 535/2200 |
| `Draw` | 2344 | 1744/10800 |
| `OnCommand` | 2380 | 2235/5100 |
| `IsOverThumb` | — | 1350/3200 |
| `OnMouseDown` | — | 1671/9300 |
| `CreateScrollListWidget` | — | 3900/8400 |

One new confirmed-unfixable category found: `ThumbHeight`/`IsOverThumb`
both have their own class-comment note that `this`/`y` arrive in
`EAX`/`EBX` rather than the normal register - same "not reproducible
from portable C++" family as `CWidget::AddChild`'s EBX `this`. The
other four still have real, un-chased deltas (branch-ordering/polarity
mismatches, the `hit`-in-register-vs-stack pattern from `HitTest`, and
the by-now-familiar ctor field-write-scheduling category) - diminishing
returns past the fixes already applied (loop-hoist on `Draw`; caching
`m_height` and matching the `h >= 10` boundary on `ThumbHeight`;
rewriting two clamps as the branchless `x & ((x < 0) - 1)` bit-trick
Ghidra's own decompile of `OnCommand` showed literally, on `OnCommand`
and `Draw`'s page-up path). One near-miss worth flagging for whoever
picks this up next: a manual asm-differ read of `OnCommand` looked like
the "any other id" fallback used the raw `id` value instead of the
hardcoded `1` already in the source - re-decompiling `0x50f7c0` fresh in
Ghidra confirmed the existing `newPos = 1;` was correct and the asm read
was a stack-offset misread. Worth remembering: **verify against a fresh
Ghidra decompile before "fixing" a suspected logic bug from raw asm
alone** - the compiler's own reordering can make stack slots read like
different values than they are.

**`Panel.cpp`: scored (2026-07-11, all 16 addressable methods).**
`HandlePress` (105/7000) and `CPanel::OnMouseDown` (210/5200) are
effectively perfect. `RowHitTest` improved 2510 → 1815/5600 (writing the
row/column split as `i % 2`/`i / 2` instead of a mixed `&`/`/` form
matched the original's full signed-modulo codegen) with a confirmed
register-convention ceiling beyond that (`retl $4` vs `$8` proves one
argument arrives in a register). The nine `Build*Panel` factories all
carry the by-now-familiar guarded-ctor field-write-scheduling delta
(5 total confirmed instances of that category across the whole tree
now) - not chased individually. Three outliers were NOT diffed in depth:
`CWorldListPanel::OnMouseDown` (6475/12800), `::OnCommand`
(30589/33200), and `BuildCreateRoomDialog` (37925/46000) - all three are
dominated by the `DAT_00e9be94` flat-ButtonWidget registry walks this
file's own comments already flag as blocked on `RegisterActiveObject`'s
reconstruction (item below); revisit once that lands.

**A real bug found in the tooling itself, not the reconstruction.**
`gen_diff_report.py`'s `find_symbol_and_size` matched hints by a bare,
truncated-at-first-`@` name - fine for the raw-C report (one function
per file, decorated names truncate to something globally unique in
practice) but silently WRONG for C++ mangled symbols, where two
different methods sharing a bare name across classes (e.g.
`CPanel::OnMouseDown` and `CWorldListPanel::OnMouseDown`) both truncate
to the same string. It picked whichever came first in the object's
symbol table, meaning `gen_cxx_score_report.py` would have silently
scored one method's bytes against the OTHER's address range. Fixed:
try an exact full-string match first; only fall back to the bare-name
heuristic when it resolves to exactly one candidate, and refuse (return
`None`) rather than guess when it's ambiguous. Every score number
actually *reported* in this session's commits was still correct - they
all came from `tools/score.sh`/manual `diff.py -e` calls with the exact
mangled symbol passed directly, never through the buggy path - but the
CI report generator itself had never been exercised against a file with
overloaded method names until `Panel.cpp`, so this was a real latent bug
worth catching before it produced a wrong report silently.

**Remaining Phase 1 work:**
1. `RegisterActiveObject`'s sorted-container reconstruction (also
   needed to resolve `CButtonWidget`'s open registry/calling-convention
   question, and the three `Panel.cpp` outliers above);
   `LoadButtonDefinitionFromXFS`'s promotion.

With `Panel.cpp` done, every `.cpp` file in `src/cxx/` (except
`GameState.cpp`/`GameStateMachine.cpp`/`State0*.cpp`, which are Phase 2+
territory) has now been through at least one score→diff→fix pass. Phase
1's widget-system byte-verification is functionally complete modulo the
known-blocked items above.

Each pass: compile → `tools/promote.sh`/manual `score.sh` sweep → diff
the worst offenders → apply confirmed-safe fixes → re-verify → add
entries to `tools/gen_cxx_score_report.py`'s `FUNCS` list so CI picks it
up → commit. Once this list is clear, move to Phase 2.

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
- ~~A tiny `tools/promote.sh` wrapping the compile + `score.sh` loop~~ —
  **done** (2026-07-11): `tools/promote.sh <cxx-source> <mangled-symbol>
  <start-VA-hex> <end-VA-hex>`. Symbol-mangling lookup is still manual
  (`llvm-objdump -t build/X_cmp.obj | grep MethodName` after a first
  compile) - not wrapped in the script.

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
