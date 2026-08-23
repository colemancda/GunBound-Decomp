/* LoadAvatarSprites - 0x004141b0 in the original binary.
 *
 * The avatar sprite compositor. Given a character's four avatar equip codes
 * (param_1=head, param_2=body, param_3=glasses, param_4=flag), it builds each
 * part's sprite filename and loads it via LoadSpriteSet, assembling the
 * multi-part avatar. Confirms the Avatar.xfs part format (see FILEFORMATS.md):
 *   - equip code bit 15 = gender (set -> 'm'=0x6d, clear -> 'f'=0x66, via
 *     `(-((code & 0x8000)!=0) & 7) + 0x66`); bits 0..14 = the part id (record
 *     index in the matching {gender}{cat}.dat table); 0xffffffff = no part.
 *   - sprite name = "{gender}{cat}%05d.img" (body %cb, glasses %cg, head %ch),
 *     flag = "mf%05d.img"; each also has a large "...l.img" in-battle variant.
 * Called from the Avatar Store (State07) and the room/battle avatar draw paths.
 *
 * Function IDENTITY is confirmed (avatar part-sprite compositor); the BODY is a
 * raw/near-verbatim Ghidra port (register-args), not hand-verified. See
 * src/README.md's "Raw/verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-16, CValueGuard sweep): recovered the guard
 * cell at all 18 argless PeekPacketChecksumState() calls.  Every one is a
 * fixed g_clientContext global and the C sites zip 1:1 with the original
 * in address order (0x41426e..0x414d00, no reordering): the equipped-part
 * cells +0x3ac08 and +0x3ae2c, and +0x3b050 / +0x3b274 - the same four
 * cells this file's own sprite-key builders already read through
 * PeekChecksumStateUnderLock.  +0x3ac08 is the equipped-avatar array the
 * store catalog writes (see the avatar-store notes in ARCHITECTURE.md).
 */
#include "ghidra_types.h"

/* DROPPED-`this` FIX (2026-08-06): every sprite-set teardown loop below
 * dispatched the node's slot-0 destructor as `(*(code *)*puVarN)(1)` -
 * plain cdecl, pushing only the flag and never the node. The callee is
 * FUN_004f14c0 (via PTR_FUN_00557524), a raw C port whose erased
 * __thiscall reads BOTH `this` and the flag off the stack - so it read
 * `this` = 1. Same bug + same fix as the State01/02/03/06 OnExit walks:
 * plain cdecl with both args explicit, capturing the node before the
 * loop advances it. */
typedef void (*VtableDtorFn)(void *thisPtr, int flag);


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

void LoadAvatarSprites(uint param_1,uint param_2,uint param_3,uint param_4,int param_5,uint param_6,
                 uint param_7)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  void *pvVar6;
  int iVar7;
  undefined4 *puVar8;
  undefined1 *puVar9;
  uint uVar10;
  undefined1 *puVar11;
  undefined4 *puVar12;
  undefined4 *puVar14;
  undefined4 *thisNode;
  int local_80b0;
  undefined4 *local_80ac;
  undefined4 local_80a8;
  undefined2 local_80a4;
  ushort local_80a2;
  int local_80a0;
  undefined4 local_809c;
  int local_8098;
  undefined4 local_8094;
  undefined4 local_8090;
  undefined4 local_808c;
  char local_8088 [128];
  /* SPLIT-BUFFER FIX (2026-08-06): Ghidra split the original's single
   * 0x8000-byte 128x128x16bpp avatar canvas into three locals
   * (local_8008[63 dwords] + local_7f0a[32258] + local_108[252]) whose
   * Ghidra names ARE the frame offsets: base -0x8008, -0x7f0a = base +
   * 0xfe (the last column of row 0, used by the right-to-left trim
   * scan) and -0x108 = base + 0x7f00 (the last row, used by the
   * bottom-up trim scan). They only form the real canvas if MSVC
   * places them contiguously in that order - it does not, and the
   * 0x2000-dword zero loop through the first (252-byte!) local zeroed
   * ~32K of the ACTIVE STACK including every return address: the next
   * `ret` popped 0 into EIP (live crash on every AVATAR click).
   * Coalesced into one real canvas. */
  undefined1 avatarCanvas [0x8000];
  undefined4 uStack_c;
  
  uStack_c = 0x4141c0;
  puVar12 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
  uVar2 = puVar12[1];
  if (uVar2 <= param_6) {
LAB_004141d8:
    if (uVar2 != param_6) goto code_r0x004141da;
    puVar8 = (undefined4 *)puVar12[4];
    while (puVar8 != puVar12) {
      thisNode = puVar8;
      puVar14 = (undefined4 *)*puVar8;
      puVar8 = (undefined4 *)puVar8[4];
      ((VtableDtorFn)*puVar14)(thisNode,1);
    }
    puVar12[3] = puVar12;
    puVar12[4] = puVar12;
  }
