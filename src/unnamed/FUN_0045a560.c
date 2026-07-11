/* FUN_0045a560 - 0x0045a560 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "ghidra_types.h"


void FUN_0045a560(undefined4 *param_1)

{
  undefined4 *unaff_FS_OFFSET;
  undefined1 local_14 [8];
  undefined4 local_c;
  undefined1 *puStack_8;
  int local_4;
  
  puStack_8 = &LAB_0053a990;
  local_c = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_c;
  *param_1 = &PTR_FUN_00555c68;
  local_4 = 0x5a;
  if (param_1[0x33f1] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0x59;
  if (param_1[0x3368] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0x58;
  if (param_1[0x32df] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0x57;
  if (param_1[0x3256] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0x56;
  if (param_1[0x31c3] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0x55;
  if (param_1[0x313a] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0x54;
  if (param_1[0x30b1] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0x53;
  if (param_1[0x3025] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0x52;
  _eh_vector_destructor_iterator_(param_1 + 0x2dca,0x224,4,ScrubChecksumGuard);
  SUBFIELD(local_4,0,undefined1) = 0x51;
  if (param_1[0x2d46] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0x50;
  if (param_1[0x2cbd] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0x4f;
  if (param_1[0x2c34] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0x4e;
  if (param_1[0x2ba0] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0x4d;
  if (param_1[0x2b00] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0x4c;
  if (param_1[0x2a77] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0x4b;
  if (param_1[0x29ee] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0x4a;
  if (param_1[0x2965] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0x49;
  if (param_1[0x28dc] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0x48;
  if (param_1[0x2853] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0x47;
  if (param_1[0x27ca] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0x46;
  if (param_1[0x2741] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0x45;
  if (param_1[0x26b5] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0x44;
  if (param_1[0x262c] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0x43;
  if (param_1[0x25a3] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0x42;
  if (param_1[0x251a] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0x41;
  if (param_1[0x2491] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0x40;
  if (param_1[0x2408] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0x3f;
  if (param_1[0x237f] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0x3e;
  if (param_1[0x22f6] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0x3d;
  if (param_1[0x2266] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0x3c;
  if (param_1[0x21dd] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0x3b;
  if (param_1[0x2154] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0x3a;
  if (param_1[0x20cb] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0x39;
  if (param_1[0x2042] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0x38;
  if (param_1[0x1fb9] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0x37;
  if (param_1[0x1f30] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0x36;
  if (param_1[0x1ea7] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0x35;
  if (param_1[0x1e1e] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0x34;
  if (param_1[0x1d95] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0x33;
  if (param_1[0x1d0c] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0x32;
  if (param_1[0x1c83] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0x31;
  if (param_1[0x1bfa] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0x30;
  if (param_1[0x1b71] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0x2f;
  if (param_1[0x1ae8] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0x2e;
  if (param_1[0x1a5f] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0x2d;
  if (param_1[0x19d6] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0x2c;
  if (param_1[0x194d] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0x2b;
  if (param_1[0x18c3] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0x2a;
  if (param_1[0x183a] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0x29;
  if (param_1[0x17b1] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0x28;
  if (param_1[0x1728] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0x27;
  if (param_1[0x169f] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0x26;
  if (param_1[0x1616] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0x25;
  if (param_1[0x158d] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0x24;
  if (param_1[0x1504] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0x23;
  if (param_1[0x147b] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0x22;
  if (param_1[0x13f2] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0x21;
  if (param_1[0x1369] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0x20;
  if (param_1[0x12e0] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0x1f;
  if (param_1[0x1257] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0x1e;
  if (param_1[0x11ce] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0x1d;
  if (param_1[0x1145] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0x1c;
  if (param_1[0x10bc] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0x1b;
  if (param_1[0x1033] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0x1a;
  if (param_1[0xfaa] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0x19;
  if (param_1[0xf21] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0x18;
  if (param_1[0xe98] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0x17;
  if (param_1[0xe0f] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0x16;
  if (param_1[0xd86] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0x15;
  if (param_1[0xcfd] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0x14;
  if (param_1[0xc74] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0x13;
  if (param_1[0xbeb] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0x12;
  if (param_1[0xb62] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0x11;
  if (param_1[0xad9] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0x10;
  if (param_1[0xa50] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0xf;
  if (param_1[0x9c7] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0xe;
  if (param_1[0x93e] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0xd;
  if (param_1[0x8b5] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0xc;
  if (param_1[0x82c] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 0xb;
  if (param_1[0x7a3] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 10;
  if (param_1[0x71a] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 9;
  if (param_1[0x690] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 8;
  if (param_1[0x607] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 7;
  if (param_1[0x57e] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 6;
  if (param_1[0x4f5] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 5;
  if (param_1[0x46c] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 4;
  if (param_1[0x3e3] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 3;
  if (param_1[0x35a] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 2;
  if (param_1[0x2d1] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  SUBFIELD(local_4,0,undefined1) = 1;
  if (param_1[0x248] != 0) {
    ScrambleChecksumGuardBytes();
    FUN_0040b540(local_14);
  }
  local_4 = (uint)SUBFIELD(local_4,1,undefined3) << 8;
  FUN_00443dc0(param_1 + 0xe);
  *param_1 = &PTR_LAB_0055752c;
  *unaff_FS_OFFSET = local_c;
  return;
}

