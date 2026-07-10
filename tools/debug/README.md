# Live debugging: Ghidra Debugger ↔ Wine (GunBound client)

Attach the **Ghidra Debugger** to the running GunBound client under Wine so the
live program counter, registers, stack and memory sync directly onto the
disassembly/decompiler view of the `GunBound.gme` program in this project.

## Why it maps cleanly

`orig/GunBound.gme` is a PE32 with `ImageBase = 0x00400000` and **no ASLR**
(`DllCharacteristics = 0x0000`), and it is **not packed**. Under Wine it always
loads at `0x400000`, so:

```
runtime virtual address  =  file RVA + 0x400000
```

Verified live: `.text 0x401000–0x543a00`, `.data 0x544000`, entry `0x5277df`.
Ghidra auto-maps the live `GunBound.gme` module (base 0x400000) onto the analyzed
program of the same name — addresses line up 1:1, no rebasing.

## Environment (discovered, not default)

| Thing            | Value                                                        |
|------------------|-------------------------------------------------------------|
| Wine build       | `lutris-7.2-2-x86_64` (Lutris-managed; **not** system Wine)  |
| Prefix           | `/home/coleman/Games/wine32-prefix` (`win32`)               |
| Client dir       | `/home/coleman/Games/TestClient`                            |
| Ghidra           | `~/Downloads/ghidra_11.0.1_PUBLIC` (has the gdb Debugger)    |
| Ghidra project   | `ghidra/GunBound.gpr` (GunBound.gme, analyzed)              |

> Ignore `~/.wine` — it is corrupt (no kernel32) and unrelated to the game.

Transport: `winedbg --gdb --no-start --port N` exposes a **gdb remote stub** (the
guest 32-bit i386 view). Ghidra's own `gdb` connects to it with `target remote`.
`winedbg` is required (not native `gdb -p`) so we get the *guest* CPU state rather
than the Wine host process frames.

## The launcher handoff — why you must ATTACH, not launch

`GunBound.gme` cannot be started bare. `Launcher.exe` (driven by
`TestClient/Launcher.ini`) AES-encrypts the account id and passes the result as the
client's **command line**, and seeds `HKLM\Software\Softnyx\GunBound` in the
registry. The game reads that command line and decrypts it:

- `src/entry/WinMain.c:176` → `GetCommandLineA()` (via the CRT entry `FUN_005277df`
  at `0x5277df`).
- `src/unnamed/.../FUN_00524bb0.c:138` → `CryptDecrypt(...)` on the credential blob.

So launching `GunBound.gme` with no argument gets you to `WinMain` but fails during
login-time credential decryption. The registry keys are **already present** in the
Lutris prefix. The reliable approach is therefore: **let the real launcher start the
game, then attach the gdb stub to the running process** (`winedbg --gdb --no-start
--port N <wpid>`). Verified working — attach reports the live `pei-i386` guest view.

> The `Launcher.exe` shipped here (INI-based, `USERNAME=colemancda2`) is a *different*
> implementation from `orig/Launcher.cs` (the ID.txt/AES version in the docs), so
> don't assume the doc's AES key reproduces its exact command line. Attach sidesteps
> this entirely.

## One-time setup (already done)

- `ghidra/GunBound.gpr` — headless-imported + analyzed `orig/GunBound.gme`.
- `tools/debug/wine-remote-gdb.sh` — custom Ghidra launcher, symlinked into
  `~/Downloads/ghidra_11.0.1_PUBLIC/Ghidra/Debug/Debugger-agent-gdb/data/debugger-launchers/`.
  (Repo is source of truth; the symlink is how Ghidra discovers it.)

## Workflow (attach — the normal path)

1. **Start your private server** so login/gameplay code paths work. From your
   GunBound server repo:
   ```
   swift run GunBoundServer broker --path .build/servers.json   # + world/other roles
   ```
   `Launcher.ini` already points `SERVER=127.0.0.1`.

2. **Launch the game the normal way** — via Lutris (the *gunbound-classic* entry),
   or run its `Launcher.exe` in the same prefix. Let it get to the login/room UI so
   the client is alive with valid credentials.

3. **Attach the gdb stub** (terminal):
   ```
   tools/debug/wine-attach.sh 12345
   ```
   It finds `GunBound.gme`'s Wine pid automatically and listens on `localhost:12345`.

4. **Open Ghidra**, open `ghidra/GunBound.gpr`, open the `GunBound.gme` program,
   then open the **Debugger** tool.

5. In the **Debugger → Targets** window, use the connect dropdown and pick
   **“gdb (wine remote stub)”**. Set `Stub host = localhost`, `Stub port = 12345`
   (defaults). Launch — Ghidra's gdb connects, enables trace sync, and captures the
   current frame immediately.

6. **Drive it.** Set breakpoints in the Ghidra listing (e.g. functions you are
   matching in `src/network/`), then `Resume`. On each stop the Listing/Decompiler
   cursor follows `$pc` and registers/stack/memory show live values. Addresses are
   `RVA + 0x400000` (entry = `0x5277df`).

