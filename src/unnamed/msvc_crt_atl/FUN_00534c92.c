/* FUN_00534c92 - 0x00534c92 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* Library Function - Single Match
    __chsize_lk
   
   Library: Visual Studio 2003 Release */

int __chsize_lk(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int *piVar5;
  undefined4 *puVar6;
  HANDLE hFile;
  BOOL BVar7;
  DWORD *pDVar8;
  DWORD DVar9;
  int iVar10;
  undefined1 local_1008 [4096];
  undefined4 local_8;
  
  iVar10 = 0;
  local_8 = DAT_0056bfd4;
  iVar1 = __lseek_lk(param_1,0,1);
  if ((iVar1 == -1) || (iVar2 = __lseek_lk(param_1,0,2), iVar2 == -1)) {
    iVar10 = -1;
  }
  else {
    iVar2 = param_2 - iVar2;
    if (iVar2 < 1) {
      if (iVar2 < 0) {
        __lseek_lk(param_1,param_2,0);
        hFile = (HANDLE)__get_osfhandle(param_1);
        BVar7 = SetEndOfFile(hFile);
        iVar10 = (BVar7 != 0) - 1;
        if (iVar10 == -1) {
          puVar6 = (undefined4 *)FUN_0052b6d4();
          *puVar6 = 0xd;
          pDVar8 = (DWORD *)FUN_0052b6dd();
          DVar9 = GetLastError();
          *pDVar8 = DVar9;
        }
      }
    }
    else {
      _memset(local_1008,0,0x1000);
      uVar3 = __setmode_lk(param_1,0x8000);
      do {
        iVar4 = 0x1000;
        if (iVar2 < 0x1000) {
          iVar4 = iVar2;
        }
        iVar4 = __write_lk(param_1,local_1008,iVar4);
        if (iVar4 == -1) {
          piVar5 = (int *)FUN_0052b6dd();
          if (*piVar5 == 5) {
            puVar6 = (undefined4 *)FUN_0052b6d4();
            *puVar6 = 0xd;
          }
          iVar10 = -1;
          break;
        }
        iVar2 = iVar2 - iVar4;
      } while (0 < iVar2);
      __setmode_lk(param_1,uVar3);
    }
    __lseek_lk(param_1,iVar1,0);
  }
  return iVar10;
}

