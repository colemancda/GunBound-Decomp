/* FUN_0047ab00 - 0x0047ab00 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_0047ab00(int param_1)

{
  char cVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 0x3fa0) + 1;
  *(int *)(param_1 + 0x3fa0) = iVar2;
  if (iVar2 < *(int *)(param_1 + 0x3f9c)) {
    FUN_00450730();
    return;
  }
  if (iVar2 == *(int *)(param_1 + 0x3f9c)) {
    cVar1 = PeekPacketChecksumBool();
    if (cVar1 == '\0') {
      FUN_004ee9b0(0);
    }
  }
  FUN_0048f1c0();
  return;
}

