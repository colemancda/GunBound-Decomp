/* State05_Logo1_OnExit - 0x00443430 in the original binary.
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
#include <windows.h>


void State05_Logo1_OnExit(void)

{
  uint uVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined2 *puVar4;
  undefined4 *puVar5;
  int iVar6;
  /* FIXED (2026-07-13): BOTH of BuildSystemInfoBlob's output blobs need to
   * be real arrays, not groups of individually-declared uStack_XX locals
   * written via pointer aliasing (`param_1[1] = ...`) - MSVC does not
   * guarantee such locals land contiguously in memory (confirmed by its
   * own C4700 "used without having been initialized" warnings on the very
   * locals this function's read-back code depends on), so the compiler is
   * free to place them anywhere, silently breaking the aliasing this raw
   * port relied on. The 2nd blob was additionally routed through a
   * completely SEPARATE, never-read-back local (systemInfoBlob2) while the
   * read-back site referenced 5 different, never-written uStack_XX locals -
   * a genuine uninitialized-stack-read bug: garbage was being copied into
   * the outgoing packet and sent over the network via SendSocketData
   * below. Fixed by making both blobs real 4-dword arrays that the
   * BuildSystemInfoBlob call and the read-back code both reference
   * consistently. */
  undefined4 systemInfoBlob1[4];
  undefined4 systemInfoBlob2[6];
  /* FIXED (2026-07-14): the trailing SendSocketData call only passed 2 of
   * its 3 real args and dropped the buffer ("this") entirely - same bug
   * as FUN_00405ba0.c's own already-fixed SendSocketData call, which
   * shares this exact object shape (g_directLinkConnection, connObj at +0x2004,
   * write cursor at +0x2000). Confirmed via angr disassembly at
   * 0x443515-0x44352b. NOTE: this raw C port is superseded at runtime by
   * the C++ CState05Logo1::OnExit (src/cxx/State05_Logo1.cpp,
   * g_gameStateVTableArray[5]) - fixed here too for consistency, but the
   * live bug is the one in that file. */

  puVar5 = *(undefined4 **)(DAT_00ea0e1c + 0x1c);
  uVar1 = puVar5[1];
  while( true ) {
    if (10000 < uVar1) goto LAB_00443475;
    if (uVar1 == 10000) break;
    puVar5 = (undefined4 *)puVar5[7];
    uVar1 = puVar5[1];
  }
  puVar2 = (undefined4 *)puVar5[4];
  while (puVar2 != puVar5) {
    puVar3 = (undefined4 *)*puVar2;
    puVar2 = (undefined4 *)puVar2[4];
    (*(code *)*puVar3)(1);
  }
  puVar5[3] = puVar5;
  puVar5[4] = puVar5;
LAB_00443475:
  BuildSystemInfoBlob(systemInfoBlob1, systemInfoBlob2);
  puVar4 = g_directLinkConnection;
  if (g_directLinkConnection != (undefined2 *)0x0) {
    /* g_directLinkConnection[1] in the original: rewritten through puVar4 (same
     * value, cast to undefined2* two lines up) since the global itself
     * is declared uint32_t - it's used as a plain integer/address in
     * ~30 other files, so retyping it as a pointer isn't worth the
     * cross-file risk for this one subscript. */
    puVar4[1] = 0xa000;
    *(undefined4 *)(puVar4 + 0x1000) = 4;
    *(undefined4 *)(puVar4 + 2) = 1;
    iVar6 = *(int *)(puVar4 + 0x1000);
    *(int *)(puVar4 + 0x1000) = iVar6 + 4;
    puVar5 = (undefined4 *)(iVar6 + 4 + (int)puVar4);
    *puVar5 = systemInfoBlob1[0];
    puVar5[1] = systemInfoBlob1[1];
    puVar5[2] = systemInfoBlob1[2];
    puVar5[3] = systemInfoBlob1[3];
    iVar6 = *(int *)(puVar4 + 0x1000);
    *(int *)(puVar4 + 0x1000) = iVar6 + 0x10;
    puVar5 = (undefined4 *)(iVar6 + 0x10 + (int)puVar4);
    *puVar5 = systemInfoBlob2[0];
    puVar5[1] = systemInfoBlob2[1];
    puVar5[2] = systemInfoBlob2[2];
    puVar5[3] = systemInfoBlob2[3];
    puVar5[4] = systemInfoBlob2[4];
    iVar6 = *(int *)(puVar4 + 0x1000) + 0x14;
    *(int *)(puVar4 + 0x1000) = iVar6;
    *puVar4 = (short)iVar6;
    SendSocketData((char *)puVar4,*(undefined4 *)((char *)puVar4 + 0x2004),iVar6);
  }
  return;
}

