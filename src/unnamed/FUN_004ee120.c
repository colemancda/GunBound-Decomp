/* FUN_004ee120 - 0x004ee120 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_004ee120(void)

{
  undefined4 *in_EAX;
  
  in_EAX[2] = DAT_00557328;
  in_EAX[3] = DAT_0055732c;
  in_EAX[4] = DAT_00557330;
  in_EAX[5] = DAT_00557334;
  in_EAX[1] = 0;
  *(undefined1 *)((int)in_EAX + 0x4b) = 0;
  *(undefined1 *)((int)in_EAX + 0x4a) = 0;
  *(undefined1 *)((int)in_EAX + 0x49) = 0;
  *(undefined1 *)(in_EAX + 0x12) = 0;
  in_EAX[0x13] = 0;
  in_EAX[0x14] = 10;
  *(undefined1 *)(in_EAX + 0x15) = 0;
  *in_EAX = &PTR_FUN_00557484;
  in_EAX[0x165] = 0;
  in_EAX[0x163] = 0;
  in_EAX[0x164] = 799;
  in_EAX[0x166] = 599;
  in_EAX[0x167] = 400;
  in_EAX[0x168] = 300;
  *(undefined1 *)(in_EAX + 0x169) = 1;
  in_EAX[0x1a] = 0;
  in_EAX[0x1b] = 0;
  in_EAX[0x1c] = 0;
  in_EAX[0x1d] = 0;
  in_EAX[0x1e] = 0;
  in_EAX[0x1f] = 0;
  in_EAX[0x20] = 0;
  in_EAX[0x21] = 0;
  return;
}

