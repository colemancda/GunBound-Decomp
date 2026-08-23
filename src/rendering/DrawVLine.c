/* DrawVLine - 0x004eb6b0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall DrawVLine(int param_1)

{
  int in_EAX;
  undefined2 *puVar1;
  undefined2 unaff_BX;
  int unaff_EDI;
  
  if (((g_screenSurface != 0) && (unaff_EDI <= g_clipMaxX)) && (g_clipMinX <= unaff_EDI)) {
    if (in_EAX < g_clipMinY) {
      param_1 = param_1 + (in_EAX - g_clipMinY);
      in_EAX = g_clipMinY;
    }
    if (g_clipMaxY < in_EAX + param_1) {
      param_1 = (g_clipMaxY - in_EAX) + 1;
    }
    if ((0 < param_1) &&
       (puVar1 = (undefined2 *)(g_screenSurface + (g_screenPitch * in_EAX + unaff_EDI) * 2), 0 < param_1
       )) {
      do {
        param_1 = param_1 + -1;
        *puVar1 = unaff_BX;
        puVar1 = puVar1 + g_screenPitch;
      } while (param_1 != 0);
    }
  }
  return;
}

