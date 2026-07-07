/* FUN_00406400 - 0x00406400 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


uint __fastcall FUN_00406400(undefined4 param_1,uint param_2)

{
  uint uVar1;
  int in_EAX;
  uint uVar2;
  uint unaff_ESI;
  
  uVar2 = *(uint *)(*(int *)(in_EAX + 4) + 0x1c);
  uVar1 = *(uint *)(uVar2 + 4);
  do {
    if (param_2 < uVar1) {
LAB_00406419:
      return uVar2 & 0xffffff00;
    }
    if (uVar1 == param_2) {
      uVar2 = *(uint *)(uVar2 + 0x10);
      uVar1 = *(uint *)(uVar2 + 8);
      if (uVar1 <= unaff_ESI) {
        while (uVar1 != unaff_ESI) {
          uVar2 = *(uint *)(uVar2 + 0x10);
          uVar1 = *(uint *)(uVar2 + 8);
          if (unaff_ESI < uVar1) {
            return uVar2 & 0xffffff00;
          }
        }
        if (*(int *)(uVar2 + 0x24) != 3) {
          return CONCAT31((int3)(uVar2 >> 8),1);
        }
      }
      goto LAB_00406419;
    }
    uVar2 = *(uint *)(uVar2 + 0x1c);
    uVar1 = *(uint *)(uVar2 + 4);
  } while( true );
}

