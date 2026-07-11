/* FUN_00450e10 - 0x00450e10 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 FUN_00450e10(int param_1)

{
  char cVar1;
  int iVar2;
  int unaff_EBX;
  
  if ((((-1 < unaff_EBX) && (unaff_EBX < *(int *)(&g_nCameraBoundX + g_clientContext))) && (-1 < param_1))
     && (param_1 < *(int *)(&g_nCameraBoundY + g_clientContext))) {
    iVar2 = FUN_004f2f90();
    if (iVar2 != 0) {
      iVar2 = *(int *)(iVar2 + 0x10);
      cVar1 = *(char *)(iVar2 + 0x15);
      while (cVar1 == '\0') {
        cVar1 = FUN_0045d640(unaff_EBX,param_1);
        if (cVar1 != '\0') {
          return 1;
        }
        iVar2 = *(int *)(iVar2 + 0x10);
        cVar1 = *(char *)(iVar2 + 0x15);
      }
    }
    iVar2 = FUN_004f2f90();
    if (iVar2 != 0) {
      iVar2 = *(int *)(iVar2 + 0x10);
      cVar1 = *(char *)(iVar2 + 0x15);
      while (cVar1 == '\0') {
        cVar1 = FUN_00478a80(iVar2,unaff_EBX,param_1);
        if (cVar1 != '\0') {
          return 1;
        }
        iVar2 = *(int *)(iVar2 + 0x10);
        cVar1 = *(char *)(iVar2 + 0x15);
      }
    }
    return 0;
  }
  return 0;
}

