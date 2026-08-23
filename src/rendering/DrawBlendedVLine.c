/* DrawBlendedVLine - 0x004eb720 in the original binary.
 *
 * Draws a vertical run of additively-blended pixels - the blending twin of
 * DrawVLine, and the vertical member of the DrawHLine / DrawVLine /
 * DrawBlendedHLine set.
 *
 * Its clip logic matches DrawVLine's exactly, with the axis pairs transposed
 * relative to the horizontal versions (g_clipMaxX/g_clipMinX bound the
 * column here, g_clipMaxY/g_clipMinY the row).  Rather than emit one run,
 * it loops regEax rows, advancing by the stride g_screenPitch and blending a
 * single pixel per row through BlendPixels16.
 */
#include "ghidra_types.h"


void __fastcall DrawBlendedVLine(int param_1,int param_2,int param_3,int regEax)

{
  int iVar1;
  
  if (((g_screenSurface != 0) && (param_2 <= g_clipMaxX)) && (g_clipMinX <= param_2)) {
    if (param_1 < g_clipMinY) {
      regEax = regEax + (param_1 - g_clipMinY);
      param_1 = g_clipMinY;
    }
    if (g_clipMaxY < param_1 + regEax) {
      regEax = (g_clipMaxY - param_1) + 1;
    }
    if ((0 < regEax) && (iVar1 = g_screenSurface + (g_screenPitch * param_1 + param_2) * 2, 0 < regEax))
    {
      do {
        BlendPixels16(iVar1,param_3,1);
        regEax = regEax + -1;
        iVar1 = iVar1 + g_screenPitch * 2;
      } while (regEax != 0);
    }
  }
  return;
}

