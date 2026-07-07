/* FUN_005024a0 - 0x005024a0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


uint FUN_005024a0(void)

{
  undefined4 in_EAX;
  __time32_t _Var1;
  uint uVar2;
  int unaff_ESI;
  
  uVar2 = CONCAT31((int3)((uint)in_EAX >> 8),*(char *)(unaff_ESI + 0x1a70));
  if ((*(char *)(unaff_ESI + 0x1a70) != '\0') && (uVar2 = 0, *(int *)(unaff_ESI + 0x1a74) != 0)) {
    _Var1 = FID_conflict___time32((__time32_t *)0x0);
    *(__time32_t *)(unaff_ESI + 0x1abc) = _Var1;
    uVar2 = FUN_00503840(*(undefined4 *)(unaff_ESI + 0x1a74));
    return uVar2;
  }
  return uVar2 & 0xffffff00;
}

