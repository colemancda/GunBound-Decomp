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

## Status: milestone 4

The aarch64 build runs on the handheld. On a Retroid Pocket 5 with ROCKNIX it
starts from a launcher in the Ports menu's directory, fills the screen, plays
sound, logs in to a server on the local network and plays a battle against a
client on a PC at the game's own frame rate. A game controller and the
touchscreen are input devices now: the left stick moves the pointer, A is the
space bar, a finger is the pointer with the left button held. All of that was
driven over ssh by scripted input; see "The handheld" for what exactly was
checked on the device and what still waits for someone to hold it.

What milestone 3 reached is unchanged:

The game runs against a server. Driven by scripted input, without a display,
the x86_64 build goes from the Softnyx logo and the title screen to the world
list sent by the broker, logs in to the world server, enters the lobby, creates
a room or joins one, and plays: two instances on one machine load a stage, take
turns, charge and fire shots, and the terrain is blown away under the
explosions. The stage background and the textured and blended Direct3D effects
are drawn, and the music and effects are mixed (DirectSound; measured, not yet
heard). Nothing in the game's own
protocol code needed help: its login uses its own SHA-1 and AES, not the
`Crypt*` imports.

How far it gets depends on the server. With the reference server
(the Swift `GunBound` package) it reaches the ready room, where the client that
joined does not see the players who were there before it, and it fails when
the game is started: three things in that server's packets are not what this
client reads. With those changed in a scratch copy of the server the battle
runs. See "Against the reference server".

The window scales to any size (aspect fit, whole multiples or stretched; sharp,
nearest or linear), switches to full screen with Alt+Enter, and was exercised
on a Wayland compositor with an OpenGL renderer at 1920x1080, though not on a
physical screen (see "What was verified where").

The x86_64 build and the aarch64 build (under `qemu-aarch64`) behave the same
up to the world list: on a virtual clock the frames they present are identical
pixel for pixel, which `test/frames.sh` checks.

Not there yet: text entry without a keyboard, and any work on speed.

## Building and running

```
recomp/run.sh --gamedir /path/to/game --server
```

builds the host program if needed, starts the reference server's broker and
world server on 127.0.0.1 (`--server`; they stop when the game exits), makes
the session token for the account `admin` / `1234`, and starts the game in a
window. Useful options: `--user NAME --password PW`, `--broker HOST[:PORT]` for
a server that is already running, `--fullscreen`, `--scale N`,
`--scale-mode fit|integer|stretch`, `--filter sharp|nearest|linear`, and
`--instance N` to run several instances on one machine (use it on each: N = 1,
2, ...). Anything after `--` goes to the game binary. The game's data directory
can also be given as `GUNBOUND_GAMEDIR`; saves and the registry file go to
`recomp/build/save/`, the server's state and logs to `recomp/build/server/`.
`recomp/run.sh --help` lists everything.

In the game: click the world, then SERVER; CREATE makes a room, a click on a
room card and JOIN enters one; in a room the master's START (READY for the
others) begins the game once the teams are even. In battle the space bar
charges and fires, which is the only battle control exercised so far.
Alt+Enter switches full screen. A game controller works as described under
"Controller and touch".

The steps by hand:

