# Reconstructed C source — status

## Scope: behavioral parity, not byte-matching (mostly)

The original plan for this repo was **matching decompilation**: write C
that recompiles under period-correct MSVC 7.10 (Visual Studio .NET 2003)
to byte-identical machine code, verified function-by-function against
`orig/GunBound.gme`. For most of this project that toolchain wasn't
available, so the fallback plan became **Winelib**: build the
reconstructed C as a native macOS binary using Wine's Win32-API-
compatible headers/libraries (`winegcc`), so real DirectDraw/Direct3D7/
DirectSound/DirectInput/Winsock calls can actually run without needing a
real Windows machine or MSVC. This still isn't byte-matching (Winelib
compiles with a modern GCC/Clang targeting the host's own architecture -
confirmed to literally be x86-64 SysV code in this environment's Docker
container, not even the same instruction set as the original 32-bit x86
binary), so it's **behavioral parity**: C that does the same thing as the
original function, verified by running it against real game data/
behavior and diffing the output — not by comparing compiled bytes
against the original binary. `PROGRESS.csv` marks functions done this
way as `PARITY-<file>` rather than the matching-decomp convention's
`DONE`, to keep the two kinds of "verified" distinguishable.

**Update: a real MSVC 7.10 toolchain is now available.** The Microsoft
Visual C++ Toolkit 2003 (a free, official, command-line-only release of
the same compiler/linker that built the original binary) was installed
in a Windows 11 VM (Parallels Desktop on the host Mac), confirmed via
`cl` with no arguments: `Microsoft (R) 32-bit C/C++ Optimizing Compiler
Version 13.10.3052 for 80x86` and `Microsoft (R) Incremental Linker
Version 7.10.3052` - both matching this project's own PE-header analysis
of `GunBound.gme`. The VM can reach this repo directly over a Parallels
shared folder (`\\Mac\Home\...`, mapped to a drive letter via `pushd`),
so no copy/sync step is needed - real matching-decomp builds are now
possible. `include/msvc/stdint.h` is a small shim providing `include/
ghidra_types.h`'s `stdint.h` dependency for this toolchain (MSVC 7.1
predates C99's real `<stdint.h>`, added in VS2010) - pass `/Iinclude\msvc
/Iinclude` (shim directory first) when compiling under this toolchain.
MSVC 7.1's C mode is strict C89 (no mixed declarations-after-statements,
no `for (int i = ...)` C99-style loop-variable declarations) - the
`lzhuf` module's hand-verified source has already been updated to be
C89-clean (declarations hoisted to the top of each block), confirmed to
not change behavior (still matches the Python reference decoder and
real archive data byte-for-byte) and to now compile clean under real
MSVC 7.1. Driving this VM is done via computer-use tooling (screenshots
+ clicks/pastes into a console window) rather than a scriptable shell -
slower per-command than the Docker/winelib workflow, but the only way to
get genuine byte-matching verification. (The `tools/msvc-env/`
Wine+Docker scaffold for a fully-scripted byte-matching pipeline is
still there and still relevant if a way to run real `cl.exe`/`link.exe`
non-interactively from this environment is ever found.)

**A real byte-comparison already paid off once.** Comparing
`InitLZHUFTree`'s real 162-byte machine code (both raw disassembly and a
fresh Ghidra re-decompile of just that address) against our hand-verified
C source found the source's `memset(text_buf, 0x20, ...)`/`s->r = N-F`
lines don't correspond to anything in that exact function - confirmed
empirically that the logic is nonetheless real and necessary (30 real
archive entries: 0/30 mismatches with it, 10/30 without), then traced
via a caller search (Ghidra's reference manager, not just guessing) to
where it actually lives: inline in the real `DecodeLZHUFBlock`
(`0x4eaba0`), immediately after its own call to `InitLZHUFTree()` - this
project's `lzhuf_decode_block()` (`src/lzhuf/DecodeLZHUFBlock.c`) is the
function that should "own" this logic by the original's boundaries, not
`lzhuf_init_tree()`. Left in place in `InitLZHUFTree.c` rather than
moved, since exact per-function ownership only matters for true
matching-decomp, not behavior - see both files' header comments for the
full writeup. This is exactly the kind of subtle bug that behavioral-
parity testing alone (matching output on the samples you happen to
test) can miss and real byte-comparison catches even without full
matching-decomp coverage.

**A real-MSVC compile sweep of `src/state_machine/` (38 files) found
another project-wide bug, plus several file-local ones.** Compiling
every file there with real MSVC 7.1 (`/O2`, via `tools/msvc-env/`)
surfaced errors gcc/winelib had been silently accepting as GNU
extensions:

- **`void *` pointer arithmetic** (`*g_pD3DDevice7 + offset`,
  `g_gameStateVTableArray[N] + offset`) - valid under gcc/clang's
  nonstandard "`sizeof(void)==1`" extension, a hard error under
  standard-conforming MSVC ("`'void *': unknown size`"). Fixed by
  retyping the affected globals (`g_pD3DDevice7`, `g_pDirect3D7`,
  `g_pDirectDraw7`, `g_pBackBufferSurface`, `g_pPrimarySurface`,
  `g_pZBufferSurface`, `g_pClipper`, `g_gameStateVTableArray`) from
  `void **`/`void *[]` to `char **`/`char *[]` - `char*` arithmetic is
  standard C with the identical one-byte-per-step semantics gcc's
  extension gave us, so this is a strictly more portable equivalent,
  not a behavior change. This fix wasn't state_machine-specific -
  these globals are used tree-wide, so it likely unblocks real-MSVC
  compiles of files outside this directory too, not verified this pass.
- **`__time32_t`** - Ghidra infers this type (the 32-bit `time_t` from
  post-split MSVC CRTs) for `time()` call sites, but MSVC 7.1 predates
  the 32/64-bit `time_t` split and has no such type in its own
  `<time.h>`. `include/ghidra_types.h` now typedefs it to `long` and
  redirects Ghidra's renamed `FID_conflict___time32` (the CRT's
  internal `_time32`/`time()`, whose real body lives in the excluded
  `msvc_crt_atl/` tree and was never actually linkable) to the real
  libc `time()`. Affects 12 files across the tree, not just
  state_machine.
- **A genuine array-vs-scalar mixup** in
  `state_machine/State09_ReadyRoom_ProcessPacket.c`: `DAT_00e9be94` is
  used as `*(int *)(DAT_00e9be94 + 0x1c)` (byte-offset-into-a-raw-
  address-value) in ~15 places across the tree, but this one file also
  used `DAT_00e9be94[7]` (array-subscript syntax) for the exact same
  offset (7 * sizeof(int) == 0x1c) - fine under gcc's looser
  scalar/array handling, a hard error under MSVC. Fixed locally at the
  three call sites in this file (explicit pointer casts) rather than
  changing the global's declared type, which would have broken its
  other byte-offset call sites elsewhere.

Net result: 32/38 files now compile clean under real MSVC (up from 28
before these fixes), matching gcc/winelib's own pass count exactly
(32/38 there too, confirming no regression from any of the above) -
the same 6 remaining failures in both compilers are the already-
documented sub-byte-field-access/raw-stack-offset files below, not new
problems. `State09_ReadyRoom_ProcessPacket.c` and
`State11_InBattle_OnEnter.c` are removed from the known-broken list
below as a result (the latter was already fixed in an earlier session
but never removed - caught while re-verifying this list against a
fresh compile pass, not by this specific fix).

## Layout: one file per decompiled function

Each original function gets its own file, named after its confirmed name
(or `FUN_<address>` if unnamed), with a header comment giving its
original address and a short description of what it does — mirroring
the convention used by community matching-decomp projects. Shared
per-module state (structs, internal-only declarations) lives in a
`<module>_internal.h` header; a `<module>_api.c` wraps the decompiled
functions in a normal malloc/free-based public API when the original
callers managed state/output buffers inline themselves (as LZHUF's do)
rather than through one clean entry point.

## What's here

- **`lzhuf/`** — the LZHUF decompressor used throughout `.xfs`/`.dat`
  decoding, split into one file per original function:
  - `GetBit.c` / `GetByte.c` — `0x4ea120` / `0x4ea1b0`, the bitstream reader.
  - `InitLZHUFTree.c` — `0x4ea300`, tree/ring-buffer setup.
  - `Reconst.c` — `0x4ea3b0`, periodic full tree rebuild.
  - `Update.c` — `0x4ea580`, adaptive frequency promotion.
  - `DecodeChar.c` — `0x4ea670`, Huffman tree walk for literals/lengths.
  - `DecodePosition.c` — `0x4ea6e0`, back-reference distance decode.
  - `DecodeLZHUFBlock.c` — `0x4eaba0`, the main LZSS unpacking loop.
  - `lzhuf_tables.c` — the static `d_code`/`d_len` decode tables
    (`DAT_0056dd30`/`DAT_0056de30`), not a function but data the above
    depend on.
  - `lzhuf_internal.h` — shared state struct + internal declarations.
  - `lzhuf_api.c` — public malloc/free-based wrapper (see `include/lzhuf.h`).

  All of the above ported from the already-validated Python reference
  (`tools/lzhuf/lzhuf.py`), itself derived from decompiling the real
  functions and fixing a transcription bug found along the way (see
  `tools/lzhuf/BUG_FOUND_wrong_decode_tables.md`). Verified byte-for-byte
  against the Python decoder on three real archive entries pulled
  straight from `orig/graphics.xfs` (`ChooseEvent.txt`, `bullet1n.img`,
  `avataimsi.img`).
- **`test_lzhuf.c`** — standalone CLI test driver, not part of the
  eventual game build; exists purely to validate `lzhuf_decode()` against
  real data without needing the rest of the game to compile.

### Raw/verbatim ports — every function in the game binary, 1,780 of them

Started from every function with a **confirmed real name** (92 of them,
outside `lzhuf/`) and cascaded outward four tiers, porting whatever
`FUN_<address>` helper each newly-added file referenced that wasn't
already ported (323, then 160, then 87, then 49 — each tier smaller as
the reachable set saturated). Once the cascade hit diminishing returns
(remaining "new" references turned out to be unresolvable vtable-slot
addresses, not real functions), switched to **porting every remaining
function in the binary regardless of whether anything already-ported
references it yet** — the direct route to the actual goal, a fully
buildable project, rather than only what's reachable by simple static
call-graph following (which can't see through vtable dispatch anyway).
That was ~1,600 more functions across five bulk batches.

**Net result: every function in `GunBound.gme`'s own code has raw C
source under `src/`**, except the statically-linked MSVC CRT/ATL
runtime (see the `msvc_crt_atl/` section below, deliberately excluded) —
1,780 raw ports plus 2 hand-verified `lzhuf/` functions, 1,782 total,
covering the entire ~1,782-function game-logic portion of the binary (1,782 = 2,326 total minus the 544 excluded CRT/ATL functions).
`PROGRESS.csv` tracks this: 0 remaining `TODO`. Named functions are
organized into subdirectories by subsystem; everything else lives flat
in `unnamed/`, addressed by `FUN_<address>` since nothing else is known
about most of them:

- **`entry/`** — `WinMain`, `InitGame`, `Shutdown`, `WndProc`, `GameTick`,
  `ChangeGameState`. Supersedes the old hand-written `main.c` skeleton —
  these are the *real* decompiled bodies now, not stubs.
- **`state_machine/`** — every `StateNN_*` function (`ProcessPacket`,
  `ProcessBattleAction`, `OnEnter`/`OnExit`, render functions) plus the
  shared `CGameState_*` base-class functions.
- **`network/`** — the packet-checksum family (`EncodeOutgoingPacketField`,
  `PeekPacketChecksumState`, etc.), `PostTurnEvent`, `HandleTurnTimeoutSlot`.
- **`replay/`** — `Replay_AppendEvent`/`AppendString`/`FlushEvent`,
  `WriteReplayEventRecord`.
- **`rendering/`** — the `Blit*` family, `BuildRotatedSpriteQuad`,
  `PresentFrame`, texture-cache lookups.
- **`directx_init/`** — `InitDirectDraw`/`InitDirectSound`/`InitDirectInput`,
  `ShutdownDirectDraw`.
- **`fileformat/`** — the `.xfs` archive reader/decoder family,
  `LoadGameDataFiles`, `ChooseEvent.txt` parsing.
- **`ui_widget/`** — `CreateButtonWidget`, `RegisterActiveObject`, and
  friends.
- **`registry/`** — `ReadRegistryDword`/`WriteRegistryDword`/
  `GetDisplayConfigFromRegistry`.

**Be clear about what "ported" means here**: these are close to verbatim
Ghidra decompiler output, not hand-verified against documented behavior
beyond what's already written up in ARCHITECTURE.md/PROTOCOL.md/
FILEFORMATS.md. `PROGRESS.csv` marks them `RAW-src` — a third status
alongside `TODO` and the hand-verified `PARITY-<file>` used for `lzhuf/`,
specifically meaning "file exists, not yet promoted to verified."
Concretely, that means:

- **They reference hundreds of not-yet-ported globals and helper
  functions** (`DAT_<address>`/`_DAT_<address>` globals, unnamed
  `FUN_<address>` helpers, string-literal symbols) that don't exist
  anywhere in this tree yet. None of these files link — most don't even
  compile standalone (undeclared identifiers) — until their dependencies
  are ported too. This is expected at this stage, not a bug to chase
  file-by-file; `include/ghidra_types.h` (see below) only fixes the
  *universal* issues, not per-file missing symbols.
- **`include/ghidra_types.h`** is a shared compatibility header (typedefs
  for Ghidra's `undefined4`/`code`/`byte`/`uint3`/etc. pseudo-types, plus
  a handful of Windows/CRT struct-tag typedefs Ghidra emits bare - `tm`,
  `sockaddr`, `hostent`, `_FILETIME`, `tagMSG`, `_WIN32_FIND_DATAA`,
  `_RTL_CRITICAL_SECTION`) that lets this raw output parse as plain C
  without hand-editing every file for that class of issue. Include it
  before `<windows.h>` in any raw port.
- **19 files (of 711 total raw ports, ~2.7%) have deeper, genuine syntax
  problems** beyond missing symbols — Ghidra's decompiler falling back to
  invalid-C pseudo-syntax for things it couldn't cleanly express
  (`variable._0_1_`-style partial-register/sub-byte-field access,
  `switch` on a pointer, array-type casts, `float10`/x87-extended-
  precision locals with no portable equivalent, an internal CRT
  thread-data struct, a genuine MSVC ATL C++ template-library call
  Ghidra qualified with `::`, or a vtable call whose return value is
  used but which the generic `code` typedef can't give a real return
  type — see the `code()` vs. `code(void)` note below for why the
  argument-count side of that same tension was resolved differently),
  usually in the largest/most complex functions or ones close to raw
  CRT/ATL internals:
  - `state_machine/State02_ServerSelect_ProcessPacket.c`
  - `state_machine/State11_InBattle_ProcessBattleAction.c` (extensive
    sub-byte-field access, `._1_3_`/`._0_4_`/etc. - this is a large,
    heavily-packed packet-decoding function with many fields read at
    non-standard offsets/widths)
  - `state_machine/State11_InBattle_Render.c` (same extensive sub-byte-
    field access pattern, ~2000-line rendering function, plus a
    pointer-arithmetic-on-non-pointer issue around line 1197)
  - `state_machine/State10_Loading_PreloadAssets.c` (`&stack0xffffff7f`
    - a raw stack-frame offset Ghidra couldn't map to any declared
    local; it's one byte before `acStack_80` starts, likely a stack-
    layout/padding mismatch in Ghidra's own analysis rather than
    something guessable from this function alone)
  - `unnamed/FUN_00423e20.c`, `unnamed/FUN_004240c0.c` (same
    `stack0xffffff80` raw-stack-offset issue as
    `State10_Loading_PreloadAssets.c`, plus sub-byte-field access and a
    vtable-return-value-used call each)
  - `unnamed/FUN_00408180.c`, `unnamed/FUN_004141b0.c` (sub-byte-field
    access, plus `FUN_00408180.c` also has a missing `DAT_0067e818`
    global from the same ~1159-address gap noted above)
  - `unnamed/FUN_0041da80.c` (SEH frame plumbing plus multiple
    `stack0xfffffbNN` raw-stack-offset references, same unrecoverable
    class as `State10_Loading_PreloadAssets.c`)
  - `unnamed/FUN_0042bbb0.c`, `unnamed/FUN_0042de70.c` ("invalid use of
    void expression" - a vtable-return-value-used pattern that needs
    per-call-site review, plus `FUN_0042bbb0.c` also references
    `uRam00001e50` - a Ghidra "unknown RAM region" pseudo-symbol, not a
    normal global, that needs real investigation before it can be
    declared)
  - `unnamed/FUN_0042f4b0.c`, `unnamed/FUN_004305c0.c`,
    `unnamed/FUN_00432850.c`, `unnamed/FUN_00437870.c`,
    `unnamed/FUN_004388e0.c`, `unnamed/FUN_00408180.c` (sub-byte-field
    access, `._0_4_`/`._1_3_`/etc. - same weapon-effect-function
    family as the ones above; each also still has its own SEH frame
    plumbing to strip, not done yet since the sub-byte access needs
    fixing regardless and the SEH-local variable names differ per
    file, not a safe blind bulk edit)

  **A recurring, mechanically-fixable sub-case found later**: an
  exception-cleanup-index local (`local_c`/`local_4`/`uStack_c`/
  `puStack_8`/etc. - the same slot the SEH frame plumbing uses, or one
  right next to it) gets counted through a function's many
  `FUN_0040a240`/`FUN_0040b540` cleanup-pair calls via single-byte
  writes that Ghidra renders as `var._0_1_ = N;`, plus one or more
  resets rendered as `var = (uint)var._1_3_ << 8;` or
  `var = CONCAT31(var._1_3_,N);`. In every case checked, the variable
  only ever holds small (<0x100) constants with the upper 3 bytes
  never set to anything but zero, so these are safe, purely mechanical
  rewrites: `var._0_1_ = N;` → `var = N;`, `var = (uint)var._1_3_ << 8;`
  → `var = 0;`, `var = CONCAT31(var._1_3_,N);` → `var = N;`.
  `unnamed/FUN_004174c0.c` and `unnamed/FUN_00406990.c` were fully
  fixed this way (plus their SEH plumbing). `unnamed/FUN_00432850.c`,
  `unnamed/FUN_0044d9b0.c`, and `unnamed/FUN_00452cc0.c` had this same
  sub-case applied but remain broken for other, unrelated reasons
  (more sub-byte-field access elsewhere, raw `stack0x...` offset
  references) - the partial fix is still correct and worth keeping.
  - `unnamed/FUN_0043a670.c` (sub-byte-field-adjacent: an lvalue-
    assignment issue at line 51 plus a `stack0xfffffdb4` raw-stack
    reference, same unrecoverable class as
    `State10_Loading_PreloadAssets.c`)
  - `unnamed/FUN_0043af40.c`, `unnamed/FUN_0044a000.c`,
    `unnamed/FUN_0044b900.c`, `unnamed/FUN_0044c950.c` (sub-byte-field
    access; `FUN_0044a000.c` additionally has its own
    `stack0xfffffee8` raw-stack reference)
  - `unnamed/FUN_0044d9b0.c`, `unnamed/FUN_00452cc0.c` (sub-byte-field
    access - `stack0xfffff51c`/`stack0xfffff518`/etc. raw-stack
    references and more - plus their own SEH frame plumbing not
    stripped yet; the mechanical exception-index sub-case described
    above was already fixed in both)
  - `unnamed/FUN_0044f050.c` (sub-byte-field access plus a
    `stack0xfffff524` raw-stack reference, plus its own SEH frame
    plumbing not stripped yet)
  - `unnamed/FUN_004513b0.c` (sub-byte-field access, plus its own SEH
    frame plumbing not stripped yet)
  - `unnamed/FUN_00477140.c` (SEH plumbing not stripped yet, plus two
    `stack0xfffffbNN` raw-stack references, same unrecoverable class
    as `State10_Loading_PreloadAssets.c`)
  - `unnamed/FUN_0047b2f0.c` (sub-byte-field access plus a
    `stack0xfffff524` raw-stack reference, plus its own SEH frame
    plumbing not stripped yet)
  - `unnamed/FUN_0047c040.c`, `unnamed/FUN_0047ca40.c` (sub-byte-field
    access, plus their own SEH frame plumbing not stripped yet)
  - `unnamed/FUN_0047c3f0.c` (`float10` - x87 extended-precision local
    with no portable equivalent - plus sub-byte-field access and its
    own SEH frame plumbing not stripped yet)
  - `unnamed/FUN_00519ef0.c`, `unnamed/FUN_0051a120.c`,
    `unnamed/FUN_004e9cc0.c`, `unnamed/FUN_0051a230.c`,
    `unnamed/FUN_004f3af0.c` (`float10` - x87 extended-precision
    locals with no portable equivalent, same class as
    `unnamed/FUN_0047c3f0.c` above)
  - `unnamed/FUN_0040a040.c` (`struct exception` used as a real,
    complete type - this project's `exception` typedef is a
    deliberately opaque placeholder, see include/ghidra_types.h's own
    comment on it - would need the real MSVC CRT exception-class
    layout to fix properly)
  - `unnamed/FUN_004e95c0.c` (`cannot convert to a pointer type` /
    `pointer value used where a floating-point was expected` - a
    genuine type-confusion in Ghidra's decompile, not investigated
    further this pass)
  - `network/InitCommP2PNotifyWindow.c`
  - `replay/WriteReplayEventRecord.c`
  - `unnamed/FUN_0041b8c0.c`, `FUN_00401880.c` (the ATL call), `FUN_00449540.c`,
    `FUN_004cb280.c`, `FUN_004ccd10.c`, `FUN_00504c10.c`, `FUN_00525c42.c`,
    `FUN_0053753c.c` (the last two are CRT-internal thread/FPU-state
    helpers, not game logic - likely not worth porting at all rather
    than fixing), `FUN_0046dde0.c`, `FUN_00471320.c`, `FUN_004ac5a0.c`
    (sub-byte-field access), `FUN_00405760.c`
    (vtable-call return value used as non-void)

  **`entry/InitGame.c` was in this list (Windows SEH `__try`/`__except`
  frame setup - direct `FS` segment-register manipulation, an internal
  exception-handler label used as a data value) but is now fixed**: the
  actual handler code (`LAB_0053ce9a`) was never included in this
  function's own decompilation, so there was no exact behavior to
  preserve - the frame push/pop plumbing was simply stripped (all three
  sites: entry, one early-return, and the function's tail), leaving the
  function's real init logic intact. This pattern (FS-register frame
  chains) will likely recur elsewhere, since structured exception
  handling is presumably used throughout the game's own error-handling
  code, not just once - the same strip-the-plumbing approach should
  apply each time, but each occurrence still needs manual review to
  confirm the handler body really is absent from the decompile before
  assuming it's safe to remove.

  These need real per-occurrence hand-translation (each `._0_1_` access
  means something different depending on context) — not attempted this
  pass, flagged here so it's a known list rather than a surprise later.

  Separately, working down `make winelib-syntax-check`'s FAIL list
  file-by-file (not all genuinely-broken, just needed small type/cast
  fixes) has so far fixed `entry/GameTick.c`, `entry/Shutdown.c`,
  `directx_init/InitDirectInput.c`, `unnamed/FUN_004edd70.c`, and
  `unnamed/FUN_004ee270.c` — mostly the same "vtable call's return
  value is used, `code`'s void return can't express that" pattern
  (fixed per call site with a local `int (**)()` cast instead of
  `code **`, rather than changing the shared `code` typedef, since
  most vtable calls really are void-returning), plus `Shutdown`'s
  `char` parameter needing to become `int` (a K&R unprototyped forward
  declaration can't be defined with a default-promoted parameter
  type), and three `DAT_<addr>` globals (`DAT_00674f68`,
  `DAT_00e52814`, `DAT_00e5369c`) needing `int *` instead of the
  generic `uint32_t` Ghidra inferred, since call sites dereference
  them as vtable-bearing pointers.
- Verified via a syntax-only compile pass (`winegcc-stable -c`, catching
  parse errors without needing every symbol resolved) inside
  `tools/winelib-env/`'s Docker image — confirms the files are
  *structurally* real C (modulo the 12 above), not that they build or
  link yet. `make winelib-syntax-check` runs this locally.

### `unnamed/msvc_crt_atl/` — 544 functions, deliberately excluded

Everything at address `0x51fe1c` and above turned out to be the
statically-linked MSVC 7.10 C runtime and ATL (Active Template Library)
— malloc/free/heap-management internals, C++ exception handling,
`CComCritSecLock`/`CAtlBaseModule`/`CSimpleArray<T>` template classes —
compiler/runtime plumbing, not game logic (the exact address boundary
matches what ARCHITECTURE.md's "Compiler/runtime" section already
independently confirmed via runtime-error strings and the traced
`fopen()` implementation). These were still bulk-ported like everything
else initially, but then moved to their own subdirectory and excluded
from the build's source list — see that directory's own `README.md` for
the full reasoning. Concretely: reimplementing a heap allocator or
exception unwinder from decompiled output is unnecessary (Winelib/glibc
already provide correct ones), riskier than most game-logic code (silent
memory corruption instead of a clean crash when subtly wrong), and off
the actual goal. One of the already-documented genuinely-broken files
(`FUN_00401880.c`'s ATL template call) is exactly the kind of problem
this exclusion sidesteps entirely for the other 543.

`PROGRESS.csv` marks these `EXCLUDED-msvc-crt-atl` — a fourth status,
distinct from `RAW-src`/`PARITY-<file>`/`TODO`, meaning "intentionally
not part of the porting effort," not "not done yet."

## Global variables

Every `DAT_<address>`/`_DAT_<address>` global and `s_<name>_<address>`
string-literal symbol referenced anywhere in the 575 raw-ported
functions — 610 numeric globals plus 212 strings — is declared in
`include/globals.h`, with storage in `src/globals.c`. Included
automatically by `ghidra_types.h` (which every raw port already
includes), so no raw-ported file needed editing to pick these up.

- **Numeric globals are typed from Ghidra's own inferred type/size at
  each address** — `uint8_t`/`uint16_t`/`uint32_t`/`void *`, matching
  whatever Ghidra's data browser has defined there. This is a real type
  in the narrow sense (right size, roughly right shape) but almost
  certainly wrong at the semantic level in most cases — a `uint32_t`
  might really be a signed `int`, a float's bit pattern, or a struct
  pointer. Good enough to compile; not verified.
- **The original scan that generated this file missed roughly 1159
  addresses** that are actually referenced somewhere in `src/` (found
  by re-diffing every `_?DAT_<address>` occurrence in source against
  what's declared here, while working down `make winelib-
  syntax-check`'s FAIL list). Many of these are likely false positives
  — small values like `DAT_00000006`/`DAT_00007f00` are almost
  certainly `MAKEINTRESOURCE`-style fake-pointer immediates (the same
  pattern already fixed by hand in `entry/WinMain.c`), not real memory
  addresses, and shouldn't be declared as globals at all. The rest are
  probably real and simply need adding. Not re-generated in bulk this
  pass — one (`DAT_0058bb04`) was added by hand since it was blocking
  `unnamed/FUN_0041eb80.c`; expect more of these to surface as
  individual compile failures while working through the FAIL list.
- **String literals have their real, actual content** — extracted
  directly from the binary's data section (not placeholders), since the
  address is conveniently embedded in Ghidra's own symbol name
  (`s_AvataEffectTexture1_00556900` → read the C string at `0x556900`).
  Cross-checking a sample against STRINGS.md's already-catalogued
  strings confirms these match.
- **20 already-documented, named globals** (`g_currentGameState`,
  `g_pD3DDevice7`, `g_sineTable360`, etc. — see ARCHITECTURE.md) get
  better types than the generic Ghidra-inferred ones: `g_sineTable360`
  is a real `float[360]`, the DirectDraw7/Direct3D7 COM interface
  pointers (`g_pD3DDevice7` and friends) are `void **` rather than their
  real `IDirect3DDevice7 *`/etc. types (this tree doesn't have hand-
  written vtable structs or real COM interface definitions wired in
  yet — every raw-ported call site already dispatches through them via
  `(**(code **)(*ptr + offset))(...)`-style manual vtable calls). The
  double-pointer is required, not cosmetic: call sites dereference the
  global itself to reach the vtable pointer (`*g_pD3DDevice7 + offset`),
  so a plain `void *` can't compile there — found while fixing
  `GameTick.c`, see below. `g_spriteVertexBuffer`'s exact size isn't
  confirmed, so it's generously overallocated (`0x10000` bytes) rather
  than tightly sized.
- **A handful of addresses are referenced under both `DAT_<addr>` and
  `_DAT_<addr>`** — Ghidra's convention for "the same memory accessed at
  two different sizes/interpretations." Aliased via `#define` to the
  same storage under one canonical name; this loses the size/type
  distinction Ghidra was drawing, a known simplification.
