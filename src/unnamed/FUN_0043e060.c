/* FUN_0043e060 - 0x0043e060 in the original binary.
 *
 * The id -> string lookup behind GetLocalizedString: a linear walk of the
 * table in EDX comparing each entry's first dword against the id in EDI.
 *
 * ABI FIX (2026-08-19).  param_1 is a PHANTOM - Ghidra marks the function
 * __fastcall but ECX is written at 0x43e060 (`mov ecx,[edx]`) before it is
 * ever read - so the real register arguments are EDX (param_2, the table) and
 * EDI (the id, which Ghidra modelled as `unaff_EDI`).  EDI is not expressible
 * under MSVC, so it has been promoted to a real trailing parameter (param_3),
 * the same trade documented for BlitSpriteAttached and InitTextBoxWidget.
 * Both call sites now pass 0 for the phantom and the id explicitly; before
 * this the id arrived as whatever happened to be in EDI, i.e. every localized
 * string lookup was searching for a garbage key.
 */
#include "ghidra_types.h"


int * __fastcall FUN_0043e060(undefined4 param_1,undefined4 *param_2,int param_3)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  int *piVar4;
  int *piVar5;
  
  piVar1 = (int *)param_2[5];
  piVar2 = (int *)0x0;
  piVar5 = (int *)*param_2;
  if ((int *)*param_2 != piVar1) {
    do {
      piVar3 = piVar5;
      if (piVar2 != (int *)0x0) goto LAB_0043e098;
      if (param_3 < *piVar3) {
        piVar5 = piVar3 + 3;
        piVar3 = piVar2;
        piVar5 = (int *)*piVar5;
      }
      else {
        piVar5 = piVar3;
        if (param_3 != *piVar3) {
          piVar5 = piVar3 + 4;
          piVar3 = piVar2;
          piVar5 = (int *)*piVar5;
        }
      }
      piVar2 = piVar3;
    } while (piVar5 != piVar1);
    if (piVar3 != (int *)0x0) {
LAB_0043e098:
      do {
        piVar5 = (int *)piVar2[3];
        if (piVar5 == piVar1) {
          piVar5 = (int *)piVar2[5];
          piVar3 = piVar2;
          if ((int *)piVar2[5] != piVar1) {
            do {
              piVar4 = piVar5;
              piVar5 = piVar4;
              if (piVar3 != (int *)piVar4[3]) break;
              piVar5 = (int *)piVar4[5];
              piVar3 = piVar4;
            } while (piVar5 != piVar1);
            if (piVar5 != piVar1) goto LAB_0043e0da;
          }
LAB_0043e0d8:
          piVar5 = (int *)0x0;
        }
        else {
          if (piVar5 == (int *)0x0) goto LAB_0043e0d8;
          for (piVar3 = (int *)piVar5[4]; piVar3 != piVar1; piVar3 = (int *)piVar3[4]) {
            piVar5 = piVar3;
          }
        }
LAB_0043e0da:
        if (piVar5 == (int *)0x0) {
          return piVar2;
        }
        if (param_3 != *piVar5) {
          return piVar2;
        }
        piVar2 = piVar5;
        if (piVar5 == (int *)0x0) {
          return (int *)0x0;
        }
      } while( true );
    }
  }
  return (int *)0x0;
}

