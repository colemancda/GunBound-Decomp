# GunBound Decomp — Toolchain (Apple Silicon / macOS)

The target `orig/GunBound.gme` is a 32-bit x86 Windows PE built with **Visual C++
2003 (MSVC linker 7.10)**. None of the matching pipeline runs natively on arm64, so
we split it: **Ghidra** runs native (JVM), the **compiler** runs in an amd64 Docker
container under Wine, and **asm-differ** compares the result byte-for-byte.

## Installed by setup

| Tool | Location | Purpose |
|------|----------|---------|
| Ghidra | `brew install ghidra` → `ghidraRun` | Disassembly / decompiler / analysis |
| JDK 21 | `openjdk@21` (Cellar) | Ghidra's required Java (system Java is 26, too new) |
| asm-differ | `tools/asm-differ/` | Per-function byte/insn diff vs original |
| Python venv | `tools/.venv/` | asm-differ deps (colorama, cxxfilt) |
| Docker | already installed | Runs amd64 Wine + MSVC 7.10 |
| qemu-system-i386 | already installed | Optional full Windows VM for runtime tests |

Ghidra needs JDK 21, not the system JDK 26. Launch with:
```
JAVA_HOME=/opt/homebrew/Cellar/openjdk@21/21.0.11/libexec/openjdk.jdk/Contents/Home ghidraRun
```

## The one piece you must supply: MSVC 7.10

The Visual C++ 2003 compiler is proprietary and cannot be downloaded here. To enable
byte-matching you need a `Vc7` tree (cl.exe, link.exe, `include/`, `lib/`, and a
PlatformSDK) from a Visual Studio .NET 2003 install. Place it at:
```
tools/msvc-env/msvc7/
```
Then build the container:
```
docker build --platform linux/amd64 -t gb-msvc tools/msvc-env
```
Until then, decompilation/analysis (Ghidra) works fully; only the *verify by
recompile* step is blocked.

### Without MSVC (behavioral-only fallback)
If you don't have/can't get MSVC 7.10, you can still produce readable, portable C and
verify behavior (parse the shipped `.xfs`/`.dat` files, run under `dxwnd`), just not
guarantee byte-identical output. Byte-matching is strongly recommended for
correctness but is optional.

## Confirmed runtime oracles

The original `GunBound.gme` (32-bit x86) has been confirmed running, unmodified, on:
- **macOS/Wine** via `dxwnd` (shipped with the game files)
- **Android** via Wine + **box64** (x86 → arm64 emulation)
- **Debian armv7** via **box86** (x86 → 32-bit ARM emulation)

These are all valid ground-truth oracles for **behavioral verification**: run the
original alongside a reconstructed build (or instrument the original with Wine/
gdb) and compare observable behavior — packet contents, file parsing, physics,
rendering output — even with no MSVC 7.10 access. This makes the behavioral-only
fallback path fully viable as a primary verification strategy, not just a stopgap,
since we now have three independent working runtimes to test against.

## Diffing a function
Once a function is compiled in the container, compare it to the original:
```
tools/.venv/bin/python tools/asm-differ/diff.py -o <FUNC_ADDR>
```
(configured via `diff_settings.py`, generated during Phase 1).
