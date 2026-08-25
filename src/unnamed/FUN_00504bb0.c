/* FUN_00504bb0 - 0x00504bb0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * STACK PARAMETER RESTORED (2026-08-25): `ret 4` says one stack argument and
 * Ghidra declared none, leaving the raw `stack0x00000004` artifact where the
 * find's param_3 should be.  [esp+0x30] at 0x504be5 (four pushes pending over
 * `sub esp,0x1c`) is that argument, and the object whose map lives at +0x290.
 * Its one call site, 0x504811, is inside a function that has not been carved,
 * so no source caller needs updating.
 */
#include "ghidra_types.h"


bool FUN_00504bb0(int param_1)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  int unaff_ESI;
  undefined1 local_1c [10];
  char local_12 [17];
  byte local_1;
  
  uVar2 = 0;
  do {
    bVar1 = (byte)uVar2;
    if (*(char *)(uVar2 + unaff_ESI) == '\0') break;
    bVar1 = bVar1 + 1;
    local_12[uVar2] = *(char *)(uVar2 + unaff_ESI);
    uVar2 = (uint)bVar1;
  } while (bVar1 < 0x10);
  local_1 = bVar1;
  local_12[bVar1] = '\0';
  iVar3 = FUN_00500ef0(local_12,(uint *)local_1c,(undefined4 *)&param_1,(int *)(param_1 + 0x290),
                       (uint *)(local_1c + 4));
  return iVar3 != 0;
}

