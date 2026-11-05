/* Vector_Size_34 - 0x00404890 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_00404890 mean this function.)
 *
 * NAMED (2026-11-05), CERTAIN. Evidence from outside the body: std::vector
 * size(): _Myfirst == 0 ? 0 : (_Mylast - _Myfirst) / 0x34, _Myfirst at +4
 * and _Mylast at +8, the layout Vector_Size_12 and Vector_Size_1e already
 * use. Its caller Vector_InsertN_34 is the 0x34-stride _Insert_n. Suffix =
 * element size, as in the siblings.
 */
#include "ghidra_types.h"


int __fastcall Vector_Size_34(int param_1)

{
  if (*(int *)(param_1 + 4) == 0) {
    return 0;
  }
  return (*(int *)(param_1 + 8) - *(int *)(param_1 + 4)) / 0x34;
}

