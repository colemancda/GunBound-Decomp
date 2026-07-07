/* FUN_0043c620 - 0x0043c620 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_0043c620(void)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int unaff_ESI;
  bool bVar6;
  
  iVar3 = DAT_005b3484;
  uVar5 = 500;
  do {
    if (unaff_ESI == 0) {
      bVar6 = uVar5 == 0x1f5;
LAB_0043c655:
      if (!bVar6) goto LAB_0043c657;
    }
    else {
      if (unaff_ESI == 1) {
        bVar6 = uVar5 == 500;
        goto LAB_0043c655;
      }
      if (unaff_ESI == 2) {
        bVar6 = uVar5 == 0x1f6;
        goto LAB_0043c655;
      }
LAB_0043c657:
      iVar4 = *(int *)(*(int *)(&DAT_006a7f8c + iVar3) + 0x1c);
      uVar2 = *(uint *)(iVar4 + 4);
      if (uVar2 <= uVar5) {
LAB_0043c667:
        if (uVar2 != uVar5) break;
        iVar4 = *(int *)(iVar4 + 0x10);
        cVar1 = *(char *)(iVar4 + 0x15);
        while (cVar1 == '\0') {
          *(undefined1 *)(iVar4 + 0x14) = 1;
          iVar4 = *(int *)(iVar4 + 0x10);
          cVar1 = *(char *)(iVar4 + 0x15);
        }
      }
    }
LAB_0043c68d:
    uVar5 = uVar5 + 1;
    if (0x1f6 < uVar5) {
      return;
    }
  } while( true );
  iVar4 = *(int *)(iVar4 + 0x1c);
  uVar2 = *(uint *)(iVar4 + 4);
  if (uVar5 < uVar2) goto LAB_0043c68d;
  goto LAB_0043c667;
}

