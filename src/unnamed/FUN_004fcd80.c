/* FUN_004fcd80 - 0x004fcd80 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */
/* WARNING: Unable to track spacebase fully for stack */
/* WARNING: Type propagation algorithm not settling */

undefined4 FUN_004fcd80(undefined4 param_1,undefined4 param_2)

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
    asStack_1c[3] = 0x4fcdb1;
    if (&stack0xfffffff4 != (undefined1 *)(iVar2 * 0x10)) {
      asStack_1c[iVar2 * -4 + 3] = 0x4fcdbc;
      /* RECOVERED (2026-07-19): EBX = the alloca'd output block (orig
       * `mov ebx,esp` just before the call), EDI = in_EAX, this function's
       * own crypto context. */
      cVar1 = (char)FUN_004fce60((int)(&stack0xfffffff4 + iVar2 * -0x10),in_EAX);
      if (cVar1 != '\0') {
        asStack_1c[iVar2 * -4 + 3] = param_2;
        asStack_1c[iVar2 * -4 + 2] = (size_t)(&stack0xfffffff4 + iVar2 * -0x10);
        asStack_1c[iVar2 * -4 + 1] = param_1;
        asStack_1c[iVar2 * -4] = 0x4fcdce;
        _strncpy((char *)asStack_1c[iVar2 * -4 + 1],(char *)asStack_1c[iVar2 * -4 + 2],
                 asStack_1c[iVar2 * -4 + 3]);
        return 1;
      }
    }
  }
  return 0;
}

