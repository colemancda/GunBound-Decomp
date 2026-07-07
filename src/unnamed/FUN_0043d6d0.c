/* FUN_0043d6d0 - 0x0043d6d0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_0043d6d0(void)

{
  undefined2 *puVar1;
  int iVar2;
  int in_EAX;
  uint uVar3;
  int iVar4;
  
  (&g_replayEventBuffer)[g_replayEventCursor] = *(undefined1 *)(in_EAX + 0xc);
  g_replayEventCursor = g_replayEventCursor + 1;
  uVar3 = 0;
  if (*(int *)(in_EAX + 0xc) != 0) {
    iVar4 = 0;
    iVar2 = g_replayEventCursor;
    if (*(int *)(in_EAX + 0xc) == 0) {
LAB_0043d766:
      g_replayEventCursor = iVar2;
                    /* WARNING: Subroutine does not return */
      FUN_004010c0(0x80070057);
    }
    do {
      (&g_replayEventBuffer)[g_replayEventCursor] = *(undefined1 *)(iVar4 + *(int *)(in_EAX + 8));
      iVar2 = g_replayEventCursor + 1;
      if (*(uint *)(in_EAX + 0xc) <= uVar3) goto LAB_0043d766;
      puVar1 = (undefined2 *)(&DAT_00e9aacd + g_replayEventCursor);
      g_replayEventCursor = g_replayEventCursor + 1;
      *puVar1 = *(undefined2 *)(iVar4 + 2 + *(int *)(in_EAX + 8));
      iVar2 = g_replayEventCursor + 2;
      if (*(uint *)(in_EAX + 0xc) <= uVar3) goto LAB_0043d766;
      puVar1 = (undefined2 *)(&DAT_00e9aace + g_replayEventCursor);
      g_replayEventCursor = g_replayEventCursor + 2;
      *puVar1 = *(undefined2 *)(*(int *)(in_EAX + 8) + 4 + iVar4);
      g_replayEventCursor = g_replayEventCursor + 2;
      uVar3 = uVar3 + 1;
      iVar4 = iVar4 + 6;
    } while (uVar3 < *(uint *)(in_EAX + 0xc));
  }
  return;
}

