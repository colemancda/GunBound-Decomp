/* FUN_004c1c90 - 0x004c1c90 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_004c1c90(int param_1)

{
  int iVar1;
  
  FUN_004eadb0();
  iVar1 = DAT_005b3484;
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 1;
  if ((&DAT_005f2f55)[iVar1] == '\x01') {
    FUN_004e3aa0(&DAT_006a7708 + iVar1);
  }
  FUN_004e3bd0();
  FUN_004eadb0();
  FUN_00406990(&DAT_006a647c + DAT_005b3484);
  FUN_004e93e0(1);
  return;
}

