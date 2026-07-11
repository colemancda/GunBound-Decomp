/* FUN_0045cb50 - 0x0045cb50 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_0045cb50(int *param_1)

{
  int *piVar1;
  bool bVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  uint uVar11;
  undefined4 *unaff_FS_OFFSET;
  undefined1 auStack_454 [548];
  undefined1 auStack_230 [548];
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_0053c46d;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  iVar5 = *(int *)(&DAT_006a7724 + g_clientContext);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if ((iVar5 + 500 < iVar4) || (cVar3 = PeekPacketChecksumBool(), cVar3 == '\x01')) {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(0);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    goto LAB_0045d128;
  }
  iVar5 = (**(code **)(*param_1 + 0x14))();
  piVar1 = param_1 + 0x2261;
  EncodeChecksumPairSum(param_1 + 0x2cc,auStack_454,piVar1);
  uStack_4 = 0;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if ((iVar4 < iVar5) || (cVar3 = FUN_0040b300(param_1 + 0x243,0), cVar3 == '\0')) {
LAB_0045cc63:
    bVar2 = false;
  }
  else {
    cVar3 = PacketChecksumLessThan(param_1 + 0x243,*(undefined4 *)(&DAT_006a7720 + g_clientContext));
    bVar2 = true;
    if (cVar3 == '\0') goto LAB_0045cc63;
  }
  uStack_4 = 0xffffffff;
  ScrubChecksumGuard();
  if (bVar2) {
    cVar3 = PacketChecksumLessThan(piVar1,5);
    if (cVar3 == '\0') {
      iVar4 = PeekChecksumStateUnderLock(piVar1);
      QueueOutgoingPacketField(iVar5 - iVar4);
      QueueOutgoingPacketField(1);
      param_1[0x2ffb] = 0;
      cVar3 = PeekPacketChecksumBool();
      if ((cVar3 == '\x01') &&
         (((cVar3 = PacketChecksumEquals(g_clientContext + 0x45354,1), cVar3 != '\0' ||
           (cVar3 = PacketChecksumEquals(g_clientContext + 0x45354,3), cVar3 != '\0')) &&
          (iVar5 < *(int *)(&DAT_006a7724 + g_clientContext))))) goto LAB_0045cdb1;
    }
    else {
      QueueOutgoingPacketField(iVar5);
      if (param_1[9] == 0xd) {
        uVar6 = EncodeChecksumDeltaDiv(param_1 + 0x19d1,auStack_230,3);
        uStack_4 = 1;
        cVar3 = CompareChecksumPair(param_1 + 0x1a5a,uVar6);
        uStack_4 = 0xffffffff;
        ScrubChecksumGuard();
        if (cVar3 == '\0') {
          (**(code **)(*param_1 + 4))(s_normal_00552230);
        }
        else {
          (**(code **)(*param_1 + 4))(s_wnormal_00553618);
        }
      }
      QueueOutgoingPacketField(0);
      param_1[0x2ffb] = 0;
      cVar3 = PeekPacketChecksumBool();
      if (cVar3 == '\x01') {
LAB_0045cdb1:
        uVar6 = PeekChecksumStateUnderLock(&DAT_00e55ab8);
        QueueOutgoingPacketField(uVar6);
        iVar4 = PeekChecksumStateUnderLock(g_clientContext + 0x3b49c);
        iVar5 = DAT_007934e8;
        if (param_1[2] == iVar4) {
          *(undefined2 *)(DAT_007934e8 + 0x4d4) = 0x4104;
          *(undefined4 *)(iVar5 + 0x44d0) = 6;
          *(char *)(iVar5 + 0x4d6) = (char)param_1[2];
          *(int *)(iVar5 + 0x44d0) = *(int *)(iVar5 + 0x44d0) + 1;
          FUN_004d25e0();
          FUN_004d2680();
        }
        FUN_00406500(0);
        FUN_00406500(1);
        EncodeChecksumState(param_1 + 0x243);
        iVar5 = FUN_004257b0();
        QueueOutgoingPacketField(iVar5 + param_1[0x2fee]);
        FUN_00406500(0);
      }
    }
  }
  else {
    FUN_0040b030();
    FUN_0040afb0(piVar1);
    cVar3 = PeekPacketChecksumBool();
    if ((cVar3 == '\x01') &&
       ((cVar3 = PacketChecksumEquals(g_clientContext + 0x45354,1), cVar3 != '\0' ||
        (cVar3 = PacketChecksumEquals(g_clientContext + 0x45354,3), cVar3 != '\0')))) {
      PeekChecksumStateUnderLock(g_clientContext + 0x5b1ac);
      FUN_004ead90();
      PeekChecksumStateUnderLock(g_clientContext + 0x5af88);
      iVar5 = FloatToInt64();
      param_1[0x2ffb] = param_1[0x2ffb] + iVar5 * 3;
      iVar5 = PeekChecksumStateUnderLock(&DAT_00796aa0);
      AddToPacketChecksum(param_1[0x2ffb] / iVar5);
      iVar5 = PeekChecksumStateUnderLock(&DAT_00796aa0);
      AddToPacketChecksum(param_1[0x2ffb] / iVar5);
      iVar5 = PeekChecksumStateUnderLock(&DAT_00796aa0);
      param_1[0x2ffb] = param_1[0x2ffb] % iVar5;
    }
  }
  cVar3 = PeekPacketChecksumBool();
  if ((cVar3 == '\x01') &&
     ((cVar3 = PacketChecksumEquals(g_clientContext + 0x45354,1), cVar3 != '\0' ||
      (cVar3 = PacketChecksumEquals(g_clientContext + 0x45354,3), cVar3 != '\0')))) {
    iVar4 = PeekChecksumStateUnderLock(param_1 + 0x2cc);
    iVar7 = PeekChecksumStateUnderLock(param_1 + 0x243);
    iVar5 = g_clientContext;
    piVar1 = (int *)(&DAT_006a7708 + g_clientContext);
    cVar3 = PeekPacketChecksumBool();
    if ((cVar3 == '\0') && ((&DAT_006a7758)[iVar5] != '\0')) {
      if (((&DAT_006a7736)[iVar5] == '\x01') &&
         ((uVar11 = iVar4 - *(int *)(&DAT_006a7714 + iVar5) >> 0x1f,
          200 < (int)((iVar4 - *(int *)(&DAT_006a7714 + iVar5) ^ uVar11) - uVar11) ||
          (uVar11 = iVar7 - *(int *)(&DAT_006a7710 + iVar5) >> 0x1f,
          300 < (int)((iVar7 - *(int *)(&DAT_006a7710 + iVar5) ^ uVar11) - uVar11))))) {
        (&DAT_006a7736)[iVar5] = 0;
      }
      iVar9 = 400;
      if (399 < iVar7) {
        iVar9 = iVar7;
      }
      iVar8 = *(int *)(&DAT_006a7720 + iVar5) + -400;
      if ((iVar9 <= iVar8) && (iVar8 = iVar7, iVar7 < 400)) {
        iVar8 = 400;
      }
      iVar7 = -0x14;
      if (-0x15 < iVar4) {
        iVar7 = iVar4;
      }
      iVar9 = *(int *)(&DAT_006a7724 + iVar5) + -0x104;
      if ((iVar7 <= iVar9) && (iVar9 = -0x14, -0x15 < iVar4)) {
        iVar9 = iVar4;
      }
      iVar4 = *piVar1 - iVar8;
      *(int *)(&DAT_006a771c + iVar5) = iVar9;
      if (((*(int *)(&DAT_006a770c + iVar5) - iVar9) * (*(int *)(&DAT_006a770c + iVar5) - iVar9) +
           iVar4 * iVar4 < 40000) &&
         (((&DAT_006a7734)[iVar5] == '\x01' || ((&DAT_006a7f6c)[iVar5] == '\0')))) {
        *(int *)(&DAT_006a7710 + iVar5) = iVar8;
        *piVar1 = iVar8;
        *(int *)(&DAT_006a7714 + iVar5) = iVar9;
        *(int *)(&DAT_006a770c + iVar5) = iVar9;
      }
      if ((((&DAT_006a7734)[iVar5] == '\0') && ((&DAT_006a7f6c)[iVar5] == '\x01')) &&
         ((&DAT_006a7736)[iVar5] == '\0')) {
        iVar4 = *(int *)(&DAT_006a7730 + iVar5);
        iVar7 = iVar4;
        if (iVar8 <= iVar4) {
          iVar7 = iVar8;
        }
        iVar10 = *(int *)(&DAT_006a772c + iVar5);
        if ((iVar10 <= iVar7) && (iVar10 = iVar4, iVar8 <= iVar4)) {
          iVar10 = iVar8;
        }
        *(int *)(&DAT_006a7718 + iVar5) = iVar10;
      }
      if ((&DAT_006a7734)[iVar5] == '\x01') {
        *(int *)(&DAT_006a7718 + iVar5) = iVar8;
        *(int *)(&DAT_006a771c + iVar5) = iVar9;
      }
    }
  }
LAB_0045d128:
  *unaff_FS_OFFSET = local_c;
  return;
}

