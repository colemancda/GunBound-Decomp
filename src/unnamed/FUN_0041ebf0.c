/* FUN_0041ebf0 - 0x0041ebf0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_0041ebf0(int param_1)

{
  char cVar1;
  byte bVar2;
  short sVar3;
  undefined2 uVar4;
  int iVar5;
  char *in_EAX;
  int iVar6;
  byte bVar7;
  char *pcVar8;
  char *pcVar9;
  byte *pbVar10;
  
  cVar1 = *in_EAX;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField((int)cVar1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  sVar3 = *(short *)(in_EAX + 1);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField((int)sVar3);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  cVar1 = in_EAX[3];
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField((int)cVar1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  cVar1 = in_EAX[4];
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField((int)cVar1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  pcVar8 = in_EAX + 7;
  if (in_EAX[6] != -1) {
    cVar1 = *pcVar8;
    pcVar8 = in_EAX + 10;
    FUN_00435ad0(&DAT_006a7f70 + param_1,*(undefined2 *)(in_EAX + 8),cVar1,10000);
  }
  pcVar9 = pcVar8 + 1;
  if (*pcVar8 != -1) {
    cVar1 = *pcVar9;
    pcVar9 = pcVar8 + 4;
    FUN_00435800(&DAT_006a7f70 + param_1,*(undefined2 *)(pcVar8 + 2),cVar1,10000);
  }
  pcVar8 = pcVar9 + 1;
  if (*pcVar9 != -1) {
    cVar1 = *pcVar8;
    pcVar8 = pcVar9 + 4;
    FUN_00435da0(&DAT_006a7f70 + param_1,*(undefined2 *)(pcVar9 + 2),cVar1,10000);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar6 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar5 = g_clientContext;
  if ((iVar6 == 3) && (*pcVar8 != -1)) {
    pbVar10 = &DAT_006a7f90 + g_clientContext;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = _rand();
    *pbVar10 = (byte)iVar6;
    iVar6 = _rand();
    bVar2 = *pbVar10;
    (&DAT_006a7f91)[iVar5] = (byte)iVar6;
    bVar7 = '\x01' << (bVar2 & 7);
    bVar7 = ~bVar7 & (byte)iVar6 | bVar7;
    bVar2 = *pbVar10;
    (&DAT_006a7f91)[iVar5] = bVar7;
    (&DAT_006a7f92)[iVar5] = bVar7 + bVar2 + -0x34;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    cVar1 = pcVar8[1];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(cVar1);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar4 = *(undefined2 *)(pcVar8 + 2);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(uVar4);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  return;
}

