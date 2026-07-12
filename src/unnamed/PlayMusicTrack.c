/* PlayMusicTrack - 0x004eea30 in the original binary.
 *
 * Music-track control: given a track name (passed in a register, invisible
 * to the C signature), compares it against the currently-playing track
 * (DAT_00793568) and returns early if unchanged, otherwise switches to it
 * via the sound object's vtable+0xc. Called from most screens' OnEnter
 * (title.mp3, channel.mp3, logo.mp3, stage%d.mp3). See ARCHITECTURE.md
 * audio section.
 *
 * unaff_EDI (the track name) arrives via a dropped EDI register - orig
 * 0x44329a (State06_Logo2_OnEnter's call site): `mov edi, 0x555570` ->
 * "logo2.mp3", AFTER an explicit `push 0x0` (param_1, unused in the
 * decompiled body but still a real stack argument affecting caller-side
 * cleanup) - promoted both to explicit parameters.
 *
 * Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


uint PlayMusicTrack(undefined4 param_1, byte *unaff_EDI)

{
  byte bVar1;
  uint in_EAX;
  byte *pbVar2;
  byte *pbVar3;
  int iVar4;
  uint uVar5;
  byte *pbVar6;
  bool bVar7;
  (void)param_1;

  if ((unaff_EDI != (byte *)0x0) &&
     (in_EAX = CONCAT31((int3)(in_EAX >> 8),DAT_0079354a), DAT_0079354a != '\0')) {
    pbVar2 = unaff_EDI;
    do {
      bVar1 = *pbVar2;
      pbVar2 = pbVar2 + 1;
    } while (bVar1 != 0);
    in_EAX = 0;
    if ((int)pbVar2 - (int)(unaff_EDI + 1) != 0) {
      pbVar3 = &DAT_00793568;
      pbVar6 = unaff_EDI;
      do {
        bVar1 = *pbVar3;
        bVar7 = bVar1 < *pbVar6;
        if (bVar1 != *pbVar6) {
LAB_004eea8f:
          iVar4 = (1 - (uint)bVar7) - (uint)(bVar7 != 0);
          goto LAB_004eea94;
        }
        if (bVar1 == 0) break;
        bVar1 = pbVar3[1];
        bVar7 = bVar1 < pbVar6[1];
        if (bVar1 != pbVar6[1]) goto LAB_004eea8f;
        pbVar3 = pbVar3 + 2;
        pbVar6 = pbVar6 + 2;
      } while (bVar1 != 0);
      iVar4 = 0;
LAB_004eea94:
      if (iVar4 == 0) {
        return 1;
      }
      (**(code **)(*(int *)*DAT_00793554 + 0xc))((int)pbVar2 - (int)(unaff_EDI + 1));
      iVar4 = (int)&DAT_00793568 - (int)unaff_EDI;
      do {
        bVar1 = *unaff_EDI;
        unaff_EDI[iVar4] = bVar1;
        unaff_EDI = unaff_EDI + 1;
      } while (bVar1 != 0);
      uVar5 = (**(code **)(*(int *)*DAT_00793554 + 8))(0);
      return uVar5;
    }
  }
  return in_EAX & 0xffffff00;
}

