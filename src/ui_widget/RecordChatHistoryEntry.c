/* RecordChatHistoryEntry - 0x00423050 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED (2026-10-26), MODERATE-HIGH (one caller, so not promoted to
 * HIGH). Sole caller ParseChatSlashCommand.c, called unconditionally on
 * every submitted chat line before any slash-command parsing. Operates
 * on a per-instance ring of ten 0x80-byte entries (DAT_005f325c +
 * param_1, counted/cursor-tracked by DAT_005f375c/DAT_005f3760 at the
 * same offset) that FUN_00415d40's init zeroes to the same 10*0x80
 * extent: walks the existing entries doing a byte-pair dedup against
 * param_2, returns on a match, otherwise shifts the ring down one slot
 * (dropping the oldest once full at 10) and appends param_2 as the
 * newest entry. Classic recall-history-ring shape: record the just-sent
 * line, deduped against recent history.
 */
#include "ghidra_types.h"


void RecordChatHistoryEntry(int param_1,byte *param_2)

{
  byte bVar1;
  char cVar2;
  byte *pbVar3;
  int iVar4;
  char *pcVar5;
  int iVar6;
  byte *pbVar7;
  char *pcVar8;
  byte *pbVar9;
  bool bVar10;
  
  iVar6 = 0;
  *(int *)(&DAT_005f3760 + param_1) = *(int *)(&DAT_005f375c + param_1);
  if (0 < *(int *)(&DAT_005f375c + param_1)) {
    pbVar3 = &DAT_005f325c + param_1;
    pbVar7 = param_2;
    pbVar9 = pbVar3;
LAB_00423076:
    do {
      bVar1 = *pbVar3;
      bVar10 = bVar1 < *pbVar7;
      if (bVar1 == *pbVar7) {
        if (bVar1 != 0) {
          bVar1 = pbVar3[1];
          bVar10 = bVar1 < pbVar7[1];
          if (bVar1 != pbVar7[1]) goto LAB_0042309a;
          pbVar3 = pbVar3 + 2;
          pbVar7 = pbVar7 + 2;
          if (bVar1 != 0) goto LAB_00423076;
        }
        iVar4 = 0;
      }
      else {
LAB_0042309a:
        iVar4 = (1 - (uint)bVar10) - (uint)(bVar10 != 0);
      }
      if (iVar4 == 0) {
        return;
      }
      iVar6 = iVar6 + 1;
      pbVar3 = pbVar9 + 0x80;
      pbVar7 = param_2;
      pbVar9 = pbVar3;
    } while (iVar6 < *(int *)(&DAT_005f375c + param_1));
  }
  if (*(int *)(&DAT_005f375c + param_1) == 10) {
    pcVar5 = &DAT_005f32dc + param_1;
    iVar6 = 9;
    pcVar8 = pcVar5;
    do {
      do {
        cVar2 = *pcVar5;
        pcVar5[-0x80] = cVar2;
        pcVar5 = pcVar5 + 1;
      } while (cVar2 != '\0');
      pcVar5 = pcVar8 + 0x80;
      iVar6 = iVar6 + -1;
      pcVar8 = pcVar5;
    } while (iVar6 != 0);
    *(undefined4 *)(&DAT_005f375c + param_1) = 9;
  }
  pbVar3 = &DAT_005f325c + param_1 + *(int *)(&DAT_005f375c + param_1) * 0x80;
  do {
    bVar1 = *param_2;
    param_2 = param_2 + 1;
    *pbVar3 = bVar1;
    pbVar3 = pbVar3 + 1;
  } while (bVar1 != 0);
  iVar6 = *(int *)(&DAT_005f375c + param_1);
  *(int *)(&DAT_005f375c + param_1) = iVar6 + 1;
  *(int *)(&DAT_005f3760 + param_1) = iVar6 + 1;
  return;
}

