/* RoomCardHitTest - 0x0042ada0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED REGISTER RECOVERED (2026-08-27): unaff_ESI is the X coordinate.
 * The body decides it -- ESI is the value tested against the 300-wide column
 * span `(i/3)*300 + 0x18 .. + 0x119` while param_1 is tested against the
 * 60-wide row span -- and the callers confirm it.
 *
 * State03_GameRoomList_HandleMouseInput packs both halves in one LPARAM: the
 * source already passes `param_4 >> 0x10` as the row, and the binary takes
 * ESI from `movzx esi,ax` on the same [esp+0x14] value, i.e. the low half.
 * All three of its sites are identical, so they need no pairing.
 * FUN_00429730 pairs `mov esi,[0x56d10c]` = g_cursorAnchorX with the
 * g_cursorAnchorY the source already passes. */
#include "ghidra_types.h"


int RoomCardHitTest(int param_1,int param_2,int regEsi)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int unaff_ESI = regEsi;
  
  iVar2 = 0;
  piVar4 = (int *)(g_clientContext + 0x4464c);
  while( true ) {
    iVar1 = (iVar2 / 3) * 300;
    iVar3 = (iVar2 % 3) * 0x3c;
    if (((((iVar1 + 0x18 < unaff_ESI) && (unaff_ESI < iVar1 + 0x119)) && (iVar3 + 0x3a < param_1))
        && (param_1 < iVar3 + 0x74)) &&
       ((param_2 != '\0' ||
        (((*piVar4 == 1 && (*(char *)(g_clientContext + 0x449a8 + iVar2) == '\0')) &&
         (*(char *)(g_clientContext + 0x4499c + iVar2) != *(char *)(g_clientContext + 0x449a2 + iVar2)))))
       )) break;
    iVar2 = iVar2 + 1;
    piVar4 = piVar4 + 1;
    if (5 < iVar2) {
      return -1;
    }
  }
  return iVar2;
}

