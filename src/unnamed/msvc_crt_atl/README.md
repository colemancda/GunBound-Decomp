# Statically-linked MSVC 7.10 CRT/ATL internals — excluded from the build

These 544 files are raw Ghidra decompiles of everything at address
`0x51fe1c` and above in `GunBound.gme`'s `.text` section — the
statically-linked Visual C++ 2003 (linker 7.10) C runtime and ATL
(Active Template Library), confirmed by the boundary already documented
in `ARCHITECTURE.md`'s "Compiler/runtime" section (the `R6002`-`R6029`
runtime-error strings, `TLOSS`/`SING`/`DOMAIN` math-error messages, and
the traced `__fsopen`→`__openfile`→`__sopen`→`__tsopen_lk` fopen chain
all live in exactly this range).

**Deliberately excluded from `src/README.md`'s "raw port" build targets
and from `PROGRESS.csv`'s function-porting tracker.** Concretely, this
is malloc/free/heap-management internals (`_malloc`, `_free`,
`__heap_alloc`, `__nh_malloc`, `__resetstkoflw`), C++ exception handling
and `_com_error`, and ATL template classes (`CComCritSecLock`,
`CAtlBaseModule`, `CSimpleArray<T>`, scalar-deleting destructors) —
compiler/runtime plumbing, not game logic. Reimplementing it from
decompiled output would be:

- **Unnecessary** — Winelib/glibc already provide correct, well-tested
  implementations of all of this (`malloc`/`free`/exception handling/
  etc.), which is exactly what the eventual real build should link
  against instead.
- **Risky** — heap allocators and exception unwinding are exactly the
  kind of code where a subtly-wrong reimplementation causes silent
  memory corruption rather than a clean crash, and CRT internals are
  especially prone to Ghidra decompiler artifacts (see e.g. the ATL
  `CSimpleArray<T>::operator[]` template call already flagged as
  genuinely broken in `src/README.md` — one of these files, moved here
  along with the rest once the pattern was recognized).
- **Off-goal** — the actual point of this project is the game's own
  logic (rendering, network protocol, file formats, game state), which
  is everything *below* `0x51fe1c`. That's what stayed in `src/unnamed/`
  proper and the named subsystem directories.

Kept on disk (not deleted) purely for reference — e.g. if a specific
decompiled CRT function's exact behavior is ever relevant to
understanding a bug in the game logic that calls it — but not part of
the build, and not something future porting passes should pick back up.
