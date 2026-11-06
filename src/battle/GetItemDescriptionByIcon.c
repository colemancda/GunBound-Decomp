/* GetItemDescriptionByIcon - 0x0041eb80 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * Evidence (outside the body): sole caller is BuildItemDescriptionTooltip
 * (0x5096b7, `push 0xffff / push ebp / push [0x5b3484]`), which calls this
 * and FindItemRecordByIcon (0x41eb10) with the same two arguments
 * (g_clientContext, item id).  The FindItemRecordByIcon result is the
 * record whose first string is copied into the tooltip's +0x90 item-name
 * field; this function's result is instead handed as the text argument of
 * CreateStaticTextWidget(0x17, 0x22, 0x8c, 0x4c, text, 0xffff), the
 * 140x76 body box under the name, and the body of the tooltip is the item
 * description.  The walk is the same one as FindItemRecordByIcon's (100
 * records of 0x9bc bytes starting at ctx+0x58b248, the icon-id cell at
 * record+0x698 compared with the argument); the difference is the return
 * value: FindItemRecordByIcon returns the record base (0x41eb6a,
 * ctx+0x58b248+i*0x9bc, where the name sits) and this returns record+0x8bc
 * (ctx+0x58bb04).  Item id is an icon id in both, hence "ByIcon".
 * Returns 0 when no record matches.
 *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at the file's one argless PeekPacketChecksumState() call: the item table's icon-id cell - FindItemRecordByIcon's walk (this one returns the +0x58bb04 field of the hit).
 */
#include "ghidra_types.h"


undefined * GetItemDescriptionByIcon(int param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = 0;
  do {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    uVar1 = PeekPacketChecksumState((void *)(param_1 + 0x58b8e0 + iVar2 * 0x9bc));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    if (param_2 == uVar1) {
      return &DAT_0058bb04 + param_1 + iVar2 * 0x9bc;
    }
    iVar2 = iVar2 + 1;
  } while (iVar2 < 100);
  return (undefined *)0x0;
}

