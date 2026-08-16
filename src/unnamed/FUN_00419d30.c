/* FUN_00419d30 - 0x00419d30 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at the file's one argless PeekPacketChecksumState() call
 * ((void *)&DAT_00796878), from tools/guard_cell_resolve.py.
 */
#include "ghidra_types.h"


int FUN_00419d30(void)

{
  int iVar1;
  uint3 extraout_var;
  int iVar2;
  uint3 uVar3;
  int unaff_EBX;
  
  iVar2 = *(int *)(unaff_EBX + 0xf6ec);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar1 = PeekPacketChecksumState((void *)&DAT_00796878);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar3 = extraout_var;
  if (iVar2 == iVar1) {
    if (*(char *)(unaff_EBX + 0x1fe18) != '\0') {
      iVar2 = FUN_004f1020();
      uVar3 = (uint3)((uint)iVar2 >> 8);
      if (*(int *)(unaff_EBX + 0xf6f4) != iVar2) goto LAB_00419d7f;
    }
    return CONCAT31(uVar3,1);
  }
LAB_00419d7f:
  return (uint)uVar3 << 8;
}

