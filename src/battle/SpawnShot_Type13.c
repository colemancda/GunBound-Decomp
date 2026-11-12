/* SpawnShot_Type13 - 0x004388e0 in the original binary.
 *
 * SIGNATURE FIX (2026-08-19): this was declared `void SpawnShot_Type13(void)`
 * - NO parameters - while the original is `ret 0x1c` = SEVEN stack arguments
 * and its one call site passes seven.  Ghidra recovered none of them and
 * reached two through raw `in_stack_000000NN` locals instead.
 *
 * The two it did reach are the 6th and 7th arguments, and the SEMANTICS pin
 * which is which rather than the offset arithmetic alone:
 *     *(undefined1 *)(obj + 0xf) = *(undefined1 *)(param_7 + 0x3c);
 * dereferences its argument at +0x3c, which is the owner byte every spawn in
 * this family reads off the projectile object - so param_7 must be the OBJECT
 * POINTER.  At the call site (orig 0x46cb00-0x46cb18) the 7th pushed value is
 * indeed an object read out of a frame slot, while the 6th is the literal 5;
 * and 5 lands in obj[0xfe5], the small per-shot field the SpawnPrimaryShot
 * notes already describe.  Reading them the other way round would make the
 * code dereference the constant 5.
 *
 * The remaining five arguments are declared but unreferenced - Ghidra found no
 * uses, and none were invented here.
 *
 * RENAMED (2026-07-16, from FUN_004388e0): projectile-shot spawner for
 * mobile TYPE 13 (structural sibling of SpawnKnightFlameShot /
 * SpawnPrimaryShot / SpawnSuperShot / SpawnShot_Type9). Mobile type
 * CONFIRMED via vtable geometry - its sole caller ExplodeSuperShot_Bullet14 is a
 * projectile method clustered with type-13's code; the effect it fires
 * is 142blast. The "_Type13" suffix is the confirmed mobile type; the
 * mobile NAME is not confirmable (the "normal" string is a red-herring
 * default anim-state, and the repo has no mobile-type->name map).
 * NOTE: still a raw port with its own dropped params / SEH plumbing to
 * finish - see src/README.md. Raw/near-verbatim Ghidra body.
 *
 * DROPPED-CELL FIX (2026-08-12, CValueGuard sweep): recovered the guard
 * cell at all 22 argless PeekPacketChecksumState() calls (peek status
 * "clean", 22 C : 22 orig).  Cells from tools/guard_cell_resolve.py over
 * 0x4388e0-0x43958e; no gotos, so the sites order-zip, and each round's
 * cell is corroborated by the neighbouring Encode/DeltaMul cell the
 * 2026-07-15/16 sweeps already fixed (0x24c0 / 0x26e4 / 0x2908).
 *
 * The object base is EBP, the operator_new(0x3fa4) result at 0x438909 -
 * i.e. the C's piVar2.  guard_cell_resolve.py cannot see that: it
 * back-tracks EBP to `xor ebp,ebp` at 0x438940 and flags the site.  That
 * xor is the ALLOCATION-FAILED path; both paths merge at 0x438942 and
 * every later [ebp+N] access assumes the object, which is what the C
 * models with piVar2.
 *
 * (Historical note, superseded by the 2026-11-12 fix below.) Six cells are chained returns of EncodeChecksumDeltaDiv (0x40a8c0):
 * the helper returns its dest cell in EAX, the code spills it to
 * frame[0x10], and the paired Peek re-reads it.  Four of the six calls
 * discard the return in the decompile and now capture it in a new
 * iVar13; the other two already assign it (iVar3 at ~line 353 and
 * puStack_8d4 at ~line 397), so those Peeks use the existing variable
 * and the statements are left untouched.
 *
 * NOTE the ten `EncodeOutgoingPacketField(piVar2 + N)` calls are NOT
 * unfixed one-arg sites: the 2026-07-16 sweep put the CELL there and it
 * is the VALUE that Ghidra dropped.  A one-argument Encode in this tree
 * can be either, so read the file's own notes before "fixing" one.
 *
 * DROPPED-CELL FIX (2026-08-16, CValueGuard flip prep): the three
 * EncodeChecksumDeltaDiv/EmitChecksumSum pairs here had ALL their arguments
 * dropped.  The original shape at each (verified at 0x430fda / 0x438e2a /
 * 0x42fde8) is
 *     lea esi,[<obj> + 0x24c0]; push esi;
 *     call DeltaDiv(esi, <stack scratch>, 4);
 *     push eax; mov eax,esi; call EmitSum
 * so the cell is <obj> + 0x930 / 0x9b9 / 0xa42 (0x24c0 / 0x26e4 / 0x2908
 * bytes) and EmitChecksumSum's second cell is the delta helper's return -
 * which IS its second argument, the stack scratch.  Ghidra never named that
 * scratch slot in this file (the sibling SpawnShot_Type9 does name it,
 * &puStack_914, and SpawnPrimaryShot names it auStack_8a0), so it is declared
 * here as auStackEmitScratch: a real 0x224-byte guard cell serving exactly the
 * role the original stack slot serves.  Its ADDRESS differs from the
 * original's - this is a raw port, not a byte-match - but the behaviour (one
 * distinct scratch cell reused by all three pairs) is the original's.
 */
