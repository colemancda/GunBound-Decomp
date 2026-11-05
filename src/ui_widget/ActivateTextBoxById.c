/* ActivateTextBoxById - 0x0040cf80 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_0040cf80 mean this function.)
 *
 * NAMED (2026-11-05), HIGH. Evidence from outside the body: Walks registry
 * param_3's layer list for the layer key param_2 and then that layer's
 * object ring for the id in ESI (both are ordered unsigned-key walks that
 * stop early once the key is passed, so a miss changes nothing); on a hit
 * it commits the outgoing focused box with CommitActiveTextInput, stores
 * the new box at registry + 8 (the same focus slot
 * NavigateTextBoxFocusOnKey cycles) and starts editing with
 * TextBoxWidget_BeginEdit. Both binary callers are in
 * State07_AvatarStore_OnCommand and pass registry 0xe9c0fc
 * (g_activeObjectRegistry2), layer 0x2710 and id 0, i.e. focus the box
 * with that fixed key.
 *
 * ARGUMENTS RE-SLOTTED AND ESI RECOVERED.  `ret 4` gives one stack argument,
 * so param_1 is ECX, param_2 is EDX and param_3 is the push.  ECX is a
 * PHANTOM (the entry writes it before any read), so it takes 0.  Both call
 * sites agree: push 0xe9c0fc -> param_3, edx = 0x2710 -> param_2, esi = 0.
 *
 * The port passed &g_activeObjectRegistry2 as param_1 -- the right value in the wrong
 * slot.  param_3 is the registry the tree walk starts from
 * (*(param_3 + 4) + 0x1c), which is what confirms the placement rather than
 * merely permitting it.
 *
 * CommitActiveTextInput EDI RECOVERED (2026-10-30): 0x40cfbf
 * `mov edi,[ebp+8]` (ebp = param_3, loaded at 0x40cf81) then
 * `test edi,edi; je; call 0x40ccf0` - EDI is the outgoing focused text box
 * *(param_3 + 8). The port passed nothing.
 */
#include "ghidra_types.h"


void __fastcall ActivateTextBoxById(undefined4 param_1,uint param_2,int param_3,uint regEsi)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = *(int *)(*(int *)(param_3 + 4) + 0x1c);
  uVar1 = *(uint *)(iVar2 + 4);
  if (uVar1 <= param_2) {
    while (uVar1 != param_2) {
      iVar2 = *(int *)(iVar2 + 0x1c);
      uVar1 = *(uint *)(iVar2 + 4);
      if (param_2 < uVar1) {
        return;
      }
    }
    iVar2 = *(int *)(iVar2 + 0x10);
    uVar1 = *(uint *)(iVar2 + 8);
    if (uVar1 <= regEsi) {
      while (uVar1 != regEsi) {
        iVar2 = *(int *)(iVar2 + 0x10);
        uVar1 = *(uint *)(iVar2 + 8);
        if (regEsi < uVar1) {
          return;
        }
      }
      if (*(int *)(param_3 + 8) != 0) {
        CommitActiveTextInput(*(int *)(param_3 + 8));
      }
      *(int *)(param_3 + 8) = iVar2;
      TextBoxWidget_BeginEdit(iVar2);
    }
  }
  return;
}

