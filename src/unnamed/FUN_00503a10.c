/* FUN_00503a10 - 0x00503a10 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * EAX and EDI RECOVERED (2026-08-25), both sites in FUN_00501770 under its
 * -0x4990 frame constant: EAX is &local_48f0 / &local_496c and EDI the value
 * at -0x4970 / iVar7 - 0x2c8.  The second site is pinned by the line above it,
 * `iVar7 = local_497c`, which is the very slot EBX is loaded from.
 */
#include "ghidra_types.h"


void FUN_00503a10(undefined4 regEax,undefined4 regEdi)

{
  char cVar1;
  int local_4;
  
  cVar1 = FUN_004fe860(regEdi,&local_4);
  if (cVar1 == '\0') {
    FUN_004fe8d0(regEax,0,0,0,0);
    cVar1 = FUN_004fe860(regEdi,&local_4);
    if (cVar1 != '\0') {
      *(undefined1 *)(local_4 + 0x1c) = 1;
    }
  }
  return;
}

