/* EncodeOutgoingPacketField - 0x0040a380 in the original binary.
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


/* `self` is the object pointer Ghidra dropped as `unaff_EDI`: the original
 * passes `this` in EDI (a custom register convention, callee cleans the one
 * stack arg via `ret 4` at 0x40a43a). Recovered from the real binary - every
 * caller is `mov edi,<obj>; call 0x40a380`. Made an explicit leading parameter
 * so callers can pass it; other (not-yet-swept) 1-arg call sites still compile
 * against the K&R decl in functions.h and simply don't run pre-logo. */
void EncodeOutgoingPacketField(void *self, uint param_1)

{
  uint uVar1;
  uint uVar2;
  undefined4 *puVar3;
  int iVar4;
  uint *puVar5;
  int unaff_EDI = (int)self;
  undefined1 local_8 [8];
  
  uVar2 = param_1;
  uVar1 = *(uint *)(unaff_EDI + 0x14);
  if (uVar1 != 0) {
    FUN_0040a240();
    param_1 = uVar1;
    FUN_0040b540(local_8);
  }
  if (DAT_00793778 == 0) {
    iVar4 = 0;
  }
  else {
    iVar4 = *(int *)(*DAT_00793774 + 0xc);
    FUN_0040b600(&DAT_00793770,&param_1,*DAT_00793774);
  }
  *(int *)(unaff_EDI + 0x14) = iVar4;
  if (iVar4 != 0) {
    param_1 = iVar4;
    /* FUN_0040b8c0 is void-returning (see its own definition) - this
     * call site's return-value use is a Ghidra per-call-site
     * decompilation inconsistency, same class as entry/WinMain.c's
     * FUN_004058c0 fix. puVar3 is left uninitialized here as a
     * result. */
    FUN_0040b8c0();
    if ((int *)*puVar3 != DAT_00793774) {
      g_valueGuardTamperFlag = 1;
    }
  }
  puVar5 = (uint *)(iVar4 * 0x10 + DAT_0079376c);
  *(uint *)(unaff_EDI + 4) = *puVar5 ^ uVar2;
  *(uint *)(unaff_EDI + 8) = puVar5[1] ^ uVar2;
  *(uint *)(unaff_EDI + 0xc) = puVar5[2] ^ uVar2;
  *(uint *)(unaff_EDI + 0x10) = puVar5[3] ^ uVar2;
  return;
}

