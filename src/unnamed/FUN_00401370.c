/* FUN_00401370 - 0x00401370 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_00401370(int *param_1)

{
  int iVar1;
  
  if (param_1[1] != 0) {
    iVar1 = 0;
    if (0 < *param_1) {
      do {
        _free(*(void **)(param_1[1] + iVar1 * 4));
        iVar1 = iVar1 + 1;
      } while (iVar1 < *param_1);
    }
    _free((void *)param_1[1]);
    param_1[1] = 0;
  }
  if ((void *)param_1[2] != (void *)0x0) {
    _free((void *)param_1[2]);
  }
  param_1[2] = 0;
  if ((void *)param_1[3] != (void *)0x0) {
    _free((void *)param_1[3]);
  }
  param_1[3] = 0;
  if (param_1[4] != 0) {
    if (0 < *param_1) {
      iVar1 = 0;
      do {
        _free(*(void **)(param_1[4] + iVar1 * 4));
        iVar1 = iVar1 + 1;
      } while (iVar1 < *param_1);
    }
    _free((void *)param_1[4]);
    param_1[4] = 0;
  }
  if (param_1[5] != 0) {
    iVar1 = 0;
    if (0 < *param_1) {
      do {
        _free(*(void **)(param_1[5] + iVar1 * 4));
        iVar1 = iVar1 + 1;
      } while (iVar1 < *param_1);
    }
    _free((void *)param_1[5]);
    param_1[5] = 0;
  }
  return;
}

