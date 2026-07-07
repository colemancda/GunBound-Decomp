/* FUN_004711f0 - 0x004711f0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int __fastcall FUN_004711f0(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 0x40) + 1;
  *(int *)(param_1 + 0x40) = iVar2;
  if (0xf < iVar2) {
    *(undefined1 *)(param_1 + 0x14) = 1;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar1 = *(int *)(param_1 + 0x44) + 6;
  *(int *)(param_1 + 0x44) = iVar1 % iVar2;
  return iVar1 / iVar2;
}

