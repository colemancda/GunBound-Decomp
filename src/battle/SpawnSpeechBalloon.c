/* SpawnSpeechBalloon - 0x004382d0 in the original binary.
 *
 * Spawns the over-head speech balloon (class id 500000 in the battle
 * entity registry at ctx+0x6a7f8c) carrying the given text, keyed by the
 * slot/id in regEcx.  Evidence, all outside this body:
 *
 * - State11_InBattle_ProcessBattleAction's three sites sit in the action
 *   0x4002/0x4004 arms - 0x4002 is that file's confirmed proximity-
 *   filtered chat message - and pass the copied chat buffer as regEbx
 *   and the wire slot byte (+8) as regEcx.  SpawnJewel, TickJewelFrame
 *   (x2) and State11_InBattle_OnTick pass RNG-picked GetLocalizedString
 *   lines (0x7f9/0x803/0x80d/0x7db/0x7e5/0x7ef families) with a jewel or
 *   roster slot - taunt/reaction lines through the same balloon.
 * - The 0x46c entity's ctor (InitSpeechBalloon, 0x44fd00) stamps class
 *   id 500000 at +4 and the slot/id at +8, exactly the
 *   DAT_006a7f8c-registry convention (class at obj+4, index key at
 *   obj+8) that InitJewel/InitMobile follow.  SpawnJewel independently
 *   walks that registry for class 500000 at index slot+8 and destroys
 *   the node before calling here - one balloon per slot, replaced on the
 *   next line.
 * - This body's own eviction does the same thing through 0x4f30c0
 *   (named FindSpriteFrame, but really the generic two-level keyed
 *   lookup: EAX=ctx+0x6a7f88, EDX=500000, ESI=this function's regEcx
 *   still live from the prologue's `mov esi,ecx`), then unlinks the
 *   +0xc/+0x10 pair and virtual-destroys - the zero-arg
 *   FindSpriteFrame()/RegisterActiveObject(0,0,0) calls this port still
 *   carries are part of the tree-wide dropped-register backlog for
 *   those two callees, not resolved here.
 * - The text lands at balloon+0x1d4 and is word-wrapped into the +0x44
 *   line buffer by SetSpeechBalloonText (0x450600) via RenderWrappedText
 *   (wrap width 15, 20-byte line slots).
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


void SpawnSpeechBalloon(int regEcx,int regEax,char *regEbx)

{
  char cVar1;
  undefined4 *puVar2;
  void *pvVar3;

  /* guard-cell: proven.  regEax is the effects-guard block ctx+0x6a7f70
   * (register arg promoted 2026-09-01, all 8 sites re-verified); every
   * caller passes exactly that value, so the +4 peek is the global flag.
   * regEcx is the per-object slot/id this balloon is keyed by (forwarded
   * to InitSpeechBalloon's EAX -> obj+8; see its file header).  regEbx
   * is the balloon text. */
  cVar1 = PeekPacketChecksumBool((byte *)(regEax + 4));
  if ((cVar1 == '\0') && (regEbx != (char *)0x0)) {
    puVar2 = (undefined4 *)FindSpriteFrame();
    if (puVar2 != (undefined4 *)0x0) {
      *(undefined4 *)(puVar2[3] + 0x10) = puVar2[4];
      *(undefined4 *)(puVar2[4] + 0xc) = puVar2[3];
      (**(code **)*puVar2)(1);
    }
    pvVar3 = operator_new(0x46c);
    if (pvVar3 != (void *)0x0) {
      InitSpeechBalloon(0,(undefined4 *)pvVar3,regEcx);
    }
    SetSpeechBalloonText((int)pvVar3,regEbx);
    RegisterActiveObject(0, 0, (undefined4 *)0);
  }
  return;
}

