/* AppendReadyRoomStatusMessage - 0x004d7d70 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * `this` SLOT ADDED (2026-10-30): this is a game-state vtable slot-10
 * (+0x28) virtual, and every caller dispatches it with ECX = the state
 * object and three stack arguments (`ret 0xc` at 0x4d7da7).  The body never
 * reads ECX - its first ECX use is the `mov cl,[eax]` strlen loop - so
 * Ghidra gave it no `this`.  But State11's slot-10 target,
 * State11_InBattle_AppendChatLine, does read it (`mov edi,ecx` at
 * 0x4c1b9f), and one call site cannot serve both shapes; in this tree
 * erased __thiscall is cdecl with `this` first, so this port now takes
 * the (unused) `this` as its first parameter like its siblings.  It has
 * no direct callers, only the vtable dispatches.
 */
#include "ghidra_types.h"


void AppendReadyRoomStatusMessage(void *thisPtr,char *param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  char *pcVar2;
  
  pcVar2 = param_1;
  do {
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  AppendChatLogEntry(g_clientContext,param_2,0,0,param_1,param_3,1,
                     (int)pcVar2 - ((int)param_1 + 1));
  return;
}

