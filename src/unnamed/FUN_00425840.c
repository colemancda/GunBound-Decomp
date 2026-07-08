/* FUN_00425840 - 0x00425840 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00425840(void)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  char *unaff_ESI;
  char local_80 [128];
  
  iVar2 = FUN_004259d0(unaff_ESI);
  if (iVar2 == -1) {
    pcVar3 = unaff_ESI;
    do {
      cVar1 = *pcVar3;
      pcVar3 = pcVar3 + 1;
    } while (cVar1 != '\0');
    if (pcVar3 != unaff_ESI + 1) {
      iVar2 = __stricmp(unaff_ESI,(char *)(g_clientContext + 0x23330));
      if (iVar2 != 0) {
        FUN_00415bc0(unaff_ESI);
        pcVar3 = (char *)FUN_0043dc70(&DAT_00796eec,0x1fe);
        _sprintf(local_80,pcVar3);
        (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))(local_80,2,6);
      }
    }
  }
  return;
}

