/* FUN_00436fd0 - 0x00436fd0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_00436fd0(int param_1,int param_2,int param_3,int param_4,int param_5)

{
  int iVar1;
  char cVar2;
  uint uVar3;
  undefined4 *puVar4;
  int iVar5;
  int iVar6;
  bool bVar7;
  int local_8;
  int local_4;
  
  iVar1 = param_3;
  cVar2 = FUN_004065a0();
  if (cVar2 == '\0') {
    if (0 < param_3) {
      param_3 = 0;
      local_8 = 0;
      local_4 = iVar1;
      do {
        uVar3 = _rand();
        uVar3 = uVar3 & 0x80000001;
        bVar7 = uVar3 == 0;
        if ((int)uVar3 < 0) {
          bVar7 = (uVar3 - 1 | 0xfffffffe) == 0xffffffff;
        }
        if (bVar7) {
          puVar4 = operator_new(0x50);
          if (puVar4 == (undefined4 *)0x0) {
            puVar4 = (undefined4 *)0x0;
          }
          else {
            puVar4[1] = 0x2e634;
            puVar4[2] = 0xffffffff;
            puVar4[3] = 0;
            puVar4[4] = 0;
            *(undefined1 *)(puVar4 + 5) = 0;
            *(undefined1 *)((int)puVar4 + 0x15) = 0;
            puVar4[6] = 0xffffffff;
            puVar4[7] = 0;
            *(undefined1 *)(puVar4 + 8) = 0;
            puVar4[10] = 0;
            puVar4[0xb] = 0;
            puVar4[9] = 0xffffffff;
            *puVar4 = &PTR_FUN_00555ec8;
            puVar4[0x10] = 0;
            puVar4[0x12] = 0x10;
            puVar4[0x13] = 0x80;
          }
          iVar5 = _rand();
          puVar4[0xe] = local_8 / iVar1 + -4 + iVar5 % 9 + param_4;
          iVar5 = _rand();
          puVar4[0xf] = param_3 / iVar1 + -4 + iVar5 % 9 + param_5;
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar5 = PeekPacketChecksumState();
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar6 = _rand();
          puVar4[0x11] = iVar6 % iVar5;
          RegisterActiveObject();
        }
        param_3 = param_3 + (param_2 - param_5);
        local_8 = local_8 + (param_1 - param_4);
        local_4 = local_4 + -1;
      } while (local_4 != 0);
    }
  }
  return;
}

