/* RequestP2PPeerByName - 0x00504880 in the original binary.
 *
 * NAMED 2026-09-01, LIKELY rather than certain.  Slot 1 (+4, 0x5575b0)
 * of vtable 0x5575ac, which ConstructCommP2POwner installs on the
 * owner+0x2c object (`lea edi,[ebp+0x2c]` at 0x4fd11c, `mov
 * [edi],0x5575ac` at 0x4fd141), with zero direct callers image-wide.
 * `this` is that +0x2c object, so `lea esi,[ecx-0x2c]` at 0x504889
 * recovers the owner.  If the 16-char
 * name is already on the session's peer roster (HasP2PSessionPeer over
 * session = this - 0x2c) it returns false without sending; otherwise it
 * sends messenger message 0x3010 whose whole payload is the strncpy'd
 * 0x10-byte name, through FUN_00502500 - the frame writer on the
 * messenger connection that SendBuddyNameMessage's header pinned down
 * (EBX = session, gates on +0x1a70/+0x1a74, stamps the +0x1abc clock).
 *
 * What is proven is exactly that: "0x3010{peer name}, sent only for
 * peers the session does not know".  The 0x3010 type itself has no
 * inbound arm in CommP2POwner_ProcessPacket's dispatcher (the CBuddy2 type space is
 * private to the messenger; the reference server has nothing to check
 * it against), so "Request...ByName" - ask the messenger server about a
 * peer we have no entry for - is the reading the guard shape supports,
 * not a decoded semantic.  Note FUN_004fda50 (slot +0x68, this =
 * session) sends the identical 0x3010{name} frame unconditionally;
 * whatever finally decodes 0x3010 should rename both together.  The
 * neighbouring slots frame this one: slot 0 of 0x5575ac (0x504800,
 * unported) sends a message to a named peer choosing direct/relay via
 * HasP2PPeerRecord, slot 2 (0x5048d0, unported) registers an id->nick
 * pair and dispatches locally.  The receive pump 0x501770 just before it
 * is the one slot of vtable 0x5575a8, the one installed at owner+0x2f4
 * (0x4fd147).
 *
 * CORRECTED (2026-10-30): this header used to call it slot 7 of the
 * owner+0x2f4 vtable. That count started at 0x557594, the base-class
 * vtable briefly stored at +0x2f4 (0x4fd128) and then replaced by
 * 0x5575a8. 0x557594's own slots are 2 __purecall and 3 no-ops, and
 * the words after them belong to the next vtables.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


uint RequestP2PPeerByName(char *param_1,int regEcx)

{
  uint uVar1;
  char local_10 [16];
  
  uVar1 = HasP2PSessionPeer(param_1,regEcx - 0x2c);
  if ((char)uVar1 != '\0') {
    return uVar1 & 0xffffff00;
  }
  _strncpy(local_10,param_1,0x10);
  /* opcode -> stack param, ECX=0x10 len, EDX=&local_10 buf, EBX=session
   * (regEcx-0x2c); orig 0x5048b1-0x5048c1. */
  uVar1 = FUN_00502500(0x10,(undefined4 *)local_10,0x3010,regEcx + -0x2c);
  return uVar1;
}

