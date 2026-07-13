/* FUN_00437150 - 0x00437150 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00437150(int param_1,int param_2,int param_3,int param_4)

{
  char cVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  int local_8;
  
  cVar1 = PeekPacketChecksumBool();
  if ((cVar1 == '\0') &&
     (local_8 = 0, 0 < (int)((uint)(byte)(&DAT_005f2f54)[g_clientContext] * param_4))) {
    do {
      puVar2 = operator_new(0x58);
      puVar5 = (undefined4 *)0x0;
      if (puVar2 != (undefined4 *)0x0) {
        puVar2[3] = 0;
        puVar2[4] = 0;
        puVar2[7] = 0;
        puVar2[10] = 0;
        puVar2[0xb] = 0;
        puVar2[0x10] = 0;
        puVar2[1] = 0x2e633;
        puVar2[2] = 0xffffffff;
        *(undefined1 *)(puVar2 + 5) = 0;
        *(undefined1 *)((int)puVar2 + 0x15) = 0;
        puVar2[6] = 0xffffffff;
        *(undefined1 *)(puVar2 + 8) = 0;
        puVar2[9] = 0xffffffff;
        *puVar2 = &PTR_FUN_00555ce0;
        puVar2[0x12] = 0x10;
        puVar2[0x13] = 0x80;
        puVar5 = puVar2;
      }
      iVar3 = _rand();
      puVar5[0xe] = (iVar3 % param_3 - param_3 / 2) + param_1;
      iVar3 = _rand();
      puVar5[0xf] = (iVar3 % param_3 - param_3 / 2) + param_2;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar3 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar4 = _rand();
      puVar5[0x11] = iVar4 % iVar3;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar3 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar4 = _rand();
      puVar5[0x14] = iVar4 % 0x15 - iVar3;
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar3 = PeekPacketChecksumState();
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar4 = _rand();
      puVar5[0x15] = iVar4 % 0x15 - iVar3;
      RegisterActiveObject(0, 0, (undefined4 *)0);
      local_8 = local_8 + 1;
    } while (local_8 < (int)((uint)(byte)(&DAT_005f2f54)[g_clientContext] * param_4));
  }
  return;
}

