/* LogicError_CopyCtor - 0x0040b940 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED (2026-10-02), CERTAIN. The copy constructor of the same MSVC7/
 * Dinkumware `std::logic_error` object LogicError_ctor (FUN_00409fd0)
 * constructs - see that file's header for the full vtable/call-site
 * argument. This one copies the base `exception` part via
 * `exception__ctor`, re-stamps the same vtable `&PTR_FUN_00544b5c`, then
 * copies the embedded message string from `param_2+0xc` into
 * `param_1+0xc` via basic_string_AssignSubstr. It has NO code caller in
 * this tree (PROGRESS.csv xref_count 0): the real caller is the C++
 * exception-handling runtime's own "catchable type" copy-construction
 * thunk, referenced only from compiler-generated RTTI/exception-info
 * data, never from a `call` instruction - exactly what is expected of a
 * copy ctor that exists solely to let `_CxxThrowException` copy the
 * thrown object into a handler's by-value catch variable.
 *
 * (FUN_0040b9f0 in the note below is basic_string_AssignSubstr's old
 * symbol, and FUN_00409fd0 is LogicError_ctor's old symbol.)
 */
#include "ghidra_types.h"


exception * __thiscall LogicError_CopyCtor(exception *param_1,exception *param_2)

{
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_00537868;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  exception__ctor(param_1,param_2);
  local_4 = 0;
  *(undefined ***)param_1 = &PTR_FUN_00544b5c;
  *(undefined4 *)(param_1 + 0x24) = 0xf;
  *(undefined4 *)(param_1 + 0x20) = 0;
  param_1[0x10] = (exception)0x0;
  /* DROPPED-ARG FIX (2026-09-21): same shape as FUN_00409fd0's call -
     FUN_0040b9f0 needs a `this` (ECX) arg this call dropped entirely -
     orig 0x40b970 `lea ecx,[esi+0xc]` (esi=this function's own
     param_1; unclobbered through to the 0x40b98b call), i.e. the
     embedded string field at param_1+0xc. `param_2+0xc`/0/0xffffffff
     (the source exception's message field, pos 0, count npos) were
     already the correct trailing 3 args, just missing their leading
     `this`. */
  basic_string_AssignSubstr((int)param_1 + 0xc,(int)(param_2 + 0xc),0,0xffffffff);
  *unaff_FS_OFFSET = local_c;
  return param_1;
}

