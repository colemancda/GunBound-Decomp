/* FUN_004398e0 - 0x004398e0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004398e0(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4,int param_5,
                 char param_6)

{
  uint uVar1;
  int iVar2;
  char cVar3;
  int iVar4;
  undefined4 *puVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  int *piVar11;
  int iVar12;
  undefined4 *unaff_FS_OFFSET;
  bool bVar13;
  undefined4 uVar14;
  undefined4 uVar15;
  undefined4 uVar16;
  undefined4 uVar17;
  undefined1 auStack_454 [20];
  undefined4 uStack_440;
  undefined1 uStack_234;
  undefined1 auStack_230 [20];
  undefined4 uStack_21c;
  undefined1 uStack_10;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_c = *unaff_FS_OFFSET;
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053d9ba;
  *unaff_FS_OFFSET = &local_c;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if ((iVar4 == 4) || (param_6 != '\0')) {
    puVar5 = operator_new(0x3fbc);
    local_4 = 0;
    if (puVar5 == (undefined4 *)0x0) {
      puVar5 = (undefined4 *)0x0;
    }
    else {
      InitProjectile(puVar5,0x186a9);
      *puVar5 = &PTR_FUN_0055658c;
      puVar5[0xfe7] = 0xffffffff;
    }
    local_4 = 0xffffffff;
    iVar4 = *(int *)(*(int *)(&DAT_006a7f8c + g_clientContext) + 0x1c);
    uVar1 = *(uint *)(iVar4 + 4);
    while (uVar1 < 0x186ab) {
      if (uVar1 == 0x186aa) {
        piVar11 = *(int **)(iVar4 + 0x10);
        bVar13 = true;
        if (piVar11[2] == 0) goto LAB_004399d4;
        break;
      }
      iVar4 = *(int *)(iVar4 + 0x1c);
      uVar1 = *(uint *)(iVar4 + 4);
    }
  }
  goto LAB_00439d73;
  while( true ) {
    piVar11 = (int *)piVar11[4];
    bVar13 = piVar11[2] == 0;
    if (!bVar13) break;
LAB_004399d4:
    if (bVar13) {
      iVar4 = piVar11[0xf];
      iVar2 = piVar11[0xe];
      iVar6 = CalculateAngleFromDelta();
      iVar7 = FloatToInt64();
      iVar8 = FloatToInt64();
      (**(code **)(*piVar11 + 4))(&DAT_00553b90);
      piVar11[0x11] = iVar6;
      cVar3 = PeekPacketChecksumBool();
      if (cVar3 == '\0') {
        uStack_234 = 0;
        uStack_440 = 0;
        /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at
         * 0x439ad8 (`lea edi,[esp + 0x250]`): the stack-scratch cell
         * whose tail dword (uStack_440, zeroed just above) is adjacent
         * to auStack_454, and which this same file later passes as a
         * cell pointer to both SyncOutgoingChecksumField (the ELSE
         * branch's mirror-image call below) and
         * PeekChecksumStateUnderLock(auStack_454). See
         * tools/encodeoutgoingpacketfield_sites.json. */
        EncodeOutgoingPacketField(auStack_454, 0);
        local_4 = 3;
        uStack_10 = 0;
        uStack_21c = 0;
        /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at
         * 0x439afe (`lea edi,[esp + 0x2c]`): the stack-scratch cell
         * whose tail dword (uStack_21c, zeroed just above) is adjacent
         * to auStack_230, which is passed as the SyncOutgoingChecksumField
         * cell two lines below and reused as a cell pointer via
         * PeekChecksumStateUnderLock(auStack_230) in the ELSE branch.
         * See tools/encodeoutgoingpacketfield_sites.json. */
        EncodeOutgoingPacketField(auStack_230, 0);
        SUBFIELD(local_4,0,undefined1) = 4;
        SyncOutgoingChecksumField(param_2 + 0x10,auStack_230);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar9 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar12 = param_5;
        uVar10 = *(undefined4 *)(param_5 + 0x3f94);
        uVar17 = 0;
        uVar16 = 0xff;
        uVar15 = 100;
        uVar14 = 0;
        PeekPacketChecksumBool(uVar9,0,100,0xff,uVar10,0);
        FUN_00432320(*(undefined1 *)(iVar12 + 0x3c),1,1,uVar9,uVar14,uVar15,uVar16,uVar10,uVar17);
        local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),3);
        ScrubChecksumGuard();
        local_4 = 0xffffffff;
        ScrubChecksumGuard();
        iVar12 = param_5;
      }
      else {
        cVar3 = FUN_004e4fe0(&DAT_006a7708 + g_clientContext,&param_3,&param_4,2,1,1);
        iVar12 = param_5;
        if (cVar3 != '\0') {
          uStack_10 = 0;
          uStack_21c = 0;
          /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at
           * 0x439be2 (`lea edi,[esp + 0x2c]`): same esp offset/zero-init
           * pattern (uStack_21c above) as the IF branch's call to
           * auStack_230 above - the same stack-scratch cell, also passed
           * to PeekChecksumStateUnderLock(auStack_230) below. See
           * tools/encodeoutgoingpacketfield_sites.json. */
          EncodeOutgoingPacketField(auStack_230, 0);
          local_4 = 1;
          uStack_234 = 0;
          uStack_440 = 0;
          /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at
           * 0x439c0e (`lea edi,[esp + 0x250]`): same esp offset/zero-init
           * pattern (uStack_440 above) as the IF branch's call to
           * auStack_454 above; this branch's own SyncOutgoingChecksumField
           * call below passes auStack_454 as the cell pointer directly.
           * See tools/encodeoutgoingpacketfield_sites.json. */
          EncodeOutgoingPacketField(auStack_454, 0);
          SUBFIELD(local_4,0,undefined1) = 2;
          QueueOutgoingPacketField(param_3);
          QueueOutgoingPacketField(param_4);
          SyncOutgoingChecksumField(param_2 + 0x10,auStack_454);
          iVar12 = param_5;
          uVar10 = *(undefined4 *)(param_5 + 0x3f94);
          uVar17 = 0;
          uVar16 = 0xff;
          uVar15 = 100;
          uVar14 = 0;
          PeekChecksumStateUnderLock(auStack_454);
          uVar9 = PeekChecksumStateUnderLock(auStack_230);
          PeekPacketChecksumBool(uVar9,uVar14,uVar15,uVar16,uVar10,uVar17);
          FUN_00432320(*(undefined1 *)(iVar12 + 0x3c),1,1,uVar9,uVar14,uVar15,uVar16,uVar10,uVar17);
          local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),1);
          ScrubChecksumGuard();
          local_4 = 0xffffffff;
          ScrubChecksumGuard();
        }
      }
      puVar5[0xfea] = iVar2 - iVar7;
      puVar5[0xfeb] = iVar4 - iVar8;
      puVar5[0xfed] = param_4;
      puVar5[0xfec] = param_3;
      puVar5[0xfee] = iVar6;
      uVar10 = FUN_004ac4d0();
      puVar5[0xfe9] = uVar10;
      iVar4 = FUN_004ac400();
      puVar5[0xfe8] = iVar4 * *(int *)(iVar12 + 0x3f94);
      cVar3 = PeekPacketChecksumBool();
      if (cVar3 == '\0') {
        RegisterActiveObject(0, 0, (undefined4 *)0);
      }
      else {
        (**(code **)*puVar5)(1);
      }
      break;
    }
  }
LAB_00439d73:
  *unaff_FS_OFFSET = local_c;
  return;
}

