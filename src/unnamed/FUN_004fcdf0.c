/* FUN_004fcdf0 - 0x004fcdf0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */
/* WARNING: Unable to track spacebase fully for stack */
/* WARNING: Type propagation algorithm not settling */

int FUN_004fcdf0(undefined4 param_1,undefined4 param_2)

{
  /* Ghidra artifact: raw stack reference the decompiler could not
   * map to a named local; declared so the raw port parses. */
  undefined stack0xfffffff4;
  char cVar1;
  int in_EAX;
  int iVar2;
  size_t asStack_1c [4];
  
  if (*(int *)(in_EAX + 0x27c) != 0) {
    iVar2 = *(int *)(in_EAX + 0x280) + 0x10;
    iVar2 = (int)(iVar2 + (iVar2 >> 0x1f & 0xfU)) >> 4;
    asStack_1c[3] = 0x4fce21;
    if (&stack0xfffffff4 != (undefined1 *)(iVar2 * 0x10)) {
      asStack_1c[iVar2 * -4 + 3] = 0x4fce2c;
      cVar1 = FUN_004fce60();
      if (cVar1 != '\0') {
        asStack_1c[iVar2 * -4 + 3] = param_2;
        asStack_1c[iVar2 * -4 + 2] = param_1;
        asStack_1c[iVar2 * 0xfffffffcU + 1] = (size_t)(&stack0xfffffff4 + iVar2 * -0x10);
        asStack_1c[iVar2 * -4] = 0x4fce3e;
        iVar2 = __strnicmp((char *)asStack_1c[iVar2 * 0xfffffffcU + 1],
                           (char *)asStack_1c[iVar2 * -4 + 2],asStack_1c[iVar2 * -4 + 3]);
        return iVar2;
      }
    }
  }
  return -1;
}

