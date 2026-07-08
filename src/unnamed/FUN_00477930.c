/* FUN_00477930 - 0x00477930 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_00477930(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 *unaff_FS_OFFSET;
  undefined1 local_ac8 [8];
  undefined1 local_ac0 [20];
  int local_aac;
  undefined1 local_89c [20];
  int local_888;
  undefined1 local_678 [20];
  int local_664;
  undefined1 local_454 [20];
  int local_440;
  undefined1 local_230 [20];
  int local_21c;
  undefined4 local_c;
  undefined1 *puStack_8;
  int local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_00539e97;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  uVar2 = FUN_0040a6e0(param_1 + 0x1178,local_230,*(undefined4 *)(&DAT_006a7714 + g_clientContext));
  local_4 = 0;
  uVar2 = FUN_0040a5f0(uVar2,local_678,0x104);
  local_4 = 1;
  FUN_0040a5f0(uVar2,local_89c,0x26);
  local_4 = 2;
  uVar2 = FUN_0040a6e0(param_1 + 0xf54,local_ac0,*(undefined4 *)(&DAT_006a7710 + g_clientContext));
  local_4 = 3;
  FUN_0040a5f0(uVar2,local_454,400);
  local_4 = 4;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar3 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar1 = *(int *)(param_1 + 0x30);
  if ((DAT_0079352c != 0) && (-1 < iVar1)) {
    iVar4 = FUN_004f30c0();
    if (iVar4 != 0) {
      if (*(char *)(iVar4 + 0x18) == '\x01') {
        BlitSprite16bpp(uVar3,uVar2);
      }
      else {
        BlitSpriteClipped(iVar1);
      }
    }
  }
  local_4 = 3;
  if (local_440 != 0) {
    FUN_0040a240();
    FUN_0040b540(local_ac8);
  }
  local_4 = 2;
  if (local_aac != 0) {
    FUN_0040a240();
    FUN_0040b540(local_ac8);
  }
  local_4 = 1;
  if (local_888 != 0) {
    FUN_0040a240();
    FUN_0040b540(local_ac8);
  }
  local_4 = 0;
  if (local_664 != 0) {
    FUN_0040a240();
    FUN_0040b540(local_ac8);
  }
  local_4 = 0xffffffff;
  if (local_21c != 0) {
    FUN_0040a240();
    FUN_0040b540(local_ac8);
  }
  *unaff_FS_OFFSET = local_c;
  return;
}

