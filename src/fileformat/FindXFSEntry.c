/* FindXFSEntry - 0x004f1110 in the original binary.
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


int FindXFSEntry(int param_1)

{
  uint uVar1;
  bool bVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  
  if (*(int *)(param_1 + 8) == 0) {
    return 0;
  }
  uVar5 = *(uint *)(param_1 + 8);
  bVar2 = false;
  uVar6 = 0;
  uVar1 = uVar5 >> 1;
  while( true ) {
    uVar7 = uVar1;
    iVar8 = *(int *)(param_1 + 0x40 + (uVar7 >> 10) * 4);
    if (iVar8 == 0) {
      iVar8 = 0;
    }
    else {
      iVar8 = (uVar7 & 0x3ff) * 0x80 + iVar8;
    }
    iVar3 = FUN_004f0990();
    if (iVar3 == 0) break;
    if (iVar3 < 0) {
      uVar5 = uVar7;
      uVar7 = uVar6;
    }
    uVar4 = uVar5 - uVar7 >> 1;
    uVar1 = uVar4 + uVar7;
    uVar6 = uVar7;
    if (uVar4 == 0) {
      if (bVar2) {
        return 0;
      }
      bVar2 = true;
    }
  }
  return iVar8;
}

