/* AddMuteListEntry - 0x00425840 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * Sole caller is ParseChatSlashCommand's "mute" arm (dispatched by an
 * exact stricmp against &DAT_005535a4, which is the literal string "mute"
 * at 0x5535a4 in the original image's data section - confirmed by reading
 * the raw bytes there). After the FindMuteListIndex (FUN_004259d0) probe
 * comes back -1 (not already muted) and an own-nickname guard, it appends
 * the typed name to the mute array via AtlArray_AppendCString and shows
 * localized string 0x1fe - the add-confirmation message paired with
 * RemoveMuteListEntry's 0x1ff removal message and ClearMuteList's 0x200
 * clear message on the same array.
 *
 * (FUN_004259d0 below is now FindMuteListIndex.)
 *
 * EAX PROMOTED (2026-08-26): this function's own dropped incoming register,
 * `mov edi,eax` at its entry, forwarded straight to FUN_004259d0 as that
 * callee's EDI.  Its single caller ParseChatSlashCommand passes its param_1,
 * and every one of ParseChatSlashCommand's own call sites passes
 * g_clientContext -- which is also what the other nine FUN_004259d0 sites
 * pass, so the chain agrees end to end.
 */
#include "ghidra_types.h"


void AddMuteListEntry(char *regEsi,int regEax)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  char local_80 [128];
  
  iVar2 = FindMuteListIndex(regEsi, regEax);
  if (iVar2 == -1) {
    pcVar3 = regEsi;
    do {
      cVar1 = *pcVar3;
      pcVar3 = pcVar3 + 1;
    } while (cVar1 != '\0');
    if (pcVar3 != regEsi + 1) {
      iVar2 = __stricmp(regEsi,(char *)(g_clientContext + 0x23330));
      if (iVar2 != 0) {
        AtlArray_AppendCString(regEsi);
        pcVar3 = (char *)GetLocalizedString(&g_localizedStringTable,0x1fe);
        _sprintf(local_80,pcVar3);
        (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))(local_80,2,6);
      }
    }
  }
  return;
}

