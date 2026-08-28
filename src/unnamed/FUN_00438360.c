/* FUN_00438360 - 0x00438360 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
*
 * DROPPED REGISTER RECOVERED (2026-08-27): unaff_ESI is read before written
 * (`test esi,esi` at 0x4383ba, `cmp esi,5` just after) and the callee ends in
 * a bare `ret`, so every argument is a register one and this is a plain
 * append with nothing to re-slot.
 *
 * Six of the seven sites load a literal -- `mov esi,5`, `mov esi,6` four
 * times, and `xor esi,esi` -- each read individually off the disassembly, so
 * they need no pairing.
 *
 * BeginNewTurn's site indexes a 4-entry table MSVC materialises in the frame
 * and that Ghidra dropped entirely, along with the peek result that indexes
 * it.  The table is {1, 3, 2, 4}, and getting those values right depends on
 * the pending-push term: the four stores at 0x4d0aa8-0x4d0ac0 each sit ONE
 * push deep (the `push 0x5a9068` at 0x4d0aa3), while the
 * `mov esi,[esp+esi*4+0x18]` that reads them back at 0x4d0ae5 has none.
 * Counted without that, the table appears to start one slot late and to run
 * to index 4.
 *
 * CAVEAT on that reconstruction: the original's read is unbounded -- the
 * index is the guarded value at g_clientContext+0x45354 with no range check,
 * so out of 0..3 the original reads adjacent frame bytes.  The C array is
 * faithful for in-range indices only; out of range it is undefined behaviour
 * rather than the original's specific garbage, and MSVC will not lay the
 * array out where the original did.
 */
#include "ghidra_types.h"


void FUN_00438360(int regEsi)

{
  uint uVar1;
  char cVar2;
  void *pvVar3;
  int iVar4;
  undefined4 *puVar5;
  int unaff_ESI = regEsi;
  bool bVar6;
  
  /* guard-cell: proven.  This helper receives the effects-guard block
   * ctx+0x6a7f70 in EAX (a register arg Ghidra dropped); every call
   * site in the binary was audited 2026-08-17 and passes exactly that
   * value, so the +4 peek is the global flag, not a per-object cell. */
  cVar2 = PeekPacketChecksumBool((byte *)(g_clientContext + 0x6a7f74));
  if (cVar2 != '\0') {
    return;
  }
  iVar4 = *(int *)(*(int *)(&DAT_006a7f8c + g_clientContext) + 0x1c);
  uVar1 = *(uint *)(iVar4 + 4);
  while (uVar1 < 0x2e636) {
    if (uVar1 == 0x2e635) {
      puVar5 = *(undefined4 **)(iVar4 + 0x10);
      bVar6 = true;
      if (puVar5[2] == 0) goto LAB_004383a5;
      break;
    }
    iVar4 = *(int *)(iVar4 + 0x1c);
    uVar1 = *(uint *)(iVar4 + 4);
  }
  goto LAB_004383df;
  while( true ) {
    puVar5 = (undefined4 *)puVar5[4];
    bVar6 = puVar5[2] == 0;
    if (!bVar6) break;
LAB_004383a5:
    if (bVar6) {
      if (((puVar5[0x11] == 0) && (unaff_ESI != 0)) && (unaff_ESI < 5)) {
        puVar5[0x11] = unaff_ESI;
        return;
      }
      *(undefined4 *)(puVar5[3] + 0x10) = puVar5[4];
      *(undefined4 *)(puVar5[4] + 0xc) = puVar5[3];
      (**(code **)*puVar5)(1);
      break;
    }
  }
LAB_004383df:
  pvVar3 = operator_new(0x58);
  if (pvVar3 == (void *)0x0) {
    iVar4 = 0;
  }
  else {
    FUN_004b3b10();
  }
  *(int *)(iVar4 + 0x44) = unaff_ESI;
  RegisterActiveObject(0, 0, (undefined4 *)0);
  return;
}

