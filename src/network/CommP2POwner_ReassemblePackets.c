/* CommP2POwner_ReassemblePackets - 0x00503c40 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * NAMED 2026-10-29, LIKELY (was FUN_00503c40).  The receive-side
 * deframer of the CommP2P owner's TCP stream.  Evidence from outside:
 *   - its one non-recursive caller is 0x501750, slot 0 of the
 *     comm-engine handler vtable 0x5575b8 (stamped at owner+4).
 *     CommEngineRecv invokes that slot as (err, node, buf, n) straight
 *     after recv(sock, buf, 6000, 0); 0x501750 forwards (buf, n) here
 *     only when err == 0, with `add ecx,0x2f0` - so `this` is the
 *     owner+0x2f4 sub-object and the input is a raw recv() chunk.
 *   - it hands each complete frame to slot 0 of that sub-object's own
 *     vtable - __purecall in the base table 0x557594, overridden by
 *     CommP2POwner_ProcessPacket in 0x5575a8 - as (frame, frame
 *     length), and that callee reads the type at frame+2 and the body
 *     at frame+4.
 * Between the two it buffers a partial ushort length prefix at this+4
 * (count at this+0x1774), rejects frames over 0x1770 bytes, and recurses
 * on any bytes left after a frame.  LIKELY rather than CERTAIN only
 * because 0x501750 is not carved, so the chain rests on the binary
 * alone; the owner-style prefix pairs it with its dispatch target.
 *
 * DISPATCH `this` RESTORED (2026-10-29): both vtbl[0] calls (0x503c97,
 * 0x503dad) load ECX = EBX = this; the port called through `code` with
 * only (buf, len).  The target is a raw-C port, so the erased __thiscall
 * is cdecl with `this` first - see CommP2PPacketHandlerFn.  Note the
 * vtable stamped by ConstructCommP2POwner is still the placeholder
 * global PTR_FUN_005575a8, so this path is not yet reachable at runtime.
 */
#include "ghidra_types.h"

/* Slot 0 of this sub-object's vtable (0x5575a8 in the original):
 * CommP2POwner_ProcessPacket, a raw-C port of a __thiscall whose erased
 * convention in this tree is cdecl with `this` first. */
typedef int (*CommP2PPacketHandlerFn)(undefined4 *self,void *frame,uint len);


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