### Debugging from the very first instruction — use CREATE_SUSPENDED

The launcher itself has the clean answer. `TestClient/Launcher.ini` supports
`CREATE_SUSPENDED` (and `INJECT_DLL`). Set:
```
CREATE_SUSPENDED=TRUE
```
Now `Launcher.exe` creates `GunBound.gme` **suspended, with the correct encrypted
credentials already on its command line**, and does not resume it. Then:

1. Launch via Lutris (the launcher spawns the suspended game and exits — that's
   `EXIT_IMMEDIATELY`, harmless).
2. `tools/debug/wine-attach.sh 12345` — attaches to the suspended process.
3. Connect Ghidra, set a breakpoint at `0x5277df` (CRT entry) or `WinMain`, then
   Resume. You catch init from the very first instruction *with* real credentials —
   no replication, no timing race.

Set `CREATE_SUSPENDED=FALSE` again when you're done so normal play isn't blocked.

> The `wine-gdbstub.sh` direct-launch path (passing a captured `CRED_ARG`) still
> exists as a fallback, but CREATE_SUSPENDED is simpler and always correct.

### Targeted probes (auto-continuing, safe)
- `cursor-probe.sh` + `gbcursor.py` — logs the cursor draw to resolve the animation frame.
- `avatar-probe.sh` + `gbavatar.py` — traces the avatar subsystem: names the three
  Avatar-Store slot handlers (`0x44b170/0x44b330/0x44b460`) by which user action fires
  them, dumps the `avatarEquipped` record on the unpackers to resolve the Head/Flag
  word order, and logs the compositor's unpacked codes. See its header for how to read
  the output (equip a distinctive flag + Standard head, then enter a room).

### High-value uses for the decomp
- **Struct layouts** (`FILEFORMATS.md` / `PROTOCOL.md`): break on a function taking
  a struct ptr, dump memory at the arg, read real field offsets/values.
- **Globals** (`src/globals.c`): hardware watchpoint on a global to find its writer.
- **Checksum/packet** (`AddToPacketChecksum`, `EncodeChecksumState`,
  `EncodeOutgoingPacketField`): capture real in/out bytes as ground-truth test
  vectors for the reimplementation.

## Capturing network test vectors

`netcap.py` + `capture-net-vectors.sh` breakpoint the encode/checksum/receive
functions and log their real inputs/outputs — ground truth for validating the
reimplementation. Addresses and conventions were read from the disassembly:

| Function | VA | Captured |
|---|---|---|
| `PeekPacketChecksumState` | `0x40a2e0` | state obj `[EAX..+0x20]` |
| `EncodeOutgoingPacketField` | `0x40a380` | state `[EDI..+0x20]`, value `[esp+4]` |
| `EncodeChecksumState` | `0x40a4a0` | state in `EAX`, + return value |
| `AddToPacketChecksum` | `0x40aab0` | state `EAX`, added value `[esp+4]` |
| `SubFromPacketChecksum` | `0x40aaf0` | state `EAX`, sub value `[esp+4]` |
| `BuildSystemInfoBlob` | `0x40d260` | out buffer `[esp+4]` on return (AES-keyed blob) |
| `ReceiveFramedPackets` | `0x4e5610` | inbound bytes `[EBX+0x230]` on return |

Usage (needs a stub from `wine-attach.sh`; this is an **alternative** to the Ghidra
connection — one gdb per stub):
```
tools/debug/capture-net-vectors.sh 12345 /tmp/gunbound-netvectors.log
```
It auto-continues (never halts the game) and caps hits per breakpoint
(`NETCAP_MAX_HITS`, default 25). Env knobs: `NETCAP_SECONDS=N` auto-detaches after
N seconds (leaves the game clean); `NETCAP_GROUPS=checksum,blob,recv` limits scope.
Ctrl-C also stops and detaches. Drive traffic (join a room, fire) while it logs.

> **Safety notes (learned the hard way — two frozen sessions during bring-up):**
>
> 1. **No `FinishBreakpoint`.** An earlier version used it to capture return values.
>    Over the winedbg remote stub it trips a gdb internal-error
>    (`finish_step_over` assertion); gdb aborts while the game is stopped at a
>    breakpoint. `netcap.py` now uses only plain auto-continuing breakpoints, with
>    return captures planted at fixed `ret` addresses — no stepping, no FinishBreakpoint.
>
> 2. **Clean detach must `interrupt` first.** You cannot delete breakpoints or
>    detach while the target is running (gdb errors out). The auto-detach path does
>    `interrupt` → `delete` → `detach` → `quit`. If it doesn't, breakpoints are left
>    planted and gdb wedges.
>
> 3. **winedbg attach mode is KillOnExit — killing the stub kills the game.** In
>    attach mode winedbg *is* the debugger; if it dies (or you `kill` a wedged one)
>    the OS terminates the debuggee. So: **never hard-kill the stub while attached.**
>    Always stop via Ctrl-C (gdb detaches) or let `NETCAP_SECONDS` auto-detach. If a
>    stub ever wedges with the port closed, there is no non-fatal recovery — the
>    game will be lost, so relaunch it.
>
> Because of #3, prefer **short `NETCAP_SECONDS` runs** and only capture when the
> game is actually on a screen that exercises the target code (e.g. the World List /
> in a room for checksum+recv traffic; a login/loading screen produces zero hits).

