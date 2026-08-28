/* IsWidgetEnabled - 0x00406400 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * DROPPED REGISTER RECOVERED (2026-08-27): unaff_ESI is the INNER key.  The
 * body is the same two-level registry lookup as SetWidgetReadyState and
 * RemoveTextBoxWidget -- outer list walked by +0x1c and keyed at +4 against param_2,
 * then the matched node's inner list walked by +0x10 and keyed at +8 against
 * ESI -- so ESI is a widget key, and the values found (1, 3, 5, 0x10) sit in
 * the same small-key band those functions use.
 *
 * Pairing is unambiguous without any ordering assumption: each of the four
 * ported callers contains exactly ONE site, and each loads a distinct literal
 * (`mov esi,5` at 0x428c21, `mov esi,3` at 0x4b82f7, `mov esi,0x10` at
 * 0x4b9d04, `mov esi,1` at 0x4d626c), all read individually off the
 * disassembly.
 *
 * There is a FIFTH binary site, 0x447671 in FUN_004475c0 with `mov esi,0xf`,
 * which has no C counterpart and should not: PROGRESS.csv marks
 * FUN_004475c0 TODO, i.e. not ported.  That is why count_call_args.py reports
 * four where callsite_regs.py reports five.
 *
 * NAMED 2026-08-27 (was IsWidgetEnabled).  A pure predicate over the
 * active-object registry: it walks to the widget at (layer key EDX,
 * widget id ESI) and returns 1 iff that widget's state field +0x24 is
 * not 3 -- the "disable" state.  A disabled widget and an absent one
 * both read 0; a widget never given a state (+0x24 == -1) reads 1.
 * It writes nothing, and its `ret` carries no immediate.
 *
 * WHY +0x24 == 3 IS "DISABLED", established outside this body.
 * ResolveNamedState (0x461c60, the widget vtable's slot 1) is the
 * field's writer: 0x461c78 `mov [esi+0x24],eax` stores FindStringNoCase
 * (0x401610)'s index of the requested state name within the name table
 * reached through this+0x1c.  SetButtonStateByIndex (0x405e30) carries
 * the inverse table -- 0 "ready", 1 "push", 2 "mouse", 3 "disable",
 * 4 "select", 5 "active" -- so index 3 is "disable".  InvokeWidget
 * (0x406300) settles it a second time without that table: its disable
 * path dispatches slot 1 with 0x551e68 ("disable") at
 * 0x40633d-0x406347, and its enable path refuses to run unless
 * [ecx+0x24] is already 3 or -1 (0x40634a-0x406355).
 * HandleActiveObjectMouseUp (0x406170) confirms the same numbering from
 * the other end: it fires a click only when +0x24 is 1 or 5
 * (0x406198-0x4061a3, "push" or "active"), then sets 0x551e70 "mouse",
 * index 2.
 *
 * SETTER AND GETTER INSIDE ONE CALLER.
 * State03_GameRoomList_HandleMouseInput enables widget 5 on
 * WM_LBUTTONDOWN over a room card (0x428bd7-0x428be5: `push 1`, then
 * InvokeWidget with esi=5), and on WM_LBUTTONDBLCLK asks THIS function
 * about that same widget 5 (0x428c2d) before acting.  One handler, one
 * id: InvokeWidget's `enabled` argument written, then read back here.
 *
 * THE FIVE CALL SITES, each in a game state's input vtable slot, all
 * with eax=0xe9be90 (&g_activeObjectRegistry) and edx=0; ESI, the
 * widget id, is the only value that varies:
 * 0x428c2d  id 5     State03_GameRoomList_HandleMouseInput (0x203)
 * 0x447671  id 0xf   FUN_004475c0 -- State07_AvatarStore's own
 * mouse-input slot (.data 0x555610, immediately
 * before its OnEnter at 0x555614, the same
 * relative slot State03, State09 and State11 use);
 * still TODO in PROGRESS.csv, hence no C call site
 * 0x4b8303  id 3     State11_InBattle_HandleKeyInput (key 0x42)
 * 0x4b9d10  id 0x10  State11_InBattle_HandleMouseInput
 * 0x4d6278  id 1     State09_ReadyRoom_HandleChatInput (0x204)
 * Each branches on the byte and keeps nothing.
 *
 * THREE OF THE FIVE THEN SYNTHESIZE THAT WIDGET'S OWN CLICK, pushing
 * (0, 0, <the id just tested>) at g_inputEventRing (0x795070):
 * 0x428c3c and 0x447680 store the triple into their own incoming frame
 * and tail-jmp to EnqueueInputEvent (0x4f2da0); 0x4b8310 pushes it and
 * calls (ebx is 0 from 0x4b82bc).  That record is exactly what the
 * genuine mouse path pushes -- HandleActiveObjectMouseUp at
 * 0x4061a5-0x4061b2 pushes 0, [obj+4] and [obj+8], i.e. (0, layer, id)
 * -- and layer is 0 for these widgets, which is the EDX this function
 * is queried with (CreateActiveObjectLayer, 0x4f2f00, keys the outer
 * node at +4 with that layer key).  The fourth site does the
 * complement: having found widget 0x10 enabled it calls InvokeWidget at
 * 0x4b9d1f (esi still 0x10, pushed enable byte edx=0) to DISABLE it,
 * then sends its packet.
 *
 * WHAT IT IS NOT.  CWidget::SetEnabled (0x50e7d0, C shim
 * Widget_SetEnabled) writes m_enabled at +0x1c of the panel-system
 * CWidget -- a different class and a different field; nothing connects
 * the two to this one.  SetWidgetReadyState (0x406380) shares this walk
 * and the != 3 guard but writes byte +0x4c, the sticky flag that makes
 * a later "ready" render as "active" instead (set to 1 beside the
 * "active" dispatch at 0x4063ec, read back as param_1[0x13] in
 * SetButtonStateByIndex), so this is not its getter either.
 *
 * ARGUMENTS.  `ret` takes no immediate, so all four are registers, and
 * param_1 (ECX) is a PHANTOM -- 0x406400 `mov ecx,[eax+4]` writes it
 * before any read -- so it must stay unvalued (0 at all four ported
 * sites).  regEax is the registry, param_2 the layer key, regEsi the
 * widget id.
 */
#include "ghidra_types.h"


uint __fastcall IsWidgetEnabled(undefined4 param_1,uint param_2,int regEax,uint regEsi)

{
  uint uVar1;
  uint uVar2;
  uint unaff_ESI = regEsi;
  
  uVar2 = *(uint *)(*(int *)(regEax + 4) + 0x1c);
  uVar1 = *(uint *)(uVar2 + 4);
  do {
    if (param_2 < uVar1) {
LAB_00406419:
      return uVar2 & 0xffffff00;
    }
    if (uVar1 == param_2) {
      uVar2 = *(uint *)(uVar2 + 0x10);
      uVar1 = *(uint *)(uVar2 + 8);
      if (uVar1 <= unaff_ESI) {
        while (uVar1 != unaff_ESI) {
          uVar2 = *(uint *)(uVar2 + 0x10);
          uVar1 = *(uint *)(uVar2 + 8);
          if (unaff_ESI < uVar1) {
            return uVar2 & 0xffffff00;
          }
        }
        if (*(int *)(uVar2 + 0x24) != 3) {
          return CONCAT31((int3)(uVar2 >> 8),1);
        }
      }
      goto LAB_00406419;
    }
    uVar2 = *(uint *)(uVar2 + 0x1c);
    uVar1 = *(uint *)(uVar2 + 4);
  } while( true );
}

