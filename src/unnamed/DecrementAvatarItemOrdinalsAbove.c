/* DecrementAvatarItemOrdinalsAbove - 0x0044c370 in the original binary.
 *
 * Decrements the dword at +4 of every 0x450-byte record in the array at
 * g_clientContext + 0x44e20 whose +4 is greater than the threshold in EBX
 * (signed compare, jle skips).  Evidence is from the two callers, the
 * GB_OP_GIFT_RESPONSE arm (call at 0x0044494e) and the sell arm (call at
 * 0x00444d90) of State07_AvatarStore_ProcessPacket: each passes, in EBX,
 * the +4 of the record it is about to remove, and the very next statement
 * is AtlArray_RemoveAt_450 on that same index.  So after a removal the
 * remaining +4 values stay dense.  Counterpart of NextAvatarItemOrdinal,
 * which appends max + 1 on a purchase.  AtlArray_CopyElement_450 already
 * records +4 as an index renumbered after a removal.
 *
 * The threshold arrives in EBX (Ghidra's regEbx parameter), which both call
 * sites already pass.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


void DecrementAvatarItemOrdinalsAbove(int regEbx)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  
  iVar2 = g_clientContext;
  iVar1 = *(int *)(g_clientContext + 0x44e24);
  uVar3 = 0;
  if (0 < iVar1) {
    iVar4 = 0;
    do {
      if (*(uint *)(iVar2 + 0x44e24) <= uVar3) {
LAB_0044c3c3:
                    /* WARNING: Subroutine does not return */
        ThrowCxxException(0x80070057);
      }
      if (regEbx < *(int *)(*(int *)(iVar2 + 0x44e20) + 4 + iVar4)) {
        if (*(uint *)(iVar2 + 0x44e24) <= uVar3) goto LAB_0044c3c3;
        *(int *)(iVar4 + 4 + *(int *)(iVar2 + 0x44e20)) =
             *(int *)(iVar4 + 4 + *(int *)(iVar2 + 0x44e20)) + -1;
      }
      uVar3 = uVar3 + 1;
      iVar4 = iVar4 + 0x450;
    } while ((int)uVar3 < iVar1);
  }
  return;
}

