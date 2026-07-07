/* FUN_0050e6c0 - 0x0050e6c0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_0050e6c0(void)

{
  void *_Dst;
  uint uVar1;
  uint uVar2;
  int iVar3;
  int unaff_ESI;
  void *unaff_EDI;
  
  uVar1 = *(uint *)(unaff_ESI + 0x10);
  uVar2 = 0;
  if (uVar1 == 0) {
    return;
  }
  do {
    if (uVar1 <= uVar2) {
LAB_0050e6ed:
                    /* WARNING: Subroutine does not return */
      FUN_004010c0(0x80070057);
    }
    if (*(void **)(*(int *)(unaff_ESI + 0xc) + uVar2 * 4) == unaff_EDI) {
      if (uVar2 + 1 <= *(uint *)(unaff_ESI + 0x10)) {
        iVar3 = (*(uint *)(unaff_ESI + 0x10) - uVar2) + -1;
        if (iVar3 != 0) {
          _Dst = (void *)(*(int *)(unaff_ESI + 0xc) + uVar2 * 4);
          _memmove(_Dst,(void *)((int)_Dst + 4),iVar3 * 4);
        }
        *(int *)(unaff_ESI + 0x10) = *(int *)(unaff_ESI + 0x10) + -1;
        if (unaff_EDI == (void *)0x0) {
          return;
        }
        FUN_0050e560();
        _free(unaff_EDI);
        return;
      }
      goto LAB_0050e6ed;
    }
    uVar2 = uVar2 + 1;
    if (uVar1 <= uVar2) {
      return;
    }
  } while( true );
}

