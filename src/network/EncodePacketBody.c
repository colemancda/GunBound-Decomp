/* EncodePacketBody - 0x004d25e0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED REGISTER ARGUMENT: Ghidra emitted the connection-object pointer
 * as `unaff_EBX`, an uninitialized local read, instead of a real parameter.
 * Disassembly at every call site (e.g. 0x4028be-0x4028c4, 0x412d5a-0x412d62,
 * 0x446d25-0x446d2f, 0x5077ef-0x5077f1) shows `mov ebx, <conn-ptr>` (usually
 * the global DAT_007934e8, sometimes a local mirroring it) immediately
 * before `call 0x4d25e0`, with `xor ecx,ecx` also always present right
 * before the call - confirming the real fastcall arg (param_1/ECX) is
 * always literal 0 and EBX carries the actual connection pointer that
 * every caller was silently failing to pass. Fixed by promoting it to a
 * real second parameter and updating all call sites to pass their local
 * connection-object pointer.
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

void __fastcall EncodePacketBody(int param_1,int connObj)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  undefined4 local_5000 [5119];
  undefined4 uStack_4;

  uStack_4 = 0x4d25ea;
  iVar3 = *(int *)(connObj + 0x44d0) - param_1;
  EncodePacketBlocks(*(undefined4 *)(connObj + 0x84e8),*(undefined2 *)(connObj + 0x4d4),local_5000,
               0x5000);
  uVar4 = ((iVar3 + 5) / 0xc) * 0x10;
  puVar5 = local_5000;
  puVar6 = (undefined4 *)(param_1 + 0x4d6 + connObj);
  for (uVar1 = (((int)uVar4 < 0) - 1 & uVar4) >> 2; uVar1 != 0; uVar1 = uVar1 - 1) {
    *puVar6 = *puVar5;
    puVar5 = puVar5 + 1;
    puVar6 = puVar6 + 1;
  }
  for (iVar2 = 0; iVar2 != 0; iVar2 = iVar2 + -1) {
    *(undefined1 *)puVar6 = *(undefined1 *)puVar5;
    puVar5 = (undefined4 *)((int)puVar5 + 1);
    puVar6 = (undefined4 *)((int)puVar6 + 1);
  }
  *(uint *)(connObj + 0x44d0) = *(int *)(connObj + 0x44d0) + (uVar4 - (iVar3 + -6));
  return;
}
