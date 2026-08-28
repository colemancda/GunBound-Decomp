/* FUN_005045a0 - 0x005045a0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-REG FIX (2026-08-28): copies the 0x34-byte records in
 * [param_1, regEbx) to regEax and returns the destination end - the STL
 * _Ucopy shape, and the range twin of FUN_00504160's fill.
 *
 * ECX -> param_1  the SOURCE cursor (`mov esi,ecx` at 0x5045a1),
 *                 advanced by 0x34 and compared against EBX each pass.
 * EDX -> param_2  PHANTOM: written at 0x5045b4 (`mov edx,esi`) before
 *                 any read.
 * [esp+4]
 *     -> param_3  the same never-read stack word FUN_00504160 takes;
 *                 every caller pushes it and clears it afterwards.
 * EAX -> regEax   the DESTINATION cursor (`mov edi,eax` at 0x5045a6),
 *                 and the return value (`mov eax,edi` at 0x5045c7).
 * EBX -> regEbx   the source END. `lea ebx,[ebx]` at 0x5045aa is an
 *                 alignment NOP, not a write.
 *
 * The port had the roles inverted in its own naming: `in_EAX` reads like
 * the source but is the destination, and param_1 is the source start.
 */
#include "ghidra_types.h"


int __fastcall FUN_005045a0(int param_1,undefined4 param_2,undefined4 param_3,int regEax,
                            int regEbx)

{
  int in_EAX = regEax;
  int unaff_EBX = regEbx;
  
  for (; param_1 != unaff_EBX; param_1 = param_1 + 0x34) {
    if (in_EAX != 0) {
      FUN_00503680(0,(undefined4 *)param_1,(undefined4 *)in_EAX);
    }
    in_EAX = in_EAX + 0x34;
  }
  return in_EAX;
}

