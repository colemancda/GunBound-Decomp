/* FUN_004174c0 - 0x004174c0 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void __fastcall FUN_004174c0(int param_1)

{
  undefined1 local_20 [12];
  int local_c;

  /* Windows SEH __try/__except frame setup stripped - handler body
   * (LAB_005389b6) wasn't included in this function's own decompile.
   * Same rationale as entry/InitGame.c - see src/README.md. local_c
   * is a real, separate local (an exception-cleanup index counted
   * down through this function's many ScrambleChecksumGuardBytes/TreeLowerBound
   * cleanup pairs), kept as-is; its `._0_1_` partial-byte writes are
   * rewritten as plain int assignments since the upper 3 bytes are
   * provably always zero at each of those points (every value written
   * is a small byte-sized constant and the one non-constant write,
   * `local_c._1_3_ << 8`, reads back only zero bytes that were never
   * set to anything else - equivalent to a plain `local_c = 0`). */
  local_c = 0x51;
  if (*(int *)(param_1 + 0xaf9c) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 0x50;
  if (*(int *)(param_1 + 0xad78) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 0x4f;
  if (*(int *)(param_1 + 0xab54) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 0x4e;
  if (*(int *)(param_1 + 0xa930) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 0x4d;
  if (*(int *)(param_1 + 0xa70c) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 0x4c;
  if (*(int *)(param_1 + 0xa4e8) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 0x4b;
  if (*(int *)(param_1 + 0xa2c4) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 0x4a;
  if (*(int *)(param_1 + 0xa0a0) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 0x49;
  if (*(int *)(param_1 + 0x9e7c) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 0x48;
  if (*(int *)(param_1 + 0x9c58) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 0x47;
  if (*(int *)(param_1 + 0x9a34) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 0x46;
  if (*(int *)(param_1 + 0x9810) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 0x45;
  if (*(int *)(param_1 + 0x95ec) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 0x44;
  if (*(int *)(param_1 + 0x93c8) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 0x43;
  if (*(int *)(param_1 + 0x91a4) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 0x42;
  if (*(int *)(param_1 + 0x8f80) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 0x41;
  if (*(int *)(param_1 + 0x8d5c) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 0x40;
  if (*(int *)(param_1 + 0x8b38) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 0x3f;
  if (*(int *)(param_1 + 0x8914) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 0x3e;
  if (*(int *)(param_1 + 0x86f0) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 0x3d;
  if (*(int *)(param_1 + 0x84cc) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 0x3c;
  if (*(int *)(param_1 + 0x82a8) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 0x3b;
  if (*(int *)(param_1 + 0x8084) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 0x3a;
  if (*(int *)(param_1 + 0x7e60) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 0x39;
  if (*(int *)(param_1 + 0x7c3c) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 0x38;
  if (*(int *)(param_1 + 0x7a18) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 0x37;
  if (*(int *)(param_1 + 0x77f4) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 0x36;
  if (*(int *)(param_1 + 0x75d0) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 0x35;
  if (*(int *)(param_1 + 0x73ac) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 0x34;
  if (*(int *)(param_1 + 0x7188) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 0x33;
  if (*(int *)(param_1 + 0x6f64) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 0x32;
  if (*(int *)(param_1 + 0x6d40) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 0x31;
  if (*(int *)(param_1 + 0x6b1c) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 0x30;
  if (*(int *)(param_1 + 0x68f8) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 0x2f;
  if (*(int *)(param_1 + 0x66d4) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 0x2e;
  if (*(int *)(param_1 + 0x64b0) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 0x2d;
  if (*(int *)(param_1 + 0x628c) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 0x2c;
  if (*(int *)(param_1 + 0x6068) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 0x2b;
  if (*(int *)(param_1 + 0x5e44) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 0x2a;
  if (*(int *)(param_1 + 0x5c20) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 0x29;
  if (*(int *)(param_1 + 0x59fc) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 0x28;
  if (*(int *)(param_1 + 0x57d8) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 0x27;
  if (*(int *)(param_1 + 0x55b4) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 0x26;
  if (*(int *)(param_1 + 0x5390) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 0x25;
  if (*(int *)(param_1 + 0x516c) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 0x24;
  if (*(int *)(param_1 + 0x4f48) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 0x23;
  if (*(int *)(param_1 + 0x4d24) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 0x22;
  if (*(int *)(param_1 + 0x4b00) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 0x21;
  if (*(int *)(param_1 + 0x48dc) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 0x20;
  if (*(int *)(param_1 + 0x46b8) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 0x1f;
  if (*(int *)(param_1 + 0x4494) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 0x1e;
  if (*(int *)(param_1 + 0x4270) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 0x1d;
  if (*(int *)(param_1 + 0x404c) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 0x1c;
  if (*(int *)(param_1 + 0x3e28) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 0x1b;
  if (*(int *)(param_1 + 0x3c04) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 0x1a;
  if (*(int *)(param_1 + 0x39e0) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 0x19;
  if (*(int *)(param_1 + 0x37bc) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 0x18;
  if (*(int *)(param_1 + 0x3598) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 0x17;
  if (*(int *)(param_1 + 0x3374) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 0x16;
  if (*(int *)(param_1 + 0x3150) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 0x15;
  if (*(int *)(param_1 + 0x2f2c) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 0x14;
  if (*(int *)(param_1 + 0x2d08) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 0x13;
  if (*(int *)(param_1 + 0x2ae4) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 0x12;
  if (*(int *)(param_1 + 0x28c0) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 0x11;
  if (*(int *)(param_1 + 0x269c) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 0x10;
  if (*(int *)(param_1 + 0x2478) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 0xf;
  if (*(int *)(param_1 + 0x2254) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 0xe;
  if (*(int *)(param_1 + 0x2030) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 0xd;
  if (*(int *)(param_1 + 0x1e0c) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 0xc;
  if (*(int *)(param_1 + 0x1be8) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 0xb;
  if (*(int *)(param_1 + 0x19c4) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 10;
  if (*(int *)(param_1 + 0x17a0) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 9;
  if (*(int *)(param_1 + 0x157c) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 8;
  if (*(int *)(param_1 + 0x1358) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 7;
  if (*(int *)(param_1 + 0x1134) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 6;
  if (*(int *)(param_1 + 0xf10) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 5;
  if (*(int *)(param_1 + 0xcec) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 4;
  if (*(int *)(param_1 + 0xac8) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 3;
  if (*(int *)(param_1 + 0x8a4) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 2;
  if (*(int *)(param_1 + 0x680) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 1;
  if (*(int *)(param_1 + 0x45c) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 0;
  if (*(int *)(param_1 + 0x238) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  local_c = 0xffffffff;
  if (*(int *)(param_1 + 0x14) != 0) {
    ScrambleChecksumGuardBytes();
    TreeLowerBound(local_20);
  }
  return;
}