- **`<ddraw.h>`/`<d3d.h>`** (Wine's DirectDraw7/Direct3D7 headers) are
  now included via `ghidra_types.h` too, resolving `IID_IDirect3D7`
  and friends — these headers were already available in the Winelib
  environment and needed no extra setup, just adding the `#include`.
- **A few `&DAT_<address>`-shaped references were fake pointers, not
  real globals at all** — Ghidra's decompiler represents certain Win32
  idioms (`MAKEINTRESOURCE(IDC_ARROW)`, the predefined registry handle
  `HKEY_CURRENT_USER`) as if they were `&DAT_<small-constant>`. Found
  and fixed at the four call sites that used them (in `WinMain.c` and
  three `unnamed/` files) rather than declaring fake globals for them.
- **Net effect**: before these globals existed, essentially none of the
  575 raw ports could compile without hitting an undeclared-identifier
  error. After, **329 of 575 (57%) compile with zero errors** doing a
  syntax-and-symbol check (not yet a full link — most still call
  `FUN_<address>` helpers that aren't ported yet, which is expected and
  a separate, ongoing effort, not a globals problem). The remaining
  errors are overwhelmingly unported `FUN_<address>` calls and the
  already-documented genuinely-broken files above, not missing globals.

### A real bug in `ghidra_types.h` itself, found and fixed

While cascading to a third tier of `unnamed/` functions, a new class of
error showed up: `called object is not a function or function pointer`,
on the standard vtable-dispatch idiom `(**(code **)(*ptr + offset))(...)`
that's used *everywhere* in this codebase. The `code` typedef was
`typedef void code;` - which looks reasonable (Ghidra's `code` is meant
to be an untyped/sizeless placeholder, same spirit as `void`) but is
actually wrong: dereferencing `code **` twice with `void` as the base
type produces a `void` *value*, and calling a `void` value is a hard
compile error, not just imprecise typing. The fix is
`typedef void code(void);` - a real (if generically-signatured) function
type, so `code **` dereferenced twice yields something actually
callable, confirmed with a standalone test case before applying it.

**This bug was present from the moment `ghidra_types.h` was created,
not newly introduced** - every earlier "N of M files compile clean"
figure quoted in this document (329/575, etc.) was measured *before*
this fix, meaning any of those "clean" files that happen to use the
vtable-dispatch idiom were actually passing for the wrong reason, or
this specific error class simply hadn't been hit by whatever subset of
files was checked in that pass.

**Re-verified with the fix applied, via a parallelized (8-way) sweep of
all 662 raw ports (as of the third tier): 383 OK / 279 FAIL (58% fully
clean, zero errors).** Several sequential attempts at this same check
timed out against this environment's background-task time budget (662
files × one `winegcc-stable`/Wine process launch each adds up) before
the parallelized retry finally completed. Every other specific
percentage elsewhere in this document predates this fix and should be
treated as superseded by this number, not as separately-still-valid
data points.

