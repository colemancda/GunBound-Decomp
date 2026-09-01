/* FUN_004382d0 - 0x004382d0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004382d0(int regEcx,int regEax,char *regEbx)

{
  char cVar1;
  undefined4 *puVar2;
  void *pvVar3;
  
  /* guard-cell: proven.  regEax is the effects-guard block ctx+0x6a7f70
   * (register arg promoted 2026-09-01, all 8 sites re-verified); every
   * caller passes exactly that value, so the +4 peek is the global flag.
   * regEcx is the per-object slot/id this balloon is keyed by (forwarded
   * to FUN_0044fd00's EAX -> obj+8 once that promotion lands; see its
   * file header).  regEbx is the balloon text. */
  cVar1 = PeekPacketChecksumBool((byte *)(regEax + 4));
  if ((cVar1 == '\0') && (regEbx != (char *)0x0)) {
    puVar2 = (undefined4 *)FindSpriteFrame();
    if (puVar2 != (undefined4 *)0x0) {
      *(undefined4 *)(puVar2[3] + 0x10) = puVar2[4];
      *(undefined4 *)(puVar2[4] + 0xc) = puVar2[3];
      (**(code **)*puVar2)(1);
    }
    pvVar3 = operator_new(0x46c);
    if (pvVar3 != (void *)0x0) {
      FUN_0044fd00(0,(undefined4 *)pvVar3,regEcx);
    }
    FUN_00450600((int)pvVar3,regEbx);
    RegisterActiveObject(0, 0, (undefined4 *)0);
  }
  return;
}

