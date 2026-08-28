/* RemoveTextBoxWidget - 0x0040cdf0 in the original binary.
 *
 * Named below; still a raw/near-verbatim port of Ghidra's decompiler
 * output rather than a hand-verified reconstruction.  See src/README.md's
 * "Raw/verbatim ports" section for what that status means.
 *
 * DECLARED ARGUMENTS FILLED.  `ret 0` puts nothing on the stack, so param_1
 * (ECX) and param_2 (EDX) are both registers, and every call site passed
 * neither.  ECX is a PHANTOM -- the entry writes it (`mov ecx,[eax+4]`)
 * before any read -- so it takes 0; EDX is 0x2710 at every site.
 *
 * ESI and EDI are also read before being written here, so they are further
 * register arguments Ghidra did not declare.  ESI genuinely varies per site
 * (0 and 1), so it stays open rather than being guessed at.
 *
 * DROPPED REGISTERS RECOVERED (2026-08-27): ESI is the inner key compared
 * against each node's +8, and EDI is the container -- &g_activeObjectRegistry2
 * (0xe9c0fc) at all six sites, loaded once per pair and left live across both
 * calls.  ESI is 0 on the first call of each pair and 1 on the second.
 *
 * The three call pairs are pinned by their own blocks rather than by order:
 * FUN_00445450's is preceded by the address-bearing label LAB_00445543, and
 * 0x445543 really is that block (`xor edx,edx / mov edi,0xe9be90 /
 * call 0x405fb0 / xor esi,esi / mov edx,0x2710 / mov edi,0xe9c0fc`).  The
 * other two carry a call-sequence fingerprint plus a store the source also
 * shows.
 *
 * Note the failure mode this change buys: __fastcall decorates as
 * @RemoveTextBoxWidget@N with N the stack-byte count, so widening 8 to 16 renames
 * the symbol and any missed call site becomes a LINK error rather than a
 * silent garbage read.
 *
 * /* RemoveTextBoxWidget - 0x0040cdf0 in the original binary.
 *
 * NAMED 2026-08-27 (was RemoveTextBoxWidget).  Removes one registered object from
 * an active-object registry by (layerKey, id) and destroys it.  It is the
 * sibling of RemoveWidget (0x405fb0) over the SECOND registry: disassembled,
 * the two are instruction-for-instruction the same two-level keyed walk and
 * the same unlink + scalar deleting destructor, differing only in that
 * RemoveWidget also clears container+0xc where this clears container+8
 * alone.
 *
 * mov eax,[edi+4] / mov eax,[eax+0x1c]    container -> outer layer list
 * mov ecx,[eax+4]  / cmp ecx,edx          outer key (the layer key) is EDX
 * mov eax,[eax+0x10] / mov ecx,[eax+8] / cmp ecx,esi   inner key is ESI
 * cmp eax,[edi+8] / mov [edi+8],0         drop the focus slot if it is us
 * mov [ecx+0x10],edx / mov [ecx+0xc],edx  unlink from the layer's list
 * mov edx,[eax] / push 1 / mov ecx,eax / call [edx]   __thiscall dtor,
 * free=1
 *
 * WHICH OBJECTS THESE ARE.  tools/callsite_regs.py 0x40cdf0 gives 8 call
 * sites in 4 pairs -- State07_AvatarStore_ProcessPacket (0x444cce/0x444cdd),
 * FUN_004452c0 (0x44542f/0x44543e), FUN_00445450 (0x44555b/0x44556a) and
 * RenderInventoryItemDetail (0x44b9f9/0x44ba08) -- with EDX = 0x2710 at 8/8,
 * EDI = 0xe9c0fc (g_activeObjectRegistry2) loaded once per pair, and ESI = 0
 * then 1.  Those two keys were pinned from the other end, not from this
 * body:
 * InitTextBoxWidget (0x40c980) receives the layer key in EAX = 0x2710 and
 * the
 * id in ECX = 0 / 1 at its only two construction sites (orig
 * 0x446489-0x4464b4, 0x4464cf-0x446500) and stores them to object +4 and +8
 * --
 * the exact fields walked here.  Each site is immediately followed by
 * `mov edx,0xe9c0fc / call 0x4f2fb0` (RegisterActiveObject), and a scan of
 * every 0xe9c0fc immediate in .text shows those are the ONLY two objects
 * ever
 * registered into the second registry in the whole binary.  So this
 * function's
 * 8 sites destroy exactly the objects InitTextBoxWidget builds.
 *
 * 0x2710 IS THE DIALOG'S KEY, NOT A CLASS KEY.  It is 10000, and the same
 * number is a layer key in an unrelated container (LoadSpriteSet registers
 * into g_spriteRegistry with key 10000 -- see
 * src/rendering/LoadSpriteSet.c).
 * The second registry itself is read at a different layer: orig 0x4d5550
 * `mov esi,0 / mov edx,0x186a0 / mov eax,0xe9c0fc / call 0x40cfe0`
 * (GetWidgetChildText, State09_ReadyRoom_OnCommand).  What is settled is
 * narrower and enough: the avatar-store gift dialog's two text boxes are
 * (0x2710,0) and (0x2710,1) in registry 2.
 *
 * WHAT THE TWO BOXES ARE.  FUN_00445450 case 0x35 reads them back with
 * GetWidgetChildText(0,0x2710,&g_activeObjectRegistry2,0) into a 16-byte
 * field and (...,1) into a length-prefixed string, then emits opcode 0x6030
 * (or 0x6031, GB_OP_GIFT_GIVEN, on the other side of a guard bool -- both
 * copy box 0's name first).  The reference server's GiftRequest.swift
 * (0x6030 = GB_OP_GIFT_REQUEST) is recipient: Username, unknown: UInt32,
 * itemPosition: UInt8, avatar: UInt32, message: length-prefixed String, and
 * Username.swift fixes Username.length at 0xC.  Box 0 -- created at
 * (0xf2,0x112), width 0x49, limit 0xc -- is the RECIPIENT NAME; box 1 --
 * (0xf2,0x139), width 0xa5, limit 0x32 -- is the GIFT MESSAGE.
 *
 * WHY THE NAME IS QUALIFIED.  The walk itself is generic and would serve any
 * registry; the qualifier is caller evidence, exactly as RemoveWidget's is
 * (EDI = &g_activeObjectRegistry at 132/133 sites there, 0xe9c0fc at 8/8
 * here).  Three of the four pairs tear down the gift dialog in the same
 * breath as its buttons and then rebuild the store's own buttons:
 * RemoveWidget(&g_activeObjectRegistry,0,0x34);   b_storewindow_cancel
 * RemoveWidget(&g_activeObjectRegistry,0,0x35);   b_storewindow_confirm
 * RemoveTextBoxWidget(0,0x2710,0,&g_activeObjectRegistry2);
 * RemoveTextBoxWidget(0,0x2710,1,&g_activeObjectRegistry2);
 * CreateAvatarStoreButtons(...);          <- 0x444ce7 / 0x445444 / 0x445570
 * The fourth pair (RenderInventoryItemDetail, orig 0x44ba08) does the same
 * four removals and then `jmp 0x44ba15` into a state check -- it does NOT
 * call CreateAvatarStoreButtons there; the one at
 * RenderInventoryItemDetail.c:118 is a later, separately-guarded branch.
 * Ids 0x34/0x35 are created in the same block as the two text boxes
 * (FUN_00445450 lines 516-518 and 520-540).  Buttons through registry 1,
 * text boxes through registry 2.
 *
 * THIS SETTLES AN OPEN QUESTION IN globals.h.  That header records a
 * disagreement about g_activeObjectRegistry2's contents: globals.c calls it
 * a
 * "flat-ButtonWidget registry root" while
 * HandleBackgroundActiveObjectMouseDown
 * records its hit result being read at +0x448, "far past CButtonWidget's
 * 0x50
 * bytes ... a larger, different class - not yet identified".  The larger
 * class
 * is the TEXT BOX: operator_new(0x458), vtable 0x55208c, text buffer at
 * +0x48,
 * focus flag at +0x448 -- the same +0x448 CommitActiveTextInput clears.
 *
 * WHY THE +0xc CLEAR IS ABSENT -- THE TWO CONTAINERS ARE DIFFERENT STRUCTS.
 * Registry 2 is registry 1 minus the +0xc cached slot, with everything above
 * it shifted down four.  Two independent witnesses:
 * - InitGame at orig 0x412330-0x41233a zeroes registry 1's +8 AND +0xc
 * (0xe9be98 / 0xe9be9c) but registry 2's +8 ONLY (0xe9c104).
 * - InitGame at orig 0x40ed16-0x40ed1b stores the same input-event ring
 * pointer (0x795070) to registry 1 at +0x10 (0xe9bea0) and to registry 2
 * at +0xc (0xe9c108) -- src/entry/InitGame.c:140.
 * So registry 2 HAS a +0xc user; it is the ring pointer, not a cached-object
 * slot, and clearing it the way RemoveWidget clears registry 1's would be a
 * bug.  Registry 2's one cached slot, +8, is the focused text-input object
 * --
 * written by FUN_0040cf80 (the focus setter, which commits the outgoing box
 * via CommitActiveTextInput first), read per frame by SyncActiveTextInput,
 * cycled by FUN_0040d020 on Tab/Enter/Escape -- and it is precisely the slot
 * this function's tail clears when the object being destroyed owns it.
 * NOTE for whoever is next in crt_shims_msvc.c: line 400 fixes up
 * g_activeObjectRegistry2 + 0x10 with the ring, which per the above is the
 * wrong offset for this container (+0xc); line 399's registry 1 is correct.
 *
 * SIBLING ACCESSORS ON THIS SAME CLASS, named on other axes -- do not add a
 * third: GetWidgetChildText (0x40cfe0) is its text getter, InitTextBoxWidget
 * (0x40c980) its constructor, FUN_0040cf80 its focus setter,
 * CommitActiveTextInput / SyncActiveTextInput the Win32 edit-control bridge.
 *
 * ARGUMENTS.  `ret 0` puts nothing on the stack, so all four are registers.
 * param_1 (ECX) is a PHANTOM -- 0x40cdf6 `mov ecx,[eax+4]` writes it before
 * any read -- and must NOT be given a value; outerKey is EDX, innerKey ESI,
 * container EDI.  The names match RemoveWidget deliberately, so the two read
 * alike.  The SIGNATURES do not, and that is a local exception rather than a
 * rule: RemoveWidget was promoted to 3-arg __cdecl with the phantom dropped,
 * for the reason FindSpriteFrame's header sets out (a __fastcall rename
 * turns
 * its ~123 not-yet-fixed callers into link errors).  Here there are no
 * unfixed callers -- all 6 ported sites already pass 4 arguments and the
 * remaining pair lives in FUN_004452c0, which is stubbed -- so the 4-arg
 * __fastcall shape is kept as-is and the phantom simply stays unvalued.
 * Promoting it to __cdecl later is a safe, separate change.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output beyond the naming --
 * see src/README.md's "Raw/verbatim ports" section for status.  NOTE: the
 * binary has 8 call sites but the ported tree has only 6; FUN_004452c0
 * (0x4452c0, TODO in PROGRESS.csv:524, auto-stubbed at globals.c:1544 and
 * functions.h:643) holds the other pair.
 * /
 */
