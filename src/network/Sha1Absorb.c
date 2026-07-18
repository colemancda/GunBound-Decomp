/* Sha1Absorb - 0x004f7380 in the original binary.
 *
 * Absorbs `length` bytes of `param_2` into the SHA-1 context `param_1`
 * (the streaming update step; the 5 H-state dwords live at param_1+0..0x10,
 * bit count at +0x14/+0x18, the 0x40-byte block buffer at +0x1c, and the
 * partial-block byte count at +0x5c).
 *
 * DROPPED REGISTER ARGUMENT (2026-07-18): the byte count arrived in EAX
 * (orig 0x4f738c `mov edi,eax`), which Ghidra emitted as an uninitialised
 * `in_EAX` read - so with a garbage length the function walked `param_2`
 * off the end and faulted (`movzx edx,[esi]` on a -1 buffer pointer during
 * the login handshake's credential hash). Promoted to an explicit third
 * parameter `length`; all 9 call sites across the 3 callers
 * (EncodeHandshakeBlock, FUN_004feb00, FUN_004ff770) recover it from their
 * own disassembly - each `mov eax,<len>` immediately before the call. NOTE
 * two of EncodeHandshakeBlock's calls ALSO dropped `param_2` (the buffer),
 * reading stack garbage - recovered there too. param_1/param_2 stay stack
 * args (the original's real ABI: ctx=[esp+4], buffer=[esp+8], length=EAX).
 */
#include "ghidra_types.h"


void Sha1Absorb(int param_1,byte *param_2,uint length)

