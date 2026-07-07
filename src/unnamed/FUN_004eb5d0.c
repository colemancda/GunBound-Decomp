/* FUN_004eb5d0 - 0x004eb5d0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_004eb5d0(undefined4 param_1,int param_2,int param_3)

{
  int in_EAX;
  int unaff_EDI;
  
  if (((DAT_0079352c != 0) && (unaff_EDI <= DAT_0056df34)) && (DAT_00793534 <= unaff_EDI)) {
    if (in_EAX < DAT_00793530) {
      param_2 = param_2 + (in_EAX - DAT_00793530);
      in_EAX = DAT_00793530;
    }
    if (DAT_0056df30 < in_EAX + param_2) {
      param_2 = (DAT_0056df30 - in_EAX) + 1;
    }
    if (0 < param_2) {
      FUN_004f26f0(DAT_0079352c + (DAT_005b3620 * unaff_EDI + in_EAX) * 2,param_3,param_2);
    }
  }
  return;
}

