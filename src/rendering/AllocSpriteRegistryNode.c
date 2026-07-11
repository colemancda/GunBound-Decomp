/* AllocSpriteRegistryNode - 0x004f3980 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void * AllocSpriteRegistryNode(void)

{
  int iVar1;
  void *pvVar2;
  uint uVar3;
  
  iVar1 = DAT_0079364c + ((int)DAT_0079364c >> 0x1f & 0x3ffU);
  if (DAT_006b9100[iVar1 >> 10] == 0) {
    pvVar2 = operator_new(0x3000);
    DAT_006b9100[(int)(DAT_0079364c + ((int)DAT_0079364c >> 0x1f & 0x3ffU)) >> 10] = pvVar2;
    DAT_0079364c = DAT_0079364c + 1;
    return pvVar2;
  }
  uVar3 = DAT_0079364c & 0x800003ff;
  if ((int)uVar3 < 0) {
    uVar3 = (uVar3 - 1 | 0xfffffc00) + 1;
  }
  DAT_0079364c = DAT_0079364c + 1;
  return (void *)(DAT_006b9100[iVar1 >> 10] + uVar3 * 0xc);
}