**A second, related bug found immediately after, while checking the
fourth tier**: `typedef void code(void);` (the fix above) turned out to
be *too* strict — a real C `(void)` prototype takes exactly zero
arguments, and several vtable calls pass real arguments, failing with
"too many arguments to function". The actual fix is the classic K&R
"unspecified argument list" form: `typedef void code();` (empty
parens, not `(void)`) — permissive about argument count the same way
the whole point of `code` is to be permissive about everything else.
Confirmed via another standalone test case. One remaining, structurally
different gap: a couple of call sites *use* a vtable call's return
value, which `code`'s `void` return type still can't express — those
are cross-referenced into the genuinely-broken-files list below rather
than papered over. This second fix landed after the 383/662 count
above, so that number is now itself slightly stale in the same
"superseded, not wrong" sense as everything before it — not
re-measured a third time this pass given how long each full sweep
takes; whoever runs the next one should expect a modest further
improvement from this fix.

## Building and testing

```
make            # native build of src/lzhuf/ only -> build/test_lzhuf
make winelib    # full Winelib build including main.c -> build/gunbound.exe
                # (needs `winegcc` on PATH - see "Wine setup" below)
```

To verify `lzhuf_decode()` against real archive data, first extract a
compressed blob and its known-good decoded reference with the Python
tooling, then diff:

