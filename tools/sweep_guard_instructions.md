# CValueGuard call-site sweep — per-file instructions

Mission: in each assigned file, recover the dropped guard-cell pointer at
every argless `PeekPacketChecksumState()` call and every 1-argument
`EncodeOutgoingPacketField(value)` call, so each passes its cell:

    PeekPacketChecksumState((void *)(<cell>))
    EncodeOutgoingPacketField(<cell>, value)      /* cast to match local idiom */

Both callees are currently bring-up stubs (Peek returns 0 ignoring args;
Encode is a no-op auto-stub), so these edits are behavior-neutral today.
Correctness comes from the original binary's disassembly, and the whole
guard system is flipped live only after the sweep completes — a wrong cell
becomes a wild pointer dereference at flip time, so NEVER GUESS. A site you
cannot back with disasm evidence stays unchanged and is reported.

## Ground truth

`tools/guard_worklist.json` → `files["<your file>"]`:
- `peek.c_argless_lines`: line numbers of the argless Peek calls (line
  numbers from generation time — re-locate by content if edits shift them).
- `peek.orig_sites`: the original binary's `call 0x40a2e0` sites in address
  order, each with `cell` (the EAX value at the call: register name,
  immediate, `&(...)` lea form, `dword ptr [esp + X]`, or
  `<clobbered:...>`) and `src` (the instruction that set it).
- `encode.c_1arg_lines` / `encode.c_2arg_lines`: the file's 1-arg
  (unfixed) and ≥2-arg (already fixed, 2026-07-15 sweep) Encode calls.
- `encode.orig_sites`: ALL original `call 0x40a380` sites in address order
  with `cell` = the EDI value.
- `peek.status` / `encode.status`: `clean` when C-site count matches
  orig-site count exactly.

Disassembler for verification and register back-tracking:

    tools/.venv-angr/bin/python3 tools/disasm_capstone.py orig/GunBound.gme 0x<start> 0x<end>

Cell resolver - does the mechanical register back-tracking for EVERY guard
call site in a function in one shot (all families, not just Peek):

    tools/.venv-angr/bin/python3 tools/guard_cell_resolve.py 0x<start> 0x<end>

