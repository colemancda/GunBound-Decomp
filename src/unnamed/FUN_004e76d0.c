/* FUN_004e76d0 - 0x004e76d0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_004e76d0(undefined4 param_1,int param_2,undefined4 *param_3)

{
  char cVar1;
  char *in_EAX;
  int iVar2;
  int unaff_ESI;
  
  *(undefined4 *)(unaff_ESI + 0x4520c) = param_1;
  *(undefined2 *)(unaff_ESI + 0x45210) = param_2;
  *(undefined4 *)(unaff_ESI + 0x45212) = *param_3;
  iVar2 = (unaff_ESI + 0x4521b) - (int)in_EAX;
  do {
    cVar1 = *in_EAX;
    in_EAX[iVar2] = cVar1;
    in_EAX = in_EAX + 1;
  } while (cVar1 != '\0');
  *(undefined4 *)(unaff_ESI + 0x45208) = 7;
  EnterCriticalSection((LPCRITICAL_SECTION)(unaff_ESI + 0x17c));
  FUN_004e72d0((undefined4 *)(unaff_ESI + 0x45212),4);
  LeaveCriticalSection((LPCRITICAL_SECTION)(unaff_ESI + 0x17c));
  return;
}

