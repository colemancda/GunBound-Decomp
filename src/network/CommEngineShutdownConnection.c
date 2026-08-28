/* CommEngineShutdownConnection - 0x004fdda0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED (2026-08-28): the graceful close - shutdown(sock, SD_BOTH) on
 * the node's socket at +8, and only when the shutdown call itself
 * fails outright does it fall back to the hard
 * CommEngineCloseConnection (was FUN_004fe6a0). Named for the winsock
 * call it wraps, in contrast to the closesocket-based Close. Two
 * callers: CommEngineRecv's peer-closed path and FUN_00501770.
 *
 *
 * DROPPED-REG FIX (2026-08-28): shuts down the node's socket and, when
 * the shutdown fails outright, erases the node. ESI is the NODE (its
 * +8 is the SOCKET shutdown(2) targets) and param_1 - `ret 4` said it
 * was there all along, read at 0x4fddb6 as `mov edx,[esp+4]` - is the
 * vtable'd ENGINE object handed to FUN_004fe6a0. The `xor ecx,ecx` at
 * 0x4fddbc is this function's own, so the erase's first argument is a
 * literal 0. Two sites: CommEngineRecv passes its regEdi engine and its
 * param_1 node; FUN_00501770 passes param_1 - 0x2f0 (already spelled in
 * its source) and the node at *(param_1 + 0x1780) (`mov esi,
 * [edi+0x1780]` at 0x501d0d, edi = its param_1).
 */
#include "ghidra_types.h"


undefined4 CommEngineShutdownConnection(int *param_1,int regEsi)

{
  int iVar1;
  int unaff_ESI = regEsi;
  
  if ((*(SOCKET *)(unaff_ESI + 8) != 0xffffffff) &&
     (iVar1 = shutdown(*(SOCKET *)(unaff_ESI + 8),2), iVar1 != -1)) {
    return 1;
  }
  CommEngineCloseConnection(0,param_1,(int *)unaff_ESI);
  return 1;
}

