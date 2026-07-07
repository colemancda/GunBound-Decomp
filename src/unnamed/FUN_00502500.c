/* FUN_00502500 - 0x00502500 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

uint __fastcall FUN_00502500(uint param_1,undefined4 *param_2)

{
  __time32_t _Var1;
  uint uVar2;
  int unaff_EBX;
  undefined4 *puVar3;
  undefined4 local_1774 [1498];
  undefined4 uStack_c;
  
  uStack_c = 0x502510;
  uVar2 = CONCAT31(0x17,*(char *)(unaff_EBX + 0x1a70));
  if ((*(char *)(unaff_EBX + 0x1a70) != '\0') && (uVar2 = 0, *(int *)(unaff_EBX + 0x1a74) != 0)) {
    uVar2 = param_1 + 4;
    if ((int)uVar2 < 0x1771) {
      puVar3 = local_1774;
      for (uVar2 = param_1 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
        *puVar3 = *param_2;
        param_2 = param_2 + 1;
        puVar3 = puVar3 + 1;
      }
      for (param_1 = param_1 & 3; param_1 != 0; param_1 = param_1 - 1) {
        *(undefined1 *)puVar3 = *(undefined1 *)param_2;
        param_2 = (undefined4 *)((int)param_2 + 1);
        puVar3 = (undefined4 *)((int)puVar3 + 1);
      }
      _Var1 = FID_conflict___time32((__time32_t *)0x0);
      *(__time32_t *)(unaff_EBX + 0x1abc) = _Var1;
      uVar2 = FUN_00503840(*(undefined4 *)(unaff_EBX + 0x1a74));
      return uVar2;
    }
  }
  return uVar2 & 0xffffff00;
}

