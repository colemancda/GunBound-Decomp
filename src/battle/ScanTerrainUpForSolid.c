/* ScanTerrainUpForSolid - 0x004e4390 in the original binary.
 *
 * Scans a terrain column UPWARD from a row for the first solid pixel and
 * returns that row, or -10000 if none.  in_EAX = row (clamped to height-1),
 * unaff_EDI = column (checked against width), regEsi = the terrain context
 * (+0x18 width = the row stride the walk steps by, +0x1c height, +0x34
 * pixels).  The row-wise twin is ScanTerrainLeftForSolid; the two share the
 * -10000 sentinel and the same clamp-then-walk shape.
 */
#include "ghidra_types.h"


int ScanTerrainUpForSolid(int regEsi)

{
  int iVar1;
  int in_EAX;
  char *pcVar2;
  int unaff_EDI;
  
  if ((-1 < unaff_EDI) && (iVar1 = *(int *)(regEsi + 0x18), unaff_EDI < iVar1)) {
    if (*(int *)(regEsi + 0x1c) <= in_EAX) {
      in_EAX = *(int *)(regEsi + 0x1c) + -1;
    }
    pcVar2 = (char *)(iVar1 * in_EAX + *(int *)(regEsi + 0x34) + unaff_EDI);
    while( true ) {
      if (in_EAX < 0) {
        return -10000;
      }
      if (*pcVar2 != '\0') break;
      pcVar2 = pcVar2 + -iVar1;
      in_EAX = in_EAX + -1;
    }
    return in_EAX;
  }
  return -10000;
}

