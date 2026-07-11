/* AcquireSoundChannel - 0x004ee9b0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


uint AcquireSoundChannel(void)

{
  char *pcVar1;
  char cVar2;
  uint uVar3;
  char *unaff_EDI;
  
  if ((unaff_EDI != (char *)0x0) && (DAT_0079354b != '\0')) {
    pcVar1 = unaff_EDI + 1;
    do {
      cVar2 = *unaff_EDI;
      unaff_EDI = unaff_EDI + 1;
    } while (cVar2 != '\0');
    if (unaff_EDI != pcVar1) {
      uVar3 = 1;
      if (1 < DAT_00793560) {
        do {
          if (*(char *)(*(int *)(DAT_00793554 + uVar3 * 4) + 0x4c) == '\0') break;
          uVar3 = uVar3 + 1;
        } while (uVar3 < DAT_00793560);
      }
      if (uVar3 != DAT_00793560) {
        cVar2 = (**(code **)(**(int **)(DAT_00793554 + uVar3 * 4) + 8))(uVar3);
        if (cVar2 == '\0') {
          uVar3 = 0xffffffff;
        }
        return uVar3;
      }
      return 0xffffffff;
    }
  }
  return 0xffffffff;
}