{
  int iVar1;
  byte *pbVar2;
  byte *pbVar3;
  byte *pbVar4;
  byte bVar5;
  uint *puVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;

  if (length == 0) {
    return;
  }
  uVar8 = *(uint *)(param_1 + 0x14) + length * 8;
  if (uVar8 < *(uint *)(param_1 + 0x14)) {
    *(int *)(param_1 + 0x18) = *(int *)(param_1 + 0x18) + 1;
  }
  uVar10 = *(uint *)(param_1 + 0x5c);
  *(uint *)(param_1 + 0x18) = *(int *)(param_1 + 0x18) + (length >> 0x1d);
  *(uint *)(param_1 + 0x14) = uVar8;
  if (uVar10 != 0) {
    uVar8 = uVar10 + length;
    iVar7 = (int)uVar10 >> 2;
    uVar10 = uVar10 & 3;
    iVar1 = param_1 + 0x1c;
    if (uVar8 < 0x40) {
      *(uint *)(param_1 + 0x5c) = uVar8;
      uVar11 = *(uint *)(iVar1 + iVar7 * 4);
      if (3 < uVar10 + length) {
        uVar9 = uVar8 & 3;
        switch(uVar10) {
        case 0:
          uVar11 = (uint)*param_2 << 0x18;
          param_2 = param_2 + 1;
        case 1:
          uVar11 = uVar11 | (uint)*param_2 << 0x10;
          param_2 = param_2 + 1;
        case 2:
          uVar11 = uVar11 | (uint)*param_2 << 8;
          param_2 = param_2 + 1;
        case 3:
          uVar11 = uVar11 | *param_2;
          param_2 = param_2 + 1;
        }
        *(uint *)(iVar1 + iVar7 * 4) = uVar11;
        while (iVar7 = iVar7 + 1, iVar7 < (int)uVar8 >> 2) {
          bVar5 = *param_2;
          pbVar2 = param_2 + 1;
          pbVar3 = param_2 + 2;
          pbVar4 = param_2 + 3;
          param_2 = param_2 + 4;
          *(uint *)(iVar1 + iVar7 * 4) =
               (uint)bVar5 << 0x18 | (uint)*pbVar2 << 0x10 | (uint)*pbVar3 << 8 | (uint)*pbVar4;
        }
        if (uVar9 == 0) {
          return;
        }
        uVar8 = 0;
        param_2 = param_2 + uVar9;
        if (uVar9 != 1) {
          if (uVar9 != 2) {
            if (uVar9 != 3) goto LAB_004f75ce;
            param_2 = param_2 + -1;
            uVar8 = (uint)*param_2 << 8;
          }
          pbVar2 = param_2 + -1;
          param_2 = param_2 + -1;
          uVar8 = uVar8 | (uint)*pbVar2 << 0x10;
        }
        uVar8 = uVar8 | (uint)param_2[-1] << 0x18;
LAB_004f75ce:
        *(uint *)(iVar1 + iVar7 * 4) = uVar8;
        return;
      }
      if (uVar10 == 0) {
        uVar11 = (uint)*param_2 << 0x18;
        param_2 = param_2 + 1;
        length = length - 1;
        if (length == 0) goto LAB_004f7529;
LAB_004f7517:
        uVar11 = uVar11 | (uint)*param_2 << 0x10;
        param_2 = param_2 + 1;
        if (length == 1) goto LAB_004f7529;
      }
      else {
        if (uVar10 == 1) goto LAB_004f7517;
        if (uVar10 != 2) {
          *(uint *)(iVar1 + iVar7 * 4) = uVar11;
          return;
        }
      }
      uVar11 = uVar11 | (uint)*param_2 << 8;
LAB_004f7529:
      *(uint *)(iVar1 + iVar7 * 4) = uVar11;
      return;
    }
    uVar8 = *(uint *)(iVar1 + iVar7 * 4);
    switch(uVar10) {
    case 0:
      uVar8 = (uint)*param_2 << 0x18;
      param_2 = param_2 + 1;
    case 1:
      uVar8 = uVar8 | (uint)*param_2 << 0x10;
      param_2 = param_2 + 1;
    case 2:
      uVar8 = uVar8 | (uint)*param_2 << 8;
      param_2 = param_2 + 1;
    case 3:
      uVar8 = uVar8 | *param_2;
      param_2 = param_2 + 1;
    default:
      *(uint *)(iVar1 + iVar7 * 4) = uVar8;
      while (iVar7 = iVar7 + 1, iVar7 < 0x10) {
        bVar5 = *param_2;
        pbVar2 = param_2 + 1;
        pbVar3 = param_2 + 2;
        pbVar4 = param_2 + 3;
        param_2 = param_2 + 4;
        *(uint *)(iVar1 + iVar7 * 4) =
             (uint)bVar5 << 0x18 | (uint)*pbVar2 << 0x10 | (uint)*pbVar3 << 8 | (uint)*pbVar4;
      }
      Sha1TransformBuffer(0,(uint *)iVar1,1,(uint *)param_1);
      length = (length - 0x40) + *(int *)(param_1 + 0x5c);
      *(undefined4 *)(param_1 + 0x5c) = 0;
    }
  }
  uVar8 = length >> 6;
  if (uVar8 != 0) {
    Sha1TransformBlocks((uint *)param_1,uVar8,param_2);
    param_2 = param_2 + uVar8 * 0x40;
    length = length + uVar8 * -0x40;
  }
  if (length == 0) {
    return;
  }
  *(uint *)(param_1 + 0x5c) = length;
  uVar10 = length & 3;
  puVar6 = (uint *)(param_1 + 0x1c);
  for (uVar8 = length >> 2; uVar8 != 0; uVar8 = uVar8 - 1) {
    *puVar6 = (uint)*param_2 << 0x18 | (uint)param_2[1] << 0x10 | (uint)param_2[2] << 8 |
              (uint)param_2[3];
    param_2 = param_2 + 4;
    puVar6 = puVar6 + 1;
  }
  uVar8 = 0;
  param_2 = param_2 + uVar10;
  if (uVar10 != 1) {
    if (uVar10 != 2) {
      if (uVar10 != 3) goto LAB_004f74df;
      uVar8 = (uint)param_2[-1] << 8;
      param_2 = param_2 + -1;
    }
    pbVar2 = param_2 + -1;
    param_2 = param_2 + -1;
    uVar8 = uVar8 | (uint)*pbVar2 << 0x10;
  }
  uVar8 = uVar8 | (uint)param_2[-1] << 0x18;
LAB_004f74df:
  *puVar6 = uVar8;
  return;
}

