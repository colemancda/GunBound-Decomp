/* DrawHLine - 0x004eb5d0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall DrawHLine(undefined4 param_1,int param_2,int param_3)

{
  int in_EAX;
  int unaff_EDI;
  
  if (((g_screenSurface != 0) && (unaff_EDI <= g_clipMaxY)) && (g_clipMinY <= unaff_EDI)) {
    if (in_EAX < g_clipMinX) {
      param_2 = param_2 + (in_EAX - g_clipMinX);
      in_EAX = g_clipMinX;
    }
    if (g_clipMaxX < in_EAX + param_2) {
      param_2 = (g_clipMaxX - in_EAX) + 1;
    }
    if (0 < param_2) {
      FillPixels16(g_screenSurface + (g_screenPitch * unaff_EDI + in_EAX) * 2,param_3,param_2);
    }
  }
  return;
}

