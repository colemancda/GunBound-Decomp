/* FUN_0041eaa0 - 0x0041eaa0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


uint FUN_0041eaa0(undefined4 param_1,int param_2)

{
  uint uVar1;
  uint extraout_EAX;
  int iVar2;
  
  iVar2 = 0;
  do {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar1 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (param_2 == uVar1) {
      uVar1 = FUN_004065a0();
      return uVar1;
    }
    iVar2 = iVar2 + 1;
  } while (iVar2 < 100);
  return extraout_EAX & 0xffffff00;
}

