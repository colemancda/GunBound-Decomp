/* FUN_00502a20 - 0x00502a20 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-REG FIX (2026-08-28): param_3 declared. It was already being
 * passed - FUN_00502800 calls this with three arguments against a
 * two-parameter declaration - and it is read at 0x502a67
 * (`mov edx,[esp+0x18]` with ebx, ebp and esi pushed, i.e. entry+0xc)
 * to become Vector_InsertN_34's EDX, the element being inserted.
 *
 * The Vector_InsertN_34 call below was mis-slotted as well. The original
 * sets `mov ecx,1` at 0x502a6d, so the __thiscall receiver is the COUNT,
 * and pushes ebx then edi - i.e. param_3 then param_2 in reverse
 * argument order - so the vector and the position are the two stack
 * arguments. The port had passed the vector into ECX.
 *
 * EDI remains this function's own outstanding dropped register: it is
 * the vector, read at 0x502a2b before anything writes it, and its one
 * caller FUN_00502800 holds it in the same register.
 */
#include "ghidra_types.h"


int * FUN_00502a20(int *param_1,int param_2,undefined4 *param_3)

{
  int iVar1;
  int unaff_EDI;
  
  iVar1 = *(int *)(unaff_EDI + 4);
  if (iVar1 != 0) {
    if ((*(int *)(unaff_EDI + 8) - iVar1) / 0x34 != 0) {
      iVar1 = (param_2 - iVar1) / 0x34;
      goto LAB_00502a67;
    }
  }
  iVar1 = 0;
LAB_00502a67:
  Vector_InsertN_34(1,unaff_EDI,param_2,param_3);
  *param_1 = iVar1 * 0x34 + *(int *)(unaff_EDI + 4);
  return param_1;
}

