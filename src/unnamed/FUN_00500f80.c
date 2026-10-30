/* FUN_00500f80 - 0x00500f80 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * EAX RECOVERED (2026-10-30): the whole body is `add eax,0x14; jmp
 * 0x4ff210` - EAX is a 0xac map node and DestroyP2PPeerRecord gets
 * its value slot at node+0x14 in EAX.  Was argless.
 */
#include "ghidra_types.h"


void FUN_00500f80(int regEax)

{
  DestroyP2PPeerRecord(regEax + 0x14);
  return;
}

