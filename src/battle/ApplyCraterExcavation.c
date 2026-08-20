/* ApplyCraterExcavation - 0x004e4970 in the original binary.
 *
 * DROPPED REGISTER ARGUMENTS, RECOVERED 2026-08-20.  Ghidra modelled the
 * eight stack arguments and missed all three register ones, so terrainCtx,
 * impactX and impactY were reading whatever happened to be in EAX/EBX/EDI -
 * and terrainCtx is a BASE POINTER that this function writes through at
 * +0x854/+0x858, so the port was doing a wild store on every crater.
 *
 * All 23 direct call sites in the original were disassembled (byte-scan for
 * E8 rel32 targeting 0x4e4970, since a linear sweep of .text desyncs), and
 * they agree completely:
 *
 *   EAX  mov eax,[0x5b3484] / add eax,0x6a7708   - identical at all 23, i.e.
 *        g_clientContext + 0x6a7708, which these same callers already spell
 *        `&DAT_006a7708 + g_clientContext` when they call
 *        RebuildTerrainColumnCache one line later.
 *   EBX  the return of a PeekPacketChecksumState of the object's +0xf54
 *   EDI  the return of a PeekPacketChecksumState of the object's +0x1178
 *
 * +0xf54 and +0x1178 are the projectile X and Y that IsProjectileInBounds
 * bounds-checks, which is corroborated by this function's own body: impactX
 * is compared against g_nCameraBoundX and impactY against g_nCameraBoundY,
 * and CarveTerrainCrater/SpawnCraterDebris take them in that order.
 *
 * Worked example (DetonateProjectile, call at 0x457b38): `add ebx,0xf54 / mov
 * eax,ebx / call 0x40a2e0 / mov ebx,eax` is the X peek feeding EBX, and `mov
 * edi,[esp+0x50]` normalises to Ghidra local iStack_ac8 - which that file
 * assigns from the +0x45e (= 0x1178 in int* units) peek.  The calibration is
 * fixed by two independent hits: the argument at [esp+0x2c] normalises to
 * 0xadc and the file passes uStack_adc, and [esp+0x38] normalises to 0xad0
 * and the file passes apuStack_ad0[0].
 *
 * Every caller ends with the same three peeks in the same order (+0x24c0,
 * then Y, then X), and the X one had its result discarded everywhere - which
 * is exactly the dropped-argument shape DetonateProjectile.c's header flagged
 * as "a dropped-arg fix for a different sweep".
 *
 * CONFIRMED AT THE ENTRY ITSELF (0x4e4970):
 *     test ebx,ebx / jl  <exit>          impactX < 0
 *     mov  eax,[0x5b3484]                g_clientContext
 *     cmp  ebx,[eax+0x6a7720] / jge      against g_nCameraBoundX
 *     test edi,edi / jl  <exit>          impactY < 0
 *     cmp  edi,[eax+0x6a7724] / jge      against g_nCameraBoundY
 *     mov  esi,eax  (at 0x4e4978, of the INCOMING eax)  -> the base later
 *                   written as [esi+0x854]/[esi+0x858]
 * so all three registers are read before being written, with EBX as X and
 * EDI as Y, matching the caller-side evidence in both role and order.
 *
 * CALLING CONVENTION: the original ends `ret 0x20`, i.e. __stdcall with
 * exactly EIGHT stack arguments plus the three register ones. Note what that
 * means for the retn census (tools/retn_signature_audit.py): before this fix
 * the declared list was 8 and 0x20/4 is 8, so the census saw a MATCH and
 * would never have flagged this function. Register arguments are invisible to
 * a ret-N comparison - which is exactly why the caller-side corroboration
 * pass (tools/sweep_callsite_corroborate.py) exists, and why its output is
 * the right worklist for this class rather than the census.
 *
 * The three recovered arguments are appended as trailing parameters, the
 * established shape in this tree (MSVC cannot express an EAX/EBX/EDI
 * argument). As with the other promotions, that is self-consistent under
 * cdecl-by-name linking but no longer byte-faithful for those three slots.
 *
 * Otherwise a raw/near-verbatim port of Ghidra's decompiler output, not
 * hand-verified. See src/README.md's "Raw/verbatim ports" section.
 */
