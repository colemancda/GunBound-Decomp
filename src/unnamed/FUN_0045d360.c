/* FUN_0045d360 - 0x0045d360 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int FUN_0045d360(int param_1)

{
  char cVar1;
  int in_EAX;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar5 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar5 = ((400 - iVar3) / iVar4) * iVar5;
  cVar1 = FUN_00406860();
  if (cVar1 != '\0') {
    cVar1 = PeekPacketChecksumBool();
    if (cVar1 == '\0') {
      cVar1 = PeekPacketChecksumBool();
      if (cVar1 == '\0') {
        iVar3 = in_EAX + 0x9230;
      }
      else {
        iVar3 = in_EAX + 0x9454;
      }
      iVar3 = PeekChecksumStateUnderLock(iVar3);
    }
    else {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar3 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    }
    iVar5 = iVar5 + iVar3;
  }
  cVar1 = PeekPacketChecksumBool();
  if (cVar1 == '\x01') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = iVar5 + iVar3;
    if (param_1 != '\0') {
      iVar3 = GetItemQuantityByIcon(g_clientContext,*(undefined2 *)(in_EAX + 0xbfbc));
      iVar5 = iVar5 + iVar3;
      goto LAB_0045d4b9;
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = GetItemQuantityByIcon(g_clientContext,*(undefined2 *)(in_EAX + 0xbfbc));
    if (iVar4 + iVar3 * -3 < 0) {
      iVar3 = 0;
    }
    else {
      iVar4 = PeekChecksumStateUnderLock((*(uint *)(in_EAX + 8) & 7) * 0x1120 + 0x50cf4 + g_clientContext);
      iVar3 = GetItemQuantityByIcon(g_clientContext,*(undefined2 *)(in_EAX + 0xbfbc));
      iVar3 = iVar3 + iVar4 * -3;
    }
  }
  else {
LAB_0045d4b9:
    if (param_1 == '\0') goto LAB_0045d527;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = iVar3 + iVar4 * -3;
  }
  iVar5 = iVar5 + iVar3;
LAB_0045d527:
  *(undefined1 *)(in_EAX + 0xae68) = 1;
  cVar1 = PeekPacketChecksumBool();
  if (cVar1 != '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(iVar5 + iVar2);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  return iVar3 * (iVar5 + iVar2);
}

