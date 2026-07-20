/* CButtonWidget factory - promoted from the raw C port
 * src/ui_widget/CreateButtonWidget.c (0x406020). See ButtonWidget.h and
 * src/cxx/README.md.
 *
 * score.sh: 4060 -> 3520/7700 (/O2) after giving CButtonWidget a real
 * constructor (see ButtonWidget.h) instead of unconditional post-`new`
 * field pokes - the original genuinely null-guards this block (skips
 * all the zero/-1 field-init if `operator new` returns null, matching
 * the same "guarded ctor + unguarded pokes" idiom already documented
 * for CLabel/CEditBox's factories), which a real ctor reproduces for
 * free via the compiler's own new-then-construct-if-non-null codegen.
 *
 * Two things kept from full byte-match here, confirmed as the same
 * cross-cutting blockers already documented elsewhere (see PLAN.md's
 * "known cross-cutting blockers"):
 *   - The constructor's own field-write ORDER doesn't fully match (the
 *     vtable-ptr write, and +0x28/+0x2c vs. +0x24, land at different
 *     points relative to each other) - the same ctor field-write
 *     scheduling quirk seen in CreateLabelWidget/CreateTextEntryWidget,
 *     not chased further there either.
 *   - `RegisterActiveObject`'s call site is structurally different: the
 *     original computes its first argument from a GLOBAL
 *     (`*(int*)0x5b3484 + 0x67ec70`, not from CreateButtonWidget's own
 *     `registry` parameter at all) and calls with no visible stack
 *     cleanup afterward (its own convention isn't ordinary __cdecl/
 *     __stdcall - the raw port's call site already showed
 *     `RegisterActiveObject();` with zero visible arguments). This
 *     `registry`/`layer` parameter pair may not even be the real
 *     shape of the original's first two arguments - left as ordinary
 *     parameters (same tradeoff as CScrollBar's factory) since the
 *     actual register-passed values aren't recoverable from the
 *     decompile alone. RegisterActiveObject (0x4f2fb0) itself is left
 *     as an extern call: it's a sorted list/tree insert sharing its
 *     underlying node structure with the turn-event scheduler
 *     (ARCHITECTURE.md's "PostTurnEvent" note) - reconstructing that
 *     container, and re-deriving this call site's true argument shape
 *     from it, is its own unit of work.
 */
#include "ButtonWidget.h"

extern "C" int FindPreloadedTextureByName(const char *name);
/* RECOVERED (2026-07-18): RegisterActiveObject (0x4f2fb0) is genuinely
 * __fastcall with a dropped-EDI node arg - ECX (param_1) is a dead ABI
 * slot, EDX is the registry, and the node is the third (stack) argument.
 * See src/ui_widget/RegisterActiveObject.c's header for the full
 * derivation. The previous plain-cdecl decl bound `_RegisterActiveObject`,
 * which the stub generator resolves to a no-op (bringup_stubs_cdecl.obj)
 * because the real symbol is the __fastcall-decorated
 * `@RegisterActiveObject@12` - so buttons never actually registered.
 * Declaring it __fastcall(unused, registry, node) binds the real function
 * and matches CreateButtonWidget's original tail (0x40610c: EDX=registry
 * from [esp+8], EDI=the freshly built button, then `call 0x4f2fb0`). */
extern "C" int __fastcall RegisterActiveObject(int unused, void *registry, void *node);

/* FIXED (2026-07-15): these 3 were declared without extern "C" - the real
 * definitions in globals.c have plain C linkage (`_s_active_00551e58`
 * etc), which a C++-mangled declaration never matches at link time
 * (confirmed via a real link test: unresolved `?s_active_00551e58@@3QBDB`
 * and siblings). */
extern "C" {
extern const char s_disable_00551e68[];  /* "disable" */
extern const char s_active_00551e58[];   /* "active" */
extern const char s_ready_00551e80[];    /* "ready" */
}

extern "C" {
/* Real signatures recovered this pass - see each .c file's own header for
 * the angr-disassembly derivation. DeletePoisonedBaseObject is genuinely
 * __thiscall IN THE ORIGINAL, but our port of it is a raw C file and
 * ghidra_types.h erases __thiscall, so the ported symbol is __cdecl with
 * both arguments on the stack - call it directly, NOT through the
 * __fastcall+dummy-EDX cast (that idiom is only for genuine C++ callees
 * whose `this` really is in ECX). Tick/Draw are real __fastcall(1 arg), safe to
 * declare directly. FindStringNoCase is an ordinary __cdecl helper, safe
 * to call directly with no cast trick needed. */
void *DeletePoisonedBaseObject(void *thisPtr, int shouldFree);
int FindStringNoCase(int *table, char *needle);
void __fastcall TickButtonAnimation(int thisPtr);
void __fastcall DrawButtonWidget(int thisPtr);
void NoOpMethod(void);
}

