/* RegisterActiveObject - 0x004f2fb0 in the original binary.
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


undefined4 __fastcall RegisterActiveObject(undefined4 param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  undefined4 *unaff_EDI;
  
  iVar2 = *(int *)(*(int *)(param_2 + 4) + 0x1c);
  uVar1 = *(uint *)(iVar2 + 4);
  while (uVar1 <= (uint)unaff_EDI[1]) {
    if (uVar1 == unaff_EDI[1]) goto LAB_004f2fd3;
    iVar2 = *(int *)(iVar2 + 0x1c);
    uVar1 = *(uint *)(iVar2 + 4);
  }
  iVar2 = FUN_004f2f00(param_2);
LAB_004f2fd3:
  uVar1 = unaff_EDI[2];
  if (uVar1 != 0xffffffff) {
    iVar2 = *(int *)(iVar2 + 0x10);
    uVar3 = *(uint *)(iVar2 + 8);
    if (uVar3 <= uVar1) {
      do {
        if (uVar3 == uVar1) {
          (**(code **)*unaff_EDI)(1);
          return 0;
        }
        iVar2 = *(int *)(iVar2 + 0x10);
        uVar3 = *(uint *)(iVar2 + 8);
      } while (uVar3 <= (uint)unaff_EDI[2]);
    }
  }
  unaff_EDI[4] = iVar2;
  unaff_EDI[3] = *(undefined4 *)(iVar2 + 0xc);
  *(undefined4 **)(*(int *)(iVar2 + 0xc) + 0x10) = unaff_EDI;
  *(undefined4 **)(iVar2 + 0xc) = unaff_EDI;
  return 1;
}

