/* DecodeMpegLayerISamples - 0x005133c0 in the original binary.
 *
 * Layer I frame decoder: header, bit allocation for every subband, then
 * the scalefactor / subband sample readers and the synthesis driver.
 *
 * Evidence for the name (all from outside the body):
 * Slot 3 of the frame-decoder table at 0x563aec (raw words 50f8b0 514fa0
 * 50f8b0 5133c0), which DecodeMpegAudioFrame indexes with the header layer
 * bits; the Layer II decoder (DecodeMpegLayerIISamples) is slots 0 and 2
 * and the Layer III trampoline slot 1, so slot 3 (bits 11) is Layer I as in
 * ISO 11172-3. The body calls ReadMpegLayerIScalefactors and
 * ReadMpegLayerISubbandSamples, then the synthesis driver installed in
 * PTR_FUN_005637cc by SetupMpegLayerIDecoder with the Layer I block length
 * 0xc, and returns EDX:EAX = (DAT_005a99f0 output bytes, padding +
 * DAT_005a9884) like its Layer II sibling. Structurally it is the same
 * routine as DecodeMpegLayerIISamples with the Layer I constants: 4-bit
 * allocation per subband, joint-stereo bound table at 0x563730, and cells
 * 0x1f / 0x1e as the allocation list terminators (Layer II uses 0x25 /
 * 0x24).
 *
 * Tables first used here: DAT_00563b00 (16 words, raw 0 2 3 4 .. 0xf 0x10,
 * the bits-per-sample step added to DAT_005ab8d4 for subbands at or above
 * the DAT_00563770 limit) and DAT_005ab8dc (16 words of runtime state
 * between the Layer II table at 0x5ab88c and the allocation list at
 * 0x5ab91c). Both are sized arrays here; neither was declared before.
 */
#include "ghidra_types.h"

/* Bit-reader refill, as inlined at every field read: top up the 32-bit
 * accumulator a byte at a time while fewer than n bits remain. */
#define L1_REFILL(n) \
  if (iVar5 < (n)) { \
    for (; iVar5 < 0x19; iVar5 = iVar5 + 8) { \
      uVar8 = uVar8 << 8 | (uint)*pbVar7; \
      pbVar7 = pbVar7 + 1; \
    } \
    DAT_005a9680 = pbVar7; \
  }

/* Take n bits off the accumulator into dest and publish the reader state. */
#define L1_TAKE(dest,n) \
  iVar5 = iVar5 - (n); \
  dest = uVar8 >> ((byte)iVar5 & 0x1f); \
  uVar8 = uVar8 - (dest << ((byte)iVar5 & 0x1f)); \
  DAT_005ab704 = iVar5; \
  DAT_005ab4f4 = uVar8;


undefined8 DecodeMpegLayerISamples(byte *param_1,undefined4 param_2)

{
  int iVar3;
  int iVar4;
  int iVar5;
  byte *pbVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  
  DAT_005ab704 = 0;
  uVar8 = 0;
  iVar5 = 0;
  DAT_005a9680 = param_1;
  DAT_005ab4f4 = 0;
  pbVar7 = param_1;
  do {
    iVar5 = iVar5 + 8;
    uVar8 = uVar8 << 8 | (uint)*pbVar7;
    pbVar7 = pbVar7 + 1;
  } while (iVar5 < 0x19);
  DAT_005a9680 = pbVar7;
  L1_TAKE(uVar10,0xc);                  /* 12-bit sync word */
  if (uVar10 != 0xfff) {
    return 0;
  }
  L1_REFILL(3);
  L1_TAKE(uVar10,3);                    /* ID + layer, discarded */
  L1_REFILL(1);
  L1_TAKE(uVar9,1);                     /* protection bit (EDX) */
  L1_REFILL(6);
  L1_TAKE(uVar10,6);                    /* bitrate index + sampling frequency */
  L1_REFILL(1);
  L1_TAKE(uVar10,1);                    /* padding bit */
  DAT_005a99ec = uVar10 << 2;
  L1_REFILL(1);
  L1_TAKE(uVar10,1);                    /* private bit */
  L1_REFILL(4);
  L1_TAKE(uVar10,4);                    /* mode + mode extension */
  _DAT_005ab8d8 = DAT_00563730[uVar10];
  iVar3 = _DAT_005ab8d8;
  if (uVar9 == 0) {
    L1_REFILL(0x14);
    iVar5 = iVar5 + -0x14;              /* copyright/original/emphasis + 16-bit CRC */
  }
  else {
    L1_REFILL(4);
    iVar5 = iVar5 + -4;                 /* copyright/original/emphasis */
  }
  uVar10 = uVar8 >> ((byte)iVar5 & 0x1f);
  DAT_005ab704 = iVar5;
  DAT_005ab8d4 = 0;
  uVar8 = uVar8 - (uVar10 << ((byte)iVar5 & 0x1f));
  iVar4 = 0;
  DAT_005ab4f4 = uVar8;
  if (0 < (int)DAT_00563b44) {
    do {
      L1_REFILL(4);
      L1_TAKE(uVar10,4);                /* bit allocation of this subband */
      DAT_005ab888 = uVar10;
      (&DAT_005ab91c)[iVar4] = uVar10;
      (&DAT_005ab604)[iVar4] = uVar10;
      if ((int)DAT_00563770 <= iVar4) {
        DAT_005ab8d4 = DAT_005ab8d4 + DAT_00563b00[uVar10];
      }
      uVar11 = DAT_005ab8dc[uVar10];
      (&DAT_005a9684)[iVar4] = uVar11;
      iVar3 = iVar3 + -1;
      if (iVar3 < 0) {
        (&DAT_005ab608)[iVar4] = uVar10;
        (&DAT_005ab91c)[iVar4] = uVar10 + 0xf;
        (&DAT_005ab920)[iVar4] = uVar10 + 0xf;
        (&DAT_005a9688)[iVar4] = uVar11;
        iVar4 = iVar4 + 1;
      }
      iVar4 = iVar4 + 1;
    } while (iVar4 < (int)DAT_00563b44);
  }
  (&DAT_005ab91c)[DAT_00563770] = 0x1f;
  (&DAT_005ab91c)[iVar4] = 0x1e;
  ReadMpegLayerIScalefactors();
  ReadMpegLayerISubbandSamples();
  (*(code *)PTR_FUN_005637cc)(&DAT_00f25f00,param_2,0xc);
  return CONCAT44(DAT_005a99f0,DAT_005a99ec + DAT_005a9884);
}