#include "ghidra_types.h"


void __fastcall RemoveTextBoxWidget(undefined4 param_1,uint param_2,uint regEsi,int regEdi)

{
  int iVar1;
  uint uVar2;
  undefined4 *puVar3;
  uint unaff_ESI = regEsi;
  int unaff_EDI = regEdi;
  
  iVar1 = *(int *)(*(int *)(unaff_EDI + 4) + 0x1c);
  uVar2 = *(uint *)(iVar1 + 4);
  while (uVar2 <= param_2) {
    if (uVar2 == param_2) {
      puVar3 = *(undefined4 **)(iVar1 + 0x10);
      uVar2 = puVar3[2];
      if (uVar2 <= unaff_ESI) goto LAB_0040ce15;
      break;
    }
    iVar1 = *(int *)(iVar1 + 0x1c);
    uVar2 = *(uint *)(iVar1 + 4);
  }
  goto LAB_0040ce21;
  while( true ) {
    puVar3 = (undefined4 *)puVar3[4];
    uVar2 = puVar3[2];
    if (unaff_ESI < uVar2) break;
LAB_0040ce15:
    if (uVar2 == unaff_ESI) goto LAB_0040ce23;
  }
LAB_0040ce21:
  puVar3 = (undefined4 *)0x0;
LAB_0040ce23:
  if (puVar3 == *(undefined4 **)(unaff_EDI + 8)) {
    *(undefined4 *)(unaff_EDI + 8) = 0;
  }
  if (puVar3 != (undefined4 *)0x0) {
    *(undefined4 *)(puVar3[3] + 0x10) = puVar3[4];
    *(undefined4 *)(puVar3[4] + 0xc) = puVar3[3];
    (**(code **)*puVar3)(1);
  }
  return;
}

