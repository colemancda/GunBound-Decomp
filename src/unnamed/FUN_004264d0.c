/* FUN_004264d0 - 0x004264d0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED REGISTERS ANALYSED, NOT APPLIED.  `ret 0`, and FOUR registers are
 * read before being written: ECX, EBX, ESI and EDI.  At the sole call site
 * (0x0042590b):
 *
 *   ecx = eax, and eax's own last write is a `cmp` -- so its value comes from
 *         further back than the call-site window reaches
 *   ebx = [edi + 0x67ec60]    <- context-relative, but through EDI
 *   esi = 1
 *   edi is pushed, so its value is live from earlier still
 *
 * Only ESI is determined.  One of four is not worth writing.
 */
#include "ghidra_types.h"


void __fastcall FUN_004264d0(int param_1)

{
  int iVar1;
  int iVar2;
  int *unaff_EBX;
  int unaff_ESI;
  
  if ((uint)unaff_EBX[1] < (uint)(param_1 + unaff_ESI)) {
                    /* WARNING: Subroutine does not return */
    ThrowCxxException(0x80070057);
  }
  iVar1 = (unaff_EBX[1] - param_1) - unaff_ESI;
  for (iVar2 = unaff_ESI; iVar2 != 0; iVar2 = iVar2 + -1) {
    FUN_00405320();
  }
  if (iVar1 != 0) {
    _memmove((void *)(*unaff_EBX + param_1 * 4),(void *)(*unaff_EBX + (param_1 + unaff_ESI) * 4),
             iVar1 * 4);
  }
  unaff_EBX[1] = unaff_EBX[1] - unaff_ESI;
  return;
}

