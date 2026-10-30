/* FUN_005024a0 - 0x005024a0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * SIGNATURE RECOVERED (2026-10-30): the header-only CBuddy2 frame writer,
 * the payload-less twin of FUN_00502500.  The original (0x5024a0-0x5024f2):
 *   - ESI is the CBuddy2 session, read before any write (`mov al,
 *     [esi+0x1a70]` at 0x5024a1) - the session flag at +0x1a70 and the
 *     connection pointer at +0x1a74 gate the send.  Promoted to the
 *     trailing regEsi.
 *   - the one stack argument (`mov ax,[esp+8]` at 0x5024b5 after `push
 *     ecx`; `ret 4`) is the opcode, stored as the frame's second word.
 *   - it builds a 4-byte frame [len = 4 : u16][opcode : u16] in the
 *     pushed-ecx slot (0x5024bc/0x5024c3), stamps the keepalive clock
 *     [esi+0x1abc] = time(0) (0x5024e0), and calls
 *     CommConnectionSendOrQueue with ECX = 4 (0x5024d7), EDX = &frame
 *     (`lea edx,[esp+4]` at 0x5024dc, one push deep = the frame slot)
 *     and the connection [esi+0x1a74] pushed (0x5024d6).
 *   - it returns that call's AL, or AL = 0 (`xor al,al` at 0x5024ef)
 *     when the session or connection is absent.
 * The port declared neither the opcode nor ESI, read an uninitialised
 * in_EAX for the high bytes of its result, and called
 * CommConnectionSendOrQueue with only the connection.  Callers:
 * Buddy2TimerWndProc (opcode 0, ESI = the GWL_USERDATA CBuddy2 at
 * 0x4fdb11) and CommP2POwnerConnect (opcode 0x1000, `mov esi,edi` =
 * this at 0x4fd4de).
 */
#include "ghidra_types.h"


uint FUN_005024a0(ushort opcode,int regEsi)

{
  __time32_t _Var1;
  int unaff_ESI = regEsi;
  ushort frame[2];
  
  if ((*(char *)(unaff_ESI + 0x1a70) != '\0') && (*(int *)(unaff_ESI + 0x1a74) != 0)) {
    frame[0] = 4;
    frame[1] = opcode;
    _Var1 = FID_conflict___time32((__time32_t *)0x0);
    *(__time32_t *)(unaff_ESI + 0x1abc) = _Var1;
    return CommConnectionSendOrQueue(4,(char *)frame,*(int *)(unaff_ESI + 0x1a74));
  }
  return 0;
}
