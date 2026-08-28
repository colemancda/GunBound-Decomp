/* SpawnBlastEffect - 0x00431d90 in the original binary.
 *
 * NAMED 2026-08-19 (was FUN_00431d90).  Spawns the terrain BLAST effect at
 * an impact point.  Direct evidence in the body:
 *   - operator_new(0x3fa0) - the projectile-family object size - then the
 *     0x4aa830 constructor, and FUN_0041da80(g_clientContext, obj, ...)
 *     registers it exactly the way projectiles are registered.
 *   - sprintf(obj+0x3898, "flame%d%d", param_4 + 1, variant)  (0x553e48)
 *     builds the animation-state name; `variant` is 3 when param_10 is set,
 *     else 1 or 2 depending on param_5.
 *   - the sprite-set name is copied into obj+0x3813 from the string table at
 *     0x56d290, indexed [ (param_5 & 0xff) * 0x10 + param_4 ]: entries are
 *     "11blast.xes", "22blast.xes", "31blast.xes" ... "151blast.xes"
 *     (orig 0x431f7a: movzx ecx,bl / shl ecx,4 / add ecx,edi /
 *      mov ecx,[ecx*4 + 0x56d290]).
 *   - it is called from every Detonate / Explode path, always immediately
 *     after ApplyBlastDamage on the same impact point.
 * param_1/param_2 are the terrain (Y, X) - see the ABI note below.
 * Raw/near-verbatim port of Ghidra's decompiler output beyond the naming -
 * not hand-verified. See src/README.md's "Raw/verbatim ports" section.
 *
 * DROPPED-REGISTER-ARG FIX (2026-08-19, full 37-site caller sweep).
 * This function is __fastcall: it takes TWO register arguments plus
 * `ret 0x20` = 8 stack arguments, and the signature below already
 * modelled all ten.  Every caller in the tree passed only the eight
 * stack ones, so param_1/param_2 arrived as whatever happened to be in
 * ECX/EDX - and the tree could not even notice, because
 * include/functions.h had NO declaration for this function: Ghidra
 * writes `void __fastcall` on its own line above the name, and the
 * header's auto-generator only matches single-line signatures.  With no
 * prototype in scope every call compiled __cdecl, i.e. the register pair
 * was never passed at all.  (63 other split-line definitions are missing
 * from functions.h for the same reason - an open audit, not fixed here.)
 *
 * SEMANTICS of the register pair (all three lines of evidence agree):
 *   param_1 = ECX = Y, the terrain ROW.  Bounded `>= -0xc8` and
 *     `< [ctx+0x6a7724]`; that global is the terrain height (it bounds
 *     the row loop in every caller's column scan).  Callers feed it the
 *     scanned ground row, seeded 10000 when the column has no ground -
 *     and DetonateSuperShot_Bullet12 feeds it FindGroundHeightAtColumn's
 *     result directly.
 *   param_2 = EDX = X, the terrain COLUMN.  Bounded `>= 0` and
 *     `< [ctx+0x6a7720]` = the terrain width.  Callers feed it a peek of
 *     the projectile's X guard cell (+0xf54 = param_1 + 0x3d5), usually
 *     the peek whose result Ghidra had discarded immediately above the
 *     call.
 * The cross-check that pins the ORDER: every caller pairs this call with
 * ApplyBlastDamage / FUN_00436070 / SpawnProjectileLightningHazard on the
 * same impact point, and those take (X, Y) - this one takes (Y, X).
 * Verified per site by push-depth normalisation against a capstone
 * disassembly of all 36 raw-C call sites (the Ghidra stack-local names
 * decoded from the normalised slots matched the C variable names the
 * dataflow independently produced at every site where both existed).
 */
#include "ghidra_types.h"


/* WARNING: Removing unreachable block (ram,0x00431e67) */

