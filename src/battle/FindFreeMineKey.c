/* FindFreeMineKey - 0x00437490 in the original binary.
 *
 * Named below; still a raw/near-verbatim port of Ghidra's decompiler
 * output rather than a hand-verified reconstruction.  See src/README.md's
 * "Raw/verbatim ports" section for what that status means.
 *
 * DROPPED REGISTER RECOVERED (2026-08-27): in_EAX is param_4 at all four
 * call sites, and both callers pin it the same way.  SpawnMine's
 * `dec edi / or edi,0xfffffff8 / inc edi` at 0x437629 is character for
 * character its own `param_4 = (param_4 - 1 | 0xfffffff8) + 1;`, so edi is
 * param_4 there; SpawnSuperMine loads edi from [esp+0x2c], which under its
 * SEH triple plus four prologue saves is E+0x10, i.e. param_4 -- witnessed by
 * the same prologue's `mov eax,[esp+0x10]` = E+4 = param_1, the argument its
 * PeekPacketChecksumBool(param_1 + 4) on the next line takes.  Both callers
 * then do `mov eax,edi` immediately before each call, including the retry
 * inside the `while (iVar2 == -1)` loop.
 *
 * NAMED 2026-08-27 (was FUN_00437490).  Given a battle player slot 0..7 in
 * EAX, returns the lowest unused entity-registry key in that player's
 * reserved 8-key block [slot*8, slot*8+8) of the class-100003 (MINE)
 * collection under g_clientContext+0x6a7f8c, or -1 when all eight are live.
 * It is pure: it reserves nothing.
 *
 * Evidence that the return value is the registry KEY, followed out of the
 * function rather than read off its body: SpawnMine keeps it in ESI
 * (0x437639 `mov esi,eax`) and hands it over as `mov ecx,esi` immediately
 * before `call 0x4977c0` (InitMine) at 0x437671.  InitMine does not touch
 * ECX before delegating to InitProjectile (0x454dc0), whose 0x454de9
 * `mov dword ptr [esi + 8], ecx` stores it at object +0x8 - the very field
 * this function's inner walk compares against.  SpawnSuperMine repeats the
 * identical ESI->ECX hand-off at 0x4378c8.  See the "active-object layer
 * registry" note: layer +0x4 = class id, +0x1c = next layer, +0x10 = the
 * collection, entries keyed at +0x8 and chained through +0x10.
 *
 * Evidence that the argument is a PLAYER SLOT: both callers normalise
 * param_4 with the signed mod-8 idiom (`and edi,0x80000007 / dec edi /
 * or edi,0xfffffff8 / inc edi` at 0x437621) - the same idiom AdvanceTurnQueue
 * applies to the turn-queue head byte at battle+0x10a8 before indexing the
 * per-player 0x224-stride guard arrays.  SpawnMine also stores the
 * normalised value as a byte at mine+0x3c.  The reference server's
 * RoomCapacity tops out at _4_4 = 8, so a battle holds at most 8 players.
 * FUN_0043c440 confirms the block is per player: it walks the same
 * in_EAX*8 .. +8 range of the same class-100003 layer and fires vtable
 * slot +0x20 on every entry, and its two call sites pass a player slot -
 * AdvanceTurnQueue at 0x4cf603 (`movzx eax,[esi+0x10a8]` mod 8, the player
 * whose turn ended) and State11_InBattle_ProcessBattleAction at 0x4b6072
 * (`movzx esi,bl`, a slot byte off the action packet).
 *
 * Evidence that -1 means "this player already has 8 live mines": both
 * callers wrap the call in `while (result == -1) { FUN_00437500(slot in
 * EDX); retry; }`, and FUN_00437500 scans the same eight keys, picks the
 * entry with the smallest +0x3f9c, fires vtable +0x20, unlinks it from the
 * +0xc/+0x10 list and invokes the scalar-deleting destructor.  Mine +0x3f9c
 * is stamped in SpawnMine at 0x437713 from PeekPacketChecksumState(
 * g_clientContext + 0xeba98), the turn counter BeginNewTurn seeds, so the
 * minimum is the OLDEST mine.  The loop only terminates because eviction
 * frees a key, which is the callers asserting exactly this contract: the
 * pair enforces a hard cap of 8 simultaneous mines per player.
 *
 * `regEax` keeps its recovered-register name per the tree's convention
 * (cf. HandleTurnTimeoutSlot, BuildRotatedSpriteQuad); it is the player
 * slot.  Note for whoever touches SpawnMine/SpawnSuperMine next: the C
 * port currently calls `InitMine(pvVar3)` and drops this key on the floor,
 * so ported mines are constructed with a garbage +0x8 registry key.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output beyond the naming -
 * not hand-verified. See src/README.md's "Raw/verbatim ports" section.
 *
 * DROPPED REGISTER RECOVERED (2026-08-27): in_EAX is param_4 at all four
 * call sites, and both callers pin it the same way.  SpawnMine's
 * `dec edi / or edi,0xfffffff8 / inc edi` at 0x437629 is character for
 * character its own `param_4 = (param_4 - 1 | 0xfffffff8) + 1;`, so edi is
 * param_4 there; SpawnSuperMine loads edi from [esp+0x2c], which under its
 * SEH triple plus four prologue saves is E+0x10, i.e. param_4 -- witnessed by
 * the same prologue's `mov eax,[esp+0x10]` = E+4 = param_1, the argument its
 * PeekPacketChecksumBool(param_1 + 4) on the next line takes.  Both callers
 * then do `mov eax,edi` immediately before each call, including the retry
 * inside the `while (iVar2 == -1)` loop. */
#include "ghidra_types.h"


uint FindFreeMineKey(int regEax)

{
  uint uVar1;
  int in_EAX = regEax;
  uint uVar2;
  int iVar3;
  int iVar4;
  bool bVar5;
  
  uVar2 = in_EAX << 3;
  iVar4 = 0;
  do {
    uVar1 = *(uint *)(*(int *)(*(int *)(&DAT_006a7f8c + g_clientContext) + 0x1c) + 4);
    iVar3 = *(int *)(*(int *)(&DAT_006a7f8c + g_clientContext) + 0x1c);
    if (0x186a3 < uVar1) {
      return uVar2;
    }
    while (uVar1 != 0x186a3) {
      iVar3 = *(int *)(iVar3 + 0x1c);
      uVar1 = *(uint *)(iVar3 + 4);
      if (0x186a3 < uVar1) {
        return uVar2;
      }
    }
    iVar3 = *(int *)(iVar3 + 0x10);
    bVar5 = *(uint *)(iVar3 + 8) == uVar2;
    if (uVar2 <= *(uint *)(iVar3 + 8) && !bVar5) {
      return uVar2;
    }
    while (!bVar5) {
      iVar3 = *(int *)(iVar3 + 0x10);
      bVar5 = *(uint *)(iVar3 + 8) == uVar2;
      if (uVar2 < *(uint *)(iVar3 + 8)) {
        return uVar2;
      }
    }
    iVar4 = iVar4 + 1;
    uVar2 = uVar2 + 1;
  } while (iVar4 < 8);
  return 0xffffffff;
}

