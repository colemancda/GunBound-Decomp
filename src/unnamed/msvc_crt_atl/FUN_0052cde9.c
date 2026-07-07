/* FUN_0052cde9 - 0x0052cde9 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* Library Function - Single Match
    __write_lk
   
   Library: Visual Studio 2003 Release */

int __write_lk(uint param_1,char *param_2,uint param_3)

{
  int *piVar1;
  char *pcVar2;
  char cVar3;
  char *pcVar4;
  BOOL BVar5;
  undefined4 *puVar6;
  uint uVar7;
  int iVar8;
  DWORD local_424;
  int local_420;
  DWORD local_41c;
  char *local_418;
  int local_414;
  ulong local_410;
  char local_40c [1028];
  undefined4 local_8;
  
  local_8 = DAT_0056bfd4;
  local_41c = 0;
  local_420 = 0;
  if (param_3 == 0) {
    return 0;
  }
  piVar1 = &DAT_00f28320 + ((int)param_1 >> 5);
  iVar8 = (param_1 & 0x1f) * 0x24;
  if ((*(byte *)(*piVar1 + 4 + iVar8) & 0x20) != 0) {
    __lseeki64_lk(param_1,0,0,2);
  }
  if ((*(byte *)((undefined4 *)(*piVar1 + iVar8) + 1) & 0x80) == 0) {
    BVar5 = WriteFile(*(HANDLE *)(*piVar1 + iVar8),param_2,param_3,&local_424,(LPOVERLAPPED)0x0);
    if (BVar5 == 0) {
      local_410 = GetLastError();
    }
    else {
      local_410 = 0;
      local_41c = local_424;
    }
LAB_0052cf05:
    if (local_41c != 0) {
      return local_41c - local_420;
    }
    if (local_410 != 0) {
      if (local_410 == 5) {
        puVar6 = (undefined4 *)FUN_0052b6d4();
        *puVar6 = 9;
        puVar6 = (undefined4 *)FUN_0052b6dd();
        *puVar6 = 5;
        return -1;
      }
      __dosmaperr(local_410);
      return -1;
    }
  }
  else {
    local_418 = param_2;
    local_410 = 0;
    if (param_3 != 0) {
      do {
        uVar7 = (int)local_418 - (int)param_2;
        pcVar4 = local_40c;
        local_414 = 0;
        do {
          if (param_3 <= uVar7) break;
          pcVar2 = local_418 + 1;
          cVar3 = *local_418;
          uVar7 = uVar7 + 1;
          if (cVar3 == '\n') {
            local_420 = local_420 + 1;
            *pcVar4 = '\r';
            pcVar4 = pcVar4 + 1;
            local_414 = local_414 + 1;
          }
          *pcVar4 = cVar3;
          pcVar4 = pcVar4 + 1;
          local_414 = local_414 + 1;
          local_418 = pcVar2;
        } while (local_414 < 0x400);
        BVar5 = WriteFile(*(HANDLE *)(*piVar1 + iVar8),local_40c,(int)pcVar4 - (int)local_40c,
                          &local_424,(LPOVERLAPPED)0x0);
        if (BVar5 == 0) {
          local_410 = GetLastError();
          goto LAB_0052cf05;
        }
        local_41c = local_41c + local_424;
        if (((int)local_424 < (int)pcVar4 - (int)local_40c) ||
           (param_3 <= (uint)((int)local_418 - (int)param_2))) goto LAB_0052cf05;
      } while( true );
    }
  }
  if (((*(byte *)(*piVar1 + 4 + iVar8) & 0x40) != 0) && (*param_2 == '\x1a')) {
    return 0;
  }
  puVar6 = (undefined4 *)FUN_0052b6d4();
  *puVar6 = 0x1c;
  puVar6 = (undefined4 *)FUN_0052b6dd();
  *puVar6 = 0;
  return -1;
}

