/* ScanTerrainLeftForSolid - 0x004e43d0 in the original binary.
 *
 * Scans a terrain row LEFTWARD from a column for the first solid pixel and
 * returns that column, or -10000 if the row has none (or the row is out of
 * range).  param_1 = column (clamped to width-1), regEax = row (checked
 * against height), param_2 = the terrain context: +0x18 width, +0x1c height,
 * +0x34 pixel buffer, one byte per pixel, non-zero = solid.
 *
 * Named as one of a pair: ScanTerrainUpForSolid is the same walk along a
 * column (stepping by the row stride) instead of along a row.
 *
 * RE-SLOTTED AND EAX RECOVERED (2026-08-24, workflow-analysed, hand-checked).
 * `ret 0` with two declared params: both are registers (param_1 = ECX, the
 * column, clamped to width-1 = [ctx+0x18]-1; param_2 = EDX, the terrain
 * context &DAT_006a7708 + g_clientContext), and EAX is the row, range-checked
 * against [ctx+0x1c].  All five call sites passed nothing.  At every site
 * ECX is the result of the SECOND bare PeekChecksumStateUnderLock statement
 * above the call and EAX the FIRST -- results the port had been discarding;
 * the callers now capture them as peekCol / peekRow.  Scans a terrain row
 * leftward from the column for the first solid pixel.
 */
#include "ghidra_types.h"


int __fastcall ScanTerrainLeftForSolid(int param_1,int param_2,int regEax)

{
  int iVar1;
  
  if ((-1 < regEax) && (regEax < *(int *)(param_2 + 0x1c))) {
    iVar1 = *(int *)(param_2 + 0x18);
    if (iVar1 <= param_1) {
      param_1 = iVar1 + -1;
    }
    if (-1 < param_1) {
      for (; *(char *)(iVar1 * regEax + *(int *)(param_2 + 0x34) + param_1) == '\0';
          param_1 = param_1 + -1) {
      }
      return param_1;
    }
  }
  return -10000;
}

