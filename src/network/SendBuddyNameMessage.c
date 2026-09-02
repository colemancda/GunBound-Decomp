/* SendBuddyNameMessage - 0x004fceb0 in the original binary.
 *
 * Named below; still a raw/near-verbatim port of Ghidra's decompiler
 * output rather than a hand-verified reconstruction.  See src/README.md's
 * "Raw/verbatim ports" section for what that status means.
 *
 * DROPPED REGISTER RECOVERED (2026-08-27): in_EAX is the string this copies,
 * and at the sole call site (0x504aeb) it is `mov eax,edi` where edi is the
 * argument the vtable call on the line above was given -- `push edi;
 * call [edx+0x30]`, which DispatchP2PMessage.c already spells
 * `(**(code **)(**(int **)(param_3 + 0x1ab0) + 0x30))(param_4)`.  So edi is
 * param_4, the same pointer the neighbouring case arm hands to
 * FUN_004fcee0 as a `char *`.
 *
 * NAMED 2026-08-27 (was SendBuddyNameMessage).  Sends a control message whose entire
 * payload is a 16-byte peer name, with the message type chosen by the
 * caller,
 * on the CBuddy2 messenger session's connection.  All of the evidence is
 * outside this body:
 *
 * - THE CALLEE IS A FRAME WRITER, NOT A COPY.  FUN_00502500 (0x502500)
 * gates on [EBX+0x1a70] (session live) and [EBX+0x1a74] (connection),
 * then lays out a wire frame:
 * word [esp+0x10] = ECX + 4        ; total frame size
 * word [esp+0x12] = word [ebp+8]   ; its stack arg = the message type
 * rep movs ECX bytes from EDX      ; the payload
 * stamps [EBX+0x1abc] = time(0) and calls FUN_00503840, a send() loop on
 * the connection's socket at +8 ([0x5442e4] = ws2_32!send) that queues on
 * WSAEWOULDBLOCK ([0x544314] = WSAGetLastError, 0x2733).  So param_1 is a
 * MESSAGE TYPE and the 0x10 bytes copied here (ECX=0x10, EDX=&local_10 at
 * 0x4fcec8/0x4fcecd) are the whole payload.
 *
 * - THE ARGUMENT IS A NAME, established at its source and at its sink.
 * Source: FUN_00501770's relay loop builds it as local_496c from record
 * words [1..4] - 16 bytes - and writes local_495c = 0, the terminator at
 * byte 16, before handing it to DispatchP2PMessage as param_4.  (Ghidra
 * types that local `sockaddr` only because of a neighbouring recvfrom;
 * it is a 16-char NUL-terminated string.)  Sink: the 0x3003 reply arm
 * memcmps 0x10 bytes of it (0x50224f) against a 0x12-stride array walked
 * from [this+0x17b0] to [this+0x17b4] and erases the match through
 * FUN_005027d0 with the container at this+0x17ac (0x50226e).
 *
 * - THE SESSION OBJECT IS A CBuddy2.  Our EBX is DispatchP2PMessage's
 * param_3 (`mov ebx,[ebp+8]` at 0x504ad5).  FUN_00501770 - one function,
 * 0x501770-0x50249c - computes that same object as (its own this - 0x2f4)
 * both where it calls DispatchP2PMessage (`add ebx,-0x2f4` at 0x5021e3,
 * `call 0x504970` at 0x5021f3) and where it creates the window titled
 * "CBuddy2 Timer Receiving Window" (0x557b74, CreateWindowExA at
 * 0x501a53), passing that same pointer as the window's GWL_USERDATA
 * (0x501a73).  FUN_004fdaa0's WM_TIMER arm reads it back out of
 * GWL_USERDATA and compares [obj+0x1abc]+0x258 against time(0) - the
 * 600-second keepalive on the clock this send path stamps.  The two
 * neighbouring window titles, "CCommEngine Notify Window" (0x557b58) and
 * "CCommP2P<> Notify Window" (0x557b34), are created the same way inside
 * CreateCommEngineNotifyWindow and InitCommP2PNotifyWindow, so the title
 * names the owning class.
 * NOTE the offsets: relative to THIS object the window handle is +0x1ab4,
 * the handler is +0x1ab0, the timer id +0x1ab8, the clock +0x1abc, and
 * the name array +0x1aa0.  FUN_00501770 addresses the same fields off a
 * base 0x2f4 higher (+0x17c0, +0x17ac), so its literals differ by 0x2f4.
 *
 * - THE TYPE IS THE ONLY THING NOT BAKED IN.  FUN_004fda50 (vtable slot
 * +0x68 of 0x557594) is byte-for-byte this shape - strncpy 0x10, ECX=0x10,
 * EBX=this - with 0x3010 baked in, and FUN_004fd810 (slot +0x5c) is this
 * body inlined with 0x3002 baked in followed by an empty 0xc043 message
 * to the peer through FUN_004fcf10.  This helper alone takes the type
 * from its caller, which is why the name stops at "NameMessage".
 *
 * - WHAT THE CALL SITE MEANS BY IT (context, not this function's meaning).
 * The single site, 0x504aeb in DispatchP2PMessage's 0xc043 arm, fires the
 * handler's vtable slot +0x30 on the peer name and then sends
 * 0x3002{name}.  The server answers 0x3003, whose arm erases that name
 * from the +0x1aa0 array (above), while the mirrored 0x3000/0x3001 arm
 * (cmp at 0x502035) inserts one through FUN_00502750.  So 0x3002 = "drop
 * peer <name> from my session list".
 *
 * WHY NOT "Server" IN THE NAME: it would imply a transport contrast with the
 * tree's SendP2PNamedMessage (0x502590) that does not exist - that function
 * also ends in `push 0x2000 / call 0x502500` (0x502636-0x502642), i.e. the
 * same writer and the same socket.  Its "P2P" describes the message's
 * addressing, not its transport.  Nor does the class partition that way: the
 * peer-directed 0xc0xx messages go through FUN_004fcf10, which branches on
 * vtable slot +0x3c to either a direct send (FUN_004fe110) or a server relay
 * (FUN_00502650 -> FUN_00502500(0x2020)).
 *
 * SCOPE WARNING: this is the CBuddy2 messenger session, a separate
 * connection
 * with its own type space (0x1010/0x2000/0x2010/0x2011/0x2020/0x3000-0x3010/
 * 0x4000 outbound, 0xc0xx peer).  It is NOT the game server's buddy-list
 * protocol that FindBuddyRoomsForServer (0x4021b0) and BuildBuddyPanel
 * (0x509110) belong to, and the reference server's Buddy* packets
 * (BuddyAddCommand, BuddyRemoveCommand, BuddyList*) are on that other,
 * GB_OP_* protocol - so there is nothing on the server side to check these
 * type codes against.  The whole CBuddy2 API is reached only through the
 * 0x557594 vtable; tools/callsite_regs.py reports 0 call sites for its
 * members.
 *
 * ABI, still dropped by this port: `this` arrives in EBX (FUN_00502500 reads
 * it as unaff_EBX) and the only call site loads it at 0x504ad5 with
 * `mov ebx,[ebp+8]`; the name arrives in EAX (`mov eax,edi` at 0x504ae9,
 * recovered 2026-08-27); the message type is the one stack argument (ret 4).
 *
 * Raw/near-verbatim port of Ghidra's decompiler output beyond the naming -
 * not hand-verified. See src/README.md's "Raw/verbatim ports" section.
 * /
 */
#include "ghidra_types.h"


void SendBuddyNameMessage(undefined4 param_1,char *regEax,int regEbx)

{
  char *in_EAX = regEax;
  char local_10 [16];

  _strncpy(local_10,in_EAX,0x10);
  /* param_1 IS the opcode (message type) -> stack param; ECX=0x10 len,
   * EDX=&local_10 (the 0x10-byte peer name), EBX=session.  The session
   * arrives in EBX and is dropped by this port; the sole caller
   * (DispatchP2PMessage's 0xc043 arm, `mov ebx,[ebp+8]` at 0x504ad5) supplies
   * its param_3 - forwarded as regEbx.  orig 0x4fcec7-0x4fced1. */
  FUN_00502500(0x10,(undefined4 *)local_10,(ushort)param_1,regEbx);
  return;
}

