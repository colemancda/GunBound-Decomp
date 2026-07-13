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

