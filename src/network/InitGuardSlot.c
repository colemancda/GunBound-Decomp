/* InitGuardSlot - 0x0040a280 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * FIXED (2026-07-16): the EncodeOutgoingPacketField call dropped self -
 * angr-confirmed (tools/encodeoutgoingpacketfield_sites.json, func_addr
 * 0x40a280): self is ecx = this __fastcall function's own param_1,
 * matching the param_1+0x14/+0x220 zero-writes immediately above (the
 * same idiom as SendOutgoingPacket.c's already-fixed call).
 */
#include "ghidra_types.h"


int __fastcall InitGuardSlot(int param_1)

{
  *(undefined1 *)(param_1 + 0x220) = 0;
  *(undefined4 *)(param_1 + 0x14) = 0;
  EncodeOutgoingPacketField((void *)param_1, 0);
  return param_1;
}

