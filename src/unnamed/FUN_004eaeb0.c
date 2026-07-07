/* FUN_004eaeb0 - 0x004eaeb0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004eaeb0(int param_1,int param_2,byte *param_3)

{
  int iVar1;
  int in_EAX;
  int iVar2;
  uint uVar3;
  int iVar4;
  int local_4;
  
  local_4 = 0xc;
  do {
    if (*param_3 != 0) {
      uVar3 = 7;
      iVar2 = param_1;
      do {
        if (((((*param_3 >> ((byte)uVar3 & 0x1f) & 1) != 0) && (iVar2 <= DAT_0056df30)) &&
            (DAT_00793530 <= iVar2)) && ((in_EAX <= DAT_0056df34 && (DAT_00793534 <= in_EAX)))) {
          *(undefined2 *)(DAT_0079352c + (in_EAX * DAT_005b3620 + iVar2) * 2) = param_2;
        }
        uVar3 = uVar3 - 1;
        iVar2 = iVar2 + 1;
      } while (uVar3 < 0x80000000);
    }
    if (param_3[1] != 0) {
      iVar4 = 0;
      iVar2 = 7;
      do {
        if ((((param_3[1] >> ((byte)iVar2 & 0x1f) & 1) != 0) &&
            (iVar1 = iVar4 + 8 + param_1, iVar1 <= DAT_0056df30)) &&
           ((DAT_00793530 <= iVar1 && ((in_EAX <= DAT_0056df34 && (DAT_00793534 <= in_EAX)))))) {
          *(undefined2 *)(DAT_0079352c + (in_EAX * DAT_005b3620 + iVar1) * 2) = param_2;
        }
        iVar4 = iVar4 + 1;
        iVar2 = iVar2 + -1;
      } while (3 < iVar2);
    }
    param_3 = param_3 + 2;
    in_EAX = in_EAX + 1;
    local_4 = local_4 + -1;
  } while (local_4 != 0);
  return;
}

