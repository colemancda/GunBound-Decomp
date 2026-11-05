/* basic_string_Erase - 0x0040bda0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * Evidence (outside the body): both callers are in
 * basic_string_AssignSubstr, which implements assign(str, pos, n) in place
 * as erase(pos + n, npos) followed by erase(0, n) on a string that is its
 * own source. The string layout (buffer or SSO storage at +4, size at
 * +0x14, capacity at +0x18, SSO threshold 0xf) matches the dinkumware
 * basic_string that basic_string_Copy and basic_string_AssignCStr share.
 * On pos > size it calls 0x520251, which throws an exception built from
 * the string 'invalid string position' (stored at 0x544b7c), exactly
 * std::string::erase's out_of_range message in MSVC 7.1. It returns this,
 * as erase(pos, n) does.
 *
 * DROPPED-ARGUMENT FIX (2026-09-20, no-prototype sweep). A std::string-
 * style erase(pos,count): `ret 8` at the epilogue (orig 0x40be12)
 * confirms 2 STACK arguments (param_2/param_3) plus ECX (param_1, `this`)
 * = 3 total, matching the declaration already in place - no register/
 * decl mismatch. The bug was purely at both call sites (both in
 * FUN_0040b9f0.c), which had NO prototype in include/functions.h (the
 * header's generator skips this split-line `int __thiscall` definition,
 * per fastcall-decls-missing-from-functions-h), so a 2-argument call
 * compiled silently instead of erroring, dropping the ECX/`this`
 * argument. Confirmed at orig 0x40ba1b-0x40ba2c (`mov ecx,ebx` precedes
 * each call; ebx is FUN_0040b9f0's own param_1/this, unchanged from the
 * caller). Fixed both calls to pass that `this` pointer as the new first
 * argument.
 */
#include "ghidra_types.h"


int __thiscall basic_string_Erase(int param_1,uint param_2,uint param_3)

{
  undefined4 *puVar1;
  uint uVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  
  if (*(uint *)(param_1 + 0x14) < param_2) {
    FUN_00520251();
  }
  uVar2 = *(int *)(param_1 + 0x14) - param_2;
  if (uVar2 < param_3) {
    param_3 = uVar2;
  }
  if (param_3 != 0) {
    puVar5 = (undefined4 *)(param_1 + 4);
    puVar4 = puVar5;
    puVar1 = puVar5;
    if (0xf < *(uint *)(param_1 + 0x18)) {
      puVar4 = (undefined4 *)*puVar5;
      puVar1 = (undefined4 *)*puVar5;
    }
    _memmove((void *)((int)puVar4 + param_2),(void *)((int)puVar1 + param_3 + param_2),
             uVar2 - param_3);
    iVar3 = *(int *)(param_1 + 0x14) - param_3;
    *(int *)(param_1 + 0x14) = iVar3;
    if (0xf < *(uint *)(param_1 + 0x18)) {
      puVar5 = (undefined4 *)*puVar5;
    }
    *(undefined1 *)((int)puVar5 + iVar3) = 0;
  }
  return param_1;
}

