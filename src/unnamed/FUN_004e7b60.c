/* FUN_004e7b60 - 0x004e7b60 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


uint FUN_004e7b60(int param_1,undefined4 *param_2,uint *param_3)

{
  ushort uVar1;
  uint uVar2;
  void *_Dst;
  int iVar3;
  uint uVar4;
  undefined4 *puVar5;
  int iVar6;
  int local_c;
  char local_8 [8];
  
  uVar2 = 0;
  if (*(int *)(param_1 + 0x454a8) == 0) {
    return 0;
  }
  uVar4 = 0;
  local_8[0] = '\0';
  local_8[1] = 0;
  local_8[2] = 0;
  local_8[3] = 0;
  local_8[4] = 0;
  local_8[5] = 0;
  local_8[6] = 0;
  local_8[7] = 0;
  if (*(int *)(param_1 + 0x454a8) != 0) {
    iVar6 = 0;
    if (*(int *)(param_1 + 0x454a8) == 0) {
                    /* WARNING: Subroutine does not return */
      ThrowCxxException(0x80070057);
    }
    do {
      FUN_004e8a70();
      if (local_c == *(int *)(param_1 + 0x45234)) {
        if (*(uint *)(param_1 + 0x454a8) <= uVar4) {
                    /* WARNING: Subroutine does not return */
          ThrowCxxException(0x80070057);
        }
        if (local_8[*(byte *)(*(int *)(param_1 + 0x454a4) + 4 + iVar6)] == '\0') {
          if (*(uint *)(param_1 + 0x454a8) <= uVar4) {
                    /* WARNING: Subroutine does not return */
            ThrowCxxException(0x80070057);
          }
          iVar6 = uVar4 * 0x206;
          uVar1 = *(ushort *)(*(int *)(param_1 + 0x454a4) + 2 + iVar6);
          *param_3 = (uint)uVar1;
          if (uVar4 < *(uint *)(param_1 + 0x454a8)) {
            puVar5 = (undefined4 *)(iVar6 + 5 + *(int *)(param_1 + 0x454a4));
            for (uVar2 = (uint)(uVar1 >> 2); uVar2 != 0; uVar2 = uVar2 - 1) {
              *param_2 = *puVar5;
              puVar5 = puVar5 + 1;
              param_2 = param_2 + 1;
            }
            for (uVar2 = uVar1 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
              *(undefined1 *)param_2 = *(undefined1 *)puVar5;
              puVar5 = (undefined4 *)((int)puVar5 + 1);
              param_2 = (undefined4 *)((int)param_2 + 1);
            }
            if (uVar4 + 1 <= *(uint *)(param_1 + 0x454a8)) {
              iVar3 = (*(uint *)(param_1 + 0x454a8) - uVar4) + -1;
              if (iVar3 != 0) {
                _Dst = (void *)(iVar6 + *(int *)(param_1 + 0x454a4));
                _memmove(_Dst,(void *)((int)_Dst + 0x206),iVar3 * 0x206);
              }
              iVar6 = *(int *)(param_1 + 0x454a8) + -1;
              *(int *)(param_1 + 0x454a8) = iVar6;
              return CONCAT31((int3)((uint)iVar6 >> 8),1);
            }
                    /* WARNING: Subroutine does not return */
            ThrowCxxException(0x80070057);
          }
                    /* WARNING: Subroutine does not return */
          ThrowCxxException(0x80070057);
        }
      }
      else {
        if (*(uint *)(param_1 + 0x454a8) <= uVar4) {
                    /* WARNING: Subroutine does not return */
          ThrowCxxException(0x80070057);
        }
        local_8[*(byte *)(*(int *)(param_1 + 0x454a4) + 4 + iVar6)] = '\x01';
      }
      uVar2 = *(uint *)(param_1 + 0x454a8);
      uVar4 = uVar4 + 1;
      iVar6 = iVar6 + 0x206;
    } while (uVar4 < uVar2);
  }
  return uVar2 & 0xffffff00;
}

