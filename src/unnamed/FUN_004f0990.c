/* FUN_004f0990 - 0x004f0990 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int __fastcall FUN_004f0990(undefined4 param_1,char *param_2)

{
  char *in_EAX;
  int iVar1;
  int iVar2;
  
  while( true ) {
    if ((*in_EAX == '\0') && (*param_2 == '\0')) {
      return 0;
    }
    iVar2 = (int)*param_2;
    iVar1 = (int)*in_EAX;
    if ((0x40 < iVar1) && (iVar1 < 0x5b)) {
      iVar1 = iVar1 + 0x20;
    }
    if ((0x40 < iVar2) && (iVar2 < 0x5b)) {
      iVar2 = iVar2 + 0x20;
    }
    if (iVar1 - iVar2 != 0) break;
    in_EAX = in_EAX + 1;
    param_2 = param_2 + 1;
  }
  return iVar1 - iVar2;
}

