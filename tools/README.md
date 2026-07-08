# GunBound Decomp — Toolchain (Windows-native)

The target `orig/GunBound.gme` is a 32-bit x86 Windows PE built with **Visual C++
2003 (MSVC linker 7.10)**. This machine runs Windows directly, so unlike the
Apple Silicon setup (Docker + Wine, see git history for that version of this
file) the compiler runs natively - no emulation layer needed.

## Installed by setup

| Tool | Location | Purpose |
|------|----------|---------|
| MSVC 7.10 (`cl.exe`/`link.exe`) | `tools/msvc-env/msvc7/{bin,include,lib}` | Exact-version compiler (from the free Visual C++ Toolkit 2003) |
| Platform SDK headers/libs | `tools/msvc-env/msvc7/PlatformSDK/{include,lib}` | windows.h/winsock2.h/etc. (Windows Server 2003 SP1 Platform SDK) |
| DirectX 7.0a headers/libs | merged into `PlatformSDK/{include,lib}` | ddraw.h/d3d.h (DX7 predates the Platform SDK bundling DirectX) |
| Python 3.12 (arm64) | `C:\Users\coleman\AppData\Local\Programs\Python\Python312-arm64\` | Runs asm-differ |
| asm-differ venv | `tools/.venv-win/` | colorama, cxxfilt, watchdog |
| LLVM / `llvm-objdump` | `C:\Program Files\LLVM\bin\llvm-objdump.exe` | Disassembles both the original PE and compiled `.obj`s |

All of the above under `tools/msvc-env/msvc7/` and `tools/.venv-win/` are
gitignored (proprietary/regenerable) - see "Rebuilding this setup" below.

## Compiling a single function

```
root="tools/msvc-env/msvc7"
export INCLUDE="$root/include;$root/PlatformSDK/include"
export LIB="$root/lib;$root/PlatformSDK/lib"
"$root/bin/cl.exe" /c /I include/msvc /I include /O2 /Fobuild/foo.obj src/path/to/foo.c
```

`include/msvc/` holds `stdint.h`/`stdbool.h` shims (MSVC 7.1 predates both);
put it on `/I` *before* `include/` so it's found first. Raw/verbatim ports
under `src/unnamed/` pull in `windows.h`/`ddraw.h`/`d3d.h` via
`include/ghidra_types.h`, which is why the Platform SDK + DirectX 7 merge
above is needed even for functions that don't touch Windows APIs directly.

## Diffing a function against the original

No full relinked/address-matched image exists (building one is a bigger lift -
a linker script/fake-object setup so every function address matches the
original), so the real `asm-differ` `-o <ADDR>` flow (which needs a mapfile)
isn't wired up. Instead, `diff_settings.py` (repo root) configures asm-differ's
**`-e`/ELF-symbol mode**, which needs no relinked image at all: `myimg` can be
any compiled `.obj`, and asm-differ disassembles just the one named symbol out
of it, lined up against the original binary's real bytes at a given VA range.
This is the real tool - colorized, aligned, scored - not an approximation.

```
GB_MYIMG=build/GetBit_cmp.obj tools/.venv-win/Scripts/python.exe \
    tools/asm-differ/diff.py -e _lzhuf_get_bit 0x4ea120 0x4ea1a4
```

`tools/score.sh <symbol> <start-VA-hex> <end-VA-hex> <obj-file>` wraps that up
and prints just the match score (`--format json` under the hood) - lower is
better, `0` is a perfect match, and the score can exceed the shown max when
there are extra/missing instructions rather than just substitutions:

```
tools/score.sh _lzhuf_get_bit 4ea120 4ea1a4 build/GetBit_cmp.obj
# score: 4260 / max: 3900
```

Expect *structural* mismatches even for correct ports - e.g. a `static`
helper the original compiler inlined (old MSVC won't inline functions
containing loops via `/Ob2` either) will show up as ours calling out to a
separate function instead of one merged block. That's a source-level fix
(fold the helper's body into the caller to match), not a toolchain issue.

Three low-level helper scripts, useful when you want raw bytes/disassembly
without going through asm-differ's scoring:
- `tools/diff_func.sh <VA-hex> <length> <obj-file>` - unscored side-by-side
  disassembly of both sides via `llvm-objdump` directly (no `diff_settings.py`
  dependency, good for a quick look).
- `tools/pe_bytes.ps1 <pe-file> <VA-hex> <length>` - dumps raw hex bytes from
  a PE at a given virtual address (walks the section table itself).
- `tools/coff_func_bytes.ps1 <obj-file> [-FuncName <name>]` - lists a
  compiled `.obj`'s function symbols/offsets, or dumps one function's raw
  bytes by name.

## Confirmed runtime oracles

The original `GunBound.gme` (32-bit x86) has been confirmed running,
unmodified, on macOS/Wine (`dxwnd`), Android (Wine + box64), and Debian armv7
(box86) - all valid ground truth for **behavioral verification** (packet
contents, file parsing, physics, rendering output) independent of whether
byte-matching succeeds.

## Rebuilding this setup from scratch

1. **MSVC 7.10**: install the free [Visual C++ Toolkit
   2003](https://en.wikipedia.org/wiki/Visual_C%2B%2B_Toolkit_2003) (exact
   version match: `13.10.3052`), then copy its `bin/include/lib` into
   `tools/msvc-env/msvc7/`.
2. **Platform SDK**: the *Web Install* installers for the Windows Server 2003
   SP1 Platform SDK are dead stubs (they fetch payload cabs from a
   long-retired `download.microsoft.com` URL). Use the **ISO Install**
   instead (`5.2.3790.1830.15.PlatformSDK_Svr2003SP1_rtm.img`, ~400MB,
   mirrored on [legacyupdate.net](https://legacyupdate.net/download-center/download/15656/windows-server-2003-sp1-platform-sdk-iso-install)).
   Mount it, then admin-install its `PSDK-x86.msi` to a local folder to get
   real (non-GUID-mangled) filenames:
   ```
   msiexec /a E:\Setup\PSDK-x86.msi /qn TARGETDIR="C:\psdk_admin"
   ```
   Copy the resulting `Include`/`Lib` into `tools/msvc-env/msvc7/PlatformSDK/`.
3. **DirectX 7.0a SDK**: `ddraw.h`/`d3d.h` aren't in the Platform SDK above.
   Grab `dx7adxf.exe` from [archive.org](https://archive.org/details/dx7adxf)
   (WinZip self-extracting archive - unzip with 7-Zip, don't run it) and
   merge its `include`/`lib` into the same `PlatformSDK/{include,lib}`
   without overwriting existing files.
4. **Python + LLVM**: `winget install Python.Python.3.12` and `winget
   install LLVM.LLVM`, then `python -m venv tools/.venv-win && tools/.venv-win/Scripts/python.exe -m pip install colorama cxxfilt watchdog`.

Note on old MS installers: anything from this era (IExpress/InstallShield
self-extractors) tends to refuse to run under WOW64 ("Setup was started in a
non-native or WoW environment") on any modern 64-bit Windows. Don't fight it -
extract with 7-Zip instead of running the installer; these are almost always
plain CAB archives under the EXE wrapper.
