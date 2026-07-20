/* State02_ServerSelect_ProcessPacket - 0x004e02b0 in the original binary.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output - not hand-
 * verified against documented behavior beyond what's already in
 * ARCHITECTURE.md/PROTOCOL.md/FILEFORMATS.md. Calls to unnamed
 * FUN_<address> helpers and DAT_<address>/_DAT_<address> globals are
 * left as-is (undeclared) - this file won't link standalone yet. See
 * src/README.md's "Raw/verbatim ports" section for status and how
 * these get promoted to verified.
 */
#include "ghidra_types.h"
#include <stdio.h>
#include <windows.h>


/* This function's five `(**(code **)(*piVar10 + 4))(s_active_00551e58 /
 * s_ready_00551e80)` calls target a widget virtual (mode-name setter) whose
 * `this` lives in ECX across the whole lookup chain, never reloaded or
 * pushed before the call - confirmed at the original 0x4e0cf7-0x4e0d0a
 * (`mov edx,[ecx]` / `push 0x551e58` / `call [edx+4]`, and the s_ready_...
 * sibling right after) via:
 *   objdump -d -Mintel --start-address=0x4e0cc1 --stop-address=0x4e0d10 \
 *     orig/GunBound.gme
 * The generic `code()` cast this file used defaults to __cdecl, which would
 * push `this` on the stack instead of leaving it in ECX - silently
 * corrupting the call. Matches the GameStateVirtualFn idiom in
 * src/entry/ChangeGameState.c/GameTick.c, extended with the one stack arg
 * this vtable slot actually takes. */
/* VTABLE-DISPATCH CONVENTION (fixed 2026-07-18): slot 1 of a registered
 * active object is its named-state setter. In the ORIGINAL binary this
 * slot is the hand-written __fastcall ResolveNamedState (0x461c60). Our
 * reconstruction instead registers real C++ CButtonWidget objects, whose
 * slot 1 is the C++ virtual CButtonWidget::SetState - a __thiscall method
 * (this in ECX, `name` PUSHED on the stack, `ret 4`).
 *
 * Two dead ends were tried first and BOTH miscompiled:
 *   - __fastcall(this, name): pushed nothing but the __thiscall callee
 *     `ret 4`'d anyway, drifting ESP +4 per call until the pvStack_e4
 *     (== `this`) reload read the opcode local (0x1102) as a pointer.
 *   - __thiscall(this, name) on a *free function pointer*: MSVC 7.1
 *     silently ignores __thiscall on a non-member pointer and emits a
 *     __cdecl call - both args pushed, `this` NOT put in ECX. ECX was
 *     left holding the call-target base (`mov ecx,[eax]` == the vtable),
 *     so SetState ran with this==&vtable and faulted writing m_state at
 *     vtable+0x24 (0x47c288). Confirmed in the rebuilt disassembly.
 *
 * Correct idiom (the project's established __thiscall-from-C emulation):
 * __fastcall with a dummy EDX slot. __fastcall puts arg0 in ECX, arg1 in
 * EDX, arg2+ on the stack, and `ret 4`s the one stack arg - identical ABI
 * to __thiscall(this, name). The EDX dummy is ignored by the thiscall
 * callee. Every object reaching these walks is a C++ widget. */
typedef void (__fastcall *WidgetSetModeNameFn)(void *thisPtr, int edxDummy, const char *modeName);

/* FIXED (2026-07-13), opcode 0x1012's `*payload == 0` branch: the 4
 * `PeekChecksumStateUnderLock(...)` calls here were each followed by a
 * `TEST AH,AH` in the original - Ghidra represented that as a
 * `char extraout_AH*` local, declared but never actually assigned
 * anywhere in the decompiled source (same "declared-but-never-written"
 * bug class as `unaff_ESI`/`in_EAX` found elsewhere this session - a
 * real MSVC recompile would read uninitialized stack garbage here
 * instead of the intended value). Confirmed via objdump at
 * 0x4e043b-0x4e04c6: AH is simply the high byte of EAX, i.e. bits 8-15
 * of PeekChecksumStateUnderLock's own `undefined4` return value - not a
 * separate/secondary output. Fixed by capturing each call's return into
 * `uVar5` and testing `(char)((uint)uVar5 >> 8) < 0` in its place
 * (equivalent to the original's `TEST AH,AH` + `JS`/`JNS`). Note this
 * predicate is currently always false: PeekPacketChecksumState.c's own
 * header documents that it unconditionally returns 0 as a deliberate
 * CValueGuard-migration bring-up stub, so this fix only removes
 * undefined behavior - it doesn't change observable output until that
 * separate, larger migration lands. */