LAB_00414205:
  puVar12 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
  uVar2 = puVar12[1];
  if (uVar2 <= param_7) {
LAB_00414214:
    if (uVar2 != param_7) goto code_r0x00414216;
    puVar8 = (undefined4 *)puVar12[4];
    while (puVar8 != puVar12) {
      thisNode = puVar8;
      puVar14 = (undefined4 *)*puVar8;
      puVar8 = (undefined4 *)puVar8[4];
      ((VtableDtorFn)*puVar14)(thisNode,1);
    }
    puVar12[3] = puVar12;
    puVar12[4] = puVar12;
  }
LAB_00414245:
  if (param_4 == 0xffffffff) {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    uVar2 = PeekPacketChecksumState((void *)(g_clientContext + 0x3b274));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    _sprintf(local_8088,s_mf_05d_img_0055220c,uVar2 & 0x7fff);
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    uVar2 = PeekPacketChecksumState((void *)(g_clientContext + 0x3b274));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  }
  else {
    _sprintf(local_8088,s_mf_05d_img_0055220c,param_4 & 0x7fff);
    uVar2 = param_4;
  }
  local_80a2 = (ushort)uVar2 & 0x7fff;
  local_8090 = LoadSpriteSet(&g_spriteRegistry,100000,local_8088);
  if (param_2 == 0xffffffff) {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    uVar2 = PeekPacketChecksumState((void *)(g_clientContext + 0x3ac08));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    uVar3 = PeekPacketChecksumState((void *)(g_clientContext + 0x3ac08));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    _sprintf(local_8088,s__cb_05d_img_00552200,(int)(char)((-((uVar3 & 0x8000) != 0) & 7U) + 0x66),
             uVar2 & 0x7fff);
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    uVar2 = PeekPacketChecksumState((void *)(g_clientContext + 0x3ac08));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  }
  else {
    _sprintf(local_8088,s__cb_05d_img_00552200,(int)(char)((-((param_2 & 0x8000) != 0) & 7U) + 0x66)
             ,param_2 & 0x7fff);
    uVar2 = param_2;
  }
  local_80a8 = CONCAT22(SUBFIELD(local_80a8,2,undefined2),(short)uVar2);
  local_808c = LoadSpriteSet(&g_spriteRegistry,0x186a1,local_8088);
  if (param_3 == 0xffffffff) {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    uVar2 = PeekPacketChecksumState((void *)(g_clientContext + 0x3b050));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    uVar3 = PeekPacketChecksumState((void *)(g_clientContext + 0x3b050));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    _sprintf(local_8088,s__cg_05d_img_005521f4,(int)(char)((-((uVar3 & 0x8000) != 0) & 7U) + 0x66),
             uVar2 & 0x7fff);
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    uVar2 = PeekPacketChecksumState((void *)(g_clientContext + 0x3b050));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  }
  else {
    _sprintf(local_8088,s__cg_05d_img_005521f4,(int)(char)((-((param_3 & 0x8000) != 0) & 7U) + 0x66)
             ,param_3 & 0x7fff);
    uVar2 = param_3;
  }
  local_80a4 = (undefined2)uVar2;
  local_809c = LoadSpriteSet(&g_spriteRegistry,0x186a2,local_8088);
  if (param_1 == 0xffffffff) {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    uVar2 = PeekPacketChecksumState((void *)(g_clientContext + 0x3ae2c));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    uVar3 = PeekPacketChecksumState((void *)(g_clientContext + 0x3ae2c));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    _sprintf(local_8088,s__ch_05d_img_005521e8,(int)(char)((-((uVar3 & 0x8000) != 0) & 7U) + 0x66),
             uVar2 & 0x7fff);
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    uVar2 = PeekPacketChecksumState((void *)(g_clientContext + 0x3ae2c));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  }
  else {
    _sprintf(local_8088,s__ch_05d_img_005521e8,(int)(char)((-((param_1 & 0x8000) != 0) & 7U) + 0x66)
             ,param_1 & 0x7fff);
    uVar2 = param_1;
  }
  local_80a8 = CONCAT22((short)uVar2,(undefined2)local_80a8);
  local_8094 = LoadSpriteSet(&g_spriteRegistry,0x186a3,local_8088);
  if (param_5 != 0) {
    ApplyAvatarStatBonuses(g_clientContext,&local_80a8,param_5,0);
  }
  local_80b0 = 0;
