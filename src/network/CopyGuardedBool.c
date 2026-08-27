/* CopyGuardedBool - 0x00406530 in the original binary.
 *
 * Copies one obfuscated bool from the srcCell guard triple into the dstCell
 * guard triple, re-scrambling it on the way, and returns dstCell.  If the
 * source's checksum byte does not match it raises g_valueGuardTamperFlag and
 * stores false instead.
 *
 * RENAMED 2026-08-27 (was RescrambleGuardedBool).  The old name asserted an
 * in-place re-scramble of a single cell; the function takes TWO cells and
 * moves a value between them.  What settles it is the call sites, which the
 * ports had all left argless:
 *
 *   - SavePlayerStateSnapshot copies +0xbfbe -> +0xc92c, +0xbfc1 -> +0xc92f,
 *     ... +0x8bb7 -> +0xc941 (eight cells, one object).
 *     RestorePlayerStateSnapshot copies the SAME EIGHT PAIRS the other way.
 *     A rescramble-in-place has no direction to reverse.
 *   - FUN_004207c0 and ChangePlayerMobile use the same offset with two
 *     different object bases (`lea eax,[src+N]` / `lea ecx,[dst+N]`), and in
 *     both the very next statement is an already-recovered Peek(src+M) /
 *     Encode(dst+M) pair on those same two bases -- so the direction is
 *     corroborated by call sites that were fixed independently, in an
 *     earlier sweep, for a different callee.
 *
 * REGISTERS RECOVERED 2026-08-27.  Both cells were dropped: `mov edi,eax` at
 * 0x406539 takes the SOURCE and `mov esi,ecx` at 0x40653b takes the
 * DESTINATION, and `mov eax,esi` at 0x406596 returns the destination.  The
 * port had `undefined4 param_1` (ECX) returned untouched and a bare
 * `byte *in_EAX`, so every one of the 62 call sites read and wrote through
 * uninitialised memory.
 *
 * The re-encode's cell was dropped too.  0x4064a0 EncodeGuardedBool takes
 * its cell in ESI, not EAX -- `mov byte ptr [esi],al` at 0x4064b5 is its
 * first store and ESI is never written in its body -- and ESI here is the
 * destination.  The port passed GB_GUARD_UNRECOVERED, i.e. the value was
 * decoded and then thrown into the scratch cell; the copy never happened.
 *
 * dstCell arrives in ECX and srcCell in EAX.  MSVC __fastcall puts the
 * second parameter in EDX rather than EAX, which is the usual trailing-
 * register idiom in this tree: the C semantics are what matter, not
 * reproducing the original's register allocation.
 */
#include "ghidra_types.h"


byte * __fastcall CopyGuardedBool(byte *dstCell,byte *srcCell)

{
  char cVar1;
  
  EnterCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  if ((byte)((*srcCell + srcCell[1]) - 0x34) == srcCell[2]) {
    cVar1 = '\x01' - ((srcCell[1] >> (*srcCell & 7) & 1) != 1);
  }
  else {
    g_valueGuardTamperFlag = 1;
    LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
    cVar1 = '\0';
  }
  EncodeGuardedBool(cVar1,dstCell);
  LeaveCriticalSection((LPCRITICAL_SECTION)&g_valueGuardLock);
  return dstCell;
}
