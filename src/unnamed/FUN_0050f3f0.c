/* FUN_0050f3f0 - 0x0050f3f0 in the original binary.
 *
 * CScrollBar drag-position solver: given the mouse Y already offset by
 * the thumb grab point (m_grabOffset + mouseY, computed by the sole
 * caller FUN_0050f460/CScrollBar's mouse-move handler at 0x50f460), maps
 * it back to a scroll position in [0, total-pageSize]. Uses the same
 * thumb-height floor/round-to-5 shape as ScrollListWidget_ThumbHeight
 * (0x50e050).
 *
 * FIXED (2026-07-13): dropped-register-argument bug, same class as
 * ThumbHeight/IsOverThumb next to this one - `unaff_ESI` (this) and
 * `in_EAX` (the grab-offset-adjusted Y) were declared but never
 * assigned. Confirmed via objdump at the sole call site (0x50f4a6-
 * 0x50f4ab): `mov eax,[esi+0x48]` (m_grabOffset) `; add eax,edi`
 * (mouse Y) `; call 0x50f3f0` - ESI (this) carries over unclobbered
 * from the caller's own ESI=this. Promoted to two explicit parameters.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


uint FUN_0050f3f0(int thisPtr,int grabAdjustedY)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;

  iVar6 = *(int *)(thisPtr + 0x34);
  iVar2 = grabAdjustedY - *(int *)(thisPtr + 0x2c);
  iVar1 = *(int *)(thisPtr + 0x38);
  iVar4 = iVar6;
  if (0 < iVar1) {
    iVar3 = (*(int *)(thisPtr + 0x3c) * iVar6) / iVar1;
    iVar4 = 10;
    if (9 < iVar3) {
      iVar4 = iVar3;
    }
    iVar4 = (iVar4 / 5) * 5;
  }
  iVar6 = iVar6 - iVar4;
  uVar5 = iVar1 - *(int *)(thisPtr + 0x3c);
  uVar5 = uVar5 & ((int)uVar5 < 0) - 1;
  if (iVar2 < 1) {
    return 0;
  }
  if (iVar2 < iVar6) {
    if (iVar6 < 1) {
      iVar6 = 1;
    }
    uVar5 = (int)(uVar5 * iVar2) / iVar6;
  }
  return uVar5;
}

