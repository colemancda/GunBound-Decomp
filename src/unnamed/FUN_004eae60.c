/* FUN_004eae60 - 0x004eae60 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004eae60(void)

{
  int iVar1;
  
  iVar1 = FUN_004f1390(0);
  if (iVar1 != 0) {
    ReadXFSEntryByte(iVar1,&DAT_00673628);
    ReadXFSEntryByte(iVar1,&DAT_005b3628);
    FUN_004f1460();
  }
  return;
}

