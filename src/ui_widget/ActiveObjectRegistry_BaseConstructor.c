/* ActiveObjectRegistry_BaseConstructor - 0x004f2e40 in the original binary.
 *
 * Named above, but still a raw/near-verbatim port of Ghidra's decompiler
 * output, not hand-verified. See src/README.md's "Raw/verbatim ports"
 * section for status.
 *
 * DROPPED REGISTER RECOVERED (2026-08-27): unaff_ESI is `this`.  The first
 * thing the body does is stamp a vtable through it
 * (`*unaff_ESI = &PTR_FUN_00557534;`) before allocating and initialising the
 * 0x20-byte node it hangs off, so this is a constructor and ESI is the object
 * being constructed.
 *
 * Seven call sites across seven callers, one each, so nothing needed pairing:
 *   - FUN_00405f00, FUN_0040cd40, FUN_004f1750 and FUN_004f3940 are two-line
 *     thunks (`push esi / mov esi,eax / call`) that already declare the value
 *     as regEax, so they simply forward it.
 *   - FUN_00401910 uses `mov ebp,[esp+0x18]`, which under its SEH triple plus
 *     two saves is E+4 = param_1.
 *   - FUN_00415d40 does `lea esi,[ebp + 0x6a7f88]` with ebp from [esp+0x1c],
 *     E+4 = param_1 under its SEH triple plus three saves -- and 0x6a7f88 is
 *     the active-object list offset the weather-hazard spawners already name.
 *   - FUN_004e3810 does `lea esi,[edi + 0x85c]` with edi from [esp+0x1c],
 *     E+4 = param_1 under its SEH triple plus three saves.
 *
 * PROMOTED (2026-08-27): the BASE-CLASS CONSTRUCTOR of the active-object
 * registry container - the class whose other members this tree has
 * already named. The whole class is one contiguous block: this ctor,
 * the destructor pair 0x4f2ea0 (scalar-deleting, and the single slot of
 * the class vtable 0x557534) / 0x4f2ee0 (non-deleting, and unreferenced
 * - every derived destructor inlines it instead), CreateActiveObjectLayer
 * 0x4f2f00, RegisterActiveObject 0x4f2fb0, SweepActiveObjectRegistry
 * 0x4f3020, and FUN_004f3060, the destroy-all-layers member both
 * destructors call.
 *
 * The BASE SUBOBJECT is 8 bytes: +0 vtable, +4 list head. The 0x20-byte
 * node newed here is the empty-list SENTINEL LAYER, built to exactly the
 * shape CreateActiveObjectLayer gives a real layer (same node vtable
 * 0x557530, whose single slot is 0x4f2e20): key 0xffffffff at +4 and at
 * +8, so both of RegisterActiveObject's sorted searches terminate on it
 * (outer `while ([n+4] <= node[1])`, inner `[n+8] <= node[2]`), and all
 * four link fields pointing at the node itself (+0xc/+0x10 inner list,
 * +0x18/+0x1c outer list) - the empty state the insert at 0x4f2f55 and
 * the sweep at 0x4f3020 both expect.
 *
 * THIS CORRECTS AN EXISTING MODEL. src/cxx/ActiveObjects.h declares
 * CActiveObjectRegistry as 0x20 bytes with outerPrev/outerNext at
 * +0x18/+0x1c, "its own head/outer sentinel", and src/globals.c's
 * comment says the same. The real constructor shows otherwise: the
 * sentinel is a SEPARATE heap node, +0x18/+0x1c are ITS fields, and the
 * container's +8 and up are derived-class storage (FUN_00405f00 writes
 * +8/+0xc/+0x14; InitGame writes +0x10, the input-event ring). The 0x20
 * sizings in globals.c cover the derived objects, not this base.
 *
 * WHY "BASE": every one of the seven call sites overwrites the
 * PTR_FUN_00557534 this stamps with a vtable of its own the moment the
 * call returns - call 0x405f03 then 0x551e88 at 0x405f13; 0x40cd43 then
 * 0x5520a0 at 0x40cd48; 0x4f1753 then 0x557528 at 0x4f1758; 0x4f3943
 * then 0x557550 at 0x4f3948; 0x40192f then 0x551cf0 at 0x401941;
 * 0x416860 then 0x555b7c at 0x416865; 0x4e3832 then 0x555b7c at
 * 0x4e3837. The matching destructors mirror it, each installing its own
 * vtable on entry and then putting PTR_FUN_00557534 back before running
 * FUN_004f3060 and deleting the sentinel through its slot 0:
 * FUN_00405f40 at 0x405f77, FUN_0040cd80 at 0x40cdb7, FUN_00401a70 at
 * 0x401b82, FUN_004e38f0 at 0x4e397c. No site leaves 0x557534 installed.
 *
 * WHICH OBJECTS: the four two-line callers are derived constructors with
 * exactly one caller each, an MSVC dynamic initializer that pairs the
 * construction with an _atexit destructor - FUN_00540d50 builds
 * g_activeObjectRegistry (0xe9be90), FUN_00540d70 builds
 * g_activeObjectRegistry2 (0xe9c0fc), FUN_005425a0 builds
 * g_spriteRegistry (0xea0e18) and FUN_005429d0 builds DAT_00eb168c.
 * The two in-place sites build the class-id-keyed battle entity
 * registry: 0x416855 `lea esi,[ebp + 0x6a7f88]` (&DAT_006a7f88 plus the
 * client-context base) and 0x4e382c `lea esi,[edi + 0x85c]`.
 *
 * CROSS-CHECK, AND A DIVERGENCE IT EXPOSES: gb_init_widget_registry in
 * src/cxx/crt_shims_msvc.c is a hand-written stand-in written before
 * this constructor was found. It sets the same sentinel fields (+0
 * vtable, +4 key, the four self-links) and the container's +4, though
 * not the sentinel's +8/+0x14/+0x15 nor the container's own vtable. Its
 * four gb_registrySentinel slots are NOT the four statics above:
 * crt_shims_msvc.c:384-387 applies them to g_activeObjectRegistry,
 * g_activeObjectRegistry2, g_spriteRegistry and DAT_00e53e88 (the
 * chat-log/replay object, which this constructor never builds), so
 * DAT_00eb168c - a real instance - gets no sentinel from the shim.
 *
 * CONVENTION: `this` arrives in ESI, not EAX. The body never pushes or
 * pops ESI and reads it at 0x4f2e42; the four thunk callers happen to
 * hold it in EAX and do `mov esi,eax`, while the other three load ESI
 * directly (`mov esi,ebp` at 0x40192d and the two `lea esi` above).
 * `this` is returned in EAX at 0x4f2e94; the port drops the return,
 * which is harmless because every caller already holds the object.
 *
 * Faithful to a fault at 0x4f2e7a: when operator_new returns null the
 * original still runs `mov [esi+4],eax` then `mov [eax+0xc],eax` and
 * writes through the null pointer. The port reproduces that.
 *
 * NAME: "_BaseConstructor" is the base-CLASS sense, on the criterion
 * CMobile_BaseDestructor's own header states - installs the base
 * vtable, while derived ctors and dtors install their own first - and
 * follows Panel_BaseConstructor (0x505760) in this directory. Left
 * unprefixed because ActiveObjects.h's CActiveObjectRegistry models the
 * derived widget-registry object rather than this base, and the binary
 * is /GR- with no RTTI, so neither has a recovered class name.
 */
#include "ghidra_types.h"


void ActiveObjectRegistry_BaseConstructor(undefined4 *regEsi)

{
  undefined4 *puVar1;
  undefined4 *unaff_ESI = regEsi;
  
  *unaff_ESI = &PTR_FUN_00557534;
  puVar1 = operator_new(0x20);
  if (puVar1 == (undefined4 *)0x0) {
    puVar1 = (undefined4 *)0x0;
  }
  else {
    puVar1[1] = 0xffffffff;
    puVar1[2] = 0xffffffff;
    puVar1[3] = 0;
    puVar1[4] = 0;
    *(undefined1 *)(puVar1 + 5) = 0;
    *puVar1 = &PTR_FUN_00557530;
    *(undefined1 *)((int)puVar1 + 0x15) = 1;
    puVar1[6] = 0;
    puVar1[7] = 0;
  }
  unaff_ESI[1] = puVar1;
  puVar1[3] = puVar1;
  *(undefined4 *)(unaff_ESI[1] + 0x10) = unaff_ESI[1];
  *(undefined4 *)(unaff_ESI[1] + 0x18) = unaff_ESI[1];
  *(undefined4 *)(unaff_ESI[1] + 0x1c) = unaff_ESI[1];
  return;
}

