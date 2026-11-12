/* FUN_00432850 - 0x00432850 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-12, CValueGuard sweep): recovered the guard
 * cell at all 19 argless PeekPacketChecksumState() and all 19 argless
 * EncodeOutgoingPacketField() calls (both lists "clean", 19 C : 19 orig
 * each).  Cells from tools/guard_cell_resolve.py over 0x432850-0x433704.
 * This is a badly degraded decompile - Ghidra dropped nearly every
 * argument in the loop body, FloatToInt64 included - but the two
 * families interleave 1:1 with the original in address order, and the
 * Peek/Encode alternation in the C matches the disassembly exactly
 * (including the two Encode-only sites at ~180/~184, whose Peeks are
 * FloatToInt64 results rather than guard reads).
 *
 * TWO DIFFERENT OBJECTS, which is the whole point of the function: it
 * copies guarded fields from the SOURCE at param_1 into each freshly
 * allocated projectile.  Peek cells are param_1-relative, Encode cells
 * are piVar3-relative, and several rounds read and write the SAME
 * offset (0xf54 at 0x432baf vs 0x432bb5), so mixing the bases up would
 * not even look wrong.  `[esp+0x1e38]` is NOT a local: the frame is
 * 0x1e18 of chkstk plus four pushes, so that slot is param_1 itself
 * (0x432873 loads it as the function's first real instruction).  ESI is
 * the new object: `xor esi,esi` at 0x432ac8 is the allocation-FAILED
 * path, both paths merge at 0x432aca, and every later [esi+N] is
 * piVar3.
 *
 * Ten cells are chained returns the decompile discarded - one
 * EncodeChecksumPairSum, one DeltaSub, two DeltaMul and six DeltaDiv -
 * captured in a new uVar12.  The six DeltaDiv rounds are independently
 * confirmed: each one's Encode cell (piVar3 + 0x795/0x81e/0x8a7/0x930/
 * 0x9b9/0xa42) is exactly the first argument the C already passes to
 * the InitGuardedChecksumSlot call three lines above it.
 *
 * NOT fixed here: Ghidra dropped the Encode VALUE as well as the cell at
 * most of these sites, so they stay one-argument calls carrying only the
 * cell - the same convention SpawnShot_Type13 already uses.  The values
 * are recoverable (each is the `push eax` of the Peek immediately
 * above), but that is a separate sweep; a missing value writes garbage
 * into a VALID cell at flip time, which is a wrong-value bug, not the
 * wild-pointer bug this pass is closing.
 *
 * FRAME-OBJECT FIX (2026-11-12): the zero-argument Init/PairSum/Sub/Mul
 * calls, the Div rounds' scratch arguments and every TreeInsert's guard
 * pointer are recovered from an esp-tracked walk of 0x432850-0x433704 (the
 * call-through-ebp EnterCriticalSection and the virtual call's ret 4 must be
 * modelled or the loop body drifts by 4).  The frame holds fourteen
 * contiguous 0x224-byte scratch objects (auScratch[14][0x224]); the three
 * prelude Inits/PairSum use [0..2], Sub and the two Muls reuse [0] and [1],
 * and each of the six Div rounds is Init into one object, Div into another.
 * Three more artifacts are gone: the first-iteration flag at 0x432eb8 is the
 * LOOP COUNTER (not the angle), piVar3[0xfe5] is param_2 (0x433000), and the
 * 0x3813 string copy targets param_1.  InitProjectile's ECX (counter + 8,
 * stored at obj+8) is still dropped.
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

void FUN_00432850(int param_1,int param_2)

{
  char cVar1;
  void *pvVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  char *pcVar7;
  undefined4 uVar8;
  char *pcVar9;
  byte bVar10;
  code *pcVar11;
  undefined4 uVar12;
  int *unaff_FS_OFFSET;
  int local_1e24;
  int local_1e10;
  int local_1e0c;
  int iVarR1;
  int iVarR2;
  /* The fourteen 0x224-byte frame objects Ghidra split into the auStack_*
   * and iStack_* locals.  The esp-tracked model (every call/ret pop applied,
   * including the call-through-ebp EnterCriticalSection and the virtual
   * call's ret 4) puts them contiguous from frame -0x1e04, 0x224 apart, which
   * exactly fills the frame up to the saved fs:[0] link at -0xc.  [k] is
   * object k = frame -0x1e04 + k*0x224; the guard pointer every callee writes
   * is at +0x14.  Rounds below name them by index (A=0 ... N=13). */
  undefined1 auScratch [14][0x224];
  undefined4 auTreeNode [2];       /* TreeInsert's out pair (stub ignores it) */
  int local_c;
  undefined1 *puStack_8;
  int local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053cb84;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = (int)&local_c;
  iVarR1 = InitGuardedChecksumSlot(param_1 + 0x6ac,auScratch[0],param_1 + 0x6ac);
  local_4 = 0;
  iVarR2 = InitGuardedChecksumSlot(param_1 + 0x488,auScratch[1],param_1 + 0x488);
  local_4 = 1;
  uVar12 = EncodeChecksumPairSum(iVarR2,auScratch[2],iVarR1);
  local_4 = 2;
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  PeekPacketChecksumState((void *)uVar12);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  local_4 = 1;
  if (*(int *)(auScratch[2] + 0x14) != 0) {
    ScrambleChecksumGuardBytes(*(int *)(auScratch[2] + 0x14),&g_valueGuardKeyTable);
    TreeInsert(auTreeNode,&g_valueGuardMap);
  }
  local_4 = 0;
  if (*(int *)(auScratch[1] + 0x14) != 0) {
    ScrambleChecksumGuardBytes(*(int *)(auScratch[1] + 0x14),&g_valueGuardKeyTable);
    TreeInsert(auTreeNode,&g_valueGuardMap);
  }
  local_4 = 0xffffffff;
  if (*(int *)(auScratch[0] + 0x14) != 0) {
    ScrambleChecksumGuardBytes(*(int *)(auScratch[0] + 0x14),&g_valueGuardKeyTable);
    TreeInsert(auTreeNode,&g_valueGuardMap);
  }
  FloatToInt64();
  FloatToInt64();
  uVar12 = EncodeChecksumDeltaSub(param_1 + 0x1c2c,auScratch[0],param_2 * 3);
  local_4 = 3;
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  local_1e10 = PeekPacketChecksumState((void *)uVar12);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  local_4 = 0xffffffff;
  if (*(int *)(auScratch[0] + 0x14) != 0) {
    ScrambleChecksumGuardBytes(*(int *)(auScratch[0] + 0x14),&g_valueGuardKeyTable);
    TreeInsert(auTreeNode,&g_valueGuardMap);
  }
  local_1e0c = 0;
  if (0 < param_2) {
    do {
      pvVar2 = operator_new(0x3f9c);
      local_4 = 4;
      if (pvVar2 == (void *)0x0) {
        piVar3 = (int *)0x0;
      }
      else {
        piVar3 = (int *)InitProjectile();
      }
      iVar4 = g_clientContext;
      local_4 = 0xffffffff;
      piVar3[0xfe4] = 0xff;
      if (*(char *)(iVar4 + 0x45578) == '\0') {
        piVar3[6] = 0x1a8e;
        piVar3[0xe] = 0x1a8f;
        piVar3[0xe25] = 0x2013;
        piVar3[0xe26] = SUBFIELD(s_flame123_00553cec,0,undefined4);
        piVar3[0xe27] = SUBFIELD(s_flame123_00553cec,4,undefined4);
        *(char *)(piVar3 + 0xe28) = s_flame123_00553cec[8];
        iVar4 = FindPreloadedTextureByName();
        piVar3[7] = iVar4;
      }
      else if (*(char *)(iVar4 + 0x45578) == '\x01') {
        piVar3[6] = 6000;
        piVar3[0xe] = 0x17d4;
        piVar3[0xe25] = 8000;
        iVar4 = FindPreloadedTextureByName();
        piVar3[7] = iVar4;
        piVar3[0xe26] = SUBFIELD(s_flameevent1_00553e2c,0,undefined4);
        piVar3[0xe27] = SUBFIELD(s_flameevent1_00553e2c,4,undefined4);
        piVar3[0xe28] = SUBFIELD(s_flameevent1_00553e2c,8,undefined4);
      }
      *(undefined1 *)(piVar3 + 0xf) = *(undefined1 *)(param_1 + 0x3c);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      PeekPacketChecksumState((void *)(param_1 + 0xf54));
      EncodeOutgoingPacketField((void *)(piVar3 + 0x3d5));
      pcVar11 = (code *)LeaveCriticalSection;
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      PeekPacketChecksumState((void *)(piVar3 + 0x3d5));
      EncodeOutgoingPacketField((void *)(piVar3 + 0xed2));
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      PeekPacketChecksumState((void *)(param_1 + 0x1178));
      EncodeOutgoingPacketField((void *)(piVar3 + 0x45e));
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      PeekPacketChecksumState((void *)(param_1 + 0x40));
      EncodeOutgoingPacketField((void *)(piVar3 + 0x10));
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      PeekPacketChecksumState((void *)(param_1 + 0x264));
      EncodeOutgoingPacketField((void *)(piVar3 + 0x99));
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      PeekPacketChecksumState((void *)(param_1 + 0x8d0));
      EncodeOutgoingPacketField((void *)(piVar3 + 0x234));
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      FloatToInt64();
      EncodeOutgoingPacketField((void *)(piVar3 + 0x122));
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      FloatToInt64();
      EncodeOutgoingPacketField((void *)(piVar3 + 0x1ab));
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      uVar12 = EncodeChecksumDeltaMul(param_1 + 0xaf4,auScratch[0],2);
      local_4 = 5;
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      uVar8 = PeekPacketChecksumState((void *)uVar12);
      EncodeOutgoingPacketField((void *)(piVar3 + 0x2bd), uVar8);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      local_4 = 0xffffffff;
      if (*(int *)(auScratch[0] + 0x14) != 0) {
        iVar4 = *(int *)(auScratch[0] + 0x14) << 4;
        iVar5 = 0x10;
        do {
          iVar6 = _rand();
          *(char *)(iVar4 + g_valueGuardKeyTable) = (char)iVar6;
          iVar4 = iVar4 + 1;
          iVar5 = iVar5 + -1;
        } while (iVar5 != 0);
        TreeInsert(auTreeNode,&g_valueGuardMap);
      }
      uVar12 = EncodeChecksumDeltaMul(param_1 + 0xd18,auScratch[1],2);
      local_4 = 6;
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      uVar8 = PeekPacketChecksumState((void *)uVar12);
      EncodeOutgoingPacketField((void *)(piVar3 + 0x346), uVar8);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      local_4 = 0xffffffff;
      if (*(int *)(auScratch[1] + 0x14) != 0) {
        iVar4 = *(int *)(auScratch[1] + 0x14) << 4;
        iVar5 = 0x10;
        do {
          iVar6 = _rand();
          *(char *)(iVar4 + g_valueGuardKeyTable) = (char)iVar6;
          iVar4 = iVar4 + 1;
          iVar5 = iVar5 + -1;
        } while (iVar5 != 0);
        TreeInsert(auTreeNode,&g_valueGuardMap);
      }
      pcVar11 = (code *)LeaveCriticalSection;
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      iVar4 = _rand();
      *(char *)((int)piVar3 + 0xf3f) = (char)iVar4;
      iVar4 = _rand();
      *(byte *)(piVar3 + 0x3d0) = (byte)iVar4;
      bVar10 = *(byte *)((int)piVar3 + 0xf3f) & 7;
      bVar10 = ~('\x01' << bVar10) & (byte)iVar4 | (local_1e0c == 0) << bVar10;
      *(byte *)(piVar3 + 0x3d0) = bVar10;
      *(byte *)((int)piVar3 + 0xf41) = bVar10 + *(char *)((int)piVar3 + 0xf3f) + -0x34;
      (*pcVar11)();
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      iVar4 = _rand();
      *(char *)((int)piVar3 + 0xf45) = (char)iVar4;
      iVar4 = _rand();
      *(byte *)((int)piVar3 + 0xf46) = (byte)iVar4;
      bVar10 = *(byte *)((int)piVar3 + 0xf45) & 7;
      bVar10 = ~('\x01' << bVar10) & (byte)iVar4 | '\0' << bVar10;
      *(byte *)((int)piVar3 + 0xf46) = bVar10;
      *(byte *)((int)piVar3 + 0xf47) = bVar10 + *(char *)((int)piVar3 + 0xf45) + -0x34;
      (*pcVar11)();
      CopyGuardedBool((byte *)((int)piVar3 + 0x3918),(byte *)(param_1 + 0x3918));
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      PeekPacketChecksumState((void *)(param_1 + 0x17e4));
      EncodeOutgoingPacketField((void *)(piVar3 + 0x5f9));
      (*pcVar11)();
      CopyGuardedBool((byte *)((int)piVar3 + 0xf3c),(byte *)(param_1 + 0xf3c));
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      PeekPacketChecksumState((void *)(param_1 + 0x1a08));
      EncodeOutgoingPacketField((void *)(piVar3 + 0x682));
      (*pcVar11)();
      piVar3[0xfe5] = param_2;
      CopyGuardedBool((byte *)((int)piVar3 + 0x391b),(byte *)(param_1 + 0x391b));
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      PeekPacketChecksumState((void *)(param_1 + 0x3920));
      EncodeOutgoingPacketField((void *)(piVar3 + 0xe48));
      (*pcVar11)();
      (**(code **)(*piVar3 + 4))(s_normal_00552230);
      pcVar7 = (char *)(param_1 + 0x3813);
      pcVar9 = PTR_s_121blast_xes_0056d33c;
      do {
        cVar1 = *pcVar9;
        pcVar9 = pcVar9 + 1;
        *pcVar7 = cVar1;
        pcVar7 = pcVar7 + 1;
      } while (cVar1 != '\0');
      /* DROPPED-ARGUMENT FIX (2026-09-21): FUN_0041da80 is __thiscall
       * with ECX=param_1 (erased to a plain leading stack arg here per
       * ghidra_types.h) ahead of these 5 stack args, which is all this
       * call ever passed. Orig 0x433077: `mov ecx,0xb` right before the
       * call (literal, this spawner's own class-id-like constant). */
      FUN_0041da80(0xb,g_clientContext,piVar3,1,1,1);
      uVar8 = InitGuardedChecksumSlot(piVar3 + 0x795,auScratch[3],piVar3 + 0xcf2);
      local_4 = 0x7;
      uVar12 = EncodeChecksumDeltaDiv(uVar8,auScratch[2],100);
      local_4 = 0x8;
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      uVar8 = PeekPacketChecksumState((void *)uVar12);
      EncodeOutgoingPacketField((void *)(piVar3 + 0x795), uVar8);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      local_4 = 0x7;
      if (*(int *)(auScratch[2] + 0x14) != 0) {
        iVar4 = *(int *)(auScratch[2] + 0x14) << 4;
        iVar5 = 0x10;
        do {
          iVar6 = _rand();
          *(char *)(iVar4 + g_valueGuardKeyTable) = (char)iVar6;
          iVar4 = iVar4 + 1;
          iVar5 = iVar5 + -1;
        } while (iVar5 != 0);
        TreeInsert(auTreeNode,&g_valueGuardMap);
      }
      local_4 = 0xffffffff;
      if (*(int *)(auScratch[3] + 0x14) != 0) {
        iVar4 = *(int *)(auScratch[3] + 0x14) << 4;
        iVar5 = 0x10;
        do {
          iVar6 = _rand();
          *(char *)(iVar4 + g_valueGuardKeyTable) = (char)iVar6;
          iVar4 = iVar4 + 1;
          iVar5 = iVar5 + -1;
        } while (iVar5 != 0);
        TreeInsert(auTreeNode,&g_valueGuardMap);
      }
      uVar8 = InitGuardedChecksumSlot(piVar3 + 0x81e,auScratch[6],piVar3 + 0xcf2);
      local_4 = 0x9;
      uVar12 = EncodeChecksumDeltaDiv(uVar8,auScratch[12],100);
      local_4 = 0xa;
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      uVar8 = PeekPacketChecksumState((void *)uVar12);
      EncodeOutgoingPacketField((void *)(piVar3 + 0x81e), uVar8);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      local_4 = 0x9;
      if (*(int *)(auScratch[12] + 0x14) != 0) {
        iVar4 = *(int *)(auScratch[12] + 0x14) << 4;
        iVar5 = 0x10;
        do {
          iVar6 = _rand();
          *(char *)(iVar4 + g_valueGuardKeyTable) = (char)iVar6;
          iVar4 = iVar4 + 1;
          iVar5 = iVar5 + -1;
        } while (iVar5 != 0);
        TreeInsert(auTreeNode,&g_valueGuardMap);
      }
      local_4 = 0xffffffff;
      if (*(int *)(auScratch[6] + 0x14) != 0) {
        iVar4 = *(int *)(auScratch[6] + 0x14) << 4;
        iVar5 = 0x10;
        do {
          iVar6 = _rand();
          *(char *)(iVar4 + g_valueGuardKeyTable) = (char)iVar6;
          iVar4 = iVar4 + 1;
          iVar5 = iVar5 + -1;
        } while (iVar5 != 0);
        TreeInsert(auTreeNode,&g_valueGuardMap);
      }
      uVar8 = InitGuardedChecksumSlot(piVar3 + 0x8a7,auScratch[8],piVar3 + 0xcf2);
      local_4 = 0xb;
      uVar12 = EncodeChecksumDeltaDiv(uVar8,auScratch[10],100);
      local_4 = 0xc;
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      uVar8 = PeekPacketChecksumState((void *)uVar12);
      EncodeOutgoingPacketField((void *)(piVar3 + 0x8a7), uVar8);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      local_4 = 0xb;
      if (*(int *)(auScratch[10] + 0x14) != 0) {
        iVar4 = *(int *)(auScratch[10] + 0x14) << 4;
        iVar5 = 0x10;
        do {
          iVar6 = _rand();
          *(char *)(iVar4 + g_valueGuardKeyTable) = (char)iVar6;
          iVar4 = iVar4 + 1;
          iVar5 = iVar5 + -1;
        } while (iVar5 != 0);
        TreeInsert(auTreeNode,&g_valueGuardMap);
      }
      local_4 = 0xffffffff;
      if (*(int *)(auScratch[8] + 0x14) != 0) {
        iVar4 = *(int *)(auScratch[8] + 0x14) << 4;
        iVar5 = 0x10;
        do {
          iVar6 = _rand();
          *(char *)(iVar4 + g_valueGuardKeyTable) = (char)iVar6;
          iVar4 = iVar4 + 1;
          iVar5 = iVar5 + -1;
        } while (iVar5 != 0);
        TreeInsert(auTreeNode,&g_valueGuardMap);
      }
      uVar8 = InitGuardedChecksumSlot(piVar3 + 0x930,auScratch[5],piVar3 + 0xd7b);
      local_4 = 0xd;
      uVar12 = EncodeChecksumDeltaDiv(uVar8,auScratch[4],100);
      local_4 = 0xe;
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      uVar8 = PeekPacketChecksumState((void *)uVar12);
      EncodeOutgoingPacketField((void *)(piVar3 + 0x930), uVar8);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      local_4 = 0xd;
      if (*(int *)(auScratch[4] + 0x14) != 0) {
        iVar4 = *(int *)(auScratch[4] + 0x14) << 4;
        iVar5 = 0x10;
        do {
          iVar6 = _rand();
          *(char *)(iVar4 + g_valueGuardKeyTable) = (char)iVar6;
          iVar4 = iVar4 + 1;
          iVar5 = iVar5 + -1;
        } while (iVar5 != 0);
        TreeInsert(auTreeNode,&g_valueGuardMap);
      }
      local_4 = 0xffffffff;
      if (*(int *)(auScratch[5] + 0x14) != 0) {
        iVar4 = *(int *)(auScratch[5] + 0x14) << 4;
        iVar5 = 0x10;
        do {
          iVar6 = _rand();
          *(char *)(iVar4 + g_valueGuardKeyTable) = (char)iVar6;
          iVar4 = iVar4 + 1;
          iVar5 = iVar5 + -1;
        } while (iVar5 != 0);
        TreeInsert(auTreeNode,&g_valueGuardMap);
      }
      uVar8 = InitGuardedChecksumSlot(piVar3 + 0x9b9,auScratch[9],piVar3 + 0xd7b);
      local_4 = 0xf;
      uVar12 = EncodeChecksumDeltaDiv(uVar8,auScratch[7],100);
      local_4 = 0x10;
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      uVar8 = PeekPacketChecksumState((void *)uVar12);
      EncodeOutgoingPacketField((void *)(piVar3 + 0x9b9), uVar8);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      local_4 = 0xf;
      if (*(int *)(auScratch[7] + 0x14) != 0) {
        iVar4 = *(int *)(auScratch[7] + 0x14) << 4;
        iVar5 = 0x10;
        do {
          iVar6 = _rand();
          *(char *)(iVar4 + g_valueGuardKeyTable) = (char)iVar6;
          iVar4 = iVar4 + 1;
          iVar5 = iVar5 + -1;
        } while (iVar5 != 0);
        TreeInsert(auTreeNode,&g_valueGuardMap);
      }
      local_4 = 0xffffffff;
      if (*(int *)(auScratch[9] + 0x14) != 0) {
        iVar4 = *(int *)(auScratch[9] + 0x14) << 4;
        iVar5 = 0x10;
        do {
          iVar6 = _rand();
          *(char *)(iVar4 + g_valueGuardKeyTable) = (char)iVar6;
          iVar4 = iVar4 + 1;
          iVar5 = iVar5 + -1;
        } while (iVar5 != 0);
        TreeInsert(auTreeNode,&g_valueGuardMap);
      }
      uVar8 = InitGuardedChecksumSlot(piVar3 + 0xa42,auScratch[13],piVar3 + 0xd7b);
      local_4 = 0x11;
      uVar12 = EncodeChecksumDeltaDiv(uVar8,auScratch[11],100);
      local_4 = 0x12;
      EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      uVar8 = PeekPacketChecksumState((void *)uVar12);
      EncodeOutgoingPacketField((void *)(piVar3 + 0xa42), uVar8);
      LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
      local_4 = 0x11;
      if (*(int *)(auScratch[11] + 0x14) != 0) {
        iVar4 = *(int *)(auScratch[11] + 0x14) << 4;
        iVar5 = 0x10;
        do {
          iVar6 = _rand();
          *(char *)(iVar4 + g_valueGuardKeyTable) = (char)iVar6;
          iVar4 = iVar4 + 1;
          iVar5 = iVar5 + -1;
        } while (iVar5 != 0);
        TreeInsert(auTreeNode,&g_valueGuardMap);
      }
      local_4 = 0xffffffff;
      if (*(int *)(auScratch[13] + 0x14) != 0) {
        iVar4 = *(int *)(auScratch[13] + 0x14) << 4;
        iVar5 = 0x10;
        do {
          iVar6 = _rand();
          *(char *)(iVar4 + g_valueGuardKeyTable) = (char)iVar6;
          iVar4 = iVar4 + 1;
          iVar5 = iVar5 + -1;
        } while (iVar5 != 0);
        TreeInsert(auTreeNode,&g_valueGuardMap);
      }
      /* EDX = [0x5b3484] + 0x6a7f88, EDI = esi, the projectile (its +0x3f90/+0x18/+0x38/+0x3894 stores match piVar3) (original call at 0x43379e); the port had passed (0,0,NULL). */
      RegisterActiveObject(0, (int)g_clientContext + 0x6a7f88, (undefined4 *)piVar3);
      local_1e10 = local_1e10 + 6;
      local_1e0c = local_1e0c + 1;
    } while (local_1e0c < param_2);
  }
  *unaff_FS_OFFSET = local_c;
  return;
}

