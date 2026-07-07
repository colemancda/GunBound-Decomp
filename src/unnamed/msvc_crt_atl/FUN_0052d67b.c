/* FUN_0052d67b - 0x0052d67b in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* Library Function - Single Match
    __ioinit
   
   Library: Visual Studio 2003 Release */

int __cdecl __ioinit(void)

{
  int *piVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined4 *puVar5;
  DWORD DVar6;
  HANDLE hFile;
  int iVar7;
  uint uVar8;
  byte *pbVar9;
  HGLOBAL pvVar10;
  HGLOBAL pvVar11;
  byte *local_48;
  _STARTUPINFOA local_44;
  
  puVar3 = _malloc(0x480);
  if (puVar3 == (undefined4 *)0x0) {
    iVar4 = -1;
  }
  else {
    DAT_00f28314 = (HGLOBAL)0x20;
    DAT_00f28320 = puVar3;
    for (; puVar3 < DAT_00f28320 + 0x120; puVar3 = puVar3 + 9) {
      *puVar3 = 0xffffffff;
      puVar3[2] = 0;
      *(undefined1 *)(puVar3 + 1) = 0;
      *(undefined1 *)((int)puVar3 + 5) = 10;
    }
    GetStartupInfoA(&local_44);
    if ((local_44.cbReserved2 != 0) && ((int *)local_44.lpReserved2 != (int *)0x0)) {
      pvVar10 = *(HGLOBAL *)local_44.lpReserved2;
      pbVar9 = (byte *)((int)local_44.lpReserved2 + 4);
      local_48 = (byte *)((int)pvVar10 + (int)pbVar9);
      if (0x7ff < (int)pvVar10) {
        pvVar10 = (HGLOBAL)0x800;
      }
      pvVar11 = pvVar10;
      if ((int)DAT_00f28314 < (int)pvVar10) {
        puVar3 = &DAT_00f28324;
        do {
          puVar5 = _malloc(0x480);
          pvVar11 = DAT_00f28314;
          if (puVar5 == (undefined4 *)0x0) break;
          DAT_00f28314 = (HGLOBAL)((int)DAT_00f28314 + 0x20);
          *puVar3 = puVar5;
          puVar2 = puVar5;
          for (; puVar5 < puVar2 + 0x120; puVar5 = puVar5 + 9) {
            *puVar5 = 0xffffffff;
            puVar5[2] = 0;
            *(undefined1 *)(puVar5 + 1) = 0;
            *(undefined1 *)((int)puVar5 + 5) = 10;
            puVar2 = (undefined4 *)*puVar3;
          }
          puVar3 = puVar3 + 1;
          pvVar11 = pvVar10;
        } while ((int)DAT_00f28314 < (int)pvVar10);
      }
      uVar8 = 0;
      if (0 < (int)pvVar11) {
        do {
          if (((*(HANDLE *)local_48 != (HANDLE)0xffffffff) && ((*pbVar9 & 1) != 0)) &&
             (((*pbVar9 & 8) != 0 || (DVar6 = GetFileType(*(HANDLE *)local_48), DVar6 != 0)))) {
            puVar3 = (undefined4 *)((int)(&DAT_00f28320)[(int)uVar8 >> 5] + (uVar8 & 0x1f) * 0x24);
            *puVar3 = *(undefined4 *)local_48;
            *(byte *)(puVar3 + 1) = *pbVar9;
            iVar4 = ___crtInitCritSecAndSpinCount(puVar3 + 3,4000);
            if (iVar4 == 0) {
              return -1;
            }
            puVar3[2] = puVar3[2] + 1;
          }
          local_48 = local_48 + 4;
          uVar8 = uVar8 + 1;
          pbVar9 = pbVar9 + 1;
        } while ((int)uVar8 < (int)pvVar11);
      }
    }
    iVar4 = 0;
    do {
      piVar1 = DAT_00f28320 + iVar4 * 9;
      if (*piVar1 == -1) {
        *(undefined1 *)(piVar1 + 1) = 0x81;
        if (iVar4 == 0) {
          DVar6 = 0xfffffff6;
        }
        else {
          DVar6 = 0xfffffff5 - (iVar4 != 1);
        }
        hFile = GetStdHandle(DVar6);
        if ((hFile == (HANDLE)0xffffffff) || (DVar6 = GetFileType(hFile), DVar6 == 0)) {
          *(byte *)(piVar1 + 1) = *(byte *)(piVar1 + 1) | 0x40;
        }
        else {
          *piVar1 = (int)hFile;
          if ((DVar6 & 0xff) == 2) {
            *(byte *)(piVar1 + 1) = *(byte *)(piVar1 + 1) | 0x40;
          }
          else if ((DVar6 & 0xff) == 3) {
            *(byte *)(piVar1 + 1) = *(byte *)(piVar1 + 1) | 8;
          }
          iVar7 = ___crtInitCritSecAndSpinCount(piVar1 + 3,4000);
          if (iVar7 == 0) {
            return -1;
          }
          piVar1[2] = piVar1[2] + 1;
        }
      }
      else {
        *(byte *)(piVar1 + 1) = *(byte *)(piVar1 + 1) | 0x80;
      }
      iVar4 = iVar4 + 1;
    } while (iVar4 < 3);
    LockResource(DAT_00f28314);
    iVar4 = 0;
  }
  return iVar4;
}

