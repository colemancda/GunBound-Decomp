/* FUN_004f09d0 - 0x004f09d0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004f09d0(void)

{
  int iVar1;
  int unaff_ESI;
  undefined4 *puVar2;
  
  *(undefined ***)(unaff_ESI + 0x10714) = &PTR_FUN_005572dc;
  InitializeCriticalSection((LPCRITICAL_SECTION)(unaff_ESI + 0x10718));
  puVar2 = (undefined4 *)(unaff_ESI + 0x40);
  for (iVar1 = 0x400; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *(undefined1 *)(unaff_ESI + 0x1044) = 0;
  *(undefined4 *)(unaff_ESI + 8) = 0;
  *(undefined4 *)(unaff_ESI + 0x1040) = 0xffffffff;
  *(undefined1 *)(unaff_ESI + 0x1045) = 1;
  return;
}

