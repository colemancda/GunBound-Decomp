/* FUN_00425840 - 0x00425840 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * EAX PROMOTED (2026-08-26): this function's own dropped incoming register,
 * `mov edi,eax` at its entry, forwarded straight to FUN_004259d0 as that
 * callee's EDI.  Its single caller ParseChatSlashCommand passes its param_1,
 * and every one of ParseChatSlashCommand's own call sites passes
 * g_clientContext -- which is also what the other nine FUN_004259d0 sites
 * pass, so the chain agrees end to end.
 */
#include "ghidra_types.h"


void FUN_00425840(char *regEsi,int regEax)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  char local_80 [128];
  
  iVar2 = FUN_004259d0(regEsi, regEax);
  if (iVar2 == -1) {
    pcVar3 = regEsi;
    do {
      cVar1 = *pcVar3;
      pcVar3 = pcVar3 + 1;
    } while (cVar1 != '\0');
    if (pcVar3 != regEsi + 1) {
      iVar2 = __stricmp(regEsi,(char *)(g_clientContext + 0x23330));
      if (iVar2 != 0) {
        AppendWordFilterEntry(regEsi);
        pcVar3 = (char *)GetLocalizedString(&g_localizedStringTable,0x1fe);
        _sprintf(local_80,pcVar3);
        (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))(local_80,2,6);
      }
    }
  }
  return;
}

