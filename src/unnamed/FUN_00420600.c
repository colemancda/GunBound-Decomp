/* FUN_00420600 - 0x00420600 in the original binary.
 *
 * No confirmed real name/purpose. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 *
 * NOT FIXED (2026-08-13, CValueGuard sweep - deliberately left argless):
 * the cell is `ctx + 0x39d0c + slot*0x224` (`imul eax,esi,0x224 / lea
 * [eax+ecx+0x39d0c]` at 0x42061b, esi = the live-in slot the C models
 * as unaff_ESI) - but ecx is `mov ecx,[esp+8]` at 0x420615, a CONTEXT
 * ARGUMENT this decompile dropped entirely: the function is really
 * (ctx) with the slot in ESI, and the C signature is `(void)`.  Naming
 * the cell means promoting the prototype and fixing the caller, which
 * is the flip task's def-promotion pass, not a call-site sweep.  Its
 * twin FUN_004dc0f0 loads ctx from [0x5b3484] directly and IS fixed.
 *
 * DROPPED-CELL FIX (2026-08-16, CValueGuard flip prep): takes the client
 * context as its one stack argument ([esp+8] after one push, `ret 4`) and a
 * slot INDEX in ESI - the artifact Ghidra named unaff_ESI and returned
 * variants of.  The peek is ctx + esi * 0x224 + 0x39d0c (0x42061b-0x420621).
 * Both are real parameters now; the 5 callers pass (g_clientContext, <slot>).
 */
#include "ghidra_types.h"


int FUN_00420600(int ctx,int unaff_ESI)

{
  int iVar1;
  int iVar2;
  
  if (unaff_ESI == 0) {
    return 0;
  }
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar1 = PeekPacketChecksumState((void *)(ctx + unaff_ESI * 0x224 + 0x39d0c));
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  iVar2 = unaff_ESI + -1;
  if (iVar1 != 0xff) {
    iVar2 = unaff_ESI;
  }
  return iVar2;
}

