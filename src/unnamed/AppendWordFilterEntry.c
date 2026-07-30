/* AppendWordFilterEntry - 0x00415bc0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * SEH-PROLOGUE ARTIFACT FIX (2026-07-30): same class as
 * WidgetChildArray_Destroy.c/FUN_00443c20.c/FUN_00509780.c -
 * `unaff_FS_OFFSET` was an uninitialised pointer the body wrote through
 * (`*unaff_FS_OFFSET = &local_c;`) on EVERY call, corrupting whatever
 * garbage address it happened to hold. Stripped per that idiom (no
 * __try/__except frames, no write-only `local_4` unwind marker).
 *
 * DROPPED `this`/2ND-ARG FIX (2026-07-30): Ghidra's decompile lost BOTH of
 * this function's real arguments - it took no parameters and read a
 * dropped `unaff_ESI`. Confirmed via objdump (LoadFourWordList's call site,
 * orig 0x415ad9-0x415ae8): `mov ecx,0xe9c9dc` sets the real thiscall
 * `this` to the word-filter AtlArray header (see globals_sized.c's
 * g_wordFilterArrayHeader), and a `push ecx` just before that (while ecx
 * still held `&acStack_10f50`, the caller's just-parsed line buffer)
 * supplies a second, stack-passed argument - the text to append. Body
 * confirms both: `[esi+4]`/`[esi+8]` are the array's count/capacity
 * (matching AtlArray_GrowBuffer's `this[1]`/`this[2]`), and the saved
 * text pointer is reloaded right before the `FUN_00405510` call as that
 * callee's own first argument (source text to construct the new element
 * from). `this` was previously taken as this function's own `param_1`
 * (a bug this file's own earlier fix pass introduced by assuming the
 * caller's line-buffer WAS the array header) - actually two distinct
 * objects. Also wires the `FUN_00405510` call, which this file always
 * called with only 1 of its real 2 args.
 *
 * functions.h stays K&R-empty (incremental-migration idiom, same as
 * AtlArray_GrowBuffer.c) - LoadFourWordList.c's call site (the only one this
 * fix touches) is correct now, but two other real callers still pass only
 * 1 arg and haven't been traced: FUN_00425840.c (a chat word-filter
 * function, plausibly the SAME g_wordFilterArrayHeader, but that
 * function's OWN `unaff_ESI` argument is separately dropped from ITS
 * caller and untraced) and State11_InBattle_ProcessBattleAction.c (deep in
 * an unrelated ~500-line battle-action handler, almost certainly a
 * different array entirely - same class of deferred trace as
 * AtlArray_GrowBuffer.c's own State11_InBattle_OnTick.c gap). Giving this
 * function a real prototype would break both of those callers' compiles
 * for no benefit on the current crash path - left for a future pass.
 */
#include "ghidra_types.h"


uint __fastcall AppendWordFilterEntry(int *thisArray,char *lineText)

{
  int iVar1;
  uint uVar2;
  char cVar3;

  uVar2 = thisArray[1];
  if ((uint)thisArray[2] <= uVar2) {
    cVar3 = AtlArray_GrowBuffer(thisArray, thisArray[1] + 1);
    if (cVar3 == '\0') {
                    /* WARNING: Subroutine does not return */
      ThrowCxxException(0x8007000e);
    }
  }
  iVar1 = *thisArray + uVar2 * 4;
  if (iVar1 != 0) {
    FUN_00405510(lineText, iVar1);
  }
  thisArray[1] = thisArray[1] + 1;
  return uVar2;
}
