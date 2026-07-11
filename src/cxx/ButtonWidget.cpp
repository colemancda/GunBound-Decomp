/* CButtonWidget factory - promoted from the raw C port
 * src/ui_widget/CreateButtonWidget.c (0x406020). See ButtonWidget.h and
 * src/cxx/README.md.
 *
 * Two things kept from full byte-match here, both already-documented
 * project-wide blockers (see PLAN.md's "known cross-cutting blockers"):
 *   - `registry`/`layer` (params 1/2) flow into RegisterActiveObject via
 *     a custom register convention the decompiler couldn't resolve as
 *     ordinary stack args (the raw port's own call site shows
 *     `RegisterActiveObject();` with zero visible arguments) - kept here
 *     as ordinary parameters, same tradeoff as CScrollBar's factory.
 *   - RegisterActiveObject (0x4f2fb0) itself is left as an extern call:
 *     it's a sorted list/tree insert keyed by a layer value then a
 *     secondary key, sharing its underlying node structure with the
 *     turn-event scheduler (ARCHITECTURE.md's "PostTurnEvent" note) -
 *     reconstructing that container is its own unit of work.
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
    CButtonWidget *p = new CButtonWidget();
    p->m_layer      = layer;  /* +0x04: the observed call sites always pass 0 here */
    p->m_id         = id;
    p->m_unk0c      = 0;
    p->m_unk10      = 0;
    p->m_unk14      = 0;
    p->m_unk15      = 0;
    p->m_state      = -1;
    p->m_texture    = 0;
    p->m_unk20      = 0;
    p->m_unk28      = 0;
    p->m_unk2c      = 0;

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
