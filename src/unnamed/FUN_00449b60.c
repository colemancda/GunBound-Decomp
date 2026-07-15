/* FUN_00449b60 - 0x00449b60 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00449b60(int param_1)

{
  char *pcVar1;
  int iVar2;
  uint uVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined4 auVar6; /* Ghidra register slot; was undefined1 [4] */
  undefined4 uVar7;
  undefined2 uVar8;
  int iVar9;
  undefined1 uVar10;
  uint uVar11;
  int iVar12;
  undefined4 *puVar13;
  undefined2 *puVar14;
  undefined4 local_84; /* Ghidra register slot; was undefined1 [4] */
  undefined4 uStack_80;
  
  puVar13 = (undefined4 *)(param_1 + 0x2d114);
  for (iVar9 = 0x10e; iVar9 != 0; iVar9 = iVar9 + -1) {
    *puVar13 = 0;
    puVar13 = puVar13 + 1;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x449b90
   * (`lea edi,[ebp+4]`, ebp = this file's own param_1, confirmed by
   * objdump of orig/GunBound.gme matching this file's own `param_1 +
   * 0x2d114`-style offsets): the cell is param_1+4. See
   * tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField(param_1 + 4, 0xffffffff);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar11 = 20000;
  local_84 = (undefined4)0xa;
  while( true ) {
    puVar13 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar3 = puVar13[1];
    if (uVar3 <= uVar11) break;
LAB_00449be9:
    uVar11 = uVar11 + 1;
    local_84 = (undefined4)((int)local_84 + -1);
    if (local_84 == (undefined4)0x0) {
      iVar2 = (*(int *)(param_1 + 0x2d110) + 8) / 9;
      local_84 = (undefined4)(param_1 + 0x2d114);
      iVar12 = 0;
      iVar9 = param_1 + 0x458;
      *(int *)(param_1 + 0x450) = (*(int *)(param_1 + 0x450) + -1 + iVar2) % iVar2;
      do {
        iVar2 = iVar12 + *(int *)(param_1 + 0x450) * 9;
        if (*(int *)(param_1 + 0x2d110) <= iVar2) {
          return;
        }
        uVar8 = DAT_00555a18;
        uVar10 = DAT_00555a1a;
        if (*(char *)(iVar2 + 0x2d54c + param_1) == '\x01') {
          uVar8 = DAT_00555a14;
          uVar10 = DAT_00555a16;
        }
        SUBFIELD(uStack_80,0,undefined3) = CONCAT12(uVar10,uVar8);
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
        uVar8 = *(undefined2 *)(param_1 + 0x2e54c + iVar2 * 2);
        FUN_004240c0(g_clientContext,
                     CONCAT11((char)((ushort)uVar8 >> 8),
                              *(char *)(iVar2 + 0x2d54c + param_1) == '\x01'),
                     *(undefined1 *)(param_1 + 0x44c),uVar8);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar7 = PeekPacketChecksumState();
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        _sprintf((char *)((int)&uStack_80 + 3),s__05d_img_00555a08,uVar7);
        LoadSpriteSet(&DAT_00ea0e18,iVar12 + 20000);
        auVar6 = local_84;
        RenderWrappedText(local_84,iVar9 + 0x17a4,0x18,0x15,0x78,1);
        iVar12 = iVar12 + 1;
        local_84 = (undefined4)((int)auVar6 + 0x78);
        iVar9 = iVar9 + 0x17e4;
      } while (iVar12 < 9);
      return;
    }
  }
LAB_00449bbf:
  if (uVar3 != uVar11) goto code_r0x00449bc1;
  puVar4 = (undefined4 *)puVar13[4];
  while (puVar4 != puVar13) {
    puVar5 = (undefined4 *)*puVar4;
    puVar4 = (undefined4 *)puVar4[4];
    (*(code *)*puVar5)(1);
  }
  puVar13[3] = puVar13;
  puVar13[4] = puVar13;
  goto LAB_00449be9;
code_r0x00449bc1:
  puVar13 = (undefined4 *)puVar13[7];
  uVar3 = puVar13[1];
  if (uVar11 < uVar3) goto LAB_00449be9;
  goto LAB_00449bbf;
}

