/* FUN_00406170 - 0x00406170 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


void FUN_00406170(void)

{
  int in_EAX;
  int *piVar1;
  
  piVar1 = (int *)FUN_0040cea0();
  *(undefined4 *)(in_EAX + 0xc) = 0;
  if (((piVar1 != (int *)0x0) && ((*(char *)(in_EAX + 0x14) == '\0' || (piVar1[1] == 1000000)))) &&
     ((piVar1[9] == 1 || (piVar1[9] == 5)))) {
    FUN_004f2da0(0,piVar1[1],piVar1[2]);
    (**(code **)(*piVar1 + 4))(s_mouse_00551e70);
    FUN_004ee9b0(0);
  }
  return;
}

