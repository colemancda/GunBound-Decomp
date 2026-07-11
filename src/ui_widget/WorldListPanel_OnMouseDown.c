/* WorldListPanel_OnMouseDown - 0x0050d5a0 in the original binary.
 *
 * Mouse-down handler for the WORLD LIST panel. If the click is inside the
 * panel rect and input is enabled (state+6==1), it maps the click to a server
 * row via WorldListRowHitTest and writes the result into the ServerSelect
 * state as the highlighted slot: g_gameStateVTableArray[2]+8 = <row> (or -1
 * for a miss), sets the "valid selection" flag (+0x24 = row!=-1), refreshes the
 * connect-button label/enabled state (InvokeWidget(+8 != -1)). This is the
 * row-click -> selection wiring; connecting then happens when the SERVER button
 * is pressed (FUN_004e1170 -> FUN_004e1bf0 on the selected slot).
 *
 * Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Removing unreachable block (ram,0x0050d634) */
/* WARNING: Removing unreachable block (ram,0x0050d63e) */
/* WARNING: Removing unreachable block (ram,0x0050d692) */
/* WARNING: Removing unreachable block (ram,0x0050d69c) */
/* WARNING: Removing unreachable block (ram,0x0050d64c) */
/* WARNING: Removing unreachable block (ram,0x0050d656) */

undefined1 __thiscall WorldListPanel_OnMouseDown(int param_1,int param_2,int param_3)

{
  int *piVar1;
  uint uVar2;
  undefined *puVar3;
  undefined1 uVar4;
  int iVar5;
  
  uVar4 = FUN_00505430(param_2,param_3);
  if ((((*(char *)(param_1 + 0x1e) != '\0') || (param_2 <= *(int *)(param_1 + 0x28))) ||
      (*(int *)(param_1 + 0x30) + *(int *)(param_1 + 0x28) <= param_2)) ||
     ((param_3 <= *(int *)(param_1 + 0x2c) ||
      (*(int *)(param_1 + 0x34) + *(int *)(param_1 + 0x2c) <= param_3)))) {
    return uVar4;
  }
  iVar5 = WorldListRowHitTest(param_3);
  puVar3 = g_gameStateVTableArray[2];
  if (g_gameStateVTableArray[2][6] == '\x01') {
    *(int *)(g_gameStateVTableArray[2] + 8) = iVar5;
    puVar3[0x24] = iVar5 != -1;
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
    InvokeWidget(*(int *)(puVar3 + 8) != -1);
  }
  return uVar4;
}

