/* Vector_Insert_1e - 0x00502b00 in the original binary.
 *
 * Named above (2026-08-28, from its Vector_*_34 twin), but still a
 * raw/near-verbatim port of Ghidra's decompiler output, not
 * hand-verified. See src/README.md's "Raw/verbatim ports" section for
 * status.
 *
 * DROPPED-REG FIX (2026-08-28): the 0x1e twin of Vector_Insert_34 - the
 * public insert(pos, val), sret out-pointer in param_1, ret 0xc. Two
 * recoveries: param_3 is the ELEMENT, already passed by the one caller
 * (Vector_PushBack_1e pushes three arguments against the two the port
 * declared) and read at 0x502b4b (`mov edx,[esp+0x18]` at depth 0xc =
 * entry+0xc) to become Vector_InsertN_1e's regEdx; and EDI is the
 * VECTOR, read at 0x502b0b (`mov esi,[edi+4]`) before anything writes
 * it, held in the same register by the caller.
 *
 * The Vector_InsertN_1e call was also mis-slotted, exactly as
 * Vector_Insert_34's was: `mov ecx,1` at 0x502b51 says the __thiscall
 * receiver is the COUNT, and the vector and position are the two pushed
 * arguments (`push ebx / push edi` at 0x502b4f).
 */
#include "ghidra_types.h"


int * Vector_Insert_1e(int *param_1,int param_2,undefined4 *param_3,int regEdi)

{
  int iVar1;
  int unaff_EDI = regEdi;
  
  iVar1 = *(int *)(unaff_EDI + 4);
  if (iVar1 != 0) {
    if ((*(int *)(unaff_EDI + 8) - iVar1) / 0x1e != 0) {
      iVar1 = (param_2 - iVar1) / 0x1e;
      goto LAB_00502b4b;
    }
  }
  iVar1 = 0;
LAB_00502b4b:
  Vector_InsertN_1e(1,unaff_EDI,param_2,param_3);
  *param_1 = iVar1 * 0x1e + *(int *)(unaff_EDI + 4);
  return param_1;
}

