/* LoadSpriteSet - 0x004f1790 in the original binary.
 *
 * No confirmed real name/purpose - referenced by at least one already-
 * ported function under src/. Raw/near-verbatim port of Ghidra's
 * decompiler output, not hand-verified. See src/README.md's "Raw/
 * verbatim ports" section for status.
 */
#include "xfs.h"
#include "ghidra_types.h"


/* Promoted: `imgName` is the sprite-set name (e.g. "logomode.img")
 * that arrived in EAX. The read cursor is a 0x1024-byte scratch buffer
 * (operator_new); the archive's file handle and LZHUF state live inside
 * g_graphicsArchive at +0x1040 / +0x1048. */

/* On error the per-entry sprite object's slot-0 vtable pointer
 * (PTR_FUN_00557524 -> FUN_004f14c0, see globals.c) is a scalar
 * deleting destructor declared `void * __thiscall(void *this,int)`
 * (this in ECX, the free-flag on the stack, callee-cleaned - see
 * FUN_004f14c0.c and the same-shaped CGameState_ScalarDeletingDestructor).
 * The call below used to go through the generic cdecl `code()` cast,
 * which drops `puVar3` (this) entirely and mis-cleans the stack. */
typedef void *(__thiscall *ScalarDeletingDtorFn)(void *thisPtr,int freeFlag);

/* RegisterActiveObject was called argless (`RegisterActiveObject();`)
 * despite the callee reading unaff_EDI/param_2 as real arguments (see
 * RegisterActiveObject.c's header). Confirmed via
 *   objdump -d -Mintel --start-address=0x4f1790 --stop-address=0x4f1880 \
 *     orig/GunBound.gme
 * at the call site (0x4f1872-0x4f1878): `mov edx,[esp+0x20]` and
 * `mov edi,esi` (`puVar3`, the sprite object just built this iteration).
 *
 * CORRECTED (2026-07-14): [esp+0x20] is this function's own `param_1`
 * (the registry container, e.g. &DAT_00ea0e18), NOT param_2 (the
 * sprite-set key) - this file previously passed param_2, matching
 * RegisterActiveObject's real body (`*(int*)(param_2+4)`, a registry
 * `+4` head-pointer dereference identical to the widget registries'
 * own idiom) against an INTEGER key instead of a pointer. Confirmed via
 * the crash it caused: with key=10000=0x2710, RegisterActiveObject
 * faulted reading *(int*)(0x2710+4) = *(int*)0x2714 - an exact match
 * to the observed fault address. Stack-offset arithmetic independently
 * confirms it: this function's prologue (`sub esp,0xc; push ebx,esi,
 * edi,eax`) consumes 0x1c bytes before the body runs, shifting the
 * caller-pushed param_1 (originally at [esp_entry+4]) to [esp+0x20]
 * with no net ESP change from the intervening (self-cleaning) calls. */

int LoadSpriteSet(undefined4 param_1,undefined4 param_2,char *imgName)

{
  void *readState;
  int iVar1;
  int iVar4;
  undefined4 *puVar3;
  int local_c;
  int local_8;
  int local_4;
  HANDLE gh = *(HANDLE *)(g_graphicsArchive.bytes + 0x1040);
  void  *lz = g_graphicsArchive.bytes + 0x1048;

  iVar1 = FindXFSEntry(&g_graphicsArchive,imgName);   /* entry record */
  if (iVar1 == 0) {
    return 0;
  }
  readState = operator_new(0x1024);
  if (readState == (void *)0x0) {
    return 0;
  }
  readState = (void *)ReadXFSEntry(readState,gh,1,iVar1,lz);
  if (readState == (void *)0x0) {
    return 0;
  }
  local_8 = iVar1;
  ReadXFSEntryByte(readState,(undefined4 *)&local_4,4);
  if (local_4 != 0) {
    return 0;
  }
  ReadXFSEntryByte(readState,(undefined4 *)&local_c,4);
  iVar1 = 0;
  if (0 < local_c) {
    do {
      puVar3 = operator_new(0x50);
      if (puVar3 == (undefined4 *)0x0) {
        puVar3 = (undefined4 *)0x0;
      }
      else {
        puVar3[1] = param_2;
        puVar3[2] = iVar1;
        puVar3[3] = 0;
        puVar3[4] = 0;
        *(undefined1 *)(puVar3 + 5) = 0;
        *(undefined1 *)((int)puVar3 + 0x15) = 0;
        *puVar3 = &PTR_FUN_00557524;
        *(undefined1 *)((int)puVar3 + 0x1b) = 0xff;
        *(undefined1 *)((int)puVar3 + 0x1a) = 0;
        *(undefined1 *)((int)puVar3 + 0x19) = 0xff;
        puVar3[8] = 0;
        puVar3[9] = 0;
        puVar3[0xb] = 0;
        puVar3[10] = 0;
        *(undefined1 *)(puVar3 + 0xc) = 0;
        puVar3[0xd] = 0;
        puVar3[0xe] = 0;
      }
      iVar4 = ReadSpriteFrameRecord(readState,(int)puVar3);
      if (iVar4 == -1) {
        if (puVar3 != (undefined4 *)0x0) {
          (*(ScalarDeletingDtorFn *)*puVar3)(puVar3,1);
        }
        return -1;
      }
      RegisterActiveObject(0, param_1, puVar3);
      iVar1 = iVar1 + 1;
    } while (iVar1 < local_c);
  }
  FUN_004f1460();
  return local_c;
}

