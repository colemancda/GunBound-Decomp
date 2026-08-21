/* HitTestJewel - 0x00425c90 in the original binary.
 *
 * NAMED 2026-08-19 (was FUN_00425c90).  Finds the JEWEL at slot EDX and
 * returns it when the point (param_3, param_4) is within range, else 0 - the
 * layer-100006 twin of HitTestLocalMobile (0x425ac0), which does the same
 * against layer 100001, the player records.
 *
 * WHAT PINS "JEWEL": SpawnJewel (0x438410) allocates the layer-100006 entity
 * with operator_new(0x2298), sprintfs its sprite name as "jewel%d"
 * (s_jewel_d_00553bd4) from the type in param_3, sets its state to "normal",
 * and writes exactly two guarded fields - EncodeOutgoingPacketField at int
 * index 0x97 = BYTE +0x25c (the X, fed `x % g_nCameraBoundX` by its
 * AdvanceTurnQueue caller) and index 0xe = byte +0x38 (the type).  +0x25c is
 * precisely the cell this function subtracts param_3 from, and the same cell
 * ApplyBlastDamage's second pass subtracts at piVar11 + 0x97.  The jewel's
 * guard block is three consecutive 0x224-byte CValueGuard cells: +0x38 type,
 * +0x25c X, +0x480 Y.
 *
 * Callers use it for the CHAIN REACTION: on a hit they peek the jewel's
 * +0x25c X, column-scan the terrain for the ground row under it, and run the
 * whole FUN_00436070 / ApplyBlastDamage / SpawnBlastEffect detonation trio at
 * that point.
 *
 * ABI: param_1 is a PHANTOM.  Ghidra marks the function __fastcall, but ECX
 * is written before it is ever read (orig 0x425caa `mov ecx,[eax+0x6a7f8c]`),
 * so only EDX (param_2, the slot index) is a real register argument; ret 0xc
 * = 3 stack args.  Every caller passed just those 3 until the 2026-08-19
 * sweep, which left param_2 reading garbage and shifted params 3-5 by two.
 * Callers now pass 0 for param_1.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output beyond this - not
 * hand-verified. See src/README.md's "Raw/verbatim ports" section.
 *
 * DROPPED-CELL FIX (2026-08-13, CValueGuard sweep): recovered the guard
 * cell at both argless PeekPacketChecksumState() calls: both are chained returns of the DeltaSub immediately above them
 * (0x425d36, 0x425db8), discarded and captured in a new uVar8 - the
 * same two-round shape as HitTestLocalMobile.
 */
#include "ghidra_types.h"


uint __fastcall
HitTestJewel(undefined4 param_1,uint param_2,undefined4 param_3,undefined4 param_4,int param_5)

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
  if (uVar1 < 0x186a7) {
    while (uVar1 != 0x186a6) {
      iVar3 = *(int *)(iVar3 + 0x1c);
      uVar1 = *(uint *)(iVar3 + 4);
      if (0x186a6 < uVar1) {
        return 0;
      }
    }
    uVar1 = *(uint *)(iVar3 + 0x10);
    uVar2 = *(uint *)(uVar1 + 8);
    while (uVar2 <= param_2) {
      if (uVar2 == param_2) {
        uVar8 = EncodeChecksumDeltaSub(uVar1 + 0x25c,local_454,param_3);
        local_4 = 0;
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        iVar3 = PeekPacketChecksumState((void *)uVar8);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        local_4 = 0xffffffff;
        if ((*(int *)(local_454 + 0x14)) != 0) {
          ScrambleChecksumGuardBytes(*(int *)(local_454 + 0x14),&DAT_0079376c);
          TreeLowerBound(local_45c,&DAT_00793770);
        }
        uVar8 = EncodeChecksumDeltaSub(uVar1 + 0x480,local_230,param_4);
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

