/* BeginServerConnect - 0x004d2480 in the original binary.
 *
 * Public entry point to (re)connect the client's connection object to a
 * host:port. Resets outgoing packet-field state (twice, under the packet
 * critical section), then calls SignalConnectRequest to hand the target
 * port to the connection object and wake the background connect worker,
 * and sets the "connect requested" flag at conn+0x84e4. The destination
 * hostname string is passed via a register (EDI) the decompiler didn't
 * model, so it isn't visible in the C signature. Used for both the broker
 * (State02 ServerSelect OnEnter) and the chosen game server (via
 * FUN_004e1bf0). Because SignalConnectRequest closes any existing socket
 * first, calling this again retargets the same connection object.
 *
 * Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void BeginServerConnect(undefined4 param_1,undefined4 param_2)

{
  int unaff_EBX;
  
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  SignalConnectRequest(param_2);
  *(undefined1 *)(unaff_EBX + 0x84e4) = 1;
  return;
}

