/* RemoveWidget - 0x00405fb0 in the original binary.
 *
 * THE NAME IS BETTER THAN I FIRST CLAIMED - CORRECTION (2026-08-20).  An
 * earlier revision of this header, and commit 2755ae1, asserted that this
 * function "has nothing to do with widgets" and that the name names the wrong
 * subsystem.  THAT WAS WRONG, and scanning the call sites is what showed it:
 * EDI - the container - is the immediate 0xe9be90 at 132 of 133 sites, and
 * DAT_00e9be90 is the ACTIVE-OBJECT (widget) REGISTRY, the same container
 * SweepActiveObjectRegistry, DrawActiveObjectRegistry and
 * TickActiveObjectRegistry walk.  So this really does operate on widgets.
 *
 * What survives from that analysis is the part about the ALGORITHM, which is
 * genuinely shared: the lookup is a generic two-level keyed container walk, and
 * FindSpriteFrame runs the identical code over a different container.  I
 * inferred the subsystem from the algorithm, which does not follow - the same
 * container shape is reused for sprites and for widgets alike.
 *
 * Disassembled at 0x405fb0 it is
 * byte-for-byte the SAME two-level keyed lookup as FindSpriteFrame
 * (0x4f30c0): outer list from container+4 then +0x1c, walked by +0x1c and
 * keyed at +4; inner list from the matched node's +0x10, walked by +0x10 and
 * keyed at +8; `xor eax,eax` on either miss.
 *
 *     mov eax,[edi+4] / mov eax,[eax+0x1c]   container -> outer list
 *     cmp ecx,edx                            outer key is EDX
 *     mov eax,[eax+0x10] / cmp ecx,esi       inner key is ESI
 *
 * so the register arguments are EDI=container, EDX=outerKey, ESI=innerKey -
 * the same three FindSpriteFrame takes, differing only in that the container
 * arrives in EDI rather than EAX. And as there, ECX is a PHANTOM: `mov
 * ecx,[eax+4]` at 0x405fb6 writes it before anything reads it, so Ghidra's
 * `param_1` is not an argument at all. `outerKey` (EDX) is real.
 *
 * What it does beyond the lookup is the tail, and it is where the "Remove"
 * came from: having found the record it clears the container's two cached
 * slots if either points at it -
 *     cmp eax,[edi+8]  / jne / mov [edi+8],0
 *     cmp eax,[edi+0xc] / ...
 * i.e. look up an entry and evict it from the registry's two cached slots.
 * "Remove" is therefore a fair description of the tail, over the right
 * subsystem - so the name stands, and no rename is called for.
 *
 * CALL SITES SCANNED (133 direct calls, cached in
 * tools/removewidget_regs.json).  The arguments are almost entirely literal,
 * so this should sweep cleanly once the source-to-site pairing is settled:
 *     EDI  0xe9be90 at 132/133 - &DAT_00e9be90, the widget registry
 *     EDX  `xor edx,edx` at 131/133 - the outer key is 0
 *     ESI  an immediate at ~124/133, spread over 37 distinct values
 *          (0x32..0x3c and friends - widget ids)
 * ECX is a phantom and must NOT be given a value.  The ESI spread means the
 * pairing does matter here, unlike the uniform cases: see
 * tools/count_call_args.py and the block/witness techniques used for the
 * render chain.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output, not hand-verified.
 * See src/README.md's "Raw/verbatim ports" section for status.
 *
 * PROMOTED (2026-08-20).  Signature is now
 * `void RemoveWidget(int container, uint outerKey, uint innerKey)` - plain
 * __cdecl, NOT __fastcall.  Two deliberate choices:
 *   - Ghidra's `param_1` (ECX) IS GONE.  It was a phantom: `mov ecx,[eax+4]`
 *     at 0x405fb6 writes ECX before anything reads it, so it was never an
 *     argument.  Keeping it would have meant inventing a value for every
 *     call site.
 *   - __cdecl rather than __fastcall, for the reason FindSpriteFrame's header
 *     sets out: __fastcall decorates the symbol with its stack-byte count, so
 *     adding parameters renames it and breaks every not-yet-fixed caller at
 *     link time.  __cdecl keeps `_RemoveWidget` and lets the 123 still-argless
 *     call sites keep compiling - they read garbage off the stack exactly as
 *     they already read garbage out of registers, so it is strictly no worse
 *     for them and unblocks the sites that ARE fixed.
 *
 * 57 of the 131 call sites are recovered.  ApplyRoomSettings - which holds 55
 * of them and was the hard case - is COMPLETE.
 *
 * The method that finished it is straight-line RUNS (tools/rw_run_pair.py):
 * delimit a run by CONTROL FLOW on both sides - any jmp/jcc/ret or branch
 * TARGET in the binary, any goto/break/case/label/if/else/brace in the source
 * - and inside such a run source order must equal VA order, which is the one
 * ordering claim that is not an assumption.  Each run is identified by the
 * CreateButtonWidget it contains, whose (key, id) literals are unique there.
 * Two details mattered: a run must extend BACKWARDS to its opening boundary,
 * or the removes that precede the create are never reached; and the source
 * side must count calls that are ALREADY recovered, or their absence
 * desynchronises the run and the whole run is discarded.
 *
 * Checked against evidence the pairing never uses: each case creates one
 * widget of a group and removes that group's other members.  47 removes
 * consistent, 0 violations.  The result reads as obviously right - case 1
 * removes 10, 12, 13 around creating 11; case 2 removes 10, 11, 13 around
 * creating 12 - with the shared tails arriving through the gotos exactly as
 * the original lays them out.
 *
 * Two more in State11_InBattle_ProcessBattleAction, confirmed by the same
 * shape in miniature: InvokeWidget(1,1) with create of widget 1 removes
 * widget 2, and the mirror image for weapon 2.
 *
 * WHAT DOES NOT YIELD: five of the remaining callers - FUN_00445450,
 * State11_InBattle_HandleKeyInput/HandleMouseInput, HandleTurnTimeoutSlot and
 * FUN_004ccd10 - have CreateButtonWidget landmarks that are NOT UNIQUE within
 * the function, so runs cannot be keyed by them at all; the tool refuses
 * rather than guessing.  Those 74 sites need a different landmark.
 *
 * The original 8 came from an exact pairing that needs no landmark at all: Ghidra emits `LAB_00XXXXXX:` labels whose names
 * are real addresses, so a label immediately followed by RemoveWidget() pins
 * that call to that VA (the label lands on the argument setup, and the call
 * follows within a few instructions).  No ordering assumption is involved.
 *
 * WHY THE OTHER 123 ARE NOT DONE.  ApplyRoomSettings alone holds 55 of them
 * and its structure defeats every cheaper method: it is a switch whose cases
 * share tails through gotos, and Ghidra emits the case bodies in a different
 * order from the binary - the CreateButtonWidget landmarks run
 * ...(50),(51),(52),(53),(62),(61),(60),(70)... in the binary against
 * ...(53),(60),(61),(62),(70)... in the source.  Aligning on those landmarks
 * by VALUE (their key/id pairs are unique) matches 11 of 24 segments and
 * would pair 25 calls, but every one of those rests on source order matching
 * VA order WITHIN a segment, and this is precisely the file that proves that
 * assumption is unsafe.  So none of the 25 were applied.
 *
 * The semantics are clear and will make the rest tractable: each case creates
 * one widget of a group and removes that group's other members - create key
 * 10 removes 11,12,13; create 20 removes 21,22,23; and so on in groups of
 * four (0xa-0xd, 0x14-0x17, 0x1e-0x21, 0x32-0x35, 0x3c-0x3e, 0x46-0x49).
 * Scanned register data is cached in tools/removewidget_regs.json. */
