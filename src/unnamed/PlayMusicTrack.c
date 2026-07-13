/* PlayMusicTrack - 0x004eea30 in the original binary.
 *
 * Music-track control: given a track name (passed in a register, invisible
 * to the C signature), compares it against the currently-playing track
 * (DAT_00793568) and returns early if unchanged, otherwise switches to it
 * via the sound channel object's vtable+0xc ("stop current") and
 * vtable+0x8 ("start new"). Called from most screens' OnEnter (title.mp3,
 * channel.mp3, logo.mp3, stage%d.mp3). See ARCHITECTURE.md audio section.
 *
 * unaff_EDI (the track name) arrives via a dropped EDI register - orig
 * 0x44329a (State06_Logo2_OnEnter's call site): `mov edi, 0x555570` ->
 * "logo2.mp3", AFTER an explicit `push 0x0` (param_1, unused in the
 * decompiled body but still a real stack argument affecting caller-side
 * cleanup) - promoted both to explicit parameters.
 *
 * Both vtable calls were also CALLING-CONVENTION CAST MISMATCHES (raw
 * `code**` cdecl cast on what's actually a __fastcall(this) callee) -
 * confirmed by disassembling 0x4eea9e-0x4eead2:
 *   +0xc slot: `mov ecx,[*DAT_00793554]; mov edx,[ecx]; call [edx+0xc]`
 *     with NO stack push at all - __fastcall(this) taking zero other
 *     args, same vtable slot/shape as InitGame.c's ChannelVtableFn.
 *   +0x8 slot: `mov ecx,[*DAT_00793554]; ...; push param_1; push edi;
 *     push 0x0; call [edx+8]` - __fastcall(this) plus 3 cdecl-style
 *     stack args (0, track-name pointer, param_1), this in ECX. The old
 *     code passed the this pointer nowhere and only pushed a literal 0,
 *     silently dropping both the updated track-name pointer and param_1.
 *
 * Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"

typedef void (__fastcall *ChannelStopFn)(void *thisPtr);
typedef uint (__fastcall *ChannelStartFn)(void *thisPtr, int a1, byte *trackName, int a2);

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
      (*(ChannelStopFn *)(*(int *)*DAT_00793554 + 0xc))(*DAT_00793554);
      iVar4 = (int)&DAT_00793568 - (int)unaff_EDI;
      pbVar3 = unaff_EDI;
      do {
        bVar1 = *pbVar3;
        pbVar3[iVar4] = bVar1;
        pbVar3 = pbVar3 + 1;
      } while (bVar1 != 0);
      uVar5 = (*(ChannelStartFn *)(*(int *)*DAT_00793554 + 8))
                        (*DAT_00793554, 0, unaff_EDI, (int)param_1);
      return uVar5;
    }
  }
  return in_EAX & 0xffffff00;
}

