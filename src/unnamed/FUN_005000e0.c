/* FUN_005000e0 - 0x005000e0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * ESI RECOVERED (2026-08-24): it is callerThis + 0x290, FUN_004fe8d0's
 * __thiscall param_1 plus a fixed offset (`lea esi,[ebx+0x290]`, EBX never
 * written after the caller's entry).
 *
 * EDI RECOVERED (2026-08-25): `lea edi,[esp+0x1a]` at 0x4fe941, no push
 * pending; the caller's frame is 0xc8 (SEH 12 + sub esp,0xac + four saves),
 * so 0x1a - 0xc8 = -0xae: the ADDRESS of its `char local_ae [17]`, which the
 * next instruction NUL-terminates (`mov [esp+ecx+0x1a],0`).  It is the name
 * buffer FUN_00500ef0 parses, so the type is char *, not undefined4.
 */
#include "ghidra_types.h"


void FUN_005000e0(int *regEsi,char *regEdi)

{
  char cVar1;
  int iVar2;
  undefined4 local_c;
  undefined4 local_8;
  undefined1 local_4 [4];
  
  iVar2 = FUN_00500ef0(regEdi,(uint *)&local_c,(undefined4 *)local_4,regEsi,(uint *)&local_8);
  if (iVar2 == 0) {
    if (*regEsi == 0) {
      cVar1 = FUN_00500c00(regEsi,regEsi[2],1);
      if (cVar1 == '\0') {
                    /* WARNING: Subroutine does not return */
        ThrowCxxException(0x8007000e);
      }
    }
    FUN_00501420(local_8,local_c,(undefined4 *)regEdi,regEsi);
  }
  return;
}

