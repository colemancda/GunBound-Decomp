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
 * DROPPED-REGISTER FIX (2026-07-17): this function takes TWO MORE genuine
 * stack parameters beyond `param_1`/`unaff_EBX`, confirmed via disassembly
 * at 0x4d2570-0x4d259a (`RET 0x8` pops 2 stack dwords; `mov esi,[esp+0x28]`
 * reads the first at entry, `mov eax,[esp+0x40]` the second right before
 * the call). Both are forwarded UNCHANGED into EncodeHandshakeBlock via the
 * ESI/EAX registers it reads (see that file's header) - `credKey` (ESI) is
 * scanned there as a <=16-byte string and strncpy'd, `credStr` (EAX) as a
 * null-terminated string, both SHA1-absorbed - the account credential/
 * system-info buffers for the login handshake. Promoted to explicit
 * trailing parameters here and threaded from the caller.
 *
 * The sole caller is State02_ServerSelect_ProcessPacket's opcode-0x1001
 * branch. Its argument mapping (from orig 0x4e09b7-0x4e09fa):
 *   ECX/param_1  = *(int *)payload            (the server's 4-byte nonce;
 *                  becomes EncodeHandshakeBlock's hashed param_3)
 *   EBX/unaff_EBX= DAT_007934ec               (the connection context)
 *   ESI/credKey  = systemInfoBlob2            (BuildSystemInfoBlob output 2)
 *   EAX/credStr  = auStack_a0                  (BuildSystemInfoBlob output 1)
 * The post-call block the caller copies into the packet is auStack_a0's
 * first 0x14 bytes (orig reads [esp+0x40..0x50] = auStack_a0), NOT the
 * uStack_c0 slot Ghidra split off - fixed at that call site.
 */
#include "ghidra_types.h"


void __fastcall AppendEncodedBlock(undefined4 param_1,int unaff_EBX,char *credKey,char *credStr)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 local_20 [8];

  EncodeHandshakeBlock(*(undefined4 *)(unaff_EBX + 0x84e8),
               &DAT_0056dbf0 + *(int *)(unaff_EBX + 0x4cc) * 0x10,param_1,(int)local_20,
               credKey,credStr);
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

