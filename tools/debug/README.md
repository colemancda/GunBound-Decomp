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

### Debugging from the very first instruction (advanced)

To break in early init *before* the game runs, you need it launched under the stub
with a valid encrypted command line (see the handoff section). Capture that argument
once (attach with `wine-attach.sh`, read `GetCommandLineA`'s buffer, or snoop the
launcher's `CreateProcess`), then:
```
tools/debug/wine-gdbstub.sh 12345 <ENCRYPTED_HEX_ARG>
```
This loads `GunBound.gme` **suspended at ntdll pre-entry**; connect from Ghidra as
above and set a breakpoint at `0x5277df` / `WinMain` before resuming. Without the
arg it still reaches `WinMain` (fine for DirectDraw/XFS/init breakpoints) but fails
credential decryption.

### High-value uses for the decomp
- **Struct layouts** (`FILEFORMATS.md` / `PROTOCOL.md`): break on a function taking
  a struct ptr, dump memory at the arg, read real field offsets/values.
- **Globals** (`src/globals.c`): hardware watchpoint on a global to find its writer.
- **Checksum/packet** (`AddToPacketChecksum`, `EncodeChecksumState`,
  `EncodeOutgoingPacketField`): capture real in/out bytes as ground-truth test
  vectors for the reimplementation.

## Teardown / troubleshooting

Stop the stub with **Ctrl-C** in its terminal when done. If a stub gets
hard-killed mid-startup it can **wedge the prefix's wineserver**, after which every
new Wine process dies with **SIGFPE (rc 136)**. Fix:

```
tools/debug/wine-debug-reset.sh
```

Then relaunch the stub. (This is the only failure mode seen during setup.)
