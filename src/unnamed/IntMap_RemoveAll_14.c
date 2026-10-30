/* IntMap_RemoveAll_14 - 0x00500a20 in the original binary.
 *
 * NAMED (2026-10-29): ATL7 CAtlMap::RemoveAll for the 0x14-node integer
 * maps - the same member as IntMap_RemoveAll_1768 and
 * HashMap_RemoveAll_2c, with FreeNode and PickSize inlined: raise the
 * lock count at map+0x20 (0x500a29), walk every bin retiring nodes by
 * their m_pNext at +0xc (0x500a63) onto m_pFree at +0x2c, delete[] the
 * bins (_free 0x525421), InitHashTable(PickSize(0), false) when
 * unlocked (0x500b2e / 0x500b35), free the plex chain at +0x28, and drop
 * the lock count again (0x500b5b).
 *
 * The instantiation is fixed by the callee: the inlined FreeNode's
 * rehash arm calls IntMap_Rehash_14 (0x500acd), the rehash that
 * IntMap_Insert_14 and IntMap_FreeNode_14 share.  The map is the one at
 * +0x20 of the 0x90-byte object whose +0x50 map IntMap_RemoveAll_1768
 * clears, and both callers (0x4fe98c, 0x4ff231) clear the two maps
 * together.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * ESI RECOVERED (2026-08-25): the map at +0x20 of the same 0x90-byte object
 * IntMap_RemoveAll_1768 clears at +0x50 -- `add esi,0x20` at 0x4ff22e and
 * `lea esi,[esp+0x4c]` (frame -0x7c = -0x9c + 0x20) at 0x4fe988.
 *
 * HashMap_PickSize ARGS RECOVERED (2026-10-29): the call at 0x500b2e
 * passed only a literal 0.  ECX = `mov ecx,esi` (the map), EAX = 0 (`xor
 * eax,eax`): RemoveAll's `InitHashTable(PickSize(0), false)`; witness: the
 * same esi is pushed as HashMap_InitHashTable's map right after (call at
 * 0x500b35).  Now passes (regEsi, 0).
 *
 * INLINED PickSize RECOVERED (2026-10-30): the inlined FreeNode's
 * threshold arm computed its bin count through FloatToInt64(), which
 * converts an uninitialised x87 ST0.  The disassembly is CAtlMap::PickSize
 * inlined: EAX = the decremented m_nElements (`mov eax,edx`, also stored to
 * [esi+4] - this port's iVar3 - 1U), `fild` of it at 0x500a8a, the UINT
 * fix-up `fadd [0x557fac]` (4294967296.0f) at 0x500a90, `fdiv [esi+0xc]`
 * (m_fOptimalLoad) at 0x500a96, and _ftol2 (0x53753c, truncating) at
 * 0x500a99.  Spelled (uint)(longlong)((double)n / m_fOptimalLoad), as in
 * HashMap_PickSize itself.
 */
#include "ghidra_types.h"


/* WARNING: Removing unreachable block (ram,0x00500aa3) */

void IntMap_RemoveAll_14(int *regEsi)

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
        iVar2 = *(int *)(iVar6 + 0xc);
        *(int *)(iVar6 + 0xc) = regEsi[0xb];
        iVar3 = regEsi[1];
        regEsi[0xb] = iVar6;
        regEsi[1] = iVar3 - 1U;
        if ((iVar3 - 1U < (uint)regEsi[7]) && (regEsi[8] == 0)) {
          /* inlined PickSize(m_nElements), 0x500a8a-0x500a99 */
          uVar5 = (uint)(longlong)((double)(iVar3 - 1U) / (double)*(float *)(regEsi + 3));
          iVar6 = 0;
          if (0x11 < uVar5) {
            do {
              puVar1 = &DAT_00557664 + iVar6;
              iVar6 = iVar6 + 1;
            } while (*puVar1 < uVar5);
          }
          uVar7 = (&DAT_00557660)[iVar6];
          if ((&DAT_00557660)[iVar6] == 0xffffffff) {
            uVar7 = uVar5;
          }
          IntMap_Rehash_14(regEsi,uVar7);
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

