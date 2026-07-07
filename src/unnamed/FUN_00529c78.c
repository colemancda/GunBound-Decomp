/* FUN_00529c78 - 0x00529c78 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    __cinit
   
   Library: Visual Studio 2003 Release */

int __cdecl __cinit(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  if (PTR___fpmath_0056bf80 != (undefined *)0x0) {
    (*(code *)PTR___fpmath_0056bf80)(param_1);
  }
  iVar1 = 0;
  puVar2 = &DAT_005636f8;
  do {
    if (iVar1 != 0) {
      return iVar1;
    }
    if ((code *)*puVar2 != (code *)0x0) {
      iVar1 = (*(code *)*puVar2)();
    }
    puVar2 = puVar2 + 1;
  } while (puVar2 < &DAT_00563714);
  if (iVar1 == 0) {
    _atexit(FUN_0052e810);
    puVar2 = &DAT_00563000;
    do {
      if ((code *)*puVar2 != (code *)0x0) {
        (*(code *)*puVar2)();
      }
      puVar2 = puVar2 + 1;
    } while (puVar2 < &DAT_005636f4);
    iVar1 = 0;
  }
  return iVar1;
}

