/* ExplodeSuperShot_Bullet11 - 0x004759b0 in the original binary.
 *
 * RENAMED (2026-08-16, from FUN_004759b0): CProjectile virtual slot 8 -
 * the post-detonation effect that the slot-6 Detonate override dispatches
 * right after marking the projectile dead (`param_1[5] = 1; (**(code
 * **)(*param_1 + 0x20))()`), only super-shot classes have it. "Explode" is
 * a descriptive label for that role, not a recovered name for mobile type
 * 10's super shot (texture bullet11p; vtable 0x555f58, ctor FUN_00475990
 * reached only through SpawnSuperShot's case 10). Type/role CONFIRMED via
 * vtable geometry (tools/projectile_class_map.py); the mobile NAME is not
 * confirmable (no mobile-type->name map in the repo).
 *
 * Body is a raw/near-verbatim Ghidra port, not hand-verified. See
 * src/README.md's "Raw/verbatim ports" section for status.
 *
 * DROPPED-CELL FIX (2026-08-12, CValueGuard sweep): recovered the guard
 * cell at all 23 argless PeekPacketChecksumState() calls (peek status
 * "clean", 23 C : 23 orig).  Cells from tools/guard_cell_resolve.py over
 * 0x4759b0-0x475ded.  No gotos; the body is one do-while, so each C site
 * is a single static call address and the sites order-zip.
 *
 * Two bases.  The five sites before the loop body's object lookup use
 * EDI = param_1 (`mov edi,ecx` at 0x4759b7, and the intervening
 * FUN_0048de60 call preserves EDI).  Everything after uses EBP, the
 * HitTestLocalMobile return at 0x475a9d - i.e. the C's own piVar5, which is
 * exactly what the 2026-07-15 Encode sweep independently concluded for
 * the four already-fixed Encode sites here.  NOTE EDI is retargeted by
 * `lea edi,[ebp+0xb728]` at 0x475af0 and again for each later round, so
 * a bare EDI after that point is a piVar5 cell, not param_1.
 *
 * The four clamp blocks are the one place order alone would not settle
 * it: `if (iVar6 + 5 < iVar7) local_10 = Peek() + 5; else local_10 =
 * Peek();` reads the SAME two cells as iVar6/iVar7 (a min()).  The
 * branch layout was checked rather than assumed - 0x475b36 `jge` sends
 * the >= case to the second block, so the C then-branch (the +5 one) is
 * the FALL-THROUGH at 0x475b38 and takes the piVar5 cell, while the else
 * takes &DAT_00e55ab8.  Same shape at the other three rounds.
 *
 * Out of scope, flagged: the `FUN_0048de60()` call at line ~23 is
 * 0x4759bd, reached with ECX still holding param_1 - a dropped
 * __thiscall `this`, for a different sweep.
 */
#include "ghidra_types.h"


