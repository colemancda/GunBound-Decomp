/* HashMap_PickSize - 0x00500e30 in the original binary.
 *
 * NAMED (2026-10-29): ATL7 CAtlMap::PickSize(nElements), the bin-count
 * chooser every CAtlMap instantiation in the image shares (identical
 * code, one copy - hence the generic HashMap_ prefix and no suffix, as
 * on HashMap_InitHashTable):
 *
 *   nBins = (size_t)(nElements / m_fOptimalLoad)   fild eax; fdiv [ecx+0xc]
 *   if (nBins > UINT_MAX) nBins = UINT_MAX          cmp eax,-1
 *   while (nBins > s_anPrimes[iPrime]) iPrime++     0x500e60 loop
 *   return s_anPrimes[iPrime] == UINT(-1)
 *          ? nBins : s_anPrimes[iPrime]             cmp ecx,-1 at 0x500e73
 *
 * Two facts from outside the body pin it.  The table at 0x557850 is
 * atlcoll.h's s_anPrimes verbatim - 17, 23, 29, 37, 41, 53, 67, 83, 103,
 * 131, 163, 211, 257, 331, 409, 521, 647, 821, 1031, 1291, ... - and
 * +0xc of the object in ECX is m_fOptimalLoad in the member layout
 * HashMap_Construct (0x4fe420) pins.  And all 29 binary call sites use it
 * the way CAtlMap does: with ECX = the map, either feeding its result
 * straight to a Rehash (the NewNode/FreeNode threshold arms of every
 * instantiation, and the nBins == 0 arm inside each Rehash, with EAX =
 * [map+4] = m_nElements), or with EAX = 0 ahead of HashMap_InitHashTable
 * (8 sites, among them the named RemoveAll members: RemoveAll's
 * `InitHashTable(PickSize(0), false)`).
 *
 * The real convention is ECX = map, EAX = nElements, plain `ret`.
 *
 * MAP AND nElements PROMOTED (2026-10-29).  The port declared it (void)
 * with both reads folded into Ghidra's FloatToInt64 call, which takes its
 * operand from an uninitialised x87 ST0, and the K&R prototype let 8 call
 * sites pass a bare 0 and 21 pass nothing.  It is now
 * (int *param_1, uint regEax): the map first (erased-__thiscall `this`,
 * ECX) and nElements trailing (EAX), and the division is spelled out:
 * `fild` of EAX with the unsigned fix-up `fadd [0x557fac]` (= 4294967296.0f)
 * at 0x500e3b, `fdiv dword [ecx+0xc]` (m_fOptimalLoad) at 0x500e41, then
 * _ftol (0x53753c) keeping the low dword.  All 29 binary sites were read
 * one by one (each C caller holds exactly one, so the containing function
 * pairs them); ECX is always the map register that is pushed to the
 * Rehash / HashMap_InitHashTable call directly after, and EAX is
 *   - 0 (`xor eax,eax`) at the 8 RemoveAll-shaped sites 0x404bfc,
 *     0x4155cc, 0x41566c, 0x4fef2e, 0x4ff0ee, 0x5001af, 0x5007ff, 0x500b2e;
 *   - [map+4] (m_nElements) at the 7 Rehash nBins == 0 arms 0x405185,
 *     0x409e55, 0x500335, 0x500475, 0x500d15, 0x5010a5, 0x501255;
 *   - the decremented count (`dec edx; mov eax,edx`) at the 7 FreeNode
 *     arms 0x4052bc, 0x409f8c, 0x4156fa, 0x500672, 0x500ead, 0x5011e5,
 *     0x501382;
 *   - the incremented [map+4] at the 7 NewNode arms 0x409dcd, 0x426a1b,
 *     0x500629, 0x5008db, 0x5014ef, 0x5015e2, 0x504529.
 * Each caller's header cites its own site.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


/* WARNING: Removing unreachable block (ram,0x00500e4e) */

uint HashMap_PickSize(int *param_1,uint regEax)

{
  uint *puVar1;
  uint uVar2;
  int iVar3;
  
  /* nBins = (size_t)(nElements / m_fOptimalLoad), 0x500e31-0x500e44 */
  uVar2 = (uint)(longlong)((double)regEax / (double)*(float *)(param_1 + 3));
  iVar3 = 0;
  if (0x11 < uVar2) {
    do {
      puVar1 = &DAT_00557854 + iVar3;
      iVar3 = iVar3 + 1;
    } while (*puVar1 < uVar2);
  }
  if ((&DAT_00557850)[iVar3] != 0xffffffff) {
    uVar2 = (&DAT_00557850)[iVar3];
  }
  return uVar2;
}

