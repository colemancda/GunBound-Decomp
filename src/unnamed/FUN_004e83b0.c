/* FUN_004e83b0 - 0x004e83b0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004e83b0(void)

{
  LPCRITICAL_SECTION lpCriticalSection;
  uint uVar1;
  int iVar2;
  void *pvVar3;
  int iVar4;
  char unaff_BL;
  int unaff_ESI;
  uint uVar5;
  
  lpCriticalSection = (LPCRITICAL_SECTION)(unaff_ESI + 0x45264);
  EnterCriticalSection(lpCriticalSection);
  uVar5 = *(uint *)(unaff_ESI + 0x454a8);
  uVar1 = 0;
  if (uVar5 != 0) {
    iVar4 = 0;
    do {
      if (uVar5 <= uVar1) goto LAB_004e8470;
      if (*(char *)(*(int *)(unaff_ESI + 0x454a4) + 4 + iVar4) == unaff_BL) {
        if (uVar1 + 1 <= *(uint *)(unaff_ESI + 0x454a8)) {
          iVar4 = (*(uint *)(unaff_ESI + 0x454a8) - uVar1) + -1;
          if (iVar4 != 0) {
            pvVar3 = (void *)(uVar1 * 0x206 + *(int *)(unaff_ESI + 0x454a4));
            _memmove(pvVar3,(void *)((int)pvVar3 + 0x206),iVar4 * 0x206);
          }
          *(int *)(unaff_ESI + 0x454a8) = *(int *)(unaff_ESI + 0x454a8) + -1;
          LeaveCriticalSection(lpCriticalSection);
          return;
        }
        goto LAB_004e8470;
      }
      uVar1 = uVar1 + 1;
      iVar4 = iVar4 + 0x206;
    } while (uVar1 < uVar5);
  }
  uVar5 = 0;
  if (*(int *)(unaff_ESI + 0x454b8) != 0) {
    iVar4 = 0;
    if (*(int *)(unaff_ESI + 0x454b8) == 0) {
LAB_004e8470:
                    /* WARNING: Subroutine does not return */
      ThrowCxxException(0x80070057);
    }
    do {
      if (*(char *)(*(int *)(unaff_ESI + 0x454b4) + 4 + iVar4) == unaff_BL) {
        if (*(uint *)(unaff_ESI + 0x454b8) < uVar5 + 1) goto LAB_004e8470;
        iVar2 = (*(uint *)(unaff_ESI + 0x454b8) - uVar5) + -1;
        if (iVar2 != 0) {
          pvVar3 = (void *)(*(int *)(unaff_ESI + 0x454b4) + iVar4);
          _memmove(pvVar3,(void *)((int)pvVar3 + 0x206),iVar2 * 0x206);
        }
        *(int *)(unaff_ESI + 0x454b8) = *(int *)(unaff_ESI + 0x454b8) + -1;
      }
      uVar5 = uVar5 + 1;
      iVar4 = iVar4 + 0x206;
    } while (uVar5 < *(uint *)(unaff_ESI + 0x454b8));
  }
  LeaveCriticalSection(lpCriticalSection);
  return;
}