void *CButtonWidget::Delete(int shouldFree)
{
    /* FIXED (2026-07-19): this used the __fastcall+dummy-EDX cast on the
     * belief that DeletePoisonedBaseObject "is genuinely __thiscall". The
     * ORIGINAL is - but our PORT of it is a raw C file, and ghidra_types.h
     * erases __thiscall unconditionally (see its own comment at line 181),
     * so the ported callee actually compiles as __cdecl with BOTH arguments
     * on the stack. Calling it __fastcall put `this` in ECX and pushed only
     * `shouldFree`, so the callee read param_1 = shouldFree (1) and param_2 =
     * garbage - i.e. `_free((void *)1)`. That is the project's documented
     * rule: the __fastcall+dummy idiom is ONLY for genuine C++ callees;
     * erased-__thiscall == __cdecl is correct for raw-C-port callees.
     * Surfaced the moment SweepActiveObjectRegistry was restored and started
     * actually invoking this vtable slot. */
    return DeletePoisonedBaseObject(this, shouldFree);
}

/* SetState is vtable slot 1, shared with unrelated classes as the generic
 * ResolveNamedState (src/registry/ResolveNamedState.c documents the
 * original address 0x461c60 and its 15+ other callers). That shared
 * symbol can't be called directly here: its other callers still pass a
 * single dropped argument under the OLD __fastcall(this) signature
 * (confirmed via a real runtime crash inside FindStringNoCase when it was
 * briefly promoted to a real 2-arg __thiscall - reverted), so
 * ResolveNamedState.c stays a no-op stub. Inlined here instead, using the
 * confirmed-safe FindStringNoCase directly against a real CButtonWidget
 * object (angr-verified at 0x461c60: table = *(this+0x1c), no-op if
 * null, then FindStringNoCase(table, needle) sets state = result and the
 * found/inverse flags). this+0x1c is m_texture: CreateButtonWidget
 * (0x4060ad-0x4060b2) stores FindPreloadedTextureByName's return value
 * there, so the texture resource's own layout doubles as the named-state
 * table (its FindStringNoCase-searchable name array), despite the
 * generic "m_texture" field name. */
void CButtonWidget::SetState(const char *name)
{
    int *table = (int *)m_texture;
    if (table == 0) {
        return;
    }
    int result = FindStringNoCase(table, (char *)name);
    m_state = result;
    if (result != -1) {
        m_unk20 = 1;
        m_unk34 = 0;
        m_unk2c = 0;
        m_unk28 = 0;
    } else {
        m_unk20 = 0;
        m_unk34 = 1;
    }
}

void CButtonWidget::Tick()
{
    TickButtonAnimation((int)this);
}

void CButtonWidget::Draw()
{
    DrawButtonWidget((int)this);
}

void CButtonWidget::NoOp()
{
    NoOpMethod();
}

/* 0x406020 - __stdcall (the original ret-cleans its stack args). Allocates
 * the 80-byte object, stores position/size/id, resolves the texture via
 * FindPreloadedTextureByName, then picks an initial visual state string:
 *   enabled == false          -> "disable"
 *   enabled, state == 3       -> "active" (only when m_unk20's flag is set)
 *   enabled, state != 3 or -1 -> "ready" (also forced when the resolve above
 *                                didn't land on state 3)
 * matching the literal branch structure of the decompiled original,
 * including its exact fallthrough into a final unconditional "ready" call
 * when the resolved state isn't 3.
 */
extern "C" CButtonWidget *CreateButtonWidget(void *registry, int layer, int id, int spriteBase,
                                              const char *textureName, int x, int y,
                                              int w, int h, char enabled, int arg11)
{
    CButtonWidget *p = new CButtonWidget(layer, id);

    p->m_spriteBase = spriteBase;
    /* FIXED (2026-07-18): +0x40 is the WIDTH and +0x44 the HEIGHT, not the
     * reverse - the original CreateButtonWidget stores [E+0x20]=w into +0x40
     * and [E+0x24]=h into +0x44 (0x40608b/0x4060a7), and FindActiveObjectAt's
     * hit-test reads +0x40 as the X-extent (`x + [+0x40]`). With them swapped
     * every button's clickable box was only `h` wide, so a click near the
     * button's true right half (e.g. BUDDY's center) missed and never fired
     * OnCommand. */
    p->m_unk40      = w;
    p->m_x          = x;
    p->m_y          = y;
    p->m_unk44      = h;
    p->m_unk48      = arg11;
    p->m_texture    = FindPreloadedTextureByName(textureName);

    const char *stateName;
    if (!enabled) {
        stateName = s_disable_00551e68;
    } else {
        if (p->m_state != 3 && p->m_state != -1) {
            goto setReady;
        }
        /* FIXED (2026-07-15): was reading p->m_unk20 (+0x20) - confirmed via
         * angr disassembly (0x4060d2: `cmp byte ptr [edi+0x4c], 1`) that the
         * original checks +0x4c, not +0x20. +0x4c is never written by this
         * factory (m_unk4c is genuinely read-only-garbage from `operator
         * new`/left as documented "opaque, untraced" in ButtonWidget.h),
         * matching the original's own dependence on whatever `operator new`
         * happens to return there - reproduced as-is rather than guessing a
         * real meaning for the field. */
        if (p->m_unk4c[0] == 1) {
            p->SetState(s_active_00551e58);
            goto setReady;
        }
        stateName = s_ready_00551e80;
    }
    p->SetState(stateName);
setReady:
    p->m_unk20 = 0;
    if (p->m_state != 3) {
        p->SetState(s_ready_00551e80);
    }
    RegisterActiveObject(0, registry, p);
    return p;
}
