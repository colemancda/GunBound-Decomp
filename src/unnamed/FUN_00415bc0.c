/* FUN_00415bc0 - 0x00415bc0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * SEH-PROLOGUE ARTIFACT + DROPPED-ARGUMENT FIX (2026-07-30): same class as
 * WidgetChildArray_Destroy.c/FUN_00443c20.c/FUN_00509780.c -
 * `unaff_FS_OFFSET` was an uninitialised pointer the body wrote through
 * (`*unaff_FS_OFFSET = &local_c;`) on EVERY call, corrupting whatever
 * garbage address it happened to hold. Stripped per that idiom (no
 * __try/__except frames, no write-only `local_4` unwind marker). Also
 * wired the `AtlArray_GrowBuffer()` call with its real args - per that
 * function's own header, this call site is clean: this = param_1 (this
 * function's own array), size = param_1[1] + 1 (one past the about-to-be-
 * used index `uVar2`). Reproduced live: loading FourWord.txt (called once
 * per non-empty/non-comment line) corrupted memory via the garbage
 * FS_OFFSET write on every line, cascading into multi-megabyte runaway
 * stack growth reported as a stack overflow deep in unrelated code.
 */
#include "ghidra_types.h"


uint __fastcall FUN_00415bc0(int *param_1)

{
  int iVar1;
  uint uVar2;
  char cVar3;

  uVar2 = param_1[1];
  if ((uint)param_1[2] <= uVar2) {
    cVar3 = AtlArray_GrowBuffer(param_1, param_1[1] + 1);
    if (cVar3 == '\0') {
                    /* WARNING: Subroutine does not return */
      ThrowCxxException(0x8007000e);
    }
  }
  iVar1 = *param_1 + uVar2 * 4;
  if (iVar1 != 0) {
    FUN_00405510(iVar1);
  }
  param_1[1] = param_1[1] + 1;
  return uVar2;
}

