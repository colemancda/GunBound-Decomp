/* FUN_004db920 - 0x004db920 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004db920(void)

{
  char cVar1;
  int iVar2;
  int iVar3;
  bool bVar4;
  
  iVar3 = 0;
  do {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar2 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (*(char *)(g_clientContext + 0x458fc + iVar2 * 2) == iVar3) {
LAB_004db999:
      iVar2 = 1;
    }
    else {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar2 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      cVar1 = *(char *)(g_clientContext + 0x458fd + iVar2 * 2);
      if (cVar1 == iVar3) goto LAB_004db999;
      iVar2 = (uint)(uint3)(cVar1 >> 7) << 8;
    }
    FUN_00406380(iVar2);
    iVar3 = iVar3 + 1;
  } while (iVar3 < 0xe);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState();
  if (iVar3 == 2) {
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (*(char *)(g_clientContext + 0x458fc + iVar2 * 2) != -1) {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar3 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      if (*(char *)(g_clientContext + 0x458fd + iVar3 * 2) != -1) {
        bVar4 = false;
        goto LAB_004dba63;
      }
    }
    bVar4 = true;
  }
  else {
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    bVar4 = *(char *)(g_clientContext + 0x458fc + iVar2 * 2) == -1;
  }
LAB_004dba63:
  FUN_00406380(bVar4);
  return;
}

