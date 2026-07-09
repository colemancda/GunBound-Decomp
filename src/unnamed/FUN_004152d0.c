/* FUN_004152d0 - 0x004152d0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined1 FUN_004152d0(undefined4 param_1)

{
  undefined1 uVar1;
  
  uVar1 = 1;
  switch(param_1) {
  case 0x3e9:
  case 0x3ea:
    ShowErrorDialog(1);
    return 0;
  case 0x3f3:
    ShowErrorDialog(1);
    return 0;
  case 0x3f4:
    ShowErrorDialog(0);
    return 1;
  case 0x3f5:
    ShowErrorDialog(1);
    return 0;
  case 0x3f6:
    ShowErrorDialog(1);
    return 0;
  case 0x3f7:
    ShowErrorDialog(1);
    uVar1 = 0;
  }
  return uVar1;
}

