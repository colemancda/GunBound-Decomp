/* FUN_00449db0 - 0x00449db0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00449db0(int param_1)

{
  char *pcVar1;
  int iVar2;
  uint uVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined1 auVar6 [4];
  undefined4 uVar7;
  undefined1 uVar8;
  int iVar9;
  undefined2 uVar10;
  uint uVar11;
  int iVar12;
  undefined4 *puVar13;
  undefined2 *puVar14;
  undefined1 local_84 [4];
  undefined4 uStack_80;
  
  puVar13 = (undefined4 *)(param_1 + 0x2d114);
  for (iVar9 = 0x10e; iVar9 != 0; iVar9 = iVar9 + -1) {
    *puVar13 = 0;
    puVar13 = puVar13 + 1;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(0xffffffff);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar11 = 20000;
  local_84 = (undefined1  [4])0xa;
  while( true ) {
    puVar13 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar3 = puVar13[1];
    if (uVar3 <= uVar11) break;
LAB_00449e39:
    uVar11 = uVar11 + 1;
    local_84 = (undefined1  [4])((int)local_84 + -1);
    if (local_84 == (undefined1  [4])0x0) {
      local_84 = (undefined1  [4])(param_1 + 0x2d114);
      iVar12 = 0;
      iVar9 = param_1 + 0x458;
      *(int *)(param_1 + 0x450) =
           (*(int *)(param_1 + 0x450) + 1) % ((*(int *)(param_1 + 0x2d110) + 8) / 9);
      do {
        iVar2 = iVar12 + *(int *)(param_1 + 0x450) * 9;
        if (*(int *)(param_1 + 0x2d110) <= iVar2) {
          return;
        }
        uVar8 = DAT_00555a1a;
        uVar10 = DAT_00555a18;
        if (*(char *)(iVar2 + 0x2d54c + param_1) == '\x01') {
          uVar8 = DAT_00555a16;
          uVar10 = DAT_00555a14;
        }
        uStack_80 = (undefined *)CONCAT22(CONCAT11(uStack_80._3_1_,uVar8),uVar10);
        switch(*(undefined4 *)(param_1 + 0x44c)) {
        case 0:
          puVar14 = (undefined2 *)(local_84 + 3);
          do {
            pcVar1 = (char *)((int)puVar14 + 1);
            puVar14 = (undefined2 *)((int)puVar14 + 1);
          } while (*pcVar1 != '\0');
          *puVar14 = DAT_00552c80;
          break;
        case 1:
          puVar14 = (undefined2 *)(local_84 + 3);
          do {
            pcVar1 = (char *)((int)puVar14 + 1);
            puVar14 = (undefined2 *)((int)puVar14 + 1);
          } while (*pcVar1 != '\0');
          *puVar14 = DAT_005535f0;
          break;
        case 2:
          puVar14 = (undefined2 *)(local_84 + 3);
          do {
            pcVar1 = (char *)((int)puVar14 + 1);
            puVar14 = (undefined2 *)((int)puVar14 + 1);
          } while (*pcVar1 != '\0');
          *puVar14 = DAT_00552c7c;
          break;
        case 3:
          uStack_80 = &DAT_00666d73;
        }
        FUN_004240c0(g_clientContext,
                     CONCAT31((int3)((uint)iVar2 >> 8),
                              *(char *)(iVar2 + 0x2d54c + param_1) == '\x01'),
                     *(undefined1 *)(param_1 + 0x44c),*(undefined2 *)(param_1 + 0x2e54c + iVar2 * 2)
                    );
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar7 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        _sprintf((char *)((int)&uStack_80 + 3),s__05d_img_00555a08,uVar7);
        FUN_004f1790(&DAT_00ea0e18,iVar12 + 20000);
        auVar6 = local_84;
        FUN_0041b4b0(local_84,iVar9 + 0x17a4,0x18,0x15,0x78,1);
        iVar12 = iVar12 + 1;
        local_84 = (undefined1  [4])((int)auVar6 + 0x78);
        iVar9 = iVar9 + 0x17e4;
      } while (iVar12 < 9);
      return;
    }
  }
LAB_00449e0f:
  if (uVar3 != uVar11) goto code_r0x00449e11;
  puVar4 = (undefined4 *)puVar13[4];
  while (puVar4 != puVar13) {
    puVar5 = (undefined4 *)*puVar4;
    puVar4 = (undefined4 *)puVar4[4];
    (*(code *)*puVar5)(1);
  }
  puVar13[3] = puVar13;
  puVar13[4] = puVar13;
  goto LAB_00449e39;
code_r0x00449e11:
  puVar13 = (undefined4 *)puVar13[7];
  uVar3 = puVar13[1];
  if (uVar11 < uVar3) goto LAB_00449e39;
  goto LAB_00449e0f;
}

