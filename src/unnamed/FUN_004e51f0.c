/* FUN_004e51f0 - 0x004e51f0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004e51f0(void)

{
  uint uVar1;
  uint in_EAX;
  uint uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  int unaff_ESI;
  int iVar7;
  
  uVar1 = *(uint *)(&DAT_006a7f7c + g_clientContext);
  if (uVar1 == 0) {
    *(undefined1 *)(unaff_ESI + 0x2c) = 1;
    return;
  }
  uVar5 = *(uint *)(unaff_ESI + 8);
  uVar6 = in_EAX;
  if (((int)uVar5 < (int)in_EAX) || (uVar6 = uVar5, (int)uVar5 <= (int)in_EAX)) {
    in_EAX = uVar5;
  }
  uVar5 = 0;
  if (uVar1 != 0) {
    iVar4 = 0;
    do {
      if (*(uint *)(&DAT_006a7f7c + g_clientContext) <= uVar5) {
                    /* WARNING: Subroutine does not return */
        FUN_004010c0(0x80070057);
      }
      uVar2 = (uint)*(ushort *)(*(int *)(&DAT_006a7f78 + g_clientContext) + 2 + iVar4);
      if ((int)uVar6 <= (int)uVar2) {
        uVar6 = uVar2;
      }
      if ((int)uVar2 <= (int)in_EAX) {
        in_EAX = uVar2;
      }
      uVar5 = uVar5 + 1;
      iVar4 = iVar4 + 6;
    } while (uVar5 < uVar1);
  }
  *(uint *)(unaff_ESI + 0x24) = in_EAX + 0x96;
  *(uint *)(unaff_ESI + 0x28) = uVar6 - 0x96;
  if ((int)(uVar6 - 400) < (int)(in_EAX + 400)) {
    iVar4 = (int)(uVar6 - in_EAX) / 2 + -400 + in_EAX;
    *(int *)(unaff_ESI + 0x24) = iVar4;
    *(int *)(unaff_ESI + 0x28) = iVar4 + 800;
  }
  if ((*(int *)(unaff_ESI + 8) + -300 < (int)in_EAX) && ((int)uVar6 < *(int *)(unaff_ESI + 8) + 300)
     ) {
    *(undefined1 *)(unaff_ESI + 0x2e) = 1;
  }
  iVar4 = *(int *)(unaff_ESI + 0x24);
  iVar3 = *(int *)(unaff_ESI + 0x18) + -400;
  iVar7 = iVar3;
  if (iVar4 <= iVar3) {
    iVar7 = iVar4;
  }
  if (iVar7 < 400) {
    iVar4 = 400;
  }
  else if (iVar3 < iVar4) {
    iVar4 = iVar3;
  }
  *(int *)(unaff_ESI + 0x24) = iVar4;
  iVar4 = *(int *)(unaff_ESI + 0x28);
  iVar7 = iVar3;
  if (iVar4 <= iVar3) {
    iVar7 = iVar4;
  }
  if (iVar7 < 400) {
    iVar3 = 400;
  }
  else if (iVar4 <= iVar3) {
    iVar3 = iVar4;
  }
  *(int *)(unaff_ESI + 0x28) = iVar3;
  *(undefined1 *)(unaff_ESI + 0x2c) = 0;
  *(undefined1 *)(unaff_ESI + 0x864) = 1;
  *(undefined1 *)(unaff_ESI + 0x2d) = 1;
  return;
}

