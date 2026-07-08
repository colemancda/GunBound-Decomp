# Real MSVC 7.10 via Docker + Wine

Runs the actual Visual C++ Toolkit 2003 `cl.exe`/`link.exe` (version
13.10.3052 / 7.10.3052 - confirmed to match `GunBound.gme`'s own PE
header) inside a `linux/amd64` Debian container via Wine, so real
byte-matching decompilation is scriptable from this machine without a
Windows VM or any interactive/computer-use driving.

## Setup (one-time)

The `msvc7/` directory (this project's copy of the Visual C++ Toolkit
2003 install - `cl.exe`, `link.exe`, headers, libs) is git-ignored,
proprietary, and not included. It was populated once by installing the
free official Microsoft Visual C++ Toolkit 2003 in a Windows VM and
copying the resulting install directory here. If `tools/msvc-env/msvc7/`
is missing, that step needs to happen again before this works.

```
docker build --platform linux/amd64 -t gb-msvc tools/msvc-env
```

## Compiling a file

`cl.exe` needs Windows-style paths (`Z:\work\...`, backslashes - a
leading `/work/...` Unix path gets misparsed as a command-line option
since MSVC's arg parser also uses `/` for options), and `INCLUDE`/`LIB`
need to be set explicitly per-invocation (the Dockerfile's `ENV` only
sets `WINEPATH`, not these). `include/msvc/stdint.h` (this project's
MSVC-compat shim - see its own header comment) needs to come before
`include/` on the include path.

```
docker run --rm --platform linux/amd64 -v "$PWD":/work -w /work \
    -e INCLUDE="Z:\\work\\include\\msvc;Z:\\work\\include;Z:\\opt\\msvc7\\include;Z:\\opt\\msvc7\\PlatformSDK\\include" \
    -e LIB="Z:\\opt\\msvc7\\lib;Z:\\opt\\msvc7\\PlatformSDK\\lib" \
    gb-msvc wine "Z:\\opt\\msvc7\\bin\\cl.exe" /c \
    "Z:\\work\\src\\lzhuf\\InitLZHUFTree.c" \
    "/FoZ:\\work\\build\\InitLZHUFTree.obj"
```

Produces a real `Intel 80386 COFF object file` (confirmed via `file`),
disassemblable with `objdump -d` (`-Mintel` or default AT&T syntax both
work) for direct instruction-level comparison against bytes extracted
from `orig/GunBound.gme` at the function's real address (see
`src/lzhuf/InitLZHUFTree.c`'s own header comment for a worked example of
this comparison catching a real bug: a `memset`/cursor-init that our
hand-verified parity source had but the real 162-byte function at
`0x4ea300` didn't).

## Alternative: driving a real Windows VM

`msvc_compile_check.ps1` is a per-file real-compile sweep (not just
syntax-check) meant to run *inside* a Windows VM with the same `msvc7/`
tree copied in at `Z:\Developer\GunBound-Decomp\tools\msvc-env\msvc7`
(assuming the repo itself is reachable at `Z:\Developer\GunBound-Decomp`,
e.g. via a Parallels shared folder). Useful as a fallback if the Docker/
Wine route above ever produces different results than real Windows for
some file (Wine's Win32 API emulation isn't perfect), but much slower to
drive interactively and was superseded by the Docker/Wine approach
above once that was confirmed working - prefer the Docker route unless
something specifically needs verifying against real Windows.

## Known gaps / next steps

- Not yet wired into the `Makefile` as a proper target - every invocation
  above was constructed by hand this session.
- Optimization flags (`/O1`/`/O2`/`/Ox`/etc.) matching the original
  build's actual settings haven't been determined - the one comparison
  done so far used default (`/Od`, unoptimized) flags, which produced a
  normal stack-frame prologue/epilogue the real (optimized, `edi`-as-
  implicit-parameter, no frame) function doesn't have. Matching flags
  needs its own investigation, likely by trying common release presets
  (`/O2 /Ob2`, `/O1`, `/Ox`) and seeing which gets closest to the real
  calling-convention/register-allocation pattern.
- This only compiles individual files to `.obj` - a full `link.exe`
  invocation producing a complete, comparable `.exe`/`.dll` hasn't been
  attempted.
- Slower than plain `winegcc` (Wine's Win32 PE-loader overhead atop
  `linux/amd64` emulation on Apple Silicon) - fine for targeted
  byte-comparison work, probably too slow for a full-tree sweep the way
  `winelib-syntax-check` does for the behavioral-parity build.
