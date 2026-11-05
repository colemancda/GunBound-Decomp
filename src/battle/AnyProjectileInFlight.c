/* AnyProjectileInFlight - 0x0043c820 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_0043c820 mean this function.)
 *
 * NAMED (2026-11-05), LIKELY. Evidence from outside the body: it scans the
 * battle entity registry DAT_006a7f8c for the layer with class id 0x186a2
 * (100002), which the layer map identifies as the projectiles (about 55
 * constructors, SpawnPrimaryShot and every bullet class), and returns
 * whether that layer's list holds anything (first element not the list
 * head); a missing layer gives false. The callers use it as a gate on the
 * mobile's pending state string at mobile + 0xbffa: SimulateMobileFrame
 * (and its C++ twin in Mobile.cpp) acts on that string only when no
 * projectile is left, and ProcessBattleAction tests it three times and,
 * when it returns true, writes the "ifire" state string into the same field
 * and returns. The name says in flight because registration in the layer
 * lasts from spawn to detonation; that lifetime is the layer map's, not
 * shown by this function.
 */
#include "ghidra_types.h"


uint AnyProjectileInFlight(void)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = *(uint *)(*(int *)(&DAT_006a7f8c + g_clientContext) + 0x1c);
  uVar2 = *(uint *)(uVar1 + 4);
  while( true ) {
    if (0x186a2 < uVar2) {
      return uVar1 & 0xffffff00;
    }
    if (uVar2 == 0x186a2) break;
    uVar1 = *(uint *)(uVar1 + 0x1c);
    uVar2 = *(uint *)(uVar1 + 4);
  }
  return CONCAT31((int3)(uVar1 >> 8),*(uint *)(uVar1 + 0x10) != uVar1);
}

