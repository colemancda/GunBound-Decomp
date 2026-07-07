/* FUN_00503a10 - 0x00503a10 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00503a10(void)

{
  char cVar1;
  undefined4 in_EAX;
  undefined4 unaff_EDI;
  int local_4;
  
  cVar1 = FUN_004fe860(unaff_EDI,&local_4);
  if (cVar1 == '\0') {
    FUN_004fe8d0(in_EAX,0,0,0,0);
    cVar1 = FUN_004fe860(unaff_EDI,&local_4);
    if (cVar1 != '\0') {
      *(undefined1 *)(local_4 + 0x1c) = 1;
    }
  }
  return;
}

