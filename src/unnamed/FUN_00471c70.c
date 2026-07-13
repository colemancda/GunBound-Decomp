/* FUN_00471c70 - 0x00471c70 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int __fastcall FUN_00471c70(int param_1)

{
  int iVar1;
  int iVar2;
  
  AdvanceSpriteAnimation(param_1);
  if (*(char *)(param_1 + 0x34) != '\0') {
    *(undefined1 *)(param_1 + 0x14) = 1;
  }
  if (*(char *)(g_clientContext + 0x45578) != '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar1 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar2 = *(int *)(param_1 + 0x44) + 5;
    *(int *)(param_1 + 0x44) = iVar2 % iVar1;
    return iVar2 / iVar1;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar1 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = *(int *)(param_1 + 0x44) + 2;
  *(int *)(param_1 + 0x44) = iVar2 % iVar1;
  return iVar2 / iVar1;
}

