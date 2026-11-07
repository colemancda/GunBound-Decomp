/* InitMpegIntensityStereoLSFTables - 0x0051a230 in the original binary.
 *
 * Fill the LSF intensity-stereo ratio table (0x5af944).
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified; see src/README.md's "Raw/verbatim ports"
 * section.
 *
 * Evidence for the name (all from outside the body):
 * Fetches its destination from GetMpegIntensityStereoLSFTable (0x5180f0,
 * the accessor for 0x5af944) and fills all 0x800 bytes: 2 intensity_scale
 * settings x 2 ratio sets x 64 (left, right) float pairs, using local
 * scales {1.0, sqrt(2)} and powers pow(2, -(n+1)*0.25) (constant at
 * 0x544af8, read from the binary), i.e. the ISO 13818-3 LSF intensity
 * ratios 2^-0.25 and 2^-0.5. The consumer ApplyMpegIntensityStereoLSF
 * indexes 0x5af944 in 8-byte pairs. Its only caller is
 * InitMpegLayerIIITables (0x519c5b), sitting between the MPEG-1 ratio
 * builder InitMpegIntensityStereoRatios and the window builder.
 */
#include "ghidra_types.h"


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void InitMpegIntensityStereoLSFTables(void)

{
  float *pfVar1;
  undefined4 *puVar2;
  float fVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  float10 fVar8;
  double dVar9;
  int iStack_38;
  int iStack_34;
  int iStack_30;
  int iStack_28;
  float local_18 [2];
  double dStack_10;
  
  local_18[0] = 1.0;
  fVar8 = (float10)FUN_00527f34(2.0);
  local_18[1] = (float)fVar8;
  iVar4 = GetMpegIntensityStereoLSFTable();
  iStack_38 = 0;
  iStack_30 = 0;
  do {
    dStack_10 = (double)(iStack_38 + 1);
    dStack_10 = _pow(2.0,dStack_10 * _DAT_00544af8);
    iVar6 = 0;
    do {
      iStack_34 = 1;
      iVar7 = 0;
      iStack_28 = 6;
      do {
        uVar5 = 0;
        if (iStack_34 != 1 && -1 < iStack_34 + -1) {
          do {
            if (uVar5 == 0) {
              fVar3 = local_18[iVar6];
              pfVar1 = (float *)(iVar4 + ((iVar6 + iStack_38 * 2) * 0x40 + iVar7) * 8);
              *pfVar1 = fVar3;
              pfVar1[1] = fVar3;
            }
            else if ((uVar5 & 1) == 0) {
              pfVar1 = (float *)(iVar4 + ((iVar6 + iStack_38 * 2) * 0x40 + iVar7) * 8);
              *pfVar1 = local_18[iVar6];
              dVar9 = _pow(dStack_10,(double)((int)uVar5 / 2));
              pfVar1[1] = (float)dVar9 * local_18[iVar6];
            }
            else {
              pfVar1 = (float *)(iVar4 + ((iVar6 + iStack_38 * 2) * 0x40 + iVar7) * 8);
              dVar9 = _pow(dStack_10,(double)((int)(uVar5 + 1) / 2));
              fVar3 = local_18[iVar6];
              *pfVar1 = (float)dVar9 * local_18[iVar6];
              pfVar1[1] = fVar3;
            }
            uVar5 = uVar5 + 1;
            iVar7 = iVar7 + 1;
          } while ((int)uVar5 < iStack_34 + -1);
        }
        if (iVar6 == 0) {
          puVar2 = (undefined4 *)(iVar4 + (iStack_30 + iVar7) * 8);
          *puVar2 = 0x3f800000;
          puVar2[1] = 0;
        }
        else {
          puVar2 = (undefined4 *)(iVar4 + ((iVar6 + iStack_38 * 2) * 0x40 + iVar7) * 8);
          *puVar2 = 0x3f800000;
          puVar2[1] = 0x3f800000;
        }
        iStack_34 = iStack_34 * 2;
        iVar7 = iVar7 + 1;
        iStack_28 = iStack_28 + -1;
      } while (iStack_28 != 0);
      iVar6 = iVar6 + 1;
    } while (iVar6 < 2);
    iStack_30 = iStack_30 + 0x80;
    iStack_38 = iStack_38 + 1;
  } while (iStack_30 < 0x100);
  return;
}

