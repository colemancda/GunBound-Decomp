# `src/cxx/` — the C++ reconstruction layer

This tree is the **C++ reconstruction** of the class hierarchies that the raw
C ports under `src/` can't express: real classes, `__thiscall` member
functions, and vtables laid out by the compiler instead of hand-indexed
`(**(code **)(*obj + 0x1c))()` dispatch.

**Why it exists**: the raw-port tree compiles as plain C, and MSVC 7.1's C
mode cannot express `__thiscall` (see the long comment in
`include/ghidra_types.h`) — so no member function can byte-match until it is
compiled as C++. This tree is where functions go when they're promoted from
"raw port" to "understood": rewritten as real methods of the classes below.

**Sources of truth**: ARCHITECTURE.md ("The `CGameState` base class and
virtual dispatch", "The 16 game states"), docs/widgets.md, and
docs/screens/*.md. Everything here mirrors those documents; where they mark
something *speculative* (names, exact inheritance), the same caveat applies
here. Confirmed facts (vtable slot order, field offsets, object sizes,
original VAs) are encoded as `GB_STATIC_ASSERT` compile-time checks so the
real target compiler verifies the layout on every syntax check.

## Conventions

- **MSVC 7.1, C++ mode** (`.cpp`/`.h`, no `/TC`). Member functions are
  implicitly `__thiscall`, matching the original binary.
- Every class/method name invented by the reconstruction keeps the original
  address in a trailing comment (`// 0x4e5320`), same style as the raw ports.
- Vtable slot order in each class declaration **is** the binary's vtable
  order — do not reorder virtuals. New-in-subclass virtuals go after all
  base-class overrides, which is where MSVC appends them.
- Object sizes and field offsets from the docs are enforced with
  `GB_STATIC_ASSERT(sizeof(X) == N)` / offset checks in `cxx_selftest.cpp`.
  Undocumented gaps are explicit `m_unkNN` members, so every documented
  offset lands exactly where the binary has it.
- States/panels whose field maps aren't reconstructed yet carry an opaque
  `unsigned char m_raw[...]` tail sized so `sizeof` still matches the
  binary's allocation — the class exists, its layout fills in over time.

## Checking

The `*.c`-only sweep scripts don't see this tree. Check it with:

```
docker exec gb-check wine 'Z:\opt\msvc7\bin\cl.exe' /c /nologo /Zs \
    'Z:\work\src\cxx\cxx_selftest.cpp'
```

`cxx_selftest.cpp` includes every header here and carries the layout asserts,
so that one command validates the whole tree.
