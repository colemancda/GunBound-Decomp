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
 * The real convention is ECX = map, EAX = nElements, plain `ret`.  The
 * port still declares it (void) with the reads folded into Ghidra's
 * FloatToInt64 call, and the prototype is left K&R: the C call sites are
 * mixed (8 pass a literal 0, 21 pass nothing), and recovering the two
 * registers at all 29 is a separate job.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 */
#include "ghidra_types.h"


/* WARNING: Removing unreachable block (ram,0x00500e4e) */

uint HashMap_PickSize(void)

{
  uint *puVar1;
  uint uVar2;
  int iVar3;
  
  uVar2 = FloatToInt64();
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

