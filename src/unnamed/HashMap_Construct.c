/* HashMap_Construct - 0x004fe420 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * ARGUMENTS RE-SLOTTED.  Ghidra typed this __thiscall, so param_1 is the ECX
 * slot and param_2..param_4 are the three stack arguments.  The port had been
 * passing its three constants as param_1..param_3, i.e. one slot too early,
 * with ECX left unsupplied -- and an earlier pass here APPENDED the recovered
 * EAX, which put it in param_4 rather than in the trailing register
 * parameter.  Appending is only correct when the call site already fills every
 * preceding slot; against a short call it is not an approximation, it is a
 * confidently wrong value where a missing one used to be.
 *
 * All nine call sites agree, so nothing had to be paired:
 *   push 0x40100000 / 0x3e800000 / 0x3f400000   -> param_2..param_4
 *   mov ecx, 0xa                                -> param_1
 *   mov eax, 0x11                               -> regEax
 *
 * ESI is a second dropped register here and remains open; unlike the rest it
 * is genuinely per-site (nine distinct values across nine sites), so it needs
 * a witness rather than this treatment.
 *
 * DROPPED REGISTER RECOVERED (2026-08-27): unaff_ESI is the real `this`.  It
 * is never written in the callee, it is the base of every field store, and
 * `mov eax,esi` returns it -- while the ECX value Ghidra called param_1 is
 * just another field, stored at +0x24.  The object is 0x30 bytes.
 *
 * Every site is a construction of a sub-object at a fixed offset of the
 * caller's own: param_1 + 0x6ff, param_1 + 0x6aa41c, param_1 + 0x6b0,
 * unaff_EDI + 0xa4, regEdi + 0x20 -- and the two static-initialiser thunks
 * reach it through FUN_0040d180 with two globals whose real extent had to be
 * restored first (see that file and globals_sized.c).
 *
 * ATL7's CAtlMap constructor, out of VC7.1's atlcoll.h, with
 * SetOptimalLoad and UpdateRehashThresholds inlined into it.  All nine
 * call sites pass that header's own default arguments, so each is a
 * plain default construction:
 *
 * CAtlMap( UINT nBins = 17, float fOptimalLoad = 0.75f,
 * float fLoThreshold = 0.25f, float fHiThreshold = 2.25f,
 * UINT nBlockSize = 10 )
 *
 * The port's argument order is neither the declaration order nor the
 * push order, so the mapping is worth spelling out:
 *
 * param_1 = nBlockSize   = 0xa          (ECX)
 * param_2 = fOptimalLoad = 0x3f400000   (0.75f, [esp+4] at entry)
 * param_3 = fLoThreshold = 0x3e800000   (0.25f)
 * param_4 = fHiThreshold = 0x40100000   (2.25f)
 * regEax  = nBins        = 0x11         (EAX)
 * regEsi  = this                        (ESI)
 *
 * The binary pushes the floats right to left, so 0x40100000 goes first
 * and 0x3f400000 last, and `ret 0xc` pops them.  `mov eax,esi` at
 * 0x4fe47b returns `this`, but no call site reads it -- FUN_0040d180
 * keeps its own copy (`mov esi,eax` before the call, `mov eax,esi`
 * after) -- so the void prototype here is not a dropped return.
 *
 * The 0x30 bytes are CAtlMap's twelve members, in declaration order:
 *
 * +0x00 m_ppBins = NULL       +0x18 m_nHiRehashThreshold
 * +0x04 m_nElements = 0       +0x1c m_nLoRehashThreshold
 * +0x08 m_nBins               +0x20 m_nLockCount = 0
 * +0x0c m_fOptimalLoad        +0x24 m_nBlockSize
 * +0x10 m_fLoThreshold        +0x28 m_pBlocks = NULL
 * +0x14 m_fHiThreshold        +0x2c m_pFree = NULL
 *
 * The tail is UpdateRehashThresholds: m_nHiRehashThreshold =
 * UINT(m_fHiThreshold*m_nBins) = 38 (0x4fe45e-0x4fe46d),
 * m_nLoRehashThreshold = UINT(m_fLoThreshold*m_nBins) = 4
 * (0x4fe469-0x4fe475), then the low one zeroed for being under 17
 * (0x4fe478-0x4fe47f).  Its int-to-float half is hoisted to the top of
 * the function: `test eax,eax` (0x4fe427), `fild [esp+8]` (0x4fe43b)
 * and `fadd [0x557fac]` (0x4fe458, 4294967296.0f) are the unsigned
 * fixup for m_nBins being UINT.  The 17 in `cmp eax,0x11` is
 * atlcoll.h's own literal, not the nBins that happens to equal it --
 * HashMap_InitHashTable (0x500c00) carries the same clamp against a
 * runtime bucket count.  The two FloatToInt64() calls below are the
 * _ftol calls at 0x4fe464 and 0x4fe470; their FPU operands are
 * invisible to Ghidra, so both products are missing from the port.
 *
 * ATL's CAtlMap and not MFC's CMap, and the binary settles it:
 * FUN_00500e30 is CAtlMap::PickSize -- it divides by m_fOptimalLoad at
 * [ecx+0xc] and scans the table at 0x557850, which is atlcoll.h's
 * s_anPrimes verbatim (17, 23, 29, 37, 41, 53, 67, 83, 103, 131, 163,
 * 211, 257, 331, 409, 521, 647, 821, ... 13316089, then the UINT_MAX
 * sentinel at 0x557940 that `cmp ecx,-1` at 0x500e73 tests).  MFC's
 * CMap has neither load factors nor a prime table.  Note that
 * HashMap_InitHashTable's own header still says "MFC's
 * CMap::InitHashTable"; that attribution is wrong for the same reason
 * -- it is CAtlMap::InitHashTable over this very object, rewriting
 * +0x08/+0x18/+0x1c with the identical under-17 clamp.
 *
 * The other named members read the same offsets: StringMap_Find_1c
 * divides the key hash by [map+8], and the RemoveAll bodies
 * FUN_00404b90 / StringMap_RemoveAll_CString (FUN_00415560 when
 * AtlArray_RemoveAll_450's header was written) / FUN_00415600 walk
 * m_ppBins over m_nBins, bracket
 * with m_nLockCount at +0x20, and free the plex chain from +0x28/+0x2c
 * before calling HashMap_InitHashTable(this, PickSize(0), 0).
 *
 * No stride suffix, for the reason HashMap_InitHashTable has none: the
 * body never touches K or V, so every instantiation is byte-identical
 * and the linker folded them onto this one address.  It builds at least
 * ten distinct maps -- DAT_00794e14 and DAT_00e9bea8 via the
 * static-initialiser thunks FUN_00540f00 / FUN_00540f20 and the
 * FUN_0040d180 wrapper, plus sub-objects at +0x1bfc (lea at 0x401987),
 * +0x6aa41c and +0x6aa44c (0x41696c, 0x416996), +0x1ac0 and +0x1af0
 * (0x4fd19a, 0x4fd1ca), +0x290 (0x4fdf3c), and +0x20 and +0x50 of
 * FUN_004ff1a0's object (0x4ff1b0, 0x4ff1d1).  A StringMap_ or IntMap_
 * prefix would claim one of those owns it.  Every adjacent pair is
 * exactly 0x30 apart, and InitCommP2PNotifyWindow's next field write
 * after its map is edi+0x2c0 -- the object size again, from outside.
 *
 * ARGUMENTS RE-SLOTTED and ESI RECOVERED (2026-08-27, carried over from
 * the pre-naming header): Ghidra typed this __thiscall, so param_1 is
 * the ECX slot.  The port had been passing the three float constants
 * one slot too early with ECX unsupplied, and an earlier pass appended
 * the recovered EAX into param_4 rather than into the trailing register
 * parameter.  unaff_ESI is the real `this` -- never written in the
 * callee and the base of every field store -- while the ECX value
 * Ghidra called param_1 is just m_nBlockSize at +0x24.
 */
#include "ghidra_types.h"


void __thiscall
HashMap_Construct(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 regEax,undefined4 *regEsi)

{
  undefined4 uVar1;
  uint uVar2;
  undefined4 *unaff_ESI = regEsi;
  
  unaff_ESI[9] = param_1;
  unaff_ESI[3] = param_2;
  *unaff_ESI = 0;
  unaff_ESI[1] = 0;
  unaff_ESI[2] = regEax;
  unaff_ESI[8] = 0;
  unaff_ESI[10] = 0;
  unaff_ESI[0xb] = 0;
  unaff_ESI[4] = param_3;
  unaff_ESI[5] = param_4;
  uVar1 = FloatToInt64();
  unaff_ESI[6] = uVar1;
  uVar2 = FloatToInt64();
  unaff_ESI[7] = uVar2;
  if (uVar2 < 0x11) {
    unaff_ESI[7] = 0;
  }
  return;
}

