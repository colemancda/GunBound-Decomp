/* DrawBlendedVLine - 0x004eb720 in the original binary.
 *
 * Draws a vertical run of additively-blended pixels - the blending twin of
 * DrawVLine, and the vertical member of the DrawHLine / DrawVLine /
 * DrawBlendedHLine set.
 *
 * Its clip logic matches DrawVLine's exactly, with the axis pairs transposed
 * relative to the horizontal versions (DAT_0056df30/DAT_00793530 bound the
 * column here, DAT_0056df34/DAT_00793534 the row).  Rather than emit one run,
 * it loops regEax rows, advancing by the stride DAT_005b3620 and blending a
 * single pixel per row through BlendPixels16.
 */
#include "ghidra_types.h"


void __fastcall DrawBlendedVLine(int param_1,int param_2,int param_3,int regEax)

{
  int iVar1;
  
  if (((DAT_0079352c != 0) && (param_2 <= DAT_0056df30)) && (DAT_00793530 <= param_2)) {
    if (param_1 < DAT_00793534) {
      regEax = regEax + (param_1 - DAT_00793534);
      param_1 = DAT_00793534;
    }
    if (DAT_0056df34 < param_1 + regEax) {
      regEax = (DAT_0056df34 - param_1) + 1;
    }
    if ((0 < regEax) && (iVar1 = DAT_0079352c + (DAT_005b3620 * param_1 + param_2) * 2, 0 < regEax))
    {
      do {
        BlendPixels16(iVar1,param_3,1);
        regEax = regEax + -1;
        iVar1 = iVar1 + DAT_005b3620 * 2;
      } while (regEax != 0);
    }
  }
  return;
}

