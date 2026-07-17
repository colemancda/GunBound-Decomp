/* FUN_004e4220 - 0x004e4220 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004e4220(int param_1)

{
  uint uVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  int iVar4;
  uint uVar5;
  undefined4 *puVar6;
  
  iVar4 = param_1;
  if (*(void **)(param_1 + 0x34) != (void *)0x0) {
    _free(*(void **)(param_1 + 0x34));
    *(undefined4 *)(param_1 + 0x34) = 0;
  }
  if (*(void **)(param_1 + 0x38) != (void *)0x0) {
    _free(*(void **)(param_1 + 0x38));
    *(undefined4 *)(param_1 + 0x38) = 0;
  }
  if (*(void **)(param_1 + 0x3c) != (void *)0x0) {
    _free(*(void **)(param_1 + 0x3c));
    *(undefined4 *)(param_1 + 0x3c) = 0;
  }
  if (*(void **)(param_1 + 0x44) != (void *)0x0) {
    _free(*(void **)(param_1 + 0x44));
    *(undefined4 *)(param_1 + 0x44) = 0;
  }
  puVar6 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
  uVar5 = puVar6[1];
  while( true ) {
    if (60000 < uVar5) goto LAB_004e42b5;
    if (uVar5 == 60000) break;
    puVar6 = (undefined4 *)puVar6[7];
    uVar5 = puVar6[1];
  }
  puVar2 = (undefined4 *)puVar6[4];
  while (puVar2 != puVar6) {
    puVar3 = (undefined4 *)*puVar2;
    puVar2 = (undefined4 *)puVar2[4];
    (*(code *)*puVar3)(1);
  }
  puVar6[3] = puVar6;
  puVar6[4] = puVar6;
LAB_004e42b5:
  FUN_004f3060(&DAT_00eb168c);
  /* Container passed in EBX by the original (`mov ebx,0xeb1bd8` immediately
   * before the call) - see src/rendering/FlushTextureCache.c's header. */
  FlushTextureCache((int)&g_textureCache);
  uVar5 = 60000;
  param_1 = 1000;
  while( true ) {
    puVar6 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
    uVar1 = puVar6[1];
    if (uVar1 <= uVar5) break;
LAB_004e4319:
    uVar5 = uVar5 + 1;
    param_1 = param_1 + -1;
    if (param_1 == 0) {
      FUN_004f3060(iVar4 + 0x85c);
      return;
    }
  }
LAB_004e42ef:
  if (uVar1 != uVar5) goto code_r0x004e42f1;
  puVar2 = (undefined4 *)puVar6[4];
  while (puVar2 != puVar6) {
    puVar3 = (undefined4 *)*puVar2;
    puVar2 = (undefined4 *)puVar2[4];
    (*(code *)*puVar3)(1);
  }
  puVar6[3] = puVar6;
  puVar6[4] = puVar6;
  goto LAB_004e4319;
code_r0x004e42f1:
  puVar6 = (undefined4 *)puVar6[7];
  uVar1 = puVar6[1];
  if (uVar5 < uVar1) goto LAB_004e4319;
  goto LAB_004e42ef;
}

