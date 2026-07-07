/* FUN_004e7740 - 0x004e7740 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 FUN_004e7740(void)

{
  LPCRITICAL_SECTION lpCriticalSection;
  int iVar1;
  uint uVar2;
  int unaff_ESI;
  uint uVar3;
  bool bVar4;
  
  if (*(int *)(unaff_ESI + 0x44de0) == 0) {
    return 0xffffffff;
  }
  lpCriticalSection = (LPCRITICAL_SECTION)(unaff_ESI + 0x17c);
  EnterCriticalSection(lpCriticalSection);
  uVar3 = 0;
  bVar4 = true;
  while( true ) {
    if (!bVar4) {
                    /* WARNING: Subroutine does not return */
      FUN_00426460();
    }
    uVar2 = 1 << ((byte)uVar3 & 0x1f);
    iVar1 = (uVar3 >> 5) * 4;
    if ((((*(uint *)(iVar1 + 0x140 + unaff_ESI) & uVar2) != 0) &&
        ((*(uint *)(iVar1 + 0x138 + unaff_ESI) & uVar2) != 0)) &&
       ((*(uint *)(iVar1 + 0x13c + unaff_ESI) & uVar2) == 0)) break;
    uVar3 = uVar3 + 1;
    bVar4 = uVar3 < 8;
    if (7 < (int)uVar3) {
      *(undefined4 *)(unaff_ESI + 0x13c) = 0;
      *(undefined4 *)(unaff_ESI + 0x138) = 0;
      InterlockedExchange((LONG *)(unaff_ESI + 0x44de0),0);
      LeaveCriticalSection(lpCriticalSection);
      return 1;
    }
  }
  LeaveCriticalSection(lpCriticalSection);
  return 0;
}

