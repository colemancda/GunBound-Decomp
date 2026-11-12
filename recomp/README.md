# Static recompilation of the GunBound client

This directory turns the original 32-bit x86 Windows executable (`orig/GunBound.gme`)
into a native Linux program by lifting every function to C and linking the result
with a runtime that stands in for Windows. The target device is a Retroid
Pocket 5 running Linux (aarch64, glibc); a native x86_64 build exists for debugging.

It is independent of the hand decompilation in `src/`: nothing here reads those
sources. The only shared input is `PROGRESS.csv`, used for function start addresses
and for the names shown in guest call stacks.

Nothing derived from the game binary is committed. The lifted C, objects and
binaries live under `recomp/build/`, which is ignored, and the program needs the
original executable and the game's data files at run time.

## Status: milestone 2

The game starts, initialises DirectDraw, Direct3D, DirectInput and its network
engine, and runs its main loop at its own 20 frames per second: the Softnyx
logo, the GunBound title screen and the world list, with the software cursor,
bitmap text, widgets and the wipes between screens. With no server configured
it shows its own "Access time has expired" dialog; clicking OK takes it through
its shutdown to `ExitProcess(0)`.

The x86_64 build and the aarch64 build (under `qemu-aarch64`) behave the same.
On a virtual clock (see below) the frames they present are identical pixel for
pixel, which `test/frames.sh` checks.

Not there yet: sound (the game is told there is no sound device and runs
silent), the textured Direct3D path used in battle (implemented but never
exercised), anything that needs a server, and input devices other than a
pointer and a keyboard.

## Building and running

```
recomp/build.sh host        # -> recomp/build/host/gunbound
recomp/build.sh aarch64     # -> recomp/build/aarch64/gunbound

token=$(recomp/tools/make_token.py myname)
recomp/build/host/gunbound --exe orig/GunBound.gme --gamedir /path/to/game \
    --savedir /path/to/saves --cmdline "$token"

sysroot=$(aarch64-buildroot-linux-gnu-gcc -print-sysroot)
qemu-aarch64 -L $sysroot recomp/build/aarch64/gunbound --exe orig/GunBound.gme ... --headless
```

Requirements: python3 with `capstone` and `pefile`, gcc, ninja, SDL2 (headers and
library; `NO_SDL=1` builds a headless-only program); for aarch64 a glibc cross
compiler with SDL2 in its sysroot (`AARCH64_CC`, default the batocera h616
buildroot gcc). `build.sh` documents its environment variables. On the 4-core
development machine lifting takes 14 s and compiling about a minute; a change to
the runtime alone rebuilds in seconds.

What the game needs:

- **Its data files** in `--gamedir` (default: the directory of `--exe`):
  `graphics.xfs`, `sound.xfs`, `avatar.xfs` and the four `.dat` files, the set
  pinned by hash in the top-level README. File names are matched without regard
  to case. A damaged `graphics.xfs` shows as a message box with empty caption and
  text followed by exit: the strings for the real message are in that archive.
- **A session token as its whole command line.** The game exits at once unless
  `GetCommandLineA()` is exactly 96 characters, the hexadecimal form of three
  AES blocks its launcher builds from the user name and password.
  `tools/make_token.py USER [PASSWORD]` builds one the same way, reading the key
  from `orig/Launcher.cs`; pass it with `--cmdline`. The token is only looked at
  by the server at login.
