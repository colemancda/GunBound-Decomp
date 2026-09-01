/* FUN_004265c0 - 0x004265c0 in the original binary.
 *
 * RECOVERED (2026-09-01): the prerequisite caller promotions landed in
 * the same batch as this note - the regEax parameter below is live and
 * every site passes the verified value; see the commit for the chain.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


int FUN_004265c0(char *regEax,int *regEsi)

{
  char cVar1;
  int iVar2;
  undefined4 local_c;
  undefined1 local_8 [4];
  undefined1 local_4 [4];
  
  iVar2 = FUN_00426780(local_8,&local_c,local_4,regEsi,(uchar *)regEax);
  if (iVar2 == 0) {
    if (*regEsi == 0) {
      cVar1 = HashMap_InitHashTable(regEsi,regEsi[2],1);
      if (cVar1 == '\0') {
                    /* WARNING: Subroutine does not return */
        ThrowCxxException(0x8007000e);
      }
    }
    iVar2 = FUN_00426960(*(int *)local_8,regEsi,(undefined4)regEax,local_c);
  }
  return iVar2 + 4;
}