/* WARNING: Removing unreachable block (ram,0x004e0fc9) */
/* WARNING: Removing unreachable block (ram,0x004e08de) */
/* WARNING: Removing unreachable block (ram,0x004e08e8) */
/* WARNING: Removing unreachable block (ram,0x004e106e) */
/* WARNING: Removing unreachable block (ram,0x004e1078) */
/* WARNING: Removing unreachable block (ram,0x004e10cc) */
/* WARNING: Removing unreachable block (ram,0x004e10d6) */
/* WARNING: Removing unreachable block (ram,0x004e0cc1) */
/* WARNING: Removing unreachable block (ram,0x004e0ccb) */
/* WARNING: Removing unreachable block (ram,0x004e093c) */
/* WARNING: Removing unreachable block (ram,0x004e0946) */
/* WARNING: Removing unreachable block (ram,0x004e1086) */
/* WARNING: Removing unreachable block (ram,0x004e1090) */
/* WARNING: Removing unreachable block (ram,0x004e0cd9) */
/* WARNING: Removing unreachable block (ram,0x004e0ce3) */
/* WARNING: Removing unreachable block (ram,0x004e08f6) */
/* WARNING: Removing unreachable block (ram,0x004e0900) */

void __thiscall
State02_ServerSelect_ProcessPacket(void *this,int payloadLen,ushort opcode,short *payload)

