/* FUN_00482130 - 0x00482130 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_00482130(int param_1)

{
  float fVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined4 *puVar7;
  int *piVar8;
  undefined4 *puVar9;
  undefined4 *puVar10;
  undefined4 *unaff_FS_OFFSET;
  int local_ad0 [2];
  undefined1 local_ac8 [8];
  undefined1 local_ac0 [20];
  int local_aac;
  undefined1 local_89c [20];
  int local_888;
  undefined1 local_678 [20];
  int local_664;
  undefined1 local_454 [20];
  int local_440;
  undefined1 local_230 [20];
  int local_21c;
  undefined4 local_c;
  undefined1 *puStack_8;
  int local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_00539a17;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  uVar3 = FUN_0040a6e0(param_1 + 0x38,local_454,*(undefined4 *)(&DAT_006a7710 + g_clientContext));
  local_4 = 0;
  FUN_0040a5f0(uVar3,local_ac0,400);
  SUBFIELD(local_4,0,undefined1) = 1;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = (uint)SUBFIELD(local_4,1,undefined3) << 8;
  if (local_aac != 0) {
    FUN_0040a240();
    FUN_0040b540(local_ad0);
  }
  local_4 = 0xffffffff;
  if (local_440 != 0) {
    FUN_0040a240();
    FUN_0040b540(local_ad0);
  }
  if ((DAT_00793530 <= iVar4 + 0x20) && (local_ad0[0] = iVar4 + -0x20, local_ad0[0] <= DAT_0056df30)
     ) {
    uVar3 = FUN_0040a6e0(param_1 + 0x25c,local_230,*(undefined4 *)(&DAT_006a7714 + g_clientContext));
    local_4 = 2;
    uVar3 = FUN_0040a5f0(uVar3,local_678,0x104);
    SUBFIELD(local_4,0,undefined1) = 3;
    FUN_0040a5f0(uVar3,local_89c,0x26);
    SUBFIELD(local_4,0,undefined1) = 4;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar5 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    SUBFIELD(local_4,0,undefined1) = 3;
    if (local_888 != 0) {
      FUN_0040a240();
      FUN_0040b540(local_ac8);
    }
    local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),2);
    if (local_664 != 0) {
      FUN_0040a240();
      FUN_0040b540(local_ac8);
    }
    local_4 = 0xffffffff;
    if (local_21c != 0) {
      FUN_0040a240();
      FUN_0040b540(local_ac8);
    }
    iVar2 = DAT_00793534;
    if ((DAT_00793534 <= iVar5) &&
       (iVar6 = FindTextureCacheEntryByName(s_Lightning_00555b90), iVar6 != 0)) {
      DAT_00ea0e28 = (float)local_ad0[0];
      _DAT_00ea0e4c = (float)(iVar4 + 0x1f);
      _DAT_00ea0e38 = *(int *)(param_1 + 0x484) << 0x18 | 0xffffff;
      DAT_00ea0e64 = 0;
      _DAT_00ea0e40 = 0;
      _DAT_00ea0eac = 0x3f800000;
      _DAT_00ea0e88 = 0x3f800000;
      _DAT_00ea0e5c = _DAT_00ea0e38;
      DAT_00ea0e70 = _DAT_00ea0e4c;
      _DAT_00ea0e80 = _DAT_00ea0e38;
      _DAT_00ea0e94 = DAT_00ea0e28;
      _DAT_00ea0ea4 = _DAT_00ea0e38;
      if (iVar2 < iVar5) {
        puVar7 = (undefined4 *)(&DAT_006ba1fc + g_spriteVertexCount * 0x6c);
        piVar8 = (int *)(param_1 + 0x488);
        do {
          iVar4 = iVar5 + -0x100;
          fVar1 = (float)*piVar8 * _DAT_00558054;
          if (iVar4 <= DAT_0056df34) {
            DAT_00ea0e2c = (float)iVar4;
            g_spriteVertexCount = g_spriteVertexCount + 2;
            DAT_00ea0e74 = (float)iVar5;
            _DAT_00ea0e60 = fVar1 + _DAT_00558054;
            puVar9 = &DAT_00ea0e28;
            puVar10 = puVar7 + -0x1b;
            _DAT_00ea0e3c = fVar1;
            _DAT_00ea0e50 = DAT_00ea0e2c;
            _DAT_00ea0e84 = _DAT_00ea0e60;
            _DAT_00ea0e98 = DAT_00ea0e74;
            DAT_00ea0ea8 = fVar1;
            for (iVar5 = 0x1b; iVar5 != 0; iVar5 = iVar5 + -1) {
              *puVar10 = *puVar9;
              puVar9 = puVar9 + 1;
              puVar10 = puVar10 + 1;
            }
            puVar9 = &DAT_00ea0e70;
            puVar10 = puVar7;
            for (iVar5 = 0x12; iVar5 != 0; iVar5 = iVar5 + -1) {
              *puVar10 = *puVar9;
              puVar9 = puVar9 + 1;
              puVar10 = puVar10 + 1;
            }
            puVar9 = &DAT_00ea0e28;
            puVar10 = puVar7 + 0x12;
            for (iVar5 = 9; iVar5 != 0; iVar5 = iVar5 + -1) {
              *puVar10 = *puVar9;
              puVar9 = puVar9 + 1;
              puVar10 = puVar10 + 1;
            }
            puVar7 = puVar7 + 0x36;
          }
          piVar8 = piVar8 + 1;
          iVar5 = iVar4;
        } while (DAT_00793534 < iVar4);
      }
    }
  }
  *unaff_FS_OFFSET = local_c;
  return;
}

