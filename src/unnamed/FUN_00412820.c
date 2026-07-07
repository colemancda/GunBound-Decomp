/* FUN_00412820 - 0x00412820 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00412820(undefined4 param_1,int param_2)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  
  g_stateChangeInProgress = 0x34;
  DAT_0079350c = param_2;
  CreateButtonWidget(&DAT_00e9be90,1000000,1000000,0x385,s_b_error_confirm_00552238,0x1c6,0x14b,0x4a
                     ,0x1a,1,0);
  FUN_004ee200();
  puVar3 = &DAT_005b1d70;
  for (iVar2 = 0x57; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  _DAT_00e53c24 = 0xf9;
  _DAT_00e53c28 = 0x229;
  _DAT_00e53c2c = 0xc1;
  _DAT_00e53c30 = 0x171;
  *(undefined2 *)puVar3 = 0;
  FUN_0041b4b0(&DAT_005b1d70,param_1,0x32,0x2b,0x15e,1);
  iVar2 = DAT_005b2b58;
  if (param_2 != '\0') {
    iVar1 = *(int *)(DAT_005b2b58 + 0x84e0);
    if (iVar1 != 0) {
      *(undefined4 *)(iVar1 + 0x22c) = 1;
      if (*(SOCKET *)(iVar1 + 0x24) != 0xffffffff) {
        closesocket(*(SOCKET *)(iVar1 + 0x24));
      }
      *(undefined4 *)(iVar1 + 0x24) = 0xffffffff;
      *(undefined1 *)(iVar1 + 0x22a) = 0;
      *(undefined1 *)(iVar2 + 0x84e5) = 0;
    }
    iVar1 = DAT_005b2b5c;
    iVar2 = *(int *)(DAT_005b2b5c + 0x84e0);
    if (iVar2 != 0) {
      *(undefined4 *)(iVar2 + 0x22c) = 1;
      if (*(SOCKET *)(iVar2 + 0x24) != 0xffffffff) {
        closesocket(*(SOCKET *)(iVar2 + 0x24));
      }
      *(undefined4 *)(iVar2 + 0x24) = 0xffffffff;
      *(undefined1 *)(iVar2 + 0x22a) = 0;
      *(undefined1 *)(iVar1 + 0x84e5) = 0;
    }
    iVar1 = DAT_005b2b60;
    iVar2 = *(int *)(DAT_005b2b60 + 0x84e0);
    if (iVar2 != 0) {
      *(undefined4 *)(iVar2 + 0x22c) = 1;
      if (*(SOCKET *)(iVar2 + 0x24) != 0xffffffff) {
        closesocket(*(SOCKET *)(iVar2 + 0x24));
      }
      *(undefined4 *)(iVar2 + 0x24) = 0xffffffff;
      *(undefined1 *)(iVar2 + 0x22a) = 0;
      *(undefined1 *)(iVar1 + 0x84e5) = 0;
    }
    if (DAT_007934f4 != 0) {
      FUN_004059a0();
    }
    SetEvent(DAT_00e55ce8);
  }
  return;
}

