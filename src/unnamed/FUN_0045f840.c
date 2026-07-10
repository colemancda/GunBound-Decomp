/* FUN_0045f840 - 0x0045f840 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int FUN_0045f840(void)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int unaff_EBX;
  
  if (*(char *)(unaff_EBX + 0x651c) == '\x01') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  else {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  iVar2 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  cVar1 = PeekPacketChecksumBool();
  if (cVar1 != '\0') {
    iVar2 = iVar2 + (iVar2 * 0x14) / 100;
  }
  cVar1 = PeekPacketChecksumBool();
  if (cVar1 != '\0') {
    iVar2 = iVar2 + (iVar2 * 0x14) / 100;
  }
  cVar1 = PeekPacketChecksumBool();
  if (cVar1 != '\0') {
    if (*(char *)(unaff_EBX + 0x651c) == '\x01') {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    }
    else {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    }
    iVar3 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar2 = iVar2 + iVar3;
  }
  return iVar2;
}

