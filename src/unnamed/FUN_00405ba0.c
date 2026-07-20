/* FUN_00405ba0 - 0x00405ba0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * FIXED (2026-07-13), three bugs:
 *
 * 1) `unaff_EBX` is a dropped register, not garbage - confirmed via
 *    objdump that it arrives unchanged in EBX with no stack argument
 *    (`ret` with no operand) at entry (0x405ba0: `mov al,[ebx+0x2009]`
 *    is the very first instruction). All 8 call sites across src/
 *    (each gated on `g_directLinkConnection != 0`) pass that same global, never
 *    anything else - hardcoded here rather than threading a parameter
 *    through 8 call sites for an invariant value, same approach as
 *    InvokeWidget's registry base.
 *
 * 2) The `SendSocketData(...)` call at the end only passed 2 of that
 *    function's 3 real parameters, and passed the WRONG one first.
 *    Confirmed via objdump at 0x405da6-0x405db3: `mov ecx,ebx` (the
 *    packet-buffer object itself -> SendSocketData's real param_1, the
 *    raw bytes to send) / `push [ebx+0x2004]` (the owning connection
 *    object -> param_2) / `push eax` (the computed length -> param_3).
 *    The raw port had this backwards and short by one argument.
 *
 * 3) `local_88`/`local_84`/the synthetic `stack0xffffff77` were three
 *    separately-declared locals standing in for ONE real ~128-byte
 *    stack buffer (objdump: `lea edi,[esp+8]; mov ecx,0x20; rep stosd`
 *    zero-fills 0x20 dwords starting where `local_88` lives, and both
 *    branches that build the outgoing message text write into that
 *    same span before the shared tail reads it back from `&local_88`)
 *    - same "must be contiguous, isn't guaranteed to be" bug class as
 *      State05_Logo1_OnExit.c/AppendPersistentButtonName.c. Fixed with
 *      one real array.
 */
#include "ghidra_types.h"


void FUN_00405ba0(void)

