/* FUN_004fcf10 - 0x004fcf10 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004fcf10(undefined4 param_1,undefined4 param_2)

{
  /* Ghidra artifact: raw stack reference the decompiler could not
   * map to a named local; declared so the raw port parses. */
  undefined stack0x00000004;
  char cVar1;
  int *in_EAX;
  undefined4 unaff_EBX;
  undefined4 unaff_EDI;
  undefined4 unaff_retaddr;
  
  cVar1 = (**(code **)(*in_EAX + 0x3c))();
  if (cVar1 != '\0') {
    FUN_004fe110(in_EAX + 0xb,unaff_EBX,unaff_EDI,unaff_retaddr,param_2);
    return;
  }
  FUN_004fd030();
  FUN_00502650(in_EAX,1,&stack0x00000004,unaff_retaddr,param_2);
  return;
}

