/* ClearMuteList - 0x00425960 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * Sole caller is ParseChatSlashCommand's "loudall" arm (dispatched by an
 * exact stricmp against s_loudall_00553580, the literal string "loudall"
 * at 0x553580). It frees the whole mute array at g_clientContext+0x67ec60,
 * running the per-element destructor FUN_00405320 on each entry first,
 * zeroes the count/capacity fields, and shows localized string 0x200 -
 * the clear-confirmation message paired with AddMuteListEntry's 0x1fe add
 * message and RemoveMuteListEntry's 0x1ff removal message on the same
 * array.
 *
 * DROPPED REGISTER RECOVERED (2026-08-24): EBX is g_clientContext, arriving
 * as ParseChatSlashCommand's own param_1.  At the sole call site (0x00421f88)
 * EBX is loaded from a slot +4 above the caller's frame -- its first stack
 * parameter -- and the body reads it as an arena base (`[regEbx + 0x67ec60]`,
 * `+0x67ec70`), which is what the context looks like.  Found by
 * tools/above_frame_params.py.
 */
#include "ghidra_types.h"


void ClearMuteList(int regEbx)

{
  int iVar1;
  
  if (*(int *)(&DAT_0067ec60 + regEbx) != 0) {
    for (iVar1 = *(int *)(&DAT_0067ec64 + regEbx); iVar1 != 0; iVar1 = iVar1 + -1) {
      FUN_00405320();
    }
    _free(*(void **)(&DAT_0067ec60 + regEbx));
    *(undefined4 *)(&DAT_0067ec60 + regEbx) = 0;
  }
  *(undefined4 *)(&DAT_0067ec64 + regEbx) = 0;
  *(undefined4 *)(&DAT_0067ec68 + regEbx) = 0;
  GetLocalizedString(&g_localizedStringTable,0x200);
  FUN_00413af0((char *)GetLocalizedString(&g_localizedStringTable,0x200));
  return;
}

