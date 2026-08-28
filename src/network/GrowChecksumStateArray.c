/* GrowChecksumStateArray - 0x0043d840 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * DROPPED-REG FIX (2026-08-28): EAX is the capacity being asked for and
 * ESI the array object; both are read before written. The object layout
 * is +0 buffer, +4 size, +8 capacity, +0xc a caller-set growth hint, and
 * the elements are 6 bytes (`_malloc(in_EAX * 6)`).
 *
 * The growth policy is the ATL7 one: when the hint at +0xc is zero it
 * takes size>>3 clamped to [4, 0x400] - see the `shr 3` / `< 4 -> 4` /
 * `0x400 <` chain in the else arm - which is the discriminator
 * src/cxx/AtlArray.h documents for telling CAtlArray apart from MFC's
 * CArray.
 *
 * Both call sites ask for one more than the current size and hand over
 * the array embedded at their object's +8: `lea eax,[edi+1]` at
 * 0x43d5f4 with esi = ecx+8 in InsertChecksumStateRecord, and
 * `lea eax,[ebx+1]` at 0x43d7e6 with esi = eax+8 (set once at
 * 0x43d78d/0x43d792) in FUN_0043d780. Both are `lea`, an address, not
 * the load callsite_regs.py renders them as.
 */
#include "ghidra_types.h"


undefined4 GrowChecksumStateArray(uint regEax,int *regEsi)

{
  uint in_EAX = regEax;
  void *pvVar1;
  uint uVar2;
  int *unaff_ESI = regEsi;
  
  if (in_EAX <= (uint)unaff_ESI[2]) {
    return 1;
  }
  uVar2 = unaff_ESI[3];
  if (*unaff_ESI == 0) {
    if (in_EAX < uVar2) {
      in_EAX = uVar2;
    }
    pvVar1 = _malloc(in_EAX * 6);
    *unaff_ESI = (int)pvVar1;
    if (pvVar1 != (void *)0x0) {
      unaff_ESI[2] = in_EAX;
      return 1;
    }
  }
  else {
    if (uVar2 == 0) {
      uVar2 = (uint)unaff_ESI[1] >> 3;
      if (uVar2 < 4) {
        uVar2 = 4;
      }
      else if (0x400 < uVar2) {
        uVar2 = 0x400;
      }
    }
    uVar2 = uVar2 + unaff_ESI[2];
    if (uVar2 <= in_EAX) {
      uVar2 = in_EAX;
    }
    pvVar1 = _malloc(uVar2 * 6);
    if (pvVar1 != (void *)0x0) {
      _memmove(pvVar1,(void *)*unaff_ESI,unaff_ESI[1] * 6);
      _free((void *)*unaff_ESI);
      *unaff_ESI = (int)pvVar1;
      unaff_ESI[2] = uVar2;
      return 1;
    }
  }
  return 0;
}

