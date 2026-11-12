/* DecodeMpegLayerIIISamples - 0x00514fc0 in the original binary.
 *
 * Layer III frame decoder (MPEG-1 path, two granules): header and side
 * info, bit reservoir, then both granules.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified; see src/README.md's "Raw/verbatim ports"
 * section.
 *
 * Evidence for the name (all from outside the body):
 * Installed by SetupMpegLayerIIIDecoder as PTR_FUN_00563da8 and reached
 * through the slot-1 trampoline (0x514fa0) of the frame-decoder table at
 * 0x563aec, alongside the already named DecodeMpegLayerIISamples in slot
 * 2. It re-reads the 0xfff sync and header, splitting mode extension into
 * DAT_005aba2c (bit 0, intensity) and DAT_005ae348 (bit 1, mid/side) as in
 * ISO 11172-3, parses the Layer III side info (main_data_begin, scfsi,
 * big_values, global_gain, scalefac_compress, window switching), manages
 * the bit reservoir, and calls DecodeMpegLayerIIIGranule(buf, 0) and (buf
 * + DAT_005ae7e0, 1).
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 DecodeMpegLayerIIISamples(byte *param_1,undefined4 *param_2)

{
  undefined1 uVar1;
  int iVar2;
  size_t _Size;
  int iVar4;
  uint uVar5;
  undefined2 uVar6;
  uint uVar7;
  int iVar8;
  int *piVar9;
  undefined4 *puVar10;
  bool bVar11;
  int iHdrProtection;
  int iHdrBitrateIdx;
  int *local_8;
  int local_4;
  
  DAT_00f25ed0 = DAT_00f25ed0 + 1;
  uVar5 = 0;
  DAT_00f25e0c = param_1;
  iVar4 = 0;
  DAT_00f25e08 = param_1;
  do {
    iVar2 = iVar4;
    iVar4 = iVar2 + 8;
    uVar5 = (uint)*DAT_00f25e08 | uVar5 << 8;
    DAT_00f25e08 = DAT_00f25e08 + 1;
  } while (iVar4 < 0x19);
  DAT_00f25e04 = iVar2 + -4;
  uVar7 = uVar5 >> ((byte)DAT_00f25e04 & 0x1f);
  DAT_00f25e00 = uVar5 - (uVar7 << ((byte)DAT_00f25e04 & 0x1f));
  if (uVar7 == 0xfff) {
    /* The nine header reads at 0x515046..0x51508f keep their EAX results:
     * 0x51504e stores the first (ID bit) into DAT_005ae34c - the only write
     * to it outside 0x515b90 - and the rest land in ESI/EDI/cells below.
     * Ghidra dropped every one of these returns. */
    DAT_005ae34c = ConsumeMpegBits(1);
    ConsumeMpegBits(2);                       /* layer, discarded */
    iHdrProtection = ConsumeMpegBits(1);      /* ESI */
    iHdrBitrateIdx = ConsumeMpegBits(4);      /* EDI */
    DAT_005ae924 = ConsumeMpegBits(2);
    DAT_005ae33c = ConsumeMpegBits(1);
    ConsumeMpegBits(1);                       /* private bit, discarded */
    DAT_005ae7e8 = ConsumeMpegBits(2);
    DAT_005ae7ec = ConsumeMpegBits(2);
    if (DAT_005ae7e8 != 1) {
      DAT_005ae7ec = 0;
    }
    DAT_005aba2c = DAT_005ae7ec & 1;
    DAT_005ae348 = (int)DAT_005ae7ec >> 1;
    DAT_005ada38 = 0;
    if (iHdrProtection == 0) {
      ConsumeMpegBits(0x14);
      DAT_005ada38 = 2;
    }
    else {
      ConsumeMpegBits(4);
    }
    if (0 < iHdrBitrateIdx) {
      DAT_005aba30 = (g_mpegL3BitrateTab[DAT_005ae34c * 0x10 + iHdrBitrateIdx] * 0xb40) /
                     g_mpegL3RateTab[DAT_005ae924 + DAT_005ae34c * 4];
    }
    DAT_005ae7f0 = ConsumeMpegBits(9);
    bVar11 = DAT_005ae7e8 != 3;
    if (bVar11) {
      DAT_005ae7f4 = ConsumeMpegBits(3);
      iVar4 = 2;
      DAT_005ae7dc = 2;
      local_4 = 0x24;
    }
    else {
      DAT_005ae7f4 = ConsumeMpegBits(5);
      iVar4 = 1;
      DAT_005ae7dc = 1;
      local_4 = 0x15;
    }
    _DAT_005ae340 = (uint)bVar11;
    /* Side info (0x51518a-0x5152e8): every ConsumeMpegBits result is stored
     * to the cell named by the mov that follows each call. Ghidra dropped
     * each EAX return and the stores read stale locals. */
    iVar8 = 0;
    iVar2 = 0;
    if (iVar4 != 0) {
      puVar10 = &DAT_005ae7f8;
      do {
        *puVar10 = ConsumeMpegBits(4);        /* 0x515197 -> [edi] */
        iVar8 = iVar8 + 1;
        puVar10 = puVar10 + 1;
        iVar2 = DAT_005ae7dc;
      } while (iVar8 < DAT_005ae7dc);
    }
    local_8 = &DAT_005ae808;
    do {
      iVar4 = 0;
      piVar9 = local_8;
      if (0 < iVar2) {
        do {
          piVar9[-2] = ConsumeMpegBits(0xc);   /* 0x5151c1 -> [esi-8] */
          piVar9[-1] = ConsumeMpegBits(9);     /* 0x5151c8 -> [esi-4] */
          iVar2 = ConsumeMpegBits(8) + DAT_005ae928; /* 0x5151d2 */
          bVar11 = DAT_005ae348 != 0;
          *piVar9 = iVar2;                     /* [esi] */
          if (bVar11) {
            *piVar9 = iVar2 + -2;
          }
          piVar9[1] = ConsumeMpegBits(4);      /* 0x5151f8 -> [esi+4] */
          iVar2 = ConsumeMpegBits(1);          /* 0x5151ff -> [esi+8] */
          piVar9[2] = iVar2;
          if (iVar2 == 0) {
            piVar9[4] = 0;
            piVar9[3] = 0;
            piVar9[5] = ConsumeMpegBits(5);    /* [esi+0x14] */
            piVar9[6] = ConsumeMpegBits(5);    /* [esi+0x18] */
            piVar9[7] = ConsumeMpegBits(5);    /* [esi+0x1c] */
            piVar9[0xb] = ConsumeMpegBits(4);  /* [esi+0x2c] */
            piVar9[0xc] = ConsumeMpegBits(3);  /* [esi+0x30] */
          }
          else {
            piVar9[3] = ConsumeMpegBits(2);    /* [esi+0xc] */
            piVar9[4] = ConsumeMpegBits(1);    /* [esi+0x10] */
            piVar9[5] = ConsumeMpegBits(5);    /* [esi+0x14] */
            piVar9[6] = ConsumeMpegBits(5);    /* [esi+0x18] */
            piVar9[8] = ConsumeMpegBits(3);    /* [esi+0x20] */
            piVar9[9] = ConsumeMpegBits(3);    /* [esi+0x24] */
            piVar9[10] = ConsumeMpegBits(3);   /* [esi+0x28] */
            piVar9[0xb] = 7;
            piVar9[0xc] = 0xd;
          }
          piVar9[0xd] = ConsumeMpegBits(1);    /* [esi+0x34] */
          piVar9[0xe] = ConsumeMpegBits(1);    /* [esi+0x38] */
          piVar9[0xf] = ConsumeMpegBits(1);    /* [esi+0x3c] */
          iVar4 = iVar4 + 1;
          piVar9 = piVar9 + 0x12;
          iVar2 = DAT_005ae7dc;
        } while (iVar4 < DAT_005ae7dc);
      }
      local_8 = local_8 + 0x24;
    } while (local_8 < (int *)&DAT_005ae808 + 2 * 0x24);
    iVar4 = DAT_005aba30 + DAT_005ae33c;
    DAT_005ae930 = DAT_005ae934 - DAT_005ae7f0;
    DAT_005ae350 = iVar4;
    if (0x1a24 < (int)DAT_005ae934) {
      _memmove(&DAT_005aba38,&DAT_005aba38 + DAT_005ae930,DAT_005ae7f0); /* byte offsets: DAT_005aba38 is the byte reservoir */
      DAT_005ae930 = 0;
      DAT_005ae934 = DAT_005ae7f0;
    }
    _Size = (DAT_005ae350 - DAT_005ada38) - local_4;
    if ((-1 < (int)_Size) && ((int)_Size < 0x2001)) {
      _memmove(&DAT_005aba38 + DAT_005ae934,param_1 + DAT_005ada38 + local_4,_Size);
      uVar1 = DAT_005ae92c;
      uVar5 = DAT_005ae344;
      DAT_005ae934 = DAT_005ae934 + _Size;
      if ((int)DAT_005ae930 < 0) {
        uVar6 = CONCAT11(DAT_005ae92c,DAT_005ae92c);
        for (uVar7 = DAT_005ae344 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
          *param_2 = CONCAT22(uVar6,uVar6);
          param_2 = param_2 + 1;
        }
        for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
          *(undefined1 *)param_2 = uVar1;
          param_2 = (undefined4 *)((int)param_2 + 1);
        }
        return CONCAT44(DAT_005ae344,iVar4);
      }
      DAT_005ae920 = DAT_005ae930 * 8;
      DecodeMpegLayerIIIGranule(param_2,0);
      DecodeMpegLayerIIIGranule((undefined1 *)(DAT_005ae7e0 + (int)param_2),1);
      return CONCAT44(DAT_005ae344,iVar4);
    }
  }
  return 0;
}

