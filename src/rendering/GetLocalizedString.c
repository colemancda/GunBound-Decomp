/* GetLocalizedString - 0x0043dc70 in the original binary.
 *
 * Looks up a localized UI string by numeric id in g_localizedStringTable
 * (the id -> string map LoadLocalizedStrings built from graphics.xfs's
 * Language.txt) and returns a pointer to it. The read half of the
 * text-localization subsystem: every dialog/message string (error popups
 * via ShowErrorDialog, native MessageBoxA prompts) resolves through here.
 * DAT_005b1444 is the ATL allocator vtable used to marshal the returned
 * string object, not the string table itself. See ARCHITECTURE.md "Text
 * localization".
 *
 * Raw/near-verbatim port of Ghidra's decompiler output, not hand-verified.
 * See src/README.md's "Raw/verbatim ports" section for status.
 */
#include "ghidra_types.h"


undefined4 * GetLocalizedString(void)

{
  int *piVar1;
  undefined *puVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined4 uStack_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;
  
  uStack_4 = 0xffffffff;
  /* Windows SEH __try/__except frame setup stripped - handler body
   * (LAB_00537938) wasn't included in this function's own decompile.
   * Same rationale as entry/InitGame.c - see src/README.md. */
  (**(code **)(DAT_005b1444 + 0xc))();
  uStack_4 = 0;
  iVar4 = FUN_0043e060();
  puVar2 = PTR_DAT_0056d460;
  if (iVar4 != 0) {
    FUN_0043ddb0();
    uStack_4 = 0xffffffff;
    piVar1 = puVar3 + 3;
    LOCK();
    iVar4 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar4 == 1 || iVar4 + -1 < 0) {
      (**(code **)(*(int *)*puVar3 + 4))(puVar3);
    }
    return puVar3 + 4;
  }
  uStack_4 = 0xffffffff;
  piVar1 = puVar3 + 3;
  LOCK();
  iVar4 = *piVar1;
  *piVar1 = *piVar1 + -1;
  UNLOCK();
  if (iVar4 == 1 || iVar4 + -1 < 0) {
    (**(code **)(*(int *)*puVar3 + 4))(puVar3);
  }
  return (undefined4 *)puVar2;
}

