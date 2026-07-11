/* FUN_004aacd0 - 0x004aacd0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_004aacd0(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  uint uVar12;
  int iVar13;
  int local_1c;
  
  iVar6 = g_clientContext;
  *(undefined1 *)(*(int *)(param_1 + 8) + 0x22d33 + g_clientContext) = 1;
  iVar13 = 0;
  do {
    if (iVar13 == 0) {
      iVar7 = *(int *)(param_1 + 0x3f9c) * -0x10 + 0xff;
LAB_004aad77:
      local_1c = 1;
      if (0 < iVar7) {
        local_1c = iVar7;
      }
    }
    else {
      if (9 < *(int *)(param_1 + 0x3f9c)) {
        iVar7 = *(int *)(param_1 + 0x3f9c) * -0x14 + 0x1c7;
        goto LAB_004aad77;
      }
      local_1c = 0xff;
    }
    iVar8 = FloatToInt64();
    iVar7 = *(int *)(param_1 + 0x3fa8);
    iVar1 = *(int *)(param_1 + 0x3fb0);
    iVar9 = FloatToInt64();
    iVar2 = *(int *)(param_1 + 0x3fb0);
    iVar10 = FloatToInt64();
    iVar3 = *(int *)(param_1 + 0x3fac);
    iVar4 = *(int *)(param_1 + 0x3fb4);
    iVar11 = FloatToInt64();
    iVar5 = *(int *)(param_1 + 0x3fb4);
    *(int *)(iVar6 + 0x22d44 + (iVar13 + *(int *)(param_1 + 8) * 2) * 0x28) = iVar7 + iVar8;
    *(int *)(iVar6 + 0x22d48 + (iVar13 + *(int *)(param_1 + 8) * 2) * 0x28) = iVar3 + iVar10;
    *(int *)(iVar6 + 0x22d4c + (iVar13 + *(int *)(param_1 + 8) * 2) * 0x28) = iVar1 + iVar8;
    *(int *)(iVar6 + 0x22d50 + (iVar13 + *(int *)(param_1 + 8) * 2) * 0x28) = iVar4 + iVar10;
    *(int *)(iVar6 + 0x22d54 + (iVar13 + *(int *)(param_1 + 8) * 2) * 0x28) = iVar2 + iVar9;
    *(int *)(iVar6 + (iVar13 + 0xdef + *(int *)(param_1 + 8) * 2) * 0x28) = iVar5 + iVar11;
    *(int *)(iVar6 + 0x22d5c + (iVar13 + *(int *)(param_1 + 8) * 2) * 0x28) = iVar7 + iVar9;
    *(int *)(iVar6 + 0x22d60 + (iVar13 + *(int *)(param_1 + 8) * 2) * 0x28) = iVar3 + iVar11;
    if (iVar13 == 0) {
      *(uint *)(*(int *)(param_1 + 8) * 0x50 + 0x22d64 + iVar6) =
           local_1c << 0x18 | *(uint *)(param_1 + 0x3fa4);
    }
    else {
      *(uint *)(iVar6 + 0x22d64 + (iVar13 + *(int *)(param_1 + 8) * 2) * 0x28) =
           local_1c << 0x18 | 0xffffff;
    }
    uVar12 = *(uint *)(param_1 + 0x3f9c) & 0x80000007;
    if ((int)uVar12 < 0) {
      uVar12 = (uVar12 - 1 | 0xfffffff8) + 1;
    }
    iVar7 = iVar13 + *(int *)(param_1 + 8) * 2;
    iVar13 = iVar13 + 1;
    *(uint *)(iVar6 + 0x22d68 + iVar7 * 0x28) = uVar12;
    if (1 < iVar13) {
      return;
    }
  } while( true );
}

