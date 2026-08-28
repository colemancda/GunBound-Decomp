/* FindItemGridCell - 0x004dc570 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
*
 * DROPPED REGISTERS RECOVERED (2026-08-27): unaff_ESI is the X coordinate and
 * unaff_EDI the Y.  The body decides which is which -- ESI is tested against
 * the 0x40-wide column span `(i%3)*0x46 + 0x210 .. +0x250` and EDI against
 * the 0x2b-wide row span `(i/3)*0x2d + 0x193 .. +0x1be`.
 *
 * Both State09_ReadyRoom_HandleChatInput sites carry the two halves of the
 * same packed coordinate, param_4, so they need no pairing between them even
 * though they sit in one caller: one splits it inline (`movzx esi,ax` /
 * `shr edi,0x10` off [esp+0xe4] = E+0xc = param_4 under four prologue saves),
 * and the other reads back the halves that an earlier block spilled from the
 * same parameter -- `movzx ecx,ax` / `shr eax,0x10` at 0x4d6372, stored one
 * push deep at 0x4d637f and 0x4d6383 into the slots the call site loads.
 * Ghidra names neither slot, which is why the second site looks unresolvable
 * until the pending push is counted.
 *
 * State09_ReadyRoom_OnTick pairs g_cursorAnchorX with g_cursorAnchorY, the
 * same globals RoomCardHitTest takes.
 */
#include "ghidra_types.h"


int FindItemGridCell(int regEsi,int regEdi)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int unaff_ESI = regEsi;
  int unaff_EDI = regEdi;
  
  iVar2 = 0;
  while( true ) {
    iVar3 = (iVar2 % 3) * 0x46;
    iVar1 = (iVar2 / 3) * 0x2d;
    if ((((iVar3 + 0x210 <= unaff_ESI) && (unaff_ESI <= iVar3 + 0x250)) &&
        (iVar1 + 0x193 <= unaff_EDI)) && (unaff_EDI <= iVar1 + 0x1be)) break;
    iVar2 = iVar2 + 1;
    if (8 < iVar2) {
      return -1;
    }
  }
  return iVar2;
}

