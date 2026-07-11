/* BeginServerConnect - 0x004d2480 in the original binary.
 *
 * Public entry point to (re)connect the client's connection object to a
 * host:port. Resets outgoing packet-field state (twice, under the packet
 * critical section), then calls SignalConnectRequest to hand the target
 * host/port to the connection object and wake the background connect
 * worker, and sets the "connect requested" flag at conn+0x84e4. param_1 is
 * the hostname string (EDI at the call), param_2 the port (EAX at the
 * call) - both confirmed from orig 0x4d24c5-0x4d24d4. Used for both the
 * broker (State02 ServerSelect OnEnter) and the chosen game server (via
 * ConnectToSelectedServer). Because SignalConnectRequest closes any existing socket
 * first, calling this again retargets the same connection object.
 *
 * unaff_EBX (the connection object base) arrives via a dropped EBX
 * register - orig 0x4e1731 (State02_ServerSelect_OnEnter's call site)
 * shows `mov ebx, ds:0x7934f0` immediately before the call, confirming
 * it's DAT_007934f0 there. Promoted to an explicit 3rd parameter.
 *
 * Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void BeginServerConnect(undefined4 param_1,undefined4 param_2,int unaff_EBX)

{
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  SignalConnectRequest(*(int *)(unaff_EBX + 0x84e0),(char *)param_1,(int)param_2);
  *(undefined1 *)(unaff_EBX + 0x84e4) = 1;
  return;
}

