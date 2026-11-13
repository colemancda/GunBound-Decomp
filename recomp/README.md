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

## Status: milestone 3

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
pixel for pixel, which `test/frames.sh` checks. Under qemu the aarch64 build
has also logged in, joined a room and become its master; a battle has not been
run on aarch64.

Not there yet: input devices other than a pointer and a keyboard, and
everything specific to the handheld.

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
Alt+Enter switches full screen.

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
  from `orig/Launcher.cs`; pass it with `--cmdline`. The token is only looked at
  by the server at login.
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
| `--scale N`, `--fullscreen` | window size as a multiple of 800x600; start full screen (Alt+Enter switches at any time) |
| `--scale-mode MODE` | `fit`: the largest picture with the game's aspect ratio (default); `integer`: whole multiples only; `stretch`: fill the window |
| `--filter FILTER` | `sharp`: point sampling up to the next whole multiple, then bilinear down to the picture's size (default); `nearest`; `linear` |
| `--no-sound`, `--dump-audio FILE` | tell the game there is no sound device; write the mixed sound to a WAV file instead of playing it (works headless) |
| `--dump-frame N[,N...]`, `--dump-every N`, `--dump-path FILE` | write presented frames (1 = first) as PNG files; a `%d` in the path is the frame number |
| `--dump-window` | frame dumps also write `FILE.window.png`, what the window shows after scaling |
| `--frames N` | exit after N presented frames |
| `--input SCRIPT`, `--input-file FILE` | synthetic input, `"FRAME:command;..."` or one step per line: `move X Y`, `click X Y`, `down`, `up`, `rdown`, `rup`, `key VK DIK`, `keydown VK DIK`, `keyup VK DIK` (hexadecimal), `text STRING`, `fullscr`, `quit`. `+N` as the frame counts from the previous step |
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
recomp/test/online.sh [HOST:PORT]    # two instances against a running server
```

`online.sh` needs a server (default: a broker on 127.0.0.1:8372). Two headless
instances of the host build log in as `admin` and `tester`; the first creates a
room, the second joins and readies, the first starts the game and both hold the
space bar when their turn may have come. It reports each stage from the packets
the clients received and leaves frames and logs in `recomp/build/online/`. It
takes about 90 seconds, because the game runs in real time.

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
| `video.c` | the SDL2 window and its scaling, input translation, the raw input log, scripted input, PNG output |
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
- *Not verified*: a physical screen, SDL's `kmsdrm` and `x11` drivers, pointer
  and keyboard events arriving through SDL (the scripts enter below SDL's
  event translation; that path was last exercised in milestone 2), the
  Alt+Enter key itself (the script command `fullscr` calls the same function),
  and an audio device: the SDL audio path ran on SDL's `dummy` driver only.
- *Sound*: the mix written by `--dump-audio` during a session is continuous
  stereo without clipping, with music from the logo on; it has been measured,
  not listened to.
- *aarch64*: the instruction tests and the frame comparison; under qemu the
  build also logged in and joined a room. In the ready room qemu falls to a
  few frames per second, which says little about the device but means a battle
  has not been run on aarch64.

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
- Guest threads are host threads and the lifted code reads and writes guest
  memory with plain loads and stores. The game was written for x86, where
  stores become visible to other processors in order; on aarch64 they need not.
  The game guards what its threads share (the event ring between the network
  threads and the main thread, the send queues) with critical sections, and
  nothing has gone wrong under qemu, but qemu on x86 cannot show such a fault.
  This is the first thing to suspect if the device shows rare hangs.

Windows
- Sound: no 3D buffers, effects or position notifications (the game uses none).
  The mixer has been checked by measuring its output, not by ear.
- Direct3D: textured, blended and colour-keyed drawing is now used all through a
  battle (backgrounds, smoke, flames, explosions, the aiming dial) and looks
  right, but it has not been compared with the original's frames. Untransformed
  vertices, lines, points, a second texture stage, fog and specular colour are
  not implemented and are reported when asked for; none was asked for.
  Interpolation is not perspective correct.
- Input: pointer and keyboard only. The visible cursor follows relative motion,
  which the runtime derives from the pointer's position in guest pixels; a
  touchscreen can use the same path. No gamepad mapping, no on-screen keyboard.
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

## Next milestone: the handheld

The target is a Retroid Pocket 5 (Snapdragon 865, 1920x1080) running ROCKNIX:
aarch64, glibc, a Wayland compositor, SDL2 on the system.

1. *Toolchain and packaging.* The aarch64 program built here links only
   `libc`, `libm` and `libSDL2-2.0.so.0` and needs glibc 2.38 (the batocera
   buildroot it is built with). ROCKNIX's glibc is newer, so the same binary
   should load there; the open question is its SDL2, which is checked by
   running it. If the glibc floor has to come down, build against an older
   sysroot (Debian 11 arm64, glibc 2.31, is what PortMaster ports use) rather
   than linking statically: SDL2 must stay the system's, because it carries the
   device's video and audio back ends. Package it as a port: a directory under
   `/storage/roms/ports/` with the binary, a launch script modelled on
   `recomp/run.sh` (token, `--gamedir`, `--savedir`, `--broker`, `--fullscreen`)
   and the user's own copies of the executable and data files. `--dump-frame`
   and `--dump-window` work over ssh for a first look without the screen.
2. *Speed.* A battle costs about three quarters of one core of the development
   machine (see Performance), so the device will need work here. Profile first:
   the candidates are the rasteriser's per-pixel loop under the full-screen
   stage background and the lifted blitters, which are compiled at `-O1` with
   every register in memory.
3. *Input.* Touch as an absolute pointer: SDL's touch events through the same
   mapping as the mouse (they are ignored today so that the synthetic mouse
   events SDL makes from them can be replaced deliberately). Gamepad through
   SDL's game controller API inside the runtime, not an external key mapper,
   because the game reads the keyboard through DirectInput state and the
   pointer through relative motion: left stick or d-pad as the arrow keys in
   battle and as pointer motion in menus, A as the left button and space bar,
   B as escape, shoulder buttons for the item keys F1-F8, and an on-screen or
   chorded text entry for the room title, chat and nothing else. The account
   comes from the launch script, so no keyboard is needed to log in.
4. *The server.* The three packet differences listed above have to be settled
   in the server before a battle works against it.
5. *Robustness.* Guest exceptions from host faults, an interpreter fallback for
   code reached only through computed addresses, and a look at memory ordering
   between guest threads on aarch64 (see Known gaps).
