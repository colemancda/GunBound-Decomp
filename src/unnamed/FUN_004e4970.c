/* FUN_004e4970 - 0x004e4970 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004e4970(int param_1,int param_2,int param_3,undefined4 param_4,undefined4 param_5,
                 undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  int *piVar1;
  undefined4 *puVar2;
  int in_EAX;
  int iVar3;
  int unaff_EBX;
  int unaff_EDI;
  bool bVar4;
  
  if ((((unaff_EBX < 0) || (*(int *)(&DAT_006a7720 + DAT_005b3484) <= unaff_EBX)) || (unaff_EDI < 0)
      ) || (*(int *)(&DAT_006a7724 + DAT_005b3484) <= unaff_EDI)) {
    *(undefined4 *)(in_EAX + 0x858) = 0xffffffff;
    *(undefined4 *)(in_EAX + 0x854) = 0xffffffff;
  }
  else {
    iVar3 = FUN_0040a4d0((uint)*(byte *)(DAT_005b3484 + 0x475c4) * 0x7d28 + 0x1a1f48 + DAT_005b3484)
    ;
    if (iVar3 == 0) {
      FUN_004e4450(unaff_EBX,unaff_EDI,param_4);
      *(int *)(in_EAX + 0x858) = param_1 / 2 + unaff_EDI;
      *(int *)(in_EAX + 0x854) = unaff_EDI - param_1 / 2;
      FUN_00439600(&DAT_006a7f70 + DAT_005b3484,unaff_EBX,unaff_EDI,param_1,param_7,param_8);
      if (DAT_0079352a != '\0') {
        Replay_AppendEvent(0xf004);
        (&g_replayEventBuffer)[g_replayEventCursor] = 0;
        param_6 = param_4;
        param_3 = param_1;
LAB_004e4ac8:
        piVar1 = (int *)(&DAT_00e9aacd + g_replayEventCursor);
        g_replayEventCursor = g_replayEventCursor + 1;
        *piVar1 = unaff_EBX;
        piVar1 = (int *)(&DAT_00e9aad0 + g_replayEventCursor);
        g_replayEventCursor = g_replayEventCursor + 4;
        *piVar1 = unaff_EDI;
        piVar1 = (int *)(&DAT_00e9aad0 + g_replayEventCursor);
        g_replayEventCursor = g_replayEventCursor + 4;
        *piVar1 = param_3;
        puVar2 = (undefined4 *)(&DAT_00e9aad0 + g_replayEventCursor);
        g_replayEventCursor = g_replayEventCursor + 4;
        *puVar2 = param_6;
        g_replayEventCursor = g_replayEventCursor + 4;
        Replay_FlushEvent();
        return;
      }
    }
    else if (iVar3 == 1) {
      FUN_004e4450(unaff_EBX,unaff_EDI,param_5);
      FUN_00439600(&DAT_006a7f70 + DAT_005b3484,unaff_EBX,unaff_EDI,param_2,param_7,param_8);
      *(int *)(in_EAX + 0x858) = param_2 / 2 + unaff_EDI;
      bVar4 = DAT_0079352a != '\0';
      *(int *)(in_EAX + 0x854) = unaff_EDI - param_2 / 2;
      if (bVar4) {
        Replay_AppendEvent(0xf004);
        (&g_replayEventBuffer)[g_replayEventCursor] = 1;
        param_6 = param_5;
        param_3 = param_2;
        goto LAB_004e4ac8;
      }
    }
    else if (iVar3 == 2) {
      FUN_004e4450(unaff_EBX,unaff_EDI,param_6);
      FUN_00439600(&DAT_006a7f70 + DAT_005b3484,unaff_EBX,unaff_EDI,param_3,param_7,param_8);
      *(int *)(in_EAX + 0x858) = param_3 / 2 + unaff_EDI;
      bVar4 = DAT_0079352a != '\0';
      *(int *)(in_EAX + 0x854) = unaff_EDI - param_3 / 2;
      if (bVar4) {
        Replay_AppendEvent(0xf004);
        (&g_replayEventBuffer)[g_replayEventCursor] = 2;
        goto LAB_004e4ac8;
      }
    }
  }
  return;
}

