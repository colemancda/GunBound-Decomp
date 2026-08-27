/* TurnEventSet_Find - 0x004e8a70 in the original binary.
 *
 * Named below; still a raw/near-verbatim port of Ghidra's decompiler
 * output rather than a hand-verified reconstruction.  See src/README.md's
 * "Raw/verbatim ports" section for what that status means.
 *
 * WHAT IT IS.  A red-black tree lookup keyed on a ushort: node _Left/_Parent/
 * _Right at +0/+4/+8, the key at +0xc and the _Isnil flag at +0xf, with the
 * header node at map+4.  The descent keeps the last node it turned left at,
 * then returns it only if its key is not GREATER than the target -- i.e. an
 * exact-match find, returning the header (end) when there is none.  Every
 * caller confirms the reading by comparing the result against the header
 * (`cmp eax,[0xe9af14]`, the map's own +4) and treating equality as "absent".
 *
 * REGISTERS PROMOTED (2026-08-27).  All 27 call sites passed nothing, so both
 * the key it compares and the slot it writes its answer into were whatever
 * happened to be in EBX and EAX.  `ret 0` with no stack arguments: ECX is the
 * map, EBX points at the ushort key, and EAX is the caller-allocated result
 * slot that 0x4e8ab6/0x4e8ac7 `mov [eax],ecx` fills -- MSVC returning a
 * 4-byte iterator through a hidden buffer pointer.
 *
 * MSVC __fastcall puts the second parameter in EDX rather than EAX, and the
 * third on the stack; the C semantics are what matter here, not reproducing
 * the original's register allocation.
 *
 * std::set<unsigned short>::find over the turn-event set at g_replayContext
 * +
 * 0x45230 (== DAT_00e9af10).  Returns the node holding the key, or the
 * header
 * node _Myhead (end()) when the key is absent, written through a
 * caller-supplied
 * 4-byte out-slot rather than returned in EAX.
 *
 * WHY THIS NAME (2026-08-27).
 *
 * ONE OWNER, ALL 27 SITES.  tools/callsite_regs.py 0x4e8a70 shows ECX = the
 * immediate 0xe9af10 at 24 sites and `<ctx>+0x45230` at the remaining three
 * (0x4e7bdc, 0x4e7db3, 0x4e814c); globals.h:982 already pins DAT_00e9af10 as
 * g_replayContext+0x45230, so those are the same object.  The rest of the
 * family
 * agrees: all 22 insert sites (FUN_004e86f0) and both call sites of the node
 * allocator (0x4e8e30) reference this one set.  This is not a shared
 * container
 * helper, so it takes no instantiation suffix - unlike StringMap_Find_1c /
 * IntMap_Find_1768, whose templates really do have several instantiations.
 * (It is NOT claimed that this is the only set<ushort> in the image; only
 * that
 * this function has one owner.)
 *
 * IT IS A set, NOT A map - WITNESSED, NOT INFERRED.  The node allocator at
 * 0x4e8e30 is `push 0x10 / call malloc / [eax]=_Left, [eax+4]=_Parent,
 * [eax+8]=_Right / mov word [eax+0xc],cx / mov byte [eax+0xe],dl / mov byte
 * [eax+0xf],0`: a 16-byte node whose value is TWO bytes at +0xc, with _Color
 * at
 * +0xe (FUN_004e8b10 writes it) and _Isnil at +0xf (this function tests it).
 * A
 * map<ushort,T> would carry a pair there and push the flags further out.
 * The
 * container itself is the 12-byte VC7 _Tree - comparator/allocator at +0
 * (never
 * read here), _Myhead at +4 (0x45234), _Mysize at +8 (0x45238, which
 * FUN_004e87b0 decrements and FUN_004e7d60's clear branch zeroes).  The
 * sibling
 * erase settles it from the other side: it throws MSVC's own
 * "invalid map/set<T> iterator" - FUN_0040bee0(s_..._00552000, 0x1b), and
 * 0x1b
 * is exactly strlen of that string.
 *
 * IT IS find, NOT lower_bound.  The descent keeps the last left turn - a
 * lower_bound - but 0x4e8aa7-0x4e8aae then discards it when the key is
 * strictly
 * less than the found node's value and returns _Myhead instead.  That
 * trailing
 * test is VC7's find() wrapper around lower_bound, and it is why all 27
 * callers
 * compare the result against the set's own +4 and read equality as "absent".
 * Do not rename this LowerBound; TreeLowerBound (0x40b540, src/registry/) is
 * a
 * different instantiation over g_valueGuardMap.
 *
 * CALLING CONVENTION - a custom register convention, not a documented ABI.
 * `ret 0`, nothing on the stack: ECX is the set, EBX points at the ushort
 * key,
 * EAX is the caller-allocated 4-byte slot that 0x4e8ab6/0x4e8ac7 `mov
 * [eax],ecx`
 * fills.  Do not describe this as "MSVC's hidden return-buffer pointer":
 * MSVC
 * pushes that pointer as a stack argument and passes nothing in EBX, and the
 * sibling insert FUN_004e86f0 carries the SAME three roles in a DIFFERENT
 * arrangement (out-slot pushed, set in EAX, key in EBX).  Two register
 * assignments for one template family is the signature of VC7 link-time
 * codegen picking a convention per function.  The port declares it
 * __fastcall
 * with the registers promoted to ordinary parameters; the C semantics are
 * what
 * matter, not reproducing the allocation.
 *
 * THE FAMILY, AND WHERE "TURN EVENT" COMES FROM.  0x4e86f0 = insert,
 * 0x4e87b0 = erase(iterator), 0x4e8ad0 = the recursive node destroy
 * (_Erase),
 * 0x4e7d60 = erase-by-key with a 0xffff sentinel meaning clear().  The
 * insert's
 * public wrapper is the already-named PostTurnEvent (0x4e7d30,
 * src/network/),
 * and every key ever stored or looked up is a GB_ACT_* turn-cycle action
 * code
 * from include/opcodes.h: 0xC300 TURN_START, 0xC302, 0xC303 TURN_PHASE,
 * 0xC306
 * AIM_CONFIRM, 0xC400 SCHED_CHECKPOINT, 0xC401 TIMEOUT_WEAPON_SELECT, 0xC409
 * FIRE_COMMITTED, 0xC40B TIMEOUT_BOOKKEEPING, 0x8005 FIELD_RELAY, 0x8006
 * FIRE_FEEDBACK_SOUND, 0x8403 FIRE, 0x8405 WEAPON_SELECT_SOUND.  Caveat for
 * whoever follows the trail: ARCHITECTURE.md (the "turn state machine"
 * section)
 * calls this container "a sorted STL-style tree keyed by trigger time - a
 * scheduled/delayed event queue".  That is WRONG.  The key is the 16-bit
 * action
 * code, compared unsigned; nothing time-valued is ever stored in it.  The
 * "turn event" half of the name comes from the turn-cycle codes and from
 * PostTurnEvent, not from that scheduler claim.
 *
 * WHAT THE LOOKUP IS FOR.  Twenty-four call sites are the inlined body of
 * erase-by-key: set the key local, find, and if the result is not _Myhead
 * hand
 * the node to FUN_004e87b0 - the "release this turn event" sites in
 * State11_InBattle_OnTick / OnEnter / ProcessPacket / ProcessBattleAction
 * and
 * FUN_004ccd10.  (Five of the OnTick ones currently call FUN_004e87b0 with
 * the
 * key pointer and node dropped - an open defect in that file, not here.)
 * The
 * other three are FUN_004e7d60 and the two queue drains FUN_004e7b60 /
 * FUN_004e80d0.  The drains walk PumpBattleActions' two 0x206-stride
 * queued-action arrays (+0x454a4/+0x454a8 and +0x454b4/+0x454b8), key on
 * record+0, and on end() deliver the record - payload copied out, tail
 * memmove'd down, count decremented - provided the slot flag
 * local_8[record+4]
 * is still clear.  On a HIT they set that flag instead, so a held code also
 * stalls every later record from the same player slot (record+4 is the slot
 * byte; local_8 is eight bytes wide).  Membership therefore means "defer",
 * never "drop": the record waits in place until the code is erased.
 * PumpBattleActions backs each queue with its own watchdog - while the
 * outgoing
 * packet cursor (PeekPacketChecksumState of g_clientContext+0x621e8) reads
 * -1,
 * DAT_0056d3dc accumulates the frame delta past 200 and DAT_0056d3d8 counts
 * up
 * to 0xc9, and either one then inlines FUN_004e8ad0 plus the _Myhead/_Mysize
 * reset and empties the whole set.  A remedy of "empty the set" only makes
 * sense if membership is what was holding the queue.
 *
 * ONE CODE WORTH KNOWING ABOUT.  0xC302 is listed in opcodes.h among the
 * action
 * codes "confirmed never implemented (default no-op)", yet
 * State10_Loading_OnEnter and State09_ReadyRoom_ProcessPacket seed it here
 * at
 * battle entry (with 0xC303) and State11_InBattle_OnTick/ProcessPacket erase
 * it.
 * It is not local-only: OnTick also BROADCASTS it via
 * QueueBroadcastEvent(0xc302,&g_replayContext), which writes the code into
 * the
 * u16 at replayCtx+0x44dee of a 0x21-byte action record.  So 0xC302 travels
 * as a
 * real action that the receiving dispatcher falls through to its default
 * case -
 * its only effect is positional, as a per-slot ordering barrier in the
 * drains
 * above.
 */
#include "ghidra_types.h"


void __fastcall TurnEventSet_Find(int param_1,undefined4 *regEax,ushort *regEbx)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *in_EAX = regEax;
  ushort *unaff_EBX = regEbx;
  
  puVar3 = *(undefined4 **)(param_1 + 4);
  if (*(char *)((int)puVar3[1] + 0xf) == '\0') {
    puVar1 = (undefined4 *)puVar3[1];
    do {
      if (*(ushort *)(puVar1 + 3) < *unaff_EBX) {
        puVar2 = (undefined4 *)puVar1[2];
      }
      else {
        puVar2 = (undefined4 *)*puVar1;
        puVar3 = puVar1;
      }
      puVar1 = puVar2;
    } while (*(char *)((int)puVar2 + 0xf) == '\0');
  }
  if ((puVar3 != *(undefined4 **)(param_1 + 4)) && (*(ushort *)(puVar3 + 3) <= *unaff_EBX)) {
    *in_EAX = puVar3;
    return;
  }
  *in_EAX = *(undefined4 **)(param_1 + 4);
  return;
}

