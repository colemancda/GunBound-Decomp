/* FUN_005322f0 - 0x005322f0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    ___free_lconv_mon
   
   Library: Visual Studio 2003 Release */

void ___free_lconv_mon(int param_1)

{
  undefined *puVar1;
  
  if (param_1 != 0) {
    puVar1 = *(undefined **)(param_1 + 0xc);
    if ((puVar1 != *(undefined **)(PTR_PTR_0056cbe4 + 0xc)) && (puVar1 != PTR_DAT_0056cbc0)) {
      _free(puVar1);
    }
    puVar1 = *(undefined **)(param_1 + 0x10);
    if ((puVar1 != *(undefined **)(PTR_PTR_0056cbe4 + 0x10)) && (puVar1 != PTR_DAT_0056cbc4)) {
      _free(puVar1);
    }
    puVar1 = *(undefined **)(param_1 + 0x14);
    if ((puVar1 != *(undefined **)(PTR_PTR_0056cbe4 + 0x14)) && (puVar1 != PTR_DAT_0056cbc8)) {
      _free(puVar1);
    }
    puVar1 = *(undefined **)(param_1 + 0x18);
    if ((puVar1 != *(undefined **)(PTR_PTR_0056cbe4 + 0x18)) && (puVar1 != PTR_DAT_0056cbcc)) {
      _free(puVar1);
    }
    puVar1 = *(undefined **)(param_1 + 0x1c);
    if ((puVar1 != *(undefined **)(PTR_PTR_0056cbe4 + 0x1c)) && (puVar1 != PTR_DAT_0056cbd0)) {
      _free(puVar1);
    }
    puVar1 = *(undefined **)(param_1 + 0x20);
    if ((puVar1 != *(undefined **)(PTR_PTR_0056cbe4 + 0x20)) && (puVar1 != PTR_DAT_0056cbd4)) {
      _free(puVar1);
    }
    puVar1 = *(undefined **)(param_1 + 0x24);
    if ((puVar1 != *(undefined **)(PTR_PTR_0056cbe4 + 0x24)) && (puVar1 != PTR_DAT_0056cbd8)) {
      _free(puVar1);
    }
  }
  return;
}

