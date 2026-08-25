/* FUN_004024f0 - 0x004024f0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED REGISTER RECOVERED (2026-08-24): EAX is the second object handed
 * on to FUN_004025e0(param_1, regEax).  Five call sites in three callers:
 *   DispatchDirectLinkPacket (2)  param_3 -- [esp+0x144] on the four-saved-register path,
 *                     the same +8 slot the FUN_00401ee0 sites read as
 *                     [esp+0x140] on the three-register path
 *   FUN_00402720 (2)  param_2 -- loaded into EDI in the prologue.  One site
 *                     reads it from the stack directly; the other is a cold
 *                     block after the epilogue (the `+0x1bdc` vtable branch)
 *                     entered ONLY by `je 0x402806` at 0x402750, which is
 *                     before both later rewrites of EDI, so EDI there is
 *                     still the prologue's param_2.
 *   FUN_00402900 (1)  param_2 -- the same cold-block shape, EBP this time,
 *                     entered only by `je 0x4029d0` at 0x40292e, before the
 *                     one rewrite at 0x402971.
 * The two cold-block sites are exactly the shape a linear trace calls
 * unsafe: the rewrites exist, but not on the path.
 */
#include "ghidra_types.h"


void FUN_004024f0(undefined4 param_1,char *param_2,undefined4 regEax)

{
  /* Ghidra artifact: raw stack reference the decompiler could not
   * map to a named local; declared so the raw port parses. */
  undefined stack0xffffff7f;
  char cVar1;
  undefined2 *puVar2;
  int iVar3;
  char *pcVar4;
  uint uVar5;
  char *pcVar6;
  undefined2 *puVar7;
  char *pcVar8;
  char local_80 [128];
  
  pcVar4 = (char *)(g_clientContext + 0x23330);
  iVar3 = -(int)pcVar4;
  do {
    cVar1 = *pcVar4;
    pcVar4[(int)(local_80 + iVar3)] = cVar1;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  puVar2 = (undefined2 *)&stack0xffffff7f;
  do {
    puVar7 = puVar2;
    puVar2 = (undefined2 *)((int)puVar7 + 1);
  } while (*(char *)((int)puVar7 + 1) != '\0');
  *(undefined2 *)((int)puVar7 + 1) = DAT_00551e34;
  *(undefined1 *)((int)puVar7 + 3) = DAT_00551e36;
  pcVar4 = param_2;
  do {
    cVar1 = *pcVar4;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  pcVar8 = &stack0xffffff7f;
  do {
    pcVar6 = pcVar8 + 1;
    pcVar8 = pcVar8 + 1;
  } while (*pcVar6 != '\0');
  pcVar6 = param_2;
  for (uVar5 = (uint)((int)pcVar4 - (int)param_2) >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined4 *)pcVar8 = *(undefined4 *)pcVar6;
    pcVar6 = pcVar6 + 4;
    pcVar8 = pcVar8 + 4;
  }
  for (uVar5 = (int)pcVar4 - (int)param_2 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *pcVar8 = *pcVar6;
    pcVar6 = pcVar6 + 1;
    pcVar8 = pcVar8 + 1;
  }
  FUN_00426120(local_80);
  iVar3 = PanelManager_FindByName((int)&g_uiPanelManager);
  if (iVar3 == 0) {
    FUN_004025e0(param_1,regEax);
    iVar3 = PanelManager_FindByName((int)&g_uiPanelManager);
    if (iVar3 == 0) {
      return;
    }
    pcVar4 = param_2;
    do {
      cVar1 = *pcVar4;
      pcVar4 = pcVar4 + 1;
    } while (cVar1 != '\0');
    iVar3 = (int)pcVar4 - (int)(param_2 + 1);
  }
  else {
    pcVar4 = param_2;
    do {
      cVar1 = *pcVar4;
      pcVar4 = pcVar4 + 1;
    } while (cVar1 != '\0');
    iVar3 = (int)pcVar4 - (int)(param_2 + 1);
  }
  FUN_00505900(param_2,iVar3);
  return;
}

