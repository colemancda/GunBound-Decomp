/* CloseConnectionSocket - 0x004e5a20 in the original binary.
 *
 * Resets the connection object's socket: state=1 (idle), closesocket() the
 * current socket if open, socket handle = -1 (INVALID_SOCKET), connected
 * flag (conn+0x22a) = 0. Called on FD_CLOSE and on any fatal recv/send error.
 *
 * FIXED (2026-07-13): same dropped-register-arg bug as ReceiveFramedPackets
 * (see that file) - the connection pointer arrived via ESI (`unaff_ESI`,
 * declared but never assigned) and every field access read garbage.
 * HandleSocketEvent's 4 call sites all have this pointer as `param_1` in
 * scope but weren't passing it - promoted to an explicit parameter here
 * and at those call sites.
 *
 * Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void CloseConnectionSocket(int conn)

{
  *(undefined4 *)(conn + 0x22c) = 1;
  if (*(SOCKET *)(conn + 0x24) != 0xffffffff) {
    closesocket(*(SOCKET *)(conn + 0x24));
  }
  *(undefined4 *)(conn + 0x24) = 0xffffffff;
  *(undefined1 *)(conn + 0x22a) = 0;
  return;
}