```python
# from tools/lzhuf/
from extract_toc import read_toc
from lzhuf import decode_lzhuf
import struct

entries, *_ = read_toc('../../orig/graphics.xfs')
name, mode_flag, file_offset, decompressed_size, compressed_size = \
    next(e for e in entries if e[0] == 'bullet1n.img')
with open('../../orig/graphics.xfs', 'rb') as f:
    f.seek(file_offset)
    real_compressed_size, checksum = struct.unpack('<II', f.read(8))
    cdata = f.read(real_compressed_size)
open('/tmp/in.bin', 'wb').write(cdata)
open('/tmp/ref.bin', 'wb').write(decode_lzhuf(cdata, decompressed_size))
```

```
build/test_lzhuf /tmp/in.bin /tmp/out.bin 3472   # decompressed_size from above
diff /tmp/ref.bin /tmp/out.bin && echo MATCH
```

## Wine setup

**Real macOS-native Winelib** needs `winegcc`, which isn't available
prebuilt anywhere for macOS (Homebrew's `wine-stable`/`wine@devel` casks
are runtime-only — they ship `wine` but no dev toolchain/headers).
Getting a native `winegcc` means building Wine from source, which hasn't
been attempted (multi-hour build, large dependency chain).

**Working now: `tools/winelib-env/`, a Docker image with a real
`winegcc`** (Debian's `wine64-tools`/`wine64` packages), used as a
stand-in until a native macOS toolchain exists. Caveat: `winegcc` always
targets whatever platform it runs on, so a binary built this way is a
**Linux ELF Winelib binary** — it validates that the code actually
compiles/links against real Win32/DirectX/Winsock declarations (real
progress), but it isn't the eventual native-macOS-binary goal, and it
can only be *run* inside a full Wine environment (not attempted beyond a
basic linkage smoke-test — a headless container has no display, which
`main.c`'s window creation and any eventual DirectDraw code will need
anyway, so there's little to gain from chasing full execution here).

```
docker build --platform linux/amd64 -t gb-winelib tools/winelib-env
docker run --rm --platform linux/amd64 -v "$PWD":/work -w /work gb-winelib \
    make winelib WINEGCC=winegcc-stable
```

produces `build/gunbound.exe` / `build/gunbound.exe.so`. `winegcc` in
this image is only on `PATH` as `winegcc-stable`, hence the explicit
`WINEGCC=` override — pass the same to any other winegcc-family tool
(`wineg++-stable`, `widl-stable`, etc.) if needed later. Also note
`-std=gnu11`, not `c11`: Wine's `winsock.h` expects glibc's BSD typedefs
(`u_short`/`u_int`), which strict C11 mode hides.

## Picking the next function to port

Good next candidates are self-contained algorithms already fully
understood and documented, with no Windows/DirectX/Winsock dependency —
same reasoning that made LZHUF a good first target, buildable/testable
with the native `make` target before Winelib is even needed:

- The `.xfs`/`.dat` checksum routine (`tools/lzhuf/verify_checksum.py`
  has the reference; simple additive checksum, no external deps).
- `BlitSprite16bpp`'s sparse-row pixel decoder (documented in full in
  `FILEFORMATS.md`'s `.img` section, already has a Python reference in
  `tools/lzhuf/decode_img.py`).

Once Winelib is confirmed working, `WndProc`/`InitGame`/`GameTick` (all
stubbed in `main.c`) are the natural next layer — real Win32/DirectX
surface, one file each per the established convention.
