/* FindActiveObjectByIndex - 0x00401c10 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
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
 *
 * NAMED (2026-08-28): this is an enumeration of an active-object
 * registry by ordinal, returning the EDI'th registered object across all
 * of the registry's layers, or 0 when there are fewer than that many.
 * Everything the name claims comes from the already-documented shape of
 * the container rather than from this loop:
 *
 *   src/cxx/ActiveObjects.h pins the layout that the walk below uses.
 *   The registry's +4 is the outer-list sentinel, layers are threaded
 *   through +0x18/+0x1c, each layer's objects hang off +0x10, and the
 *   layer node itself carries flag15 = 1 at +0x15 where a plain
 *   ActiveObjectNode is only 0x14 bytes long and has no such field.
 *
 *   So the `while (*(node + 0x15) == 0)` here is not a filter on some
 *   per-object property - it is the inner circular list's TERMINATOR,
 *   the point at which the walk comes back round to the layer it started
 *   from. Every registered object is counted; none is skipped. That is
 *   also why RegisterActiveObject and SweepActiveObjectRegistry, which
 *   walk the same two rings, need no equivalent test: they stop on the
 *   0xffffffff sentinel id instead.
 *
 * The one ported caller agrees: FUN_00505d20 passes the widget's
 * selected-row field at this+0x90 - guarded against -1 on the line above
 * - and then reads the returned node's +0x21 as a string. An ordinal in,
 * the row's object out.
 *
 * Named FindActiveObjectByIndex to sit beside FindActiveObjectAt
 * (0x40cea0), the hit-test that resolves a point to the same kind of
 * object out of the same kind of registry. The registry here is
 * DAT_00e53e88, one of the four objects that
 * ActiveObjectRegistry_BaseConstructor's header lists as instances of
 * this container.
 */
#include "ghidra_types.h"


int FindActiveObjectByIndex(int regEax,int regEdi)

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

