/* FUN_00429b50 - 0x00429b50 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00429b50(void)

{
  int iVar1;
  int in_EAX;
  int *piVar2;
  int iVar3;
  
  iVar3 = 0;
  if (0 < *(int *)(&DAT_005f3258 + DAT_005b3484)) {
    piVar2 = (int *)(&DAT_005f3058 + DAT_005b3484);
    do {
      if ((piVar2[-0x40] == *(int *)(DAT_005b3484 + 0x3f804)) &&
         (*piVar2 == *(int *)(DAT_005b3484 + 0x44664 + *(int *)(in_EAX + 4) * 4))) {
        return;
      }
      iVar3 = iVar3 + 1;
      piVar2 = piVar2 + 1;
    } while (iVar3 < *(int *)(&DAT_005f3258 + DAT_005b3484));
  }
  if (*(char *)(*(int *)(in_EAX + 4) + 0x449ae + DAT_005b3484) == '\0') {
    FUN_0042a090();
    iVar1 = DAT_007934e8;
    iVar3 = DAT_005b3484;
    *(undefined4 *)(DAT_007934e8 + 0x44d0) = 6;
    *(undefined2 *)(iVar1 + 0x4d4) = 0x2110;
    *(undefined2 *)(iVar1 + 0x4d6) = *(undefined2 *)(iVar3 + 0x44664 + *(int *)(in_EAX + 4) * 4);
    iVar3 = *(int *)(iVar1 + 0x44d0);
    *(int *)(iVar1 + 0x44d0) = iVar3 + 2;
    *(undefined4 *)(iVar3 + 0x4d2 + iVar1) = _DAT_00551cb1;
    *(int *)(iVar1 + 0x44d0) = *(int *)(iVar1 + 0x44d0) + 4;
    *(undefined1 *)(in_EAX + 0x8f) = 0;
    FUN_004d2680();
    return;
  }
  FUN_00508910();
  return;
}

