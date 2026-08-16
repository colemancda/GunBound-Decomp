# CValueGuard dropped-cell sweep — batch instructions

Repo: /home/coleman/Developer/GunBound-Decomp (branch main).

## Goal
For each assigned file, give every **argless** `PeekPacketChecksumState()`
call and every **1-arg** `EncodeOutgoingPacketField(<value>)` call back the
guard-cell pointer Ghidra dropped:

    PeekPacketChecksumState()            -> PeekPacketChecksumState((void *)(<cell>))
    EncodeOutgoingPacketField(v)         -> EncodeOutgoingPacketField((void *)(<cell>), v)

`<cell>` must be spelled with the file's OWN C locals/params wherever
possible (e.g. `param_1 + 0x99`, `local_1574`, `g_clientContext + 0x45354`,
`&DAT_00796aa0`).  Note `param_1` is usually `int *`, so a byte offset
0x264 becomes `param_1 + 0x99` (divide by 4); a `void *`/`int` base keeps
the byte offset.

## Tools (run from the repo root)
- Worksheet:   `tools/.venv-angr/bin/python3 tools/guard_file_report.py <file.c>`
  Prints the unfixed C sites (numbered, with line numbers) and then the
  disassembly-resolved cell for every guard call site in the function.
- Raw disasm:  `tools/.venv-angr/bin/python3 tools/disasm_capstone.py orig/GunBound.gme 0x<start> 0x<end>`
- Method notes: `tools/sweep_guard_instructions.md` (READ THIS FIRST).
- Syntax check (must be clean before committing each file):
  `docker exec gb-check wine 'Z:\opt\msvc7\bin\cl.exe' /c /nologo /Zs 'Z:\work\<path with backslashes>'`
  Ignore warnings C4047/C4090/C4276/C4133 and lines starting with `wine:`.

## Key facts established this session (use them)
1. **The delta/pair helpers return their SECOND argument** — the caller's
   stack scratch guard object, NOT their destination.  (0x40a5f0 DeltaAdd,
   0x40a6e0 DeltaSub, 0x40b180 DeltaShr, 0x40a8c0 DeltaDiv, 0x40aca0
   PairDiff, 0x40ada0 InitGuardedChecksumSlot ... all end `mov eax,esi`
   with ESI = arg2.)  So a Peek that the resolver reports as
   "<clobbered by call at 0xNNNN>" right after one of those calls reads
   that call's **arg2**, which the C usually still spells out
   (`EncodeChecksumDeltaShr(param_1 + 0x10, auStack_ac4, 8)` -> the next
   Peek's cell is `auStack_ac4`).  If Ghidra dropped the helper's args,
   capture the helper's return into a fresh local instead
   (`pvDelta = EncodeChecksumDeltaShr(...);` + `void *pvDelta;` decl).
2. `<esi/ebx/edi crosses block end at 0xNNNN> + 0xOFF` almost always means
   the register still holds `this`/the object — confirm with the disasm
   (look for the single `mov esi,ecx` / `mov ebx,[esp+N]` that set it) and
   then write `param_1 + OFF/4`.
3. Frame slots (`dword ptr [esp + 0xNN]`) hold cell POINTERS parked by the
   compiler.  Find the `mov [esp+0xNN], reg` that wrote it **at the right
   push depth** (the report normalizes; the raw disasm does not) and use
   what that register held.
4. Ghidra often lays blocks out in a DIFFERENT ORDER than the binary.
   Never zip C sites to disasm rows by position alone — match landmarks
   (helper calls, `cmp` constants, string ids, `puStack_8`/`local_4`
   marker values, sprite ids).

## Hard rules
- **Never invent a cell.**  If a site is genuinely ambiguous, leave it
  argless, append an inline `/* NOT FIXED: <why> */` comment on that line,
  and say so in your report.  A wrong cell is far worse than a skipped one.
- Do not touch anything under `src/network/`.
- Do not "fix" 2-arg Encode calls that already carry a cell.
- Add a `DROPPED-CELL FIX (2026-08-16, CValueGuard sweep): ...` paragraph
  to each file's header comment, right after the line containing
  `verbatim ports" section for status.`, describing which cells you
  recovered and how you pinned the non-obvious ones.
- **One commit per file**, message style:
  `sweep: N cells in <FunctionName> (<short note>)`.
  Then `git push` after each commit.  Do NOT add any Co-Authored-By,
  Claude-Session or Generated-with-Claude trailers — this repo forbids them.
- Syntax-check each file before its commit; the check must be clean.
- Work the files in the order given.

## Report back
A short list: file -> sites fixed / sites skipped (with reasons).
