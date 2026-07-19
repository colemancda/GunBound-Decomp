/* FUN_004cbda0 - 0x004cbda0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004cbda0(undefined4 param_1,int param_2)

{
  ushort *puVar1;
  byte bVar2;
  char cVar3;
  undefined1 uVar4;
  ushort uVar5;
  undefined2 uVar6;
  int iVar7;
  int iVar8;
  byte bVar9;
  
  if ((*(int *)(g_clientContext + 0x621e0) != 0) && (cVar3 = PeekPacketChecksumBool(), cVar3 != '\0')) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar7 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar7 != 0) {
      QueueBroadcastEvent(0xc401);
      (&g_abBroadcastEventBuffer)[g_dwBroadcastEventCursor] = (char)param_2;
      g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
      cVar3 = PacketChecksumEquals(param_2 * 0x224 + 0x39f30 + g_clientContext,0xff);
      if (cVar3 == '\0') {
        (&g_abBroadcastEventBuffer)[g_dwBroadcastEventCursor] = 0;
        iVar7 = g_clientContext;
        g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
        *(undefined2 *)(*(int *)(g_clientContext + 0x621e0) + 0xbfbc) = 0;
      }
      else {
        QueueOutgoingPacketField(0);
        (&g_abBroadcastEventBuffer)[g_dwBroadcastEventCursor] = 0xff;
        iVar7 = g_clientContext;
        param_2 = param_2 + 1;
        g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
        *(undefined2 *)(*(int *)(g_clientContext + 0x621e0) + 0xbfbc) = 0xff00;
      }
      uVar4 = PeekChecksumStateUnderLock(param_2 * 0x224 + 0x39f30 + iVar7);
      (&g_abBroadcastEventBuffer)[g_dwBroadcastEventCursor] = uVar4;
      g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
      iVar7 = *(int *)(g_clientContext + 0x621e0);
      uVar5 = PeekChecksumStateUnderLock(param_2 * 0x224 + 0x39f30 + g_clientContext);
      puVar1 = (ushort *)(iVar7 + 0xbfbc);
      *puVar1 = *puVar1 | uVar5;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at
       * 0x4cbf1f (`mov edi,esi` at 0x4cbf1d; real disasm at 0x4cbf12
       * shows `esi = [old esi(=param_2*0x224) + eax(=g_clientContext) +
       * 0x39f30]`, i.e. esi is recomputed from the SAME expression used
       * one line above as the argument to
       * `PeekChecksumStateUnderLock(param_2 * 0x224 + 0x39f30 +
       * g_clientContext)`): cell is that identical expression. See
       * tools/encodeoutgoingpacketfield_sites.json. */
      EncodeOutgoingPacketField(param_2 * 0x224 + 0x39f30 + g_clientContext, 0);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar6 = PeekChecksumStateUnderLock(*(int *)(g_clientContext + 0x621e0) + 0x90c);
      iVar7 = g_clientContext;
      *(undefined2 *)(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar6;
      g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 2;
      uVar6 = PeekChecksumStateUnderLock(*(int *)(iVar7 + 0x621e0) + 0xb30);
      iVar7 = g_clientContext;
      *(undefined2 *)(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar6;
      g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 2;
      uVar4 = PacketChecksumEquals(*(int *)(iVar7 + 0x621e0) + 0x1c54,1);
      (&g_abBroadcastEventBuffer)[g_dwBroadcastEventCursor] = uVar4;
      g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
      BroadcastQueuedEvent();
      FUN_004cc5c0(*(undefined1 *)(*(int *)(g_clientContext + 0x621e0) + 8),cVar3 != '\0',
                   *(undefined1 *)(*(int *)(g_clientContext + 0x621e0) + 0xbfbc));
      iVar7 = *(int *)(g_clientContext + 0x621e0);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar8 = _rand();
      *(byte *)(iVar7 + 0x8bb4) = (byte)iVar8;
      iVar8 = _rand();
      bVar2 = *(byte *)(iVar7 + 0x8bb4);
      *(byte *)(iVar7 + 0x8bb5) = (byte)iVar8;
      bVar9 = '\x01' << (bVar2 & 7);
      bVar9 = ~bVar9 & (byte)iVar8 | bVar9;
      *(byte *)(iVar7 + 0x8bb5) = bVar9;
      *(byte *)(iVar7 + 0x8bb6) = bVar9 + bVar2 + -0x34;
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      cVar3 = FUN_0041ea30(g_clientContext,*(undefined2 *)(*(int *)(g_clientContext + 0x621e0) + 0xbfbc));
      if (cVar3 != '\0') {
        cVar3 = PeekPacketChecksumBool();
        if (cVar3 == '\0') {
          SetGuardedBool(0,GB_GUARD_UNRECOVERED);
          SetGuardedBool(0,GB_GUARD_UNRECOVERED);
          cVar3 = PeekPacketChecksumBool();
          if (cVar3 == '\0') {
            SetGuardedBool(1,GB_GUARD_UNRECOVERED);
            QueueBroadcastEvent(0xc301);
            (&g_abBroadcastEventBuffer)[g_dwBroadcastEventCursor] = 1;
            g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
            uVar6 = FUN_0045d360(0);
            *(undefined2 *)(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = uVar6;
            g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 2;
            FUN_0041f200(0);
            BroadcastQueuedEvent();
          }
        }
        SetGuardedBool(0,GB_GUARD_UNRECOVERED);
        SetGuardedBool(0,GB_GUARD_UNRECOVERED);
        QueueOutgoingPacketField(0xffffffff);
        QueueOutgoingPacketField(0xffffffff);
        *(undefined1 *)(*(int *)(g_clientContext + 0x621e0) + 0xbfe8) = 0;
      }
    }
  }
  return;
}

