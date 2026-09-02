/* FUN_004fd9c0 - 0x004fd9c0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

undefined4 __thiscall
FUN_004fd9c0(int param_1,char *param_2,char *param_3,undefined2 param_4,undefined2 param_5)

{
  undefined4 uVar1;
  /* One contiguous 0x18-byte frame payload: 0xc + 8 + 2 + 2.  The raw port
   * split it into four separate locals; the callee copies 0x18 bytes from
   * EDX so they must be adjacent (not guaranteed for separate MSVC locals) -
   * merged. */
  char frame [0x18];
  undefined4 uStack_4;

  uStack_4 = 0x4fd9ca;
  if (*(char *)(param_1 + 0x1a70) == '\0') {
    return 0x1700;
  }
  _strncpy(frame,param_2,0xc);
  _strncpy(frame + 0xc,param_3,8);
  *(undefined2 *)(frame + 0x14) = param_4;
  *(undefined2 *)(frame + 0x16) = param_5;
  /* opcode -> stack param, ECX=0x18 len, EDX=&frame buf, EBX=this;
   * orig 0x4fda28-0x4fda36. */
  uVar1 = FUN_00502500(0x18,(undefined4 *)frame,0x4000,param_1);
  return uVar1;
}

