/* FUN_004fcee0 - 0x004fcee0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * EAX RECOVERED (2026-08-25).  At 0x4fd802 the caller does `mov eax,ebx`
 * where EBX was loaded once at 0x4fd7d4, `mov ebx,[esp+0xc]` with two pushes
 * standing = E+4 = its param_2; the linear trace only reported `pop ebx`
 * because the call sits past a hoisted epilogue.  The second site passes the
 * same kind of value, its caller's param_4.
 */
#include "ghidra_types.h"


void FUN_004fcee0(char *regEax,int regEbx)

{
  /* One contiguous 0x24-byte frame payload (the callee copies 0x24 bytes from
   * EDX): a 0x10-char name, a NUL terminator at +0x10, rest scratch.  The raw
   * port split it into local_24[16]+local_14, not guaranteed adjacent -
   * merged.  EBX (the session) is dropped by this port; its two callers load
   * it (FUN_004fd7c0 param_1, DispatchP2PMessage param_3) - forwarded as
   * regEbx. */
  char local_24 [0x24];

  _strncpy(local_24,regEax,0x10);
  local_24[0x10] = 0;
  /* opcode -> stack param, ECX=0x24 len, EDX=&local_24 buf, EBX=session;
   * orig 0x4fcef3-0x4fcf06. */
  FUN_00502500(0x24,(undefined4 *)local_24,0x3000,regEbx);
  return;
}

