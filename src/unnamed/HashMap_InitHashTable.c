/* HashMap_InitHashTable - 0x00500c00 in the original binary.
 *
 * MFC's CMap::InitHashTable(nHashSize, bAllocNow), and the signature matches
 * that exactly: free any existing bucket array, allocate and zero nHashSize
 * pointers when bAllocNow is set, store the bucket count at +8, and compute
 * the two load-factor thresholds at +0x18 and +0x1c (the second cleared when
 * it lands under 0x11).  Every map insert calls it with (map, map[2], 1) the
 * first time the bucket array is null.
 *
 * REHASH THRESHOLDS RECOVERED (2026-10-30): the two FloatToInt64() calls
 * converted an uninitialised x87 ST0, so m_nHiRehashThreshold (+0x18) and
 * m_nLoRehashThreshold (+0x1c) were garbage after every InitHashTable.
 * The tail is ATL's UpdateRehashThresholds over nBins (EBX = [ebp+0xc] =
 * param_2, re-stored to [ebp+0x10] and loaded by `fild [ebp+0x10]` at
 * 0x500c8e), the UINT fix-up `fadd [0x557fac]` (4294967296.0f) at
 * 0x500c96, then `fld st(0); fmul [esi+0x14]` (m_fHiThreshold) at
 * 0x500c9e and _ftol2 (0x53753c, truncating) at 0x500ca1 stored to +0x18
 * at 0x500ca9, and `fmul [esi+0x10]` (m_fLoThreshold) at 0x500ca6 and
 * _ftol2 at 0x500cac stored to +0x1c at 0x500cb4.  Spelled out as
 * (uint)(longlong)((double)nBins * m_f*Threshold), as in the seven Rehash
 * copies.  (This function is ATL's CAtlMap::InitHashTable, not MFC's -
 * see HashMap_Construct.)
 *
 * SEH-PROLOGUE ARTIFACT FIX (2026-10-30): the original links an EH frame
 * (push -1 / push 0x537710 / mov eax,fs:[0] ... mov fs:[0],esp at
 * 0x500c03-0x500c11) around the operator_new, and unlinks it at both
 * exits (mov fs:[0],ecx at 0x500c73 and 0x500cc7).  Ghidra rendered
 * that as writes through an uninitialised `unaff_FS_OFFSET` pointer -
 * live on every map's first insert - plus the try-state counter
 * local_8.  The handler (LAB_00537710) is not part of this decompile,
 * so the plumbing is stripped as in ConstructStringFromText.c.
 */
#include "ghidra_types.h"


undefined4 HashMap_InitHashTable(undefined4 *param_1,int param_2,int param_3)

{
  void *pvVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;

  if ((void *)*param_1 != (void *)0x0) {
    _free((void *)*param_1);
    *param_1 = 0;
  }
  if (param_3 != '\0') {
    pvVar1 = operator_new(param_2 * 4);
    *param_1 = pvVar1;
    puVar5 = (undefined4 *)*param_1;
    iVar4 = param_2;
    if (puVar5 == (undefined4 *)0x0) {
      return 0;
    }
    for (; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar5 = 0;
      puVar5 = puVar5 + 1;
    }
  }
  param_1[2] = param_2;
  /* UpdateRehashThresholds, 0x500c8e-0x500cb4: nBins (param_2) as UINT */
  uVar2 = (uint)(longlong)((double)(uint)param_2 * (double)*(float *)(param_1 + 5));
  param_1[6] = uVar2;
  uVar3 = (uint)(longlong)((double)(uint)param_2 * (double)*(float *)(param_1 + 4));
  param_1[7] = uVar3;
  if (uVar3 < 0x11) {
    param_1[7] = 0;
  }
  return 1;
}