void __fastcall ExplodeSuperShot_Bullet11(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int *piVar5;
  int iVar6;
  int iVar7;
  int local_14;
  int local_10;
  int local_c;
  
  FUN_0048de60();
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar2 = PeekPacketChecksumState((void *)(param_1 + 0x1178));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  uVar3 = PeekPacketChecksumState((void *)(param_1 + 0xf54));
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
  /* RECOVERED (2026-08-19): the two dropped __fastcall register
   * arguments (orig 0x475a20 mov cl,1 / 0x475a22 xor edx,edx).  param_1 is the randomise flag,
   * param_2 the sub-effect index (the callee caps it at < 4).  The third
   * register argument, EAX, needs nothing here: the 2026-08-17 audit proved
   * every site passes ctx+0x6a7f70 and the callee already inlines the
   * resulting +0x6a7f74 gate peek. */
  SpawnSuperFlameEffect(1,0,uVar3,uVar2,0x2076,s_ssflame11_00554ae4);
  local_c = 0;
  local_14 = 0;
  do {
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar2 = PeekPacketChecksumState((void *)(param_1 + 0x33c8));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar3 = PeekPacketChecksumState((void *)(param_1 + 0x1178));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    uVar4 = PeekPacketChecksumState((void *)(param_1 + 0xf54));
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
    piVar5 = (int *)HitTestLocalMobile(g_clientContext,uVar4,uVar3,uVar2);
    if (piVar5 != (int *)0x0) {
      cVar1 = PeekPacketChecksumBool();
      if (cVar1 != '\0') {
        cVar1 = PeekPacketChecksumBool();
        if ((cVar1 != '\x01') && (piVar5[9] != 0xe)) {
          (**(code **)(*piVar5 + 4))(&PTR_DAT_00555cc8);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar6 = PeekPacketChecksumState((void *)((int)piVar5 + 0xb728));
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar7 = PeekPacketChecksumState((void *)&DAT_00e55ab8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          if (iVar6 + 5 < iVar7) {
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            local_10 = PeekPacketChecksumState((void *)((int)piVar5 + 0xb728));
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            local_10 = local_10 + 5;
          }
          else {
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            local_10 = PeekPacketChecksumState((void *)&DAT_00e55ab8);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          }
          /* FIXED (2026-07-15): dropped `self` arg - angr-confirmed at
           * 0x475c2b (`lea edi,[ebp+0xb94c]`, ebp = this file's own
           * piVar5, per `mov ebp,eax` right after the HitTestLocalMobile call
           * above) a CValueGuard cell at piVar5+0xb94c; +0x224 past the
           * cell used at the previous call (0xb728), matching
           * sizeof(CValueGuard)=0x224 - these 4 calls step through a
           * 4-element guard-cell array. `piVar5` is `int *` (scales by
           * 4), so the byte offset is taken via `(int)piVar5 + N`. See
           * tools/encodeoutgoingpacketfield_sites.json. */
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField((int)piVar5 + 0xb728, local_10);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar6 = PeekPacketChecksumState((void *)((int)piVar5 + 0xb94c));
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar7 = PeekPacketChecksumState((void *)&DAT_00e55ab8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          if (iVar6 + 5 < iVar7) {
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            local_10 = PeekPacketChecksumState((void *)((int)piVar5 + 0xb94c));
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            local_10 = local_10 + 5;
          }
          else {
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            local_10 = PeekPacketChecksumState((void *)&DAT_00e55ab8);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          }
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField((int)piVar5 + 0xb94c, local_10);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar6 = PeekPacketChecksumState((void *)((int)piVar5 + 0xbb70));
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar7 = PeekPacketChecksumState((void *)&DAT_00e55ab8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          if (iVar6 + 5 < iVar7) {
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            local_10 = PeekPacketChecksumState((void *)((int)piVar5 + 0xbb70));
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            local_10 = local_10 + 5;
          }
          else {
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            local_10 = PeekPacketChecksumState((void *)&DAT_00e55ab8);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          }
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField((int)piVar5 + 0xbb70, local_10);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar6 = PeekPacketChecksumState((void *)((int)piVar5 + 0xbd94));
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          iVar7 = PeekPacketChecksumState((void *)&DAT_00e55ab8);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          if (iVar6 + 5 < iVar7) {
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            local_10 = PeekPacketChecksumState((void *)((int)piVar5 + 0xbd94));
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            local_10 = local_10 + 5;
          }
          else {
            EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
            local_10 = PeekPacketChecksumState((void *)&DAT_00e55ab8);
            LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          }
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EncodeOutgoingPacketField((int)piVar5 + 0xbd94, local_10);
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          uVar2 = PeekPacketChecksumState((void *)((int)piVar5 + 0xb30));
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          EnterCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          uVar3 = PeekPacketChecksumState((void *)((int)piVar5 + 0x90c));
          LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_005a9068);
          SpawnFlameEffect(local_c,uVar3,uVar2,*(undefined4 *)(param_1 + 0x3894),param_1 + 0x3898);
          local_c = local_c + 1;
        }
      }
    }
    local_14 = local_14 + 1;
  } while (local_14 < 8);
  return;
}