- **Registry values**, kept in a text file in `.reg` format (`--registry`, default
  `recomp-registry.txt` in the save directory). It is created with the two values
  the game cannot start without, under `HKEY_LOCAL_MACHINE\Software\Softnyx\GunBound`:
  `Location` (`C:\GunBound\`, with the trailing backslash) and `Version` (280: the
  game compares it with the version stored in `graphics.xfs` and `sound.xfs`). Add
  `"IP"="..."` and `"Port"=dword:...` there to point the game at a server.

Options:

| | |
|---|---|
| `--exe PATH` | the original executable (default `$RECOMP_EXE`, then `./GunBound.gme`) |
| `--gamedir DIR` | the game's files, the guest's `C:\GunBound` |
| `--savedir DIR` | where the game's writes go (default: the game directory). A different directory is an overlay: it is looked at first and is the only place files are created, changed or deleted, so the game's files can be kept read-only. A file there is copied from the game directory the first time it is opened for writing. |
| `--cmdline STRING` | the guest command line, verbatim |
| `--registry FILE` | registry backing file |
| `--headless` | no window |
| `--scale N`, `--fullscreen` | window size as a multiple of 800x600, or a letterboxed full-screen window |
| `--dump-frame N`, `--dump-path FILE` | write presented frame N (1 = first) as a PNG |
| `--frames N` | exit after N presented frames |
| `--input SCRIPT` | synthetic input, `"FRAME:command;..."`: `move X Y`, `down`, `up`, `rdown`, `rup`, `key VK DIK`, `text STRING`, `quit` |
| `--virtual-clock` | guest time advances with the main thread's work instead of real time: runs are repeatable and as fast as the machine allows |
| `--trace-imports`, `--verbose` | log every host-function call; log window messages, files, registry, sockets and COM object creation |

Exit status: the guest's own exit code, or 2 for a setup error, 3 for an
unimplemented import or COM method, 4 for an unimplemented instruction,
unsupported control flow or an unhandled guest exception, 5 for a host fault
(reported with the guest address and guest call stack).

Debugging: the lifted functions are ordinary C functions named `f_<address>`, so
`gdb` can break on them (`break f_0040eaa0`, `finish`, then
`print/x rt_cpu()->r[0].d` for EAX).

## Tests

```
recomp/test/run.sh host|aarch64      # instruction semantics against a real x86 CPU
recomp/test/frames.sh [frames...]    # whole program: host and aarch64 frames must match
```

`test/snippets.S` contains 115 hand-written x86 functions. `run.sh` runs them
natively as a freestanding 32-bit program to obtain reference results, lifts the
same bytes, runs the lifted code and compares: 93128 input vectors, covering
adc/sbb, shifts and rotates by CL, all multiply and divide forms, the sixteen
condition codes, the rep string instructions in both directions, jump tables
(including the two shapes of the C run-time's memcpy), every kind of call, x87
arithmetic, and a non-local transfer of control from a deep callee into a
continuation of an outer activation, through recursion. Flags the processor
leaves undefined are masked. The lifted code is checked both with and without
the flag-liveness pass. `expected.txt` holds the reference output for machines
that cannot execute 32-bit x86 code.

`frames.sh` runs the game headless on the virtual clock, dumps a few frames from
the host build and from the aarch64 build under qemu, and requires them to be
identical. It needs the game's files (`GAMEDIR`).

## Design

### Lifter (`lift/`)

`lift.py` drives `analyze.py` (discovery) and `translate.py` (instruction
semantics) and writes `chunk_NNN.c`, `funcs.h`, `tables.c` and `report.txt`.

*Function starts* are the PE entry point, the `addr` column of `PROGRESS.csv`,
every direct call target, and addresses found as code immediates or as dwords in
the data sections, provided they lead to plausible code. That last group is how
the C++ exception funclets, catch continuations, callbacks and SEH handler labels
get lifted: nothing calls them directly. Pointers into the middle of an
instruction are rejected.

*Bodies* come from recursive descent, so jump tables and other data in the code
section are never decoded. A jump to another function's start is a C tail call; a
block shared by two functions is emitted in both.

*Jump tables* (`jmp [reg*4 + table]`) are sized from the preceding
`cmp reg, N; ja default`, through a byte index table when there is one, and
otherwise by scanning entries until they stop being code addresses. Leading
slots that hold no code address are skipped, and a table that is indexed
backwards from the address past its end is collected from below. The emitted
code loads the target from guest memory and switches on it.

*Calling model.* One C function per guest function, `void f_XXXXXXXX(CPU *c)`.
Registers, flags and the x87 stack are fields of `CPU`. The guest stack is in
guest memory and is used literally: `call` stores the guest return address and
calls the C function, `ret N` pops it and returns. Helpers that play with the
stack, such as `__SEH_prolog` and `_chkstk`, work unchanged.

*Non-local returns.* After each call the caller checks that the address the
callee's `ret` popped is the one it pushed. A mismatch means the guest stack was
unwound past this frame: an SEH handler or a C++ catch resumed in an outer
function (whose continuation is lifted as a function of its own), and that
function returned to *its* caller. Lifted functions keep no state in host
locals, so the host stack is unwound by simply returning from every C frame
until the one whose call pushed the address that was popped, identified by the
return address and the stack slot it was read from. Host code that called into
the guest (`rt_call_guest`) takes part in the same protocol.

*Atomic instructions.* `lock xadd`, `lock cmpxchg` and `xchg` with memory are
lifted as atomic operations; a `lock` prefix on anything else is trapped.

*Flags* are computed eagerly, but only those a later instruction can read: a
per-function liveness pass removes the rest. Calls, returns and indirect jumps
are treated as reading every flag.

*Unsupported instructions* become `rt_unimplemented_insn(c, addr, "mnemonic")`,
so the output always compiles. The lifter lists them in `report.txt`.

*Image repairs.* The lifter recovers the fourteen SEH scope-table handler fields
that the import rebuilder overwrote (see Findings) and emits them as a patch
table that the loader applies.

### Runtime (`runtime/`)

| file | |
|---|---|
| `cpu.h` | CPU state and the inline helpers the lifted code uses |
| `mem.c` | the guest address space, 1 GiB reserved at host address 4 GiB so that guest address `a` is host address `0x100000000 + a` (`-DRT_DYNAMIC_BASE` uses a variable base); the guest heap and the `VirtualAlloc` arena, both locked |
| `loader.c` | maps the PE image, points every IAT slot at a fake address, applies the lifter's patches; refuses an executable whose code section does not match the lifted one |
| `dispatch.c` | indirect calls, host-function dispatch, `rt_call_guest`, the non-local return search, guest call stacks and the fault handler |
| `thread.c` | guest threads on pthreads (a `CPU`, TEB and guest stack each), the handle table, events, mutexes, the wait functions, critical sections, TLS, the guest clock |
| `seh.c` | `RaiseException` and `RtlUnwind` over the guest's SEH chain |
| `imports.c`, `misc.c` | the rest of kernel32, modules (`LoadLibraryA`/`GetProcAddress`), winmm, ole32 |
| `file.c`, `registry.c` | files with the save-directory overlay, resources; the registry file |
| `winsock.c` | ws2_32 on BSD sockets, with a poller thread for `WSAAsyncSelect` and `WSAEventSelect` |
| `user32.c` | window classes, windows, per-thread message queues, timers, focus and activation, a built-in EDIT class, `wsprintfA`, gdi32 and imm32 |
| `video.c` | the SDL2 window, input translation, the raw input log, scripted input, PNG output |
| `ddraw.c`, `raster.c` | DirectDraw 7 surfaces and the Direct3D 7 device; the triangle rasteriser |
| `dinput.c` | DirectInput 8 keyboard and mouse |
| `x87.c` | the less common x87 operations |

Guest layout: system block at 0x20000, main stack 0x30000-0x130000, image at
0x400000, heap from 0x1000000, `VirtualAlloc` arena (and thread stacks) from
0x20000000, fake host-function addresses at 0x3FF00000.

*Host functions.* Every import, COM method and `GetProcAddress` result is a fake
guest address that dispatches to a C handler taking the stdcall arguments. A
slot without a handler stops the program with the name of what was called and
the guest call stack. DirectX objects are small guest-memory blocks holding a
vtable of such addresses and an index into host state.

*Windows and input.* Window procedures are guest functions. Messages are queued
per guest thread; `SendMessage` across threads waits for the owner to pump. The
thread that opens the video layer is the only one that talks to SDL: it turns
pointer, key and text events into `WM_*` messages for the main window or the
focus window, and keeps the state DirectInput reads. Frames reach the window as
RGB565 through a streaming texture scaled to fit.

*Direct3D.* Triangles of pre-transformed vertices are rasterised in software
with Direct3D 7's rules (pixel centres at integer coordinates, top-left fill
rule, 28.4 fixed-point coverage), stage-0 texture and alpha operations, point or
bilinear sampling, colour key, alpha test, blending and a 16-bit depth buffer.

## Lifter coverage

From `report.txt` for the current image:

| | |
|---|---|
| functions | 5653 (2404 from PROGRESS.csv, 12 more call targets, 2960 + 235 code pointers from data and immediates, 42 labels) |
| instructions | 361391 unique, 368702 emitted |
| code section bytes covered | 1284450 of 1323008 |
| jump tables | 133, all resolved (85 from the bounds check, 46 by scanning, 2 by scanning backwards) |
| indirect jumps | 133 table, 11 import thunks, 7 dispatched at run time |
| indirect calls | 13532 |
| decode failures | 0 |
| scope tables repaired | 14 |
| trapped instructions | 438 sites, 32 mnemonics, all SSE2 |

The trapped instructions are the SSE2 paths of the CRT math library. They should
be unreachable: `cpuid` reports a CPU without SSE2 and `IsProcessorFeaturePresent`
cannot be resolved, so the CRT selects its x87 paths. None has been reached.

The seven run-time dispatched jumps are four virtual tail calls
(0x406347, 0x406367, 0x406374, 0x52006b) and three `jmp eax` in the CRT's
exception code: `_JumpToContinuation` (0x5283e6), `_CallMemberFunction`
(0x5283f2) and the translator guard (0x528628). Their targets must be lifted
function entries; catch continuations are, because the catch funclets name them
as immediates.

## Imports

187 of the 219 entries in the import table have handlers. Of the 32 without,
14 are not imports at all (the `ntdll!RtlLeaveCriticalSection` entries, see
Findings). The other 18 have not been reached:

- advapi32: the ten `Crypt*` functions, `InitializeSecurityDescriptor`,
  `SetSecurityDescriptorDacl`
- kernel32: `CreatePipe`, `PeekNamedPipe`, `DuplicateHandle`, `GetLocaleInfoA`,
  `GetDateFormatA`, `GetTimeFormatA`

Handlers that deliberately do less than Windows: `CreateProcessA` and
`ShellExecuteA` refuse and log; `DirectSoundCreate8` reports no sound device;
`TerminateThread` cancels the thread at its next blocking call;
`SetEnvironmentVariableA`, `SetFileAttributesA` and `FlushFileBuffers` succeed
without effect; `GetProcAddress` knows only what the runtime implements.

A run from start to the world list and out through the game's shutdown calls
105 distinct imports and 42 COM methods.

## Findings about the executable

- It is an unpacked dump of a protected image. The entry point is the ordinary
  MSVC `WinMainCRTStartup` and the code section is plain code. The import table
  was rebuilt by a tool and lives in the `.phnx` section.
- Two IAT slots are named `LockResource`. The one the CRT's `_ioinit` calls is
  really `SetHandleCount`: the two are the same routine in NT's kernel32. The
  handler returns its argument, which is correct for both.
- Fourteen "imports" of `ntdll!RtlLeaveCriticalSection` are the handler fields of
  single-entry `__try/__finally` scope tables in `.rdata` (0x544bd0, 0x544be0,
  0x544c08, ...) that the import rebuilder overwrote, apparently because each
  funclet leads to `LeaveCriticalSection`. Normal execution calls the funclets
  directly and is unaffected; unwinding through those frames would call the
  wrong address. Each true handler is the target of the direct
  `or dword ptr [ebp-4], -1; call funclet` in the owning function (for `free` at
  0x5250c0 it is 0x525113); the lifter derives all fourteen.
- The code section contains a 0x1070-byte data table at 0x5363e0, which the
  pointer scan rejects, and the CRT's memcpy and memmove use jump tables that are
  indexed from 1 or backwards from their end.
- DirectDraw, DirectSound and DirectInput are not in the import table; the
  program loads `ddraw.dll`, `dsound.dll` and `dinput8.dll` by name and calls
  `DirectDrawCreateEx`, `DirectSoundCreate8` and `DirectInput8Create`.
- The first constructors run before `WinMain`: the network engine creates two
  hidden STATIC windows and calls `WSAStartup` from static initialisers.
- `WinMain` returns immediately unless the command line is exactly 96
  characters (0x40dc59), which it parses as 48 hexadecimal bytes.
- The settings key is `HKEY_LOCAL_MACHINE\Software\Softnyx\GunBound`. `Location`
  is concatenated with file names without a separator in places, so it must end
  in a backslash.
- The archive code opens with `OPEN_ALWAYS`, so a missing archive is created
  empty, and has a read-write mode; every open seen so far (`graphics.xfs`,
  `Avatar.xfs`, `sound.xfs`) is read-only. `WinMain` deletes `test.txt` and
  `c:\comsik.txt` when it starts. `InitGame` fails with code 0xcd or 0xce when
  the version in `graphics.xfs` or `sound.xfs` differs from the registry's.
- Direct3D is used on every frame, not only in battle: `GameTick` clears through
  the device, and the wipe between screens and the dimming behind a dialog are
  untextured triangles (FVF 0x244, triangle fans) drawn over the software-blitted
  back buffer. The frame is presented with `Blt` from the back buffer to the
  primary surface; `Flip` is not called.
- The pointer is read twice: window messages carry absolute positions for the
  widgets, while the visible cursor is moved by DirectInput's relative data
  (buffered `GetDeviceData` with 20-byte records), starting at the centre.
- At start-up the game also connects to `localhost:8355` and sends a short
  presence message there; the broker connection goes to the registry's `IP` and
  `Port` (the launcher's default is 8372) and starts with a 10-byte request.
- The only C++ `try` blocks in the image are the 28 in STL and ATL container
  code that clean up and rethrow; nothing in the game catches an exception and
  continues. All 28 handlers are `catch (...)`.

## Known gaps

Control flow
- C++ exceptions and SEH are implemented but have only been exercised by the
  self-test's synthetic non-local return: no path in the game short of running
  out of memory raises an exception.
- Hardware exceptions (access violation, divide error, `int3`) are not turned
  into guest exceptions; they stop the program with a diagnostic.
- `setjmp`/`longjmp` and any other jump to an address that is not a lifted
  function entry are fatal. `rt_call_slow`/`rt_jmp_slow` are where an interpreter
  fallback would go.
- A stale activation of a call site could claim a non-local return only if it
  were the innermost frame to check and expected the very address popped; the
  CRT's unwinding code always sits in between.
- Guest recursion uses the host stack as well as the guest stack (16 MiB per
  created thread).

Arithmetic
- x87 values are doubles. That matches the 53-bit precision the CRT selects, but
  an integer above 2^53 loaded with `fild qword` loses bits, 80-bit loads and
  stores round to double, and 64-bit precision mode is treated as 53-bit.
- The rounding mode is honoured by `fist`/`fistp`/`frndint` only; arithmetic
  always rounds to nearest. 24-bit precision is applied to arithmetic results.
- `fsin`, `fcos`, `fptan`, `fpatan`, `fyl2x`, `fyl2xp1`, `f2xm1` use the host
  libm and are not bit-identical to x87. `fprem` always completes in one step.
- x87 exception flags, the C1 flag and stack overflow/underflow are not modelled.
- SSE2 and MMX instructions are trapped. 16-bit addressing and segment registers
  other than FS are trapped; none occur.

Windows
- No sound.
- Direct3D: textured drawing, bilinear filtering, colour keys and the depth
  buffer are implemented from the documentation but nothing has drawn a textured
  triangle yet, so they are unverified. Untransformed vertices, lines, points, a
  second texture stage, fog and specular colour are not implemented and are
  reported when asked for. Interpolation is not perspective correct.
- Input: pointer and keyboard only. The visible cursor follows relative motion,
  so an absolute pointer (a touchscreen) stays in step only while the game does
  not clamp or scale that motion. No gamepad mapping, no on-screen keyboard.
- The EDIT control keeps text and a caret position but draws nothing (the game
  draws the text itself) and has no clipboard or selection editing.
- Strings are Latin-1 (code page 1252). `LCMAP_SORTKEY` is not supported.
- Window messages the game does not depend on are not generated (`WM_PAINT`,
  `WM_SIZE`, `WM_SETCURSOR`, non-client messages).
- `TerminateThread` does not free the thread's stack. Guest addresses at or
  above 1 GiB fault; `VirtualAlloc` at a caller-chosen address outside an
  existing reservation fails.
- Winsock: `WSAAsyncSelect`/`WSAEventSelect` have been exercised for connecting
  and sending against a plain TCP listener, not against a game server. Only
  IPv4; no `listen` (the image does not import it); out-of-band data is ignored.

Performance (not addressed yet)
- Registers and flags live in memory, and every flag is considered live across
  calls and returns. The rasteriser is a straightforward per-pixel loop. Even so
  the title and world-list screens run at full speed under `qemu-aarch64`.

## Next milestone

1. Run against a server: log in, list worlds, enter the lobby. This exercises
   the socket notifications, the EDIT control and keyboard input for real, and
   will reach the first of the missing imports (the `Crypt*` functions are the
   likely candidates) and the lobby's panels.
2. Battle: verify the textured Direct3D path against the original's frames,
   then speed up the rasteriser where a real device needs it.
3. Sound: DirectSound buffers on an SDL audio stream, including the streaming
   thread the game uses for music.
4. The device: build against its SDL2, full-screen scaling to 1080p, touch as an
   absolute pointer (feed DirectInput the difference between the touch position
   and the game's cursor), gamepad as pointer and keys, text entry without a
   keyboard.
5. Robustness: guest exceptions from host faults, and an interpreter fallback for
   code reached only through computed addresses.
