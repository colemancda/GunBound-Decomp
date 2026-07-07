/* FUN_00525b1f - 0x00525b1f in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */

void FUN_00525b1f(void *param_1)

{
  void *pvVar1;
  int iVar2;
  _EXCEPTION_POINTERS *local_18;
  
  pvVar1 = (void *)(*DAT_005b1914)(DAT_0056c230);
  if (pvVar1 == (void *)0x0) {
    iVar2 = (*DAT_005b1918)(DAT_0056c230,param_1);
    pvVar1 = param_1;
    if (iVar2 == 0) {
      __amsg_exit(0x10);
    }
  }
  else {
    *(undefined4 *)((int)pvVar1 + 0x4c) = *(undefined4 *)((int)param_1 + 0x4c);
    *(undefined4 *)((int)pvVar1 + 0x50) = *(undefined4 *)((int)param_1 + 0x50);
    *(undefined4 *)((int)pvVar1 + 4) = *(undefined4 *)((int)param_1 + 4);
    _free(param_1);
  }
  if (PTR_FUN_0056bf84 != (undefined *)0x0) {
    (*(code *)PTR_FUN_0056bf84)();
  }
  (**(code **)((int)pvVar1 + 0x4c))(*(undefined4 *)((int)pvVar1 + 0x50));
  __endthread();
  __XcptFilter(local_18->ExceptionRecord->ExceptionCode,local_18);
  return;
}

