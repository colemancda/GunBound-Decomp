# GunBound-Decomp
GunBound Thor's hammer decompilation project

See [tools/README.md](tools/README.md) for toolchain setup,
[PROGRESS.csv](PROGRESS.csv) for the function-level decompilation worklist,
[ARCHITECTURE.md](ARCHITECTURE.md) for reverse-engineered structural notes
(game-state machine, network protocol, subsystem init),
[PROTOCOL.md](PROTOCOL.md) for the full packet/opcode reference, and
[FILEFORMATS.md](FILEFORMATS.md) for the custom `.xfs`/`.dat`/`.img`/`.sv`
file formats, and [STRINGS.md](STRINGS.md) for a categorized reference of
every string embedded in the binary.

## Reference file hashes

The original game/asset files are not committed to this repo (proprietary,
gitignored under `orig/`). These SHA-256 hashes pin the exact copies the
decompilation is being verified against — re-hash your local copy and compare
before relying on any progress here.

| File | SHA-256 | Size |
|------|---------|------|
| `GunBound.gme` | `4af6283dfd151f5256b9bc0da8d07fff16384950c00da3b2baae825f5fc0fcde` | 1,815,040 |
| `Launcher.cs` | `6b6f479b24632391ade9b4a959029464832a3c08a598912360d1ecf5add0b258` | 16,876 |
| `avatar.xfs` | `117399ff9d2aed6b2777f992617c47cb073881845473d013f9a3e782c1a31d96` | 122,361 |
| `characterdata.dat` | `b7278385d6ea60af3cdcbccbf6df15a74e857f196adbb87e5e99bea6a0feecaf` | 1,130 |
| `itemdata.dat` | `752299574279973d055ed7a0220832e5cd94f7e255a65fe767cdd75de7164c26` | 1,729 |
| `specialdata.dat` | `9cc0d99f87e4fff6fd56160c3737fb966546ab9bb77a6a33374cb4642233e086` | 88 |
| `stage.dat` | `103c2b488977e1721becf8cb90496f95477302ec24141f94116d5214a3e6cfca` | 1,238 |

Not yet hashed/copied into `orig/`: `graphics.xfs`, `sound.xfs`,
`characterdata_imortal.dat`, `characterdata_original.dat`, `GunBound.exe`
(the .NET launcher stub, not the decomp target).

Verify with: `shasum -a 256 orig/GunBound.gme`
