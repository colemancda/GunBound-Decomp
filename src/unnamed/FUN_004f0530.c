/* FUN_004f0530 - 0x004f0530 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

uint FUN_004f0530(void)

{
  int *piVar1;
  uint uVar2;
  int iVar3;
  undefined4 *unaff_ESI;
  undefined4 *puVar4;
  DWORD local_200c;
  int local_2008;
  DWORD local_2004;
  undefined1 local_2000 [8188];
  undefined4 uStack_4;
  
  uStack_4 = 0x4f053a;
  local_2008 = 0;
  local_2004 = FUN_004ea760(unaff_ESI[0x407],local_2000,unaff_ESI,0x1000);
  piVar1 = unaff_ESI + 2;
  iVar3 = 0x100;
  do {
    local_2008 = local_2008 + piVar1[-2] + piVar1[-1] + piVar1[1] + *piVar1;
    piVar1 = piVar1 + 4;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  uVar2 = SetFilePointer((HANDLE)unaff_ESI[0x400],
                         *(int *)(unaff_ESI[0x401] + 0x7c) + *(int *)(unaff_ESI[0x401] + 0x74),
                         (PLONG)0x0,0);
  if (uVar2 != 0xffffffff) {
    uVar2 = WriteFile((HANDLE)unaff_ESI[0x400],&local_2004,4,&local_200c,(LPOVERLAPPED)0x0);
    if (local_200c == 4) {
      uVar2 = WriteFile((HANDLE)unaff_ESI[0x400],&local_2008,4,&local_200c,(LPOVERLAPPED)0x0);
      if (local_200c == 4) {
        uVar2 = WriteFile((HANDLE)unaff_ESI[0x400],local_2000,local_2004,&local_200c,
                          (LPOVERLAPPED)0x0);
        if (local_200c == local_2004) {
          *(DWORD *)(unaff_ESI[0x401] + 0x7c) = *(int *)(unaff_ESI[0x401] + 0x7c) + local_2004 + 8;
          puVar4 = unaff_ESI;
          for (iVar3 = 0x400; iVar3 != 0; iVar3 = iVar3 + -1) {
            *puVar4 = 0;
            puVar4 = puVar4 + 1;
          }
          unaff_ESI[0x403] = 0;
          return 1;
        }
      }
    }
  }
  return uVar2 & 0xffffff00;
}

