/* FUN_004fd960 - 0x004fd960 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 __thiscall FUN_004fd960(int param_1,char *param_2,char *param_3)

{
  undefined4 uVar1;
  /* One contiguous 0x28-byte frame payload: two 0x14 fields.  The raw port
   * split it into local_28[20]+local_14[20]; the callee copies 0x28 bytes
   * from EDX so they must be adjacent, which MSVC will not guarantee for
   * separate locals - merged. */
  char local_28 [0x28];

  if (*(char *)(param_1 + 0x1a70) == '\0') {
    return 0;
  }
  _strncpy(local_28,param_2,0x14);
  _strncpy(local_28 + 0x14,param_3,0x14);
  /* opcode -> stack param, ECX=0x28 len, EDX=&local_28 buf, EBX=this;
   * orig 0x4fd99e-0x4fd9ac. */
  uVar1 = FUN_00502500(0x28,(undefined4 *)local_28,0x3006,param_1);
  return uVar1;
}

