/* FUN_00401c10 - 0x00401c10 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-REG FIX (2026-08-28): EDI is the ordinal being looked up. The
 * body walks the bucket ring at regEax+4 (next at +0x1c) and, inside
 * each bucket, the node chain at +0x10, counting only nodes whose +0x15
 * flag is clear; it returns the node whose running count equals EDI.
 * EDI is read at 0x401c30 (`cmp ecx,edi`) and written nowhere - the
 * `mov edi,edi` at 0x401c1e is MSVC's two-byte hot-patch pad, not a
 * write.
 *
 * Only one of the three binary sites has a ported caller. At 0x505d7f
 * FUN_00505d20 loads it with `mov edi,[esi+0x90]` at 0x505d6f, esi being
 * its own `this` - which is the very field the source's surrounding
 * guard already tests, `*(int *)(param_1 + 0x90) != -1`. So the ordinal
 * is that widget's selected row, and the caller uses the returned node's
 * +0x21 as a string.
 */
#include "ghidra_types.h"


int FUN_00401c10(int regEax,int regEdi)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int unaff_EDI = regEdi;
  
  iVar2 = *(int *)(*(int *)(regEax + 4) + 0x1c);
  iVar4 = 0;
  do {
    if (iVar2 == *(int *)(regEax + 4)) {
      return 0;
    }
    iVar3 = *(int *)(iVar2 + 0x10);
    cVar1 = *(char *)(iVar3 + 0x15);
    while (cVar1 == '\0') {
      if (iVar4 == unaff_EDI) {
        return iVar3;
      }
      iVar3 = *(int *)(iVar3 + 0x10);
      iVar4 = iVar4 + 1;
      cVar1 = *(char *)(iVar3 + 0x15);
    }
    iVar2 = *(int *)(iVar2 + 0x1c);
  } while( true );
}

