/* FUN_004ff690 - 0x004ff690 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004ff690(undefined4 param_1)

{
  int in_EAX;
  int iVar1;
  int *unaff_ESI;
  SOCKET unaff_EDI;
  
  if (in_EAX != 0x10) {
                    /* WARNING: Could not recover jumptable at 0x004ff699. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    closesocket(unaff_EDI);
    return;
  }
  iVar1 = FUN_004ff350(unaff_ESI,param_1);
  if (iVar1 == 0) {
                    /* WARNING: Could not recover jumptable at 0x004ff6b4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    closesocket(unaff_EDI);
    return;
  }
  (**(code **)(*unaff_ESI + 0xc))(0,iVar1);
  return;
}

