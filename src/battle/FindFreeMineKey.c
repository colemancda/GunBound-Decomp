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
 * THE KEY SPACE IS 64 WIDE = 8 PLAYERS x 8 MINES, witnessed outside both
 * this function and its callers.  ExplodeSuperShot_Bullet8 (0x4837e0) runs
 * three sibling scan loops over the registry: the mobile loop and the jewel
 * loop both end `cmp eax,8` (0x483a9a, 0x483d41), but the mine loop - the
 * one whose body is `call 0x425e60` (HitTestMine) at 0x483db4 - ends
 * `cmp eax,0x40 / jl 0x483d50` at 0x483fd2.  A 64-wide mine key space beside
 * 8-wide mobile/jewel spaces is exactly the slot*8 partition this function
 * computes.
 *
 * Evidence that the return value is the registry KEY, followed out of the
 * function rather than read off its body: SpawnMine keeps it in ESI
 * (0x437639 `mov esi,eax`) and hands it over as `mov ecx,esi` immediately
 * before `call 0x4977c0` (InitMine) at 0x437671; SpawnSuperMine does the
 * same at 0x4378e3, before its `call 0x4977c0` at 0x4378e5.  InitMine does
 * not touch ECX before delegating to InitProjectile (0x454dc0), which does
 * not touch it either before 0x454de9 `mov dword ptr [esi + 8], ecx` - two
 * instructions after the `mov [esi+4],eax` that stamps the class id, i.e.
 * the same +4/+8 pair this function's two walks match on.  See the
 * "active-object layer registry" note: layer +0x4 = class id, +0x1c = next
 * layer, +0x10 = the collection, entries keyed at +0x8 and chained through
 * +0x10; both lists are sorted and terminate on a max-key tail sentinel,
 * which is why an absent key simply falls out as the return value.
 *
 * Evidence that the layer is MINES: `push 0x186a3` feeding InitProjectile
 * occurs at exactly ONE site in the whole image, InitMine 0x4977dc (the
 * other 0x186a3 immediates are avatar LoadSpriteSet ids and cmp operands),
 * and InitMine installs vtable 0x5563f0 with SpawnMine/SpawnSuperMine
 * loading "rayonmine"/"srayonmine".  The constant is hard-coded here, so
 * this function can never search any other layer.
 *
 * Evidence that the argument is a PLAYER SLOT, taken from the producers:
 * SpawnMine's param_4 is `(char)param_1[0xf]`, the detonating projectile's
 * +0x3c owner byte (DetonateShot1_Bullet7.c:581,603), and SpawnSuperMine's
 * single call site pushes `movzx edx, byte ptr [esi + 0x3c]` at 0x49c0cb.
 * Projectile +0x3c is used elsewhere as a per-player index - see
 * ExplodeSuperShot_Bullet2's `g_clientContext + 0x5b83c + *(byte *)(param_1
 * + 0x3c) * 4` and `+ 0x4590c + slot`.  SpawnMine additionally pins it with
 * the signed mod-8 idiom before the call (`and edi,0x80000007 / dec edi /
 * or edi,0xfffffff8 / inc edi`, 0x437621-0x43762d) - the same idiom
 * AdvanceTurnQueue applies to the turn-queue head byte at battle+0x10a8
 * before indexing the per-player 0x224-stride tables at +0xebef4.  NOTE:
 * SpawnSuperMine does NOT mask before the call (0x43789d `mov edi,
 * [esp+0x2c]` / 0x4378a1 `mov eax,edi` / 0x4378a3 `call`); it masks only
 * later, at 0x43798b, for its `mov byte ptr [ebp+0x3c],dl` store - harmless
 * because its caller already hands it an owner byte.  A battle holds at most
 * 8 participants (the reference server's RoomCapacity tops out at
 * `case _4_4 = 8`).
 *
 * The sibling FUN_0043c440 confirms the block is per player: it walks the
 * same in_EAX*8 .. +8 range of the same class-100003 layer and fires vtable
 * slot +0x20 on every entry it finds, and both its call sites pass a player
 * slot - AdvanceTurnQueue at 0x4cf603 (`movzx eax,[esi+0x10a8]` mod 8, the
 * player whose turn ended) and State11_InBattle_ProcessBattleAction at
 * 0x4b6072, whose `movzx esi,bl` carries `bVar16 = *(byte *)(param_2 + 5)`
 * off the action packet - range-checked by that function's own
 * `if (7 < bVar16) goto <default>` a few hundred lines earlier.
 *
 * Evidence that -1 means "this player already has 8 live mines": both
 * callers wrap the call in `while (result == -1) { FUN_00437500(slot in
 * EDX); retry; }` (0x43763b-0x437653, 0x4378aa-0x4378c3), and FUN_00437500
 * scans the same eight keys, keeps the entry with the smallest +0x3f9c
 * (0x43755b-0x437567), fires vtable +0x20 (0x4375be), unlinks it from the
 * +0xc/+0x10 list (0x4375c1-0x4375d0) and invokes the scalar-deleting
 * destructor (0x4375d5 `push 1 / call [edx]`).  Mine +0x3f9c is stamped in
 * SpawnMine at 0x437713 from PeekPacketChecksumState(g_clientContext +
 * 0xeba98), the turn counter BeginNewTurn seeds and increments
 * (BeginNewTurn.c:76,136), so the minimum is the OLDEST mine.  The loop only
 * terminates because eviction frees a key - the callers asserting exactly
 * this contract: the pair enforces a hard cap of 8 simultaneous mines per
 * player.
 *
 * `regEax` keeps its recovered-register name per the tree's convention
 * (cf. HandleTurnTimeoutSlot, BuildRotatedSpriteQuad); it is the player
 * slot.  Note for whoever touches SpawnMine/SpawnSuperMine next: the C port
 * calls `InitMine(pvVar3)` against a `undefined4 * InitMine();` prototype,
 * so this key is dropped on the floor and ported mines are constructed with
 * a garbage +0x8 registry key.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output beyond the naming -
 * not hand-verified. See src/README.md's "Raw/verbatim ports" section.
 *
 * DROPPED REGISTER RECOVERED (2026-08-27): in_EAX is param_4 at all four
 * call sites.  SpawnMine's `dec edi / or edi,0xfffffff8 / inc edi` at
 * 0x437629 is character for character its own `param_4 = (param_4 - 1 |
 * 0xfffffff8) + 1;`, so edi is param_4 there; SpawnSuperMine loads edi from
 * [esp+0x2c], which under its SEH triple plus four prologue saves is E+0x10,
 * i.e. param_4 -- witnessed by the same prologue's `mov eax,[esp+0x10]` =
 * E+4 = param_1, the argument its PeekPacketChecksumBool(param_1 + 4) on the
 * next line takes.  Both callers then do `mov eax,edi` immediately before
 * each call, including the retry inside the `while (iVar2 == -1)` loop.
 *
 * 60b748e6 - the new note was appended without removing the old header's
 * copy.  Keep one.)
 */
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

