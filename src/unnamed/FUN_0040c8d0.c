/* FUN_0040c8d0 - 0x0040c8d0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED REGISTER RECOVERED: EAX is DAT_007934e4, loaded at its sole call
 * site (0x004d6621).  The object it points at has an HWND at +4 and an enable
 * flag at +8, which is consistent with the SendMessageA below.
 */
#include "ghidra_types.h"


void __fastcall FUN_0040c8d0(undefined4 param_1,WPARAM param_2,LPARAM param_3,int regEax)

{
  
  if (*(char *)(regEax + 8) != '\0') {
    SendMessageA(*(HWND *)(regEax + 4),0xb1,param_2,param_3);
  }
  return;
}