LAB_00414610:
  puVar12 = (undefined4 *)avatarCanvas;
  for (iVar7 = 0x2000; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar12 = 0;
    puVar12 = puVar12 + 1;
  }
  /* RECOVERED (2026-08-06): the per-part frame-index ladders and all
   * three of FUN_00414070's arguments were dead-code-eliminated by
   * Ghidra (the results only fed dropped register args). From orig
   * 0x414620-0x41475e / 0x414d90-0x414ebb: counter = local_80b0
   * (0..0x2b); a part with exactly 0x16 frames wraps (counter % 0x16),
   * head/glasses with 0x2c frames index directly, otherwise the frame
   * ping-pongs - body/flag mirror over [0..0x15] via 0x15-c / c-0x16 /
   * 0x2b-c, head/glasses via 0x15-c / c-0xb / 0x36-c. Frame counts are
   * the LoadSpriteSet return values stored just above. */
  {
    int c = local_80b0;
    int bodyFrame, flagFrame, headFrame, glassesFrame;
    if (local_808c == 0x16) { bodyFrame = c % 0x16; }
    else { bodyFrame = (c < 0x16) ? ((c < 0xb) ? c : 0x15 - c)
                                  : ((c < 0x21) ? c - 0x16 : 0x2b - c); }
    if (local_8090 == 0x16) { flagFrame = c % 0x16; }
    else { flagFrame = (c < 0x16) ? ((c < 0xb) ? c : 0x15 - c)
                                  : ((c < 0x21) ? c - 0x16 : 0x2b - c); }
    if (local_8094 == 0x2c) { headFrame = c; }
    else { headFrame = (c < 0x16) ? ((c < 0xb) ? c : 0x15 - c)
                                  : ((c < 0x21) ? c - 0xb : 0x36 - c); }
    if (local_809c == 0x2c) { glassesFrame = c; }
    else { glassesFrame = (c < 0x16) ? ((c < 0xb) ? c : 0x15 - c)
                                     : ((c < 0x21) ? c - 0xb : 0x36 - c); }
    FUN_00414070(flagFrame,0x186a0,(int)avatarCanvas);
    FUN_00414070(headFrame,0x186a3,(int)avatarCanvas);
    FUN_00414070(glassesFrame,0x186a2,(int)avatarCanvas);
    FUN_00414070(bodyFrame,0x186a1,(int)avatarCanvas);
  }
  iVar7 = 0;
  puVar12 = (undefined4 *)avatarCanvas;
  do {
    iVar4 = 0;
    puVar8 = puVar12;
    do {
      if ((*(byte *)((int)puVar8 + 1) & 0xf0) != 0) {
        iVar4 = 0x7f;
        puVar11 = avatarCanvas + 0x7f00;   /* last row (bottom-up scan) */
        goto LAB_004147a7;
      }
      iVar4 = iVar4 + 1;
      puVar8 = (undefined4 *)((int)puVar8 + 2);
    } while (iVar4 < 0x80);
    iVar7 = iVar7 + 1;
    puVar12 = puVar12 + 0x40;
  } while (iVar7 < 0x80);
  goto LAB_004149a1;
code_r0x004141da:
  puVar12 = (undefined4 *)puVar12[7];
  uVar2 = puVar12[1];
  if (param_6 < uVar2) goto LAB_00414205;
  goto LAB_004141d8;
code_r0x00414216:
  puVar12 = (undefined4 *)puVar12[7];
  uVar2 = puVar12[1];
  if (param_7 < uVar2) goto LAB_00414245;
  goto LAB_00414214;
LAB_004147a7:
  do {
    iVar5 = 0;
    puVar9 = puVar11;
    do {
      iVar1 = iVar4;
      if ((puVar9[1] & 0xf0) != 0) goto LAB_004147d2;
      iVar5 = iVar5 + 1;
      puVar9 = puVar9 + 2;
    } while (iVar5 < 0x80);
    iVar4 = iVar4 + -1;
    puVar11 = puVar11 + -0x100;
    iVar1 = local_80a8;
  } while (-1 < iVar4);
LAB_004147d2:
  local_80a8 = iVar1;
  iVar4 = 0;
  puVar12 = (undefined4 *)avatarCanvas;
  do {
    iVar5 = 0;
    puVar8 = puVar12;
    do {
      iVar1 = iVar4;
      if ((*(byte *)((int)puVar8 + 1) & 0xf0) != 0) goto LAB_0041480a;
      iVar5 = iVar5 + 1;
      puVar8 = puVar8 + 0x40;
    } while (iVar5 < 0x80);
    iVar4 = iVar4 + 1;
    puVar12 = (undefined4 *)((int)puVar12 + 2);
    iVar1 = local_80a0;
  } while (iVar4 < 0x80);
