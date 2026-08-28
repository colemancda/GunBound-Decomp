/* SpawnBattleAnnouncement - 0x00438360 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * DROPPED REGISTER RECOVERED (2026-08-27): unaff_ESI is read before written
 * (`test esi,esi` at 0x4383ba, `cmp esi,5` just after) and the callee ends in
 * a bare `ret`, so every argument is a register one and this is a plain
 * append with nothing to re-slot.
 *
 * Six of the seven sites load a literal -- `mov esi,5`, `mov esi,6` four
 * times, and `xor esi,esi` -- each read individually off the disassembly, so
 * they need no pairing.
 *
 * BeginNewTurn's site indexes a 4-entry table MSVC materialises in the frame
 * and that Ghidra dropped entirely, along with the peek result that indexes
 * it.  The table is {1, 3, 2, 4}, and getting those values right depends on
 * the pending-push term: the four stores at 0x4d0aa8-0x4d0ac0 each sit ONE
 * push deep (the `push 0x5a9068` at 0x4d0aa3), while the
 * `mov esi,[esp+esi*4+0x18]` that reads them back at 0x4d0ae5 has none.
 * Counted without that, the table appears to start one slot late and to run
 * to index 4.
 *
 * CAVEAT on that reconstruction: the original's read is unbounded -- the
 * index is the guarded value at g_clientContext+0x45354 with no range check,
 * so out of 0..3 the original reads adjacent frame bytes.  The C array is
 * faithful for in-range indices only; out of range it is undefined behaviour
 * rather than the original's specific garbage, and MSVC will not lay the
 * array out where the original did.
 *
 * NAMED 2026-08-27 (was SpawnBattleAnnouncement).  Puts up the battle's single
 * screen-centre announcement banner, showing frame `regEsi` of the
 * sprite set "yesoori.img".
 *
 * The object is class id 0x2e635 (190005) in the battle entity registry
 * at g_clientContext+0x6a7f8c, built by FUN_004b3b10 (which stamps that
 * id and vtable 0x5566c0).  That ctor has exactly one caller - this
 * function - so this is the only way the banner ever comes to exist.
 * Only one can be live: the ctor sets the registry key at +8 to 0, and
 * RegisterActiveObject destroys an incoming node whose key is already
 * present in the layer (its duplicate-node early-out at 0x4f300a) -
 * which is why this function unlinks and destroys the live instance
 * through vtable slot 0 (DeletePoisonedBaseObject) before allocating
 * its replacement.
 *
 * What that object is, all from outside this body:
 * - vtable slot 3 (0x4b3d50, uncarved) is its Draw, reached from the
 * entity draw pass FUN_00450c20 that State11_InBattle_Render runs
 * over this same registry (its case 0x2e635 selects blend mode 1,
 * SRC=5/DEST=6).  It copies the object's +0x48/+0x4c/+0x50 into
 * g_clientContext+0x23260/+0x23264/+0x23268, raises the byte flag at
 * +0x2325c, and calls 0x4b3b60, which blits sprite set 0x1bbc frame
 * [+0x44] into the surface pointer and pitch at +0x23254/+0x23258.
 * - those two cells are YesooriTexture's:
 * State11_InBattle_ClearEffectTextures locks that texture and stores
 * its lpSurface/lPitch into exactly them once per frame.  0x4b3b60
 * re-centres the frame's hotspot by +0x80 and clamps to 0..0xff, i.e.
 * a 256x256 destination.
 * - set 0x1bbc is loaded as "yesoori.img" by
 * State10_Loading_PreloadAssets (0x441608) and ProcessBattleFrame
 * (0x4df066); 0x4b3b60 is the only code that draws from it.
 * - State11_InBattle_RenderModeIcons draws the quad while the flag is
 * up: FUN_004ec120(alpha=+0x23268, 400, 0x12a, size=+0x23264,
 * angle=+0x23260) - one sprite at screen centre, so +0x48 is a
 * rotation in degrees, +0x4c a size and +0x50 an alpha.
 * - vtable slot 2 (0x4b3ce0, uncarved) is its Tick: phase 0 spins +0x48
 * from 0x100 to 0 while growing +0x4c 0->0x100 and fading +0x50 in;
 * phase 1 holds 20 ticks, but only once +0x44 is non-zero; phase 2
 * grows +0x4c past 0x200 while fading out, then sets the +0x14 kill
 * byte.  A transient, self-destroying overlay, not a HUD element.
 *
 * THE FRAMES ARE CONFIRMED (2026-08-27, decoded from graphics.xfs).
 * yesoori.img holds 9 flat ARGB4444 frames, all 256 wide, 194-254 tall,
 * hotspot x = -128; the art wraps each phrase onto two rows of the
 * 256-wide canvas.  By index:
 * 0 READY          1 SOLO START!    2 TAG START!
 * 3 SCORE START!   4 JEWEL START!   5 SUDDEN DEATH
 * 6 GREAT!!!       7 A Team Win!    8 B Team Win!
 * 7 and 8 are unreachable - no call site passes them.
 * Reproducing this needs more than tools/lzhuf does today: that decoder
 * reads only an entry's FIRST block, which is why large .img entries had
 * looked like noise past 4096 bytes.  A graphics.xfs entry is a CHAIN of
 * blocks, each `[u32 compressedSize][u32 checksum]` then one LZHUF
 * stream expanding to at most 4096 bytes (the checksum the client
 * verifies covers exactly that block).  yesoori.img is 235 such blocks;
 * decoding them all and concatenating makes every block checksum match
 * and the 9 frames parse exactly to the end of the entry - frame 0's
 * header is 0x30 bytes, later frames' 0x28 (no flags/frame-count pair).
 *
 * The seven call sites supply the frame key (EAX is uniformly
 * ctx+0x6a7f70, the effects-guard block whose +4 gate suppresses this
 * spawn exactly as it does every other effect spawner's):
 * 0        State11_InBattle_OnEnter, at battle entry - READY.  Note 0
 * is a real frame, not "no image": the Tick simply holds it
 * indefinitely, because phase 1 will not advance while +0x44
 * is still 0.
 * 1/3/2/4  BeginNewTurn, only when the turn counter at ctx+0xeba98 is
 * 0, indexed by the battle mode cell ctx+0x45354 through the
 * 4-entry table {1,3,2,4} that MSVC materialises in its
 * frame: mode 0 -> SOLO START!, mode 1 -> SCORE START!,
 * mode 2 -> TAG START! (2 is the value RenderModeIcons tests
 * before binding TagTexture), mode 3 -> JEWEL START!.  That
 * mapping independently confirms the table's reconstruction.
 * This is also what the +0x44==0 fast path serves: keys 1..4
 * turn the live READY banner into its mode banner in flight
 * rather than restarting the animation.
 * 5        SUDDEN DEATH, in State11_InBattle_ProcessBattleAction's
 * GB_ACT_TURN_TIMEOUT arm, between PlayMusicTrack(1,
 * "sudden.mp3") and the localized notice 0x267.
 * 6        GREAT!!!, in the score-award arm shared by
 * FinishTurnAndSelectNext, FUN_004ccd10,
 * State11_InBattle_ProcessBattleAction and
 * State11_InBattle_OnTick: ctx+k*0x224+0x5cba0 += 4, a
 * delta-scaled 500 added to +0x5ba80, a floating number over
 * the mobile via FUN_004368f0, notice 0x273/0x274.
 * Keys 5 and 6 fail the `< 5` test deliberately, so they always replace
 * whatever banner is up.
 *
 * NOT FIXED HERE: the trailing RegisterActiveObject(0,0,0) has dropped
 * arguments.  0x4383f6-0x438408 loads EDX = g_clientContext+0x6a7f88
 * (the registry container) and EDI = the freshly built object.
 */
