/* InitTornadoHazard - 0x004ac5a0 in the original binary.
 *
 * RENAMED (2026-07-16, from FUN_004ac5a0): constructor for the Tornado
 * terrain-hazard object. Sets the vtable (PTR_FUN_005565e4), the
 * active-object layer key (param_1[1] = 500), and the standard node
 * links. Called only by SpawnTornadoHazard. Identity CONFIRMED:
 * RenderWeatherHazards maps layer 500 -> s_TornadoTexture. Raw/near-
 * verbatim Ghidra body - see src/README.md.
 *
 * OBJECT LAYOUT & vtable (decoded 2026-07-16, angr; object = 0x6a8 bytes):
 *   +0x00  vtable ptr (PTR_FUN_005565e4)
 *   +0x04  active-object layer key = 0x1f4 (500) -> RenderWeatherHazards
 *   +0x08..+0x2c  node header (list links / status; +0x14/+0x15 = the
 *          dead/finished flags the list checks)
 *   +0x38  guard cell: WORLD-X position (spawn param_2)
 *   +0x25c guard cell: WIDTH/strength (spawn param_3)
 *   +0x480 animation frame counter (zeroed by spawner; inc'd per tick)
 *   +0x484 guard cell: LIFETIME countdown ticks (spawn param_4=10000)
 * This ctor only zero-inits the three guard cells (+0x38/+0x25c/+0x484)
 * and the node header; it creates NO sub-sprite list (+0x10 = 0). All
 * visible geometry is produced per-frame by the vtable methods:
 *   slot2 (+0x08) 0x4ac750 = tick: `inc [this+0x480]; ret`
 *   slot3 (+0x0c) 0x4ac760 = RENDER: screenX = pos(+0x38) - cameraX
 *          (g_clientContext+0x6a7710) + 400; width from strength(+0x25c);
 *          reads frame(+0x480) -> swirl rotation (frame%64)*-6 deg and
 *          sprite index frame%8; draws s_TornadoTexture, clamped to
 *          screen bounds 0x793530/0x56df30.
 *   slot4 (+0x10) 0x4acc90 = lifetime tick: dec +0x484; if <0 set +0x14=1.
 * Firewall (InitFirewallHazard) / Lightning (InitLightningHazard) are the
 * same template with every cell offset +4 (extra InitGuardedBool field),
 * so their frame counter is at +0x484 and lifetime at +0x488; their
 * render methods 0x471550 / 0x46e020 use animation stride frame*0x6c.
 */
#include "ghidra_types.h"


undefined4 * InitTornadoHazard(undefined4 *param_1)

{
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_c = *unaff_FS_OFFSET;
  puStack_8 = &LAB_00537d41;
  *unaff_FS_OFFSET = &local_c;
  param_1[1] = 500;
  param_1[2] = 0xffffffff;
  param_1[3] = 0;
  param_1[4] = 0;
  *(undefined1 *)(param_1 + 5) = 0;
  *(undefined1 *)((int)param_1 + 0x15) = 0;
  param_1[6] = 0xffffffff;
  param_1[7] = 0;
  *(undefined1 *)(param_1 + 8) = 0;
  param_1[10] = 0;
  param_1[0xb] = 0;
  param_1[9] = 0xffffffff;
  local_4 = 0;
  *param_1 = &PTR_FUN_005565e4;
  *(undefined1 *)(param_1 + 0x96) = 0;
  param_1[0x13] = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x4ac600
   * (`lea edi,[esi + 0x38]`, esi = this file's own param_1): the cell is
   * param_1+0x38; tableHandle(+0x14)=param_1+0x4c (== param_1[0x13],
   * `undefined4 *` scales by 4) is zeroed immediately above. `param_1` is
   * `undefined4 *`, so byte offsets use `(int)param_1 + N`. Matches the
   * identical constructor idiom in InitFirewallHazard.c. See
   * tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((int)param_1 + 0x38, 0);
  SUBFIELD(local_4,0,undefined1) = 1;
  *(undefined1 *)(param_1 + 0x11f) = 0;
  param_1[0x9c] = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x4ac61a
   * (`lea edi,[esi + 0x25c]`, esi = param_1): cell is param_1+0x25c;
   * tableHandle(+0x14)=param_1+0x270 (== param_1[0x9c]) is zeroed just
   * above. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((int)param_1 + 0x25c, 0);
  local_4 = CONCAT31(SUBFIELD(local_4,1,undefined3),2);
  *(undefined1 *)(param_1 + 0x1a9) = 0;
  param_1[0x126] = 0;
  /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at 0x4ac634
   * (`lea edi,[esi + 0x484]`, esi = param_1): cell is param_1+0x484;
   * tableHandle(+0x14)=param_1+0x498 (== param_1[0x126]) is zeroed just
   * above. See tools/encodeoutgoingpacketfield_sites.json. */
  EncodeOutgoingPacketField((int)param_1 + 0x484, 0);
  *unaff_FS_OFFSET = local_c;
  return param_1;
}