```
recomp/build.sh host        # -> recomp/build/host/gunbound
recomp/build.sh aarch64     # -> recomp/build/aarch64/gunbound

token=$(recomp/tools/make_token.py myname mypassword)
recomp/build/host/gunbound --exe orig/GunBound.gme --gamedir /path/to/game \
    --savedir /path/to/saves --cmdline "$token" --broker 127.0.0.1:8372

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
  from `orig/Launcher.cs`; pass it with `--cmdline`. The program can do the
  same itself, for machines without Python: `--login USER PASSWORD` reads the
  key from `Launcher.cs` (or from `launcher.key`, 32 hexadecimal digits) in
  the game or save directory, or from the file named by `--login-key`. The
  key is in neither the repository nor the program. The token is only looked
  at by the server at login.
- **Registry values**, kept in a text file in `.reg` format (`--registry`, default
  `recomp-registry.txt` in the save directory). It is created with the two values
  the game cannot start without, under `HKEY_LOCAL_MACHINE\Software\Softnyx\GunBound`:
  `Location` (`C:\GunBound\`, with the trailing backslash) and `Version` (280: the
  game compares it with the version stored in `graphics.xfs` and `sound.xfs`), and
  with the settings the game's launcher provisions (`Background`, `Effect3D`, the
  volumes, `MouseSpeed`; without `Background` a stage has a flat colour behind
  it). `--broker HOST[:PORT]` writes the server's address there (`IP`, `BuddyIP`,
  `Port`).
- **A server**: a broker that lists the worlds, and a world server. Without one
  the world list stays empty and the game shows its "Access time has expired"
  dialog.

Options:

| | |
|---|---|
| `--exe PATH` | the original executable (default `$RECOMP_EXE`, then `./GunBound.gme`) |
| `--gamedir DIR` | the game's files, the guest's `C:\GunBound` |
| `--savedir DIR` | where the game's writes go (default: the game directory). A different directory is an overlay: it is looked at first and is the only place files are created, changed or deleted, so the game's files can be kept read-only. A file there is copied from the game directory the first time it is opened for writing. |
| `--cmdline STRING` | the guest command line, verbatim |
| `--registry FILE` | registry backing file |
| `--broker HOST[:PORT]` | the server that lists the worlds (default port 8372); stored in the registry file |
| `--local-address IP` | bind every socket to this address and report it as the machine's own. With 127.0.0.2, 127.0.0.3, ... (not 127.0.0.1) several instances can run on one machine |
| `--headless` | no window |
| `--login USER PASSWORD`, `--login-key FILE`, `--print-token` | make the session token from the launcher's key instead of taking it from `--cmdline`; print it and exit |
| `--scale N`, `--window-size WxH`, `--fullscreen` | window size as a multiple of 800x600 or in pixels; start full screen (Alt+Enter switches at any time) |
| `--scale-mode MODE` | `fit`: the largest picture with the game's aspect ratio (default); `integer`: whole multiples only; `stretch`: fill the window |
| `--filter FILTER` | `sharp`: point sampling up to the next whole multiple, then bilinear down to the picture's size (default); `nearest`; `linear` |
| `--no-sound`, `--dump-audio FILE` | tell the game there is no sound device; write the mixed sound to a WAV file instead of playing it (works headless) |
| `--dump-frame N[,N...]`, `--dump-every N`, `--dump-path FILE` | write presented frames (1 = first) as PNG files; a `%d` in the path is the frame number |
| `--dump-window` | frame dumps also write `FILE.window.png`, what the window shows after scaling |
| `--frames N` | exit after N presented frames |
| `--input SCRIPT`, `--input-file FILE` | synthetic input, `"FRAME:command;..."` or one step per line: `move X Y`, `click X Y`, `down`, `up`, `rdown`, `rup`, `key VK DIK`, `keydown VK DIK`, `keyup VK DIK` (hexadecimal), `text STRING`, `fullscr`, `quit`; for the controller `stick X Y`, `rstick X Y` (percent), `pdown B`, `pup B`, `ptap B`, `plug`, `unplug`; for a finger `tdown X Y`, `tmove X Y` (thousandths of the window), `tup`. `+N` as the frame counts from the previous step |
| `--no-pad`, `--pad-speed N`, `--pad-config FILE`, `--print-pad-config` | game controllers: ignore them; pointer speed at full deflection in game pixels per second (default 600); a mapping file; print the mapping in force, in that file's format |
| `--pad-virtual` | attach an SDL virtual controller that the `--input` controller commands drive, so that a test goes through SDL's controller code (needs a window; `SDL_VIDEODRIVER=dummy` provides one without a display) |
| `--trace-input` | log controller and touch input, the key, character and pointer messages the game's window procedures receive, and what its DirectInput devices read |
| `--guest-cpu N\|auto\|any` | confine all guest threads to one CPU (`auto`: the fastest one), which gives them x86's memory ordering; the default is `auto` except on x86, where it is `any`. See "Threads and memory ordering" |
| `--profile FILE` | sample the program counter as CPU time is used and write the counts at exit; `tools/profile_report.py FILE [BINARY]` prints the table |
| `--virtual-clock` | guest time advances with the main thread's work instead of real time: runs are repeatable and as fast as the machine allows |
| `--trace-net` | log the bytes of everything sent and received on sockets |
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

```
recomp/test/pad.sh [host|aarch64 ...]   # controller and touch, no device and no server
```

`pad.sh` runs the game to its world-list screen while a script pushes the left
stick, presses A, the right trigger and B, unplugs and plugs the controller,
drags a finger and ends with Back+Start. It passes when the pointer moved by
the right amount, the cursor the game draws is at that place in a dumped
frame, the space bar arrived as `WM_KEYDOWN`, `WM_CHAR` and `WM_KEYUP` and was
read down and up by the game's DirectInput keyboard, the trigger clicked, and
the finger pressed and released the left button at the mapped positions. Each
build is driven twice: headless, with the commands entering just below SDL,
and in a 1920x1080 window on SDL's dummy video driver with `--pad-virtual`,
where they are an SDL virtual joystick and SDL touch events and SDL's
controller mapping, hot-plug events and the scaling rectangle are on the path.
The SDL2 in the cross compiler's sysroot has neither the dummy video driver
nor virtual joysticks, so under qemu the second way is skipped; it was run by
hand on the device instead.

```
recomp/test/online.sh [HOST:PORT]    # two instances against a running server
```

`online.sh` needs a server (default: a broker on 127.0.0.1:8372). Two headless
instances of the host build log in as `admin` and `tester`; the first creates a
room, the second joins and readies, the first starts the game and both hold the
space bar when their turn may have come. It reports each stage from the packets
the clients received and leaves frames and logs in `recomp/build/online/`. It
takes about 90 seconds, because the game runs in real time. It also checks
that the room's title went out with its space and that the power bar filled
while the fire key was held. With `PAD=1` the space in the title and the fire
key are the controller's A button. The battle needs a server that sends what
the client reads (see "Against the reference server").

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
| `winsock.c` | ws2_32 on BSD sockets, with a poller thread for `WSAAsyncSelect` and `WSAEventSelect`; the local-address option and the network trace |
| `user32.c` | window classes, windows, per-thread message queues, timers, focus and activation, a built-in EDIT class, `wsprintfA`, gdi32 and imm32 |
| `video.c` | the SDL2 window and its scaling, input translation (pointer, keyboard, SDL game controllers, touch), the raw input log, scripted input, PNG output |
| `pad.c` | controller buttons, sticks and fingers turned into pointer and keyboard input; the mapping and its configuration file |
| `login.c` | `--login`: AES-128 and the session token |
| `profile.c` | `--profile`: the sampling profiler |
| `ddraw.c`, `raster.c` | DirectDraw 7 surfaces and the Direct3D 7 device; the triangle rasteriser |
| `dinput.c` | DirectInput 8 keyboard and mouse |
| `dsound.c` | DirectSound 8 buffers on a software mixer, played through SDL audio or written to a WAV file |
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
RGB565 through a streaming texture. The picture's rectangle in the window is
computed by the runtime (not by SDL's logical size), pointer positions are
mapped back through it, and pointer motion is reported in guest pixels, so
that the cursor the game draws from relative motion stays under the pointer.

*Controller and touch.* See the section of that name below.

*Sound.* The game creates a primary buffer and 16 two-second secondary buffers
(22050 Hz, 16 bit, stereo), decodes its own MP3 music and effects, and streams
into the buffers a half at a time while polling the play cursor. A buffer's
samples live in guest memory, so `Lock` returns pointers into the buffer. The
mixer resamples by linear interpolation to 44.1 kHz stereo and applies
DirectSound's volume and pan (hundredths of a decibel). SDL's audio callback
pulls the mix; with no device (headless, `--dump-audio`, a build without SDL) a
thread following the guest clock pulls it instead, so the play cursors advance
either way.

*Several instances on one machine.* The game binds UDP port 8363 for its
peer-to-peer traffic and sends its own events to itself at 127.0.0.1:8363.
`--local-address` gives an instance its own address: sockets are bound to it,
the machine's name resolves to it, and those datagrams to itself are sent
there.

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
Findings). The other 18 have not been reached, in a session that goes from
start-up through login, lobby, room and battle:

- advapi32: the ten `Crypt*` functions, `InitializeSecurityDescriptor`,
  `SetSecurityDescriptorDacl`. All of them are used only by one library
  linked into the image (around 0x520000-0x525000): it verifies a signed file
  (`CryptImportKey`, `CryptHashData`, `CryptVerifySignatureA`), decrypts with a
  derived key, and starts a child process through pipes. That is the shape of
  the anti-cheat loader the protection used; nothing calls it in this dump.
- kernel32: `CreatePipe`, `PeekNamedPipe`, `DuplicateHandle` (the same
  library), `GetLocaleInfoA`, `GetDateFormatA`, `GetTimeFormatA` (the C
  run-time's locale code)

Handlers that deliberately do less than Windows: `CreateProcessA` and
`ShellExecuteA` refuse and log; `TerminateThread` cancels the thread at its
next blocking call; `SetEnvironmentVariableA`, `SetFileAttributesA` and
`FlushFileBuffers` succeed without effect; `GetProcAddress` knows only what the
runtime implements.

A session through a battle calls 114 distinct imports and 51 COM methods.
Of the COM interfaces, `IDirectSound8` lacks `DuplicateSoundBuffer` and
`VerifyCertification`, `IDirectSoundBuffer8` lacks `SetFX`, `AcquireResources`
and `GetObjectInPath`, and a buffer's `QueryInterface` refuses everything
(no `IDirectSoundNotify`, no 3D interfaces); the game uses none of them. A call
to a missing method stops the program and names it.

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
  message there, 39 bytes with its window's name and the name of the screen it
  is on ("GunBound", "World list"). The address is fixed in the code, next to
  the `Software\Softnyx\GameBuddy` registry key that names an executable: it is
  the companion messenger program on the same machine, not a server. Nothing
  needs to answer; the game goes on when the connection is refused.
- The buddy server is a third service: the game connects to the registry's
  `BuddyIP` (its own address when there is none) at `BuddyPort`, 8352 by
  default, and tries again every so often. The reference server has no such
  service; the game carries on with an empty buddy list.
- The broker connection goes to the registry's `IP` and `Port` (the launcher's
  default is 8372) and starts with a 10-byte request; the game then connects to
  the world server the answer names.
- Login needs none of the `Crypt*` imports. The game has its own SHA-1 and AES:
  the user name goes out under a fixed key and the rest of the request under a
  key derived from the name, the password and the server's nonce.
- Peer-to-peer traffic uses UDP port 8363 on every client. A client sends its
  own events to itself as well, to 127.0.0.1:8363, and acts on them when they
  arrive; the ready room does not show the local player without that. After
  login it sends its four-byte session number to the world server's UDP port,
  and the server echoes it. Datagrams that are not acknowledged are repeated and
  finally sent through the server (opcode 0x4500); when that fails too the game
  shows "Communication is not done properly" and leaves the room.
- The game asks for the machine's own address with `gethostbyname` of its host
  name and passes it on. A host name that resolves to 127.0.1.1, as on Debian,
  would be useless to a peer, so the runtime answers with the address of the
  interface the default route uses.
- Sends go straight to `send`; only when it reports `WSAEWOULDBLOCK` is the
  packet queued for the next `FD_WRITE`.
- Sound is 16 streaming buffers filled a half at a time by the game's own MP3
  decoder (see Design); no `IDirectSoundNotify`, no static buffers.
- The only C++ `try` blocks in the image are the 28 in STL and ATL container
  code that clean up and rethrow; nothing in the game catches an exception and
  continues. All 28 handlers are `catch (...)`.

## Against the reference server

The server is the Swift package `GunBound` (`swift run GunBoundServer`, world
server on 8370, broker on 8372 with a directory file; accounts are created on
first login with the password 1234). `recomp/run.sh --server` starts both on
127.0.0.1 without changing anything in that package.

What works with it unchanged: the server list, login, the lobby with its
channel list and room list, creating a room, joining it from a second client,
the peer-to-peer exchange between the two, the ready state, and host migration
when the room's master leaves.

Three things in its packets differ from what this client reads. They were
found from the client's side: the bytes are what `--trace-net` logged, the
offsets are those of the client's handlers. With all three changed in a
scratch copy of the server, the same scripted session plays a battle.

1. *Join room response* (0x2111), the status byte of each player record. The
   record is 49 bytes: slot, name (12), address and port twice (12), two
   mobiles, team, status, avatar (8), guild (8), two ranks. The server sends
   the status as 0 for a player who is not ready:

   `00 61 64 6d 69 6e 00*7  7f 00 00 01 20 ab  7f 00 00 01 20 ab  ff ff  00  00  00 80 00 80 00 80 00 00 ...`

   The room list's packet handler (0x426ad0) stores that byte as the slot's state, where 0 means
   an empty slot, 1 a player and 3 a ready player (the join notification
   0x3010, which has no such byte, sets 1 itself). The joining client
   therefore shows every player who was already in the room as an empty slot.
   Sending 1 for "not ready" fixes it.

2. *Start game notification* (0x3432). Decrypted, the server's packet is

   `b2 62 00 00  02  02 00  00 61 64 6d 69 6e 00*7 00 ff ff 55 00 00 00 01 00  01 74 65 73 74 65 72 ...`

   that is, the room's settings (4 bytes), the map, the player count (2), the
   22-byte player records, then `00 ff` and the four bytes of the start
   request. The ready room's packet handler (0x4d38c0, at 0x4d4004) reads the map from the first byte, the
   count from the next two and the records from the fourth byte on: there is
   no settings field. Read that way the count is 0x62, the records are
   garbage, and the first player's name in the peer table loses its first
   character, so that no datagram addressed to that player is accepted any
   more and both clients end with "Communication is not done properly".
   Without the four leading bytes the packet is read as intended.

3. *Random mobiles and map.* For a player whose mobile is "random" the server
   means to pick one but sends 0xff (`Mobile.random` is the enumeration case,
   not the function that picks). The client expects an actual mobile there.
   The random map is picked from all cases including "random" (0) itself.

One run in about thirty stalled at "PLEASE WAIT" after connecting to the world
server: the server logged the connection and no request. It has not happened
again and the client was not being traced at the time, so which side was at
fault is not known.

## What was verified where

Everything above was driven by `--input` scripts and judged from dumped frames,
on the x86_64 build, in real time against the server.

- *Window, scaling, full screen*: on SDL's `wayland` driver with its OpenGL
  renderer, in a private headless GNOME Shell with one virtual 1920x1080
  monitor, and on SDL's `dummy` driver with the software renderer. The window's
  contents were read back (`--dump-window`): a 1440x1080 picture centred in
  1920x1080 for `fit`, 800x600 for `integer`, the whole screen for `stretch`,
  and the switch to full screen and back.
- *On the handheld*: see "The handheld".
- *Not verified*: SDL's `kmsdrm` and `x11` drivers, pointer and keyboard
  events of real devices arriving through SDL on the PC (the scripts enter
  below SDL's event translation; that path was last exercised in milestone 2),
  the Alt+Enter key itself (the script command `fullscr` calls the same
  function), and the sound by ear: SDL's audio ran on its `dummy` driver on
  the PC and on PulseAudio on the handheld, unheard.
- *Sound*: the mix written by `--dump-audio` during a session is continuous
  stereo without clipping, with music from the logo on; it has been measured,
  not listened to.
- *aarch64*: under qemu the instruction tests, the frame comparison, the
  controller test and, from the packaged launcher, login and the lobby; a
  battle on the device itself (qemu falls to a few frames per second in the
  ready room).

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

Threads
- See "Threads and memory ordering". With the default `--guest-cpu auto` the
  guest's threads share one CPU; with `--guest-cpu any` on aarch64 the unlocked
  rings listed there are exposed.

Windows
- Sound: no 3D buffers, effects or position notifications (the game uses none).
  The mixer has been checked by measuring its output, not by ear.
- Direct3D: textured, blended and colour-keyed drawing is now used all through a
  battle (backgrounds, smoke, flames, explosions, the aiming dial) and looks
  right, but it has not been compared with the original's frames. Untransformed
  vertices, lines, points, a second texture stage, fog and specular colour are
  not implemented and are reported when asked for; none was asked for.
  Interpolation is not perspective correct.
- Input: no on-screen keyboard, so a room title or a chat line needs a real
  keyboard. One finger only. A touch in the black bars beside the picture
  counts as a touch on the picture's edge.
- The EDIT control keeps text and a caret position but draws nothing (the game
  draws the text itself) and has no clipboard or selection editing.
- Strings are Latin-1 (code page 1252). `LCMAP_SORTKEY` is not supported.
- Window messages the game does not depend on are not generated (`WM_PAINT`,
  `WM_SIZE`, `WM_SETCURSOR`, non-client messages).
- `TerminateThread` does not free the thread's stack. Guest addresses at or
  above 1 GiB fault; `VirtualAlloc` at a caller-chosen address outside an
  existing reservation fails.
- Winsock: only IPv4; no `listen` (the image does not import it); out-of-band
  data is ignored. Two instances on one machine need `--local-address`.

Performance (not addressed yet)
- Registers and flags live in memory, and every flag is considered live across
  calls and returns. The rasteriser is a straightforward per-pixel loop.
- Measured on the development machine (Core i5-4590), two instances playing
  each other: the title and world-list screens need about 5% of a core; a
  91-second session with 40 seconds of battle (stage background and 3D effects
  on) used 35 seconds of CPU per instance, so the battle needs most of a core.
  The session also finished 4 seconds behind the game's 20 frames per second;
  whether that was the loading screen or battle frames overrunning their 50 ms
  has not been measured.
- Under `qemu-aarch64` the title and world-list screens run at full speed, the
  ready room at a few frames per second.
- A profile of one client through such a session (`--profile`, x86_64): 37% of
  the CPU time in `texel` and 30% in `rt_raster_triangle` (`raster.c`: the
  Direct3D rasteriser, almost all of it the stage background and the effects),
  11% in the game's LZHUF decompressor while loading (`LZHUFUpdate`,
  `DecodeChar`, `DecodeLZHUFBlock`), 4% in `State11_InBattle_ClearEffectTextures`,
  5% in the sprite blitters (`BlitSpriteRowClipped`, `BlitSprite16bpp`), 2% in
  the MP3 decoder; 28% lifted code in all, 70% runtime. On the Retroid Pocket 5
  the same session: 24% `rt_raster_triangle`, 22% `texel`, 7%
  `BlitSpriteRowClipped`, 6% `State11_InBattle_ClearEffectTextures`, 8% LZHUF,
  3% `FlushCompositorLayer`; 45% lifted code, 53% runtime. The device used 41 s
  of one core for the 92 s and kept the game's 20 frames per second; nothing
  has been optimised.

## Controller and touch

The game knows a mouse and a keyboard. It reads them three ways, and input
from a controller or a finger has to arrive on all of them at once:

- window messages with absolute positions (`WM_MOUSEMOVE`, the button
  messages) for the widgets, and `WM_KEYDOWN`/`WM_CHAR` for text fields;
- the DirectInput mouse, whose relative motion moves the cursor the game draws;
- the DirectInput keyboard, read in buffered mode by a thread of the game's
  own every 10 ms. Battle keys come only from here: the space bar going down
  starts charging and its release fires (0x4b82b0).

`pad.c` therefore produces exactly what `video.c` produces for a real mouse
and keyboard, through the same functions: a pointer step updates the absolute
position, queues `WM_MOUSEMOVE` and adds the same step to the relative motion
and the raw input log; a key sets the key state, logs a DirectInput event and
queues the key message, and a held key repeats as on Windows.

The mapping (`--print-pad-config` prints it in the format `--pad-config` reads):

| control | default |
|---|---|
| left stick | the pointer: nothing inside the dead zone (15% of the travel), then speed = `--pad-speed` (600 game pixels per second) x (remaining travel)^2, so that small deflections are precise and the rim is fast |
| right stick | the pointer at 0.35 of that speed |
| A | Space: down on press, up on release (charge and fire) |
| B | Escape |
| X, right trigger, left stick click | left mouse button |
| Y, left trigger | right mouse button |
| d-pad | arrow keys (move, angle) |
| Start | Enter |
| Back / Select | Tab |
| left / right shoulder | F7 / F8, the two function keys the battle's key handler acts on besides the item keys |
| Back + Start | close the game: the window's close message, and the process is ended two seconds later if it is still there |

A button can be any key (`key f1`, `key 0xVK 0xDIK`), a mouse button or
nothing, a stick the pointer at some speed, the arrow keys or nothing. F1 to
F6 (the item slots) are not on any button by default. Button names are SDL's
game controller names, so what "A" is depends on the mapping SDL has for the
device. A mouse click from a button or a finger is held for at least two
frames, because the game samples the buttons once a frame.

Controllers are SDL game controllers: every one with a mapping is opened, all
act as one, and they may come and go at any time; when one goes, everything
it held is released. A joystick without a mapping is reported with its GUID.

Touch: the first finger down is the pointer with the left button held, mapped
through the picture's rectangle like the mouse; other fingers are ignored
until it lifts. SDL's synthetic mouse events for touches are turned off. A
Wayland compositor reports the system pointer's unchanged position again
after every touch; such events are recognised and dropped, or the game's
cursor would jump back there.

## Threads and memory ordering

The game was written for x86, where all processors see each other's stores in
the order they were made (TSO). aarch64 does not promise that, and the lifted
code reads and writes guest memory with plain loads and stores. What the
game's threads share, from its code:

| thread (start routine) | count | what it does |
|---|---|---|
| main | 1 | everything else: `GameTick`, drawing, the window procedure |
| socket worker (0x405dc0, body 0x405dd0, events handled at 0x4e57c0) | 4 | one per TCP connection: `WSAEventSelect`, connect, `recv`, queued sends |
| input worker (0x4156b0, loop 0x4157b0) | 1 | every 10 ms: reads the DirectInput keyboard (0x4ede50) |
| heartbeat (0x4156c0, loop 0x415810) | 1 | every 10 s: sends a packet (0x401200) |
| UDP worker (0x4f47e0, body 0x4e6770) | 1 | peer-to-peer datagrams: receive, resend, keep alive |
| sound stream (0x4ef870, body 0x4ef880) | one per channel | every 100 ms: play cursor, refill a DirectSound buffer |

| shared state | writer -> reader | protection in the game |
|---|---|---|
| input event ring (indices 0x795070 / 0x795074) | `EnqueueInputEvent` 0x4f2da0 on the socket workers, the input worker and the main thread -> `ProcessInputEventQueue` 0x412130 on the main thread | none: the slot is written, then the index |
| per-connection receive ring (connection +0x24234 / +0x24238) | `ReceiveFramedPackets` 0x4e5610 on a socket worker -> `ProcessIncomingPackets` 0x4d27e0 on the main thread | none: data, then index |
| game event ring (0x793798 / 0x79379c) | `QueueGameEvent` 0x4e5dc0 on the UDP worker -> `PumpBattleActions` 0x412cc3 on the main thread | none: data, then index |
| sound channel fields (+0x14, +0x38, +0x4c) | play calls on the main thread -> the stream thread | written without the channel's lock, then `SetEvent` |
| connection state (+0x22a, +0x22c, socket +0x24) | socket worker <-> main thread | plain fields |
| send queue (connection +0x24a40) | main thread -> socket worker | critical section, correct |
| replay and broadcast state | main thread <-> UDP worker | critical sections and `InterlockedExchange` |
| key repeat timers (0xe52810 +0x258) | input worker <-> `GameTick` | none (a race on x86 as well) |

The three rings are the danger. Each publishes by storing the data and then
the index, with no lock and no locked instruction. On x86 that is enough for
one writer and one reader, because the reader cannot see the new index before
the data. On aarch64 it can: the two stores may become visible in either
order, and the main thread would then act on an event, a packet or a battle
action that is not there yet. (The input event ring has several writers and
is not safe on x86 either; that race is the game's own and is left alone.)

What the runtime does about it:

1. *One CPU for the guest* (`--guest-cpu`, on by default except on x86). All
   guest threads are confined to a single CPU, the fastest one. Threads that
   take turns on one processor see each other's stores in program order, which
   restores x86's guarantee completely, for these rings and for anything not
   found by reading the code, without touching the lifted code. The main
   thread is the only one that does much work, so little is lost. Threads the
   runtime and SDL start for themselves (SDL's audio thread, the socket
   poller, the graphics driver's) are not confined; what they share with the
   guest is guarded by host locks, apart from the sound mixer, which reads
   sample data the game is writing, as a sound card would.
2. *Full barriers where x86 had them.* `lock xadd`, `lock cmpxchg` and `xchg`
   with memory (about 37 sites, nearly all string reference counts) are atomic
   builtins followed and preceded by a full barrier on aarch64, because on x86
   they also order the plain loads and stores around them. The same barrier is
   in `EnterCriticalSection`, `LeaveCriticalSection`, `SetEvent`, `ResetEvent`,
   the wait functions and `InterlockedExchange`.

The second measure alone does not make the rings safe; it is the first that
does. With `--guest-cpu any` on aarch64 the rings are exposed. One battle on
the device ran that way without a visible fault, which shows only that the
window is small.

## The handheld

The target is a Retroid Pocket 5 (Snapdragon 865, 1920x1080, built-in
controller, touchscreen) running ROCKNIX.

```
recomp/package.sh [--login USER PASSWORD] [--broker HOST[:PORT]]
```

builds the aarch64 program and writes `recomp/build/dist/gunbound-rocknix/`
and `gunbound-rocknix.tar.gz`: `GunBound.sh`, the launcher that goes into
`/storage/roms/ports/`, and next to it the directory `gunbound/` with the
program (debug information removed), `gunbound.conf` (account, server
address, further options), `pad.cfg`, `README.txt` with the steps to copy it
to the device over ssh and run it, `BUILD-INFO.txt`, and an empty `game/` for
the user's own files. No game data goes into the package; the program is
derived from the game's executable, so the package is for the owner of the
game. `--login` adds a ready session token, so that the device needs no key;
otherwise the launcher makes the token on the device with `--login` from a
`Launcher.cs` in `game/` or a `launcher.key`.

The launcher follows the other ports on the device: it sources PortMaster's
`control.txt` and calls `get_controls` (which gives SDL the controller
mappings made in EmulationStation), selects sway's Wayland display, asks
PortMaster's helper to put the window full screen, logs to
`gunbound/log.txt`, and runs the program with `--fullscreen --scale-mode fit`.
If the port directory does not allow execution (a FAT card) it runs a copy
from `/tmp`. Arguments are passed on, so
`bash GunBound.sh --headless --frames 200 --dump-frame 150` works over ssh.

What the program needs: `/lib/ld-linux-aarch64.so.1`, `libc.so.6` and
`libm.so.6` with glibc symbols up to 2.38 (the batocera buildroot toolchain it
is built with), and `libSDL2-2.0.so.0`, 2.0.14 or newer. ROCKNIX release
20261101 has glibc 2.44 and SDL 2.32.10 (the real SDL2, with Wayland,
PulseAudio and PipeWire); its package files show glibc 2.40 in July 2025 and
2.41 from April 2026, so the floor of 2.38 is below anything recent.

Checked on the device (ROCKNIX 20261101, kernel 7.2), over ssh, with scripted
input:

- The installed port starts from `GunBound.sh`: a Wayland window on sway with
  SDL's OpenGL renderer, 1920x1080 with a 1440x1080 picture (read back with
  `--dump-window`), sound on PulseAudio.
- Login, lobby, creating a room and a whole battle against a client on a PC,
  with a server on the PC: 1750 frames in 92 s, the game's frame rate, using
  41 s of one core; datagrams in both directions, none relayed. The battle was
  run headless; on the screen only the path to the lobby was run, where
  presenting costs about 0.5 s of CPU per 330 frames.
- The controller code through SDL: the `pad.sh` scenario with `--pad-virtual`
  in the full-screen window (stick, A, trigger, hot-plug, B, Back+Start, on
  which the game closed by itself).
- The built-in controller is seen by SDL as a game controller ("DualSense
  Wireless Controller": ROCKNIX's InputPlumber presents the built-in pad as
  one) and its sticks' resting noise arrives as about 3% deflection, inside
  the dead zone: the pointer does not drift.
- The touchscreen: events injected into its kernel device arrive as SDL touch
  events and land where they should through the rotation of the panel and the
  picture's rectangle (the centre of the panel is 400,300).
- A battle with `--guest-cpu any` as well as with the default.

Not checked: anyone pressing the real buttons or touching the real screen
(events written to the built-in pad's kernel device are overwritten by its
next report, so its buttons could not be driven from a script); which
physical button SDL calls A with the user's EmulationStation mapping (the
mapping file says the one labelled A); a battle on the screen rather than
headless; starting it from the Ports menu instead of ssh; how long the
battery lasts.

## Next

1. *Play it by hand* on the device, and settle the controls: whether the
   pointer speed and curve suit the stick, which buttons should carry the item
   keys F1 to F6, and a way to enter text without a keyboard.
2. *Speed.* The device keeps up today (45% of one core over a session with a
   battle), but most of the runtime's share is the software rasteriser. The
   candidates are a span-based inner loop with the texture format and the
   blend mode resolved per triangle instead of per pixel, and the lifted
   blitters, which are compiled at `-O1` with every register in memory.
3. *The server.* The three packet differences listed above have to be settled
   in the server before a battle works against it.
4. *Robustness.* Guest exceptions from host faults, and an interpreter
   fallback for code reached only through computed addresses.
