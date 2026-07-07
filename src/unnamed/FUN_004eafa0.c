/* FUN_004eafa0 - 0x004eafa0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __thiscall FUN_004eafa0(int param_1,int param_2,undefined2 param_3)

{
  byte *in_EAX;
  int iVar1;
  int iVar2;
  int local_4;
  
  local_4 = 0xc;
  do {
    if (*in_EAX != 0) {
      iVar2 = 7;
      iVar1 = param_2;
      do {
        if (((((*in_EAX >> ((byte)iVar2 & 0x1f) & 1) != 0) && (iVar1 <= DAT_0056df30)) &&
            (DAT_00793530 <= iVar1)) && ((param_1 <= DAT_0056df34 && (DAT_00793534 <= param_1)))) {
          *(undefined2 *)(DAT_0079352c + (param_1 * DAT_005b3620 + iVar1) * 2) = param_3;
        }
        iVar2 = iVar2 + -1;
        iVar1 = iVar1 + 1;
      } while (1 < iVar2);
    }
    in_EAX = in_EAX + 1;
    param_1 = param_1 + 1;
    local_4 = local_4 + -1;
  } while (local_4 != 0);
  return;
}

