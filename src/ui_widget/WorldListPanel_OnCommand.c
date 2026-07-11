/* WorldListPanel_OnCommand - 0x0050d810 in the original binary.
 *
 * Command handler for the WORLD LIST panel (vtable slot at PTR_LAB_00557f08).
 * Handles child-widget events for the server browser, writing directly into
 * the ServerSelect state object (g_gameStateVTableArray[2]):
 *   - param_2==0, param_3==0: reset to the top page - zero scroll offset
 *     (state +0x14/+0x18) and the per-slot error array, then send an outgoing
 *     0x1100 request for page 0.
 *   - param_2==0, param_3==1: the other page/refresh action - sends 0x1101
 *     (with a selector record) or clears the list, and updates button labels.
 *   - other param_2 (e.g. the 0x2000 scroll notification from the list widget):
 *     forwarded to Widget_OnCommandDefault for in-list focus navigation.
 * This is the glue that turns list scrolling/paging into paged server
 * requests; see docs/screens/02_server_select.md.
 *
 * Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Removing unreachable block (ram,0x0050db4d) */
/* WARNING: Removing unreachable block (ram,0x0050db57) */
/* WARNING: Removing unreachable block (ram,0x0050d9fa) */
/* WARNING: Removing unreachable block (ram,0x0050da04) */
/* WARNING: Removing unreachable block (ram,0x0050d9b9) */
/* WARNING: Removing unreachable block (ram,0x0050d9c3) */
/* WARNING: Removing unreachable block (ram,0x0050d9d1) */
/* WARNING: Removing unreachable block (ram,0x0050d9db) */
/* WARNING: Removing unreachable block (ram,0x0050d8e7) */
/* WARNING: Removing unreachable block (ram,0x0050d8f1) */
/* WARNING: Removing unreachable block (ram,0x0050d889) */
/* WARNING: Removing unreachable block (ram,0x0050d893) */
/* WARNING: Removing unreachable block (ram,0x0050d8a1) */
/* WARNING: Removing unreachable block (ram,0x0050d8ab) */
/* WARNING: Removing unreachable block (ram,0x0050db35) */
/* WARNING: Removing unreachable block (ram,0x0050db3f) */
/* WARNING: Removing unreachable block (ram,0x0050db76) */
/* WARNING: Removing unreachable block (ram,0x0050db80) */

void __thiscall WorldListPanel_OnCommand(int param_1,int param_2,int param_3,undefined4 param_4)

