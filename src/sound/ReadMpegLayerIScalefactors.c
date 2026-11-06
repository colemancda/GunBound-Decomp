/* ReadMpegLayerIScalefactors - 0x00513850 in the original binary.
 *
 * Read the Layer I scalefactor indices: one 6-bit index per subband with
 * nonzero allocation.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified; see src/README.md's "Raw/verbatim ports"
 * section.
 *
 * Evidence for the name (all from outside the body):
 * LIKELY. Called at 0x513808 by the Layer I frame decoder at 0x5133c0
 * (slot 3 of the 0x563aec table; Layer I per header field +8 == 3 as in
 * SetupMpegLayerIDecoder). ISO 11172-3 Layer I frame order is allocation,
 * scalefactors, samples, and this runs between the two; it reads 6 bits
 * per nonzero-allocation subband (DAT_00563b44 bands) and multiplies the
 * 6-bit table entry (0x5a9888) by the per-band step.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void ReadMpegLayerIScalefactors(void)

{
  int iVar1;
  
  iVar1 = 0;
  if (0 < DAT_00563b44) {
    do {
      if ((&DAT_005ab604)[iVar1] != 0) {
        if (DAT_005ab704 < 6) {
          for (; DAT_005ab704 < 0x19; DAT_005ab704 = DAT_005ab704 + 8) {
            DAT_005ab4f4 = DAT_005ab4f4 << 8 | (uint)*DAT_005a9680;
            DAT_005a9680 = DAT_005a9680 + 1;
          }
        }
        DAT_005ab704 = DAT_005ab704 + -6;
        _DAT_005ab888 = DAT_005ab4f4 >> ((byte)DAT_005ab704 & 0x1f);
        DAT_005ab4f4 = DAT_005ab4f4 - (_DAT_005ab888 << ((byte)DAT_005ab704 & 0x1f));
        *(float *)(PTR_DAT_00563b40 + iVar1 * 4) =
             (float)(&DAT_005a9888)[_DAT_005ab888] * (float)(&DAT_005a9684)[iVar1];
      }
      iVar1 = iVar1 + 1;
    } while (iVar1 < DAT_00563b44);
  }
  return;
}

