/* FUN_0052d3f5 - 0x0052d3f5 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    __read_lk
   
   Library: Visual Studio 2003 Release */

int __read_lk(uint param_1,char *param_2,char *param_3)

{
  int *piVar1;
  byte *pbVar2;
  char *pcVar3;
  byte bVar4;
  char cVar5;
  BOOL BVar6;
  DWORD DVar7;
  undefined4 *puVar8;
  char *pcVar9;
  int iVar10;
  DWORD local_10;
  char *local_c;
  char local_5;
  
  local_c = (char *)0x0;
  if (param_3 != (char *)0x0) {
    piVar1 = &DAT_00f28320 + ((int)param_1 >> 5);
    iVar10 = (param_1 & 0x1f) * 0x24;
    bVar4 = *(byte *)(*piVar1 + iVar10 + 4);
    if ((bVar4 & 2) == 0) {
      pcVar9 = param_2;
      if (((bVar4 & 0x48) != 0) && (*(char *)(*piVar1 + iVar10 + 5) != '\n')) {
        param_3 = (char *)((int)param_3 - 1);
        *param_2 = *(char *)(*piVar1 + 5 + iVar10);
        pcVar9 = param_2 + 1;
        local_c = (char *)0x1;
        *(undefined1 *)(*piVar1 + 5 + iVar10) = 10;
      }
      BVar6 = ReadFile(*(HANDLE *)(*piVar1 + iVar10),pcVar9,(DWORD)param_3,&local_10,
                       (LPOVERLAPPED)0x0);
      if (BVar6 == 0) {
        DVar7 = GetLastError();
        if (DVar7 == 5) {
          puVar8 = (undefined4 *)FUN_0052b6d4();
          *puVar8 = 9;
          puVar8 = (undefined4 *)FUN_0052b6dd();
          *puVar8 = 5;
        }
        else {
          if (DVar7 == 0x6d) {
            return 0;
          }
          __dosmaperr(DVar7);
        }
        return -1;
      }
      if ((*(byte *)(*piVar1 + 4 + iVar10) & 0x80) == 0) {
        return (int)local_c + local_10;
      }
      if ((local_10 == 0) || (*param_2 != '\n')) {
        pbVar2 = (byte *)(*piVar1 + 4 + iVar10);
        *pbVar2 = *pbVar2 & 0xfb;
      }
      else {
        pbVar2 = (byte *)(*piVar1 + 4 + iVar10);
        *pbVar2 = *pbVar2 | 4;
      }
      local_c = param_2 + (int)local_c + local_10;
      param_3 = param_2;
      pcVar9 = param_2;
      if (param_2 < local_c) {
        do {
          cVar5 = *param_3;
          if (cVar5 == '\x1a') {
            if ((*(byte *)(*piVar1 + 4 + iVar10) & 0x40) == 0) {
              pbVar2 = (byte *)(*piVar1 + 4 + iVar10);
              *pbVar2 = *pbVar2 | 2;
            }
            break;
          }
          if (cVar5 == '\r') {
            if (param_3 < local_c + -1) {
              if (param_3[1] == '\n') {
                pcVar3 = param_3 + 2;
                goto LAB_0052d582;
              }
LAB_0052d59c:
              param_3 = param_3 + 1;
              *pcVar9 = '\r';
            }
            else {
              pcVar3 = param_3 + 1;
              BVar6 = ReadFile(*(HANDLE *)(*piVar1 + iVar10),&local_5,1,&local_10,(LPOVERLAPPED)0x0)
              ;
              if (((BVar6 == 0) && (DVar7 = GetLastError(), DVar7 != 0)) || (local_10 == 0))
              goto LAB_0052d59c;
              if ((*(byte *)(*piVar1 + 4 + iVar10) & 0x48) == 0) {
                if ((pcVar9 == param_2) && (local_5 == '\n')) goto LAB_0052d582;
                __lseek_lk(param_1,0xffffffff,1);
                if (local_5 == '\n') goto LAB_0052d5a0;
                goto LAB_0052d59c;
              }
              if (local_5 == '\n') {
LAB_0052d582:
                param_3 = pcVar3;
                *pcVar9 = '\n';
              }
              else {
                *pcVar9 = '\r';
                *(char *)(*piVar1 + 5 + iVar10) = local_5;
                param_3 = pcVar3;
              }
            }
            pcVar9 = pcVar9 + 1;
            pcVar3 = param_3;
          }
          else {
            *pcVar9 = cVar5;
            pcVar9 = pcVar9 + 1;
            pcVar3 = param_3 + 1;
          }
LAB_0052d5a0:
          param_3 = pcVar3;
        } while (param_3 < local_c);
      }
      return (int)pcVar9 - (int)param_2;
    }
  }
  return 0;
}