undefined4 __thiscall CommP2POwner_ReassemblePackets(undefined4 *param_1,ushort *param_2,uint param_3)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  undefined4 *vtbl;
  undefined4 *puVar7;
  ushort *puVar8;
  undefined4 *puVar9;
  undefined4 *puVar10;
  /* COALESCED: Ghidra split the 6000-byte frame buffer at esp+0x18 into
   * local_2ee8[1498] + auStack_1780[8]; the copies write up to 0x1770
   * bytes into it, so it is one array (esp+0x18 .. esp+0x1788). */
  undefined4 local_2ee8 [1500];
  undefined4 local_1778 [1499];
  undefined4 uStack_c;
  
  uStack_c = 0x503c50;
  uVar4 = param_1[0x5dd];
  if ((((uVar4 == 0) && (2 < param_3)) && (*param_2 == param_3)) && (param_3 < 0x1771)) {
    puVar7 = local_2ee8;
    for (uVar4 = param_3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
      *puVar7 = *(undefined4 *)param_2;
      param_2 = param_2 + 2;
      puVar7 = puVar7 + 1;
    }
    vtbl = (undefined4 *)*param_1;
    for (uVar4 = param_3 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *(char *)puVar7 = (char)*param_2;
      param_2 = (ushort *)((int)param_2 + 1);
      puVar7 = (undefined4 *)((int)puVar7 + 1);
    }
    /* `this` RESTORED: `mov ecx,ebx; call [eax]` at 0x503c95/0x503c97. */
    iVar1 = ((CommP2PPacketHandlerFn)*vtbl)(param_1,local_2ee8,param_3);
    if (iVar1 != 0) {
      return 1;
    }
    return 0;
  }
  if (uVar4 < 2) {
    if (uVar4 + param_3 < 2) goto LAB_00503de7;
    uVar2 = 2 - uVar4;
    puVar8 = param_2;
    puVar7 = (undefined4 *)(uVar4 + 4 + (int)param_1);
    for (uVar5 = uVar2 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *puVar7 = *(undefined4 *)puVar8;
      puVar8 = puVar8 + 2;
      puVar7 = puVar7 + 1;
    }
    param_2 = (ushort *)((int)param_2 + uVar2);
    for (uVar4 = uVar2 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *(char *)puVar7 = (char)*puVar8;
      puVar8 = (ushort *)((int)puVar8 + 1);
      puVar7 = (undefined4 *)((int)puVar7 + 1);
    }
    param_3 = param_3 - uVar2;
    param_1[0x5dd] = param_1[0x5dd] + uVar2;
    if (param_3 == 0) {
      return 1;
    }
  }
  uVar2 = (uint)*(ushort *)(param_1 + 1);
  if ((6000 < uVar2) || (uVar4 = param_1[0x5dd], uVar2 < uVar4)) {
    return 0;
  }
  if (uVar2 <= uVar4 + param_3) {
    uVar5 = uVar2 - uVar4;
    if (uVar4 == 2) {
      SUBFIELD(local_2ee8[0],0,undefined2) = *(undefined2 *)(param_1 + 1);
    }
    else {
      puVar9 = local_2ee8;
      puVar7 = param_1;
      for (uVar6 = uVar4 >> 2; puVar7 = puVar7 + 1, uVar6 != 0; uVar6 = uVar6 - 1) {
        *puVar9 = *puVar7;
        puVar9 = puVar9 + 1;
      }
      for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
        *(undefined1 *)puVar9 = *(undefined1 *)puVar7;
        puVar7 = (undefined4 *)((int)puVar7 + 1);
        puVar9 = (undefined4 *)((int)puVar9 + 1);
      }
    }
    puVar8 = param_2;
    puVar7 = (undefined4 *)((int)local_2ee8 + param_1[0x5dd]);
    for (uVar4 = uVar5 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
      *puVar7 = *(undefined4 *)puVar8;
      puVar8 = puVar8 + 2;
      puVar7 = puVar7 + 1;
    }
    for (uVar4 = uVar5 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *(char *)puVar7 = (char)*puVar8;
      puVar8 = (ushort *)((int)puVar8 + 1);
      puVar7 = (undefined4 *)((int)puVar7 + 1);
    }
    puVar7 = (undefined4 *)*param_1;
    param_1[0x5dd] = 0;
    puVar9 = (undefined4 *)(uVar5 + (int)param_2);
    puVar10 = local_1778;
    for (uVar4 = param_3 - uVar5 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
      *puVar10 = *puVar9;
      puVar9 = puVar9 + 1;
      puVar10 = puVar10 + 1;
    }
    for (uVar4 = param_3 - uVar5 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *(undefined1 *)puVar10 = *(undefined1 *)puVar9;
      puVar9 = (undefined4 *)((int)puVar9 + 1);
      puVar10 = (undefined4 *)((int)puVar10 + 1);
    }
    /* `this` RESTORED: `mov ecx,ebx; call [edx]` at 0x503dab/0x503dad. */
    iVar1 = ((CommP2PPacketHandlerFn)*puVar7)(param_1,local_2ee8,uVar2);
    if (iVar1 != 0) {
      /* RECURSION RECOVERED (2026-10-29), orig 0x503db7-0x503dcf: return 1
       * unless the bytes this frame consumed (uVar5, [esp+0xc]) are fewer
       * than the bytes still in hand (param_3, reloaded from [ebp+0xc] -
       * already reduced by any header bytes taken above); signed
       * `cmp/jge`.  Otherwise recurse on the remainder: ECX = EBX = this,
       * then `lea ecx,[esp+0x178c]` with one push pending = esp+0x1788 =
       * local_1778 (the tail copy's destination) and [esp+0x10] =
       * param_3 - uVar5.  The previous port passed auStack_1780 as this,
       * an uninitialised EBX as the buffer, and compared against an
       * uninitialised ESI. */
      if ((int)param_3 <= (int)uVar5) {
        return 1;
      }
      uVar3 = CommP2POwner_ReassemblePackets(param_1,(ushort *)local_1778,param_3 - uVar5);
      return uVar3;
    }
    return 0;
  }
LAB_00503de7:
  puVar7 = (undefined4 *)(uVar4 + 4 + (int)param_1);
  for (uVar2 = param_3 >> 2; uVar2 != 0; uVar2 = uVar2 - 1) {
    *puVar7 = *(undefined4 *)param_2;
    param_2 = param_2 + 2;
    puVar7 = puVar7 + 1;
  }
  for (uVar4 = param_3 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(char *)puVar7 = (char)*param_2;
    param_2 = (ushort *)((int)param_2 + 1);
    puVar7 = (undefined4 *)((int)puVar7 + 1);
  }
  param_1[0x5dd] = param_1[0x5dd] + param_3;
  return 1;
}

