/* Vector_Tidy_8 - 0x00502a90 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED (2026-08-28): the destroy-everything member of the 8-byte
 * {CStringA, CStringA} vector family - sweep [begin, end) through the
 * element destructor CStringPair_Destroy (was FUN_00415890), _free the
 * buffer, null the base/end/cap trio at +4/+8/+0xc. That is, verbatim,
 * the member the VC7.1 <vector> calls _Tidy (the destructor's body),
 * and the library's own name is kept per the tree's convention of
 * preferring exact library member names. The stride-8 fields and the
 * shared pair destructor tie it to the family whose insert is
 * Vector_InsertN_8 (0x503130) and whose range-destroy is
 * Vector_DestroyRange_8 (0x503110).
 *
 * EBX RECOVERED (2026-08-25) from the single site in FUN_00501770, under the
 * -0x4990 frame constant that function's earlier recoveries established and
 * that four independent slots agree on: `lea ebx,[esp+0x38]` = &local_4958.
 */
#include "ghidra_types.h"


void Vector_Tidy_8(int regEbx)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *(int *)(regEbx + 4);
  if (iVar2 != 0) {
    iVar1 = *(int *)(regEbx + 8);
    for (; iVar2 != iVar1; iVar2 = iVar2 + 8) {
      /* DROPPED-REG FIX 2026-08-28: the sweep cursor, already in ESI. */
      CStringPair_Destroy(iVar2);
    }
    _free(*(void **)(regEbx + 4));
  }
  *(undefined4 *)(regEbx + 4) = 0;
  *(undefined4 *)(regEbx + 8) = 0;
  *(undefined4 *)(regEbx + 0xc) = 0;
  return;
}