#include "ghidra_types.h"


void SpawnBattleAnnouncement(int regEsi)

{
  uint uVar1;
  char cVar2;
  void *pvVar3;
  int iVar4;
  undefined4 *puVar5;
  int unaff_ESI = regEsi;
  bool bVar6;
  
  /* guard-cell: proven.  This helper receives the effects-guard block
   * ctx+0x6a7f70 in EAX (a register arg Ghidra dropped); every call
   * site in the binary was audited 2026-08-17 and passes exactly that
   * value, so the +4 peek is the global flag, not a per-object cell. */
  cVar2 = PeekPacketChecksumBool((byte *)(g_clientContext + 0x6a7f74));
  if (cVar2 != '\0') {
    return;
  }
  iVar4 = *(int *)(*(int *)(&DAT_006a7f8c + g_clientContext) + 0x1c);
  uVar1 = *(uint *)(iVar4 + 4);
  while (uVar1 < 0x2e636) {
    if (uVar1 == 0x2e635) {
      puVar5 = *(undefined4 **)(iVar4 + 0x10);
      bVar6 = true;
      if (puVar5[2] == 0) goto LAB_004383a5;
      break;
    }
    iVar4 = *(int *)(iVar4 + 0x1c);
    uVar1 = *(uint *)(iVar4 + 4);
  }
  goto LAB_004383df;
  while( true ) {
    puVar5 = (undefined4 *)puVar5[4];
    bVar6 = puVar5[2] == 0;
    if (!bVar6) break;
LAB_004383a5:
    if (bVar6) {
      if (((puVar5[0x11] == 0) && (unaff_ESI != 0)) && (unaff_ESI < 5)) {
        puVar5[0x11] = unaff_ESI;
        return;
      }
      *(undefined4 *)(puVar5[3] + 0x10) = puVar5[4];
      *(undefined4 *)(puVar5[4] + 0xc) = puVar5[3];
      (**(code **)*puVar5)(1);
      break;
    }
  }
LAB_004383df:
  pvVar3 = operator_new(0x58);
  if (pvVar3 == (void *)0x0) {
    iVar4 = 0;
  }
  else {
    FUN_004b3b10();
  }
  *(int *)(iVar4 + 0x44) = unaff_ESI;
  RegisterActiveObject(0, 0, (undefined4 *)0);
  return;
}

