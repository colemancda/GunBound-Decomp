/* HitTestMine - 0x00425e60 in the original binary.
 *
 * NAMED 2026-08-19 (was FUN_00425e60).  Finds the MINE at slot EDX and
 * returns it when the point (param_3, param_4) is in range, else 0 - the
 * layer-100003 sibling of HitTestLocalMobile (players) and HitTestJewel.
 *
 * WHAT PINS "MINE": class 100003 has exactly one constructor in the binary,
 * InitMine (0x4977c0), and its two spawners load the textures "rayonmine"
 * (SpawnMine) and "srayonmine" (SpawnSuperMine).  The cells this function
 * subtracts, +0x40 and +0x264, are the FIRST TWO of the shared CValueGuard
 * block InitProjectile lays out at +0x40/+0x264/+0x488/... - the projectile
 * base position pair - which is also why callers peek the returned entity's
 * +0x40 for its X where the jewel path peeks +0x25c.  (An earlier note here
 * wrongly copied HitTestJewel's offsets; corrected 2026-08-19.)
 *
 * Callers use it for the CHAIN REACTION, exactly as with jewels: on a hit
 * they peek the mine's X, column-scan the terrain for the ground row under
 * it, and run the FUN_00436070 / ApplyBlastDamage / SpawnBlastEffect trio at
 * that point - a blast sets off nearby mines.
 *
 * ABI: param_1 is a PHANTOM.  Ghidra marks the function __fastcall, but ECX
 * is written before it is ever read (orig 0x425e7a `mov ecx,[eax+0x6a7f8c]`),
 * so only EDX (param_2, the slot index) is a real register argument; ret 0xc
 * = 3 stack args.  Every caller passed just those 3 until the 2026-08-19
 * sweep, which left param_2 reading garbage and shifted params 3-5 by two.
 * Callers now pass 0 for param_1.
 * Raw/near-verbatim port of Ghidra's decompiler output beyond this - not
 * hand-verified. See src/README.md's "Raw/verbatim ports" section.
 *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at both argless PeekPacketChecksumState() calls: both chained DeltaSub returns (0x425f03, 0x425f85), discarded, captured in a new uVar8 - HitTestJewel's shape with +0x40/+0x264 instead of +0x25c/+0x480.
 */
#include "ghidra_types.h"


uint __fastcall
HitTestMine(undefined4 param_1,uint param_2,undefined4 param_3,undefined4 param_4,int param_5)

{
  uint uVar1;
  undefined4 uVar8;
  uint uVar2;
  int iVar3;
  int iVar4;
  undefined1 local_45c [8];
  undefined1 local_454 [548];
  undefined1 local_230 [548];
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  iVar3 = g_clientContext;
  local_4 = 0xffffffff;
  /* Windows SEH __try/__except frame setup stripped - handler body
   * (LAB_0053aef6) wasn't included in this function's own decompile.
   * Same rationale as entry/InitGame.c - see src/README.md. */
  iVar3 = *(int *)(*(int *)(&DAT_006a7f8c + iVar3) + 0x1c);
  uVar1 = *(uint *)(iVar3 + 4);
  if (uVar1 < 0x186a4) {
    while (uVar1 != 0x186a3) {
      iVar3 = *(int *)(iVar3 + 0x1c);
      uVar1 = *(uint *)(iVar3 + 4);
      if (0x186a3 < uVar1) {
        return 0;
      }
    }
    uVar1 = *(uint *)(iVar3 + 0x10);
    uVar2 = *(uint *)(uVar1 + 8);
    while (uVar2 <= param_2) {
      if (uVar2 == param_2) {
        uVar8 = EncodeChecksumDeltaSub(uVar1 + 0x40,local_454,param_3);
        local_4 = 0;
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar3 = PeekPacketChecksumState((void *)uVar8);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        local_4 = 0xffffffff;
        if ((*(int *)(local_454 + 0x14)) != 0) {
          ScrambleChecksumGuardBytes(*(int *)(local_454 + 0x14),&DAT_0079376c);
          TreeLowerBound(local_45c,&DAT_00793770);
        }
        uVar8 = EncodeChecksumDeltaSub(uVar1 + 0x264,local_230,param_4);
        local_4 = 1;
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar4 = PeekPacketChecksumState((void *)uVar8);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        local_4 = 0xffffffff;
        if ((*(int *)(local_230 + 0x14)) != 0) {
          ScrambleChecksumGuardBytes(*(int *)(local_230 + 0x14),&DAT_0079376c);
          TreeLowerBound(local_45c,&DAT_00793770);
        }
        return (param_5 * param_5 <= iVar3 * iVar3 + iVar4 * iVar4) - 1 & uVar1;
      }
      uVar1 = *(uint *)(uVar1 + 0x10);
      uVar2 = *(uint *)(uVar1 + 8);
    }
  }
  return 0;
}

