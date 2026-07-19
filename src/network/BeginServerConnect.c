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
 * DROPPED-REGISTER FIX: `conn` (the connection object base) arrives via a
 * dropped EBX register, which Ghidra emitted as an uninitialised
 * `unaff_EBX`. Promoted to an explicit 3rd parameter. Re-verified
 * (2026-07-19) by angr CFG sweep - 100% agreement across both call sites:
 *   0x4e1731 (State02_ServerSelect_OnEnter): `mov ebx, dword ptr [0x7934f0]`
 *            then `call 0x4d2480` at 0x4e1746  -> DAT_007934f0
 *   0x4e1d2a (ConnectToSelectedServer): `mov ebx, eax` then `call 0x4d2480`
 *            at 0x4e1d2e, where EAX came from `mov eax, dword ptr
 *            [0x7934ec]` at 0x4e1d08          -> DAT_007934ec
 * EBX is genuinely read-before-written in the callee (`lea edi,[ebx+0x84]`
 * at 0x4d2492, the first use of EBX in the function).
 *
 * The two stack args are stdcall (`ret 8` at 0x4d24e3): orig 0x4d24c5-c9
 * reads [esp+0x14] -> port and [esp+0x10] -> hostname, i.e. param_1 is the
 * host string and param_2 the port.
 *
 * Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void BeginServerConnect(undefined4 param_1,undefined4 param_2,int conn)

{
  int unaff_EBX = conn;

  /* FIXED (2026-07-15): dropped `self` args - angr-confirmed at
   * 0x4d2498/0x4d24b9 (`lea edi,[ebx + 0x84]` / `lea edi,[ebx + 0x2a8]`,
   * ebx = unaff_EBX, the connection object base already promoted to a
   * parameter above): two distinct CValueGuard cells at unaff_EBX+0x84 and
   * unaff_EBX+0x2a8, the same two cells InitConnectionObject.c zero-inits
   * for this same connection object. `unaff_EBX` is plain `int`, so byte
   * offsets are natural. See tools/encodeoutgoingpacketfield_sites.json. */
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(unaff_EBX + 0x84, 0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(unaff_EBX + 0x2a8, 0);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  SignalConnectRequest(*(int *)(unaff_EBX + 0x84e0),(char *)param_1,(int)param_2);
  *(undefined1 *)(unaff_EBX + 0x84e4) = 1;
  return;
}

