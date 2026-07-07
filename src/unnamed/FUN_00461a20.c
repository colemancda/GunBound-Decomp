/* FUN_00461a20 - 0x00461a20 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00461a20(int param_1)

{
  undefined *puVar1;
  undefined4 uVar2;
  char cVar3;
  undefined1 uVar4;
  undefined2 uVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  int local_1c;
  undefined4 local_14 [5];
  
  cVar3 = FUN_004065a0();
  if (cVar3 != '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar6 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if ((*(uint *)(param_1 + 8) & 7) == uVar6) {
      iVar8 = 0;
      local_1c = 0;
      do {
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar7 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        if (iVar7 == 0) break;
        local_1c = local_1c + 1;
        iVar8 = iVar8 + 0x224;
      } while (iVar8 < 0xcd8);
      if (local_1c != 6) {
        local_14[0] = 1;
        local_14[1] = 2;
        local_14[2] = 3;
        local_14[3] = 7;
        local_14[4] = 0xf;
        iVar8 = _rand();
        uVar2 = local_14[iVar8 % 5];
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EncodeOutgoingPacketField(uVar2);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        Replay_AppendEvent(0x8406);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar5 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        *(undefined2 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar5;
        g_replayEventCursor = g_replayEventCursor + 2;
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar5 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        *(undefined2 *)(&g_replayEventBuffer + g_replayEventCursor) = uVar5;
        g_replayEventCursor = g_replayEventCursor + 2;
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar8 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        (&g_replayEventBuffer)[g_replayEventCursor] = '\x01' - (iVar8 != 1);
        puVar1 = &DAT_00e9aacd + g_replayEventCursor;
        g_replayEventCursor = g_replayEventCursor + 1;
        *puVar1 = (undefined1)local_1c;
        g_replayEventCursor = g_replayEventCursor + 1;
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar4 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        (&g_replayEventBuffer)[g_replayEventCursor] = uVar4;
        g_replayEventCursor = g_replayEventCursor + 1;
        Replay_FlushEvent();
      }
    }
  }
  return;
}

