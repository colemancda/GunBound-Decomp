/* IntMap_GetStartPosition_14 - 0x00500b70 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * (Notes in other files that still say FUN_00500b70 mean this function.)
 *
 * NAMED (2026-11-04), CERTAIN. ATL7 CAtlMap::GetStartPosition: NULL when
 * m_nElements (+4) is zero, otherwise the first non-empty bin of m_ppBins
 * (+0), scanning m_nBins (+8). The map arrives in ECX. Its only caller is
 * the first call of CommP2PReceiveDatagram's enumerate-and-expire loop
 * over the map at peer-record+0x20, which pairs it with
 * IntMap_GetNextAssoc_14 (the position, key and value outputs) and
 * IntMap_RemoveKey_14 on the same map - the GetStartPosition /
 * GetNextAssoc / RemoveKey triple of CAtlMap. The body does not depend on
 * the node size; the suffix follows the 0x14-node map it serves
 * (IntMap_Insert_14 / IntMap_RemoveKey_14 act on the same map in that
 * function), and a byte search of the image finds no second copy of this
 * body.
 */
#include "ghidra_types.h"


int __fastcall IntMap_GetStartPosition_14(int *param_1)

{
  uint uVar1;
  int *piVar2;
  
  if (param_1[1] == 0) {
    return 0;
  }
  uVar1 = 0;
  if (param_1[2] != 0) {
    piVar2 = (int *)*param_1;
    do {
      if (*piVar2 != 0) {
        return ((int *)*param_1)[uVar1];
      }
      uVar1 = uVar1 + 1;
      piVar2 = piVar2 + 1;
    } while (uVar1 < (uint)param_1[2]);
  }
  return 0;
}

