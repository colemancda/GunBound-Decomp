/* FUN_004fe420 - 0x004fe420 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


void __thiscall
FUN_004fe420(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 in_EAX;
  undefined4 uVar1;
  uint uVar2;
  undefined4 *unaff_ESI;
  
  unaff_ESI[9] = param_1;
  unaff_ESI[3] = param_2;
  *unaff_ESI = 0;
  unaff_ESI[1] = 0;
  unaff_ESI[2] = in_EAX;
  unaff_ESI[8] = 0;
  unaff_ESI[10] = 0;
  unaff_ESI[0xb] = 0;
  unaff_ESI[4] = param_3;
  unaff_ESI[5] = param_4;
  uVar1 = FUN_0053753c();
  unaff_ESI[6] = uVar1;
  uVar2 = FUN_0053753c();
  unaff_ESI[7] = uVar2;
  if (uVar2 < 0x11) {
    unaff_ESI[7] = 0;
  }
  return;
}

