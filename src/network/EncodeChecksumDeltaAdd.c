/* EncodeChecksumDeltaAdd - 0x0040a5f0 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * FIXED (2026-07-15): all 3 EncodeOutgoingPacketField calls dropped
 * `self`. Confirmed via angr backward-taint (tools/
 * encodeoutgoingpacketfield_sites.json, func_addr 0x40a5f0) and orig
 * disassembly at 0x40a5f0-0x40a686: the first two calls (0x40a636/
 * 0x40a65c) both pass `lea edi,[esp+0x20]` - the same stack cell Ghidra
 * names `local_21c` here (EncodeOutgoingPacketField reads/writes
 * self+0x14, so self is local_21c's address minus 0x14, same idiom as
 * src/unnamed/FUN_00415d40.c's global-relative sites). The third call
 * (0x40a681) passes `mov edi,esi` where esi==param_2 - confirmed by the
 * immediately preceding `mov [esi+0x220],bl` / `mov [esi+0x14],ebx`
 * matching this file's own `param_2+0x220`/`param_2+0x14` writes just
 * above it. */
#include "ghidra_types.h"


int EncodeChecksumDeltaAdd(undefined4 param_1,int param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 local_238 [28];
  int local_21c;
  undefined1 local_10;
  undefined4 local_c;
  undefined1 *puStack_8;
  uint local_4;

  local_4 = 0xffffffff;
  /* Windows SEH __try/__except frame setup stripped - handler body
   * (LAB_00538e6a) wasn't included in this function's own decompile.
   * Same rationale as entry/InitGame.c - see src/README.md. */
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  local_10 = 0;
  local_21c = 0;
  EncodeOutgoingPacketField((char *)&local_21c - 0x14, 0);
  local_4 = 1;
  iVar1 = PeekPacketChecksumState();
  EncodeOutgoingPacketField((char *)&local_21c - 0x14, iVar1 + param_3);
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  *(undefined1 *)(param_2 + 0x220) = 0;
  *(undefined4 *)(param_2 + 0x14) = 0;
  uVar2 = PeekPacketChecksumState();
  EncodeOutgoingPacketField((void *)param_2, uVar2);
  local_4 = local_4 & 0xffffff00;
  if (local_21c != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_238);
  }
  return param_2;
}

