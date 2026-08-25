/* FUN_004dffb0 - 0x004dffb0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * EAX RECOVERED (2026-08-25) from the single site in FUN_004dfdb0, whose frame
 * is fixed by its own prologue: `mov ebx,[esp+0x14]` = E+8 = param_2 and
 * `mov edi,[esp+0x1c]` = E+4 = param_1, both loaded once at the entry and
 * never rewritten.  So `mov eax,ebx` at 0x4dfe4f is param_2,
 * and the pushed argument is param_1.
 * This is the introsort tail: the caller falls into it once the range is
 * large but the depth budget has run out.
 */
#include "ghidra_types.h"


void FUN_004dffb0(int param_1,int regEax)

{
  int iVar1;
  
  iVar1 = regEax - param_1 >> 2;
  if (1 < iVar1) {
    iVar1 = iVar1 - (regEax - param_1 >> 0x1f) >> 1;
    while (0 < iVar1) {
      iVar1 = iVar1 + -1;
      FUN_004e01b0(param_1,(regEax - param_1) >> 2,iVar1,*(int *)(param_1 + iVar1 * 4));
    }
  }
  return;
}

