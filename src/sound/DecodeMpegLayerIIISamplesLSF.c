/* DecodeMpegLayerIIISamplesLSF - 0x005159d0 in the original binary.
 *
 * Layer III frame decoder for the MPEG-2 / 2.5 (low sampling frequency)
 * streams: one granule per frame. Sibling of DecodeMpegLayerIIISamples
 * (0x514fc0, the two-granule MPEG-1 decoder).
 *
 * Evidence for the name (all from outside the body):
 * SetupMpegLayerIIIDecoder ends with PTR_FUN_00563da8 =
 * DecodeMpegLayerIIISamples, then replaces it with this routine when the
 * stream header's ID field (+4) is not 1. Ghidra never carved it (the
 * original code was installed as a bare address, LAB_005159d0), so it had
 * no PROGRESS row; the 0x514fa0 trampoline of the 0x563aec table reaches it
 * through [0x563da8]. Like its sibling it reads a 12-bit sync (0xfff, or
 * 0xffe which also sets DAT_005aba34 = 1, the MPEG-2.5 flag), then lets
 * FUN_00515b90 parse the rest of the header and the side information (that
 * routine is passed DAT_005ae938 and returns the number of bytes it
 * consumed), manages the bit reservoir with the same 0x1a24 / 0x2000
 * bounds and calls DecodeMpegLayerIIIGranule(buf, DAT_005ae938) once.
 * DAT_005ae938 (a dword between DAT_005ae934 and DAT_005ae93c, never written
 * outside this routine) is the granule parity: it is toggled with xor 1 on
 * every successful frame, which selects the overlap row (granule ^ 1)
 * in the Layer III channel synthesis drivers.
 *
 * Result is EDX:EAX = (DAT_005ae344 output bytes, DAT_005ae350 frame
 * bytes), or 0 on a bad sync or an out-of-range reservoir copy. When the
 * reservoir cannot yet supply main_data_begin bytes (DAT_005ae930 < 0) the
 * output is filled with the silence byte DAT_005ae92c instead of decoding.
 */
#include "ghidra_types.h"


undefined8 DecodeMpegLayerIIISamplesLSF(byte *param_1,undefined4 *param_2)

{
  undefined1 uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  undefined2 uVar10;
  
  DAT_00f25ed0 = DAT_00f25ed0 + 1;
  iVar4 = 0;
  uVar7 = 0;
  DAT_00f25e08 = param_1;
  DAT_00f25e0c = param_1;
  DAT_00f25e04 = 0;
  DAT_00f25e00 = 0;
  do {
    iVar4 = iVar4 + 8;
    DAT_00f25e04 = iVar4;
    uVar7 = uVar7 << 8 | (uint)*DAT_00f25e08;
    DAT_00f25e08 = DAT_00f25e08 + 1;
    DAT_00f25e00 = uVar7;
  } while (iVar4 < 0x19);
  iVar4 = iVar4 + -0xc;
  uVar6 = uVar7 >> ((byte)iVar4 & 0x1f);
  DAT_00f25e04 = iVar4;
  DAT_005aba34 = 0;
  DAT_00f25e00 = uVar7 - (uVar6 << ((byte)iVar4 & 0x1f));
  if (uVar6 != 0xfff) {
    DAT_005aba34 = 1;
    if (uVar6 != 0xffe) {
      return 0;
    }
  }
  iVar9 = FUN_00515b90(DAT_005ae938);
  iVar4 = DAT_005ae33c + DAT_005aba30;
  uVar7 = DAT_005ae934;
  DAT_005ae350 = iVar4;
  DAT_005ae930 = DAT_005ae934 - DAT_005ae7f0;
  if (0x1a24 < (int)DAT_005ae934) {
    _memmove(&DAT_005aba38,&DAT_005aba38 + DAT_005ae930,DAT_005ae7f0); /* byte offsets: DAT_005aba38 is the byte reservoir */
    uVar7 = DAT_005ae7f0;
    iVar4 = DAT_005ae350;
    DAT_005ae930 = 0;
    DAT_005ae934 = uVar7;
  }
  iVar5 = (iVar4 - DAT_005ada38) - iVar9;
  if ((iVar5 < 0) || (0x2000 < iVar5)) {
    return 0;
  }
  _memmove(&DAT_005aba38 + uVar7,param_1 + DAT_005ada38 + iVar9,iVar5);
  DAT_005ae934 = DAT_005ae934 + iVar5;
  if ((int)DAT_005ae930 < 0) {
    uVar1 = (undefined1)DAT_005ae92c;
    uVar10 = CONCAT11(uVar1,uVar1);
    uVar2 = DAT_005ae344;
    for (uVar3 = DAT_005ae344 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
      *param_2 = CONCAT22(uVar10,uVar10);
      param_2 = param_2 + 1;
    }
    for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
      *(undefined1 *)param_2 = uVar1;
      param_2 = (undefined4 *)((int)param_2 + 1);
    }
  }
  else {
    DAT_005ae920 = DAT_005ae930 * 8;
    DecodeMpegLayerIIIGranule(param_2,DAT_005ae938);
  }
  uVar8 = DAT_005ae344;
  DAT_005ae938 = DAT_005ae938 ^ 1;
  return CONCAT44(uVar8,iVar4);
}
