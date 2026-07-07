/* FUN_004a1690 - 0x004a1690 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_004a1690(int *param_1)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  
  (**(code **)(*param_1 + 0x18))();
  FUN_004585e0();
  if (param_1[0xfe7] != -1) {
    param_1[0xfe7] = param_1[0xfe7] + 1;
  }
  FUN_00450730();
  cVar1 = FUN_004065a0();
  if (cVar1 != '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar2 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(iVar2 + 1);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  iVar2 = param_1[0xed1];
  param_1[0xed1] = iVar2 + 1;
  if (iVar2 + 1 == 5) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  return;
}

