/* StringMap_RemoveAll_28 - 0x004fee20 in the original binary.
 *
 * NAMED (2026-10-29): ATL7 CAtlMap::RemoveAll for the 0x28-node maps -
 * the same member as StringMap_RemoveAll_1c, with FreeNode and PickSize
 * inlined: raise the lock count at map+0x20 (0x4fee29), walk every bin
 * retiring nodes by their m_pNext at +0x20 (0x4fee63) onto m_pFree at
 * +0x2c, delete[] the bins (_free 0x525421), InitHashTable(PickSize(0),
 * false) when unlocked (0x4fef2e / 0x4fef35), free the plex chain at
 * +0x28, and drop the lock count (0x4fef5b).
 *
 * The instantiation is fixed by the callee: the inlined FreeNode's
 * rehash arm calls StringMap_Rehash_28 (0x4feecd), the rehash
 * StringMap_Insert_28 uses.  The one caller is DestroyCommP2POwner
 * (0x4fd334, map at +0x1ac0), right after it clears the 0x1c map at
 * +0x1af0 with StringMap_RemoveAll_1c.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * HashMap_PickSize ARGS RECOVERED (2026-10-29): the call at 0x4fef2e
 * passed only a literal 0.  ECX = `mov ecx,esi` (the map), EAX = 0 (`xor
 * eax,eax`): RemoveAll's `InitHashTable(PickSize(0), false)`; witness: the
 * same esi is pushed as HashMap_InitHashTable's map right after (call at
 * 0x4fef35).  Now passes (regEsi, 0).
 *
 * INLINED PickSize RECOVERED (2026-10-30): the inlined FreeNode's
 * threshold arm computed its bin count through FloatToInt64(), which
 * converts an uninitialised x87 ST0.  The disassembly is CAtlMap::PickSize
 * inlined: EAX = the decremented m_nElements (`mov eax,edx`, also stored to
 * [esi+4] - this port's iVar3 - 1U), `fild` of it at 0x4fee8a, the UINT
 * fix-up `fadd [0x557fac]` (4294967296.0f) at 0x4fee90, `fdiv [esi+0xc]`
 * (m_fOptimalLoad) at 0x4fee96, and _ftol2 (0x53753c, truncating) at
 * 0x4fee99.  Spelled (uint)(longlong)((double)n / m_fOptimalLoad), as in
 * HashMap_PickSize itself.
 */
#include "ghidra_types.h"


/* WARNING: Removing unreachable block (ram,0x004feea3) */

void StringMap_RemoveAll_28(int *regEsi)

{
  uint *puVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  int *piVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  uint local_8;
  
  regEsi[8] = regEsi[8] + 1;
  if ((*regEsi != 0) && (local_8 = 0, regEsi[2] != 0)) {
    do {
      iVar6 = *(int *)(*regEsi + local_8 * 4);
      while (iVar6 != 0) {
        iVar2 = *(int *)(iVar6 + 0x20);
        *(int *)(iVar6 + 0x20) = regEsi[0xb];
        iVar3 = regEsi[1];
        regEsi[0xb] = iVar6;
        regEsi[1] = iVar3 - 1U;
        if ((iVar3 - 1U < (uint)regEsi[7]) && (regEsi[8] == 0)) {
          /* inlined PickSize(m_nElements), 0x4fee8a-0x4fee99 */
          uVar5 = (uint)(longlong)((double)(iVar3 - 1U) / (double)*(float *)(regEsi + 3));
          iVar6 = 0;
          if (0x11 < uVar5) {
            do {
              puVar1 = &DAT_00557a44 + iVar6;
              iVar6 = iVar6 + 1;
            } while (*puVar1 < uVar5);
          }
          uVar7 = (&DAT_00557a40)[iVar6];
          if ((&DAT_00557a40)[iVar6] == 0xffffffff) {
            uVar7 = uVar5;
          }
          StringMap_Rehash_28(regEsi,uVar7);
        }
        iVar6 = iVar2;
        if (regEsi[1] == 0) {
          regEsi[0xb] = 0;
          piVar8 = (int *)regEsi[10];
          if ((int *)regEsi[10] != (int *)0x0) {
            do {
              piVar4 = (int *)*piVar8;
              _free(piVar8);
              piVar8 = piVar4;
            } while (piVar4 != (int *)0x0);
            regEsi[10] = 0;
          }
        }
      }
      local_8 = local_8 + 1;
    } while (local_8 < (uint)regEsi[2]);
  }
  _free((void *)*regEsi);
  *regEsi = 0;
  regEsi[1] = 0;
  if (regEsi[8] == 0) {
    uVar10 = 0;
    uVar9 = HashMap_PickSize(regEsi,0);
    HashMap_InitHashTable(regEsi,uVar9,uVar10);
  }
  regEsi[0xb] = 0;
  piVar8 = (int *)regEsi[10];
  if ((int *)regEsi[10] != (int *)0x0) {
    do {
      piVar4 = (int *)*piVar8;
      _free(piVar8);
      piVar8 = piVar4;
    } while (piVar4 != (int *)0x0);
    regEsi[10] = 0;
  }
  regEsi[8] = regEsi[8] + -1;
  return;
}

