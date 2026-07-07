/* FUN_004ffe80 - 0x004ffe80 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004ffe80(undefined4 *param_1)

{
  char *pcVar1;
  char *_Source;
  char cVar2;
  uint uVar3;
  __time32_t _Var4;
  int *piVar5;
  int iVar6;
  int iVar7;
  SOCKET s;
  uint local_44;
  char *local_40;
  sockaddr local_38;
  ushort local_28;
  undefined1 local_26 [16];
  char local_16 [16];
  undefined4 local_6;
  
  local_28 = 0x26;
  cVar2 = FUN_004fcd80(local_26,0x10);
  if (cVar2 != '\0') {
    local_38.sa_family = 2;
    if (param_1[0xa5] != 0) {
      uVar3 = 0;
      if (param_1[0xa6] != 0) {
        piVar5 = (int *)param_1[0xa4];
        do {
          if (*piVar5 != 0) {
            local_40 = (char *)((int *)param_1[0xa4])[uVar3];
            goto joined_r0x004ffee3;
          }
          uVar3 = uVar3 + 1;
          piVar5 = piVar5 + 1;
        } while (uVar3 < (uint)param_1[0xa6]);
      }
    }
    local_40 = (char *)0x0;
joined_r0x004ffee3:
    _Source = local_40;
    if (_Source != (char *)0x0) {
      local_40 = _Source;
      if ((_Source != (char *)0x0) &&
         (local_40 = *(char **)(_Source + 0xa4), local_40 == (char *)0x0)) {
        uVar3 = *(uint *)(_Source + 0xa8) % (uint)param_1[0xa6];
        do {
          uVar3 = uVar3 + 1;
          if ((uint)param_1[0xa6] <= uVar3) break;
          pcVar1 = *(char **)(param_1[0xa4] + uVar3 * 4);
          if (pcVar1 != (char *)0x0) {
            local_40 = pcVar1;
          }
        } while (local_40 == (char *)0x0);
      }
      if (_Source[0x30] == '\0') {
        _strncpy(local_16,_Source,0x10);
        local_6 = *(undefined4 *)(_Source + 0x2c);
        *(int *)(_Source + 0x2c) = *(int *)(_Source + 0x2c) + 1;
        if (*(int *)(_Source + 0x14) == 0) {
          if (*(int *)(_Source + 0x1c) != 0) {
            local_38.sa_data._0_2_ = *(undefined2 *)(_Source + 0x20);
            local_38.sa_data._2_4_ = *(int *)(_Source + 0x1c);
            sendto(param_1[0xa2],(char *)&local_28,(uint)local_28,0,&local_38,0x10);
          }
          if (*(int *)(_Source + 0x24) == 0) goto LAB_00500008;
          s = param_1[0xa2];
          local_38.sa_data._0_2_ = *(undefined2 *)(_Source + 0x28);
          local_38.sa_data._2_4_ = *(int *)(_Source + 0x24);
        }
        else {
          local_38.sa_data._0_2_ = *(undefined2 *)(_Source + 0x18);
          s = param_1[0xa2];
          local_38.sa_data._2_4_ = *(int *)(_Source + 0x14);
        }
        sendto(s,(char *)&local_28,(uint)local_28,0,&local_38,0x10);
      }
LAB_00500008:
      local_44 = *(uint *)(_Source + 0x98);
      uVar3 = local_44 - 1;
      if (-1 < (int)uVar3) {
        iVar6 = uVar3 * 0x1750;
        do {
          if (*(uint *)(_Source + 0x98) <= uVar3) {
LAB_005000d3:
                    /* WARNING: Subroutine does not return */
            FUN_004010c0(0x80070057);
          }
          iVar7 = *(int *)(_Source + 0x94) + iVar6;
          _Var4 = FID_conflict___time32((__time32_t *)0x0);
          if (0x3c < _Var4 - *(int *)(iVar7 + 0x174c)) {
            (**(code **)*param_1)
                      (0,_Source,*(undefined2 *)(iVar7 + 0xc),iVar7 + 0x10,
                       *(undefined2 *)(iVar7 + 0xe),iVar7);
            if (*(uint *)(_Source + 0x98) < local_44) goto LAB_005000d3;
            iVar7 = (*(uint *)(_Source + 0x98) - uVar3) + -1;
            if (iVar7 != 0) {
              _memmove((void *)(*(int *)(_Source + 0x94) + iVar6),
                       (void *)(*(int *)(_Source + 0x94) + iVar6 + 0x1750),iVar7 * 0x1750);
            }
            *(int *)(_Source + 0x98) = *(int *)(_Source + 0x98) + -1;
          }
          uVar3 = uVar3 - 1;
          local_44 = local_44 - 1;
          iVar6 = iVar6 + -0x1750;
        } while (-1 < (int)uVar3);
      }
      goto joined_r0x004ffee3;
    }
  }
  return;
}