#include "ghidra_types.h"


void SpawnShot_Type13(undefined4 param_1,undefined4 param_2,undefined4 param_3,
                 undefined4 param_4,undefined4 param_5,int param_6,int param_7)

{
  /* Ghidra artifact: raw stack reference the decompiler could not
   * map to a named local; declared so the raw port parses. */
  char cVar1;
  int *piVar2;
  int iVar3;
  int iVar13;
  char *pcVar4;
  undefined4 uVar5;
  char *pcVar7;
  byte bVar8;
  undefined4 *unaff_FS_OFFSET;
  undefined1 *puStack_8d4;
  int *piStack_8d0;
  char *pcVar13;
  undefined1 auStackEmitScratch [0x224];   /* frame object A, orig -0x8a0 */
  undefined1 auScratchB [0x238];   /* B, orig -0x67c; Mul/Div write [arg2+0x220] and [arg2+0x14] */
  undefined1 auScratchC [0x238];   /* C, orig -0x458 */
  undefined1 auScratchD [0x238];   /* D, orig -0x234 */
  undefined4 auTreeNode [2];       /* TreeInsert's out pair (stub ignores it) */
  int iVarMul;
  int iVarDiv;
  int iVarArg;
  undefined1 uStack_48;
  undefined4 uStack_40;
  undefined4 uStack_38;
  undefined1 uStack_30;
  undefined4 uStack_28;
  undefined4 uStack_20;
  undefined1 uStack_18;
  undefined1 uStack_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_0053ca83;
  uStack_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &uStack_c;
  piVar2 = operator_new(0x3fa4);
  local_4 = 0;
  if (piVar2 == (int *)0x0) {
    piVar2 = (int *)0x0;
  }
  else {
    InitProjectile();
    *piVar2 = (int)&PTR_FUN_00555e0c;
    piVar2[0xfe8] = 0;
  }
  local_4 = 0xffffffff;
  if (*(char *)(g_clientContext + 0x45578) == '\0') {
    piVar2[6] = 0x1a8c;
    piVar2[0xe] = 0x1a8d;
    piVar2[0xe25] = 0x2015;
    iVar3 = FindPreloadedTextureByName();
    piVar2[7] = iVar3;
    piVar2[0xe26] = DAT_00553bb4;
    piVar2[0xe27] = DAT_00553bb8;
    *(undefined1 *)(piVar2 + 0xe28) = DAT_00553bbc;
  }
  else if (*(char *)(g_clientContext + 0x45578) == '\x01') {
    piVar2[6] = 6000;
    piVar2[0xe] = 0x17d4;
    piVar2[0xe25] = 8000;
    iVar3 = FindPreloadedTextureByName();
    piVar2[7] = iVar3;
    piVar2[0xe26] = SUBFIELD(s_flameevent1_00553e2c,0,undefined4);
    piVar2[0xe27] = SUBFIELD(s_flameevent1_00553e2c,4,undefined4);
    piVar2[0xe28] = SUBFIELD(s_flameevent1_00553e2c,8,undefined4);
  }
  pcVar13 = s_normal_00552230;
  (**(code **)(*piVar2 + 4))();
  FloatToInt64();
  FloatToInt64();
  piVar2[0xfe4] = 0xff;
  *(undefined1 *)(piVar2 + 0xf) = *(undefined1 *)(param_7 + 0x3c);
  /* FIXED (2026-07-15): dropped `self` args - angr-confirmed at 0x438ab7
   * .. 0x438c56 (`lea edi,[ebp + OFFSET]`, ebp = this file's own local
   * object pointer `piVar2`): the offsets/order (0xf54, 0x3b48, 0x1178,
   * 0x40, 0x264, 0x488, 0x8d0, 0x6ac, 0xaf4, 0xd18) exactly match the
   * same field family already established for the sibling functions in
   * this batch (src/battle/SpawnSuperShot.c, src/unnamed/SpawnShot_Type9.c)
   * which explicitly confirm several of these same cells via nearby
   * EncodeChecksumDeltaMul/FUN_0040b090 calls. See
   * tools/encodeoutgoingpacketfield_sites.json. */
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EncodeOutgoingPacketField(piVar2 + 0x3d5);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  PeekPacketChecksumState((void *)(piVar2 + 0x3d5));
  EncodeOutgoingPacketField(piVar2 + 0xed2);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EncodeOutgoingPacketField(piVar2 + 0x45e);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EncodeOutgoingPacketField(piVar2 + 0x10);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EncodeOutgoingPacketField(piVar2 + 0x99);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  FloatToInt64();
  EncodeOutgoingPacketField(piVar2 + 0x122);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  FloatToInt64();
  EncodeOutgoingPacketField(piVar2 + 0x234);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  FloatToInt64();
  EncodeOutgoingPacketField(piVar2 + 0x1ab);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EncodeOutgoingPacketField(piVar2 + 0x2bd);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EncodeOutgoingPacketField(piVar2 + 0x346);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EncodeGuardedBool(0,(byte *)GB_GUARD_UNRECOVERED) /* value+ptr both dropped by Ghidra; battle path, unrecovered */;
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar3 = _rand();
  *(char *)((int)piVar2 + 0xf45) = (char)iVar3;
  iVar3 = _rand();
  *(byte *)((int)piVar2 + 0xf46) = (byte)iVar3;
  bVar8 = *(byte *)((int)piVar2 + 0xf45) & 7;
  bVar8 = ~('\x01' << bVar8) & (byte)iVar3 | '\0' << bVar8;
  *(byte *)((int)piVar2 + 0xf46) = bVar8;
  *(byte *)((int)piVar2 + 0xf47) = bVar8 + *(char *)((int)piVar2 + 0xf45) + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  /* FIXED (2026-07-15): dropped `self` args - angr-confirmed at 0x438d30
   * (`lea edi,[ebp + 0x17e4]`): cell is piVar2+0x5f9 (== piVar2+0x17e4
   * bytes) - matches the same field established for the sibling
   * functions in this batch. See
   * tools/encodeoutgoingpacketfield_sites.json. */
  CopyGuardedBool((byte *)((int)piVar2 + 0x3918),(byte *)(param_7 + 0x3918));
  /* PEEK CELL CORRECTED 2026-08-27: this read was given piVar2+0x5f9 by the
   * 2026-07-15 sweep, which had only established the ENCODE cell (edi =
   * ebp = piVar2) and carried that base across to the peek.  The binary
   * reads the OTHER object: `lea eax,[esi + 0x17e4]` at 0x438d24, esi loaded
   * from [esp+0x8d4] = param_7 -- the same source object the
   * CopyGuardedBool above it copies from.  Frame check: the neighbouring
   * [esp+0x8d0] is param_6, witnessed by `mov [ebp+0x3f94],ecx` against
   * this file's own `piVar2[0xfe5] = param_6`. */
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  PeekPacketChecksumState((void *)(param_7 + 0x17e4));
  EncodeOutgoingPacketField(piVar2 + 0x5f9);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  /* FIXED (2026-07-15): dropped `self` args - angr-confirmed at 0x438d77
   * (`lea edi,[ebp + 0x1a08]`): cell is piVar2+0x682 (== piVar2+0x1a08
   * bytes). See tools/encodeoutgoingpacketfield_sites.json. */
  CopyGuardedBool((byte *)((int)piVar2 + 0xf3c),(byte *)(param_7 + 0xf3c));
  piVar2[0xfe5] = param_6;
  /* PEEK CELL CORRECTED 2026-08-27: this read was given piVar2+0x682 by the
   * 2026-07-15 sweep, which had only established the ENCODE cell (edi =
   * ebp = piVar2) and carried that base across to the peek.  The binary
   * reads the OTHER object: `lea eax,[esi + 0x1a08]` at 0x438d6b, esi loaded
   * from [esp+0x8d4] = param_7 -- the same source object the
   * CopyGuardedBool above it copies from.  Frame check: the neighbouring
   * [esp+0x8d0] is param_6, witnessed by `mov [ebp+0x3f94],ecx` against
   * this file's own `piVar2[0xfe5] = param_6`. */
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  PeekPacketChecksumState((void *)(param_7 + 0x1a08));
  EncodeOutgoingPacketField(piVar2 + 0x682);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  /* FIXED (2026-07-15): dropped `self` args - angr-confirmed at 0x438db1
   * (`lea edi,[ebp + 0x3920]`): cell is piVar2+0xe48 (== piVar2+0x3920
   * bytes). See tools/encodeoutgoingpacketfield_sites.json. */
  CopyGuardedBool((byte *)((int)piVar2 + 0x391b),(byte *)(param_7 + 0x391b));
  /* PEEK CELL CORRECTED 2026-08-27: this read was given piVar2+0xe48 by the
   * 2026-07-15 sweep, which had only established the ENCODE cell (edi =
   * ebp = piVar2) and carried that base across to the peek.  The binary
   * reads the OTHER object: `lea eax,[esi + 0x3920]` at 0x438da5, esi loaded
   * from [esp+0x8d4] = param_7 -- the same source object the
   * CopyGuardedBool above it copies from.  Frame check: the neighbouring
   * [esp+0x8d0] is param_6, witnessed by `mov [ebp+0x3f94],ecx` against
   * this file's own `piVar2[0xfe5] = param_6`. */
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  PeekPacketChecksumState((void *)(param_7 + 0x3920));
  EncodeOutgoingPacketField(piVar2 + 0xe48);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  pcVar7 = (char *)((int)piVar2 + 0x3813);
  pcVar4 = PTR_s_142blast_xes_0056d344;
  do {
    cVar1 = *pcVar4;
    pcVar4 = pcVar4 + 1;
    *pcVar7 = cVar1;
    pcVar7 = pcVar7 + 1;
  } while (cVar1 != '\0');
  /* piStack_8d0/puStack_8d4 below are Ghidra SEH-scope-table artifacts
   * (puStack_8d4's value is literally the return address right after
   * the FUN_0041da80 call, 0x438df2+5), not real arguments - left as
   * dead stores, matching the file's own established "raw stack
   * reference" artifact convention above. */
  piStack_8d0 = (int *)g_clientContext;
  puStack_8d4 = (undefined1 *)0x438df7;
  /* DROPPED-ARGUMENT FIX (2026-09-21): Ghidra dropped this call's real
   * args entirely (decompiled as a bare `FUN_0041da80()`, confusing the
   * SEH plumbing above for its arguments). Reconstructed from orig
   * 0x438dc6-0x438ded: `mov ecx,0xd` right before the call is
   * FUN_0041da80's own ECX param_1 (__thiscall, erased to a plain
   * leading stack arg per ghidra_types.h); the 5 stack pushes are (in
   * push order, deepest first) literal 1, `edx=[esp+0x8d0]` (this
   * file's own documented alias for this function's param_6, see the
   * comment a few lines above at piStack_8d0/puStack_8d4's real
   * counterpart), literal 1, `ebp` (this function's own object, piVar2),
   * and `eax=[0x5b3484]` (g_clientContext). */
  FUN_0041da80(0xd,g_clientContext,piVar2,1,param_6,1);
  iVar3 = GetPlayerRecordBySlot();
  if ((iVar3 != 0) && (cVar1 = PeekPacketChecksumBool((byte *)(iVar3 + 0xbfca)), cVar1 != '\0')) {
    EncodeChecksumDeltaDiv(piVar2 + 0x930,auStackEmitScratch,4);
    puStack_8 = (undefined1 *)0x1;
    EmitChecksumSum(piVar2 + 0x930, (void *)auStackEmitScratch);
    puStack_8 = (undefined1 *)0xffffffff;
    if (*(int *)(auStackEmitScratch + 0x14) != 0) {
      ScrambleChecksumGuardBytes(*(int *)(auStackEmitScratch + 0x14),&g_valueGuardKeyTable);
      TreeInsert(auTreeNode,&g_valueGuardMap);
    }
    EncodeChecksumDeltaDiv(piVar2 + 0x9b9,auStackEmitScratch,4);
    puStack_8 = (undefined1 *)0x2;
    EmitChecksumSum(piVar2 + 0x9b9, (void *)auStackEmitScratch);
    puStack_8 = (undefined1 *)0xffffffff;
    if (*(int *)(auStackEmitScratch + 0x14) != 0) {
      ScrambleChecksumGuardBytes(*(int *)(auStackEmitScratch + 0x14),&g_valueGuardKeyTable);
      TreeInsert(auTreeNode,&g_valueGuardMap);
    }
    EncodeChecksumDeltaDiv(piVar2 + 0xa42,auStackEmitScratch,4);
    puStack_8 = (undefined1 *)0x3;
    EmitChecksumSum(piVar2 + 0xa42, (void *)auStackEmitScratch);
    puStack_8 = (undefined1 *)0xffffffff;
    if (*(int *)(auStackEmitScratch + 0x14) != 0) {
      ScrambleChecksumGuardBytes(*(int *)(auStackEmitScratch + 0x14),&g_valueGuardKeyTable);
      TreeInsert(auTreeNode,&g_valueGuardMap);
    }
  }
  /* DROPPED-ARGUMENT FIX (2026-11-12): the six Mul/Div rounds below were
   * argless in the raw port.  Recovered from orig 0x438f45-0x4395c4 (esp
   * tracked through the whole frame, so every slot is a stable frame offset):
   * each round is
   *     mulR = DeltaMul(cell, scratch1, k);   k = 3, or the value peeked from
   *                                           0xe9c578 in the guarded block
   *     divR = DeltaDiv(mulR, scratch2, v);   v = the value peeked from
   *                                           0xe55ab8 / 0x796aa0
   *     Encode(cell, [Peek(cell) +] Peek(divR))
   * and then the two scratches' +0x14 guard pointers are scrambled and
   * TreeInsert'ed, DIV scratch first (reverse construction order).  The
   * scratches are the frame objects at -0x8a0 (A = auStackEmitScratch),
   * -0x67c (B), -0x458 (C) and -0x234 (D), 0x224 bytes apart; their +0x14
   * fields are the iStack_88c / iStack_668 / iStack_444 / iStack_220 locals
   * Ghidra split out.  The Ghidra locals iStack_894, iStack_680, iStack_670,
   * iStack_698 and friends were esp-drift artifacts and are gone.  The
   * restored epilogue chain is uStack_c (prologue's saved fs:[0]); the raw
   * port restored a state word that the artifact stores had overwritten. */
  cVar1 = PeekPacketChecksumBool((byte *)(g_clientContext + 0x5b818));
  if (cVar1 == '\x01') {
    iVarMul = EncodeChecksumDeltaMul(piVar2 + 2352,auScratchB,3);
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVarArg = PeekPacketChecksumState((void *)&DAT_00e55ab8);
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVarDiv = EncodeChecksumDeltaDiv(iVarMul,auStackEmitScratch,iVarArg);
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVarArg = PeekPacketChecksumState((void *)(piVar2 + 2352));
    EncodeOutgoingPacketField(piVar2 + 2352,iVarArg + PeekPacketChecksumState((void *)iVarDiv));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    if (*(int *)(auStackEmitScratch + 0x14) != 0) {
      ScrambleChecksumGuardBytes(*(int *)(auStackEmitScratch + 0x14),&g_valueGuardKeyTable);
      TreeInsert(auTreeNode,&g_valueGuardMap);
    }
    if (*(int *)(auScratchB + 0x14) != 0) {
      ScrambleChecksumGuardBytes(*(int *)(auScratchB + 0x14),&g_valueGuardKeyTable);
      TreeInsert(auTreeNode,&g_valueGuardMap);
    }
    iVarMul = EncodeChecksumDeltaMul(piVar2 + 2489,auStackEmitScratch,3);
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVarArg = PeekPacketChecksumState((void *)&DAT_00e55ab8);
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVarDiv = EncodeChecksumDeltaDiv(iVarMul,auScratchB,iVarArg);
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVarArg = PeekPacketChecksumState((void *)(piVar2 + 2489));
    EncodeOutgoingPacketField(piVar2 + 2489,iVarArg + PeekPacketChecksumState((void *)iVarDiv));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    if (*(int *)(auScratchB + 0x14) != 0) {
      ScrambleChecksumGuardBytes(*(int *)(auScratchB + 0x14),&g_valueGuardKeyTable);
      TreeInsert(auTreeNode,&g_valueGuardMap);
    }
    if (*(int *)(auStackEmitScratch + 0x14) != 0) {
      ScrambleChecksumGuardBytes(*(int *)(auStackEmitScratch + 0x14),&g_valueGuardKeyTable);
      TreeInsert(auTreeNode,&g_valueGuardMap);
    }
    iVarMul = EncodeChecksumDeltaMul(piVar2 + 2626,auStackEmitScratch,3);
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVarArg = PeekPacketChecksumState((void *)&DAT_00e55ab8);
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVarDiv = EncodeChecksumDeltaDiv(iVarMul,auScratchB,iVarArg);
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVarArg = PeekPacketChecksumState((void *)(piVar2 + 2626));
    EncodeOutgoingPacketField(piVar2 + 2626,iVarArg + PeekPacketChecksumState((void *)iVarDiv));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    if (*(int *)(auScratchB + 0x14) != 0) {
      ScrambleChecksumGuardBytes(*(int *)(auScratchB + 0x14),&g_valueGuardKeyTable);
      TreeInsert(auTreeNode,&g_valueGuardMap);
    }
    if (*(int *)(auStackEmitScratch + 0x14) != 0) {
      ScrambleChecksumGuardBytes(*(int *)(auStackEmitScratch + 0x14),&g_valueGuardKeyTable);
      TreeInsert(auTreeNode,&g_valueGuardMap);
    }
  }
  cVar1 = CheckGuardedBoolAnd();
  if (cVar1 != '\0') {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVarArg = PeekPacketChecksumState((void *)&DAT_00e9c578);
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVarMul = EncodeChecksumDeltaMul(piVar2 + 2352,auStackEmitScratch,iVarArg);
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVarArg = PeekPacketChecksumState((void *)&DAT_00796aa0);
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVarDiv = EncodeChecksumDeltaDiv(iVarMul,auScratchB,iVarArg);
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    EncodeOutgoingPacketField(piVar2 + 2352,PeekPacketChecksumState((void *)iVarDiv));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    if (*(int *)(auScratchB + 0x14) != 0) {
      ScrambleChecksumGuardBytes(*(int *)(auScratchB + 0x14),&g_valueGuardKeyTable);
      TreeInsert(auTreeNode,&g_valueGuardMap);
    }
    if (*(int *)(auStackEmitScratch + 0x14) != 0) {
      ScrambleChecksumGuardBytes(*(int *)(auStackEmitScratch + 0x14),&g_valueGuardKeyTable);
      TreeInsert(auTreeNode,&g_valueGuardMap);
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVarArg = PeekPacketChecksumState((void *)&DAT_00e9c578);
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVarMul = EncodeChecksumDeltaMul(piVar2 + 2489,auStackEmitScratch,iVarArg);
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVarArg = PeekPacketChecksumState((void *)&DAT_00796aa0);
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVarDiv = EncodeChecksumDeltaDiv(iVarMul,auScratchB,iVarArg);
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    EncodeOutgoingPacketField(piVar2 + 2489,PeekPacketChecksumState((void *)iVarDiv));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    if (*(int *)(auScratchB + 0x14) != 0) {
      ScrambleChecksumGuardBytes(*(int *)(auScratchB + 0x14),&g_valueGuardKeyTable);
      TreeInsert(auTreeNode,&g_valueGuardMap);
    }
    if (*(int *)(auStackEmitScratch + 0x14) != 0) {
      ScrambleChecksumGuardBytes(*(int *)(auStackEmitScratch + 0x14),&g_valueGuardKeyTable);
      TreeInsert(auTreeNode,&g_valueGuardMap);
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVarArg = PeekPacketChecksumState((void *)&DAT_00e9c578);
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVarMul = EncodeChecksumDeltaMul(piVar2 + 2626,auScratchD,iVarArg);
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVarArg = PeekPacketChecksumState((void *)&DAT_00796aa0);
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    iVarDiv = EncodeChecksumDeltaDiv(iVarMul,auScratchC,iVarArg);
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    EncodeOutgoingPacketField(piVar2 + 2626,PeekPacketChecksumState((void *)iVarDiv));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    if (*(int *)(auScratchC + 0x14) != 0) {
      ScrambleChecksumGuardBytes(*(int *)(auScratchC + 0x14),&g_valueGuardKeyTable);
      TreeInsert(auTreeNode,&g_valueGuardMap);
    }
    if (*(int *)(auScratchD + 0x14) != 0) {
      ScrambleChecksumGuardBytes(*(int *)(auScratchD + 0x14),&g_valueGuardKeyTable);
      TreeInsert(auTreeNode,&g_valueGuardMap);
    }
  }
  /* EDX = [0x5b3484] + 0x6a7f88, EDI = ebp, the projectile allocated at 0x438909 (original call at 0x4395d7); the port had passed (0,0,NULL). */
  RegisterActiveObject(0, (int)g_clientContext + 0x6a7f88, (undefined4 *)piVar2);
  *unaff_FS_OFFSET = uStack_c;
  return;
}

