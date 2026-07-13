/* FUN_00464060 - 0x00464060 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00464060(void)

{
  byte bVar1;
  char cVar2;
  undefined1 uVar3;
  int iVar4;
  byte bVar5;
  int iVar6;
  int unaff_EDI;
  
  cVar2 = PeekPacketChecksumBool();
  if (((cVar2 == '\0') && (cVar2 = PeekPacketChecksumBool(), cVar2 != '\0')) &&
     (*(int *)(unaff_EDI + 0x24) != 0xe)) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = _rand();
    *(byte *)(unaff_EDI + 0x8bc0) = (byte)iVar4;
    iVar4 = _rand();
    bVar1 = *(byte *)(unaff_EDI + 0x8bc0);
    *(byte *)(unaff_EDI + 0x8bc1) = (byte)iVar4;
    bVar5 = '\x01' << (bVar1 & 7);
    bVar5 = ~bVar5 & (byte)iVar4 | bVar5;
    *(byte *)(unaff_EDI + 0x8bc1) = bVar5;
    *(byte *)(unaff_EDI + 0x8bc2) = bVar5 + bVar1 + -0x34;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = DAT_007934e8;
    *(undefined4 *)(DAT_007934e8 + 0x44d0) = 6;
    *(undefined2 *)(iVar6 + 0x4d4) = 0x4100;
    *(uint *)(iVar6 + 0x4d6) = *(uint *)(unaff_EDI + 0xb0b0) | 0x10;
    iVar4 = *(int *)(iVar6 + 0x44d0) + 4;
    *(int *)(iVar6 + 0x44d0) = iVar4;
    cVar2 = *(char *)(unaff_EDI + 0xb0ac);
    if ((cVar2 == -1) && (*(int *)(unaff_EDI + 0xb0b0) != 4)) {
      cVar2 = PeekChecksumStateUnderLock(g_clientContext + 0x62630);
      iVar4 = *(int *)(DAT_007934e8 + 0x44d0);
      iVar6 = DAT_007934e8;
    }
    *(char *)(iVar4 + 0x4d0 + iVar6) = cVar2;
    *(int *)(iVar6 + 0x44d0) = *(int *)(iVar6 + 0x44d0) + 1;
    SendOutgoingPacket(iVar6);
    QueueBroadcastEvent(0xc304);
    *(uint *)(&g_abBroadcastEventBuffer + g_dwBroadcastEventCursor) = *(uint *)(unaff_EDI + 0xb0b0) | 0x10;
    iVar4 = g_dwBroadcastEventCursor;
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 4;
    if ((*(char *)(unaff_EDI + 0xb0ac) == -1) && (*(int *)(unaff_EDI + 0xb0b0) != 4)) {
      uVar3 = PeekChecksumStateUnderLock(g_clientContext + 0x62630);
      (&g_abBroadcastEventBuffer)[g_dwBroadcastEventCursor] = uVar3;
    }
    else {
      (&DAT_00e9aad0)[iVar4] = *(char *)(unaff_EDI + 0xb0ac);
    }
    g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
    BroadcastQueuedEvent();
    return;
  }
  return;
}

