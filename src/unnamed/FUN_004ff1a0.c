/* FUN_004ff1a0 - 0x004ff1a0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * EDI RECOVERED (2026-08-25): the object whose last four dwords (+0x80..+0x8c)
 * this clears.  At 0x5014b4 it is `lea edi,[ebp+0x14]` = the source's
 * puVar2 + 0x14; at 0x4fe90f it is `lea edi,[esp+0x2c]`, frame -0x9c in a
 * caller whose frame is 0xc8 -- a 0x90-byte object that caller never declared.
 */
#include "ghidra_types.h"


void FUN_004ff1a0(int regEdi)

{
  
  FUN_004fe420(0xa,0x3f400000,0x3e800000,0x40100000,0x11);
  FUN_004fe420(0xa,0x3f400000,0x3e800000,0x40100000,0x11);
  *(undefined4 *)(regEdi + 0x80) = 0;
  *(undefined4 *)(regEdi + 0x84) = 0;
  *(undefined4 *)(regEdi + 0x88) = 0;
  *(undefined4 *)(regEdi + 0x8c) = 0;
  return;
}

