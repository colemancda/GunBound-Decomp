/* FUN_0049e470 - 0x0049e470 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_0049e470(int param_1)

{
  int iVar1;
  int iVar2;
  
  *(int *)(param_1 + 0x44) = *(int *)(param_1 + 0x44) + 1;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar1 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = *(int *)(param_1 + 0x40) + 1;
  *(int *)(param_1 + 0x40) = iVar2;
  *(int *)(param_1 + 0x44) = *(int *)(param_1 + 0x44) % iVar1;
  if (7 < iVar2) {
    *(undefined1 *)(param_1 + 0x14) = 1;
  }
  return;
}

