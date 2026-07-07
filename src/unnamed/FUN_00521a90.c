/* FUN_00521a90 - 0x00521a90 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

void FUN_00521a90(int *param_1,char *param_2)

{
  byte *_Dest;
  byte bVar1;
  int iVar2;
  char *_Format;
  byte *pbVar3;
  uint uVar4;
  DWORD nNumberOfBytesToWrite;
  DWORD local_1004;
  char local_1000 [4092];
  undefined4 uStack_4;
  
  uStack_4 = 0x521a9a;
  if (*param_1 != -1) {
    if ((param_1[0x40d] != 0) && (*param_2 != '!')) {
      if ((uint)param_1[0x40d] < (uint)param_1[0x40e]) {
        return;
      }
      param_1[0x40e] = param_1[0x40e] + 1;
    }
    EnterCriticalSection((LPCRITICAL_SECTION)(param_1 + 1));
    _vsprintf(local_1000,param_2,&stack0x0000000c);
    GetLocalTime((LPSYSTEMTIME)(param_1 + 0x407));
    _Dest = (byte *)(param_1 + 7);
    _Format = (char *)FUN_005218c0(&DAT_0056a3dc,(short)param_1[0x409],
                                   *(undefined2 *)((int)param_1 + 0x1026),(short)param_1[0x40a],
                                   *(undefined2 *)((int)param_1 + 0x102a),local_1000);
    _sprintf((char *)_Dest,_Format);
    uVar4 = 0xffffffff;
    pbVar3 = _Dest;
    do {
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      bVar1 = *pbVar3;
      pbVar3 = pbVar3 + 1;
    } while (bVar1 != 0);
    nNumberOfBytesToWrite = ~uVar4 - 1;
    if (param_1[0x40c] == 0) {
      if (0 < (int)nNumberOfBytesToWrite) {
        pbVar3 = _Dest;
        do {
          iVar2 = param_1[0x40b] * 3 + 1;
          param_1[0x40b] = iVar2;
          *pbVar3 = *pbVar3 ^ (char)iVar2 + 0x46U;
          pbVar3 = pbVar3 + 1;
        } while ((int)(pbVar3 + (-0x1c - (int)param_1)) < (int)nNumberOfBytesToWrite);
      }
    }
    else if (0 < (int)nNumberOfBytesToWrite) {
      pbVar3 = _Dest;
      do {
        iVar2 = param_1[0x40c];
        param_1[0x40c] = iVar2 + 2;
        *pbVar3 = *pbVar3 ^ (char)(iVar2 + 2) + 0x43U;
        pbVar3 = pbVar3 + 1;
      } while ((int)(pbVar3 + (-0x1c - (int)param_1)) < (int)nNumberOfBytesToWrite);
    }
    WriteFile((HANDLE)*param_1,_Dest,nNumberOfBytesToWrite,&local_1004,(LPOVERLAPPED)0x0);
    LeaveCriticalSection((LPCRITICAL_SECTION)(param_1 + 1));
  }
  return;
}

