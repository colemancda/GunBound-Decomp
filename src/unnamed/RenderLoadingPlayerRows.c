/* RenderLoadingPlayerRows - 0x00442d50 in the original binary.
 *
 * Draws the loading screen's player rows: for each of up to four players
 * in one group of slots, then up to four in the other, it finds the n-th
 * occupied slot (byte at g_clientContext + 0x45914 non-zero, grouped by the
 * byte at + 0x4590c being 0 for the first pass and 1 for the second) and
 * calls RenderLoadingPlayerRow with row n (n + 4 for the second group) and
 * that slot in EDI.  Evidence is from the caller and callee: the sole
 * caller State10_Loading_Render invokes it inside its DAT_00e55a34 == -1
 * branch, right after blitting sprite 0x17, and its header describes
 * "two per-player status rows" for this part of the screen; the callee is
 * RenderLoadingPlayerRow, which draws per-player name strings and icons.
 * The stack argument is the caller's own this (ret 4, popped but never
 * read in this body).  LIKELY: the verb and noun follow the callee, and
 * the meaning of the +0x4590c grouping byte is not established.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


void RenderLoadingPlayerRows(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = 0;
LAB_00442d55:
  iVar1 = 0;
  iVar3 = 0;
  do {
    if ((*(char *)(g_clientContext + 0x4590c + iVar3) == '\0') &&
       (*(char *)(g_clientContext + 0x45914 + iVar3) != '\0')) {
      if (iVar2 == iVar1) break;
      iVar1 = iVar1 + 1;
    }
    iVar3 = iVar3 + 1;
    if (7 < iVar3) {
      iVar2 = 0;
      goto LAB_00442db0;
    }
  } while( true );
  if (iVar3 == -1) goto LAB_00442d9e;
  RenderLoadingPlayerRow(iVar2,iVar3);
  iVar2 = iVar2 + 1;
  if (3 < iVar2) goto LAB_00442d9e;
  goto LAB_00442d55;
LAB_00442d9e:
  iVar2 = 0;
LAB_00442db0:
  iVar1 = 0;
  iVar3 = 0;
  do {
    if ((*(char *)(g_clientContext + 0x4590c + iVar3) == '\x01') &&
       (*(char *)(g_clientContext + 0x45914 + iVar3) != '\0')) {
      if (iVar2 == iVar1) break;
      iVar1 = iVar1 + 1;
    }
    iVar3 = iVar3 + 1;
    if (7 < iVar3) {
      return;
    }
  } while( true );
  if (iVar3 == -1) {
    return;
  }
  RenderLoadingPlayerRow(iVar2 + 4,iVar3);
  iVar2 = iVar2 + 1;
  if (3 < iVar2) {
    return;
  }
  goto LAB_00442db0;
}

