/* BeginUdpSessionProbe - 0x004e76d0 in the original binary.
 *
 * Arms and fires the post-login UDP echo probe.  Stores the game server's
 * address and port in the broadcast/P2P context, copies the 4-byte login
 * session id and the local account name in beside them, sets the attempt
 * counter +0x45208 to 7, and sends the session id as one 4-byte datagram to
 * that address under the context's +0x17c critical section.  The UDP worker
 * thread (FUN_004e6770) re-sends the identical datagram every 2 s while the
 * counter is positive and posts failure event 4 if all 7 attempts go
 * unanswered; the receive path (FUN_004e6160) cancels it -- counter := -1,
 * success event 3 -- when the server echoes those same 4 bytes back.
 *
 * NAME EVIDENCE.  The sole call site (0x4e0371) is the
 * GB_OP_AUTHENTICATION_RESPONSE *success* branch of
 * State02_ServerSelect_ProcessPacket, and it identifies every argument:
 *
 *   - The destination is the GAME SERVER, not a peer.  ECX/EDX are read out
 *     of the sockaddr the line above fills with
 *     `getpeername(<the game connection's socket>, &sStack_d0, ...)`, so this
 *     probes the server we are already connected to.  The per-peer tables
 *     (+0x18/+0x38 addresses, +0x58/+0x68 ports) are untouched: it is not a
 *     NAT punch-through and not a P2P handshake.
 *   - The 4 bytes sent are the LOGIN SESSION ID.  param_3 points at
 *     packet payload+2, and the reference server decodes
 *     AuthenticationResponse.UserData as `session: UInt32` (big-endian) then
 *     `username` -- GunBound/Sources/GunBoundProtocol/Packets/
 *     AuthenticationResponse.swift:158-160, the same Swift source
 *     include/opcodes.h is generated from.  regEax is
 *     g_clientContext+0x23330, the 12-byte `username` this same handler
 *     copied out of payload+6 thirty instructions earlier.
 *   - "Probe", not "keepalive": the keepalive in this subsystem is the
 *     separate 25-second QueueBroadcastEvent(0x4fff/0x8fff) branch of the
 *     same worker loop (FUN_004e6770.c:63-72).  This one fires once at login
 *     and stops on the first echo.
 *   - "Begin", not "Send": arming +0x45208 = 7 is the half the worker thread
 *     and the receive path key off; the raw sender is already named
 *     SendUdpDatagram.
 *
 * The name copied to +0x4521b is stored and never read -- a whole-image scan
 * for the disp32 0x4521b finds no other reference.
 *
 * DROPPED REGISTERS RECOVERED AND ARGUMENTS RE-SLOTTED (2026-08-26).  The
 * source passed ONE argument to a three-parameter __fastcall, and in the
 * wrong slot: `&uStack_f0` is the PUSHED argument, i.e. sessionId, while
 * serverAddr and serverPort arrive in ECX and EDX.
 *
 * The body says what they are -- serverAddr is stored to +0x4520c and
 * serverPort to +0x45210, and SendUdpDatagram is then called with exactly
 * those two as its address and port.  The call site agrees: ECX is
 * `mov ecx,[esp+0x38]` with one push pending and EDX is `mov edx,[esp+0x32]`
 * with none, which under the caller's -0x100 frame are -0xcc and -0xce --
 * both INSIDE its `sockaddr sStack_d0` (-0xd0, 16 bytes).  As sockaddr fields
 * those are sa_data+2 (the four address bytes) and sa_data+0 (the two port
 * bytes).
 *
 * regEsi is &g_replayContext, the name BroadcastQueuedEvent.c already gives
 * this global; regEax is set at 0x4e033b and not rewritten before the call.
 */
#include "ghidra_types.h"


void __fastcall BeginUdpSessionProbe(undefined4 serverAddr,int serverPort,undefined4 *sessionId,
                                     char *localUserName,int replayCtx)

{
  char cVar1;
  int iVar2;
  
  *(undefined4 *)(replayCtx + 0x4520c) = serverAddr;
  *(undefined2 *)(replayCtx + 0x45210) = serverPort;
  *(undefined4 *)(replayCtx + 0x45212) = *sessionId;
  iVar2 = (replayCtx + 0x4521b) - (int)localUserName;
  do {
    cVar1 = *localUserName;
    localUserName[iVar2] = cVar1;
    localUserName = localUserName + 1;
  } while (cVar1 != '\0');
  *(undefined4 *)(replayCtx + 0x45208) = 7;
  EnterCriticalSection((LPCRITICAL_SECTION)(replayCtx + 0x17c));
  SendUdpDatagram(*(int *)(replayCtx + 0x4520c),(int)*(short *)(replayCtx + 0x45210),
                  (char *)(replayCtx + 0x45212),4,replayCtx);
  LeaveCriticalSection((LPCRITICAL_SECTION)(replayCtx + 0x17c));
  return;
}
