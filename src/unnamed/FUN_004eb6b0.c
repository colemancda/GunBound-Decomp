/* FUN_004eb6b0 - 0x004eb6b0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_004eb6b0(int param_1)

{
  int in_EAX;
  undefined2 *puVar1;
  undefined2 unaff_BX;
  int unaff_EDI;
  
  if (((DAT_0079352c != 0) && (unaff_EDI <= DAT_0056df30)) && (DAT_00793530 <= unaff_EDI)) {
    if (in_EAX < DAT_00793534) {
      param_1 = param_1 + (in_EAX - DAT_00793534);
      in_EAX = DAT_00793534;
    }
    if (DAT_0056df34 < in_EAX + param_1) {
      param_1 = (DAT_0056df34 - in_EAX) + 1;
    }
    if ((0 < param_1) &&
       (puVar1 = (undefined2 *)(DAT_0079352c + (DAT_005b3620 * in_EAX + unaff_EDI) * 2), 0 < param_1
       )) {
      do {
        param_1 = param_1 + -1;
        *puVar1 = unaff_BX;
        puVar1 = puVar1 + DAT_005b3620;
      } while (param_1 != 0);
    }
  }
  return;
}

