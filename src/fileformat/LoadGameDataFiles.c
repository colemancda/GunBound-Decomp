/* LoadGameDataFiles - 0x00419d90 in the original binary.
 *
 * Raw/near-verbatim port of Ghidra's decompiler output - not hand-
 * verified against documented behavior beyond what's already in
 * ARCHITECTURE.md/PROTOCOL.md/FILEFORMATS.md. Calls to unnamed
 * FUN_<address> helpers and DAT_<address>/_DAT_<address> globals are
 * left as-is (undeclared) - this file won't link standalone yet. See
 * src/README.md's "Raw/verbatim ports" section for status and how
 * these get promoted to verified.
 *
 * DROPPED-CELL FIX (2026-08-11): all 3 PeekPacketChecksumState and all 103
 * EncodeOutgoingPacketField calls had lost their guard-cell pointer arg
 * (EAX resp. EDI in the original; both callees are still bring-up stubs,
 * so this is behavior-neutral until the guard system is flipped live).
 * Recovered per tools/guard_worklist.json + disasm of 0x419e60-0x41b3d9;
 * spot-verified at 0x419ee4-0x419f65, 0x41a4be-0x41a4d6, 0x41ab5b-0x41ab66,
 * 0x41ad53-0x41ae06, 0x41af00-0x41afce, 0x41b15a-0x41b34e. Cells:
 *  - Peek: &DAT_00e525e8 (mov eax,0xe525e8 at 0x419e87/0x41ac97/0x41b3ac).
 *  - characterdata loop: [esp+0xc] = param_1+0xf05a8 (0x419ec1-0x419ed8),
 *    += 0xb1ac per iteration (0x41ab84); cell = that base + 0x224*i for
 *    dword index i in -1..0x51. [esp+0xc] is the same physical slot Ghidra
 *    named iStack_181dc in the stage loop, so it is reused here - its
 *    dropped init/increment are the two added iStack_181dc statements.
 *  - stage.dat outer: iStack_181dc(+0x80) + 0x224*i for the 10 fields;
 *    inner: [esp+0x1c] = iStack_181dc+0x2708 (0x41aee8), += 0x224 per
 *    inner iteration (0x41afe9), + 0x1120*j for j in -1..4. [esp+0x1c] is
 *    pcStack_181cc's slot (unused by this loop in the decompile), so it
 *    carries the added cursor init/increment.
 *  - itemdata.dat: pcStack_181cc (= param_1+0x58b8d6, already in the
 *    port; edi loaded at 0x41b1ea and preserved across the _rand/critical-
 *    section calls) + {-0x66e, -0x44a, -0x226, +0xa}.
 */
#include "xfs.h"
#include "ghidra_types.h"
#include <windows.h>


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */

byte LoadGameDataFiles(int param_1)