LAB_0041480a:
  local_80a0 = iVar1;
  iVar4 = 0x7f;
  puVar11 = avatarCanvas + 0xfe;    /* last column (right-left scan) */
  do {
    iVar5 = 0;
    puVar9 = puVar11;
    do {
      iVar1 = iVar4;
      if ((puVar9[1] & 0xf0) != 0) goto LAB_00414842;
      iVar5 = iVar5 + 1;
      puVar9 = puVar9 + 0x100;
    } while (iVar5 < 0x80);
    iVar4 = iVar4 + -1;
    puVar11 = puVar11 + -2;
    iVar1 = local_8098;
  } while (-1 < iVar4);
LAB_00414842:
  local_8098 = iVar1;
  puVar12 = operator_new(0x50);
  if (puVar12 == (undefined4 *)0x0) {
    puVar12 = (undefined4 *)0x0;
  }
  else {
    puVar12[1] = param_6;
    puVar12[2] = local_80b0;
    puVar12[3] = 0;
    puVar12[4] = 0;
    *(undefined1 *)(puVar12 + 5) = 0;
    *(undefined1 *)((int)puVar12 + 0x15) = 0;
    *puVar12 = &PTR_FUN_00557524;
    *(undefined1 *)((int)puVar12 + 0x1b) = 0xff;
    *(undefined1 *)((int)puVar12 + 0x1a) = 0;
    *(undefined1 *)((int)puVar12 + 0x19) = 0xff;
    puVar12[8] = 0;
    puVar12[9] = 0;
    puVar12[0xb] = 0;
    puVar12[10] = 0;
    *(undefined1 *)(puVar12 + 0xc) = 0;
    puVar12[0xd] = 0;
    puVar12[0xe] = 0;
  }
  iVar5 = (local_8098 - local_80a0) + 1;
  iVar4 = (local_80a8 - iVar7) + 1;
  puVar12[9] = iVar4;
  iVar4 = iVar4 * iVar5;
  puVar12[0xf] = iVar4 * 2;
  puVar12[10] = local_80a0 + -0x40;
  *(undefined1 *)(puVar12 + 6) = 2;
  puVar12[8] = iVar5;
  puVar12[0xb] = iVar7 + -0x40;
  *(undefined1 *)(puVar12 + 0xc) = 0;
  pvVar6 = operator_new(iVar4 * 2);
  puVar12[0xd] = pvVar6;
  uVar2 = 0;
  if (puVar12[9] != 0) {
    local_80ac = (undefined4 *)((int)avatarCanvas + (iVar7 * 0x80 + local_80a0) * 2);
    do {
      uVar3 = puVar12[8] * 2;
      uVar3 = ((int)uVar3 < 0) - 1 & uVar3;
      puVar8 = local_80ac;
      puVar14 = (undefined4 *)(puVar12[0xd] + puVar12[8] * uVar2 * 2);
      for (uVar10 = uVar3 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
        *puVar14 = *puVar8;
        puVar8 = puVar8 + 1;
        puVar14 = puVar14 + 1;
      }
      for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
        *(undefined1 *)puVar14 = *(undefined1 *)puVar8;
        puVar8 = (undefined4 *)((int)puVar8 + 1);
        puVar14 = (undefined4 *)((int)puVar14 + 1);
      }
      uVar2 = uVar2 + 1;
      local_80ac = local_80ac + 0x40;
    } while (uVar2 < (uint)puVar12[9]);
  }
  iVar7 = *(int *)(DAT_00ea0e1c + 0x1c);
  uVar2 = *(uint *)(iVar7 + 4);
  while (uVar2 <= (uint)puVar12[1]) {
    if (uVar2 == puVar12[1]) goto LAB_0041496a;
    iVar7 = *(int *)(iVar7 + 0x1c);
    uVar2 = *(uint *)(iVar7 + 4);
  }
  iVar7 = CreateActiveObjectLayer((int)&g_spriteRegistry);
LAB_0041496a:
  uVar2 = puVar12[2];
  if (uVar2 != 0xffffffff) {
    iVar7 = *(int *)(iVar7 + 0x10);
    uVar3 = *(uint *)(iVar7 + 8);
    if (uVar3 <= uVar2) {
      do {
        if (uVar3 == uVar2) {
          ((VtableDtorFn)*(void **)*puVar12)((void *)puVar12,1);
          goto LAB_004149a1;
        }
        iVar7 = *(int *)(iVar7 + 0x10);
        uVar3 = *(uint *)(iVar7 + 8);
      } while (uVar3 <= (uint)puVar12[2]);
    }
  }
  puVar12[4] = iVar7;
  puVar12[3] = *(undefined4 *)(iVar7 + 0xc);
  *(undefined4 **)(*(int *)(iVar7 + 0xc) + 0x10) = puVar12;
  *(undefined4 **)(iVar7 + 0xc) = puVar12;
LAB_004149a1:
  local_80b0 = local_80b0 + 1;
  if (0x2b < local_80b0) goto code_r0x004149b3;
  goto LAB_00414610;
