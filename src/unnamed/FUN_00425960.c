/* FUN_00425960 - 0x00425960 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00425960(void)

{
  int unaff_EBX;
  int iVar1;
  
  if (*(int *)(&DAT_0067ec60 + unaff_EBX) != 0) {
    for (iVar1 = *(int *)(&DAT_0067ec64 + unaff_EBX); iVar1 != 0; iVar1 = iVar1 + -1) {
      FUN_00405320();
    }
    _free(*(void **)(&DAT_0067ec60 + unaff_EBX));
    *(undefined4 *)(&DAT_0067ec60 + unaff_EBX) = 0;
  }
  *(undefined4 *)(&DAT_0067ec64 + unaff_EBX) = 0;
  *(undefined4 *)(&DAT_0067ec68 + unaff_EBX) = 0;
  GetLocalizedString(&g_localizedStringTable,0x200);
  FUN_00413af0();
  return;
}

