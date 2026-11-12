# Static recompilation of the GunBound client

This directory turns the original 32-bit x86 Windows executable (`orig/GunBound.gme`)
into a native Linux program by lifting every function to C and linking the result
with a small runtime that stands in for Windows. The target device is a Retroid
Pocket 5 running Linux (aarch64, glibc); a native x86_64 build exists for debugging.

It is independent of the hand decompilation in `src/`: nothing here reads those
sources. The only shared input is `PROGRESS.csv`, used for function start addresses
and for the names shown in guest call stacks.

Nothing derived from the game binary is committed. The lifted C, objects and
binaries live under `recomp/build/`, which is ignored, and the program needs the
original executable at run time (it maps its data sections from it).

## Status: milestone 1

The whole image is lifted, compiled and linked, and runs from the PE entry point
through the MSVC CRT startup (heap, TLS, stdio handles, environment, argument
parsing, locale tables) and into the C++ static constructors. It stops at the
first Win32 import without a handler, prints the import name and the guest call
stack, and exits with status 3:

```
UNIMPLEMENTED import user32.dll!CreateWindowExA
  called from 0x004fdcc7; first stack arguments: 00000000 00557b50 00557b58 80000000 00000000 00000000
guest state:
  eax=0012fe5c ebx=00000000 ecx=00e53e90 edx=00000000 esi=013416dc edi=00e55a34
  esp=0012fdf4 ebp=013416d8 eflags=00000246 fs=00021000 x87: top=0 cw=023f sw=0100
guest call stack (most recent first):
   #0  [0012fdf4] 0x004fdcc7  CreateCommEngineNotifyWindow+0x47
   #1  [0012fe2c] 0x004fd11c  ConstructCommP2POwner+0x2c
   #2  [0012fe4c] 0x004fd0cd  CreateCommP2POwner+0x3d
   #3  [0012fe68] 0x00401a2b  FUN_00401910+0x11b
   #4  [0012fe8c] 0x00540daa  sub_00540da0+0xa
   #5  [0012fe94] 0x00529cd6  __cinit+0x5e
   #6  [0012fea0] 0x00527922  entry+0x143
```

That is a static constructor creating the hidden notification window of the
network engine, before `WinMain` is reached. The x86_64 build and the aarch64
build (under `qemu-aarch64`) produce the same output, and their import traces
(3.2 million calls) are identical apart from the values of `GetTickCount`. A
build lifted with `--no-flag-liveness` produces the same trace as well.

## Building and running

```
recomp/build.sh host        # -> recomp/build/host/gunbound
recomp/build.sh aarch64     # -> recomp/build/aarch64/gunbound

recomp/build/host/gunbound --exe orig/GunBound.gme [--trace-imports] [-- guest args]

sysroot=$(aarch64-buildroot-linux-gnu-gcc -print-sysroot)
qemu-aarch64 -L $sysroot recomp/build/aarch64/gunbound --exe orig/GunBound.gme
```

Requirements: python3 with `capstone` and `pefile`, gcc, ninja; for aarch64 a
glibc cross compiler (`AARCH64_CC`, default the batocera h616 buildroot gcc).
`build.sh` documents its environment variables (`OPT`, `JOBS`, `EXTRA_CFLAGS`,
`LIFT_FLAGS`, `VARIANT`).

On the 4-core development machine: lifting takes 14 s, and compiling the 108
generated C files plus the runtime at `-O1 -j4` takes 51 s with the host gcc 14
and 63 s with the cross gcc 12. The binary is about 9.5 MB.

Exit status: the guest's own exit code, or 2 for a setup error, 3 for an
unimplemented import, 4 for an unimplemented instruction or unsupported control
flow, 5 for a host fault (reported with the guest address and guest call stack).

## Self-test

```
recomp/test/run.sh host
recomp/test/run.sh aarch64
```

`test/snippets.S` contains 113 hand-written x86 functions. The script runs them
natively as a freestanding 32-bit program to obtain reference results, lifts the
same bytes, runs the lifted code and compares: 92132 input vectors, covering
adc/sbb, shifts and rotates by CL (including counts of 0 and counts beyond the
operand width), all multiply and divide forms, the sixteen condition codes, the
rep string instructions in both directions, jump tables, every kind of call, and
x87 arithmetic in each operand order, comparisons and `fistp` in all four rounding
modes. Flags the processor leaves undefined are masked. The lifted code is checked
both with and without the flag-liveness pass. `expected.txt` holds the reference
output for machines that cannot execute 32-bit x86 code.

## Design

### Lifter (`lift/`)

`lift.py` drives `analyze.py` (discovery) and `translate.py` (instruction
semantics) and writes `chunk_NNN.c`, `funcs.h`, `tables.c` and `report.txt`.

*Function starts* are the PE entry point, the `addr` column of `PROGRESS.csv`,
every direct call target, and addresses found as code immediates or as dwords in
the data sections, provided they lead to plausible code. That last group is how
the C++ exception unwind funclets, callbacks and SEH handler labels get lifted:
nothing calls them directly. Pointers into the middle of an instruction are
rejected.

