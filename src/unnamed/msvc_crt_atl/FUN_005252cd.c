/* FUN_005252cd - 0x005252cd in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    __onexit_lk
   
   Library: Visual Studio 2003 Release */

void __onexit_lk(void)

{
  size_t sVar1;
  void *pvVar2;
  size_t sVar3;
  undefined4 unaff_EDI;
  
  sVar1 = __msize(DAT_00f29688);
  if (sVar1 < (uint)((int)DAT_00f29684 + (4 - (int)DAT_00f29688))) {
    sVar3 = 0x800;
    if (sVar1 < 0x800) {
      sVar3 = sVar1;
    }
    pvVar2 = _realloc(DAT_00f29688,sVar3 + sVar1);
    if (pvVar2 == (void *)0x0) {
      pvVar2 = _realloc(DAT_00f29688,sVar1 + 0x10);
      if (pvVar2 == (void *)0x0) {
        return;
      }
    }
    DAT_00f29684 = (undefined4 *)((int)pvVar2 + ((int)DAT_00f29684 - (int)DAT_00f29688 >> 2) * 4);
    DAT_00f29688 = pvVar2;
  }
  *DAT_00f29684 = unaff_EDI;
  DAT_00f29684 = DAT_00f29684 + 1;
  return;
}

