/* FUN_0042a090 - 0x0042a090 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Removing unreachable block (ram,0x0042a0d2) */
/* WARNING: Removing unreachable block (ram,0x0042a0dc) */

void FUN_0042a090(void)

{
  int *piVar1;
  uint uVar2;
  undefined1 uVar3;
  int iVar4;
  undefined4 uVar5;
  uint3 uVar6;
  char cVar7;
  undefined4 unaff_EBX;
  int unaff_EDI;
  
  cVar7 = (char)unaff_EBX;
  DAT_0056d118 = (cVar7 != '\x01') - 1;
  InvokeWidget(unaff_EBX);
  InvokeWidget(unaff_EBX);
  if (*(int *)(*(int *)(DAT_00e9be94 + 0x1c) + 4) == 0) {
    piVar1 = *(int **)(*(int *)(DAT_00e9be94 + 0x1c) + 0x10);
    uVar2 = piVar1[2];
    while (uVar2 < 3) {
      if (uVar2 == 2) {
        (**(code **)(*piVar1 + 4))(s_disable_00551e68);
        break;
      }
      piVar1 = (int *)piVar1[4];
      uVar2 = piVar1[2];
    }
  }
  if (cVar7 != '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar4 != 1) {
      uVar5 = 1;
      goto LAB_0042a13e;
    }
  }
  uVar5 = 0;
LAB_0042a13e:
  InvokeWidget(uVar5);
  InvokeWidget(unaff_EBX);
  if ((*(int *)(unaff_EDI + 4) == -1) || (cVar7 == '\0')) {
    uVar5 = 0;
  }
  else {
    uVar5 = 1;
  }
  InvokeWidget(uVar5);
  InvokeWidget(unaff_EBX);
  InvokeWidget(unaff_EBX);
  uVar6 = (uint3)((uint)*(int *)(unaff_EDI + 0x118) >> 8);
  if ((*(int *)(unaff_EDI + 0x118) < 1) || (cVar7 == '\0')) {
    iVar4 = (uint)uVar6 << 8;
  }
  else {
    iVar4 = CONCAT31(uVar6,1);
  }
  InvokeWidget(iVar4);
  if ((*(char *)(unaff_EDI + 0x120) == '\0') || (cVar7 == '\0')) {
    uVar3 = 0;
  }
  else {
    uVar3 = 1;
  }
  InvokeWidget(uVar3);
  InvokeWidget(unaff_EBX);
  InvokeWidget(unaff_EBX);
  return;
}

