/* FUN_004ce3d0 - 0x004ce3d0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * 2026-09-02: FindSpriteFrame's register args recovered from orig
 * 0x4ce4fb-0x4ce50d - see the site comment.
 *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at the file's one argless PeekPacketChecksumState() call
 * ((void *)(g_clientContext + 0xeba98)), from tools/guard_cell_resolve.py.
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
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVar2 = PeekPacketChecksumState((void *)(g_clientContext + 0xeba98));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    if (*(int *)(param_1 + 0x8a0) <= iVar2) {
      cVar1 = FUN_0043c820();
      if (cVar1 != '\0') {
        EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
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
        LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
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
          /* RECOVERED (2026-09-02), orig 0x4ce4fb-0x4ce50d: EAX =
           * [0x5b3484]+0x6a7f88 = g_clientContext + 0x6a7f88 (the
           * active-object layer registry), EDX = 0x186a7 (class id), ESI =
           * [edi+8] where EDI = piVar3 (the player record: the very next
           * uses of EDI are `lea ecx,[edi+0x1a2c]` @0x4ce51a = the C's
           * PeekChecksumStateUnderLock(piVar3 + 0x68b), 0x68b*4 == 0x1a2c,
           * and `push edi` @0x4ce52c = FUN_0041c360(g_clientContext,
           * piVar3)), so the frame is piVar3[2] - the same +8 slot/0x186a7
           * pairing as FUN_0044fd70.c's FindSpriteFrame.  Cached scan:
           * tools/findspriteframe_sites.json call_addr 0x4ce50d. */
          iVar2 = FindSpriteFrame(g_clientContext + 0x6a7f88,0x186a7,piVar3[2]);
          if (iVar2 != 0) {
            *(undefined1 *)(iVar2 + 0x14) = 1;
          }
          /* FIXED (2026-09-20): dropped __thiscall ECX arg - at orig
           * 0x4ce526-0x4ce530, `mov ecx,eax` sets `this` from THIS Peek's
           * own return value (eax), right after the two stack pushes
           * (edi=piVar3, then edx=g_clientContext). The raw port had
           * discarded the result entirely. See FUN_0041c360.c's header
           * for the argument-order rationale. */
          uVar4 = PeekChecksumStateUnderLock(piVar3 + 0x68b);
          FUN_0041c360(uVar4,g_clientContext,piVar3);
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

