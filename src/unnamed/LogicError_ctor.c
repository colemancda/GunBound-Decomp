/* LogicError_ctor - 0x00409fd0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED (2026-10-02), CERTAIN. This is MSVC7/Dinkumware's
 * `std::logic_error::logic_error(const string&)` - the shared base
 * constructor behind out_of_range/length_error/invalid_argument. Library
 * identity, not application logic:
 *
 *  - `param_1` is a genuine `exception*` (the type this whole cluster
 *    already uses - `exception__ctor`/`exception__dtor` in
 *    src/cxx/crt_shims_c.c are the real CRT shims, not placeholders),
 *    stamped here with vtable `&PTR_FUN_00544b5c`.
 *  - `param_2` is NOT a raw C string: it is handed straight to
 *    basic_string_AssignSubstr as the SOURCE OBJECT argument, which reads
 *    `*(srcObj+0x14)` as a length - that only produces a sane length for
 *    a real `std::string` object, never for a string literal. So this
 *    constructs the embedded message field (at `this+0xc`) FROM another
 *    string object, i.e. the `logic_error(const string&)` overload.
 *  - Every call site that reaches this constructs the message in a local
 *    string first (via basic_string_AssignCStr, e.g.
 *    `s_map_set_T_too_long_00551fec`, `s_invalid_bitset_N_position_*`)
 *    and then, immediately after this call returns, re-stamps a SECOND,
 *    DIFFERENT vtable (`&PTR_FUN_00544b68` or `&PTR_FUN_00544b74` -
 *    src/unnamed/FUN_00426460.c, FUN_005030a0.c, FUN_0040bae0.c,
 *    FUN_0040b600.c, FUN_004e87b0.c, FUN_004e8b10.c, FUN_00443840.c) onto
 *    the very same object before throwing via `__CxxThrowException_8` -
 *    exactly the base-ctor-then-derived-ctor vtable-stamping sequence
 *    C++ generates, with the trivial derived ctors (two distinct derived
 *    classes, matching two distinct real STL classes e.g. length_error
 *    vs out_of_range) inlined into each throw site. `PTR_FUN_00544b5c`
 *    itself is installed from exactly 3 places (docs/vtable_census.txt:
 *    installs=3, slots=2) - this ctor, its copy-ctor sibling
 *    LogicError_CopyCtor (FUN_0040b940), and the destructor
 *    FUN_0040a040 - precisely a ctor/copy-ctor/dtor set for one class.
 *  - The throw-site messages themselves ("vector<T> too long", "invalid
 *    map/set<T> iterator", "invalid bitset<N> position", "map/set<T> too
 *    long") are the verbatim strings MSVC's own `<stdexcept>`/`<xutility>`
 *    internals use for exactly `length_error`/`out_of_range`, and the
 *    sibling helpers that reach this same constructor
 *    (FUN_00520251/FUN_00520291, PROGRESS.csv status
 *    EXCLUDED-msvc-crt-atl) are independently classified pure CRT code,
 *    not game logic.
 */
#include "ghidra_types.h"


undefined4 * __thiscall LogicError_ctor(undefined4 *param_1,undefined4 param_2)

{
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  /* Windows SEH __try/__except frame setup stripped - handler body
   * (LAB_00537868) wasn't included in this function's own decompile.
   * Same rationale as entry/InitGame.c - see src/README.md. */
  FUN_00525d92();
  local_4 = 0;
  *param_1 = &PTR_FUN_00544b5c;
  param_1[8] = 0;
  param_1[9] = 0xf;
  *(undefined1 *)(param_1 + 4) = 0;
  /* (FUN_0040b9f0 below is basic_string_AssignSubstr's old symbol.)
   * DROPPED-ARG FIX (2026-09-21): FUN_0040b9f0 needs a `this` (ECX) arg
     that this call dropped entirely - orig 0x409ff8 `lea ecx,[esi+0xc]`
     (esi=this function's own param_1; ecx stays live, unclobbered,
     through to the 0x40a016 call), i.e. the embedded string field at
     param_1+0xc, not `param_2`. `param_2`/0/0xffffffff (the incoming
     message string, pos 0, count npos) were already the correct
     trailing 3 args, just missing their leading `this`. */
  basic_string_AssignSubstr((int)param_1 + 0xc,param_2,0,0xffffffff);
  return param_1;
}