*Bodies* come from recursive descent, so jump tables and other data in the code
section are never decoded. A jump to another function's start is a C tail call; a
block shared by two functions is emitted in both.

*Jump tables* (`jmp [reg*4 + table]`) are sized from the preceding
`cmp reg, N; ja default`, through a byte index table when there is one, and
otherwise by scanning entries until they stop being code addresses. The emitted
code loads the target from guest memory and switches on it, with a runtime
dispatch as the default case, so an underestimated table still works.

*Calling model.* One C function per guest function, `void f_XXXXXXXX(CPU *c)`.
Registers, flags and the x87 stack are fields of `CPU`. The guest stack is in
guest memory and is used literally: `call` stores the guest return address and
calls the C function, `ret N` pops it and returns. Helpers that play with the
stack, such as `__SEH_prolog` and `_chkstk`, work unchanged. After each call the
caller checks that the popped address is the one it pushed (`RT_RETCHECK`);
a mismatch is fatal for now and is the hook for non-local control flow.

*Flags* are computed eagerly, but only those a later instruction can read: a
per-function liveness pass removes the rest. Calls, returns and indirect jumps
are treated as reading every flag.

*Unsupported instructions* become `rt_unimplemented_insn(c, addr, "mnemonic")`,
so the output always compiles. The lifter lists them in `report.txt`.

### Runtime (`runtime/`)

- `cpu.h`: CPU state and the inline helpers the lifted code uses.
- `mem.c`: the guest address space, 1 GiB reserved at host address 4 GiB so that
  guest address `a` is host address `0x100000000 + a` with a constant base
  (`-DRT_DYNAMIC_BASE` uses a variable base instead). Only the regions in use are
  accessible, so a wild guest pointer faults instead of corrupting the host.
  Also the guest heap and the `VirtualAlloc` arena.
- `loader.c`: maps the PE headers and sections and points every IAT slot at a
  fake address. It refuses an executable whose code section does not match the
  checksum recorded by the lifter.
- `dispatch.c`: indirect calls (a dense table over the code section), import
  dispatch, the guest call stack printer and the fault handler.
- `imports.c`: Win32 handlers. `x87.c`: the less common x87 operations.
- `main.c`: builds the PEB, TEB, environment and command line, then calls the
  entry point.

Guest layout: system block at 0x20000, stack 0x30000-0x130000, image at
0x400000, heap from 0x1000000, `VirtualAlloc` arena from 0x20000000, fake import
addresses at 0x3FF00000.

### Deviations from the original plan

- Function starts also come from pointers in data and code immediates, not only
  from `PROGRESS.csv` and call targets. Without this about 3200 funclets and
  callbacks would be missing.
- The flag-liveness pass was added now rather than later; it removes most flag
  computations and can be switched off with `--no-flag-liveness`.
- The guest mapping sits at a fixed host address. This makes memory accesses
  cheaper and wild pointers detectable; the variable-base build remains available.
- The indirect-call table is filled at startup from a sorted list rather than
  being a 10 MB initialised array.

## Lifter coverage

From `report.txt` for the current image:

| | |
|---|---|
| functions | 5653 (2404 from PROGRESS.csv, 12 more call targets, 2960 + 235 code pointers from data and immediates, 42 labels) |
| instructions | 361235 unique, 368546 emitted |
| code section bytes covered | 1283998 of 1323008 |
| jump tables | 121, all resolved (85 from the bounds check, 36 by scanning) |
| indirect jumps | 121 table, 11 import thunks, 7 dispatched at run time |
| indirect calls | 13532 |
| decode failures | 0 |
| trapped instructions | 438 sites, 32 mnemonics, all SSE2 |

The trapped instructions are the SSE2 paths of the CRT math library:
movlpd 53, mulsd 46, addsd 40, mulpd 34, subsd 26, movd 25, movapd 24, addpd 19,
pextrw 19, andpd 18, movq 17, psrlq 15, movsd 14, psllq 12, pshufd 10, xorpd 9,
pcmpeqd 8, comisd 7, orpd 6, pmovmskb 6, unpcklpd 6, pinsrw 5, psubd 4, divsd 3,
shufpd 3, pxor 2, stmxcsr 2, cvtdq2pd 1, cvtsd2si 1, pmaxsw 1, psubq 1, ucomisd 1.
They should be unreachable: `cpuid` reports a CPU without SSE2 and
`IsProcessorFeaturePresent` cannot be resolved, so the CRT selects its x87 paths.

The seven run-time dispatched jumps are three virtual tail calls
(`jmp [reg+4]` at 0x406347, 0x406367, 0x406374), one more at 0x52006b, and three
`jmp eax` in the CRT's exception unwinding code (0x5283e6, 0x5283f2, 0x528628).
The first four target function entries, which the dispatch table handles; none
of the seven has been executed yet. The last three jump into the middle of
functions and need the exception milestone.

## Imports