#include "ghidra_types.h"


void RemoveWidget(int container,uint outerKey,uint innerKey)

{
  int iVar1;
  uint uVar2;
  undefined4 *puVar3;
  
  iVar1 = *(int *)(*(int *)(container + 4) + 0x1c);
  uVar2 = *(uint *)(iVar1 + 4);
  while (uVar2 <= outerKey) {
    if (uVar2 == outerKey) {
      puVar3 = *(undefined4 **)(iVar1 + 0x10);
      uVar2 = puVar3[2];
      if (uVar2 <= innerKey) goto LAB_00405fd5;
      break;
    }
    iVar1 = *(int *)(iVar1 + 0x1c);
    uVar2 = *(uint *)(iVar1 + 4);
  }
  goto LAB_00405fe1;
  while( true ) {
    puVar3 = (undefined4 *)puVar3[4];
    uVar2 = puVar3[2];
    if (innerKey < uVar2) break;
LAB_00405fd5:
    if (uVar2 == innerKey) goto LAB_00405fe3;
  }
LAB_00405fe1:
  puVar3 = (undefined4 *)0x0;
LAB_00405fe3:
  if (puVar3 == *(undefined4 **)(container + 8)) {
    *(undefined4 *)(container + 8) = 0;
  }
  if (puVar3 == *(undefined4 **)(container + 0xc)) {
    *(undefined4 *)(container + 0xc) = 0;
  }
  if (puVar3 != (undefined4 *)0x0) {
    *(undefined4 *)(puVar3[3] + 0x10) = puVar3[4];
    *(undefined4 *)(puVar3[4] + 0xc) = puVar3[3];
    (**(code **)*puVar3)(1);
  }
  return;
}

