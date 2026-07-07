/* FUN_004ee850 - 0x004ee850 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status and src/unnamed/README.md for
 * this subdirectory's specific caveats.
 */
#include "ghidra_types.h"


void FUN_004ee850(void)

{
  int iVar1;
  void *_Memory;
  int *piVar2;
  uint uVar3;
  
  uVar3 = 0;
  if (DAT_00793560 != 0) {
    do {
      if (DAT_00793549 != '\0') {
        if (uVar3 != 0xffffffff) {
          (**(code **)(**(int **)((int)DAT_00793554 + uVar3 * 4) + 0xc))();
        }
        if (uVar3 == 0) {
          DAT_00793568 = 0;
        }
      }
      uVar3 = uVar3 + 1;
    } while (uVar3 < DAT_00793560);
  }
  if (DAT_0079354c != (int *)0x0) {
    uVar3 = 0;
    if (DAT_00793560 != 0) {
      do {
        if (DAT_00793554 != (void *)0x0) {
          (**(code **)(**(int **)((int)DAT_00793554 + uVar3 * 4) + 0xc))();
          iVar1 = *(int *)((int)DAT_00793554 + uVar3 * 4);
          *(undefined1 *)(iVar1 + 0x10) = 0;
          SetEvent(*(HANDLE *)(iVar1 + 8));
          if (*(HANDLE *)(iVar1 + 4) != (HANDLE)0x0) {
            WaitForSingleObject(*(HANDLE *)(iVar1 + 4),1000);
          }
          _Memory = *(void **)((int)DAT_00793554 + uVar3 * 4);
          if (_Memory != (void *)0x0) {
            FUN_004ef3f0(_Memory);
            _free(_Memory);
          }
        }
        if (DAT_00793558 != (void *)0x0) {
          piVar2 = *(int **)((int)DAT_00793558 + uVar3 * 4);
          (**(code **)(*piVar2 + 8))(piVar2);
          *(undefined4 *)((int)DAT_00793558 + uVar3 * 4) = 0;
        }
        uVar3 = uVar3 + 1;
      } while (uVar3 < DAT_00793560);
    }
    if (DAT_00793554 != (void *)0x0) {
      _free(DAT_00793554);
      DAT_00793554 = (void *)0x0;
    }
    if (DAT_00793558 != (void *)0x0) {
      _free(DAT_00793558);
      DAT_00793558 = (void *)0x0;
    }
    if (DAT_00793550 != (int *)0x0) {
      (**(code **)(*DAT_00793550 + 0x48))(DAT_00793550);
      (**(code **)(*DAT_00793550 + 8))(DAT_00793550);
      DAT_00793550 = (int *)0x0;
    }
    (**(code **)(*DAT_0079354c + 8))(DAT_0079354c);
    DAT_0079354c = (int *)0x0;
  }
  FUN_004f0d70();
  FreeLibrary(DAT_007935e8);
  return;
}

