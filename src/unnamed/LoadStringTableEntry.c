/* LoadStringTableEntry - 0x00401820 in the original binary.
 *
 * Win32 string-table lookup: LoadResource + LockResource on the resource
 * regEbx, then walk `regEax & 0xf` counted strings from the start of the
 * block and return the one that lands there (null if it runs past
 * SizeofResource or the string is empty).  That `& 0xf` is what identifies
 * it -- string tables hold sixteen strings per resource, which is why both
 * callers look the resource up as (id >> 4) + 1 and then hand the id here.
 *
 * BOTH REGISTERS RECOVERED (2026-08-25).  regEbx is the HRSRC, held in
 * pHVar1 at both sites (from FindResourceExA in one caller, FindResourceA in
 * the other), and regEax is the string id -- the same value each caller has
 * already shifted right by four to find the block.
 */
#include "ghidra_types.h"


uint LoadStringTableEntry(HMODULE param_1,uint regEax,HRSRC regEbx)

{
  HGLOBAL hResData;
  ushort *puVar1;
  DWORD DVar2;
  ushort *puVar3;
  uint uVar4;
  
  hResData = LoadResource(param_1,regEbx);
  if (hResData == (HGLOBAL)0x0) {
    return 0;
  }
  puVar1 = LockResource(hResData);
  if (puVar1 != (ushort *)0x0) {
    DVar2 = SizeofResource(param_1,regEbx);
    puVar3 = (ushort *)(DVar2 + (int)puVar1);
    for (uVar4 = regEax & 0xf; uVar4 != 0; uVar4 = uVar4 - 1) {
      if (puVar3 <= puVar1) {
        return 0;
      }
      puVar1 = puVar1 + *puVar1 + 1;
    }
    if (puVar1 < puVar3) {
      return -(uint)(*puVar1 != 0) & (uint)puVar1;
    }
  }
  return 0;
}

