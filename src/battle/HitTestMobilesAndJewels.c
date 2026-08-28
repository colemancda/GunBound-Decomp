/* HitTestMobilesAndJewels - 0x00450e10 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED (2026-08-28): does the point (x, y) hit any player mobile or
 * any jewel. The two layer keys are the whole claim and both are
 * pinned by the registry map (docs + ActiveObjects.h): 100001 is the
 * player-mobile layer and 0x186a6 = 100006 the jewel layer. The
 * per-object probes agree from inside their own already-documented
 * cells: FUN_0045d640 works the mobile position guard block (EDI +
 * 0x243 ints = +0x90c, the mobile X the registry note pins), and
 * FUN_00478a80 subtracts the jewel X/Y guard cells +0x25c/+0x480 that
 * HitTestJewel's header established. Callers are the per-step
 * collision probe of projectile integration: eleven sites across the
 * six Simulate* files (plus the Projectile.cpp twin), and the
 * column-scan loops in FUN_00458920 / FUN_00458a00 / FUN_004e4fe0.
 * Not named HitTestEntities: mines, projectiles and the other layer
 * classes are deliberately NOT probed here.
 *
 * (The note below predates the 2026-08-28 renames: FUN_004f2f90 is now
 * FindActiveObjectLayer.)
 *
 * DROPPED-REG FIX (2026-08-28): a point-vs-entities hit test. param_1
 * is the Y (bounded by g_nCameraBoundY), regEbx the X (bounded by
 * g_nCameraBoundX), and regEax the active-object layer registry at
 * &DAT_006a7f88 + g_clientContext - UNIFORM at all fifteen call sites,
 * every one a `lea`, which callsite_regs.py renders identically to the
 * load it is not. The body looks up class 100001 (the mobiles) and
 * probes each with FUN_0045d640(x,y), then class 0x186a6 with
 * FUN_00478a80(node,x,y); the two class keys were dropped along with
 * the registry because the FUN_004f2f90 lookups compiled argless.
 *
 * The fifteen X values were paired per site: in the six projectile
 * Simulate* files both the X and Y loads sit at zero pending depth, so
 * the Y slot the C already names anchors the frame base and the X is
 * the slot at the load's own offset - each file's two sites confirm one
 * base twice. In FUN_00458920 / FUN_00458a00 / FUN_004e4fe0 the X is
 * the cursor variable their own terrain-pixel guard indexes (the
 * un-multiplied operand of pitch*row + base + column).
 */
#include "ghidra_types.h"


undefined4 HitTestMobilesAndJewels(int param_1,int regEax,int regEbx)

{
  char cVar1;
  int iVar2;
  int unaff_EBX = regEbx;
  
  if ((((-1 < unaff_EBX) && (unaff_EBX < *(int *)(&g_nCameraBoundX + g_clientContext))) && (-1 < param_1))
     && (param_1 < *(int *)(&g_nCameraBoundY + g_clientContext))) {
    iVar2 = FindActiveObjectLayer(0,100001,regEax);
    if (iVar2 != 0) {
      iVar2 = *(int *)(iVar2 + 0x10);
      cVar1 = *(char *)(iVar2 + 0x15);
      while (cVar1 == '\0') {
        cVar1 = FUN_0045d640(unaff_EBX,param_1);
        if (cVar1 != '\0') {
          return 1;
        }
        iVar2 = *(int *)(iVar2 + 0x10);
        cVar1 = *(char *)(iVar2 + 0x15);
      }
    }
    iVar2 = FindActiveObjectLayer(0,0x186a6,regEax);
    if (iVar2 != 0) {
      iVar2 = *(int *)(iVar2 + 0x10);
      cVar1 = *(char *)(iVar2 + 0x15);
      while (cVar1 == '\0') {
        cVar1 = FUN_00478a80(iVar2,unaff_EBX,param_1);
        if (cVar1 != '\0') {
          return 1;
        }
        iVar2 = *(int *)(iVar2 + 0x10);
        cVar1 = *(char *)(iVar2 + 0x15);
      }
    }
    return 0;
  }
  return 0;
}

