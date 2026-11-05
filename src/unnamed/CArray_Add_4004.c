/* CArray_Add_4004 - 0x004e5c70 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * Evidence (outside the body): the 0x4004-stride sibling of
 * CArray_Add_1750 (same shape: grow through CArray_Grow_4004 when the
 * count reaches the capacity, throw 0x8007000e if growth fails, copy the
 * caller's record into slot index count, bump the count, return the old
 * index), and CArray_Grow_4004 is its named callee. Its sole caller
 * SendSocketData copies the unsent packet into a stack buffer and appends
 * it here, to the array at conn+0x24a40, inside EnterCriticalSection /
 * LeaveCriticalSection on conn+0x24a58, when send fails with
 * WSAEWOULDBLOCK (0x2733). Named CArray_ to match CArray_Grow_4004 and
 * CArray_Add_1750.
 */
#include "ghidra_types.h"


uint CArray_Add_4004(undefined4 *param_1,int *regEbx)

{
  uint uVar1;
  char cVar2;
  int iVar3;
  undefined4 *puVar4;
  
  uVar1 = regEbx[1];
  if ((uint)regEbx[2] <= uVar1) {
    cVar2 = CArray_Grow_4004(uVar1 + 1,regEbx);
    if (cVar2 == '\0') {
                    /* WARNING: Subroutine does not return */
      ThrowCxxException(0x8007000e);
    }
  }
  puVar4 = (undefined4 *)(uVar1 * 0x4004 + *regEbx);
  if (puVar4 != (undefined4 *)0x0) {
    for (iVar3 = 0x1001; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar4 = *param_1;
      param_1 = param_1 + 1;
      puVar4 = puVar4 + 1;
    }
  }
  regEbx[1] = regEbx[1] + 1;
  return uVar1;
}

