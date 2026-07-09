/* BuildLobbyChatPanel - 0x00509af0 in the original binary.
 *
 * Builds the lobby chat panel. A 0x94-byte CPanel (vtable PTR_LAB_00557cd4),
 * 0x225 x 0x103 = 549x259. Children:
 *   CreateTextEntryWidget(0, 0x1a, 0xeb, 0x1e4, 0xc, 0x50) -> the chat INPUT
 *       line: a Win32-EDIT-backed field at (26,235), 484x12, max length 80.
 *   a small 0x40-byte label/icon widget (vtable 0x557da0, 22x22).
 *   CreateScrollListWidget(mgr, 0x20e, 0x3f, 0x12, 0x9a, 0xd) -> scrollbar at
 *       (526,63), 18x154, page size 13.
 * The chat history rows are drawn by the panel itself, not as child widgets.
 * See docs/widgets.md panel catalog.
 *
 * Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 * BuildLobbyChatPanel(int param_1)

{
  uint uVar1;
  int *piVar2;
  undefined4 uVar3;
  char cVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  int iVar8;
  undefined4 *puVar9;
  int *piVar10;
  int unaff_retaddr;
  int iVar11;
  undefined4 uStack_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  /* Windows SEH __try/__except frame setup stripped - handler body
   * (LAB_0053795b) wasn't included in this function's own decompile.
   * Same rationale as entry/InitGame.c - see src/README.md. */
  puVar5 = operator_new(0x94);
  local_4 = 0;
  if (puVar5 == (undefined4 *)0x0) {
    puVar9 = (undefined4 *)0x0;
  }
  else {
    Panel_BaseConstructor(puVar5);
    *puVar5 = &PTR_LAB_00557cd4;
    *(undefined1 *)(puVar5 + 0xe) = 1;
    *(undefined1 *)((int)puVar5 + 5) = 0;
    puVar5[0x24] = 0xffffffff;
    puVar9 = puVar5;
  }
  local_4 = 0xffffffff;
  puVar9[9] = 0x2329;
  puVar9[0x13] = 0;
  puVar9[0x11] = 0x2711;
  puVar9[0x12] = 0;
  puVar9[10] = 0x17;
  puVar9[0xb] = 0x11f;
  puVar9[0xc] = 0x225;
  puVar9[0xd] = 0x103;
  puVar6 = (undefined4 *)CreateTextEntryWidget(0,0x1a,0xeb,0x1e4,0xc,0x50);
  Widget_AddChild(puVar6);
  PanelManager_ClearAllFocus(param_1);
  (**(code **)*puVar6)(1);
  iVar8 = 0;
  iVar11 = 0x108;
  do {
    puVar7 = operator_new(0x40);
    puVar6 = (undefined4 *)0x0;
    if (puVar7 != (undefined4 *)0x0) {
      puVar7[3] = 0;
      puVar7[4] = 0;
      puVar7[5] = 0;
      puVar7[6] = 0;
      puVar7[2] = 0;
      *(undefined1 *)(puVar7 + 1) = 0;
      *(undefined1 *)(puVar7 + 7) = 1;
      *(undefined1 *)((int)puVar7 + 0x1d) = 0;
      *(undefined1 *)((int)puVar7 + 0x1e) = 0;
      puVar7[8] = 1;
      *(undefined1 *)(puVar7 + 0xe) = 0;
      *(undefined1 *)((int)puVar7 + 0x39) = 0;
      *(undefined1 *)((int)puVar7 + 0x3a) = 0;
      *puVar7 = &PTR_LAB_00557da0;
      puVar6 = puVar7;
    }
    puVar6[0xf] = iVar8 + 0x4b0;
    puVar6[9] = iVar8;
    puVar6[10] = iVar11;
    puVar6[0xb] = 9;
    puVar6[0xc] = 0x16;
    puVar6[0xd] = 0x16;
    *(bool *)((int)puVar6 + 0x3a) = iVar8 == param_1;
    uVar1 = puVar9[4];
    if (((uint)puVar9[5] <= uVar1) && (cVar4 = AtlArray_GrowBuffer(), cVar4 == '\0')) goto LAB_00509cbe;
    puVar7 = (undefined4 *)(puVar9[3] + uVar1 * 4);
    if (puVar7 != (undefined4 *)0x0) {
      *puVar7 = puVar6;
    }
    puVar9[4] = puVar9[4] + 1;
    Widget_MoveBy(puVar9[10],puVar9[0xb]);
    iVar11 = iVar11 + 0x20;
    puVar6[2] = puVar9;
    iVar8 = iVar8 + 1;
  } while (iVar11 < 0x208);
  iVar11 = CreateScrollListWidget(unaff_retaddr,0x20e,0x3f,0x12,0x9a,0xd);
  uVar1 = puVar9[4];
  if ((uVar1 < (uint)puVar9[5]) || (cVar4 = AtlArray_GrowBuffer(), cVar4 != '\0')) {
    piVar10 = (int *)(puVar9[3] + uVar1 * 4);
    if (piVar10 != (int *)0x0) {
      *piVar10 = iVar11;
    }
    puVar9[4] = puVar9[4] + 1;
    Widget_MoveBy(puVar9[10],puVar9[0xb]);
    *(undefined4 **)(iVar11 + 8) = puVar9;
    piVar10 = (int *)(unaff_retaddr + 4);
    if (*(char *)((int)puVar9 + 5) == '\0') {
      uVar3 = *(undefined4 *)(unaff_retaddr + 8);
      FUN_0050f390();
      puVar6 = *(undefined4 **)(unaff_retaddr + 0x14);
      if (puVar6 != (undefined4 *)0x0) {
        puVar6[2] = puVar9;
      }
      *(undefined4 *)(unaff_retaddr + 0x14) = *puVar6;
      puVar6[1] = uVar3;
      *puVar6 = 0;
      *(int *)(unaff_retaddr + 0xc) = *(int *)(unaff_retaddr + 0xc) + 1;
      if (*(undefined4 **)(unaff_retaddr + 8) == (undefined4 *)0x0) {
        *piVar10 = (int)puVar6;
      }
      else {
        **(undefined4 **)(unaff_retaddr + 8) = puVar6;
      }
      *(undefined4 **)(unaff_retaddr + 8) = puVar6;
    }
    else {
      iVar11 = *piVar10;
      FUN_0050f390();
      piVar2 = *(int **)(unaff_retaddr + 0x14);
      if (piVar2 != (int *)0x0) {
        piVar2[2] = (int)puVar9;
      }
      *(int *)(unaff_retaddr + 0x14) = *piVar2;
      *piVar2 = iVar11;
      piVar2[1] = 0;
      *(int *)(unaff_retaddr + 0xc) = *(int *)(unaff_retaddr + 0xc) + 1;
      if (*piVar10 == 0) {
        *(int **)(unaff_retaddr + 8) = piVar2;
        *piVar10 = (int)piVar2;
      }
      else {
        *(int **)(*piVar10 + 4) = piVar2;
        *piVar10 = (int)piVar2;
      }
    }
    return puVar9;
  }
LAB_00509cbe:
                    /* WARNING: Subroutine does not return */
  FUN_004010c0(0x8007000e);
}

