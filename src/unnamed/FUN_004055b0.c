/* FUN_004055b0 - 0x004055b0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-REG FIX (2026-08-28): assigns a counted string into a
 * CString-style HANDLE whose address arrives in EDI - strlen the
 * source, then AssignStringBuffer(handle, text, length), with the null
 * source short-circuited to an empty assignment. ECX is a PHANTOM (its
 * first touch is the write `mov cl,[eax]` in the strlen loop at
 * 0x4055d0); EDX is the declared param_2, the text. All three sites
 * pass the address of a handle variable: FUN_00501770's 0x1ffe arm
 * hands its two decode buffers to the two handles it seeded from the
 * (**(DAT_005b1444+0xc))() object, and FUN_00507660 hands a child
 * widget's +0x38 text to a handle in an 8-byte frame hole Ghidra left
 * undeclared - the same string whose -0xc length header the code after
 * the call reads back.
 */
#include "ghidra_types.h"


void __fastcall FUN_004055b0(undefined4 param_1,char *param_2,int regEdi)

{
  char cVar1;
  char *pcVar2;
  int unaff_EDI = regEdi;
  
  pcVar2 = param_2;
  if (param_2 != (char *)0x0) {
    do {
      cVar1 = *pcVar2;
      pcVar2 = pcVar2 + 1;
    } while (cVar1 != '\0');
    AssignStringBuffer(unaff_EDI,param_2);
    return;
  }
  AssignStringBuffer(unaff_EDI,0);
  return;
}

