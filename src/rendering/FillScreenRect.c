/* FillScreenRect - 0x004eb800 in the original binary.
 *
 * Renamed from FillRect (its first assigned name) to FillScreenRect: it
 * collided with the real Win32 GDI FillRect(HDC, const RECT*, HBRUSH) that
 * <windows.h> already declares, breaking the whole build (C2373 redefinition)
 * for every file that includes both functions.h and windows.h.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FillScreenRect(int param_1,int param_2,int param_3,int param_4)

{
  int in_EAX;
  int iVar1;
  
  if (DAT_0079352c != 0) {
    if (param_2 < DAT_00793530) {
      param_3 = param_3 + (param_2 - DAT_00793530);
      param_2 = DAT_00793530;
    }
    if (DAT_0056df30 < param_2 + param_3) {
      param_3 = (DAT_0056df30 - param_2) + 1;
    }
    if (0 < param_3) {
      if (param_1 < DAT_00793534) {
        in_EAX = in_EAX + (param_1 - DAT_00793534);
        param_1 = DAT_00793534;
      }
      if (DAT_0056df34 < param_1 + in_EAX) {
        in_EAX = (DAT_0056df34 - param_1) + 1;
      }
      if ((0 < in_EAX) &&
         (iVar1 = DAT_0079352c + (DAT_005b3620 * param_1 + param_2) * 2, 0 < in_EAX)) {
        do {
          FillPixels16(iVar1,param_4,param_3);
          in_EAX = in_EAX + -1;
          iVar1 = iVar1 + DAT_005b3620 * 2;
        } while (in_EAX != 0);
      }
    }
  }
  return;
}

