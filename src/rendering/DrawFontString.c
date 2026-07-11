/* DrawFontString - 0x004eb510 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __thiscall DrawFontString(int param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  char *in_EAX;
  int iVar2;
  char *pcVar3;
  int local_4;
  
  cVar1 = *in_EAX;
  if (cVar1 != '\0') {
    local_4 = param_1 + 6;
    iVar2 = param_1 + 0xc;
    do {
      pcVar3 = in_EAX + 1;
      if (cVar1 < '\0') {
        pcVar3 = in_EAX + 2;
        if (DAT_00793530 <= iVar2) {
          DrawWideGlyph(param_1,param_2,param_3);
        }
        param_1 = param_1 + 0xc;
        iVar2 = iVar2 + 0xc;
        local_4 = local_4 + 0xc;
      }
      else {
        if ((cVar1 != ' ') && (DAT_00793530 <= local_4)) {
          DrawNarrowGlyph(param_1,param_2,param_3);
        }
        param_1 = param_1 + 6;
        iVar2 = iVar2 + 6;
        local_4 = local_4 + 6;
      }
    } while ((param_1 <= DAT_0056df30) && (cVar1 = *pcVar3, in_EAX = pcVar3, cVar1 != '\0'));
  }
  return;
}

