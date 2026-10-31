/* AtlArray_AppendCString - 0x00415bc0 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (FUN_00425840, mentioned in a note below, is now AddMuteListEntry.)
 * (FUN_00509780 below is now BuildAvatarShopIpConfirmDialog.)
 *
 * RENAMED (2026-10-26): this is a single shared/generic ATL-array-append
 * template instantiation - grows the array via AtlArray_GrowBuffer if
 * needed, then calls ConstructStringFromText to construct one CStringT-
 * style element and returns its index - used by THREE unrelated callers/
 * containers (LoadFourWordList.c's word-filter array, AddMuteListEntry.c's
 * chat mute list, and State11_InBattle_ProcessBattleAction.c's own,
 * separate array), not word-filter-specific. The old name
 * AppendWordFilterEntry was only accurate for the first of those three;
 * see AtlArray_RemoveAt_CString.c's own header for the full three-caller
 * E8-scan evidence that establishes this is a shared template member, the
 * same reasoning that already named this file's RemoveAt counterpart.
 * (AppendWordFilterEntry is now AtlArray_AppendCString.)
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
 * text pointer is reloaded right before the `ConstructStringFromText` call as that
 * callee's own first argument (source text to construct the new element
 * from). `this` was previously taken as this function's own `param_1`
 * (a bug this file's own earlier fix pass introduced by assuming the
 * caller's line-buffer WAS the array header) - actually two distinct
 * objects. Also wires the `ConstructStringFromText` call, which this file always
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


uint __fastcall AtlArray_AppendCString(int *thisArray,char *lineText)

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
    ConstructStringFromText(lineText, iVar1);
  }
  thisArray[1] = thisArray[1] + 1;
  return uVar2;
}
