/* FUN_00434fc0 - 0x00434fc0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __thiscall FUN_00434fc0(undefined4 param_1,undefined4 param_2,int param_3)

{
  int *piVar1;
  char cVar2;
  char *pcVar3;
  void *pvVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  byte bVar12;
  uint uVar13;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053ca9b;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  cVar2 = PeekPacketChecksumBool(param_1);
  if (cVar2 == '\0') {
    if ((-1 < param_3) && (param_3 < *(int *)(&g_nCameraBoundX + g_clientContext))) {
      pcVar3 = (char *)(*(int *)(&DAT_006a773c + g_clientContext) + param_3);
      iVar11 = 0;
      if (0 < *(int *)(&g_nCameraBoundY + g_clientContext)) {
        do {
          if (*pcVar3 != '\0') goto LAB_00435034;
          pcVar3 = pcVar3 + *(int *)(&g_nCameraBoundX + g_clientContext);
          iVar11 = iVar11 + 1;
        } while (iVar11 < *(int *)(&g_nCameraBoundY + g_clientContext));
      }
    }
    iVar11 = 10000;
LAB_00435034:
    iVar9 = iVar11;
    FUN_00436070(&DAT_006a7f70 + g_clientContext,param_3,iVar11);
    FUN_0043af40(param_3,iVar11,0,0x1e,0x1e,0x1e,0xff);
    pvVar4 = operator_new(0x3fa0);
    local_4 = 0;
    if (pvVar4 == (void *)0x0) {
      iVar11 = 0;
    }
    else {
      iVar11 = FUN_004aa830();
    }
    local_4 = 0xffffffff;
    *(undefined4 *)(iVar11 + 0x18) = 0xffffffff;
    *(undefined4 *)(iVar11 + 0x3894) = 0x1f4f;
    *(undefined1 *)(iVar11 + 0x3c) = 0xff;
    *(undefined4 *)(iVar11 + 0x38) = 0xffffffff;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(param_3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar5 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar5);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(iVar9);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(param_3 << 8);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(iVar9 << 8);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(0);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar5 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar5);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar5 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar5);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar5 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar5);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar5 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar5);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = _rand();
    *(char *)(iVar11 + 0xf3f) = (char)iVar6;
    iVar6 = _rand();
    *(byte *)(iVar11 + 0xf40) = (byte)iVar6;
    bVar12 = *(byte *)(iVar11 + 0xf3f) & 7;
    bVar12 = ~('\x01' << bVar12) & (byte)iVar6 | '\0' << bVar12;
    *(byte *)(iVar11 + 0xf40) = bVar12;
    *(byte *)(iVar11 + 0xf41) = *(byte *)(iVar11 + 0xf3f) + bVar12 + -0x34;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar5 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(uVar5);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar5 = PeekPacketChecksumState();
    EncodeOutgoingPacketField(uVar5);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    *(undefined4 *)(iVar11 + 0x3898) = SUBFIELD(s_lightningflame_00553c58,0,undefined4);
    *(undefined4 *)(iVar11 + 0x389c) = SUBFIELD(s_lightningflame_00553c58,4,undefined4);
    *(undefined4 *)(iVar11 + 0x38a0) = SUBFIELD(s_lightningflame_00553c58,8,undefined4);
    *(undefined2 *)(iVar11 + 0x38a4) = SUBFIELD(s_lightningflame_00553c58,12,undefined2);
    *(char *)(iVar11 + 0x38a6) = s_lightningflame_00553c58[0xe];
    *(undefined4 *)(iVar11 + 0x3813) = SUBFIELD(s_lightningblast_xes_00553c44,0,undefined4);
    *(undefined4 *)(iVar11 + 0x3817) = SUBFIELD(s_lightningblast_xes_00553c44,4,undefined4);
    *(undefined4 *)(iVar11 + 0x381b) = SUBFIELD(s_lightningblast_xes_00553c44,8,undefined4);
    *(undefined4 *)(iVar11 + 0x381f) = SUBFIELD(s_lightningblast_xes_00553c44,12,undefined4);
    *(undefined2 *)(iVar11 + 0x3823) = SUBFIELD(s_lightningblast_xes_00553c44,16,undefined2);
    *(char *)(iVar11 + 0x3825) = s_lightningblast_xes_00553c44[0x12];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(0x46);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(0x46);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(0x46);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(0x1e);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(0x1e);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(0x1e);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(0x6e);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(0x6e);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(0x6e);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar5 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(uVar5);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = _rand();
    *(char *)(iVar11 + 0x33bc) = (char)iVar6;
    iVar6 = _rand();
    *(byte *)(iVar11 + 0x33bd) = (byte)iVar6;
    bVar12 = *(byte *)(iVar11 + 0x33bc) & 7;
    bVar12 = ~('\x01' << bVar12) & (byte)iVar6 | '\0' << bVar12;
    *(byte *)(iVar11 + 0x33bd) = bVar12;
    *(byte *)(iVar11 + 0x33be) = *(byte *)(iVar11 + 0x33bc) + bVar12 + -0x34;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = _rand();
    *(char *)(iVar11 + 0x33bf) = (char)iVar6;
    iVar6 = _rand();
    *(byte *)(iVar11 + 0x33c0) = (byte)iVar6;
    bVar12 = '\x01' << (*(byte *)(iVar11 + 0x33bf) & 7);
    bVar12 = ~bVar12 & (byte)iVar6 | bVar12;
    *(byte *)(iVar11 + 0x33c0) = bVar12;
    *(byte *)(iVar11 + 0x33c1) = *(byte *)(iVar11 + 0x33bf) + bVar12 + -0x34;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = _rand();
    *(char *)(iVar11 + 0x33c2) = (char)iVar6;
    iVar6 = _rand();
    *(byte *)(iVar11 + 0x33c3) = (byte)iVar6;
    bVar12 = *(byte *)(iVar11 + 0x33c2) & 7;
    bVar12 = ~('\x01' << bVar12) & (byte)iVar6 | '\0' << bVar12;
    *(byte *)(iVar11 + 0x33c3) = bVar12;
    *(byte *)(iVar11 + 0x33c4) = *(byte *)(iVar11 + 0x33c2) + bVar12 + -0x34;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar6 = _rand();
    *(char *)(iVar11 + 0x33c5) = (char)iVar6;
    iVar6 = _rand();
    *(byte *)(iVar11 + 0x33c6) = (byte)iVar6;
    bVar12 = *(byte *)(iVar11 + 0x33c5) & 7;
    bVar12 = ~('\x01' << bVar12) & (byte)iVar6 | '\0' << bVar12;
    *(byte *)(iVar11 + 0x33c6) = bVar12;
    *(byte *)(iVar11 + 0x33c7) = *(byte *)(iVar11 + 0x33c5) + bVar12 + -0x34;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(0x1e);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(0x1e);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    RegisterActiveObject();
    iVar11 = g_clientContext;
    piVar1 = (int *)(&DAT_006a7708 + g_clientContext);
    cVar2 = PeekPacketChecksumBool();
    if ((cVar2 == '\0') && ((&DAT_006a7758)[iVar11] != '\0')) {
      if (((&DAT_006a7736)[iVar11] == '\x01') &&
         ((uVar13 = iVar9 - *(int *)(&g_nCameraY + iVar11) >> 0x1f,
          200 < (int)((iVar9 - *(int *)(&g_nCameraY + iVar11) ^ uVar13) - uVar13) ||
          (uVar13 = param_3 - *(int *)(&g_nCameraX + iVar11) >> 0x1f,
          300 < (int)((param_3 - *(int *)(&g_nCameraX + iVar11) ^ uVar13) - uVar13))))) {
        (&DAT_006a7736)[iVar11] = 0;
      }
      iVar6 = 400;
      if (399 < param_3) {
        iVar6 = param_3;
      }
      iVar7 = *(int *)(&g_nCameraBoundX + iVar11) + -400;
      if ((iVar6 <= iVar7) && (iVar7 = param_3, param_3 < 400)) {
        iVar7 = 400;
      }
      iVar6 = -0x14;
      if (-0x15 < iVar9) {
        iVar6 = iVar9;
      }
      iVar8 = *(int *)(&g_nCameraBoundY + iVar11) + -0x104;
      if ((iVar6 <= iVar8) && (iVar8 = iVar9, iVar9 < -0x14)) {
        iVar8 = -0x14;
      }
      iVar9 = *piVar1 - iVar7;
      *(int *)(&g_nCameraScrollY + iVar11) = iVar8;
      if (((*(int *)(&DAT_006a770c + iVar11) - iVar8) * (*(int *)(&DAT_006a770c + iVar11) - iVar8) +
           iVar9 * iVar9 < 40000) &&
         (((&DAT_006a7734)[iVar11] == '\x01' || ((&DAT_006a7f6c)[iVar11] == '\0')))) {
        *(int *)(&g_nCameraX + iVar11) = iVar7;
        *piVar1 = iVar7;
        *(int *)(&g_nCameraY + iVar11) = iVar8;
        *(int *)(&DAT_006a770c + iVar11) = iVar8;
      }
      if ((((&DAT_006a7734)[iVar11] == '\0') && ((&DAT_006a7f6c)[iVar11] == '\x01')) &&
         ((&DAT_006a7736)[iVar11] == '\0')) {
        iVar9 = *(int *)(&DAT_006a7730 + iVar11);
        iVar6 = iVar7;
        if (iVar9 < iVar7) {
          iVar6 = iVar9;
        }
        iVar10 = *(int *)(&DAT_006a772c + iVar11);
        if ((iVar10 <= iVar6) && (iVar10 = iVar9, iVar7 <= iVar9)) {
          iVar10 = iVar7;
        }
        *(int *)(&g_nCameraScrollX + iVar11) = iVar10;
      }
      if ((&DAT_006a7734)[iVar11] == '\x01') {
        *(int *)(&g_nCameraScrollX + iVar11) = iVar7;
        *(int *)(&g_nCameraScrollY + iVar11) = iVar8;
      }
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar5 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(uVar5);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  }
  *unaff_FS_OFFSET = local_c;
  return;
}

