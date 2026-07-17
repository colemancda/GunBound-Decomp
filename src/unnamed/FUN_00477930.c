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
  undefined1 local_ac0 [548];
  undefined1 local_89c [548];
  undefined1 local_678 [548];
  undefined1 local_454 [548];
  undefined1 local_230 [548];
  undefined4 local_c;
  undefined1 *puStack_8;
  int local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_00539e97;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  uVar2 = EncodeChecksumDeltaSub(param_1 + 0x1178,local_230,*(undefined4 *)(&g_nCameraY + g_clientContext));
  local_4 = 0;
  uVar2 = EncodeChecksumDeltaAdd(uVar2,local_678,0x104);
  local_4 = 1;
  EncodeChecksumDeltaAdd(uVar2,local_89c,0x26);
  local_4 = 2;
  uVar2 = EncodeChecksumDeltaSub(param_1 + 0xf54,local_ac0,*(undefined4 *)(&g_nCameraX + g_clientContext));
  local_4 = 3;
  EncodeChecksumDeltaAdd(uVar2,local_454,400);
  local_4 = 4;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar3 = PeekPacketChecksumState();
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar1 = *(int *)(param_1 + 0x30);
  if ((DAT_0079352c != 0) && (-1 < iVar1)) {
    iVar4 = FindSpriteFrame();
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
  if ((*(int *)(local_454 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_ac8);
  }
  local_4 = 2;
  if ((*(int *)(local_ac0 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_ac8);
  }
  local_4 = 1;
  if ((*(int *)(local_89c + 0x14)) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_ac8);
  }
  local_4 = 0;
  if ((*(int *)(local_678 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_ac8);
  }
  local_4 = 0xffffffff;
  if ((*(int *)(local_230 + 0x14)) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_ac8);
  }
  *unaff_FS_OFFSET = local_c;
  return;
}

