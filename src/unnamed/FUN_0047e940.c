/* FUN_0047e940 - 0x0047e940 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_0047e940(undefined4 param_1)

{
  undefined4 *in_EAX;
  
  in_EAX[2] = param_1;
  in_EAX[1] = 190000;
  in_EAX[3] = 0;
  in_EAX[4] = 0;
  *(undefined1 *)(in_EAX + 5) = 0;
  *(undefined1 *)((int)in_EAX + 0x15) = 0;
  in_EAX[6] = 0xffffffff;
  in_EAX[7] = 0;
  *(undefined1 *)(in_EAX + 8) = 0;
  in_EAX[10] = 0;
  in_EAX[0xb] = 0;
  in_EAX[9] = 0xffffffff;
  *in_EAX = &PTR_FUN_005560bc;
  in_EAX[0x10] = 0;
  in_EAX[0x12] = 0x10;
  in_EAX[0x13] = 0x80;
  in_EAX[0x11] = 0;
  return;
}

