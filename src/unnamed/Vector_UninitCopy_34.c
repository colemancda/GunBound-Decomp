/* Vector_UninitCopy_34 - 0x005045a0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * DROPPED-REG FIX (2026-08-28): copies the 0x34-byte records in
 * [param_1, regEbx) to regEax and returns the destination end - the STL
 * _Ucopy shape, and the range twin of Vector_UninitFillN_34's fill.
 *
 * ECX -> param_1  the SOURCE cursor (`mov esi,ecx` at 0x5045a1),
 *                 advanced by 0x34 and compared against EBX each pass.
 * EDX -> param_2  PHANTOM: written at 0x5045b4 (`mov edx,esi`) before
 *                 any read.
 * [esp+4]
 *     -> param_3  the same never-read stack word Vector_UninitFillN_34 takes;
 *                 every caller pushes it and clears it afterwards.
 * EAX -> regEax   the DESTINATION cursor (`mov edi,eax` at 0x5045a6),
 *                 and the return value (`mov eax,edi` at 0x5045c7).
 * EBX -> regEbx   the source END. `lea ebx,[ebx]` at 0x5045aa is an
 *                 alignment NOP, not a write.
 *
 * The port had the roles inverted in its own naming: `in_EAX` reads like
 * the source but is the destination, and param_1 is the source start.
 *
 * NAMED (2026-08-28): VC7.1 <memory>'s
 * `_Uninit_copy(_First, _Last, _Dest, _Al)` for the 0x34-byte element -
 * `for (; _First != _Last; ++_Dest, ++_First) _Al.construct(_Dest,
 * *_First); return _Dest;` - which is exactly this loop, with
 * Vector_CopyElement_34 as the construct. The never-read stack word is
 * that `_Al&`: an empty allocator object still occupies an argument
 * slot, which is why every caller pushes it and then discards it with
 * `add esp,4`.
 *
 * Its three callers are all inside Vector_InsertN_34's reallocate and
 * shift-up paths, and the first of them feeds its returned destination
 * end straight into Vector_UninitFillN_34 - the caller-side use that
 * fixes the return value as _Dest and not, say, a count.
 *
 * Named Vector_UninitCopy_34 rather than reusing the existing
 * Vector_CopyBackward_34/Vector_FillN_34 vocabulary because the contrast
 * is real: those two ASSIGN over live elements with a flat 0xd-dword
 * copy, while this one CONSTRUCTS into raw storage through the element's
 * copy constructor. Same 0x34 stride, different half of the insert.
 */
#include "ghidra_types.h"


int __fastcall Vector_UninitCopy_34(int param_1,undefined4 param_2,undefined4 param_3,int regEax,
                            int regEbx)

{
  int in_EAX = regEax;
  int unaff_EBX = regEbx;
  
  for (; param_1 != unaff_EBX; param_1 = param_1 + 0x34) {
    if (in_EAX != 0) {
      Vector_CopyElement_34(0,(undefined4 *)param_1,(undefined4 *)in_EAX);
    }
    in_EAX = in_EAX + 0x34;
  }
  return in_EAX;
}

