/* NextAvatarItemOrdinal - 0x0044c310 in the original binary.
 *
 * Returns the maximum of the dword at +4 over the 0x450-byte records of the
 * array at g_clientContext + 0x44e20, plus one (-1 + 1 = 0 when the array
 * is empty).  Evidence is from the sole caller: the GB_OP_BUY_RESPONSE arm
 * of State07_AvatarStore_ProcessPacket (call at 0x00445067) builds a fresh
 * record on the stack and stores this result into local_464, i.e. that
 * record's +4 (local_468 is the record base), before AtlArray_Add_450
 * appends the record to the 0x44e20 array and to the 0x44e30 array.  The
 * record's +4 field is documented in AtlArray_CopyElement_450 as an index
 * renumbered after a removal (see DecrementAvatarItemOrdinalsAbove, which
 * decrements every +4 above a removed record's own); the 0x6002 inventory
 * branch seeds it with -1.  So +4 is a running ordinal and this yields the
 * next one.  "Ordinal" rather than "Order" because the field is not
 * shown to be a purchase order; its on-screen use is not established.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


int NextAvatarItemOrdinal(void)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = -1;
  uVar1 = 0;
  if (0 < *(int *)(g_clientContext + 0x44e24)) {
    iVar2 = 0;
    do {
      if (*(uint *)(g_clientContext + 0x44e24) <= uVar1) {
LAB_0044c364:
                    /* WARNING: Subroutine does not return */
        ThrowCxxException(0x80070057);
      }
      if (iVar3 < *(int *)(*(int *)(g_clientContext + 0x44e20) + 4 + iVar2)) {
        if (*(uint *)(g_clientContext + 0x44e24) <= uVar1) goto LAB_0044c364;
        iVar3 = *(int *)(iVar2 + 4 + *(int *)(g_clientContext + 0x44e20));
      }
      uVar1 = uVar1 + 1;
      iVar2 = iVar2 + 0x450;
    } while ((int)uVar1 < *(int *)(g_clientContext + 0x44e24));
  }
  return iVar3 + 1;
}

