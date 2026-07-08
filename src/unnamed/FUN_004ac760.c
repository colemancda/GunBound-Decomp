/* FUN_004ac760 - 0x004ac760 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __fastcall FUN_004ac760(int param_1)

{
  bool bVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined4 *puVar7;
  uint uVar8;
  undefined4 *puVar9;
  undefined4 *puVar10;
  undefined4 *unaff_FS_OFFSET;
  uint local_688 [2];
  undefined1 local_680 [8];
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
  puStack_8 = &LAB_00539270;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  local_688[0] = 0;
  uVar2 = FUN_0040a6e0(param_1 + 0x38,local_678,*(undefined4 *)(&DAT_006a7710 + g_clientContext));
  local_4 = 0;
  FUN_0040a5f0(uVar2,local_454,400);
  local_4._0_1_ = 1;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar3 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_4 = (uint)local_4._1_3_ << 8;
  if (local_440 != 0) {
    FUN_0040a240();
    FUN_0040b540(local_688);
  }
  local_4 = 0xffffffff;
  if (local_664 != 0) {
    FUN_0040a240();
    FUN_0040b540(local_688);
  }
  iVar6 = param_1 + 0x25c;
  FUN_0040a8c0(iVar6,local_454,2);
  local_4 = 2;
  local_688[0] = 1;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar4 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (DAT_00793530 <= iVar4 + iVar3) {
    FUN_0040a8c0(iVar6,local_678,2);
    local_4 = 3;
    local_688[0] = 3;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar4 = PeekPacketChecksumState();
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    bVar1 = false;
    if (iVar3 - iVar4 <= DAT_0056df30) goto LAB_004ac8fb;
  }
  bVar1 = true;
LAB_004ac8fb:
  local_4 = 2;
  if ((local_688[0] & 2) != 0) {
    local_688[0] = local_688[0] & 0xfffffffd;
    if (local_664 != 0) {
      FUN_0040a240();
      FUN_0040b540(local_680);
    }
  }
  local_4 = 0xffffffff;
  if (((local_688[0] & 1) != 0) && (local_440 != 0)) {
    FUN_0040a240();
    FUN_0040b540(local_680);
  }
  if (!bVar1) {
    iVar4 = FindTextureCacheEntryByName(s_TornadoTexture_00555bc0);
    if (iVar4 != 0) {
      uVar8 = *(uint *)(param_1 + 0x480) & 0x8000003f;
      if ((int)uVar8 < 0) {
        uVar8 = (uVar8 - 1 | 0xffffffc0) + 1;
      }
      iVar4 = uVar8 * -6;
      local_688[0] = *(uint *)(param_1 + 0x480) & 0x80000007;
      if ((int)local_688[0] < 0) {
        local_688[0] = (local_688[0] - 1 | 0xfffffff8) + 1;
      }
      FUN_0040a8c0(iVar6,local_678,2);
      local_4 = 4;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar5 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      DAT_00ea0e28 = (float)(iVar3 - iVar5);
      local_4 = 0xffffffff;
      _DAT_00ea0e94 = DAT_00ea0e28;
      if (local_664 != 0) {
        FUN_0040a240();
        FUN_0040b540(local_680);
      }
      FUN_0040a8c0(iVar6,local_230,2);
      local_4 = 5;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar6 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      _DAT_00ea0e4c = (float)(iVar6 + -1 + iVar3);
      local_4 = 0xffffffff;
      DAT_00ea0e70 = _DAT_00ea0e4c;
      if (local_21c != 0) {
        FUN_0040a240();
        FUN_0040b540(local_680);
      }
      _DAT_00ea0ea4 = 0xffffffff;
      _DAT_00ea0e80 = 0xffffffff;
      _DAT_00ea0e5c = 0xffffffff;
      _DAT_00ea0e38 = 0xffffffff;
      if (iVar4 < *(int *)(&DAT_006a7724 + g_clientContext)) {
        puVar7 = (undefined4 *)(&DAT_006ba1fc + g_spriteVertexCount * 0x6c);
        iVar3 = iVar4;
        do {
          iVar6 = iVar3 + 0x40;
          if (DAT_00793534 <= iVar6) {
            if (iVar4 - DAT_0056df34 != 0 && DAT_0056df34 <= iVar4) break;
            DAT_00ea0e2c = (float)iVar3;
            uVar8 = local_688[0] & 0x80000001;
            DAT_00ea0e74 = (float)iVar6;
            if ((int)uVar8 < 0) {
              uVar8 = (uVar8 - 1 | 0xfffffffe) + 1;
            }
            _DAT_00ea0e3c = (float)(int)uVar8 * _DAT_00557fb8;
            _DAT_00ea0e40 = (float)((int)local_688[0] / 2) * _DAT_00558054 + _DAT_00557fe4;
            _DAT_00ea0e60 = _DAT_00ea0e3c + _DAT_00557fb8;
            _DAT_00ea0e88 = _DAT_00ea0e40 + _DAT_00558068;
            puVar9 = &DAT_00ea0e28;
            puVar10 = puVar7 + -0x1b;
            _DAT_00ea0e50 = DAT_00ea0e2c;
            DAT_00ea0e64 = _DAT_00ea0e40;
            _DAT_00ea0e84 = _DAT_00ea0e60;
            _DAT_00ea0e98 = DAT_00ea0e74;
            DAT_00ea0ea8 = _DAT_00ea0e3c;
            _DAT_00ea0eac = _DAT_00ea0e88;
            for (iVar3 = 0x1b; iVar3 != 0; iVar3 = iVar3 + -1) {
              *puVar10 = *puVar9;
              puVar9 = puVar9 + 1;
              puVar10 = puVar10 + 1;
            }
            puVar9 = &DAT_00ea0e70;
            puVar10 = puVar7;
            for (iVar3 = 0x12; iVar3 != 0; iVar3 = iVar3 + -1) {
              *puVar10 = *puVar9;
              puVar9 = puVar9 + 1;
              puVar10 = puVar10 + 1;
            }
            puVar9 = &DAT_00ea0e28;
            puVar10 = puVar7 + 0x12;
            for (iVar3 = 9; iVar3 != 0; iVar3 = iVar3 + -1) {
              *puVar10 = *puVar9;
              puVar9 = puVar9 + 1;
              puVar10 = puVar10 + 1;
            }
            g_spriteVertexCount = g_spriteVertexCount + 2;
            puVar7 = puVar7 + 0x36;
          }
          local_688[0] = local_688[0] + 1 & 0x80000007;
          if ((int)local_688[0] < 0) {
            local_688[0] = (local_688[0] - 1 | 0xfffffff8) + 1;
          }
          iVar3 = iVar6;
        } while (iVar6 < *(int *)(&DAT_006a7724 + g_clientContext));
      }
    }
  }
  *unaff_FS_OFFSET = local_c;
  return;
}

