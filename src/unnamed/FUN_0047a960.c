/* FUN_0047a960 - 0x0047a960 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_0047a960(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  
  iVar4 = *(int *)(g_clientContext + 0x23270);
  uVar3 = *(uint *)(param_1 + 8);
  iVar1 = *(int *)(g_clientContext + 0x23274);
  *(undefined1 *)(uVar3 + 0x23278 + g_clientContext) = 1;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  *(undefined4 *)((*(int *)(param_1 + 8) + 9000) * 0x10 + g_clientContext) = uVar2;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  *(undefined4 *)(*(int *)(param_1 + 8) * 0x10 + 0x23284 + g_clientContext) = uVar2;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  *(undefined4 *)(*(int *)(param_1 + 8) * 0x10 + 0x23288 + g_clientContext) = uVar2;
  uVar3 = uVar3 & 0x80000003;
  if ((int)uVar3 < 0) {
    uVar3 = (uVar3 - 1 | 0xfffffffc) + 1;
  }
  iVar4 = ((*(uint *)(param_1 + 8) >> 2) * iVar1 + uVar3 * 2) * 0x40 + iVar4;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_004784a0(iVar4,iVar1);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  FUN_004784a0(iVar1 * 0x80 + iVar4,iVar1);
  return;
}

