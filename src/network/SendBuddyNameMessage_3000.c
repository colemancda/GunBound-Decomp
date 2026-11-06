/* SendBuddyNameMessage_3000 - 0x004fcee0 in the original binary.
 *
 * NAMED (batch 36), LIKELY. The fixed-type sibling of SendBuddyNameMessage
 * (0x4fceb0): it strncpy's a 16-char peer name (EAX) into a stack frame,
 * NUL-terminates it at +0x10 and sends it as CBuddy2 message type 0x3000
 * through the same frame writer, CommP2POwner_SendFrame (0x502500), with
 * the session object in EBX. SendBuddyNameMessage takes its type from the
 * caller; here 0x3000 is baked in (`push 0x3000` at 0x4fcef3), hence the
 * suffix. The suffix is the message type, not a payload size.
 *
 * Differences from the sibling that the name hides: the length handed to
 * the writer is 0x24 (`mov ecx,0x24` at 0x4fcef8), the whole stack buffer,
 * not 0x10, so the tail after the NUL goes out as uninitialised scratch.
 *
 * Evidence for the type: SendBuddyNameMessage's header places 0x3000/0x3001
 * in the messenger type space and says the receiving arm for them inserts
 * the name into the +0x1aa0 peer array (Vector_PushBack_12), the mirror of
 * 0x3002/0x3003, which erase. Both callers are in the 0xc042 peer
 * message flow and send it only when a flag is set: CommP2POwner_
 * SendBuddyAnswer (0x4fd802, EAX = its name argument) after its own
 * 0xc042 send to the peer succeeded, and the incoming-0xc042 arm of
 * DispatchP2PMessage (0x504ac7, EAX = param_4) after notifying the
 * handler. So it reports the peer name to the server as part of that
 * exchange. The wire meaning of 0x3000 is inferred from that header, not
 * from the reference server, which does not model the CBuddy2 type space.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * EAX RECOVERED (2026-08-25).  At 0x4fd802 the caller does `mov eax,ebx`
 * where EBX was loaded once at 0x4fd7d4, `mov ebx,[esp+0xc]` with two pushes
 * standing = E+4 = its param_2; the linear trace only reported `pop ebx`
 * because the call sits past a hoisted epilogue.  The second site passes the
 * same kind of value, its caller's param_4.
 */
#include "ghidra_types.h"


void SendBuddyNameMessage_3000(char *regEax,int regEbx)

{
  /* One contiguous 0x24-byte frame payload (the callee copies 0x24 bytes from
   * EDX): a 0x10-char name, a NUL terminator at +0x10, rest scratch.  The raw
   * port split it into local_24[16]+local_14, not guaranteed adjacent -
   * merged.  EBX (the session) is dropped by this port; its two callers load
   * it (FUN_004fd7c0 param_1, DispatchP2PMessage param_3) - forwarded as
   * regEbx. */
  char local_24 [0x24];

  _strncpy(local_24,regEax,0x10);
  local_24[0x10] = 0;
  /* opcode -> stack param, ECX=0x24 len, EDX=&local_24 buf, EBX=session;
   * orig 0x4fcef3-0x4fcf06. */
  CommP2POwner_SendFrame(0x24,(undefined4 *)local_24,0x3000,regEbx);
  return;
}

