/* FUN_0044b460 - 0x0044b460 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_0044b460(void)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int unaff_ESI;
  
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar1 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar2 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar4 = (*(char *)(iVar2 + *(int *)(unaff_ESI + 0x450) * 9 + 0x2d54c + unaff_ESI) != '\x01') - 1 &
          0x8000;
  switch(*(undefined4 *)(unaff_ESI + 0x44c)) {
  case 0:
    uVar3 = 0xffffffff;
    uVar1 = uVar4 | uVar1 & 0xffff;
    uVar4 = 0xffffffff;
    goto LAB_0044b59d;
  case 1:
    FUN_004141b0(uVar4 | uVar1 & 0xffff,0xffffffff,0xffffffff,0xffffffff,unaff_ESI + 0x31488,200000,
                 300000);
    FUN_00449250(unaff_ESI,1,1);
    return;
  case 2:
    uVar4 = uVar4 | uVar1 & 0xffff;
    uVar3 = 0xffffffff;
    break;
  case 3:
    uVar3 = uVar4 | uVar1 & 0xffff;
    uVar4 = 0xffffffff;
    break;
  default:
    goto switchD_0044b51a_default;
  }
  uVar1 = 0xffffffff;
LAB_0044b59d:
  FUN_004141b0(0xffffffff,uVar1,uVar4,uVar3,unaff_ESI + 0x31488,200000,300000);
switchD_0044b51a_default:
  FUN_00449250(unaff_ESI,1,1);
  return;
}

