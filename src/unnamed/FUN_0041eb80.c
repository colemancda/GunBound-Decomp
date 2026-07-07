/* FUN_0041eb80 - 0x0041eb80 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined * FUN_0041eb80(int param_1,ushort param_2)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = 0;
  do {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar1 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if (param_2 == uVar1) {
      return &DAT_0058bb04 + param_1 + iVar2 * 0x9bc;
    }
    iVar2 = iVar2 + 1;
  } while (iVar2 < 100);
  return (undefined *)0x0;
}

