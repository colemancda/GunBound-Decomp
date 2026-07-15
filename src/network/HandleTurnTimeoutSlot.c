/* HandleTurnTimeoutSlot - 0x004cc1e0 in the original binary.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output - not hand-
 * verified against documented behavior beyond what's already in
 * ARCHITECTURE.md/PROTOCOL.md/FILEFORMATS.md. Calls to unnamed
 * FUN_<address> helpers and DAT_<address>/_DAT_<address> globals are
 * left as-is (undeclared) - this file won't link standalone yet. See
 * src/README.md's "Raw/verbatim ports" section for status and how
 * these get promoted to verified.
 */
#include "ghidra_types.h"
#include <windows.h>


void HandleTurnTimeoutSlot(int param_1)

{
  byte *pbVar1;
  byte bVar2;
  undefined2 uVar3;
  char cVar4;
  int in_EAX;
  int *piVar5;
  uint uVar6;
  undefined4 uVar7;
  int iVar8;
  byte bVar9;
  uint unaff_EBX;
  code *pcVar10;
  uint unaff_retaddr;
  undefined4 uVar11;
  char *pcVar12;
  undefined4 uVar13;
  
  piVar5 = (int *)GetPlayerRecordBySlot(g_clientContext);
  if (piVar5 != (int *)0x0) {
    (**(code **)(*piVar5 + 4))(&DAT_00556770);
    bVar2 = *(byte *)(in_EAX + 2);
    *(ushort *)(piVar5 + 0x2fef) = -(ushort)(*(char *)(in_EAX + 1) == -1) & 0xff00 | (ushort)bVar2;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar6 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (param_1 != uVar6) {
      uVar3 = *(undefined2 *)(in_EAX + 3);
      /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at
       * 0x4cc290 (`lea edi,[ebx+0x15e4]` at 0x4cc283, ebx = piVar5 per
       * `mov ebx,eax` right after the GetPlayerRecordBySlot call above)
       * the cell is (int)piVar5+0x15e4. `piVar5` is `int *` (scales by
       * 4), so the byte offset is taken via `(int)piVar5 + N`, matching
       * this file's own existing idiom (see the +0x8bba/+0x8bbb pokes
       * below). See tools/encodeoutgoingpacketfield_sites.json. */
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeOutgoingPacketField((int)piVar5 + 0x15e4, uVar3);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at
       * 0x4cc2b5 (`lea edi,[ebx+0x90c]` at 0x4cc2af) the cell is
       * (int)piVar5+0x90c. See
       * tools/encodeoutgoingpacketfield_sites.json. */
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar7 = PeekPacketChecksumState();
      EncodeOutgoingPacketField((int)piVar5 + 0x90c, uVar7);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      unaff_EBX = (uint)*(ushort *)(in_EAX + 5);
      /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at
       * 0x4cc2e2 (`lea edi,[ebx+0x1808]` at 0x4cc2d5) the cell is
       * (int)piVar5+0x1808. See
       * tools/encodeoutgoingpacketfield_sites.json. */
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeOutgoingPacketField((int)piVar5 + 0x1808, unaff_EBX);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at
       * 0x4cc307 (`lea edi,[ebx+0xb30]` at 0x4cc301) the cell is
       * (int)piVar5+0xb30. See
       * tools/encodeoutgoingpacketfield_sites.json. */
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar7 = PeekPacketChecksumState();
      EncodeOutgoingPacketField((int)piVar5 + 0xb30, uVar7);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    }
    cVar4 = *(char *)(in_EAX + 7);
    /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at
     * 0x4cc338 (`lea edi,[ebx+0x1c54]` at 0x4cc332) the cell is
     * (int)piVar5+0x1c54. See
     * tools/encodeoutgoingpacketfield_sites.json. */
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((int)piVar5 + 0x1c54, cVar4 == '\x01');
    pcVar10 = (code *)LeaveCriticalSection;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar6 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (param_1 == uVar6) {
      pbVar1 = (byte *)((int)piVar5 + 0x8bba);
      cVar4 = PeekPacketChecksumBool();
      if (cVar4 == '\0') {
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar8 = _rand();
        *pbVar1 = (byte)iVar8;
        iVar8 = _rand();
        *(byte *)((int)piVar5 + 0x8bbb) = (byte)iVar8;
        unaff_EBX = *pbVar1 & 7;
        bVar9 = ~('\x01' << (sbyte)unaff_EBX) & (byte)iVar8 | '\0' << (sbyte)unaff_EBX;
        *(byte *)((int)piVar5 + 0x8bbb) = bVar9;
        *(byte *)(piVar5 + 0x22ef) = bVar9 + *pbVar1 + -0x34;
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        CreateButtonWidget(&DAT_00e9be90,0,0x12,0x3fa,s_b_play_weapon3_00554144,0x58,0x232,0x25,0x26
                           ,0,0);
        InvokeWidget(18,0);
      }
      else {
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar8 = _rand();
        *pbVar1 = (byte)iVar8;
        iVar8 = _rand();
        *(byte *)((int)piVar5 + 0x8bbb) = (byte)iVar8;
        unaff_EBX = *pbVar1 & 7;
        bVar9 = ~('\x01' << (sbyte)unaff_EBX) & (byte)iVar8 | '\0' << (sbyte)unaff_EBX;
        *(byte *)((int)piVar5 + 0x8bbb) = bVar9;
        *(byte *)(piVar5 + 0x22ef) = bVar9 + *pbVar1 + -0x34;
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        CreateButtonWidget(&DAT_00e9be90,0,0x12,0x3fa,s_b_play_weapon3_00554144,0x58,0x232,0x25,0x26
                           ,0,0);
        InvokeWidget(18,0);
        cVar4 = PeekPacketChecksumBool();
        if (cVar4 == '\x01') {
          InvokeWidget(1,1);
          RemoveWidget();
          uVar13 = 6;
          pcVar12 = s_b_play_weapon1_00554164;
          uVar11 = 0x3e9;
          uVar7 = 1;
        }
        else {
          InvokeWidget(2,1);
          RemoveWidget();
          uVar13 = 0x2e;
          pcVar12 = s_b_play_weapon2_00554154;
          uVar11 = 0x3ea;
          uVar7 = 2;
        }
        CreateButtonWidget(&DAT_00e9be90,0,uVar7,uVar11,pcVar12,uVar13,0x232,0x25,0x26,1,0);
        pcVar10 = (code *)LeaveCriticalSection;
      }
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar6 = PeekPacketChecksumState();
    (*pcVar10)(&DAT_005a9068);
    if ((unaff_retaddr & 0xff) != uVar6) {
      FUN_004cc5c0(unaff_retaddr,bVar2,unaff_EBX);
    }
  }
  return;
}