code_r0x004149b3:
  puVar12 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
  uVar2 = puVar12[1];
  if (uVar2 < 0x186a1) {
LAB_004149c5:
    if (uVar2 != 100000) goto code_r0x004149c7;
    puVar8 = (undefined4 *)puVar12[4];
    while (puVar8 != puVar12) {
      thisNode = puVar8;
      puVar14 = (undefined4 *)*puVar8;
      puVar8 = (undefined4 *)puVar8[4];
      ((VtableDtorFn)*puVar14)(thisNode,1);
    }
    puVar12[3] = puVar12;
    puVar12[4] = puVar12;
  }
LAB_004149fc:
  puVar12 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
  uVar2 = puVar12[1];
  if (uVar2 < 0x186a2) {
LAB_00414a0e:
    if (uVar2 != 0x186a1) goto code_r0x00414a10;
    puVar8 = (undefined4 *)puVar12[4];
    while (puVar8 != puVar12) {
      thisNode = puVar8;
      puVar14 = (undefined4 *)*puVar8;
      puVar8 = (undefined4 *)puVar8[4];
      ((VtableDtorFn)*puVar14)(thisNode,1);
    }
    puVar12[3] = puVar12;
    puVar12[4] = puVar12;
  }
LAB_00414a3b:
  puVar12 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
  uVar2 = puVar12[1];
  if (uVar2 < 0x186a3) {
LAB_00414a4d:
    if (uVar2 != 0x186a2) goto code_r0x00414a4f;
    puVar8 = (undefined4 *)puVar12[4];
    while (puVar8 != puVar12) {
      thisNode = puVar8;
      puVar14 = (undefined4 *)*puVar8;
      puVar8 = (undefined4 *)puVar8[4];
      ((VtableDtorFn)*puVar14)(thisNode,1);
    }
    puVar12[3] = puVar12;
    puVar12[4] = puVar12;
  }
LAB_00414a7a:
  puVar12 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
  uVar2 = puVar12[1];
  if (uVar2 < 0x186a4) {
LAB_00414a8c:
    if (uVar2 != 0x186a3) goto code_r0x00414a8e;
    puVar8 = (undefined4 *)puVar12[4];
    while (puVar8 != puVar12) {
      thisNode = puVar8;
      puVar14 = (undefined4 *)*puVar8;
      puVar8 = (undefined4 *)puVar8[4];
      ((VtableDtorFn)*puVar14)(thisNode,1);
    }
    puVar12[3] = puVar12;
    puVar12[4] = puVar12;
  }
LAB_00414ab9:
  if (param_4 == 0xffffffff) {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    param_4 = PeekPacketChecksumState((void *)(g_clientContext + 0x3b274));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  }
  _sprintf(local_8088,s_mf_05dl_img_005521dc,param_4 & 0x7fff);
  local_8090 = LoadSpriteSet(&g_spriteRegistry,100000,local_8088);
  /* DOUBLE-CLEANUP FIX (2026-08-06): Ghidra hoisted EnterCriticalSection
   * into a generic `code *` local and dispatched it unprototyped - cdecl
   * to MSVC, so the caller cleaned 4 bytes the __stdcall callee had
   * ALREADY popped: +4 ESP drift per call, x4 calls = the +0x10 drift
   * that pushed the large-variant canvas zero-fill (esp-relative
   * [esp+0xb8]) over this function's own saved EBP/return address -
   * caught live with a hardware watchpoint on the return slot (writer =
   * the rep-stos, esp 0x10 above its block-A level). Same class as
   * InitDirectDraw.c's COM-dispatch fix. Calls devirtualised back to
   * the real __stdcall import. */
  if (param_2 == 0xffffffff) {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    uVar2 = PeekPacketChecksumState((void *)(g_clientContext + 0x3ac08));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    uVar3 = PeekPacketChecksumState((void *)(g_clientContext + 0x3ac08));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    _sprintf(local_8088,s__cb_05dl_img_005521cc,(int)(char)((-((uVar3 & 0x8000) != 0) & 7U) + 0x66),
             uVar2 & 0x7fff);
  }
  else {
    _sprintf(local_8088,s__cb_05dl_img_005521cc,
             (int)(char)((-((param_2 & 0x8000) != 0) & 7U) + 0x66),param_2 & 0x7fff);
  }
  local_808c = LoadSpriteSet(&g_spriteRegistry,0x186a1,local_8088);
  uVar2 = param_3;
  if (param_3 == 0xffffffff) {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    uVar2 = PeekPacketChecksumState((void *)(g_clientContext + 0x3b050));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    param_3 = PeekPacketChecksumState((void *)(g_clientContext + 0x3b050));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  }
  _sprintf(local_8088,s__cg_05dl_img_005521bc,(int)(char)((-((param_3 & 0x8000) != 0) & 7U) + 0x66),
           uVar2 & 0x7fff);
  local_809c = LoadSpriteSet(&g_spriteRegistry,0x186a2,local_8088);
  uVar2 = param_1;
  if (param_1 == 0xffffffff) {
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    uVar2 = PeekPacketChecksumState((void *)(g_clientContext + 0x3ae2c));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    param_1 = PeekPacketChecksumState((void *)(g_clientContext + 0x3ae2c));
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  }
  _sprintf(local_8088,s__ch_05dl_img_005521ac,(int)(char)((-((param_1 & 0x8000) != 0) & 7U) + 0x66),
           uVar2 & 0x7fff);
  local_8094 = LoadSpriteSet(&g_spriteRegistry,0x186a3,local_8088);
  local_80b0 = 0;
