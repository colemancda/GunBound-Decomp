/* FUN_004d0a10 - 0x004d0a10 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004d0a10(int *param_1,undefined2 *param_2)

{
  undefined1 uVar1;
  undefined2 uVar2;
  short sVar3;
  uint in_EAX;
  int iVar4;
  int iVar5;
  char *_Format;
  undefined4 uVar6;
  char local_80 [128];
  
  param_1[0x428] = in_EAX & 0xff;
  uVar2 = *param_2;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(uVar2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar4 == 0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    FUN_00438360();
  }
  if (*(char *)(g_clientContext + 0x45127) != '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (iVar4 - iVar5 == 10) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar4 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar5 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar4 = iVar4 - iVar5;
      _Format = (char *)GetLocalizedString(&g_localizedStringTable,0x261);
      _sprintf(local_80,_Format,iVar4);
      (**(code **)(*param_1 + 0x28))(local_80,2,6);
    }
  }
  FUN_0041ebf0(g_clientContext);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar6 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(uVar6);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar5 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iVar4 % iVar5 == 0) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(iVar4 + 3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  iVar4 = *(int *)(g_clientContext + 0x621e0);
  if ((iVar4 != 0) && (*(int *)(iVar4 + 0x24) != 0xd)) {
    *(undefined4 *)(iVar4 + 0xb0b0) = 4;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = PeekPacketChecksumState();
  EncodeOutgoingPacketField(iVar4 + 1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar1 = *(undefined1 *)(param_2 + 1);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(uVar1);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  sVar3 = *(short *)((int)param_2 + 3);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField((int)sVar3);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  param_1[0x42e] = 1;
  FUN_004cf310();
  return;
}

