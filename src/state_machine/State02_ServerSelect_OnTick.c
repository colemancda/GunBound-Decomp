/* State02_ServerSelect_OnTick - 0x004e1960 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Removing unreachable block (ram,0x004e19b9) */
/* WARNING: Removing unreachable block (ram,0x004e19c3) */
/* WARNING: Removing unreachable block (ram,0x004e1a16) */
/* WARNING: Removing unreachable block (ram,0x004e1a20) */
/* WARNING: Removing unreachable block (ram,0x004e19d1) */
/* WARNING: Removing unreachable block (ram,0x004e19db) */

void __fastcall State02_ServerSelect_OnTick(int param_1)

{
  int *piVar1;
  uint uVar2;
  char cVar3;
  undefined1 uVar4;
  int iVar5;
  int iVar6;
  undefined4 *puVar7;
  
  iVar6 = DAT_007934ec;
  *(int *)(param_1 + 0x20) = *(int *)(param_1 + 0x20) + 1;
  if ((*(char *)(param_1 + 4) != '\0') && (*(char *)(iVar6 + 0x84e4) == '\0')) {
    if (*(char *)(iVar6 + 0x84e5) == '\0') {
      DAT_0056d118 = 0xffffffff;
      if (((*(int *)(*(int *)(DAT_00e9be94 + 0x1c) + 4) == 0) &&
          (piVar1 = *(int **)(*(int *)(DAT_00e9be94 + 0x1c) + 0x10), piVar1[2] == 0)) &&
         ((piVar1[9] == 3 || (piVar1[9] == -1)))) {
        if ((char)piVar1[0x13] == '\x01') {
          (**(code **)(*piVar1 + 4))(s_active_00551e58);
        }
        else {
          (**(code **)(*piVar1 + 4))(s_ready_00551e80);
        }
      }
      if (*(int *)(*(int *)(DAT_00e9be94 + 0x1c) + 4) == 0) {
        piVar1 = *(int **)(*(int *)(DAT_00e9be94 + 0x1c) + 0x10);
        uVar2 = piVar1[2];
        while (uVar2 < 2) {
          if (uVar2 == 1) {
            if ((piVar1[9] == 3) || (piVar1[9] == -1)) {
              if ((char)piVar1[0x13] == '\x01') {
                (**(code **)(*piVar1 + 4))(s_active_00551e58);
              }
              else {
                (**(code **)(*piVar1 + 4))(s_ready_00551e80);
              }
            }
            break;
          }
          piVar1 = (int *)piVar1[4];
          uVar2 = piVar1[2];
        }
      }
      InvokeWidget(*(int *)(param_1 + 8) != -1);
      ShowErrorDialog(0);
      *(undefined1 *)(param_1 + 6) = 1;
      cVar3 = PeekPacketChecksumBool();
      if (cVar3 != '\0') {
        SetGuardedBool(0);
      }
      FUN_004d24f0();
      iVar6 = DAT_007934ec;
    }
    else {
      *(undefined1 *)(param_1 + 5) = 1;
    }
    *(undefined1 *)(param_1 + 4) = 0;
  }
  if (*(char *)(param_1 + 5) != '\0') {
    *(undefined2 *)(iVar6 + 0x4d4) = 0x1000;
    *(undefined4 *)(iVar6 + 0x44d0) = 6;
    SendOutgoingPacket(iVar6);
    *(undefined1 *)(param_1 + 5) = 0;
  }
  iVar6 = DAT_007934f0;
  if ((*(char *)(param_1 + 7) != '\0') && (*(char *)(DAT_007934f0 + 0x84e5) != '\0')) {
    *(undefined1 *)(param_1 + 7) = 0;
    puVar7 = (undefined4 *)(param_1 + 0x28);
    for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar7 = 0;
      puVar7 = puVar7 + 1;
    }
    *(undefined4 *)(iVar6 + 0x44d0) = 6;
    *(undefined2 *)(iVar6 + 0x4d4) = 0x1100;
    *(undefined1 *)(iVar6 + 0x4d6) = 0;
    iVar5 = *(int *)(iVar6 + 0x44d0);
    *(int *)(iVar6 + 0x44d0) = iVar5 + 1;
    *(undefined1 *)(iVar5 + 0x4d1 + iVar6) = 0;
    *(int *)(iVar6 + 0x44d0) = *(int *)(iVar6 + 0x44d0) + 1;
    cVar3 = PeekPacketChecksumBool();
    iVar6 = DAT_007934f0;
    if (cVar3 == '\0') {
      *(undefined2 *)(*(int *)(DAT_007934f0 + 0x44d0) + 0x4d0 + DAT_007934f0) =
           *(undefined2 *)(param_1 + 0x18);
    }
    else {
      *(ushort *)(*(int *)(DAT_007934f0 + 0x44d0) + 0x4d0 + DAT_007934f0) =
           *(ushort *)(g_clientContext + 0x3b96b) >> 4;
    }
    *(int *)(iVar6 + 0x44d0) = *(int *)(iVar6 + 0x44d0) + 2;
    SendOutgoingPacket(iVar6);
  }
  iVar6 = g_clientContext;
  iVar5 = 0;
  if (*(char *)(g_clientContext + 0x3f808) != '\0') {
    do {
      uVar4 = FUN_00402020();
      *(undefined1 *)(iVar5 + 0x4110a + iVar6) = uVar4;
      iVar5 = iVar5 + 1;
    } while (iVar5 < (int)(uint)*(byte *)(iVar6 + 0x3f808));
  }
  return;
}

