/* FUN_004f16c0 - 0x004f16c0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004f16c0(void)

{
  int iVar1;
  undefined4 unaff_ESI;
  char local_5;
  undefined1 local_4 [4];
  
  FUN_004f08a0();
  iVar1 = ReadXFSEntryByte(unaff_ESI,&local_5);
  if (iVar1 != -2) {
    FUN_004f08a0();
    FUN_004f08a0();
    iVar1 = ReadXFSEntryByte(unaff_ESI,local_4);
    if (iVar1 != -2) {
      FUN_004f08a0();
      if (local_5 != '\0') {
        iVar1 = ReadXFSEntryByte(unaff_ESI,local_4);
        if (iVar1 != -2) {
          FUN_004f08a0();
        }
      }
    }
  }
  return;
}

