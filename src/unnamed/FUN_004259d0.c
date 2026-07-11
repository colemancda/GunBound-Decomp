/* FUN_004259d0 - 0x004259d0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


uint FUN_004259d0(uchar *param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int unaff_EDI;
  
  iVar1 = *(int *)(&DAT_0067ec64 + unaff_EDI);
  uVar3 = 0;
  if (0 < iVar1) {
    do {
      if (*(uint *)(&DAT_0067ec64 + unaff_EDI) <= uVar3) {
                    /* WARNING: Subroutine does not return */
        ThrowCxxException(0x80070057);
      }
      iVar2 = __mbsicmp(*(uchar **)(*(int *)(&DAT_0067ec60 + unaff_EDI) + uVar3 * 4),param_1);
      if (iVar2 == 0) {
        return uVar3;
      }
      uVar3 = uVar3 + 1;
    } while ((int)uVar3 < iVar1);
  }
  return 0xffffffff;
}

