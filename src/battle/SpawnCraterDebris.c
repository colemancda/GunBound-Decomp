/* SpawnCraterDebris - 0x00439600 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


uint SpawnCraterDebris(int *param_1,int param_2,int param_3,int param_4,int param_5,int param_6)

{
  byte bVar1;
  int iVar2;
  int in_EAX;
  uint uVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  int iVar7;
  int *piVar8;
  int local_94;
  char local_80 [128];
  
  uVar3 = PeekPacketChecksumBool();
  if ((char)uVar3 == '\0') {
    bVar1 = (&DAT_005f2f54)[g_clientContext];
    uVar3 = (uint)bVar1;
    if (bVar1 != 1) {
      if (bVar1 == 3) {
        local_94 = in_EAX / 2;
      }
      else {
        local_94 = (int)(in_EAX + (in_EAX >> 0x1f & 3U)) >> 2;
      }
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar4 = FloatToInt64();
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar5 = FloatToInt64();
      uVar3 = param_4 * -0x55555554;
      iVar2 = (param_4 * 2) / 3;
      if (0 < local_94) {
        do {
          piVar6 = operator_new(0x5c);
          piVar8 = (int *)0x0;
          if (piVar6 != (int *)0x0) {
            piVar6[3] = 0;
            piVar6[4] = 0;
            piVar6[7] = 0;
            piVar6[10] = 0;
            piVar6[0xb] = 0;
            piVar6[0x10] = 0;
            piVar6[1] = 0x186a8;
            piVar6[2] = -1;
            *(undefined1 *)(piVar6 + 5) = 0;
            *(undefined1 *)((int)piVar6 + 0x15) = 0;
            piVar6[6] = -1;
            *(undefined1 *)(piVar6 + 8) = 0;
            piVar6[9] = -1;
            *piVar6 = (int)&PTR_FUN_005562f4;
            piVar8 = piVar6;
          }
          iVar7 = _rand();
          piVar8[0xe] = (iVar7 % param_4 - param_4 / 2) + param_2;
          iVar7 = _rand();
          piVar8[0xf] = (iVar7 % param_4 - param_4 / 2) + param_3;
          iVar7 = _rand();
          piVar8[0x13] = (iVar7 % iVar2 - iVar2 / 2) + param_5 / 300;
          iVar7 = _rand();
          piVar8[0x15] = iVar4;
          piVar8[0x14] = param_6 / 300 - iVar7 % iVar2;
          piVar8[0x16] = 0x3c - iVar5;
          iVar7 = _rand();
          piVar8[0x11] = iVar7 % 0x32 + 10;
          piVar8[7] = *param_1;
          uVar3 = _rand();
          uVar3 = uVar3 & 0x80000007;
          if ((int)uVar3 < 0) {
            uVar3 = (uVar3 - 1 | 0xfffffff8) + 1;
          }
          _sprintf(local_80,s_ani__02d_00553b98,uVar3 + 1);
          (**(code **)(*piVar8 + 4))(local_80);
          uVar3 = RegisterActiveObject();
          local_94 = local_94 + -1;
        } while (local_94 != 0);
      }
    }
  }
  return uVar3;
}

