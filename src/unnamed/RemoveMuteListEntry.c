/* RemoveMuteListEntry - 0x004258e0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * Sole caller is ParseChatSlashCommand's "loud" arm (dispatched by an
 * exact stricmp against &DAT_00553588, which is the literal string "loud"
 * at 0x553588 in the original image's data section - confirmed by reading
 * the raw bytes there). It looks the typed name up via FindMuteListIndex
 * (FUN_004259d0 below), and when found removes it from the mute array via
 * AtlArray_RemoveAt_CString, then shows localized string 0x1ff - the
 * removal-confirmation message paired with AddMuteListEntry's 0x1fe
 * add message and ClearMuteList's 0x200 clear message on the same array.
 *
 * (FUN_00425840 is now AddMuteListEntry; FUN_004259d0 is now
 * FindMuteListIndex.)
 *
 * EAX PROMOTED (2026-08-26): this function's own dropped incoming register,
 * `mov edi,eax` at its entry, forwarded straight to FUN_004259d0 as that
 * callee's EDI.  Its single caller ParseChatSlashCommand passes its param_1,
 * and every one of ParseChatSlashCommand's own call sites passes
 * g_clientContext -- which is also what the other nine FUN_004259d0 sites
 * pass, so the chain agrees end to end.
 */
#include "ghidra_types.h"


void RemoveMuteListEntry(undefined4 param_1,int regEax)

{
  int iVar1;
  char *_Format;
  char local_80 [128];
  
  iVar1 = FindMuteListIndex(param_1, regEax);
  if (iVar1 != -1) {
    /* DROPPED REGISTERS RECOVERED (2026-08-27): 0x4258fe-0x425909 is
       `lea ebx,[edi + 0x67ec60]` with edi = regEax (set by this function's
       own `mov edi,eax` at 0x4258ef and never rewritten), `mov esi,1`, and
       `mov ecx,eax` = FUN_004259d0's return, i.e. iVar1. */
    AtlArray_RemoveAt_CString(iVar1,(int *)(regEax + 0x67ec60),1);
    _Format = (char *)GetLocalizedString(&g_localizedStringTable,0x1ff);
    _sprintf(local_80,_Format,param_1);
    (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x28))(local_80,2,6);
  }
  return;
}

