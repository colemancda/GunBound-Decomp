/* FUN_00436980 - 0x00436980 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __thiscall FUN_00436980(undefined4 param_1,int param_2,int param_3,int param_4)

{
  char cVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  int iVar6;
  
  cVar1 = FUN_004065a0(param_1);
  if ((cVar1 == '\0') && (iVar6 = 0, (&DAT_005f2f54)[DAT_005b3484] != '\0')) {
    do {
      puVar2 = operator_new(0x4c);
      puVar5 = (undefined4 *)0x0;
      if (puVar2 != (undefined4 *)0x0) {
        puVar2[3] = 0;
        puVar2[4] = 0;
        puVar2[7] = 0;
        puVar2[10] = 0;
        puVar2[0xb] = 0;
        puVar2[0x10] = 0;
        puVar2[1] = 0x30d41;
        puVar2[2] = 0xffffffff;
        *(undefined1 *)(puVar2 + 5) = 0;
        *(undefined1 *)((int)puVar2 + 0x15) = 0;
        puVar2[6] = 0xffffffff;
        *(undefined1 *)(puVar2 + 8) = 0;
        puVar2[9] = 0xffffffff;
        *puVar2 = &PTR_FUN_00555c54;
        puVar5 = puVar2;
      }
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar3 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar4 = _rand();
      puVar5[0xe] = (iVar4 % 0x15 - iVar3) + param_2;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar3 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar4 = _rand();
      puVar5[0xf] = (iVar4 % 0x15 - iVar3) + param_3;
      iVar3 = _rand();
      puVar5[0x11] = iVar3 % 10 + 10;
      *(undefined2 *)(puVar5 + 0x12) = param_4;
      RegisterActiveObject();
      iVar6 = iVar6 + 1;
    } while (iVar6 < (int)((uint)(byte)(&DAT_005f2f54)[DAT_005b3484] * 2));
  }
  return;
}

