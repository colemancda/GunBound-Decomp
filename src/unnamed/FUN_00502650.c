/* FUN_00502650 - 0x00502650 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

uint FUN_00502650(int param_1,int param_2,int param_3,undefined4 *param_4,uint param_5)

{
  uint uVar1;
  uint uVar2;
  char *_Dest;
  undefined4 *puVar3;
  int iVar4;
  undefined4 local_2ee3;
  undefined1 local_1778 [5996];
  undefined4 uStack_c;
  
  uStack_c = 0x502660;
  if (0xff < (ushort)param_5) {
    param_5 = 0xff;
  }
  if (0 < param_2) {
    if (100 < param_2) {
      param_2 = 100;
    }
    uVar1 = param_5 & 0xffff;
    puVar3 = &local_2ee3;
    for (uVar2 = uVar1 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
      *puVar3 = *param_4;
      param_4 = param_4 + 1;
      puVar3 = puVar3 + 1;
    }
    for (param_5 = param_5 & 3; param_5 != 0; param_5 = param_5 - 1) {
      *(undefined1 *)puVar3 = *(undefined1 *)param_4;
      param_4 = (undefined4 *)((int)param_4 + 1);
      puVar3 = (undefined4 *)((int)puVar3 + 1);
    }
    *(short *)((int)&local_2ee3 + uVar1) = (short)param_2;
    _Dest = (char *)((int)&local_2ee3 + uVar1 + 2);
    if (0 < param_2) {
      iVar4 = 0;
      do {
        _strncpy(_Dest,*(char **)(param_3 + iVar4 * 4),0x10);
        _Dest = _Dest + 0x10;
        iVar4 = iVar4 + 1;
      } while (iVar4 < param_2);
    }
    param_5 = FUN_004f7210(*(undefined4 *)(param_1 + 0x1a78),local_1778,6000);
    if ((char)param_5 != '\0') {
      uVar1 = FUN_00502500(0x2020);
      return uVar1;
    }
  }
  return param_5 & 0xffffff00;
}

