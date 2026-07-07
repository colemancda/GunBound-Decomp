/* FUN_00442d50 - 0x00442d50 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00442d50(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = 0;
LAB_00442d55:
  iVar1 = 0;
  iVar3 = 0;
  do {
    if ((*(char *)(DAT_005b3484 + 0x4590c + iVar3) == '\0') &&
       (*(char *)(DAT_005b3484 + 0x45914 + iVar3) != '\0')) {
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
  FUN_00442e00();
  iVar2 = iVar2 + 1;
  if (3 < iVar2) goto LAB_00442d9e;
  goto LAB_00442d55;
LAB_00442d9e:
  iVar2 = 0;
LAB_00442db0:
  iVar1 = 0;
  iVar3 = 0;
  do {
    if ((*(char *)(DAT_005b3484 + 0x4590c + iVar3) == '\x01') &&
       (*(char *)(DAT_005b3484 + 0x45914 + iVar3) != '\0')) {
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
  FUN_00442e00();
  iVar2 = iVar2 + 1;
  if (3 < iVar2) {
    return;
  }
  goto LAB_00442db0;
}

