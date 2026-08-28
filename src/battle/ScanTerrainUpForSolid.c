/* ScanTerrainUpForSolid - 0x004e4390 in the original binary.
 *
 * Scans a terrain column UPWARD from a row for the first solid pixel and
 * returns that row, or -10000 if none.  in_EAX = row (clamped to height-1),
 * unaff_EDI = column (checked against width), regEsi = the terrain context
 * (+0x18 width = the row stride the walk steps by, +0x1c height, +0x34
 * pixels).  The row-wise twin is ScanTerrainLeftForSolid; the two share the
 * -10000 sentinel and the same clamp-then-walk shape.
 *
 * DROPPED REGISTERS RECOVERED (2026-08-27): in_EAX is the starting ROW and
 * unaff_EDI the COLUMN, and both are guard-peek results the callers were
 * discarding.  Each site reads
 * `PeekChecksumStateUnderLock(<row cell>)` then
 * `PeekChecksumStateUnderLock(<column cell>)` immediately before the call,
 * and the second result stays in EDI across it.
 *
 * All three caller files already had this exact shape written down for the
 * sibling ScanTerrainLeftForSolid -- locals named peekRow/peekCol capturing
 * the two peeks instead of dropping them -- so these sites reuse it rather
 * than inventing anything.  Sites within one caller are separated by their
 * guard-cell constants (0xa, then the 0xb/0xc and 0xd/0xe pairs) and by
 * whether the second helper is the Add or the Sub form.
 */
#include "ghidra_types.h"


int ScanTerrainUpForSolid(int regEsi,int regEax,int regEdi)

{
  int iVar1;
  int in_EAX = regEax;
  char *pcVar2;
  int unaff_EDI = regEdi;
  
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