#include "ghidra_types.h"


void ApplyCraterExcavation(int param_1,int param_2,int param_3,undefined4 param_4,undefined4 param_5,
                 undefined4 param_6,undefined4 param_7,undefined4 param_8,
                 int terrainCtx,int impactX,int impactY)

{
  int *piVar1;
  undefined4 *puVar2;
  int iVar3;
  bool bVar4;
  
  if ((((impactX < 0) || (*(int *)(&g_nCameraBoundX + g_clientContext) <= impactX)) || (impactY < 0)
      ) || (*(int *)(&g_nCameraBoundY + g_clientContext) <= impactY)) {
    *(undefined4 *)(terrainCtx + 0x858) = 0xffffffff;
    *(undefined4 *)(terrainCtx + 0x854) = 0xffffffff;
  }
  else {
    iVar3 = PeekChecksumStateUnderLock((uint)*(byte *)(g_clientContext + 0x475c4) * 0x7d28 + 0x1a1f48 + g_clientContext)
    ;
    if (iVar3 == 0) {
      CarveTerrainCrater(impactX,impactY,param_4);
      *(int *)(terrainCtx + 0x858) = param_1 / 2 + impactY;
      *(int *)(terrainCtx + 0x854) = impactY - param_1 / 2;
      SpawnCraterDebris(&DAT_006a7f70 + g_clientContext,impactX,impactY,param_1,param_7,param_8);
      if (DAT_0079352a != '\0') {
        QueueBroadcastEvent(0xf004);
        (&g_abBroadcastEventBuffer)[g_dwBroadcastEventCursor] = 0;
        param_6 = param_4;
        param_3 = param_1;
LAB_004e4ac8:
        piVar1 = (int *)(&DAT_00e9aacd + g_dwBroadcastEventCursor);
        g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 1;
        *piVar1 = impactX;
        piVar1 = (int *)(&DAT_00e9aad0 + g_dwBroadcastEventCursor);
        g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 4;
        *piVar1 = impactY;
        piVar1 = (int *)(&DAT_00e9aad0 + g_dwBroadcastEventCursor);
        g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 4;
        *piVar1 = param_3;
        puVar2 = (undefined4 *)(&DAT_00e9aad0 + g_dwBroadcastEventCursor);
        g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 4;
        *puVar2 = param_6;
        g_dwBroadcastEventCursor = g_dwBroadcastEventCursor + 4;
        BroadcastQueuedEvent();
        return;
      }
    }
    else if (iVar3 == 1) {
      CarveTerrainCrater(impactX,impactY,param_5);
      SpawnCraterDebris(&DAT_006a7f70 + g_clientContext,impactX,impactY,param_2,param_7,param_8);
      *(int *)(terrainCtx + 0x858) = param_2 / 2 + impactY;
      bVar4 = DAT_0079352a != '\0';
      *(int *)(terrainCtx + 0x854) = impactY - param_2 / 2;
      if (bVar4) {
        QueueBroadcastEvent(0xf004);
        (&g_abBroadcastEventBuffer)[g_dwBroadcastEventCursor] = 1;
        param_6 = param_5;
        param_3 = param_2;
        goto LAB_004e4ac8;
      }
    }
    else if (iVar3 == 2) {
      CarveTerrainCrater(impactX,impactY,param_6);
      SpawnCraterDebris(&DAT_006a7f70 + g_clientContext,impactX,impactY,param_3,param_7,param_8);
      *(int *)(terrainCtx + 0x858) = param_3 / 2 + impactY;
      bVar4 = DAT_0079352a != '\0';
      *(int *)(terrainCtx + 0x854) = impactY - param_3 / 2;
      if (bVar4) {
        QueueBroadcastEvent(0xf004);
        (&g_abBroadcastEventBuffer)[g_dwBroadcastEventCursor] = 2;
        goto LAB_004e4ac8;
      }
    }
  }
  return;
}

