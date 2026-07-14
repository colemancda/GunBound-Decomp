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
 * DROPPED-ASSIGNMENT FIX (2026-07-14): `puVar3` (the CStringData header used
 * for the refcount-release logic in both branches) was read before ever
 * being assigned - Ghidra's decompile dropped the capture of the first
 * vtable call's own return value. Confirmed against the original
 * disassembly (0x43dc92-0x43dc95): `call [eax+0xc]; lea esi,[eax+0x10]` -
 * the call's EAX return (the nil-string CStringData header) is what `esi`
 * (and therefore this file's puVar3, computed as esi-0x10 at 0x43dccd/
 * 0x43dd02) derives from. The FOUND branch's fuller original logic (esi
 * reloaded from a stack slot FUN_0043ddb0 can overwrite with a real found
 * entry, 0x43dcb8-0x43dcc9) isn't reconstructed here - FUN_0043ddb0 has its
 * own dropped-args gap and this branch is unreached in bring-up (the string
 * table is always empty, LoadLocalizedStrings is dropped - see
 * bringup_drop.txt), but puVar3 is at least captured so it no longer reads
 * garbage there either.
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
  puVar3 = (undefined4 *)(**(code **)(DAT_005b1444 + 0xc))();
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

