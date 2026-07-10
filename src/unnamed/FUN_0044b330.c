/* FUN_0044b330 - 0x0044b330 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_0044b330(int param_1)

{
  char cVar1;
  int iVar2;
  
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (*(uint *)(g_clientContext + 0x44e24) <= (uint)(*(int *)(param_1 + 0x454) + iVar2)) {
                    /* WARNING: Subroutine does not return */
    FUN_004010c0(0x80070057);
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  cVar1 = PeekPacketChecksumBool();
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(-(uint)(cVar1 != '\0') & 0x8000);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(0xffffffff);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_004141b0(0xffffffff,0xffffffff,0xffffffff,0xffffffff,param_1 + 0x31488,200000,300000);
  FUN_00449250(param_1,1,1);
  return;
}

