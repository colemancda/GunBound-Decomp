/* FUN_0050f000 - 0x0050f000 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


int __fastcall FUN_0050f000(undefined4 param_1,int param_2)

{
  undefined4 *puVar1;
  int iVar2;
  int in_EAX;
  int unaff_ESI;
  
  puVar1 = *(undefined4 **)(in_EAX + 4);
  do {
    if (puVar1 == (undefined4 *)0x0) {
      return 0;
    }
    iVar2 = puVar1[2];
    puVar1 = (undefined4 *)*puVar1;
  } while ((*(int *)(iVar2 + 0x20) != param_2) || (*(int *)(iVar2 + 0x24) != unaff_ESI));
  return iVar2;
}