{
  byte bVar1;
  undefined2 uVar2;
  undefined4 uVar3;
  char cVar4;
  byte bVar5;
  FILE *pFVar6;
  long lVar7;
  int iVar8;
  int iVar9;
  char *pcVar10;
  size_t sVar11;
  char *pcVar12;
  int iStack_181dc;
  undefined4 *puStack_181d8;
  char cStack_181d4;
  char *pcStack_181cc;
  char cStack_181c5;
  uint uStack_181c4;
  char *pcStack_181c0;
  int iStack_181bc;
  undefined1 auStack_181b8 [1024];
  char acStack_17db8 [128];
  char acStack_17d38 [30672];
  undefined1 auStack_10568 [4];
  undefined4 auStack_10564 [40];
  int iStack_104c4;
  char local_f0a8 [61596];
  undefined4 uStack_c;
  
  uStack_c = 0x419da0;
  BuildAssetPath(auStack_181b8,&DAT_005b1ed0,s_Avatar_xfs_00553660,0);
  /* WRONG-TARGET FIX (2026-07-29): the raw port opened Avatar.xfs into the
   * shared one-shot &g_xfsScratch buffer, but objdump (0x419dc3-0x419dce)
   * shows the real target is `param_1 + 0xf6e8` - a PERSISTENT per-client
   * archive slot: `lea ecx,[esp+0x38]` (path) / `add esi,0xf6e8` (esi =
   * [ebp+8] = this function's own param_1) / `call 0x4f0a50`
   * (OpenXFSArchive). This is the same archive FUN_00423bf0.c/
   * FUN_00423e20.c/FUN_004240c0.c/FUN_004e3c50.c read from at
   * g_clientContext + 0xf6e8 (this function is called with param_1 =
   * g_clientContext, matching those callers). Using g_xfsScratch left that
   * slot permanently unopened (all-garbage), so every one of those avatar
   * asset lookups fed CompareXFSEntryName a NULL/garbage record pointer -
   * the persistent page-fault chasing this whole session, reproduced even
   * on pure idle since FindOrInsertXFSEntry's insertion-scan sees whatever
   * garbage this arena slot's "entry count" field happened to hold. */
  cVar4 = OpenXFSArchive((XFSArchive *)(param_1 + 0xf6e8),auStack_181b8,1,0);
  if (cVar4 == '\0') {
    return 7;
  }
  BuildAssetPath(auStack_181b8,&DAT_005b1ed0,s_characterdata_dat_0055364c,0);
  pFVar6 = (FILE *)FUN_00525fac(auStack_181b8,&DAT_00553648);
  if (pFVar6 == (FILE *)0x0) {
    return 2;
  }
  pcVar10 = acStack_17db8;
  for (iVar9 = 0xa60; iVar9 != 0; iVar9 = iVar9 + -1) {
    pcVar10[0] = '\0';
    pcVar10[1] = '\0';
    pcVar10[2] = '\0';
    pcVar10[3] = '\0';
    pcVar10 = pcVar10 + 4;
  }
  _fseek(pFVar6,0,2);
  lVar7 = _ftell(pFVar6);
  _fseek(pFVar6,0,0);
  _fread(acStack_17db8,1,lVar7 - 1U,pFVar6);
  DecodeLZHUFBlock(param_1,auStack_10568,acStack_17db8,lVar7 - 1U,0x14c0);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  iVar9 = PeekPacketChecksumState((void *)&DAT_00e525e8);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  if (iStack_104c4 != iVar9) {
    return 1;
  }
  _fclose(pFVar6);
  puStack_181d8 = auStack_10564;
  iStack_181dc = param_1 + 0xf05a8;
  pcStack_181cc = (char *)0x10;
  do {
    uVar3 = puStack_181d8[-1];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + -0x224),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = *puStack_181d8;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)iStack_181dc,uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[1];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0x224),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[2];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0x448),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[3];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0x66c),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[4];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0x890),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[5];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0xab4),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[6];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0xcd8),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[7];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0xefc),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[8];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0x1120),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[9];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0x1344),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[10];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0x1568),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[0xb];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0x178c),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[0xc];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0x19b0),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[0xd];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0x1bd4),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[0xe];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0x1df8),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[0xf];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0x201c),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[0x10];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0x2240),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[0x11];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0x2464),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[0x12];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0x2688),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[0x13];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0x28ac),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[0x14];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0x2ad0),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[0x15];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0x2cf4),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[0x16];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0x2f18),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[0x17];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0x313c),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[0x18];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0x3360),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[0x19];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0x3584),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[0x1a];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0x37a8),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[0x1b];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0x39cc),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[0x1c];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0x3bf0),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[0x1d];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0x3e14),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[0x1e];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0x4038),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[0x1f];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0x425c),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[0x20];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0x4480),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[0x21];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0x46a4),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[0x22];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0x48c8),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[0x23];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0x4aec),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[0x24];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0x4d10),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[0x25];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0x4f34),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[0x26];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0x5158),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[0x27];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0x537c),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[0x28];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0x55a0),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[0x29];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0x57c4),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[0x2a];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0x59e8),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[0x2b];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0x5c0c),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[0x2c];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0x5e30),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[0x2d];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0x6054),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[0x2e];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0x6278),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[0x2f];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0x649c),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[0x30];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0x66c0),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[0x31];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0x68e4),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[0x32];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0x6b08),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[0x33];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0x6d2c),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[0x34];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0x6f50),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[0x35];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0x7174),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[0x36];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0x7398),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[0x37];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0x75bc),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[0x38];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0x77e0),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[0x39];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0x7a04),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[0x3a];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0x7c28),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[0x3b];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0x7e4c),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[0x3c];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0x8070),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[0x3d];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0x8294),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[0x3e];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0x84b8),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[0x3f];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0x86dc),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[0x40];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0x8900),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[0x41];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0x8b24),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[0x42];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0x8d48),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[0x43];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0x8f6c),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[0x44];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0x9190),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[0x45];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0x93b4),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[0x46];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0x95d8),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[0x47];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0x97fc),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[0x48];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0x9a20),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[0x49];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0x9c44),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[0x4a];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0x9e68),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[0x4b];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0xa08c),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[0x4c];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0xa2b0),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[0x4d];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0xa4d4),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[0x4e];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0xa6f8),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[0x4f];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0xa91c),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[0x50];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0xab40),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = puStack_181d8[0x51];
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EncodeOutgoingPacketField((void *)(iStack_181dc + 0xad64),uVar3);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    puStack_181d8 = puStack_181d8 + 0x53;
    iStack_181dc = iStack_181dc + 0xb1ac;
    pcStack_181cc = (char *)((int)pcStack_181cc + -1);
  } while (pcStack_181cc != (char *)0x0);
  BuildAssetPath(auStack_181b8,&DAT_005b1ed0,s_stage_dat_0055363c,0);
  pFVar6 = (FILE *)FUN_00525fac(auStack_181b8,&DAT_00553648);
  if (pFVar6 != (FILE *)0x0) {
    _fseek(pFVar6,0,2);
    lVar7 = _ftell(pFVar6);
    sVar11 = lVar7 - 5;
    _fseek(pFVar6,0,0);
    _fread((void *)(param_1 + 0x1a1e44),4,1,pFVar6);
    *(uint *)(param_1 + 0x1a1e44) = (*(int *)(param_1 + 0x1a1e44) - 0x3ae53U) / 0x7c17;
    _fread(local_f0a8,sVar11,1,pFVar6);
    DecodeLZHUFBlock(param_1,acStack_17db8,local_f0a8,sVar11,0x3c80);
    cVar4 = 'M';
    iVar9 = 0;
    cStack_181d4 = 'M';
    if (0 < (int)sVar11) {
      do {
        cVar4 = cVar4 + local_f0a8[iVar9];
        iVar9 = iVar9 + 1;
        cStack_181d4 = cVar4;
      } while (iVar9 < (int)sVar11);
    }
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar9 = PeekPacketChecksumState((void *)&DAT_00e525e8);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    if ((*(int *)(param_1 + 0x1a1e44) != iVar9) ||
       (_fread(&cStack_181c5,1,1,pFVar6), cStack_181d4 != cStack_181c5)) {
      return 3;
    }
    _fclose(pFVar6);
    pcVar10 = acStack_17d38;
    iStack_181dc = param_1 + 0x1a1ec8;
    uStack_181c4 = 0x20;
    while( true ) {
      pcVar12 = pcVar10 + -0x80;
      iVar9 = iStack_181dc - (int)pcVar12;
      do {
        cVar4 = *pcVar12;
        pcVar12[iVar9 + -0x80] = cVar4;
        pcVar12 = pcVar12 + 1;
      } while (cVar4 != '\0');
      pcVar12 = pcVar10;
      do {
        cVar4 = *pcVar12;
        pcVar12[iStack_181dc - (int)pcVar10] = cVar4;
        pcVar12 = pcVar12 + 1;
      } while (cVar4 != '\0');
      uVar2 = *(undefined2 *)(pcVar10 + 0x80);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeOutgoingPacketField((void *)(iStack_181dc + 0x80),uVar2);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar2 = *(undefined2 *)(pcVar10 + 0x82);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeOutgoingPacketField((void *)(iStack_181dc + 0x2a4),uVar2);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar3 = *(undefined4 *)(pcVar10 + 0x84);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeOutgoingPacketField((void *)(iStack_181dc + 0x4c8),uVar3);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar3 = *(undefined4 *)(pcVar10 + 0x88);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeOutgoingPacketField((void *)(iStack_181dc + 0x6ec),uVar3);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar3 = *(undefined4 *)(pcVar10 + 0x8c);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeOutgoingPacketField((void *)(iStack_181dc + 0x910),uVar3);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar3 = *(undefined4 *)(pcVar10 + 0x90);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeOutgoingPacketField((void *)(iStack_181dc + 0xb34),uVar3);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar3 = *(undefined4 *)(pcVar10 + 0x94);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeOutgoingPacketField((void *)(iStack_181dc + 0xd58),uVar3);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar3 = *(undefined4 *)(pcVar10 + 0x98);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeOutgoingPacketField((void *)(iStack_181dc + 0xf7c),uVar3);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar3 = *(undefined4 *)(pcVar10 + 0x9c);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeOutgoingPacketField((void *)(iStack_181dc + 0x11a0),uVar3);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar3 = *(undefined4 *)(pcVar10 + 0xa0);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeOutgoingPacketField((void *)(iStack_181dc + 0x13c4),uVar3);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      pcStack_181c0 = pcVar10 + 0xc4;
      pcStack_181cc = (char *)(iStack_181dc + 0x2708);
      iStack_181bc = 8;
      do {
        uVar3 = *(undefined4 *)(pcStack_181c0 + -0x20);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EncodeOutgoingPacketField(pcStack_181cc + -0x1120,uVar3);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar3 = *(undefined4 *)pcStack_181c0;
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EncodeOutgoingPacketField(pcStack_181cc,uVar3);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar3 = *(undefined4 *)(pcStack_181c0 + 0x20);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EncodeOutgoingPacketField(pcStack_181cc + 0x1120,uVar3);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar3 = *(undefined4 *)(pcStack_181c0 + 0x40);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EncodeOutgoingPacketField(pcStack_181cc + 0x2240,uVar3);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar3 = *(undefined4 *)(pcStack_181c0 + 0x60);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EncodeOutgoingPacketField(pcStack_181cc + 0x3360,uVar3);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        uVar3 = *(undefined4 *)(pcStack_181c0 + 0x80);
        EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        EncodeOutgoingPacketField(pcStack_181cc + 0x4480,uVar3);
        LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
        pcStack_181c0 = pcStack_181c0 + 4;
        pcStack_181cc = pcStack_181cc + 0x224;
        iStack_181bc = iStack_181bc + -1;
      } while (iStack_181bc != 0);
      pcVar10 = pcVar10 + 0x1e4;
      iStack_181dc = iStack_181dc + 0x7d28;
      uStack_181c4 = uStack_181c4 - 1;
      if (uStack_181c4 == 0) break;
      iStack_181bc = 0;
    }
    BuildAssetPath(auStack_181b8,&DAT_005b1ed0,s_itemdata_dat_0055362c,0);
    pFVar6 = (FILE *)FUN_00525fac(auStack_181b8,&DAT_00553648);
    if (pFVar6 == (FILE *)0x0) {
      return 5;
    }
    _fseek(pFVar6,0,2);
    lVar7 = _ftell(pFVar6);
    sVar11 = lVar7 - 1;
    _fseek(pFVar6,0,0);
    _fread(local_f0a8,sVar11,1,pFVar6);
    DecodeLZHUFBlock(param_1,acStack_17db8,local_f0a8,sVar11,0x7850);
    cVar4 = 'M';
    iVar9 = 0;
    cStack_181d4 = 'M';
    if (0 < (int)sVar11) {
      do {
        cVar4 = cVar4 + local_f0a8[iVar9];
        iVar9 = iVar9 + 1;
        cStack_181d4 = cVar4;
      } while (iVar9 < (int)sVar11);
    }
    _fread(&cStack_181c5,1,1,pFVar6);
    if (cStack_181d4 != cStack_181c5) {
      return 6;
    }
    _fclose(pFVar6);
    pcVar10 = acStack_17db8;
    pcStack_181cc = &DAT_0058b8d6 + param_1;
    iStack_181bc = 100;
    do {
      pcVar12 = pcVar10;
      do {
        cVar4 = *pcVar12;
        pcVar12[(int)(pcStack_181cc + (-0x68e - (int)pcVar10))] = cVar4;
        pcVar12 = pcVar12 + 1;
      } while (cVar4 != '\0');
      uVar3 = *(undefined4 *)(pcVar10 + 0x20);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeOutgoingPacketField(pcStack_181cc + -0x66e,uVar3);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar3 = *(undefined4 *)(pcVar10 + 0x24);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeOutgoingPacketField(pcStack_181cc + -0x44a,uVar3);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uVar3 = *(undefined4 *)(pcVar10 + 0x28);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeOutgoingPacketField(pcStack_181cc + -0x226,uVar3);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      cVar4 = pcVar10[0x2c];
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar9 = _rand();
      pcStack_181cc[-2] = (char)iVar9;
      bVar1 = pcStack_181cc[-2];
      uStack_181c4 = bVar1 & 7;
      iVar9 = _rand();
      bVar5 = (byte)iVar9 & ~('\x01' << ((byte)uStack_181c4 & 0x1f)) |
              (cVar4 != '\0') << ((byte)uStack_181c4 & 0x1f);
      pcStack_181cc[-1] = bVar5;
      *pcStack_181cc = bVar5 + bVar1 + -0x34;
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      cVar4 = pcVar10[0x2d];
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar9 = _rand();
      pcStack_181cc[1] = (char)iVar9;
      bVar1 = pcStack_181cc[1];
      uStack_181c4 = bVar1 & 7;
      iVar9 = _rand();
      bVar5 = (byte)iVar9 & ~('\x01' << ((byte)uStack_181c4 & 0x1f)) |
              (cVar4 != '\0') << ((byte)uStack_181c4 & 0x1f);
      pcStack_181cc[2] = bVar5;
      pcStack_181cc[3] = bVar5 + bVar1 + -0x34;
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      cVar4 = pcVar10[0x2e];
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      iVar9 = _rand();
      pcStack_181cc[4] = (char)iVar9;
      bVar1 = pcStack_181cc[4];
      uStack_181c4 = bVar1 & 7;
      iVar9 = _rand();
      bVar5 = (byte)iVar9 & ~('\x01' << ((byte)uStack_181c4 & 0x1f)) |
              (cVar4 != '\0') << ((byte)uStack_181c4 & 0x1f);
      pcStack_181cc[5] = bVar5;
      pcStack_181cc[6] = bVar5 + bVar1 + -0x34;
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      uStack_181c4 = (uint)*(ushort *)(pcVar10 + 0x30);
      EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      EncodeOutgoingPacketField(pcStack_181cc + 0xa,uStack_181c4);
      LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
      pcVar12 = pcVar10 + 0x32;
      iVar9 = 0x22e - (int)pcVar12;
      do {
        cVar4 = *pcVar12;
        pcVar12[(int)(pcStack_181cc + iVar9)] = cVar4;
        pcVar12 = pcVar12 + 1;
      } while (cVar4 != '\0');
      pcStack_181cc = pcStack_181cc + 0x9bc;
      pcVar10 = pcVar10 + 0x134;
      iStack_181bc = iStack_181bc + -1;
    } while (iStack_181bc != 0);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar9 = PeekPacketChecksumState((void *)&DAT_00e525e8);
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    iVar8 = GetItemQuantityByIcon(param_1,99);
    return -(iVar8 != iVar9) & 6;
  }
  return 4;
}

