/* FUN_00532291 - 0x00532291 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    ___free_lconv_num
   
   Library: Visual Studio 2003 Release */

void ___free_lconv_num(undefined4 *param_1)

{
  undefined *puVar1;
  
  if (param_1 != (undefined4 *)0x0) {
    puVar1 = (undefined *)*param_1;
    if ((puVar1 != *(undefined **)PTR_PTR_0056cbe4) && (puVar1 != PTR_DAT_0056cbb4)) {
      _free(puVar1);
    }
    puVar1 = (undefined *)param_1[1];
    if ((puVar1 != *(undefined **)(PTR_PTR_0056cbe4 + 4)) && (puVar1 != PTR_DAT_0056cbb8)) {
      _free(puVar1);
    }
    puVar1 = (undefined *)param_1[2];
    if ((puVar1 != *(undefined **)(PTR_PTR_0056cbe4 + 8)) && (puVar1 != PTR_DAT_0056cbbc)) {
      _free(puVar1);
    }
  }
  return;
}

