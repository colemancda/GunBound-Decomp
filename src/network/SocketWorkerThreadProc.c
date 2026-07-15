/* SocketWorkerThreadProc - 0x00405dc0 in the original binary.
 *
 * __beginthread thread-proc entry point for the connection-object worker
 * (started from FUN_004058c0 with the new connection object as its arg).
 * Orig 0x405dc0-0x405dc5: `mov esi, [esp+8]` (the CRT thread-trampoline's
 * arg) then falls straight into FUN_00405dd0, which uses esi directly as
 * a register - not a separate re-passed argument. Promoted to an explicit
 * parameter forwarded to FUN_00405dd0.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void SocketWorkerThreadProc(void *unaff_ESI)

{
  FUN_00405dd0(unaff_ESI);
  return;
}

