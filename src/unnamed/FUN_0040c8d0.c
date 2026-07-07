/* FUN_0040c8d0 - 0x0040c8d0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_0040c8d0(undefined4 param_1,WPARAM param_2,LPARAM param_3)

{
  int in_EAX;
  
  if (*(char *)(in_EAX + 8) != '\0') {
    SendMessageA(*(HWND *)(in_EAX + 4),0xb1,param_2,param_3);
  }
  return;
}