{
  char cVar1;
  undefined2 uVar2;
  undefined2 uVar3;
  undefined2 uVar4;
  undefined4 uVar5;
  char *pcVar6;
  char *pcVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  undefined4 *puVar13;
  int iVar14;
  undefined2 *pktBuf;
  char *pcVar15;
  char *pcVar16;
  undefined4 *puVar17;
  char msgBuf [128];

  pktBuf = (undefined2 *)g_directLinkConnection;
  iVar14 = g_clientContext;
  if (*(char *)((int)pktBuf + 0x2009) == '\0') {
    return;
  }
  uVar2 = *(undefined2 *)(g_clientContext + 0x44e60);
  uVar3 = *(undefined2 *)(g_clientContext + 0x3f804);
  uVar4 = *(undefined2 *)(g_clientContext + 0x41340);
  uVar5 = CONCAT22(uVar4,uVar3);
  *(undefined4 *)pktBuf = 4;
  pktBuf[1] = 0xa510;
  SUBFIELD(uVar5,2,undefined1) = (byte)uVar4;
  SUBFIELD(uVar5,0,undefined1) = (byte)uVar3;
  *(undefined4 *)(pktBuf + 2) = uVar5;
  pktBuf[4] = uVar2;
  iVar8 = *(int *)(pktBuf + 0x1000);
  *(int *)(pktBuf + 0x1000) = iVar8 + 6;
  *(ushort *)(iVar8 + 6 + (int)pktBuf) =
       (ushort)(byte)((byte)((ushort)uVar2 >> 8) ^ 0x6b) + (ushort)(byte)((byte)uVar2 ^ 0x69) +
       (ushort)(byte)((byte)((ushort)uVar4 >> 8) ^ 0x73) + (ushort)(SUBFIELD(uVar5,2,undefined1) ^ 0x6d) +
       (ushort)(byte)((byte)((ushort)uVar3 >> 8) ^ 0x6f) + (ushort)((byte)uVar5 ^ 99);
  iVar8 = *(int *)(pktBuf + 0x1000);
  *(int *)(pktBuf + 0x1000) = iVar8 + 2;
  puVar13 = (undefined4 *)msgBuf;
  for (iVar9 = 0x20; iVar9 != 0; iVar9 = iVar9 + -1) {
    *puVar13 = 0;
    puVar13 = puVar13 + 1;
  }
  puVar13 = (undefined4 *)(iVar8 + 2 + (int)pktBuf);
  *puVar13 = *(undefined4 *)msgBuf;
  puVar13[1] = *(undefined4 *)(msgBuf + 4);
  *(int *)(pktBuf + 0x1000) = *(int *)(pktBuf + 0x1000) + 8;
  iVar8 = *(int *)(iVar14 + 0x3f804);
  if (iVar8 == -1) {
    pcVar6 = (char *)GetLocalizedString(&g_localizedStringTable,0x334);
    pcVar7 = pcVar6;
    do {
      cVar1 = *pcVar7;
      pcVar7 = pcVar7 + 1;
    } while (cVar1 != '\0');
    pcVar16 = msgBuf;
    do {
      pcVar15 = pcVar16 + 1;
      pcVar16 = pcVar16 + 1;
    } while (*pcVar15 != '\0');
    pcVar15 = pcVar6;
    for (uVar10 = (uint)((int)pcVar7 - (int)pcVar6) >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
      *(undefined4 *)pcVar16 = *(undefined4 *)pcVar15;
      pcVar15 = pcVar15 + 4;
      pcVar16 = pcVar16 + 4;
    }
    for (uVar10 = (int)pcVar7 - (int)pcVar6 & 3; uVar10 != 0; uVar10 = uVar10 - 1) {
      *pcVar16 = *pcVar15;
      pcVar15 = pcVar15 + 1;
      pcVar16 = pcVar16 + 1;
    }
  }
  else {
    iVar9 = *(int *)(iVar14 + 0x41340);
    if (iVar9 == -1) {
      iVar9 = *(int *)(iVar14 + 0x44e60) + 1;
      iVar8 = iVar8 + 1;
      pcVar7 = (char *)GetLocalizedString(&g_localizedStringTable,0x335);
    }
    else {
      if (iVar9 == -2) {
        iVar8 = iVar8 + 1;
        pcVar7 = (char *)GetLocalizedString(&g_localizedStringTable,0x336);
        _sprintf(msgBuf,pcVar7,iVar8);
        goto LAB_00405d5e;
      }
      iVar9 = iVar9 + 1;
      iVar8 = iVar8 + 1;
      pcVar7 = (char *)GetLocalizedString(&g_localizedStringTable,0x337);
    }
    _sprintf(msgBuf,pcVar7,iVar8,iVar9);
  }
LAB_00405d5e:
  pcVar7 = msgBuf;
  do {
    cVar1 = *pcVar7;
    pcVar7 = pcVar7 + 1;
  } while (cVar1 != '\0');
  uVar10 = (int)pcVar7 - ((int)msgBuf + 1);
  uVar11 = ((int)uVar10 < 0) - 1 & uVar10;
  puVar13 = (undefined4 *)msgBuf;
  puVar17 = (undefined4 *)(*(int *)(pktBuf + 0x1000) + (int)pktBuf);
  for (uVar12 = uVar11 >> 2; uVar12 != 0; uVar12 = uVar12 - 1) {
    *puVar17 = *puVar13;
    puVar13 = puVar13 + 1;
    puVar17 = puVar17 + 1;
  }
  for (uVar11 = uVar11 & 3; uVar11 != 0; uVar11 = uVar11 - 1) {
    *(undefined1 *)puVar17 = *(undefined1 *)puVar13;
    puVar13 = (undefined4 *)((int)puVar13 + 1);
    puVar17 = (undefined4 *)((int)puVar17 + 1);
  }
  iVar14 = *(int *)(pktBuf + 0x1000) + uVar10;
  *(int *)(pktBuf + 0x1000) = iVar14;
  *pktBuf = (short)iVar14;
  SendSocketData((char *)pktBuf,*(undefined4 *)((char *)pktBuf + 0x2004),iVar14);
  return;
}
