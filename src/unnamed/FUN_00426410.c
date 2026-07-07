/* FUN_00426410 - 0x00426410 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int * __fastcall FUN_00426410(int *param_1)

{
  int iVar1;
  
  iVar1 = (**(code **)(DAT_005b1444 + 0xc))();
  *param_1 = iVar1 + 0x10;
  return param_1;
}

