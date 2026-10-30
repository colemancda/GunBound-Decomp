/* CommP2POwner_OnConnectionClosed - 0x005016d0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED 2026-10-29, CERTAIN (was FUN_005016d0).  Slot 2 of 0x5575b8, the
 * comm-engine handler vtable ConstructCommP2POwner stamps at owner+4
 * (`mov dword ptr [esi], 0x5575b8` at 0x4fd134, ESI = owner+4), read
 * from the original .rdata.  Its one invoker is CommEngineCloseConnection
 * (`call dword ptr [eax+8]` at 0x4fe6ac, ECX = the handler), the engine's
 * shared close routine on recv()==0, socket errors, FD_CLOSE, failed
 * shutdown and the owner's destructor - so this is the owner's
 * connection-closed notification.  It clears the session flags at
 * this+0x1a6c/+0x1a6d/+0x1a70, kills the timer at +0x1ab4, frees the two
 * buffers at +0x1d98/+0x201c and calls slot 1 of the object at +0x1aac.
 * `this` is the handler sub-object (owner+4), so these offsets are
 * owner+0x1a70.. - the +0x1a6c here is NOT the refcount
 * CommP2POwner_Release decrements at owner+0x1a6c.
 *
 * IGNORED STACK ARGUMENTS: the epilogue is `ret 8` (0x501745) and
 * CommEngineCloseConnection pushes two dwords (its ECX value, then the
 * connection node, 0x4fe6a8/0x4fe6a9), but the body never reads them.
 * The port declares only the ECX this.
 *
 * KNOWN DEFECT, NOT FIXED: the final virtual call (0x501738-0x501740:
 * `mov ecx,[esi+0x1aac]; mov edx,[ecx]; call [edx+4]`) passes that
 * object as ECX; the port's `(**(code **)(... + 4))()` drops it.  The
 * callee's class is unidentified, so its convention in this tree is not
 * known and the call is left as Ghidra emitted it.
 */
#include "ghidra_types.h"


void __fastcall CommP2POwner_OnConnectionClosed(int param_1)

{
  *(undefined1 *)(param_1 + 0x1a6c) = 0;
  *(undefined1 *)(param_1 + 0x1a6d) = 0;
  *(undefined4 *)(param_1 + 0x1a70) = 0;
  if (*(UINT_PTR *)(param_1 + 0x1ab4) != 0) {
    KillTimer(*(HWND *)(param_1 + 0x1ab0),*(UINT_PTR *)(param_1 + 0x1ab4));
    *(undefined4 *)(param_1 + 0x1ab4) = 0;
  }
  if (*(void **)(param_1 + 0x1d98) != (void *)0x0) {
    _free(*(void **)(param_1 + 0x1d98));
    *(undefined4 *)(param_1 + 0x1d98) = 0;
  }
  if (*(void **)(param_1 + 0x201c) != (void *)0x0) {
    _free(*(void **)(param_1 + 0x201c));
    *(undefined4 *)(param_1 + 0x201c) = 0;
  }
  (**(code **)(**(int **)(param_1 + 0x1aac) + 4))();
  return;
}