LAB_00414d80:
  puVar12 = (undefined4 *)avatarCanvas;
  for (iVar7 = 0x2000; iVar7 != 0; iVar7 = iVar7 + -1) {
    *puVar12 = 0;
    puVar12 = puVar12 + 1;
  }
  /* RECOVERED (2026-08-06): the per-part frame-index ladders and all
   * three of FUN_00414070's arguments were dead-code-eliminated by
   * Ghidra (the results only fed dropped register args). From orig
   * 0x414620-0x41475e / 0x414d90-0x414ebb: counter = local_80b0
   * (0..0x2b); a part with exactly 0x16 frames wraps (counter % 0x16),
   * head/glasses with 0x2c frames index directly, otherwise the frame
   * ping-pongs - body/flag mirror over [0..0x15] via 0x15-c / c-0x16 /
   * 0x2b-c, head/glasses via 0x15-c / c-0xb / 0x36-c. Frame counts are
   * the LoadSpriteSet return values stored just above. */
  {
    int c = local_80b0;
    int bodyFrame, flagFrame, headFrame, glassesFrame;
    if (local_808c == 0x16) { bodyFrame = c % 0x16; }
    else { bodyFrame = (c < 0x16) ? ((c < 0xb) ? c : 0x15 - c)
                                  : ((c < 0x21) ? c - 0x16 : 0x2b - c); }
    if (local_8090 == 0x16) { flagFrame = c % 0x16; }
    else { flagFrame = (c < 0x16) ? ((c < 0xb) ? c : 0x15 - c)
                                  : ((c < 0x21) ? c - 0x16 : 0x2b - c); }
    if (local_8094 == 0x2c) { headFrame = c; }
    else { headFrame = (c < 0x16) ? ((c < 0xb) ? c : 0x15 - c)
                                  : ((c < 0x21) ? c - 0xb : 0x36 - c); }
    if (local_809c == 0x2c) { glassesFrame = c; }
    else { glassesFrame = (c < 0x16) ? ((c < 0xb) ? c : 0x15 - c)
                                     : ((c < 0x21) ? c - 0xb : 0x36 - c); }
    FUN_00414070(flagFrame,0x186a0,(int)avatarCanvas);
    FUN_00414070(headFrame,0x186a3,(int)avatarCanvas);
    FUN_00414070(glassesFrame,0x186a2,(int)avatarCanvas);
    FUN_00414070(bodyFrame,0x186a1,(int)avatarCanvas);
  }
  iVar7 = 0;
  puVar12 = (undefined4 *)avatarCanvas;
  do {
    iVar4 = 0;
    puVar8 = puVar12;
    do {
      if ((*(byte *)((int)puVar8 + 1) & 0xf0) != 0) {
        iVar4 = 0x7f;
        puVar11 = avatarCanvas + 0x7f00;   /* last row (bottom-up scan) */
        goto LAB_00414f07;
      }
      iVar4 = iVar4 + 1;
      puVar8 = (undefined4 *)((int)puVar8 + 2);
    } while (iVar4 < 0x80);
    iVar7 = iVar7 + 1;
    puVar12 = puVar12 + 0x40;
  } while (iVar7 < 0x80);
  goto LAB_00415105;
code_r0x004149c7:
  puVar12 = (undefined4 *)puVar12[7];
  uVar2 = puVar12[1];
  if (100000 < uVar2) goto LAB_004149fc;
  goto LAB_004149c5;
code_r0x00414a10:
  puVar12 = (undefined4 *)puVar12[7];
  uVar2 = puVar12[1];
  if (0x186a1 < uVar2) goto LAB_00414a3b;
  goto LAB_00414a0e;
code_r0x00414a4f:
  puVar12 = (undefined4 *)puVar12[7];
  uVar2 = puVar12[1];
  if (0x186a2 < uVar2) goto LAB_00414a7a;
  goto LAB_00414a4d;
code_r0x00414a8e:
  puVar12 = (undefined4 *)puVar12[7];
  uVar2 = puVar12[1];
  if (0x186a3 < uVar2) goto LAB_00414ab9;
  goto LAB_00414a8c;
