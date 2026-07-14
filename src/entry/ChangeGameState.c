/* ChangeGameState - 0x004122f0 in the original binary.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output - not hand-
 * verified against documented behavior beyond what's already in
 * ARCHITECTURE.md/PROTOCOL.md/FILEFORMATS.md. Calls to unnamed
 * FUN_<address> helpers and DAT_<address>/_DAT_<address> globals are
 * left as-is (undeclared) - this file won't link standalone yet. See
 * src/README.md's "Raw/verbatim ports" section for status and how
 * these get promoted to verified.
 */
#include "ghidra_types.h"
#include <windows.h>


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention */

/* CGameState's OnEnter(+0x1c)/OnExit(+0x20) virtuals both take `this` via
 * ECX (__fastcall) - orig 0x41230b/0x41231b and 0x412450-0x412468 both
 * show `mov ecx, [.. *4+0x5b33f8]` (the state object) immediately before
 * `call [eax+0x20/0x1c]`, with no other push - the generic zero-arg
 * code() cast this file used to make those calls with silently dropped
 * `this`, leaving every OnEnter/OnExit reading garbage/null off its own
 * object pointer. */
typedef void (__fastcall *GameStateVirtualFn)(void *thisPtr);

void ChangeGameState(int newStateId)

{
  if ((newStateId != g_currentGameState) && (g_stateChangeInProgress == 0)) {
    DAT_00e55a45 = 0;
    ((GameStateVirtualFn)(*(void ***)g_gameStateVTableArray[g_currentGameState])[8])
              (g_gameStateVTableArray[g_currentGameState]);
    SweepActiveObjectRegistry((int)&DAT_00e9be90);
    _DAT_00e9be98 = 0;
    _DAT_00e9be9c = 0;
    DAT_00e9c104 = 0;
    SweepActiveObjectRegistry((int)&DAT_00e9c0fc);
    FUN_005098e0((int)&g_uiPanelManager, 10000);
    if (newStateId == 0xf) {
      PostQuitMessage(0);
      return;
    }
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext,(char *)s_b_gamelist_buddyup_005522bc);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext,(char *)s_b_gamelist_buddydown_005522a4);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext,(char *)s_b_gamelist_channelup_0055228c);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext,(char *)s_b_gamelist_channeldown_00552274);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext,(char *)s_b_buddy_up_00552268);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext,(char *)s_b_buddy_down_00552258);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext,(char *)s_b_buddy_exit_00552248);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext,(char *)s_b_error_confirm_00552238);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext,(char *)s_cursor_005524e8);
    g_cursorTexture = FindPreloadedTextureByName(s_cursor_005524e8);
    ResolveNamedState(s_normal_00552230);
    FUN_005099b0();
    ((GameStateVirtualFn)(*(void ***)g_gameStateVTableArray[newStateId])[7])
              (g_gameStateVTableArray[newStateId]);
    g_currentGameState = newStateId;
    FUN_004f0320();
    if (g_stateChangeRequested != '\0') {
      g_stateChangeRequested = 0;
      return;
    }
    DAT_0056d108 = 10;
    _DAT_007934d8 = 0xffffffff;
  }
  return;
}

