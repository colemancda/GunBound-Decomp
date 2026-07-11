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

void ChangeGameState(int newStateId)

{
  if ((newStateId != g_currentGameState) && (g_stateChangeInProgress == 0)) {
    DAT_00e55a45 = 0;
    (**(code **)(*(int *)g_gameStateVTableArray[g_currentGameState] + 0x20))();
    FUN_004f3020();
    _DAT_00e9be98 = 0;
    _DAT_00e9be9c = 0;
    DAT_00e9c104 = 0;
    FUN_004f3020();
    FUN_005098e0(10000);
    if (newStateId == 0xf) {
      PostQuitMessage(0);
      return;
    }
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    AppendPersistentButtonName(&DAT_0067ec70 + g_clientContext);
    g_cursorTexture = FindPreloadedTextureByName(s_cursor_005524e8);
    ResolveObjectHandle(s_normal_00552230);
    FUN_005099b0();
    (**(code **)(*(int *)g_gameStateVTableArray[newStateId] + 0x1c))();
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

