/* FUN_004ce610 - 0x004ce610 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004ce610(int param_1)

{
  undefined *puVar1;
  byte bVar2;
  int iVar3;
  char cVar4;
  int iVar5;
  undefined4 uVar6;
  undefined4 *puVar7;
  int iVar8;
  byte bVar9;
  
  if (*(int *)(param_1 + 0x98) == 0) {
LAB_004ce86c:
    FUN_0043bda0();
    iVar5 = 0;
    do {
      iVar8 = GetPlayerRecordBySlot(g_clientContext);
      if (iVar8 != 0) {
        FUN_0045ea40();
      }
      iVar5 = iVar5 + 1;
    } while (iVar5 < 8);
    if (*(int *)(g_clientContext + 0x621e0) != 0) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar5 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (((iVar5 < 1) && (cVar4 = PeekPacketChecksumBool(), cVar4 != '\0')) &&
         (cVar4 = PeekPacketChecksumBool(), cVar4 == '\0')) {
        iVar5 = *(int *)(g_clientContext + 0x621e0);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar8 = _rand();
        *(byte *)(iVar5 + 0x8bc0) = (byte)iVar8;
        iVar8 = _rand();
        bVar2 = *(byte *)(iVar5 + 0x8bc0);
        *(byte *)(iVar5 + 0x8bc1) = (byte)iVar8;
        bVar9 = '\x01' << (bVar2 & 7);
        bVar9 = ~bVar9 & (byte)iVar8 | bVar9;
        *(byte *)(iVar5 + 0x8bc1) = bVar9;
        *(byte *)(iVar5 + 0x8bc2) = bVar9 + bVar2 + -0x34;
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar3 = DAT_007934e8;
        iVar8 = g_clientContext;
        *(undefined4 *)(DAT_007934e8 + 0x44d0) = 6;
        *(undefined2 *)(iVar3 + 0x4d4) = 0x4100;
        *(undefined4 *)(iVar3 + 0x4d6) = *(undefined4 *)(*(int *)(iVar8 + 0x621e0) + 0xb0b0);
        iVar5 = *(int *)(iVar3 + 0x44d0);
        *(int *)(iVar3 + 0x44d0) = iVar5 + 4;
        *(undefined1 *)(iVar5 + 0x4d4 + iVar3) = *(undefined1 *)(*(int *)(iVar8 + 0x621e0) + 0xb0ac)
        ;
        *(int *)(iVar3 + 0x44d0) = *(int *)(iVar3 + 0x44d0) + 1;
        SendOutgoingPacket(iVar3);
        QueueBroadcastEvent(0xc304);
        iVar5 = g_clientContext;
        *(undefined4 *)(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) =
             *(undefined4 *)(*(int *)(g_clientContext + 0x621e0) + 0xb0b0);
        puVar1 = &DAT_00e9aad0 + g_dwBroadcastEventCursor;
        g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 4;
        *puVar1 = *(undefined1 *)(*(int *)(iVar5 + 0x621e0) + 0xb0ac);
        g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
        BroadcastQueuedEvent();
      }
    }
    FUN_004cea70(param_1);
    return;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar5 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar5 < *(int *)(param_1 + 0x9c)) goto LAB_004ce86c;
  cVar4 = FUN_0043c820();
  if (cVar4 == '\x01') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at
     * 0x4ce683 (`lea edi,[esi + 0x6240c]` at 0x4ce679; real disasm
     * shows esi == g_clientContext throughout this function, e.g. the
     * `lea edi,[esi+0x6a7f70]` right before matches this file's own
     * `&DAT_006a7f70 + g_clientContext` idiom used a few lines below):
     * cell is g_clientContext+0x6240c, same cell as FUN_004ce3d0.c's
     * fix. See tools/encodeoutgoingpacketfield_sites.json. */
    EncodeOutgoingPacketField(g_clientContext + 0x6240c, 1);
                    /* WARNING: Could not recover jumptable at 0x004ce694. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    return;
  }
  switch(*(undefined4 *)(param_1 + 0x49c)) {
  case 2:
    FUN_0042bb10(*(undefined4 *)(param_1 + 0x69c),0xfffffed4);
    FUN_00434ac0(&DAT_006a7f70 + g_clientContext,*(undefined4 *)(param_1 + 0x29c));
    break;
  case 3:
    FUN_0042bb10(*(undefined4 *)(param_1 + 0x69c),0xfffffed4);
    FUN_004337f0(&DAT_006a7f70 + g_clientContext,*(undefined4 *)(param_1 + 0x29c));
    break;
  case 4:
    FUN_0042bb10(*(undefined4 *)(param_1 + 0x69c),0xfffffed4);
    FUN_00434160(&DAT_006a7f70 + g_clientContext,*(undefined4 *)(param_1 + 0x29c));
    break;
  case 5:
    FUN_0042bb10(*(undefined4 *)(param_1 + 0x69c),0xfffffed4);
    FUN_00434fc0(&DAT_006a7f70 + g_clientContext,*(undefined4 *)(param_1 + 0x29c),0);
    break;
  case 6:
    AddToPacketChecksum(0xb4);
    uVar6 = PeekChecksumStateUnderLock(&DAT_00e9bed8);
    cVar4 = PacketChecksumGreaterThan(g_clientContext + 0x5b1ac,uVar6);
    if (cVar4 != '\0') {
      uVar6 = PeekChecksumStateUnderLock(&DAT_00e9bed8);
      SubFromPacketChecksum(uVar6);
    }
  default:
switchD_004ce6ac_default:
    uVar6 = PeekChecksumStateUnderLock(&DAT_00e9ba40);
    QueueOutgoingPacketField(uVar6);
    break;
  case 7:
    QueueOutgoingPacketField(0);
    goto switchD_004ce6ac_default;
  }
  iVar5 = 0;
  if (*(int *)(param_1 + 0x98) != 1 && -1 < *(int *)(param_1 + 0x98) + -1) {
    puVar7 = (undefined4 *)(param_1 + 0x9c);
    do {
      *puVar7 = puVar7[1];
      puVar7[0x80] = puVar7[0x81];
      puVar7[0x100] = puVar7[0x101];
      puVar7[0x180] = puVar7[0x181];
      iVar5 = iVar5 + 1;
      puVar7 = puVar7 + 1;
    } while (iVar5 < *(int *)(param_1 + 0x98) + -1);
  }
  *(int *)(param_1 + 0x98) = *(int *)(param_1 + 0x98) + -1;
  return;
}

