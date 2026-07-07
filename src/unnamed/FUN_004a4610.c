/* FUN_004a4610 - 0x004a4610 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_004a4610(int *param_1)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  
  (**(code **)(*param_1 + 0x18))();
  FUN_00450730();
  iVar3 = param_1[0xfe9] + 2;
  param_1[0xfe9] = iVar3;
  if (0x1e < iVar3) {
    iVar3 = 0x1e;
  }
  param_1[0xfe9] = iVar3;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  param_1[0xfe7] = (param_1[0xfe8] + param_1[0xfe7]) % iVar3;
  cVar1 = FUN_004065a0();
  if (cVar1 != '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar3 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(iVar3 + 1);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  iVar3 = param_1[0xed1];
  param_1[0xed1] = iVar3 + 1;
  if (iVar3 + 1 == 5) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar2);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  return;
}

