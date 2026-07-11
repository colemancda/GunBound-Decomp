/* AllocTextureCacheNode - 0x004f3dc0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void * AllocTextureCacheNode(void)

{
  int iVar1;
  void *pvVar2;
  uint uVar3;
  
  iVar1 = DAT_00793660 + ((int)DAT_00793660 >> 0x1f & 0x3ffU);
  if (DAT_007921b0[iVar1 >> 10] == 0) {
    pvVar2 = operator_new(0x20000);
    DAT_007921b0[(int)(DAT_00793660 + ((int)DAT_00793660 >> 0x1f & 0x3ffU)) >> 10] = pvVar2;
    DAT_00793660 = DAT_00793660 + 1;
    return pvVar2;
  }
  uVar3 = DAT_00793660 & 0x800003ff;
  if ((int)uVar3 < 0) {
    uVar3 = (uVar3 - 1 | 0xfffffc00) + 1;
  }
  DAT_00793660 = DAT_00793660 + 1;
  return (void *)(uVar3 * 0x80 + DAT_007921b0[iVar1 >> 10]);
}