### Interactive capture inside Ghidra

Two Ghidra launchers are registered (connect dropdown):

- **gdb (wine remote stub)** — plain interactive attach.
- **gdb (wine remote stub + netcap logging)** — same, but also installs netcap's
  logger breakpoints (`wine-remote-gdb-netcap.sh`). They auto-continue (never halt
  the game) and stream vectors to `OPT_NETCAP_LOG` (default
  `/tmp/gunbound-netvectors.log`) while you use Ghidra normally. They're `internal`
  so they don't clutter Ghidra's breakpoint list. **No timed auto-detach** — you
  drive the game to make traffic, watch the log, and **disconnect in Ghidra** to
  detach cleanly. Set your own Ghidra UI breakpoints on top if you want to halt and
  inspect a specific hit with the Listing in front of you.

> Captures only produce data when the game is actually sending/receiving — the
> World List *refreshing*, or in a room. A "PLEASE WAIT" / login screen is parked on
> the server and yields zero hits.

## Getting all the C++ objects into Ghidra (DWARF, not hand-transcription)

Every reconstructed type in `src/cxx/` can be pushed into Ghidra with exact,
compiler-verified layouts — no retyping structs by hand:

```
tools/debug/build_ghidra_types.sh          # -> build/gb_cxx_types.o  (ELF32 + DWARF)
```
It compiles the `src/cxx/` headers with host `g++ -m32 -g -femit-class-debug-always`.
Because the headers' `GB_STATIC_ASSERT`s force g++'s layout to equal MSVC 7.1's
(== the binary), the DWARF offsets/sizes/vtables/inheritance are the real ones.

Then import into Ghidra (already run once; re-run after header changes):
```
analyzeHeadless <proj> GbTypes -import build/gb_cxx_types.o \
    -postScript ExportDwarfTypesToGdt.java ghidra/gb_cxx_types.gdt   # -> portable archive
analyzeHeadless ghidra GunBound -process GunBound.gme \
    -postScript ApplyCxxTypes.java ghidra/gb_cxx_types.gdt           # import + retype globals
```
This imported all 35 C++ types (CGameState + 10 states, the CWidget/CPanel tree,
protocol structs, ServerListSoA) into `ghidra/GunBound.gpr` and typed
`g_gameStateObjects` (0x5b33f8) as `CGameState *[16]`. In the GUI you can also just
`File -> Open File Archive -> ghidra/gb_cxx_types.gdt` and drag types onto data.

The state objects are heap-allocated, so apply a `CStateNN *` at the decompiler
(right-click -> Retype) or in the **Debugger** — once typed, both the decompiler
and the live Debugger memory/Watches view render named C++ fields.

## Reading the live C++ GameState (`gbstate.py`)

`gbstate.py` decodes the running game's `CGameState` object into named fields from
`src/cxx/GameState.h` / `ClientContext.h`. Load it in any gdb attached to the stub
(standalone or next to netcap):
```
(gdb) source tools/debug/gbstate.py
(gdb) gbstate                 # current CGameState* → state id/name, vtable, named fields
(gdb) gbstate ctx             # server-list SoA from g_clientContext (names/players/caps)
(gdb) gbstate raw 0x80        # hexdump the current state object
(gdb) gbstate widget <addr>   # walk a CWidget/CPanel tree: rect, type/id, [Focus/Enabled/Hidden], children
(gdb) gbstate panels          # walk g_uiPanelManager and dump every attached panel's tree (auto-root)
(gdb) gbstate json [path]     # write gameState + view hierarchy as JSON (default /tmp/gb-view.json)
```
`gbstate widget` recurses the `m_children` (CAtlArray) tree and prints each node's
rect/type/id/flags — pass a root panel pointer read from the state object or the
decompiler.
Anchors: `g_currentGameState @0x7934d0`, `g_gameStateObjects[16] @0x5b33f8`,
`g_clientContext @0x5b3484`. It has full field maps for states 1/2/3/5/6 and
hexdumps the rest. Read-only. In Ghidra you get the same thing graphically once the
`CState*` structs are in the Data Type Manager and applied to `g_gameStateObjects`.

## Teardown / troubleshooting

Stop the stub with **Ctrl-C** in its terminal when done. If a stub gets
hard-killed mid-startup it can **wedge the prefix's wineserver**, after which every
new Wine process dies with **SIGFPE (rc 136)**. Fix:

```
tools/debug/wine-debug-reset.sh
```

Then relaunch the stub. (This is the only failure mode seen during setup.)
