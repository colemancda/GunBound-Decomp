/* FUN_004eadb0 - 0x004eadb0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_004eadb0(int param_1)

{
  int in_EAX;
  int iVar1;
  int iVar2;
  int unaff_ESI;
  int unaff_EDI;
  
  iVar1 = param_1;
  if (in_EAX <= param_1) {
    iVar1 = in_EAX;
  }
  if (iVar1 < 0) {
    DAT_00793530 = 0;
LAB_004eadd7:
    iVar2 = param_1;
    iVar1 = DAT_00793530;
    if (param_1 <= in_EAX) goto LAB_004eaddd;
  }
  else {
    DAT_00793530 = in_EAX;
    iVar1 = param_1;
    if (in_EAX <= param_1) goto LAB_004eadd7;
LAB_004eaddd:
    DAT_00793530 = iVar1;
    iVar2 = in_EAX;
  }
  if (iVar2 < 800) {
    DAT_0056df30 = param_1;
    if (param_1 <= in_EAX) {
      DAT_0056df30 = in_EAX;
    }
  }
  else {
    DAT_0056df30 = 799;
  }
  iVar1 = unaff_EDI;
  if (unaff_ESI <= unaff_EDI) {
    iVar1 = unaff_ESI;
  }
  if (iVar1 < 0) {
    DAT_00793534 = 0;
LAB_004eae2a:
    iVar2 = unaff_EDI;
    iVar1 = DAT_00793534;
    if (unaff_ESI < unaff_EDI) goto LAB_004eae32;
  }
  else {
    DAT_00793534 = unaff_ESI;
    iVar1 = unaff_EDI;
    if (unaff_ESI <= unaff_EDI) goto LAB_004eae2a;
  }
  DAT_00793534 = iVar1;
  iVar2 = unaff_ESI;
LAB_004eae32:
  if (iVar2 < 600) {
    DAT_0056df34 = unaff_EDI;
    if (unaff_EDI <= unaff_ESI) {
      DAT_0056df34 = unaff_ESI;
    }
    return;
  }
  DAT_0056df34 = 599;
  return;
}