LAB_00414f07:
  do {
    iVar5 = 0;
    puVar9 = puVar11;
    do {
      iVar1 = iVar4;
      if ((puVar9[1] & 0xf0) != 0) goto LAB_00414f32;
      iVar5 = iVar5 + 1;
      puVar9 = puVar9 + 2;
    } while (iVar5 < 0x80);
    iVar4 = iVar4 + -1;
    puVar11 = puVar11 + -0x100;
    iVar1 = local_8098;
  } while (-1 < iVar4);
LAB_00414f32:
  local_8098 = iVar1;
  iVar4 = 0;
  puVar12 = (undefined4 *)avatarCanvas;
  do {
    iVar5 = 0;
    puVar8 = puVar12;
    do {
      iVar1 = iVar4;
      if ((*(byte *)((int)puVar8 + 1) & 0xf0) != 0) goto LAB_00414f6a;
      iVar5 = iVar5 + 1;
      puVar8 = puVar8 + 0x40;
    } while (iVar5 < 0x80);
    iVar4 = iVar4 + 1;
    puVar12 = (undefined4 *)((int)puVar12 + 2);
    iVar1 = local_80a0;
  } while (iVar4 < 0x80);
LAB_00414f6a:
  local_80a0 = iVar1;
  iVar4 = 0x7f;
  puVar11 = avatarCanvas + 0xfe;    /* last column (right-left scan) */
  do {
    iVar5 = 0;
    puVar9 = puVar11;
    do {
      iVar1 = iVar4;
      if ((puVar9[1] & 0xf0) != 0) goto LAB_00414fa2;
      iVar5 = iVar5 + 1;
      puVar9 = puVar9 + 0x100;
    } while (iVar5 < 0x80);
    iVar4 = iVar4 + -1;
    puVar11 = puVar11 + -2;
    iVar1 = local_80a8;
  } while (-1 < iVar4);
LAB_00414fa2:
  local_80a8 = iVar1;
  puVar12 = operator_new(0x50);
  if (puVar12 == (undefined4 *)0x0) {
    puVar12 = (undefined4 *)0x0;
  }
  else {
    puVar12[1] = param_7;
    puVar12[2] = local_80b0;
    puVar12[3] = 0;
    puVar12[4] = 0;
    *(undefined1 *)(puVar12 + 5) = 0;
    *(undefined1 *)((int)puVar12 + 0x15) = 0;
    *puVar12 = &PTR_FUN_00557524;
    *(undefined1 *)((int)puVar12 + 0x1b) = 0xff;
    *(undefined1 *)((int)puVar12 + 0x1a) = 0;
    *(undefined1 *)((int)puVar12 + 0x19) = 0xff;
    puVar12[8] = 0;
    puVar12[9] = 0;
    puVar12[0xb] = 0;
    puVar12[10] = 0;
    *(undefined1 *)(puVar12 + 0xc) = 0;
    puVar12[0xd] = 0;
    puVar12[0xe] = 0;
  }
  iVar5 = (local_80a8 - local_80a0) + 1;
  iVar4 = (local_8098 - iVar7) + 1;
  puVar12[9] = iVar4;
  iVar4 = iVar4 * iVar5;
  puVar12[0xf] = iVar4 * 2;
  puVar12[10] = local_80a0 + -0x40;
  *(undefined1 *)(puVar12 + 6) = 2;
  puVar12[8] = iVar5;
  puVar12[0xb] = iVar7 + -0x40;
  *(undefined1 *)(puVar12 + 0xc) = 0;
  pvVar6 = operator_new(iVar4 * 2);
  puVar12[0xd] = pvVar6;
  uVar2 = 0;
  if (puVar12[9] != 0) {
    local_80ac = (undefined4 *)((int)avatarCanvas + (iVar7 * 0x80 + local_80a0) * 2);
    do {
      uVar3 = puVar12[8] * 2;
      uVar3 = ((int)uVar3 < 0) - 1 & uVar3;
      puVar8 = local_80ac;
      puVar14 = (undefined4 *)(puVar12[0xd] + puVar12[8] * uVar2 * 2);
      for (uVar10 = uVar3 >> 2; uVar10 != 0; uVar10 = uVar10 - 1) {
        *puVar14 = *puVar8;
        puVar8 = puVar8 + 1;
        puVar14 = puVar14 + 1;
      }
      for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
        *(undefined1 *)puVar14 = *(undefined1 *)puVar8;
        puVar8 = (undefined4 *)((int)puVar8 + 1);
        puVar14 = (undefined4 *)((int)puVar14 + 1);
      }
      uVar2 = uVar2 + 1;
      local_80ac = local_80ac + 0x40;
    } while (uVar2 < (uint)puVar12[9]);
  }
  iVar7 = *(int *)(DAT_00ea0e1c + 0x1c);
  uVar2 = *(uint *)(iVar7 + 4);
  while (uVar2 <= (uint)puVar12[1]) {
    if (uVar2 == puVar12[1]) goto LAB_004150ca;
    iVar7 = *(int *)(iVar7 + 0x1c);
    uVar2 = *(uint *)(iVar7 + 4);
  }
  iVar7 = CreateActiveObjectLayer((int)&g_spriteRegistry);
