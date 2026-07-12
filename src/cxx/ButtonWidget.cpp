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
extern "C" void RegisterActiveObject(void *registry, CButtonWidget *button);

extern const char s_disable_00551e68[];  /* "disable" */
extern const char s_active_00551e58[];   /* "active" */
extern const char s_ready_00551e80[];    /* "ready" */

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
CButtonWidget * __stdcall CreateButtonWidget(void *registry, int layer, int id, int spriteBase,
                                              const char *textureName, int x, int y,
                                              int w, int h, char enabled, int arg11)
{
    CButtonWidget *p = new CButtonWidget(layer, id);

    p->m_spriteBase = spriteBase;
    p->m_unk40      = h;
    p->m_x          = x;
    p->m_y          = y;
    p->m_unk44      = w;
    p->m_unk48      = arg11;
    p->m_texture    = FindPreloadedTextureByName(textureName);

    const char *stateName;
    if (!enabled) {
        stateName = s_disable_00551e68;
    } else {
        if (p->m_state != 3 && p->m_state != -1) {
            goto setReady;
        }
        if (p->m_unk20 == 1) {
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
    RegisterActiveObject(registry, p);
    return p;
}
