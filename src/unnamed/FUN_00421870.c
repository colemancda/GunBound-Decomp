/* FUN_00421870 - 0x00421870 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * ARGUMENTS RE-SLOTTED AND EBX RECOVERED (2026-08-27).  All six call sites
 * passed NOTHING to this two-parameter __fastcall, so param_1 and param_2
 * were reading stale ECX/EDX and unaff_EBX was an uninitialised destination.
 *
 * Every site sets the same three registers in the same order: `lea ebx,
 * [esp+0x94 or 0x114]`, `mov ecx,1` (twice via edi/esi), `lea edx,
 * [esp+0x134]`.  So param_1 is 1 and param_2 is one address at all six.
 *
 * The frame is anchored by this caller's own strcpy: the C writes through
 * `(int)local_ff + (-1 - (int)param_2)`, i.e. base E-0x100, and the binary's
 * matching `lea edx,[esp+0x12c]` fixes esp at E-0x22c.  That makes the call
 * sites' [esp+0x134] E-0xf8 -- eight bytes into the length-prefixed command
 * buffer whose length byte is local_100 -- and [esp+0x94] / [esp+0x114]
 * E-0x198 / E-0x118, which land INSIDE local_1a0[116] and local_120[32] at
 * offset 8 rather than on any declared local of their own.
 *
 * Only one of the six writes to the local_120 buffer, and the source names it
 * without any ordering assumption: that site is followed by `_atol(local_120)`
 * while the other five sit beside local_1a0 uses -- matching the single
 * binary site that uses `lea ebx,[esp+0x114]` instead of `+0x94`. */
#include "ghidra_types.h"


void __fastcall FUN_00421870(int param_1,int param_2,undefined4 *regEbx)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  undefined4 *unaff_EBX = regEbx;
  undefined4 *puVar4;
  undefined4 *puVar5;
  
  iVar1 = 0;
  for (; param_1 != 0; param_1 = param_1 + -1) {
    iVar1 = iVar1 + 1 + (int)*(char *)(iVar1 + param_2);
  }
  if (unaff_EBX != (undefined4 *)0x0) {
    if (*(char *)(iVar1 + param_2) < '\0') {
      uVar2 = 0;
    }
    else {
      uVar2 = (uint)*(char *)(iVar1 + param_2);
    }
    puVar4 = (undefined4 *)(iVar1 + 1 + param_2);
    puVar5 = unaff_EBX;
    for (uVar3 = uVar2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
      *puVar5 = *puVar4;
      puVar4 = puVar4 + 1;
      puVar5 = puVar5 + 1;
    }
    for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
      *(undefined1 *)puVar5 = *(undefined1 *)puVar4;
      puVar4 = (undefined4 *)((int)puVar4 + 1);
      puVar5 = (undefined4 *)((int)puVar5 + 1);
    }
    *(undefined1 *)((int)*(char *)(iVar1 + param_2) + (int)unaff_EBX) = 0;
  }
  return;
}

