/* FUN_00425e60 - 0x00425e60 in the original binary.
 *
 * IDENTIFIED but NOT renamed (2026-08-19).  This is the layer-100003 twin of
 * HitTestLocalMobile (0x425ac0) / HitTestJewel (0x425c90): it walks the DAT_006a7f8c registry for the
 * collection whose key is 100003, finds the entry whose index equals the EDX
 * argument, and guard-computes (entityX - param_3) and (entityY - param_4)
 * from that entity's +0x40 and +0x264 CValueGuard cells - the same
 * subtract-then-compare shape HitTestLocalMobile uses on a player record's
 * +0x90c/+0xb30, and HitTestJewel on a jewel's +0x25c/+0x480.  (CORRECTION,
 * same day: an earlier revision of this note copied HitTestJewel's
 * +0x25c/+0x480 here.  This function's cells are +0x40 and +0x264 - a
 * consecutive 0x224-byte pair based at +0x40, not at +0x25c - which is why
 * its callers peek the returned entity's +0x40 for the X where the jewel
 * path peeks +0x25c.)  It returns the entity when the point is in range, else 0;
 * callers peek +0x40 on the result.  All six call sites are 0..7 slot loops
 * inside SimulateSuperShot_Bullet3 / ExplodeSuperShot_Bullet8, fed
 * (x, y, radius) from the projectile's +0xf54 / +0x1178 / +0x3198 cells.
 *
 * It is NOT renamed because what an entity of class id 100003 actually IS has
 * not been established - naming it "HitTestSomething" would encode a guess.
 * The mechanism is proven and its TWIN now is too (layer 100006 turned out to
 * be the jewels - see HitTestJewel), but nothing in the tree CREATES a
 * layer-100003 entity: every function carrying the 0x186a3 immediate only
 * walks the collection.  Find the producer and this one names itself.  Its
 * guard block based at +0x40 (vs the jewel's +0x38) is the distinguishing
 * fingerprint to match a constructor against.
 *
 * ABI: param_1 is a PHANTOM.  Ghidra marks the function __fastcall, but ECX
 * is written before it is ever read (orig 0x425e7a `mov ecx,[eax+0x6a7f8c]`), so only EDX (param_2, the
 * slot index) is a real register argument; ret 0xc = 3 stack args.  Every
 * caller passed just those 3 until the 2026-08-19 sweep, which left param_2
 * reading garbage and shifted params 3-5 by two.  Callers now pass 0 for
 * param_1.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output beyond this - not
 * hand-verified. See src/README.md's "Raw/verbatim ports" section.
 *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at both argless PeekPacketChecksumState() calls: both chained DeltaSub returns (0x425f03, 0x425f85), discarded, captured in a new uVar8 - HitTestJewel's shape with +0x40/+0x264 instead of +0x25c/+0x480.
 */
#include "ghidra_types.h"


uint __fastcall
FUN_00425e60(undefined4 param_1,uint param_2,undefined4 param_3,undefined4 param_4,int param_5)

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
          ScrambleChecksumGuardBytes();
          TreeLowerBound(local_45c);
        }
        uVar8 = EncodeChecksumDeltaSub(uVar1 + 0x264,local_230,param_4);
        local_4 = 1;
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar4 = PeekPacketChecksumState((void *)uVar8);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        local_4 = 0xffffffff;
        if ((*(int *)(local_230 + 0x14)) != 0) {
          ScrambleChecksumGuardBytes();
          TreeLowerBound(local_45c);
        }
        return (param_5 * param_5 <= iVar3 * iVar3 + iVar4 * iVar4) - 1 & uVar1;
      }
      uVar1 = *(uint *)(uVar1 + 0x10);
      uVar2 = *(uint *)(uVar1 + 8);
    }
  }
  return 0;
}

