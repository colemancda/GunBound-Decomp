/* FUN_0045ec30 - 0x0045ec30 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 FUN_0045ec30(void)

{
  char cVar1;
  int in_EAX;
  int iVar2;
  int iVar3;
  
  cVar1 = FUN_004065a0();
  if (cVar1 == '\0') {
    cVar1 = FUN_004065a0();
    iVar2 = in_EAX + 0x4948;
    if (cVar1 == '\0') {
      cVar1 = FUN_0040b4d0(in_EAX + 0x292c,iVar2);
      if ((cVar1 != '\0') && (cVar1 = FUN_0040b4d0(iVar2,in_EAX + 0x2708), cVar1 != '\0')) {
        return 1;
      }
      cVar1 = FUN_0040b4d0(in_EAX + 0x2d74,iVar2);
      if (cVar1 == '\0') {
        return 0;
      }
      iVar3 = in_EAX + 0x2b50;
    }
    else {
      cVar1 = FUN_0040b4d0(in_EAX + 0x3604,iVar2);
      if ((cVar1 != '\0') && (cVar1 = FUN_0040b4d0(iVar2,in_EAX + 0x33e0), cVar1 != '\0')) {
        return 1;
      }
      cVar1 = FUN_0040b4d0(in_EAX + 0x3a4c,iVar2);
      if (cVar1 == '\0') {
        return 0;
      }
      iVar3 = in_EAX + 0x3828;
    }
    cVar1 = FUN_0040b4d0(iVar2,iVar3);
    if (cVar1 == '\0') {
      return 0;
    }
    return 1;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState();
  iVar3 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if ((iVar2 <= iVar3) && (cVar1 = FUN_0040b4d0(in_EAX + 0x4948,in_EAX + 0x40b8), cVar1 != '\0')) {
    return 1;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState();
  iVar3 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if ((iVar2 <= iVar3) && (cVar1 = FUN_0040b4d0(in_EAX + 0x4948,in_EAX + 0x4500), cVar1 != '\0')) {
    return 1;
  }
  return 0;
}

