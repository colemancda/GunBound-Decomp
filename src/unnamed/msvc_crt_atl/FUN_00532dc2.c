/* FUN_00532dc2 - 0x00532dc2 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __SEH_prolog replaced with injection: SEH_prolog */
/* WARNING: Function: __SEH_epilog replaced with injection: EH_epilog3 */
/* Library Function - Single Match
    __alloc_osfhnd
   
   Library: Visual Studio 2003 Release */

int __cdecl __alloc_osfhnd(void)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  int local_20;
  undefined1 local_14 [8];
  undefined4 uStack_c;
  undefined *local_8;
  
  local_8 = &DAT_00549a98;
  uStack_c = 0x532dce;
  local_20 = -1;
  iVar1 = __mtinitlocknum(0xb);
  if (iVar1 == 0) {
LAB_00532e63:
    local_20 = -1;
  }
  else {
    __lock(0xb);
    local_8 = (undefined *)0x0;
    for (iVar1 = 0; iVar1 < 0x40; iVar1 = iVar1 + 1) {
      puVar3 = (undefined4 *)(&DAT_00f28320)[iVar1];
      if (puVar3 == (undefined4 *)0x0) {
        puVar3 = _malloc(0x480);
        if (puVar3 != (undefined4 *)0x0) {
          (&DAT_00f28320)[iVar1] = puVar3;
          DAT_00f28314 = DAT_00f28314 + 0x20;
          for (; puVar3 < (undefined4 *)((&DAT_00f28320)[iVar1] + 0x480); puVar3 = puVar3 + 9) {
            *(undefined1 *)(puVar3 + 1) = 0;
            *puVar3 = 0xffffffff;
            *(undefined1 *)((int)puVar3 + 5) = 10;
            puVar3[2] = 0;
          }
          local_20 = iVar1 << 5;
          iVar1 = __lock_fhandle(local_20);
          if (iVar1 == 0) {
            local_20 = -1;
          }
        }
        break;
      }
      for (; puVar3 < (undefined4 *)((&DAT_00f28320)[iVar1] + 0x480); puVar3 = puVar3 + 9) {
        if ((*(byte *)(puVar3 + 1) & 1) == 0) {
          if (puVar3[2] == 0) {
            __lock(10);
            local_8 = (undefined *)0x1;
            if (puVar3[2] == 0) {
              iVar2 = ___crtInitCritSecAndSpinCount(puVar3 + 3,4000);
              if (iVar2 == 0) {
                __local_unwind2(local_14,0xffffffff);
                goto LAB_00532e63;
              }
              puVar3[2] = puVar3[2] + 1;
            }
            local_8 = (undefined *)0x0;
            FUN_00532e9b();
          }
          EnterCriticalSection((LPCRITICAL_SECTION)(puVar3 + 3));
          if ((*(byte *)(puVar3 + 1) & 1) == 0) {
            *puVar3 = 0xffffffff;
            local_20 = ((int)puVar3 - (&DAT_00f28320)[iVar1]) / 0x24 + iVar1 * 0x20;
            break;
          }
          LeaveCriticalSection((LPCRITICAL_SECTION)(puVar3 + 3));
        }
      }
      if (local_20 != -1) break;
    }
    local_8 = (undefined *)0xffffffff;
    FUN_00532f35();
  }
  return local_20;
}

