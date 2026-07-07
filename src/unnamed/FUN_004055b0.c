/* FUN_004055b0 - 0x004055b0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_004055b0(undefined4 param_1,char *param_2)

{
  char cVar1;
  char *pcVar2;
  undefined4 unaff_EDI;
  
  pcVar2 = param_2;
  if (param_2 != (char *)0x0) {
    do {
      cVar1 = *pcVar2;
      pcVar2 = pcVar2 + 1;
    } while (cVar1 != '\0');
    FUN_004056c0(unaff_EDI,param_2);
    return;
  }
  FUN_004056c0(unaff_EDI,0);
  return;
}