68 of the 219 imports have handlers, all in kernel32: version queries, module
handle and file name, command line, environment, startup info, standard handles,
last error, the heap functions, `VirtualAlloc`/`Free`/`Protect`, the `IsBad*Ptr`
checks, TLS, critical sections, `InterlockedExchange`, tick count, performance
counter, system and local time, `Sleep`, `GetSystemInfo`, code page and string
type queries, `MultiByteToWideChar`/`WideCharToMultiByte`, `LCMapString`,
`lstrlen`/`lstrcmp`/`lstrcat`, `CloseHandle`, `ExitProcess`, `TerminateProcess`,
`SetUnhandledExceptionFilter`. `GetProcAddress` and `LoadLibraryA` always fail,
which sends the CRT down its fallback paths.

36 distinct imports are called before the stop at the 37th. `--trace-imports`
logs each call.

## Findings about the executable

- It is an unpacked dump of a protected image. The entry point is the ordinary
  MSVC `WinMainCRTStartup` and the code section is plain code. The import table
  was rebuilt by a tool and lives in the `.phnx` section.
- Two IAT slots are named `LockResource`. The one the CRT's `_ioinit` calls is
  really `SetHandleCount`: the two are the same routine in NT's kernel32. The
  handler returns its argument, which is correct for both.
- Fourteen "imports" of `ntdll!RtlLeaveCriticalSection` are not imports. They
  are the handler fields of SEH scope tables in `.rdata` (0x544bd0, 0x544be0,
  0x544c08, ...) that the import rebuilder overwrote, apparently because each
  `__finally` funclet leads to `LeaveCriticalSection`. Normal execution calls the
  funclets directly and is unaffected. Exception unwinding through those frames
  would call the wrong address; the entries can be repaired from the funclet
  that each owning function calls (for `free` at 0x5250c0 it is 0x525113).
- The code section contains a 0x1070-byte data table at 0x5363e0. The pointer
  scan rejects it.
- DirectDraw, DirectSound and DirectInput are not in the import table; the
  program loads `ddraw.dll`, `dsound.dll` and `dinput8.dll` by name.

## Known gaps

Control flow
- No SEH or C++ exception dispatch. `RaiseException` and `RtlUnwind` have no
  handler, the three `jmp eax` sites would fail, and any return-address mismatch
  is fatal. `setjmp`/`longjmp` fails the same way.
- One guest thread. `CreateThread` has no handler, critical sections only keep
  their bookkeeping fields, the heap is not locked, and `lock` prefixes are
  ignored (`xadd` and `cmpxchg` are not atomic).
- An indirect call or jump to an address that is not a lifted function entry is
  fatal. `rt_call_slow`/`rt_jmp_slow` are where an interpreter fallback goes.
- A divide error or `int3` is fatal instead of raising a guest exception.
- Guest recursion uses the host stack as well as the guest stack.

Arithmetic
- x87 values are doubles. That matches the 53-bit precision the CRT selects, but
  an integer above 2^53 loaded with `fild qword` loses bits, 80-bit loads and
  stores round to double, and 64-bit precision mode is treated as 53-bit.
- The rounding mode is honoured by `fist`/`fistp`/`frndint` only; arithmetic
  always rounds to nearest. 24-bit precision is applied to arithmetic results.
- `fsin`, `fcos`, `fptan`, `fpatan`, `fyl2x`, `fyl2xp1`, `f2xm1` use the host
  libm and are not bit-identical to x87. `fprem` always completes in one step.
- x87 exception flags, the C1 flag and stack overflow/underflow are not modelled.
  The sign and payload of a generated NaN are the host's (positive on aarch64,
  negative on x86).
- SSE2 and MMX instructions are trapped (see above).
- 16-bit addressing and segment registers other than FS are trapped; none occur.

Environment
- Guest addresses at or above 1 GiB fault. `VirtualAlloc` at a caller-chosen
  address outside an existing reservation fails, and freed regions and large
  heap blocks are not recycled.
- Strings are treated as Latin-1 (ACP 1252). `LCMAP_SORTKEY` is not supported.

Performance (deliberately not addressed yet)
- Registers and flags live in memory, and every flag is considered live across
  calls and returns. Moving registers to locals and adding call-graph flag
  summaries are the obvious next optimisations.

## Next milestone

Reach `WinMain` and the first frame of the message loop:

1. Guest callbacks and control flow: a `rt_call_guest(addr, args...)` helper for
   host-to-guest calls (window procedures, thread entry points), `CreateThread`
   on pthreads with a `CPU` and TEB per thread and real critical sections, and
   SEH (`RaiseException`, `RtlUnwind`, the `RT_RETCHECK` unwind path, repair of
   the fourteen scope table entries).
2. user32 on SDL2: window classes, `CreateWindowExA`, the message queue, timers
   and input, enough for the hidden notification window and the main window.
3. `LoadLibraryA`/`GetProcAddress` returning host-implemented modules, starting
   with DirectDraw (guest-visible COM vtables backed by an SDL texture).
4. Files, registry and sockets: `CreateFileA` and friends with a drive mapping,
   advapi32 registry calls backed by a small settings file, winsock on BSD
   sockets, DirectSound on SDL audio.
