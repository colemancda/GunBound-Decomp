/* FUN_004ce3d0 - 0x004ce3d0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004ce3d0(int param_1)

{
  char cVar1;
  int iVar2;
  int *piVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  
  if (*(int *)(param_1 + 0x89c) != 0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar2 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (*(int *)(param_1 + 0x8a0) <= iVar2) {
      cVar1 = FUN_0043c820();
      if (cVar1 != '\0') {
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at
         * 0x4ce441 (`mov edi,esi` at 0x4ce43f; real disasm at 0x4ce42a
         * shows `esi = g_clientContext (ds:0x5b3484); add esi,0x6240c`
         * just above the mov, i.e. esi is NOT this file's own param_1,
         * it's a fresh cell computed off the global client-context base):
         * cell is g_clientContext+0x6240c, the same expression already
         * used as a cell-pointer arg elsewhere in this codebase (see
         * ApplyBattleActionToContext.c's
         * `PacketChecksumEquals(g_clientContext + 0x6240c, ...)`). See
         * tools/encodeoutgoingpacketfield_sites.json. */
        EncodeOutgoingPacketField(g_clientContext + 0x6240c, 1);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        return;
      }
      piVar3 = (int *)GetPlayerRecordBySlot(g_clientContext);
      if (piVar3 != (int *)0x0) {
        cVar1 = PeekPacketChecksumBool();
        if (cVar1 == '\x01') {
          (**(code **)(*piVar3 + 4))(&DAT_00553bcc);
          SetGuardedBool(1,GB_GUARD_UNRECOVERED);
          QueueOutgoingPacketField(0);
          piVar3[0x2ffb] = 0;
          QueueOutgoingPacketField(0);
          piVar3[0x2b84] = 0;
          uVar4 = QueueOutgoingPacketField(*(undefined4 *)(param_1 + 0xaa0));
          EncodeChecksumState(uVar4);
          uVar4 = QueueOutgoingPacketField(0);
          EncodeChecksumState(uVar4);
          iVar2 = FindSpriteFrame();
          if (iVar2 != 0) {
            *(undefined1 *)(iVar2 + 0x14) = 1;
          }
          PeekChecksumStateUnderLock(piVar3 + 0x68b);
          FUN_0041c360(g_clientContext,piVar3);
          SetGuardedBool(0,GB_GUARD_UNRECOVERED);
          *(undefined1 *)(piVar3 + 0x2b85) = 0;
          SetGuardedBool(0,GB_GUARD_UNRECOVERED);
          QueueOutgoingPacketField(0);
          QueueOutgoingPacketField(0);
          QueueOutgoingPacketField(0);
          piVar3[0x2fee] = *(int *)(param_1 + 0xea0);
        }
        iVar2 = 0;
        if (*(int *)(param_1 + 0x89c) != 1 && -1 < *(int *)(param_1 + 0x89c) + -1) {
          puVar5 = (undefined4 *)(param_1 + 0x8a0);
          do {
            *puVar5 = puVar5[1];
            puVar5[0x80] = puVar5[0x81];
            puVar5[0x100] = puVar5[0x101];
            puVar5[0x180] = puVar5[0x181];
            iVar2 = iVar2 + 1;
            puVar5 = puVar5 + 1;
          } while (iVar2 < *(int *)(param_1 + 0x89c) + -1);
        }
      }
      *(int *)(param_1 + 0x89c) = *(int *)(param_1 + 0x89c) + -1;
      return;
    }
  }
  *(undefined1 *)(param_1 + 0x94) = 0;
  FUN_004cea70(param_1);
  return;
}