{
  undefined *puVar1;
  int iVar2;
  uint uVar3;
  int *piVar4;
  int iVar5;
  undefined4 *puVar6;
  bool bVar7;
  
  iVar2 = DAT_007934f0;
  puVar1 = g_gameStateVTableArray[2];
  if (param_2 != 0) goto LAB_0050dc19;
  if (param_3 == 0) {
    *(undefined4 *)(g_gameStateVTableArray[2] + 0x14) = 0;
    puVar1[0x10] = 0;
    puVar6 = (undefined4 *)(puVar1 + 0x28);
    for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar6 = 0;
      puVar6 = puVar6 + 1;
    }
    *(undefined4 *)(iVar2 + 0x44d0) = 6;
    *(undefined2 *)(iVar2 + 0x4d4) = 0x1100;
    *(undefined1 *)(iVar2 + 0x4d6) = 0;
    iVar5 = *(int *)(iVar2 + 0x44d0);
    *(int *)(iVar2 + 0x44d0) = iVar5 + 1;
    *(undefined1 *)(iVar5 + 0x4d1 + iVar2) = 0;
    *(int *)(iVar2 + 0x44d0) = *(int *)(iVar2 + 0x44d0) + 1;
    *(undefined4 *)(puVar1 + 0x14) = 0;
    *(undefined4 *)(puVar1 + 0x18) = 0;
    *(undefined2 *)(*(int *)(iVar2 + 0x44d0) + 0x4d0 + iVar2) = 0;
    *(int *)(iVar2 + 0x44d0) = *(int *)(iVar2 + 0x44d0) + 2;
    FUN_004d2680();
    *(undefined4 *)(puVar1 + 8) = 0xffffffff;
    DAT_0056d118 = 0;
    if ((*(int *)(*(int *)(DAT_00e9be94 + 0x1c) + 4) == 0) &&
       (piVar4 = *(int **)(*(int *)(DAT_00e9be94 + 0x1c) + 0x10), piVar4[2] == 0)) {
      (**(code **)(*piVar4 + 4))(s_disable_00551e68);
    }
    if (*(int *)(*(int *)(DAT_00e9be94 + 0x1c) + 4) == 0) {
      piVar4 = *(int **)(*(int *)(DAT_00e9be94 + 0x1c) + 0x10);
      uVar3 = piVar4[2];
      while (uVar3 < 2) {
        if (uVar3 == 1) {
          (**(code **)(*piVar4 + 4))(s_disable_00551e68);
          break;
        }
        piVar4 = (int *)piVar4[4];
        uVar3 = piVar4[2];
      }
    }
    FUN_00406300(0);
    uVar3 = Widget_FindChildIndex();
    if (uVar3 != 0xffffffff) {
      if (*(uint *)(param_1 + 0x10) <= uVar3) {
                    /* WARNING: Subroutine does not return */
        ThrowCxxException(0x80070057);
      }
      *(undefined1 *)(*(int *)(*(int *)(param_1 + 0xc) + uVar3 * 4) + 0x3a) = 1;
    }
    uVar3 = Widget_FindChildIndex();
    if (uVar3 != 0xffffffff) {
      if (*(uint *)(param_1 + 0x10) <= uVar3) {
                    /* WARNING: Subroutine does not return */
        ThrowCxxException(0x80070057);
      }
      *(undefined1 *)(*(int *)(*(int *)(param_1 + 0xc) + uVar3 * 4) + 0x3a) = 0;
    }
    goto LAB_0050dc19;
  }
  if (param_3 != 1) goto LAB_0050dc19;
  g_gameStateVTableArray[2][0x10] = 2;
  *(undefined4 *)(puVar1 + 0x14) = 0;
  FUN_00402060();
  *(undefined4 *)(puVar1 + 8) = 0xffffffff;
  iVar2 = DAT_007934f0;
  if (DAT_00e54a9c == 0) {
    *(undefined1 *)(g_clientContext + 0x3f808) = 0;
    puVar1[0x1c] = 0;
    DAT_0056d118 = 0xffffffff;
    if (((*(int *)(*(int *)(DAT_00e9be94 + 0x1c) + 4) == 0) &&
        (piVar4 = *(int **)(*(int *)(DAT_00e9be94 + 0x1c) + 0x10), piVar4[2] == 0)) &&
       ((piVar4[9] == 3 || (piVar4[9] == -1)))) {
      if ((char)piVar4[0x13] == '\x01') {
        (**(code **)(*piVar4 + 4))(s_active_00551e58);
      }
      else {
        (**(code **)(*piVar4 + 4))(s_ready_00551e80);
      }
    }
    if (*(int *)(*(int *)(DAT_00e9be94 + 0x1c) + 4) == 0) {
      piVar4 = *(int **)(*(int *)(DAT_00e9be94 + 0x1c) + 0x10);
      uVar3 = piVar4[2];
      if (uVar3 < 2) {
        do {
          if (uVar3 == 1) {
            if ((piVar4[9] != 3) && (piVar4[9] != -1)) goto LAB_0050d953;
            if ((char)piVar4[0x13] != '\x01') {
              (**(code **)(*piVar4 + 4))(s_ready_00551e80);
              goto LAB_0050d953;
            }
            (**(code **)(*piVar4 + 4))(s_active_00551e58);
            bVar7 = *(int *)(puVar1 + 8) != -1;
            goto LAB_0050da2d;
          }
          piVar4 = (int *)piVar4[4];
          uVar3 = piVar4[2];
        } while (uVar3 < 2);
        bVar7 = *(int *)(puVar1 + 8) != -1;
        goto LAB_0050da2d;
      }
    }
LAB_0050d953:
    bVar7 = *(int *)(puVar1 + 8) != -1;
  }
  else {
    *(undefined2 *)(DAT_007934f0 + 0x4d4) = 0x1101;
    *(undefined4 *)(iVar2 + 0x44d0) = 6;
    *(undefined4 *)(puVar1 + 0x14) = 0;
    *(undefined4 *)(puVar1 + 0x18) = 0;
    FUN_004d2530(&DAT_00e54aa0);
    FUN_004d2680();
    DAT_0056d118 = 0;
    if ((*(int *)(*(int *)(DAT_00e9be94 + 0x1c) + 4) == 0) &&
       (piVar4 = *(int **)(*(int *)(DAT_00e9be94 + 0x1c) + 0x10), piVar4[2] == 0)) {
      (**(code **)(*piVar4 + 4))(s_disable_00551e68);
    }
    if (*(int *)(*(int *)(DAT_00e9be94 + 0x1c) + 4) == 0) {
      piVar4 = *(int **)(*(int *)(DAT_00e9be94 + 0x1c) + 0x10);
      uVar3 = piVar4[2];
      while (uVar3 < 2) {
        if (uVar3 == 1) {
          (**(code **)(*piVar4 + 4))(s_disable_00551e68);
          break;
        }
        piVar4 = (int *)piVar4[4];
        uVar3 = piVar4[2];
      }
    }
    bVar7 = false;
  }
LAB_0050da2d:
  FUN_00406300(bVar7);
  uVar3 = Widget_FindChildIndex();
  if (uVar3 != 0xffffffff) {
    if (*(uint *)(param_1 + 0x10) <= uVar3) {
                    /* WARNING: Subroutine does not return */
      ThrowCxxException(0x80070057);
    }
    *(undefined1 *)(*(int *)(*(int *)(param_1 + 0xc) + uVar3 * 4) + 0x3a) = 0;
  }
  uVar3 = Widget_FindChildIndex();
  if (uVar3 != 0xffffffff) {
    if (*(uint *)(param_1 + 0x10) <= uVar3) {
                    /* WARNING: Subroutine does not return */
      ThrowCxxException(0x80070057);
    }
    *(undefined1 *)(*(int *)(*(int *)(param_1 + 0xc) + uVar3 * 4) + 0x3a) = 1;
  }
LAB_0050dc19:
  Widget_OnCommandDefault(param_2,param_3,param_4);
  return;
}

