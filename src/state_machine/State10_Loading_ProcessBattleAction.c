/* State10_Loading_ProcessBattleAction - 0x0043e440 in the original binary.
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


void __thiscall State10_Loading_ProcessBattleAction(void *this,int packetBuf)

{
  byte bVar1;
  char cVar2;
  int *piVar3;
  undefined4 uVar4;
  int iVar5;
  char *_Format;
  byte bVar6;
  undefined4 *puVar7;
  byte *pbVar8;
  undefined4 *puVar9;
  undefined4 *unaff_FS_OFFSET;
  int iVar10;
  int iVar11;
  char acStack_4d4 [128];
  undefined1 auStack_454 [548];
  undefined1 auStack_230 [548];
  undefined4 uStack_c;
  undefined1 *puStack_8;
  int iStack_4;
  
  uStack_c = *unaff_FS_OFFSET;
  iStack_4 = 0xffffffff;
  puStack_8 = &LAB_00540806;
  *unaff_FS_OFFSET = &uStack_c;
  iVar5 = g_clientContext;
  bVar1 = *(byte *)(packetBuf + 5);
  if (bVar1 < 8) {
    if (*(short *)(packetBuf + 2) == 3) {
      iVar5 = (uint)*(byte *)(packetBuf + 0x21) * 0xd + 0x457f1 + g_clientContext;
      iVar10 = (uint)bVar1 * 0xd + 0x457f1 + g_clientContext;
      iVar11 = iVar5;
      _Format = (char *)GetLocalizedString(&g_localizedStringTable,0x260);
      _sprintf(acStack_4d4,_Format,iVar10,iVar5,iVar11);
      (**(code **)(*(int *)this + 0x28))(acStack_4d4,2,6);
    }
    else if (*(short *)(packetBuf + 2) == -0x3cff) {
      *(uint *)(g_gameStateVTableArray[0xb] + 0x10a4) = (uint)*(ushort *)(packetBuf + 0x22);
      piVar3 = (int *)GetPlayerRecordBySlot(iVar5);
      if (piVar3 != (int *)0x0) {
        if ((piVar3[9] != 0xe) && (cVar2 = PeekPacketChecksumBool(), cVar2 == '\x01')) {
          uVar4 = FUN_0040aba0(piVar3 + 0x19d1,auStack_230,piVar3 + 0x1b6c);
          iStack_4 = 0;
          uVar4 = FUN_0040a8c0(uVar4,auStack_454,3);
          iStack_4 = 1;
          cVar2 = FUN_0040b490(piVar3 + 0x1a5a,uVar4);
          iStack_4 = 0;
          FUN_0040a2a0();
          iStack_4 = 0xffffffff;
          FUN_0040a2a0();
          if (cVar2 == '\0') {
            (**(code **)(*piVar3 + 4))(s_normal_00552230);
          }
          else {
            (**(code **)(*piVar3 + 4))(s_wnormal_00553618);
          }
        }
        if (piVar3[0x2c29] != -1) {
          FUN_004eeae0();
          piVar3[0x2c29] = -1;
        }
        FUN_00406500(0);
        FUN_00406500(0);
      }
      iVar5 = FUN_0040a4d0((uint)bVar1 * 0x224 + 0xebef4 + g_clientContext);
      if (((iVar5 != -1) && (iVar5 = *(int *)(g_gameStateVTableArray[0xb] + 0x10a4), iVar5 != 60000)
          ) && (iVar5 != 0xffff)) {
        AddToPacketChecksum(iVar5);
      }
      puVar7 = (undefined4 *)(packetBuf + 0x24);
      puVar9 = (undefined4 *)(g_gameStateVTableArray[0xb] + 0x2302);
      for (iVar5 = 8; iVar10 = g_clientContext, iVar5 != 0; iVar5 = iVar5 + -1) {
        *puVar9 = *puVar7;
        puVar7 = puVar7 + 1;
        puVar9 = puVar9 + 1;
      }
      pbVar8 = &DAT_006a9b6c + g_clientContext;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar5 = _rand();
      *pbVar8 = (byte)iVar5;
      iVar5 = _rand();
      bVar1 = *pbVar8;
      (&DAT_006a9b6d)[iVar10] = (byte)iVar5;
      bVar6 = '\x01' << (bVar1 & 7);
      bVar6 = ~bVar6 & (byte)iVar5 | bVar6;
      (&DAT_006a9b6d)[iVar10] = bVar6;
      (&DAT_006a9b6e)[iVar10] = bVar6 + bVar1 + -0x34;
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      *(undefined1 *)(*(int *)(g_clientContext + 0x621e0) + 0xae68) = 1;
    }
  }
  *unaff_FS_OFFSET = uStack_c;
  return;
}

