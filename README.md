# GunBound-Decomp
GunBound Thor's hammer decompilation project

See [tools/README.md](tools/README.md) for toolchain setup,
[PROGRESS.csv](PROGRESS.csv) for the function-level decompilation worklist,
[ARCHITECTURE.md](ARCHITECTURE.md) for reverse-engineered structural notes
(game-state machine, network protocol, subsystem init),
[PROTOCOL.md](PROTOCOL.md) for the full packet/opcode reference,
[FILEFORMATS.md](FILEFORMATS.md) for the custom `.xfs`/`.dat`/`.img`/`.sv`
file formats, [STRINGS.md](STRINGS.md) for a categorized reference of
every string embedded in the binary, and [CONSTANTS.md](CONSTANTS.md) for a
consolidated index of every enum/constant/opcode/struct-offset confirmed
across all of the above.

## Source layout — the C and C++ trees

The reconstructed source is **one codebase at two fidelity tiers**, not two
separate projects:

- **`src/` (raw C ports)** — the bulk of the work. One original function per
  file, plain C, compiled in MSVC 7.1's **C mode**. Virtual dispatch is
  hand-indexed (`(**(code **)(*obj + 0x1c))()`), vtables and structs are
  offset math. See [src/README.md](src/README.md).
- **`src/cxx/` (C++ reconstruction)** — where a function goes once it's
  understood well enough to express as a real class member. MSVC 7.1's C mode
  **cannot express `__thiscall`**, so no member function can byte-match the
  original until it's compiled as C++; anything class/vtable-shaped therefore
  lives here as real methods with compiler-laid vtables. See
  [src/cxx/README.md](src/cxx/README.md).

A function **migrates** from the C tree to the C++ tree as it's promoted from
"raw port" to "reconstructed" — during that migration both versions can
coexist (the `.cpp` is the higher-fidelity version of the same original
address). They are **built and checked separately today**: the `Makefile`
sweeps `.c` files only, while the C++ tree is validated on its own by
compiling `src/cxx/cxx_selftest.cpp` (layout enforced with
`GB_STATIC_ASSERT`, not by linking). The long-term goal is a single
recompiled binary that links both — normal for mixed C/C++ — but the project
is still at the per-function match/layout-check stage, so nothing links into
a full target yet.

## Reimplementation guides

Reimplementation-focused docs, built from the reverse engineering above:

- [docs/screens/](docs/screens/README.md) — one build-oriented document per
  game screen (state, rendering, input, network, transitions).
- [docs/widgets.md](docs/widgets.md) — the reusable UI-widget system (the
  `CWidget`/`CPanel` hierarchy, the flat `ButtonWidget`, and the panel catalog).
- [docs/localized-strings.md](docs/localized-strings.md) — the extracted
  `Language.txt` string table (id → verbatim **English** message), and how ids
  map to server error codes.
- [docs/porting-sdl3.md](docs/porting-sdl3.md) — mapping the DirectX/Win32 usage
  to **SDL3** (a faithful, cross-platform port).
- [docs/porting-spritekit.md](docs/porting-spritekit.md) — mapping the client to
  Apple's **SpriteKit** (an idiomatic scene-graph re-expression).

## Reference file hashes

The original game/asset files are not committed to this repo (proprietary,
gitignored under `orig/`). These SHA-256 hashes pin the exact copies the
decompilation is being verified against — re-hash your local copy and compare
before relying on any progress here.

The content assets (`graphics.xfs`, `sound.xfs`, `avatar.xfs`, and the `.dat`
files) are the **`TestClient/` set from
[jglim/gunbound-launcher](https://github.com/jglim/gunbound-launcher)** — an
**English** build. Critically, that client's **`GunBound.gme` is byte-for-byte
identical to our decompilation target** (`4af6283d…`), so the decomp stays
valid against it and its assets are the ones the target actually loads.

| File | SHA-256 | Size |
|------|---------|------|
| `GunBound.gme` | `4af6283dfd151f5256b9bc0da8d07fff16384950c00da3b2baae825f5fc0fcde` | 1,815,040 |
| `Launcher.cs` | `6b6f479b24632391ade9b4a959029464832a3c08a598912360d1ecf5add0b258` | 16,876 |
| `avatar.xfs` | `829be830e0c50c273d5e0ece03c22fbe0c45e07527129e60e8843d16a1df0e6d` | 22,968 |
| `graphics.xfs` | `a52f9f468bb1c6d772bfa0431ec436b0c515a7cebc490c6970e55c7dffb20f08` | 90,913,019 |
| `sound.xfs` | `081c1b9f5751c486512a9df1a894f6db7a5ed891b8ebdad9fbce1b9169901023` | 18,604,788 |
| `characterdata.dat` | `b7278385d6ea60af3cdcbccbf6df15a74e857f196adbb87e5e99bea6a0feecaf` | 1,130 |
| `itemdata.dat` | `de6f4d3c424df046d344c4f952542255a1eeb2898457eac74ff6379051b48523` | 1,650 |
| `specialdata.dat` | `9cc0d99f87e4fff6fd56160c3737fb966546ab9bb77a6a33374cb4642233e086` | 88 |
| `stage.dat` | `103c2b488977e1721becf8cb90496f95477302ec24141f94116d5214a3e6cfca` | 1,238 |

`graphics.xfs`/`sound.xfs`/`avatar.xfs` are **not committed** (too large,
and `orig/` is gitignored regardless) — hashes above just pin the exact
copies used to validate the file-format findings in
[FILEFORMATS.md](FILEFORMATS.md). The **container formats** documented there
are unchanged by the asset swap (the `.xfs`/`.dat` layouts are identical), but
some *content* examples in FILEFORMATS.md (e.g. Portuguese item-description
text) were taken from the previous asset set and now read as English in the
committed hashes' files.

Not yet hashed/copied into `orig/`: `characterdata_imortal.dat`,
`characterdata_original.dat`, `GunBound.exe` (the .NET launcher stub, not
the decomp target).

Verify with: `shasum -a 256 orig/GunBound.gme`
