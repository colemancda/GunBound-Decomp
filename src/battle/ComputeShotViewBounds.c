/* ComputeShotViewBounds - 0x004e51f0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-REG FIX (2026-08-28): the second of this function's two register
 * arguments. 0x4e53a0 is a bare `ret` and the body reads no [esp+N] at
 * all, so both inputs are registers: ESI is the shot/camera context
 * (already promoted as regEsi) and EAX is the shot's spawn X.
 *
 * EAX is read before written - the body seeds its running min and max
 * from it, compares it against *(regEsi + 8), then folds every terrain
 * column at DAT_006a7f78 into the pair and finally writes the 800-wide
 * window regEsi+0x24 / regEsi+0x28 around the result with the +/-0x96
 * margins. A horizontal coordinate, in other words, which is what the
 * three call sites confirm.
 *
 * All three sites needed frame arithmetic rather than pairing, because
 * ESI is uniform (`add esi,0x6a7708` at every one) and each caller is a
 * different file, so there is nothing to pair. Two load EAX in their own
 * SEH prologue, three pushes deep:
 *
 *   SpawnPrimaryShot    0x42bbbe  mov eax,[esp+0x24]  esp = entry-0xc
 *                                 -> entry+0x18 = param_6
 *   SpawnSuperShot      0x42de7e  mov eax,[esp+0x20]  esp = entry-0xc
 *                                 -> entry+0x14 = param_5
 *   SpawnItemProjectile 0x4317f2  mov eax,[esp+0x2c]  esp = entry-0x20
 *                                 -> entry+0xc  = param_3
 *
 * The third frame is confirmed independently by the very next
 * instruction pair: `or edi,0xffffffff / mov [esp+0x1c],edi` at
 * 0x4317f6 reaches entry-4, which is the source's own
 * `local_4 = 0xffffffff` on the line above the call. Nothing writes EAX
 * between the load and the call at any of the three.
 *
 * The three recovered parameters corroborate each other: each is the
 * value its caller hands to EncodeOutgoingPacketField twice, once plain
 * and once shifted left by 8 (SpawnPrimaryShot at +0x45e and +0x99,
 * SpawnSuperShot at the same offsets, SpawnItemProjectile at +0xf54 and
 * +0x40) - a coordinate stored both as an integer and as its 8.8
 * fixed-point twin.
 */
#include "ghidra_types.h"


void ComputeShotViewBounds(int regEsi,uint regEax)

{
  uint uVar1;
  uint in_EAX = regEax;
  uint uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  
  uVar1 = *(uint *)(&DAT_006a7f7c + g_clientContext);
  if (uVar1 == 0) {
    *(undefined1 *)(regEsi + 0x2c) = 1;
    return;
  }
  uVar5 = *(uint *)(regEsi + 8);
  uVar6 = in_EAX;
  if (((int)uVar5 < (int)in_EAX) || (uVar6 = uVar5, (int)uVar5 <= (int)in_EAX)) {
    in_EAX = uVar5;
  }
  uVar5 = 0;
  if (uVar1 != 0) {
    iVar4 = 0;
    do {
      if (*(uint *)(&DAT_006a7f7c + g_clientContext) <= uVar5) {
                    /* WARNING: Subroutine does not return */
        ThrowCxxException(0x80070057);
      }
      uVar2 = (uint)*(ushort *)(*(int *)(&DAT_006a7f78 + g_clientContext) + 2 + iVar4);
      if ((int)uVar6 <= (int)uVar2) {
        uVar6 = uVar2;
      }
      if ((int)uVar2 <= (int)in_EAX) {
        in_EAX = uVar2;
      }
      uVar5 = uVar5 + 1;
      iVar4 = iVar4 + 6;
    } while (uVar5 < uVar1);
  }
  *(uint *)(regEsi + 0x24) = in_EAX + 0x96;
  *(uint *)(regEsi + 0x28) = uVar6 - 0x96;
  if ((int)(uVar6 - 400) < (int)(in_EAX + 400)) {
    iVar4 = (int)(uVar6 - in_EAX) / 2 + -400 + in_EAX;
    *(int *)(regEsi + 0x24) = iVar4;
    *(int *)(regEsi + 0x28) = iVar4 + 800;
  }
  if ((*(int *)(regEsi + 8) + -300 < (int)in_EAX) && ((int)uVar6 < *(int *)(regEsi + 8) + 300)
     ) {
    *(undefined1 *)(regEsi + 0x2e) = 1;
  }
  iVar4 = *(int *)(regEsi + 0x24);
  iVar3 = *(int *)(regEsi + 0x18) + -400;
  iVar7 = iVar3;
  if (iVar4 <= iVar3) {
    iVar7 = iVar4;
  }
  if (iVar7 < 400) {
    iVar4 = 400;
  }
  else if (iVar3 < iVar4) {
    iVar4 = iVar3;
  }
  *(int *)(regEsi + 0x24) = iVar4;
  iVar4 = *(int *)(regEsi + 0x28);
  iVar7 = iVar3;
  if (iVar4 <= iVar3) {
    iVar7 = iVar4;
  }
  if (iVar7 < 400) {
    iVar3 = 400;
  }
  else if (iVar4 <= iVar3) {
    iVar3 = iVar4;
  }
  *(int *)(regEsi + 0x28) = iVar3;
  *(undefined1 *)(regEsi + 0x2c) = 0;
  *(undefined1 *)(regEsi + 0x864) = 1;
  *(undefined1 *)(regEsi + 0x2d) = 1;
  return;
}

