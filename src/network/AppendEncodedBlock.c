/* AppendEncodedBlock - 0x004d2570 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * unaff_EBX (the +0x84e8/+0x4cc/+0x44d0 connection-context base) arrives
 * via a dropped EBX register, not a real parameter - confirmed at the
 * State02_ServerSelect_ProcessPacket call site (orig 0x4e09cd..0x4e09fa,
 * `mov ebx, ds:0x7934ec` immediately before `call 0x4d2570`), matching the
 * same DAT_007934ec/+0x44d0 base already used throughout that caller.
 * Promoted to an explicit 2nd parameter, following the same idiom as
 * BeginServerConnect's unaff_EBX fix (src/network/BeginServerConnect.c).
 * The only real call site (State02_ServerSelect_ProcessPacket) currently
 * still drops the ECX `this`-derived param_1 arg too - left as-is here
 * since fixing that is out of scope for this function's own pass; only
 * the newly-added unaff_EBX arg is supplied at that call site.
 *
 * NEWLY DISCOVERED, NOT YET FIXED (2026-07-13): this signature is still
 * incomplete. Confirmed via objdump at 0x4d2570-0x4d259a that this
 * function actually takes TWO MORE genuine stack parameters beyond
 * `param_1`/`unaff_EBX` (`RET 0x8` pops 2 stack dwords; `mov esi,
 * [esp+0x28]` and `mov eax,[esp+0x40]` read them) - call them `arg1`
 * (loaded into ESI, still live/unclobbered) and `arg2` (loaded into EAX
 * right before the EncodeHandshakeBlock call). Both are forwarded into
 * EncodeHandshakeBlock, which independently shows the exact same gap as
 * `unaff_ESI` and `in_EAX` (see that file's own header) - `arg1` is
 * scanned there as a <=16-byte string and strncpy'd, `arg2` as a
 * null-terminated string, both hashed via Sha1Absorb before
 * EncodeCipherBlock - almost certainly the account credential strings
 * for the login handshake. The caller (State02_ServerSelect_
 * ProcessPacket.c, opcode 0x1001 branch) currently passes a 3rd,
 * unrelated argument (`&uStack_c0`) that doesn't correspond to anything
 * in this function's real signature, and its post-call code re-reads
 * `uStack_c0/bc/b8/b4/b0` as if THIS function wrote an output block
 * there - it doesn't; this function writes its own 8-dword result
 * directly into the connection's outgoing-packet buffer internally.
 * That caller-side block is dead/wrong once this is fixed properly.
 * Deferred: fixing this needs a dedicated pass across all three files
 * (this one, EncodeHandshakeBlock.c, and the ProcessPacket.c call site)
 * with confidence on what arg1/arg2 actually are before threading them
 * through - not a quick register-promotion like most of this session's
 * other fixes.
 */
#include "ghidra_types.h"


void __fastcall AppendEncodedBlock(undefined4 param_1,int unaff_EBX)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 local_20 [8];

  EncodeHandshakeBlock(*(undefined4 *)(unaff_EBX + 0x84e8),
               &DAT_0056dbf0 + *(int *)(unaff_EBX + 0x4cc) * 0x10,param_1,local_20);
  puVar2 = local_20;
  puVar3 = (undefined4 *)(*(int *)(unaff_EBX + 0x44d0) + 0x4d0 + unaff_EBX);
  for (iVar1 = 8; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  *(int *)(unaff_EBX + 0x44d0) = *(int *)(unaff_EBX + 0x44d0) + 0x20;
  return;
}

