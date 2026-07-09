/* ReadXFSEntry - 0x004f0380 in the original binary.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output - not hand-
 * verified against documented behavior beyond what's already in
 * ARCHITECTURE.md/PROTOCOL.md/FILEFORMATS.md. Calls to unnamed
 * FUN_<address> helpers and DAT_<address>/_DAT_<address> globals are
 * left as-is (undeclared) - this file won't link standalone yet. See
 * src/README.md's "Raw/verbatim ports" section for status and how
 * these get promoted to verified.
 */
#include "ghidra_types.h"
#include <windows.h>


undefined4 __fastcall ReadXFSEntry(undefined4 param_1,int param_2,int param_3,undefined4 param_4)

{
  undefined4 in_EAX;
  int iVar1;
  undefined4 *unaff_ESI;
  undefined4 *puVar2;
  
  unaff_ESI[0x400] = in_EAX;
  unaff_ESI[0x401] = param_3;
  unaff_ESI[0x403] = 0;
  *(char *)(unaff_ESI + 0x406) = param_2;
  puVar2 = unaff_ESI;
  for (iVar1 = 0x400; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  unaff_ESI[0x407] = param_4;
  unaff_ESI[0x404] = *(undefined4 *)(unaff_ESI[0x401] + 0x74);
  unaff_ESI[0x405] = 0;
  *(undefined1 *)(unaff_ESI + 0x408) = 1;
  if ((param_2 != '\0') && (*(int *)(param_3 + 0x70) == 0)) {
    DecodeXFSEntryBlock();
  }
  return;
}

