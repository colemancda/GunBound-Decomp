/* FUN_004f1390 - 0x004f1390 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


undefined4 __thiscall FUN_004f1390(char param_1,undefined4 param_2)

{
  undefined4 in_EAX;
  int iVar1;
  void *pvVar2;
  undefined4 uVar3;
  uint uVar4;
  int unaff_EDI;
  
  if (param_1 == '\0') {
    if ((*(char *)(unaff_EDI + 0x1044) == '\0') && (*(char *)(unaff_EDI + 0x1045) == '\0')) {
      uVar4 = FUN_004f1220(unaff_EDI,in_EAX,param_2);
      *(undefined1 *)(unaff_EDI + 0x1044) = 1;
      pvVar2 = operator_new(0x1024);
      if (pvVar2 != (void *)0x0) {
        iVar1 = *(int *)(unaff_EDI + 0x40 + (uVar4 >> 10) * 4);
        if (iVar1 == 0) {
          iVar1 = 0;
        }
        else {
          iVar1 = (uVar4 & 0x3ff) * 0x80 + iVar1;
        }
        uVar3 = ReadXFSEntry(iVar1,unaff_EDI + 0x1048);
        return uVar3;
      }
    }
  }
  else {
    iVar1 = FindXFSEntry(unaff_EDI,in_EAX);
    if (iVar1 != 0) {
      pvVar2 = operator_new(0x1024);
      if (pvVar2 != (void *)0x0) {
        uVar3 = ReadXFSEntry(iVar1,unaff_EDI + 0x1048);
        return uVar3;
      }
    }
  }
  return 0;
}