{
  short sVar1;
  char cVar2;
  u_short uVar3;
  undefined2 *puVar4;
  undefined4 uVar5;
  uint uVar6;
  byte bVar7;
  int iVar8;
  char *pcVar9;
  int *piVar10;
  uint uVar11;
  byte bVar12;
  char *pcVar13;
  short *psVar14;
  short *psVar15;
  uint *puVar16;
  uint *puVar17;
  byte *pbVar18;
  byte *pbVar19;
  int iVar20;
  undefined4 *puVar21;
  byte *pbVar22;
  bool bVar23;
  uint uStack_f0;
  uint uStack_ec;
  char cStack_e5;
  void *pvStack_e4;
  byte bStack_dd;
  int iStack_dc;
  int iStack_d8;
  int iStack_d4;
  sockaddr sStack_d0;
  undefined4 uStack_c0;
  undefined4 uStack_bc;
  undefined4 uStack_b8;
  undefined4 uStack_b4;
  undefined4 uStack_b0;
  undefined1 auStack_a0 [32];
  /* BuildSystemInfoBlob's 2nd output (orig ESI, dropped) - NOT verified
   * against this call site's original disassembly; added only to satisfy
   * the now-2-parameter signature (see BuildSystemInfoBlob.c). Revisit if
   * this code path is ever exercised. */
  undefined4 systemInfoBlob2[6];
  byte abStack_80 [128];
  
  iVar20 = g_clientContext;
  pvStack_e4 = this;
  if (0x101f < opcode) {
    if (opcode == 0x1102) {
      if (*payload != 0) {
        return;
      }
      *(bool *)((int)this + 0x1c) = (char)payload[1] == '\0';
      cVar2 = *(char *)((int)payload + 3);
      *(char *)(iVar20 + 0x3f808) = cVar2;
      /* BRING-UP VALIDATION HACK (2026-07-17): the real ServerSelect
       * input-enable happens on the broker auth handshake (opcode 0x1012
       * authenticationResponse -> m_inputEnabled=1), which the test broker
       * does not run - it only serves the 0x1102 directory. Force input
       * enabled here so the connect path can be exercised end-to-end
       * (Enter -> HandleKeyInput -> ConnectToSelectedServer -> world
       * server). DAT_007933b8=1 makes Enter auto-select the first online
       * server. REMOVE once the broker completes 0x1010->0x1012. */
      *(undefined1 *)((int)this + 0x24) = 1;
      DAT_007933b8 = 1;
      pbVar19 = (byte *)(payload + 2);
      if (*(char *)((int)this + 0x10) == '\x02') {
        *(bool *)((int)this + 0x1c) = cVar2 == '\x10';
      }
      if (*(char *)(iVar20 + 0x3f808) != '\0') {
        *(undefined4 *)((int)this + 0x14) = *(undefined4 *)((int)this + 0x18);
      }
      puVar21 = (undefined4 *)(iVar20 + 0x4004a);
      for (iVar8 = 0x400; iVar8 != 0; iVar8 = iVar8 + -1) {
        *puVar21 = 0;
        puVar21 = puVar21 + 1;
      }
      iStack_d4 = 0;
      if (*(char *)(iVar20 + 0x3f808) != '\0') {
        iStack_dc = 0;
        uStack_f0 = 0;
        iStack_d8 = 0x410aa;
        do {
          *(undefined2 *)(iStack_d8 + -0x1890 + iVar20) = *(undefined2 *)pbVar19;
          *(byte *)(iVar20 + 0x3f83a + iStack_d4) = pbVar19[2];
          uVar6 = (uint)pbVar19[3];
          pbVar18 = pbVar19 + 4;
          uVar11 = (uint)(pbVar19[3] >> 2);
          pbVar19 = pbVar18;
          pbVar22 = (byte *)(uStack_f0 + 0x3f84a + iVar20);
          for (; uVar11 != 0; uVar11 = uVar11 - 1) {
            *(undefined4 *)pbVar22 = *(undefined4 *)pbVar19;
            pbVar19 = pbVar19 + 4;
            pbVar22 = pbVar22 + 4;
          }
          for (uVar11 = uVar6 & 3; uVar11 != 0; uVar11 = uVar11 - 1) {
            *pbVar22 = *pbVar19;
            pbVar19 = pbVar19 + 1;
            pbVar22 = pbVar22 + 1;
          }
          pbVar18 = pbVar18 + uVar6;
          *(undefined1 *)(uVar6 + uStack_f0 + 0x3f84a + iVar20) = 0;
          uVar6 = (uint)*pbVar18;
          pbVar19 = pbVar18 + 1;
          pbVar22 = abStack_80;
          for (uVar11 = (uint)(*pbVar18 >> 2); uVar11 != 0; uVar11 = uVar11 - 1) {
            *(undefined4 *)pbVar22 = *(undefined4 *)pbVar19;
            pbVar19 = pbVar19 + 4;
            pbVar22 = pbVar22 + 4;
          }
          for (uVar11 = uVar6 & 3; uVar11 != 0; uVar11 = uVar11 - 1) {
            *pbVar22 = *pbVar19;
            pbVar19 = pbVar19 + 1;
            pbVar22 = pbVar22 + 1;
          }
          pbVar19 = pbVar18 + 1 + uVar6;
          abStack_80[uVar6] = 0;
          RenderWrappedText(iStack_dc + 0x4004a + iVar20,abStack_80,0x40,0x24,0x100,1);
          iVar8 = iStack_d4;
          *(undefined4 *)(iVar20 + 0x4104a + iStack_d4 * 4) = *(undefined4 *)pbVar19;
          uVar3 = htons(*(u_short *)(pbVar19 + 4));
          iVar20 = g_clientContext;
          *(u_short *)(iStack_d8 + -0x20 + g_clientContext) = uVar3;
          *(undefined2 *)(iStack_d8 + iVar20) = *(undefined2 *)(pbVar19 + 6);
          *(undefined2 *)(iStack_d8 + 0x20 + iVar20) = *(undefined2 *)(pbVar19 + 8);
          *(undefined2 *)(iStack_d8 + 0x40 + iVar20) = *(undefined2 *)(pbVar19 + 10);
          bVar23 = pbVar19[0xc] != 0;
          *(bool *)(iVar20 + 0x3f809 + iVar8) = bVar23;
          pbVar19 = pbVar19 + 0xd;
          if (!bVar23) {
            *(undefined1 *)(iVar20 + 0x3f83a + iVar8) = 3;
          }
          *(undefined1 *)(iVar20 + 0x4110a + iVar8) = 0;
          uVar6 = (uint)*(ushort *)(iStack_d8 + -0x1890 + iVar20);
          if (((*(uint *)(iVar20 + 0x3f804) == uVar6) || (uVar6 == DAT_005b2b64)) && (bVar23)) {
            *(int *)((int)pvStack_e4 + 8) = iVar8;
          }
          iStack_dc = iStack_dc + 0x100;
          iStack_d4 = iVar8 + 1;
          iStack_d8 = iStack_d8 + 2;
          uStack_f0 = uStack_f0 + 0x80;
        } while (iStack_d4 < (int)(uint)*(byte *)(iVar20 + 0x3f808));
      }
      cVar2 = PeekPacketChecksumBool();
      iVar20 = g_clientContext;
      if (cVar2 != '\0') {
        uVar6 = *(ushort *)(g_clientContext + 0x3b96b) & 0x8000000f;
        if (*(char *)(uVar6 + 0x3f809 + g_clientContext) == '\0') {
          pbVar19 = (byte *)(g_clientContext + 0x3b968);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar8 = _rand();
          *pbVar19 = (byte)iVar8;
          iVar8 = _rand();
          bVar12 = *pbVar19;
          *(byte *)(iVar20 + 0x3b969) = (byte)iVar8;
          bVar7 = bVar12 & 7;
          bVar7 = ~('\x01' << bVar7) & (byte)iVar8 | '\0' << bVar7;
          *(byte *)(iVar20 + 0x3b969) = bVar7;
          *(byte *)(iVar20 + 0x3b96a) = bVar12 + bVar7 + -0x34;
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        }
        else {
          *(uint *)((int)pvStack_e4 + 8) = uVar6;
          ConnectToSelectedServer(pvStack_e4,uVar6);
        }
      }
      g_serverWaitTicks = 0xffffffff;
      if (((*(int *)(*(int *)(DAT_00e9be94 + 0x1c) + 4) == 0) &&
          (piVar10 = *(int **)(*(int *)(DAT_00e9be94 + 0x1c) + 0x10), piVar10[2] == 0)) &&
         ((piVar10[9] == 3 || (piVar10[9] == -1)))) {
        if ((char)piVar10[0x13] == '\x01') {
          (*(WidgetSetModeNameFn *)(*piVar10 + 4))(piVar10, 0, s_active_00551e58);
        }
        else {
          (*(WidgetSetModeNameFn *)(*piVar10 + 4))(piVar10, 0, s_ready_00551e80);
        }
      }
      if (*(int *)(*(int *)(DAT_00e9be94 + 0x1c) + 4) == 0) {
        piVar10 = *(int **)(*(int *)(DAT_00e9be94 + 0x1c) + 0x10);
        uVar6 = piVar10[2];
        while (uVar6 < 2) {
          if (uVar6 == 1) {
            if ((piVar10[9] == 3) || (piVar10[9] == -1)) {
              if ((char)piVar10[0x13] == '\x01') {
                (*(WidgetSetModeNameFn *)(*piVar10 + 4))(piVar10, 0, s_active_00551e58);
              }
              else {
                (*(WidgetSetModeNameFn *)(*piVar10 + 4))(piVar10, 0, s_ready_00551e80);
              }
            }
            break;
          }
          piVar10 = (int *)piVar10[4];
          uVar6 = piVar10[2];
        }
      }
      iVar20 = *(int *)((int)pvStack_e4 + 8);
    }
    else {
      if (opcode != 0x2001) {
        return;
      }
      if (*payload == 0) {
        FUN_004d24f0();
        iVar8 = DAT_007934ec;
        iVar20 = g_clientContext;
        DAT_007934ec = DAT_007934e8;
        DAT_007934e8 = iVar8;
        *(uint *)(g_clientContext + 0x3f804) =
             (uint)*(ushort *)(g_clientContext + 0x3f81a + *(int *)((int)this + 0x68) * 2);
        DAT_005b2b64 = 0xffffffff;
        pcVar9 = (char *)(*(int *)((int)this + 0x68) * 0x80 + 0x3f84a + iVar20);
        pcVar13 = (char *)(iVar20 + 0x3b8e8);
        do {
          cVar2 = *pcVar9;
          pcVar9 = pcVar9 + 1;
          *pcVar13 = cVar2;
          pcVar13 = pcVar13 + 1;
        } while (cVar2 != '\0');
        if (DAT_00793529 == '\0') {
          FUN_00404410(&DAT_00e53e88);
        }
        else {
          BuildSystemInfoBlob(auStack_a0, systemInfoBlob2);
          if (DAT_00e55a64 != (int *)0x0) {
            (**(code **)(*DAT_00e55a64 + 0xc))(&DAT_005b1c70,DAT_005b33f4,auStack_a0,&uStack_c0);
          }
          DAT_00793529 = '\0';
        }
        if (g_directLinkConnection == 0) {
          FUN_00404410(&DAT_00e53e88);
        }
        else {
          FUN_00405ba0();
        }
        g_pendingGameState = 3;
        g_stateChangeRequested = 1;
        ChangeGameState(3);
        return;
      }
      cVar2 = PeekPacketChecksumBool();
      if (cVar2 != '\0') {
        /* RECOVERED (2026-07-19), orig 0x4e08b2-0x4e08be:
         * `mov eax,[0x5b3484]` / `push 0` / `add eax,0x3b968`. */
        SetGuardedBool(0,g_clientContext + 0x3b968);
      }
      *(undefined1 *)((int)this + 6) = 1;
      *(undefined1 *)((int)this + 0x24) = 1;
      g_serverWaitTicks = 0xffffffff;
      if (((*(int *)(*(int *)(DAT_00e9be94 + 0x1c) + 4) == 0) &&
          (piVar10 = *(int **)(*(int *)(DAT_00e9be94 + 0x1c) + 0x10), piVar10[2] == 0)) &&
         ((piVar10[9] == 3 || (piVar10[9] == -1)))) {
        if ((char)piVar10[0x13] == '\x01') {
          (*(WidgetSetModeNameFn *)(*piVar10 + 4))(piVar10, 0, s_active_00551e58);
        }
        else {
          (*(WidgetSetModeNameFn *)(*piVar10 + 4))(piVar10, 0, s_ready_00551e80);
        }
      }
      iVar20 = *(int *)(DAT_00e9be94 + 0x1c);
      bVar23 = *(int *)(iVar20 + 4) == 0;
      if (bVar23) {
        do {
          if (bVar23) {
            piVar10 = *(int **)(iVar20 + 0x10);
            uVar6 = piVar10[2];
            if (uVar6 < 2) goto LAB_004e0d3c;
            goto LAB_004e0d7f;
          }
          iVar20 = *(int *)(iVar20 + 0x1c);
          bVar23 = true;
        } while (*(int *)(iVar20 + 4) == 0);
        iVar20 = *(int *)((int)this + 8);
      }
      else {
LAB_004e0d7f:
        iVar20 = *(int *)((int)this + 8);
      }
    }
    goto LAB_004e1121;
  }
  if (opcode == 0x101f) {
    DAT_00e55e3c = 1;
    DAT_007934f8 = 1;
    DAT_005b2b54 = *(undefined4 *)payload;
    DAT_005b343c = payload[2];
    return;
  }
  if (opcode == 0x1001) {
    *(undefined1 *)((int)this + 5) = 0;
    BuildSystemInfoBlob(auStack_a0, systemInfoBlob2);
    /* BRING-UP HACK (2026-07-18): the login credentials normally arrive as the
     * launcher's 96-hex session token - WinMain sscanfs it into DAT_005b3440
     * and BuildSystemInfoBlob AES-decrypts those 3 blocks into credKey (the
     * username, strncpy'd 16 bytes and encrypted with the fixed login key =
     * the server's `encryptedUsername`) and credStr (the password, SHA1'd into
     * the session key). Launching gunbound_bringup.exe directly leaves that
     * blob ALL-ZERO, so the decrypt yields garbage and the world server
     * answers 0x1012 status 0x0010 (badUsername) - confirmed in its own log,
     * which showed an all-zero authenticationRequest body. Inject a known
     * login so the auth -> join-channel -> lobby path can be exercised.
     * The test server auto-registers any valid username with password "1234".
     * REMOVE once a real launcher token is supplied. */
    {
      static const char kUser[] = "test";
      static const char kPass[] = "1234";
      int ci;
      for (ci = 0; ci < 0x14; ci++) { ((char *)systemInfoBlob2)[ci] = '\0'; }
      for (ci = 0; ci < (int)sizeof(kUser); ci++) { ((char *)systemInfoBlob2)[ci] = kUser[ci]; }
      /* auStack_a0's first 0x14 bytes are copied VERBATIM into the packet as
       * the password field (see the copy below), so the whole 0x14 must be
       * cleared - zeroing only the 5 bytes of kPass left BuildSystemInfoBlob's
       * decrypted-garbage tail in the packet, and the server compared
       * "1234\0\xe7\x85\x88..." against "1234" and answered badPassword. */
      for (ci = 0; ci < 0x14; ci++) { ((char *)auStack_a0)[ci] = '\0'; }
      for (ci = 0; ci < (int)sizeof(kPass); ci++) { ((char *)auStack_a0)[ci] = kPass[ci]; }
    }
    iVar20 = DAT_007934ec;
    *(undefined2 *)(DAT_007934ec + 0x4d4) = 0x1010;
    *(undefined4 *)(iVar20 + 0x44d0) = 6;
    /* Login handshake block. Arg mapping recovered from orig 0x4e09b7-
     * 0x4e09fa (see AppendEncodedBlock.c's header): param_1 = the server's
     * 4-byte nonce *(int *)payload (hashed inside EncodeHandshakeBlock),
     * unaff_EBX = the connection context DAT_007934ec, and the two
     * credential/system-info buffers BuildSystemInfoBlob just filled -
     * systemInfoBlob2 (credKey/ESI, strncpy'd) and auStack_a0 (credStr/EAX,
     * null-terminated). Previously this dropped both credential args (ESI/
     * EAX read uninitialised -> fault at EncodeHandshakeBlock+0x15) and put
     * the stack buffer &uStack_c0 where the context belonged. */
    AppendEncodedBlock(*(undefined4 *)payload,DAT_007934ec,(char *)systemInfoBlob2,
                       (char *)auStack_a0);
    iVar20 = DAT_007934ec;
    puVar21 = (undefined4 *)(*(int *)(DAT_007934ec + 0x44d0) + 0x4d0 + DAT_007934ec);
    /* The block copied into the outgoing packet is auStack_a0's first 0x14
     * bytes (orig post-call reads [esp+0x40..0x50] = auStack_a0), not the
     * uStack_c0 slot Ghidra split off. */
    *puVar21 = *(undefined4 *)auStack_a0;
    puVar21[1] = *(undefined4 *)(auStack_a0 + 4);
    puVar21[2] = *(undefined4 *)(auStack_a0 + 8);
    puVar21[3] = *(undefined4 *)(auStack_a0 + 0xc);
    puVar21[4] = *(undefined4 *)(auStack_a0 + 0x10);
    *(int *)(iVar20 + 0x44d0) = *(int *)(iVar20 + 0x44d0) + 0x14;
    uVar5 = PeekChecksumStateUnderLock(&DAT_00796878);
    iVar8 = DAT_007934ec;
    *(undefined4 *)(*(int *)(DAT_007934ec + 0x44d0) + 0x4d0 + DAT_007934ec) = uVar5;
    iVar20 = *(int *)(iVar8 + 0x44d0);
    *(int *)(iVar8 + 0x44d0) = iVar20 + 4;
    *(undefined1 *)(iVar20 + 0x4d4 + iVar8) = *(undefined1 *)(g_clientContext + 0xebee4);
    *(int *)(iVar8 + 0x44d0) = *(int *)(iVar8 + 0x44d0) + 1;
    uStack_f0 = 0x10;
    getsockname(*(SOCKET *)(*(int *)(iVar8 + 0x84e0) + 0x24),&sStack_d0,(int *)&uStack_f0);
    iVar20 = DAT_007934ec;
    *(undefined4 *)(*(int *)(DAT_007934ec + 0x44d0) + 0x4d0 + DAT_007934ec) =
         SUBFIELD(sStack_d0.sa_data,2,undefined4);
    *(int *)(iVar20 + 0x44d0) = *(int *)(iVar20 + 0x44d0) + 4;
    uStack_f0 = 0x10;
    getsockname(DAT_00e55cf4,&sStack_d0,(int *)&uStack_f0);
    iVar20 = DAT_007934ec;
    *(undefined2 *)(*(int *)(DAT_007934ec + 0x44d0) + 0x4d0 + DAT_007934ec) =
         SUBFIELD(sStack_d0.sa_data,0,undefined2);
    *(int *)(iVar20 + 0x44d0) = *(int *)(iVar20 + 0x44d0) + 2;
    /* RECOVERED (2026-07-18), orig 0x4e0b07 `mov ecx,0x20`: this call site
     * passes param_1 = 0x20, NOT 0 - EncodePacketBody's param_1 is the OFFSET
     * within the packet body at which the opcode-checksummed encoding starts
     * (it encodes `cursor - param_1` bytes from body+param_1). The
     * authenticationRequest's first 0x20 bytes must stay RAW: bytes 0..15 are
     * `encryptedUsername`, a single AES block encrypted directly with the fixed
     * login key, and 16..31 the `unknown` field; only `encryptedData` from
     * +0x20 on is packet-encoded with the session key. EncodePacketBody.c's
     * header generalised "ECX is always literal 0" from the OTHER four call
     * sites - it does not hold here, and wrapping the username block was why
     * the world server could not decrypt it (badUsername). */
    EncodePacketBody(0x20,iVar20);
    SendOutgoingPacket(iVar20);
    return;
  }
  if (opcode != 0x1012) {
    return;
  }
  if (*payload != 0) {
    switch(*payload) {
    case 0x5001:
      *(undefined4 *)((int)this + *(int *)((int)this + 0x68) * 4 + 0x28) = 0x1d;
      break;
    case 0x5011:
      *(undefined4 *)((int)this + *(int *)((int)this + 0x68) * 4 + 0x28) = 0x1e;
      break;
    case 0x5012:
      *(undefined4 *)((int)this + *(int *)((int)this + 0x68) * 4 + 0x28) = 0x1f;
      break;
    case 0x5013:
      *(undefined4 *)((int)this + *(int *)((int)this + 0x68) * 4 + 0x28) = 0x20;
    }
    cVar2 = PeekPacketChecksumBool();
    if (cVar2 != '\0') {
      /* RECOVERED (2026-07-19), orig 0x4e0c8d-0x4e0c99: same cell,
       * `mov eax,[0x5b3484]` / `push 0` / `add eax,0x3b968`. */
      SetGuardedBool(0,g_clientContext + 0x3b968);
    }
    g_serverWaitTicks = 0xffffffff;
    if (((*(int *)(*(int *)(DAT_00e9be94 + 0x1c) + 4) == 0) &&
        (piVar10 = *(int **)(*(int *)(DAT_00e9be94 + 0x1c) + 0x10), piVar10[2] == 0)) &&
       ((piVar10[9] == 3 || (piVar10[9] == -1)))) {
      if ((char)piVar10[0x13] == '\x01') {
        (*(WidgetSetModeNameFn *)(*piVar10 + 4))(piVar10, 0, s_active_00551e58);
      }
      else {
        (*(WidgetSetModeNameFn *)(*piVar10 + 4))(piVar10, 0, s_ready_00551e80);
      }
    }
    if (*(int *)(*(int *)(DAT_00e9be94 + 0x1c) + 4) == 0) {
      piVar10 = *(int **)(*(int *)(DAT_00e9be94 + 0x1c) + 0x10);
      uVar6 = piVar10[2];
      while (uVar6 < 2) {
        if (uVar6 == 1) {
          if ((piVar10[9] == 3) || (piVar10[9] == -1)) {
            if ((char)piVar10[0x13] == '\x01') {
              (*(WidgetSetModeNameFn *)(*piVar10 + 4))(piVar10, 0, s_active_00551e58);
            }
            else {
              (*(WidgetSetModeNameFn *)(*piVar10 + 4))(piVar10, 0, s_ready_00551e80);
            }
          }
          break;
        }
        piVar10 = (int *)piVar10[4];
        uVar6 = piVar10[2];
      }
    }
    InvokeWidget(2,*(int *)((int)this + 8) != -1);
    *(undefined1 *)((int)this + 0x24) = 1;
    *(undefined1 *)((int)this + 6) = 1;
    return;
  }
  uStack_f0 = *(uint *)(payload + 1);
  iStack_dc = 0x10;
  getpeername(*(SOCKET *)(*(int *)(DAT_007934ec + 0x84e0) + 0x24),&sStack_d0,&iStack_dc);
  iVar20 = g_clientContext;
  *(undefined4 *)(g_clientContext + 0x23330) = *(undefined4 *)(payload + 3);
  *(undefined4 *)(iVar20 + 0x23334) = *(undefined4 *)(payload + 5);
  uVar5 = *(undefined4 *)(payload + 7);
  *(undefined1 *)(iVar20 + 0x2333c) = 0;
  *(undefined4 *)(iVar20 + 0x23338) = uVar5;
  puVar16 = (uint *)(payload + 9);
  FUN_004e76d0(&uStack_f0);
  if (payloadLen < 0xa1) goto LAB_004e071c;
  FUN_005204f0(g_clientContext + 0x23330);
  uVar6 = *puVar16;
  uStack_ec = *(uint *)(payload + 0xb);
  uStack_f0 = uVar6;
  QueueOutgoingPacketField(uVar6 & 0xffff);
  /* RECOVERED (2026-07-19), orig 0x4e03cc-0x4e03e4: `mov eax,[0x5b3484]`
   * (= g_clientContext) / `add eax,0x3b498` / `test edi,0x8000` / push 1|0 /
   * `call 0x406500`. This is the site that faulted right after the world
   * server accepted the login. */
  SetGuardedBool((uVar6 & 0x8000) != 0,g_clientContext + 0x3b498);
  QueueOutgoingPacketField(uStack_f0 >> 0x10);
  QueueOutgoingPacketField(uStack_ec & 0xffff);
  QueueOutgoingPacketField(uStack_ec >> 0x10);
  cVar2 = PeekPacketChecksumBool();
  if (cVar2 == '\0') {
    uVar5 = PeekChecksumStateUnderLock(g_clientContext + 0x3ae2c);
    if ((char)((uint)uVar5 >> 8) < 0) {
      QueueOutgoingPacketField(0);
    }
    uVar5 = PeekChecksumStateUnderLock(g_clientContext + 0x3b050);
    if ((char)((uint)uVar5 >> 8) < 0) goto LAB_004e04b5;
  }
  else {
    uVar5 = PeekChecksumStateUnderLock(g_clientContext + 0x3ae2c);
    if (-1 < (char)((uint)uVar5 >> 8)) {
      QueueOutgoingPacketField(0);
    }
    uVar5 = PeekChecksumStateUnderLock(g_clientContext + 0x3b050);
    if (-1 < (char)((uint)uVar5 >> 8)) {
LAB_004e04b5:
      QueueOutgoingPacketField(0);
    }
  }
  iVar20 = g_clientContext;
  *(undefined4 *)(g_clientContext + 0x23313) = *(undefined4 *)(payload + 0xd);
  *(undefined4 *)(iVar20 + 0x23317) = *(undefined4 *)(payload + 0xf);
  *(undefined1 *)(iVar20 + 0x2331b) = 0;
  if ((*(char *)(iVar20 + 0x2331a) < '\0') && (-1 < *(char *)(iVar20 + 0x23319))) {
    *(undefined1 *)(iVar20 + 0x2331a) = 0;
  }
  *(short *)(iVar20 + 0x23344) = payload[0x11] + 4;
  if (*(short *)(iVar20 + 0x23344) == -1) {
    *(undefined2 *)(iVar20 + 0x23344) = 0x17;
  }
  sVar1 = payload[0x12];
  *(short *)(iVar20 + 0x23346) = sVar1 + 4;
  if ((short)(sVar1 + 4) == -1) {
    *(undefined2 *)(iVar20 + 0x23346) = 0x17;
  }
  QueueOutgoingPacketField(payload[0x13]);
  QueueOutgoingPacketField(*(undefined4 *)(payload + 0x14));
  QueueOutgoingPacketField(*(undefined4 *)(payload + 0x16));
  QueueOutgoingPacketField(*(undefined4 *)(payload + 0x18));
  psVar14 = payload + 0x1a;
  iVar20 = 0;
  do {
    QueueOutgoingPacketField(*(undefined4 *)psVar14);
    QueueOutgoingPacketField(*(undefined4 *)(psVar14 + 2));
    iVar20 = iVar20 + 0x224;
    psVar14 = psVar14 + 4;
  } while (iVar20 < 0x2ad0);
  pvStack_e4 = (void *)0x0;
  do {
    psVar15 = psVar14;
    uVar5 = *(undefined4 *)psVar15;
    uStack_f0 = (int)pvStack_e4 + g_clientContext + 0x2e718;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(uVar5);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar5 = *(undefined4 *)(psVar15 + 2);
    uStack_f0 = (int)pvStack_e4 + g_clientContext + 0x311e8;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField(uVar5);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    pvStack_e4 = (void *)((int)pvStack_e4 + 0x224);
    psVar14 = psVar15 + 4;
  } while ((int)pvStack_e4 < 0x2ad0);
  uVar5 = *(undefined4 *)(psVar15 + 4);
  uStack_f0 = g_clientContext + 0x39258;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(uVar5);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar5 = *(undefined4 *)(psVar15 + 6);
  uStack_f0 = g_clientContext + 0x3947c;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(uVar5);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar5 = *(undefined4 *)(psVar15 + 8);
  uStack_f0 = g_clientContext + 0x39ae8;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(uVar5);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar5 = *(undefined4 *)(psVar15 + 10);
  uStack_f0 = g_clientContext + 0x39d0c;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(uVar5);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  puVar16 = (uint *)(psVar15 + 0xc);
LAB_004e071c:
  uVar6 = *puVar16;
  uStack_f0 = g_clientContext + 0x396a0;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(uVar6);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar20 = g_clientContext;
  puVar4 = (undefined2 *)(&DAT_006aa658 + g_clientContext);
  iVar8 = 4;
  puVar16 = puVar16 + 1;
  do {
    puVar17 = puVar16;
    *puVar4 = (short)*puVar17;
    puVar4 = puVar4 + 1;
    iVar8 = iVar8 + -1;
    puVar16 = puVar17 + 1;
  } while (iVar8 != 0);
  cStack_e5 = (char)puVar17[1] == '\x01';
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar8 = _rand();
  *(byte *)(iVar20 + 0x23310) = (byte)iVar8;
  iVar8 = _rand();
  bStack_dd = *(byte *)(iVar20 + 0x23310);
  *(byte *)(iVar20 + 0x23311) = (byte)iVar8;
  uStack_f0 = bStack_dd & 7;
  bVar12 = ~('\x01' << (sbyte)uStack_f0) & (byte)iVar8 | (cStack_e5 != '\0') << (sbyte)uStack_f0;
  *(byte *)(iVar20 + 0x23311) = bVar12;
  *(byte *)(iVar20 + 0x23312) = bStack_dd + bVar12 + -0x34;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar5 = *(undefined4 *)((int)puVar17 + 5);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EncodeOutgoingPacketField(uVar5);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  {
    /* BRING-UP EXPERIMENT (2026-07-19): the original sends joinChannelRequest
     * (0x2000) here after auth success; our client's normal trigger for that
     * is not yet found. Fire it once directly to validate the join->0x2001->
     * lobby path. Replicates State02_ServerSelect_OnTopButton's param_2==3. */
    static int joinedOnce = 0;
    if (!joinedOnce) {
      int cj = DAT_007934ec;
      joinedOnce = 1;
      *(undefined2 *)(cj + 0x4d4) = 0x2000;
      *(undefined4 *)(cj + 0x44d0) = 6;
      *(undefined2 *)(*(int *)(cj + 0x44d0) + 0x4d0 + cj) = 0xffff;
      *(int *)(cj + 0x44d0) = *(int *)(cj + 0x44d0) + 2;
      SendOutgoingPacket(cj);
    }
  }
  *(undefined1 *)(g_clientContext + 0xebee4) = 0;
  if (payloadLen < 0x1c) {
    return;
  }
  if (g_directLinkConnection != 0) {
    return;
  }
  DAT_00793529 = 1;
  return;
  while( true ) {
    piVar10 = (int *)piVar10[4];
    uVar6 = piVar10[2];
    if (1 < uVar6) break;
LAB_004e0d3c:
    if (uVar6 == 1) {
      if ((piVar10[9] != 3) && (piVar10[9] != -1)) goto LAB_004e0d7f;
      if ((char)piVar10[0x13] == '\x01') {
        (*(WidgetSetModeNameFn *)(*piVar10 + 4))(piVar10, 0, s_active_00551e58);
        iVar20 = *(int *)((int)this + 8);
        goto LAB_004e1121;
      }
      (*(WidgetSetModeNameFn *)(*piVar10 + 4))(piVar10, 0, s_ready_00551e80);
      goto LAB_004e0d7f;
    }
  }
  iVar20 = *(int *)((int)this + 8);
LAB_004e1121:
  InvokeWidget(2,iVar20 != -1);
  return;
}