LAB_004150ca:
  uVar2 = puVar12[2];
  if (uVar2 != 0xffffffff) {
    iVar7 = *(int *)(iVar7 + 0x10);
    uVar3 = *(uint *)(iVar7 + 8);
    if (uVar3 <= uVar2) {
      do {
        if (uVar3 == uVar2) {
          ((VtableDtorFn)*(void **)*puVar12)((void *)puVar12,1);
          goto LAB_00415105;
        }
        iVar7 = *(int *)(iVar7 + 0x10);
        uVar3 = *(uint *)(iVar7 + 8);
      } while (uVar3 <= (uint)puVar12[2]);
    }
  }
  puVar12[4] = iVar7;
  puVar12[3] = *(undefined4 *)(iVar7 + 0xc);
  *(undefined4 **)(*(int *)(iVar7 + 0xc) + 0x10) = puVar12;
  *(undefined4 **)(iVar7 + 0xc) = puVar12;
LAB_00415105:
  local_80b0 = local_80b0 + 1;
  if (0x2b < local_80b0) goto code_r0x00415113;
  goto LAB_00414d80;
code_r0x00415127:
  puVar12 = (undefined4 *)puVar12[7];
  uVar2 = puVar12[1];
  if (100000 < uVar2) goto LAB_0041515c;
  goto LAB_00415125;
code_r0x00415170:
  puVar12 = (undefined4 *)puVar12[7];
  uVar2 = puVar12[1];
  if (0x186a1 < uVar2) goto LAB_0041519b;
  goto LAB_0041516e;
code_r0x00415113:
  puVar12 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
  uVar2 = puVar12[1];
  if (uVar2 < 0x186a1) {
LAB_00415125:
    if (uVar2 != 100000) goto code_r0x00415127;
    puVar8 = (undefined4 *)puVar12[4];
    while (puVar8 != puVar12) {
      thisNode = puVar8;
      puVar14 = (undefined4 *)*puVar8;
      puVar8 = (undefined4 *)puVar8[4];
      ((VtableDtorFn)*puVar14)(thisNode,1);
    }
    puVar12[3] = puVar12;
    puVar12[4] = puVar12;
  }
LAB_0041515c:
  puVar12 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
  uVar2 = puVar12[1];
  if (uVar2 < 0x186a2) {
LAB_0041516e:
    if (uVar2 != 0x186a1) goto code_r0x00415170;
    puVar8 = (undefined4 *)puVar12[4];
    while (puVar8 != puVar12) {
      thisNode = puVar8;
      puVar14 = (undefined4 *)*puVar8;
      puVar8 = (undefined4 *)puVar8[4];
      ((VtableDtorFn)*puVar14)(thisNode,1);
    }
    puVar12[3] = puVar12;
    puVar12[4] = puVar12;
  }
LAB_0041519b:
  puVar12 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
  uVar2 = puVar12[1];
  while( true ) {
    if (0x186a2 < uVar2) goto LAB_004151da;
    if (uVar2 == 0x186a2) break;
    puVar12 = (undefined4 *)puVar12[7];
    uVar2 = puVar12[1];
  }
  puVar8 = (undefined4 *)puVar12[4];
  while (puVar8 != puVar12) {
    thisNode = puVar8;
    puVar14 = (undefined4 *)*puVar8;
    puVar8 = (undefined4 *)puVar8[4];
    ((VtableDtorFn)*puVar14)(thisNode,1);
  }
  puVar12[3] = puVar12;
  puVar12[4] = puVar12;
LAB_004151da:
  puVar12 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
  uVar2 = puVar12[1];
  if (uVar2 < 0x186a4) {
    while (uVar2 != 0x186a3) {
      puVar12 = (undefined4 *)puVar12[7];
      uVar2 = puVar12[1];
      if (0x186a3 < uVar2) {
        return;
      }
    }
    puVar8 = (undefined4 *)puVar12[4];
    while (puVar8 != puVar12) {
      thisNode = puVar8;
      puVar14 = (undefined4 *)*puVar8;
      puVar8 = (undefined4 *)puVar8[4];
      ((VtableDtorFn)*puVar14)(thisNode,1);
    }
    puVar12[3] = puVar12;
    puVar12[4] = puVar12;
  }
  return;
}

