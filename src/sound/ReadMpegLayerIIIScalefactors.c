/* ReadMpegLayerIIIScalefactors - 0x00519260 in the original binary.
 *
 * Read the Layer III scalefactors for one granule and channel (MPEG-1
 * path).
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified; see src/README.md's "Raw/verbatim ports"
 * section.
 *
 * Evidence for the name (all from outside the body):
 * Called from DecodeMpegLayerIIIGranule when DAT_005ae34c != 0.
 * DAT_005ae34c is a header bit read at 0x515b90 right after the 0xfff sync
 * (the ID bit, one bit after the 12-bit sync) and indexes the bitrate
 * tables as [bit][bitrate index] at 0x515b90 and 0x514fc0, so it is the
 * MPEG-1 / MPEG-2 selector. Uses the (slen1, slen2) table at 0x5448e8,
 * whose 16 entries (0,0),(0,1),(0,2),(0,3),(3,0),... match ISO 11172-3 for
 * scalefac_compress.
 */
#include "ghidra_types.h"


void ReadMpegLayerIIIScalefactors(undefined4 *param_1,int param_2,int param_3,int param_4)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  int iVar5;
  
  uVar3 = g_mpegSlenTab[*(int *)(param_2 + 0xc) * 2];
  uVar1 = g_mpegSlenTab[*(int *)(param_2 + 0xc) * 2 + 1];
  if (*(int *)(param_2 + 0x14) == 2) {
    if (*(int *)(param_2 + 0x18) == 0) {
      iVar5 = 6;
      puVar4 = param_1 + 0x24;
      do {
        uVar2 = ConsumeMpegBits(uVar3);
        puVar4[-0xd] = uVar2;
        uVar2 = ConsumeMpegBits(uVar3);
        *puVar4 = uVar2;
        uVar2 = ConsumeMpegBits(uVar3);
        puVar4[0xd] = uVar2;
        puVar4 = puVar4 + 1;
        iVar5 = iVar5 + -1;
      } while (iVar5 != 0);
      iVar5 = 6;
      param_1 = param_1 + 0x2a;
      do {
        uVar3 = ConsumeMpegBits(uVar1);
        param_1[-0xd] = uVar3;
        uVar3 = ConsumeMpegBits(uVar1);
        *param_1 = uVar3;
        uVar3 = ConsumeMpegBits(uVar1);
        param_1[0xd] = uVar3;
        param_1 = param_1 + 1;
        iVar5 = iVar5 + -1;
      } while (iVar5 != 0);
      return;
    }
    iVar5 = 8;
    puVar4 = param_1;
    do {
      uVar2 = ConsumeMpegBits(uVar3);
      *puVar4 = uVar2;
      puVar4 = puVar4 + 1;
      iVar5 = iVar5 + -1;
    } while (iVar5 != 0);
    iVar5 = 3;
    puVar4 = param_1 + 0x27;
    do {
      uVar2 = ConsumeMpegBits(uVar3);
      puVar4[-0xd] = uVar2;
      uVar2 = ConsumeMpegBits(uVar3);
      *puVar4 = uVar2;
      uVar2 = ConsumeMpegBits(uVar3);
      puVar4[0xd] = uVar2;
      puVar4 = puVar4 + 1;
      iVar5 = iVar5 + -1;
    } while (iVar5 != 0);
    iVar5 = 6;
    param_1 = param_1 + 0x2a;
    do {
      uVar3 = ConsumeMpegBits(uVar1);
      param_1[-0xd] = uVar3;
      uVar3 = ConsumeMpegBits(uVar1);
      *param_1 = uVar3;
      uVar3 = ConsumeMpegBits(uVar1);
      param_1[0xd] = uVar3;
      param_1 = param_1 + 1;
      iVar5 = iVar5 + -1;
    } while (iVar5 != 0);
    return;
  }
  if (param_4 != 0) {
    if ((param_3 & 8) == 0) {
      iVar5 = 6;
      puVar4 = param_1;
      do {
        uVar2 = ConsumeMpegBits(uVar3);
        *puVar4 = uVar2;
        puVar4 = puVar4 + 1;
        iVar5 = iVar5 + -1;
      } while (iVar5 != 0);
    }
    else {
      iVar5 = 6;
      puVar4 = param_1;
      do {
        *puVar4 = puVar4[-0x7c];
        puVar4 = puVar4 + 1;
        iVar5 = iVar5 + -1;
      } while (iVar5 != 0);
    }
    if ((param_3 & 4) == 0) {
      puVar4 = param_1 + 6;
      iVar5 = 5;
      do {
        uVar2 = ConsumeMpegBits(uVar3);
        *puVar4 = uVar2;
        puVar4 = puVar4 + 1;
        iVar5 = iVar5 + -1;
      } while (iVar5 != 0);
    }
    else {
      puVar4 = param_1 + 6;
      iVar5 = 5;
      do {
        *puVar4 = puVar4[-0x7c];
        puVar4 = puVar4 + 1;
        iVar5 = iVar5 + -1;
      } while (iVar5 != 0);
    }
    if ((param_3 & 2) == 0) {
      puVar4 = param_1 + 0xb;
      iVar5 = 5;
      do {
        uVar3 = ConsumeMpegBits(uVar1);
        *puVar4 = uVar3;
        puVar4 = puVar4 + 1;
        iVar5 = iVar5 + -1;
      } while (iVar5 != 0);
    }
    else {
      puVar4 = param_1 + 0xb;
      iVar5 = 5;
      do {
        *puVar4 = puVar4[-0x7c];
        puVar4 = puVar4 + 1;
        iVar5 = iVar5 + -1;
      } while (iVar5 != 0);
    }
    if ((param_3 & 1) == 0) {
      param_1 = param_1 + 0x10;
      iVar5 = 5;
      do {
        uVar3 = ConsumeMpegBits(uVar1);
        *param_1 = uVar3;
        param_1 = param_1 + 1;
        iVar5 = iVar5 + -1;
      } while (iVar5 != 0);
      return;
    }
    param_1 = param_1 + 0x10;
    iVar5 = 5;
    do {
      *param_1 = param_1[-0x7c];
      param_1 = param_1 + 1;
      iVar5 = iVar5 + -1;
    } while (iVar5 != 0);
    return;
  }
  iVar5 = 0xb;
  puVar4 = param_1;
  do {
    uVar2 = ConsumeMpegBits(uVar3);
    *puVar4 = uVar2;
    puVar4 = puVar4 + 1;
    iVar5 = iVar5 + -1;
  } while (iVar5 != 0);
  iVar5 = 10;
  param_1 = param_1 + 0xb;
  do {
    uVar3 = ConsumeMpegBits(uVar1);
    *param_1 = uVar3;
    param_1 = param_1 + 1;
    iVar5 = iVar5 + -1;
  } while (iVar5 != 0);
  return;
}