It prints, per site, the resolved cell expression plus the exact mov/lea/add
chain it followed, so you can check its work without re-deriving it.  Use it
to get the whole function's cell list up front, then spend your attention on
the two things it cannot do: naming the C local/global each expression maps
to, and checking landmarks.  It is a HINT GENERATOR with the same standing
caveat as the json hints - it walks the function LINEARLY, so a site whose
register was set on another control-flow path is wrong.  It self-marks the
known hazards with `!!`: `<clobbered by call ...>` (the chained-return
pattern - the cell is that helper's discarded return value) and
CROSSES-BRANCH-TARGET (a branch target lies between the write and the use,
so the value may arrive from elsewhere).  Read every `!!` site by hand, and
spot-check the unflagged ones as usual.  esp-relative results are normalised to
settled-frame slots (see below), but naming the slot still needs the
per-function frame base.

FRAME-SLOT ARITHMETIC - the thing that most often produces a wrong cell
that still *looks* plausible.  `[esp + X]` is only the slot named by X
when esp is at its settled depth.  Three ways it is not, all of which
have bitten this sweep:
  1. inside a `push .. / call ..` argument block (the critical-section
     pairs around nearly every guard call);
  2. anywhere in the PROLOGUE, before the callee-saved pushes finish -
     FUN_00491b40's `mov [esp+0xc],edi` and FUN_00497ad0's
     `mov [esp+8],ebx` both really write frame[0x14];
  3. between a __cdecl `call` and the caller's `add esp,N` that cleans
     up after it - FUN_0048b420 0x48b78c reads frame[0x14] as
     `[esp+0x18]`, and reading it naively picks up a stale Peek RESULT
     and passes a value as a pointer.
guard_cell_resolve.py handles (1) and (3) and refuses to guess at (2).
When you name a slot yourself, find its writers with the same depth
model, and check none of them is a Peek RESULT rather than a cell.

The file's header comment states its function's original address.

## Mapping C lines to original sites

1. `clean` + straight-line control flow (no Ghidra label soup): zip C lines
   with orig sites in order. THEN spot-verify at least 3 sites (or all, if
   fewer) by disassembling around their `call_addr` and checking the
   surrounding landmarks (nearby immediates, global addresses, offsets,
   localized-string ids) against the C neighborhood.
2. Goto-shuffled decompiles (out-of-order `while(true)`/`LAB_` blocks —
   common): do NOT trust line order. Match each C site to its orig site by
   landmarks per site.
RELIABILITY WARNING (2026-08-11, from the State11_OnTick sweep): the
encode json's `cell` back-tracks have proven WRONG at sites inside loops
(the old scanner missed same-block EDI reloads — e.g. 0x4be9f3 is really
`lea edi,[ecx+eax+0x5dcc0]`, not its claimed `[esp+0x3c]`). Treat every
json `cell` as a HINT: derive the actual cell from the disasm at the
call_addr yourself, especially for `dword ptr [esp+X]` claims and any
site inside a loop. The peek json's EAX entries have matched disasm so
far, but verify them too when anything looks off.

3. For Encode: the orig list covers BOTH the already-fixed 2-arg calls and
   your 1-arg targets, interleaved in call order. Align the full sequence
   (all C Encode calls by line order vs all orig sites by address order)
   and use the 2-arg calls' existing (known-correct) cells to lock the
   alignment: the orig `cell` at those positions must be consistent with
   the C cell already passed. Mismatch there = your alignment is wrong —
   re-derive before touching anything.

## Translating a cell expression to C

- Immediate (e.g. `0x796aa0`): find the symbol — grep `include/globals.h`
  for `DAT_00796aa0` or a named global whose comment cites the address.
  Pass `&DAT_00796aa0` / `&g_name`. If no symbol exists at that address,
  check `src/globals.c` and report it rather than inventing one.
- `&([reg + 0xNNN])` lea forms: identify what the base register holds at
  that point (disasm back-track) — commonly `g_clientContext`
  (`mov reg,[0x5b3484]`), the function's `this`/param, or a local array.
  Express as the C-level equivalent, e.g.
  `(void *)(g_clientContext + 0xf54)` or `(void *)(param_1 + 0x488)`.
- Bare register (`edi`, `esi`, `ebx`, `ebp`): back-track the register's
  last load before the call (widen the disasm window as needed, including
  across the block boundary the same way the value actually flows). The
  source is usually one of the lea/mov forms above; translate that.
- `dword ptr [esp + X]`: a stack slot holding a precomputed cell pointer.
  Ghidra local names encode frame offsets (local_NNN = frame base - NNN);
  find which C local corresponds and pass it. If the local was optimized
  out of the decompile, reconstruct from the store into that slot in the
  disasm.
- `<clobbered:add eax,0xNNN>`: the scanner stopped at an arithmetic step —
  the cell is (previous EAX value) + 0xNNN. Back-track one more step in
  the disasm (e.g. `mov eax,[0x5b3484]; add eax,0x3b49c` →
  `g_clientContext + 0x3b49c`).
- Cells inside per-player arrays: stride 0x224 starting at
  `g_clientContext+0xebef4` is the per-player cell array; also seen:
  per-category arrays at `g_clientContext+0x5f3774` / `+0x5f4004`
  (stride 0x224). An index-scaled lea (`imul idx,0x224` feeding the lea)
  translates to `ctx + idx*0x224 + base`.
- Chained-return cells: the guard-family lock wrappers (0x40a470 Queue,
  0x40a4a0 EncodeChecksumState, 0x40a5f0/0x40a6e0/0x40a7d0/0x40a8c0/
  0x40aba0/0x40b180/0x40aca0/0x40ada0 delta/pair helpers) RETURN their
  cell pointer in EAX.  WHICH cell: it is their SECOND argument - the
  caller's stack SCRATCH guard object - not their destination
  (0x40a5f0's epilogue is `mov eax,esi` with ESI = arg2, the object
  whose +0x14/+0x220 fields the caller then tests; verified 2026-08-16
  in SimulateSuperShot_Bullet13).  So when the decompile kept the arg
  list, the cell can be spelled with the C's own scratch local
  (`Peek((void *)local_1574)`) instead of capturing the return. A
  pattern like `call 0x40aba0; mov edi,eax; ... mov eax,edi; call
  0x40a2e0` means the Peek cell is that helper's return value — which
  the decompile usually DISCARDED. Capture it in a local (reuse an
  existing uVarN if free, else add one in the file's style) and pass it.
- IMPORTANT (scratch files): the session scratchpad is shared between
  concurrently-running sweep agents — name any disasm dumps uniquely
  (e.g. FUN_00XXXXXX_full.asm), never generic names like full.asm.

## Editing rules

- Touch ONLY the call arguments (and, where a needed value was discarded,
  introduce a minimal local following the file's existing naming style).
- Do not reorder or reformat existing code; keep the raw-port look.
- Add ONE dated header note (2026-08-11) in the file's established
  "DROPPED-x FIX" style summarizing the recovery and citing
  tools/guard_worklist.json + spot-verified disasm.
- Do NOT touch include/functions.h, src/network/*.c stubs, or any file not
  assigned to you.
- Do NOT commit.

## Verification

Syntax-check every edited file (exit 0 required; C4047 warnings are
expected house style and ignored):

    docker exec gb-check wine 'Z:\opt\msvc7\bin\cl.exe' /c /nologo /Zs 'Z:\work\src\<subdir>\<file>'

If the container is wedged, `docker restart gb-check` and retry.

## The full guard family (when your brief says "all families")

`tools/guard_family_sites.json` holds every call site of the 26 wrapper/
helper members: per site `call_addr`, `eax`/`eax_src` (backward-tracked
EAX), `pushes` (last ≤3 push operands), and `window` (the 12 preceding
instructions — resolve ANY register from it without re-running angr).
`prologues` holds each member's entry disasm. Verified ABI table
(2026-08-11, from those prologues + targeted disasm):

| member | cell | value/other | notes |
|---|---|---|---|
| PeekPacketChecksumState 0x40a2e0 | EAX | — | returns value |
| EncodeOutgoingPacketField 0x40a380 | EDI | value push | inner store |
| QueueOutgoingPacketField 0x40a470 | EAX | value push, ret 4 | lock wrapper; RETURNS cell |
| PeekChecksumStateUnderLock 0x40a4d0 | stack [esp+4], ret 4 | — | Ghidra kept most args |
| EncodeChecksumState 0x40a4a0 | dest=EAX | src cell push, ret 4 | dest.Encode(src.Peek()); RETURNS dest. C def currently mis-uses src as dest — def promotion needed |
| EncodeChecksumStateXored 0x40a440 | EAX | — | |
| EmitChecksumSum 0x40afb0 | EAX | + stack args | |
| Delta/Pair/Negate helpers 0x40a500-0x40b180 | stack args (mostly Ghidra-kept) | — | SEH-framed (defs may need SEH strip); RETURN their cell in EAX (the chained-return pattern) |
| PacketChecksum{Eq,Ne,Gt,Ge,Lt,Le} 0x40b270-0x40b360 | stack (cell, other), Ghidra-kept | — | comparators |
| ScrubChecksumGuard 0x40a2a0 | **ECX** | — | 852 argless C sites; get ECX from the window |
| PeekPacketChecksumBool 0x4065a0 | EAX (GuardedBool*) | — | 1,226 argless C sites |
| SetGuardedBool 0x406500 | EAX | + stack | check each site: w/args C calls may still drop the cell |
| EncodeGuardedBool 0x4064a0 / Rescramble 0x406530 / CheckAnd 0x406610 / CheckBoth 0x406710 | see prologues+windows | — | resolve per site |

Rules for family fixes are the same as Peek/Encode: cells from disasm
evidence only; behavior-neutral while the stubs ignore args; K&R decls
stay until the flip. When a member's C DEFINITION itself drops the cell
(like QueueOutgoingPacketField before 2026-08-11), do NOT change the
definition — report it; the coordinator promotes definitions centrally.

## Report

Per file: sites fixed (per-family counts), mapping method (order-zip vs
landmark), spot-checks performed, unresolved sites with reasons, syntax
check result.
