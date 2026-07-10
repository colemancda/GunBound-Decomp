/* FUN_004258e0 - 0x004258e0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004258e0(undefined4 param_1)

{
  int iVar1;
  char *_Format;
  char local_80 [128];
  
  iVar1 = FUN_004259d0(param_1);
  if (iVar1 != -1) {
    FUN_004264d0();
    _Format = (char *)GetLocalizedString(&g_localizedStringTable,0x1ff);
    _sprintf(local_80,_Format,param_1);
    (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))(local_80,2,6);
  }
  return;
}

