/* FUN_004124a0 - 0x004124a0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004124a0(char param_1)

{
  int iVar1;
  int in_EAX;
  undefined4 uVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  
  DAT_0079350c = param_1;
  g_stateChangeInProgress = in_EAX;
  CreateButtonWidget(&DAT_00e9be90,1000000,1000000,0x385,s_b_error_confirm_00552238,0x1c6,0x14b,0x4a
                     ,0x1a,1,0);
  FUN_004ee200();
  uVar8 = 1;
  uVar7 = 0x15e;
  uVar6 = 0x2b;
  puVar4 = &DAT_005b1d70;
  for (iVar3 = 0x57; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar4 = 0;
    puVar4 = puVar4 + 1;
  }
  uVar5 = 0x32;
  _DAT_00e53c24 = 0xf9;
  _DAT_00e53c28 = 0x229;
  _DAT_00e53c2c = 0xc1;
  _DAT_00e53c30 = 0x171;
  *(undefined2 *)puVar4 = 0;
  uVar2 = FUN_0043dc70(&DAT_00796eec,in_EAX + 199);
  FUN_0041b4b0(&DAT_005b1d70,uVar2,uVar5,uVar6,uVar7,uVar8);
  iVar3 = DAT_005b2b58;
  if (param_1 != '\0') {
    iVar1 = *(int *)(DAT_005b2b58 + 0x84e0);
    if (iVar1 != 0) {
      *(undefined4 *)(iVar1 + 0x22c) = 1;
      if (*(SOCKET *)(iVar1 + 0x24) != 0xffffffff) {
        closesocket(*(SOCKET *)(iVar1 + 0x24));
      }
      *(undefined4 *)(iVar1 + 0x24) = 0xffffffff;
      *(undefined1 *)(iVar1 + 0x22a) = 0;
      *(undefined1 *)(iVar3 + 0x84e5) = 0;
    }
    iVar1 = DAT_005b2b5c;
    iVar3 = *(int *)(DAT_005b2b5c + 0x84e0);
    if (iVar3 != 0) {
      *(undefined4 *)(iVar3 + 0x22c) = 1;
      if (*(SOCKET *)(iVar3 + 0x24) != 0xffffffff) {
        closesocket(*(SOCKET *)(iVar3 + 0x24));
      }
      *(undefined4 *)(iVar3 + 0x24) = 0xffffffff;
      *(undefined1 *)(iVar3 + 0x22a) = 0;
      *(undefined1 *)(iVar1 + 0x84e5) = 0;
    }
    iVar1 = DAT_005b2b60;
    iVar3 = *(int *)(DAT_005b2b60 + 0x84e0);
    if (iVar3 != 0) {
      *(undefined4 *)(iVar3 + 0x22c) = 1;
      if (*(SOCKET *)(iVar3 + 0x24) != 0xffffffff) {
        closesocket(*(SOCKET *)(iVar3 + 0x24));
      }
      *(undefined4 *)(iVar3 + 0x24) = 0xffffffff;
      *(undefined1 *)(iVar3 + 0x22a) = 0;
      *(undefined1 *)(iVar1 + 0x84e5) = 0;
    }
    if (DAT_00e55a64 != (int *)0x0) {
      (**(code **)(*DAT_00e55a64 + 4))();
    }
    DAT_00e55a64 = (int *)0x0;
    if (DAT_007934f4 != 0) {
      FUN_004059a0();
    }
    SetEvent(DAT_00e55ce8);
  }
  return;
}