void __fastcall
SpawnBlastEffect(int param_1,int param_2,byte param_3,int param_4,uint param_5,undefined4 param_6,
            undefined4 param_7,byte param_8,undefined4 param_9,char param_10)

{
  char cVar1;
  void *pvVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  char *pcVar6;
  char *pcVar7;
  int *piVar8;
  undefined4 *unaff_FS_OFFSET;
  undefined1 local_89c [548];
  undefined1 local_678 [548];
  undefined1 local_454 [548];
  undefined1 local_230 [548];
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  local_c = *unaff_FS_OFFSET;
  puStack_8 = &LAB_0053cc82;
  *unaff_FS_OFFSET = &local_c;
  piVar8 = (int *)0x0;
  if ((((-1 < param_2) && (param_2 < *(int *)(&g_nCameraBoundX + g_clientContext))) && (-0xc9 < param_1))
     && (param_1 < *(int *)(&g_nCameraBoundY + g_clientContext))) {
    pvVar2 = operator_new(0x3fa0);
    local_4 = 0;
    if (pvVar2 != (void *)0x0) {
      piVar8 = (int *)InitBlastEffect((undefined4 *)pvVar2);
    }
    local_4 = 0xffffffff;
    piVar8[6] = -1;
    if (param_10 == '\0') {
      iVar3 = ((char)param_5 != '\0') + 8000 + param_4 * 2;
    }
    else {
      iVar3 = param_4 + 0x2008;
    }
    piVar8[0xe25] = iVar3;
    *(byte *)(piVar8 + 0xf) = param_3 & 7;
    piVar8[0xe] = -1;
    uVar4 = QueueOutgoingPacketField(param_2);
    EncodeChecksumState(uVar4);
    QueueOutgoingPacketField(param_1);
    QueueOutgoingPacketField(param_2 << 8);
    QueueOutgoingPacketField(param_1 << 8);
    uVar4 = QueueOutgoingPacketField(0);
    uVar4 = EncodeChecksumState(uVar4);
    uVar4 = EncodeChecksumState(uVar4);
    uVar4 = EncodeChecksumState(uVar4);
    EncodeChecksumState(uVar4);
    SetGuardedBool(param_6,GB_GUARD_UNRECOVERED);
    QueueOutgoingPacketField(param_7);
    SetGuardedBool(0,GB_GUARD_UNRECOVERED);
    QueueOutgoingPacketField(0);
    piVar8[0xfe4] = (uint)param_8;
    if (param_10 == '\0') {
      iVar3 = ((char)param_5 != '\0') + 1;
    }
    else {
      iVar3 = 3;
    }
    _sprintf((char *)(piVar8 + 0xe26),s_flame_d_d_00553e48,param_4 + 1,iVar3);
    pcVar6 = (&PTR_s_11blast_xes_0056d290)[(param_5 & 0xff) * 0x10 + param_4];
    pcVar7 = (char *)((int)piVar8 + 0x3813);
    do {
      cVar1 = *pcVar6;
      pcVar6 = pcVar6 + 1;
      *pcVar7 = cVar1;
      pcVar7 = pcVar7 + 1;
    } while (cVar1 != '\0');
    FUN_0041da80(g_clientContext,piVar8,param_5,param_10,1);
    cVar1 = PeekPacketChecksumBool((byte *)(g_clientContext + 0x5b818));
    if (cVar1 == '\x01') {
      uVar4 = EncodeChecksumDeltaMul(piVar8 + 0x930,local_89c,3);
      local_4 = 1;
      uVar5 = PeekChecksumStateUnderLock(&DAT_00e55ab8);
      uVar4 = EncodeChecksumDeltaDiv(uVar4,local_678,uVar5);
      SUBFIELD(local_4,0,undefined1) = 2;
      EmitChecksumSum(piVar8 + 0x930, (void *)uVar4);
      local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),1);
      ScrubChecksumGuard();
      local_4 = 0xffffffff;
      ScrubChecksumGuard();
      uVar4 = EncodeChecksumDeltaMul(piVar8 + 0x9b9,local_678,3);
      local_4 = 3;
      uVar5 = PeekChecksumStateUnderLock(&DAT_00e55ab8);
      uVar4 = EncodeChecksumDeltaDiv(uVar4,local_89c,uVar5);
      SUBFIELD(local_4,0,undefined1) = 4;
      EmitChecksumSum(piVar8 + 0x9b9, (void *)uVar4);
      local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),3);
      ScrubChecksumGuard();
      local_4 = 0xffffffff;
      ScrubChecksumGuard();
      uVar4 = EncodeChecksumDeltaMul(piVar8 + 0xa42,local_678,3);
      local_4 = 5;
      uVar5 = PeekChecksumStateUnderLock(&DAT_00e55ab8);
      uVar4 = EncodeChecksumDeltaDiv(uVar4,local_89c,uVar5);
      SUBFIELD(local_4,0,undefined1) = 6;
      EmitChecksumSum(piVar8 + 0xa42, (void *)uVar4);
      local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),5);
      ScrubChecksumGuard();
      local_4 = 0xffffffff;
      ScrubChecksumGuard();
    }
    cVar1 = CheckGuardedBoolAnd(*(char *)(g_clientContext + 0x45127) == '\x02');
    if (cVar1 != '\0') {
      uVar4 = PeekChecksumStateUnderLock(&DAT_00e9c578);
      uVar4 = EncodeChecksumDeltaMul(piVar8 + 0x930,local_678,uVar4);
      local_4 = 7;
      uVar5 = PeekChecksumStateUnderLock(&DAT_00796aa0);
      uVar4 = EncodeChecksumDeltaDiv(uVar4,local_89c,uVar5);
      SUBFIELD(local_4,0,undefined1) = 8;
      EncodeChecksumState(uVar4);
      local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),7);
      ScrubChecksumGuard();
      local_4 = 0xffffffff;
      ScrubChecksumGuard();
      uVar4 = PeekChecksumStateUnderLock(&DAT_00e9c578);
      uVar4 = EncodeChecksumDeltaMul(piVar8 + 0x9b9,local_678,uVar4);
      local_4 = 9;
      uVar5 = PeekChecksumStateUnderLock(&DAT_00796aa0);
      uVar4 = EncodeChecksumDeltaDiv(uVar4,local_89c,uVar5);
      SUBFIELD(local_4,0,undefined1) = 10;
      EncodeChecksumState(uVar4);
      local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),9);
      ScrubChecksumGuard();
      local_4 = 0xffffffff;
      ScrubChecksumGuard();
      uVar4 = PeekChecksumStateUnderLock(&DAT_00e9c578);
      uVar4 = EncodeChecksumDeltaMul(piVar8 + 0xa42,local_230,uVar4);
      local_4 = 0xb;
      uVar5 = PeekChecksumStateUnderLock(&DAT_00796aa0);
      uVar4 = EncodeChecksumDeltaDiv(uVar4,local_454,uVar5);
      SUBFIELD(local_4,0,undefined1) = 0xc;
      EncodeChecksumState(uVar4);
      local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),0xb);
      ScrubChecksumGuard();
      local_4 = 0xffffffff;
      ScrubChecksumGuard();
    }
    EncodeDividedChecksum(piVar8 + 0x795, param_10);
    EncodeDividedChecksum(piVar8 + 0x81e, param_10);
    EncodeDividedChecksum(piVar8 + 0x8a7, param_10);
    EncodeDividedChecksum(piVar8 + 0x930, param_10);
    EncodeDividedChecksum(piVar8 + 0x9b9, param_10);
    EncodeDividedChecksum(piVar8 + 0xa42, param_10);
    (**(code **)(*piVar8 + 8))();
    (**(code **)*piVar8)(1);
  }
  *unaff_FS_OFFSET = local_c;
  return;
}

