/* AppendChatLogPanelLine - 0x00505900 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * (FUN_00505ad0.c in the notes below is now
 * src/ui_widget/CChatLogPanel_SubmitWhisper.c.)
 *
 * NAMED (2026-09-21). `param_1` (ECX) is a CChatLogPanel*
 * (src/cxx/Widget.h, sizeof 0x1050, builder BuildChatLogPanel): this
 * writes into `m_history` (+0xa8, the class's own 4000-byte field,
 * matching this function's ~4000-byte staging buffer copied there) and
 * the two per-panel counters `m_unk1048`/`m_unk104c` (+0x1048/+0x104c)
 * used here exactly as a scrolling-history write cursor and a 100-line
 * cap with ring-buffer eviction. `param_2` (EDX) is the sender/label
 * text (DisplayIncomingWhisper.c's own header already identifies its
 * caller as routing "into the sender's CChatLogPanel"); it is
 * formatted as "<label>] " via RenderWrappedText and followed by the
 * message text (param_3/len param_4), then the wrapped line is
 * appended and the panel's child/scroll range updated
 * (Widget_SetChildRange). All 3 callers (DisplayIncomingWhisper.c,
 * FUN_00505ad0.c - a localized-string label via GetLocalizedString,
 * FUN_004024f0.c) reach this only after a successful
 * PanelManager_FindByName lookup for that panel.
 *
 * DROPPED-ARGUMENT FIX (2026-09-21): the declaration below was already
 * correct (4 real params: ECX=param_1, EDX=param_2 - both confirmed
 * still holding their entry-time values at 0x505915/0x505931, `ret 8`
 * at 0x505abf/0x4368a0 confirming 2 real stack dwords beyond the 2
 * registers) - but had no functions.h prototype, so all 3 call sites in
 * the tree silently compiled passing only param_3/param_4 on the stack
 * and dropped param_1/param_2 (the two registers) entirely. Each site's
 * ECX/EDX reconstructed independently from its own disasm - see each
 * call site's own comment (src/unnamed/FUN_00505ad0.c,
 * src/unnamed/DisplayIncomingWhisper.c, src/unnamed/FUN_004024f0.c).
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */
/* WARNING: Type propagation algorithm not settling */

void __fastcall AppendChatLogPanelLine(int param_1,char *param_2,char *param_3,uint param_4)

{
  char cVar1;
  undefined2 *puVar2;
  char *pcVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  undefined4 *puVar8;
  undefined2 *puVar9;
  undefined4 *puVar10;
  undefined1 local_2fa8 [3];
  undefined1 auStack_2fa5 [3996];
  undefined2 uStack_2009;
  char local_2006 [8186];
  undefined4 uStack_c;
  
  uStack_c = 0x505910;
  local_2fa8[0] = 0;
  puVar8 = (undefined4 *)((int)local_2fa8 + 1);
  for (iVar5 = 999; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar8 = 0;
    puVar8 = puVar8 + 1;
  }
  *(undefined2 *)puVar8 = 0;
  *(undefined1 *)((int)puVar8 + 2) = 0;
  pcVar3 = param_2;
  do {
    cVar1 = *pcVar3;
    pcVar3[(int)&uStack_2009 + (1 - (int)param_2)] = cVar1;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  puVar2 = &uStack_2009;
  do {
    puVar9 = puVar2;
    puVar2 = (undefined2 *)((int)puVar9 + 1);
  } while (*(char *)((int)puVar9 + 1) != '\0');
  *(undefined2 *)((int)puVar9 + 1) = DAT_00553624;
  *(undefined1 *)((int)puVar9 + 3) = DAT_00553626;
  pcVar3 = param_2;
  do {
    cVar1 = *pcVar3;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
  uVar6 = ((int)param_4 < 0) - 1 & param_4;
  pcVar3 = pcVar3 + (int)(local_2006 + -(int)(param_2 + 1));
  for (uVar7 = uVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
    *(undefined4 *)pcVar3 = *(undefined4 *)param_3;
    param_3 = param_3 + 4;
    pcVar3 = pcVar3 + 4;
  }
  for (uVar6 = uVar6 & 3; uVar6 != 0; uVar6 = uVar6 - 1) {
    *pcVar3 = *param_3;
    param_3 = param_3 + 1;
    pcVar3 = pcVar3 + 1;
  }
  pcVar3 = param_2 + 1;
  do {
    cVar1 = *param_2;
    param_2 = param_2 + 1;
  } while (cVar1 != '\0');
  param_2[(int)(local_2006 + (param_4 - (int)pcVar3))] = '\0';
  iVar4 = RenderWrappedText(local_2fa8,(int)&uStack_2009 + 1,0x28,0x22,4000,0);
  iVar5 = *(int *)(param_1 + 0x104c) + iVar4;
  if (100 < iVar5) {
    iVar5 = iVar5 + -100;
    uVar7 = (100 - iVar5) * 0x28;
    puVar8 = (undefined4 *)(param_1 + 0xa8 + iVar5 * 0x28);
    puVar10 = (undefined4 *)(param_1 + 0xa8);
    for (uVar7 = (((int)uVar7 < 0) - 1 & uVar7) >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
      *puVar10 = *puVar8;
      puVar8 = puVar8 + 1;
      puVar10 = puVar10 + 1;
    }
    for (iVar5 = 0; iVar5 != 0; iVar5 = iVar5 + -1) {
      *(undefined1 *)puVar10 = *(undefined1 *)puVar8;
      puVar8 = (undefined4 *)((int)puVar8 + 1);
      puVar10 = (undefined4 *)((int)puVar10 + 1);
    }
    *(int *)(param_1 + 0x104c) = 100 - iVar4;
  }
  puVar8 = (undefined4 *)local_2fa8;
  puVar10 = (undefined4 *)(param_1 + 0xa8 + *(int *)(param_1 + 0x104c) * 0x28);
  for (uVar7 = ((iVar4 * 0x28 < 0) - 1 & iVar4 * 0x28) >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
    *puVar10 = *puVar8;
    puVar8 = puVar8 + 1;
    puVar10 = puVar10 + 1;
  }
  for (iVar5 = 0; iVar5 != 0; iVar5 = iVar5 + -1) {
    *(undefined1 *)puVar10 = *(undefined1 *)puVar8;
    puVar8 = (undefined4 *)((int)puVar8 + 1);
    puVar10 = (undefined4 *)((int)puVar10 + 1);
  }
  iVar5 = *(int *)(param_1 + 0x104c) + iVar4;
  *(int *)(param_1 + 0x104c) = iVar5;
  if (*(int *)(param_1 + 0x1048) == (iVar5 - iVar4) + -0xf) {
    *(int *)(param_1 + 0x1048) = *(int *)(param_1 + 0x1048) + iVar4;
  }
  Widget_SetChildRange(iVar5,0xe);
  uVar7 = Widget_FindChildIndex();
  if (uVar7 != 0xffffffff) {
    if (*(uint *)(param_1 + 0x10) <= uVar7) {
                    /* WARNING: Subroutine does not return */
      ThrowCxxException(0x80070057);
    }
    *(undefined4 *)(*(int *)(*(int *)(param_1 + 0xc) + uVar7 * 4) + 0x40) =
         *(undefined4 *)(param_1 + 0x1048);
  }
  return;
}

