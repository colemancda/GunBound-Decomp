/* FUN_00425700 - 0x00425700 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00425700(void)

{
  int iVar1;
  DWORD DVar2;
  int unaff_ESI;
  
  iVar1 = __stricmp((char *)(DAT_005b3484 + 0x23313),&DAT_00551e24);
  if (iVar1 != 0) {
    iVar1 = __stricmp((char *)(DAT_005b3484 + 0x23313),&DAT_00552c68);
    if ((iVar1 != 0) && (*(int *)(&DAT_0067e3c8 + unaff_ESI) < 0x20)) {
      DVar2 = GetTickCount();
      *(DWORD *)(&DAT_0067e348 + *(int *)(&DAT_0067e3c8 + unaff_ESI) * 4 + unaff_ESI) =
           DVar2 + 10000;
      *(int *)(&DAT_0067e3c8 + unaff_ESI) = *(int *)(&DAT_0067e3c8 + unaff_ESI) + 1;
    }
  }
  return;
}

