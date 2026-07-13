/* FUN_004372f0 - 0x004372f0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __thiscall
FUN_004372f0(char param_1,undefined4 param_2,int param_3,int param_4,int param_5,undefined4 param_6)

{
  char cVar1;
  void *pvVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  
  cVar1 = PeekPacketChecksumBool();
  if (cVar1 == '\0') {
    pvVar2 = operator_new(0x54);
    if (pvVar2 == (void *)0x0) {
      piVar3 = (int *)0x0;
    }
    else {
      FUN_00471af0();
    }
    piVar3[0xe] = param_3;
    piVar3[0xf] = param_4;
    if (param_1 == '\0') {
      iVar5 = 0;
    }
    else {
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar4 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar5 = _rand();
      iVar5 = iVar5 % iVar4;
    }
    *(char *)(piVar3 + 0x14) = param_1;
    piVar3[0x11] = iVar5;
    piVar3[6] = param_5;
    iVar5 = FindPreloadedTextureByName(param_6);
    piVar3[7] = iVar5;
    (**(code **)(*piVar3 + 4))(s_flame_00553d2c);
    RegisterActiveObject(0, 0, (undefined4 *)0);
  }
  return;
}

