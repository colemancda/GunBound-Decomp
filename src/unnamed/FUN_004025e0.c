/* FUN_004025e0 - 0x004025e0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004025e0(undefined4 param_1,char *param_2)

{
  char cVar1;
  bool bVar2;
  int iVar3;
  undefined4 *puVar4;
  
  iVar3 = FUN_00509730();
  if (iVar3 == 0) {
    puVar4 = (undefined4 *)FUN_00401bb0(param_1);
    bVar2 = false;
    if (puVar4 == (undefined4 *)0x0) {
      puVar4 = operator_new(0x5c);
      if (puVar4 == (undefined4 *)0x0) {
        puVar4 = (undefined4 *)0x0;
      }
      else {
        puVar4[1] = 0;
        puVar4[2] = 0xffffffff;
        puVar4[3] = 0;
        puVar4[4] = 0;
        *(undefined1 *)(puVar4 + 5) = 0;
        *(undefined1 *)((int)puVar4 + 0x15) = 0;
        *puVar4 = &PTR_FUN_00551cb4;
        *(undefined1 *)(puVar4 + 0xc) = 0;
        *(undefined4 *)((int)puVar4 + 0x31) = 0xffffffff;
        *(undefined4 *)((int)puVar4 + 0x35) = 0xffffffff;
        *(undefined4 *)((int)puVar4 + 0x39) = 0xffffffff;
        *(undefined4 *)((int)puVar4 + 0x3d) = 0xffffffff;
      }
      iVar3 = 0x21 - (int)param_2;
      do {
        cVar1 = *param_2;
        param_2[(int)puVar4 + iVar3] = cVar1;
        param_2 = param_2 + 1;
      } while (cVar1 != '\0');
      *(undefined2 *)((int)puVar4 + 0x2e) = 500;
      bVar2 = true;
    }
    FUN_00509260(&DAT_00e53c40,puVar4);
    if ((bVar2) && (puVar4 != (undefined4 *)0x0)) {
      (**(code **)*puVar4)(1);
    }
  }
  return;
}

