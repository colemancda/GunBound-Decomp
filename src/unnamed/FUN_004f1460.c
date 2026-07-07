/* FUN_004f1460 - 0x004f1460 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


void FUN_004f1460(void)

{
  void *in_EAX;
  int iVar1;
  int unaff_EDI;
  
  if (in_EAX != (void *)0x0) {
    if (*(char *)((int)in_EAX + 0x1018) == '\0') {
      if ((*(int *)((int)in_EAX + 0x100c) != 0) &&
         (*(int *)(*(int *)((int)in_EAX + 0x1004) + 0x70) == 0)) {
        FUN_004f0530();
      }
      iVar1 = *(int *)((int)in_EAX + 0x1004);
      if (*(int *)(iVar1 + 0x70) == 1) {
        iVar1 = *(int *)(iVar1 + 0x78);
      }
      else {
        iVar1 = *(int *)(iVar1 + 0x7c);
      }
      *(int *)(unaff_EDI + 0x10) = *(int *)(unaff_EDI + 0x10) + iVar1;
      *(undefined1 *)(unaff_EDI + 0x1044) = 0;
    }
    _free(in_EAX);
  }
  return;
}

