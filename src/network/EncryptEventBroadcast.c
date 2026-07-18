/* EncryptEventBroadcast - 0x004e6df0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void EncryptEventBroadcast(void)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  int unaff_EBX;
  undefined4 *puVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined4 local_400 [256];
  
  DAT_0056dc97 = *(undefined1 *)(unaff_EBX + 0x44df4);
  DAT_0056dc95 = *(undefined1 *)(unaff_EBX + 0x44dee);
  DAT_0056dc9a = *(undefined1 *)(unaff_EBX + 0x44def);
  iVar3 = 0x21;
  cVar1 = *(char *)(unaff_EBX + 0x44dee) + *(char *)(unaff_EBX + 0x44def) +
          *(char *)(unaff_EBX + 0x44df4) + -0x34;
  if (0x21 < *(int *)(unaff_EBX + 0x44fec)) {
    do {
      cVar1 = cVar1 + *(char *)(unaff_EBX + 0x44dec + iVar3);
      iVar3 = iVar3 + 1;
    } while (iVar3 < *(int *)(unaff_EBX + 0x44fec));
  }
  *(char *)(unaff_EBX + 0x44df0) = cVar1;
  *(undefined1 *)(unaff_EBX + 0x44ff4) = 1;
  /* RECOVERED (2026-07-18), orig 0x4e6e4e-0x4e6e6d: key = ECX = the 16 bytes
   * at 0x56dc90, EDX=0x10, EDI = ebx+0x44ff8 (the schedule inside the event/
   * replay context). NOTE that key region is split into per-byte DAT_ globals
   * in this port, so only its first byte is guaranteed contiguous - not on the
   * login/lobby path, flagged for the same coalescing treatment if exercised. */
  /* NOT ENABLED: the schedule context is `unaff_EBX + 0x44ff8`, and unaff_EBX
   * is itself a still-unrecovered dropped register here - with real args
   * RijndaelSetKey now EXPANDS a ~0x210-byte schedule into that pointer, which
   * on a garbage base corrupts memory (observed: a wild write killing the
   * Logo2->Title transition). Before the arg recovery this call always failed
   * the length check and wrote nothing, so skipping it preserves exactly the
   * previous behaviour without the corruption. Re-enable once unaff_EBX is
   * recovered from this function's callers. */
  iVar3 = *(int *)(unaff_EBX + 0x44fec) + -0x12;
  iVar5 = 0;
  if (0 < (int)(iVar3 + (iVar3 >> 0x1f & 0xfU)) >> 4) {
    puVar4 = local_400;
    do {
      EncodeCipherBlock(puVar4,unaff_EBX + 0x44ff8);
      iVar3 = *(int *)(unaff_EBX + 0x44fec) + -0x12;
      iVar5 = iVar5 + 1;
      puVar4 = puVar4 + 4;
    } while (iVar5 < (int)(iVar3 + (iVar3 >> 0x1f & 0xfU)) >> 4);
  }
  iVar3 = *(int *)(unaff_EBX + 0x44fec) + -0x12;
  uVar2 = ((int)(iVar3 + (iVar3 >> 0x1f & 0xfU)) >> 4) * 0x10;
  *(uint *)(unaff_EBX + 0x44fec) = uVar2 + 0x21;
  puVar4 = local_400;
  puVar6 = (undefined4 *)(unaff_EBX + 0x44e0d);
  for (uVar2 = (((int)uVar2 < 0) - 1 & uVar2) >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
    *puVar6 = *puVar4;
    puVar4 = puVar4 + 1;
    puVar6 = puVar6 + 1;
  }
  for (iVar3 = 0; iVar3 != 0; iVar3 = iVar3 + -1) {
    *(undefined1 *)puVar6 = *(undefined1 *)puVar4;
    puVar4 = (undefined4 *)((int)puVar4 + 1);
    puVar6 = (undefined4 *)((int)puVar6 + 1);
  }
  return;
}

