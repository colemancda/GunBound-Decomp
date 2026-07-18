/* CLabel methods - promoted from the raw C port
 * src/ui_widget/Label_OnMouseDown.c (0x5052e0). See src/cxx/README.md. */
#include "Widget.h"

/* Sprite-lookup/blit primitives - the same recovered shapes Panel.cpp
 * uses for CWorldListPanel::Update (see Widget_DrawSelf.c /
 * FindSpriteFrame.c for the derivations). */
extern "C" {
extern unsigned int DAT_0079352c;
extern unsigned char DAT_00ea0e18[0x20];
int FindSpriteFrame(int container, unsigned int outerKey, unsigned int innerKey);
int BlitSprite16bpp(int frame, int x, int y, int outerKey);
int BlitSpriteClipped(int frame, int x, int y, int outerKey);
}

/* 0x507ee0 - the label factory (docs/widgets.md's CreateLabelWidget),
 * __stdcall (the original ret-cleans 0x18 bytes). Its exact shape is
 * `new CLabel()` (default ctor inlined under the null guard) followed
 * by UNGUARDED argument pokes - the original really does store through
 * a null pointer if the allocation fails; preserved as-is.
 * score.sh: 550/3600 - the zero-init and argument pokes all match;
 * remaining delta is field-write ordering within the inlined default
 * ctor (the vtable-pointer write lands at a different point relative to
 * the other field writes - a compiler scheduling choice, not a logic
 * difference). Not chased further. */
extern "C" CLabel *CreateLabelWidget(int id, int spriteId, int x, int y, int w, int h)
{
    CLabel *p = new CLabel();
    p->m_id = id;
    p->m_spriteId = spriteId;
    p->m_x = x;
    p->m_y = y;
    p->m_width = w;
    p->m_height = h;
    return p;
}

/* 0x50e350, vtable slot 8. The label does NOT blit its own sprite:
 * when both gate flags are set it reports evt 1 ("paint me") up its
 * own OnCommand spine - the owning panel's OnCommand override does
 * the actual FindSpriteFrame/blit for the label's current state -
 * then the usual child draw broadcast. (Refines docs/widgets.md's
 * "Draw blits via FindSpriteFrame": the blit is parent-mediated.)
 * score.sh: 105/3500 - effectively perfect (loop-hoist fix applied). */
void CLabel::Draw()
{
    if (m_unk38 != 0 && m_enabled != 0) {
        OnCommand(1, m_id, 0);
    }
    unsigned int count = m_children.GetCount();
    unsigned int i = 0;
    if (i < count) {
        do {
            m_children[i]->Draw();
            ++i;
        } while (i < (unsigned int)m_children.GetCount());
    }
}

/* 0x505380, vtable slot 9 (RECOVERED 2026-07-18 via the 0x557da0 vtable
 * dump + angr/capstone of the body - this function was never ported at
 * all, which is why every CLabel-sprite widget, most visibly the
 * scrollbar arrows, drew nothing). THE label sprite draw: picks the
 * 5-way visual state
 *     0 normal / 1 hover (+0x39) / 2 pressed (+0x39 && +0x38)
 *     / 3 disabled (!+0x1c) / 4 tab-selected (+0x3a == 1)
 * (matching the 5 states each .epa button definition carries), then
 * blits frame=state of sprite set m_spriteId at (m_x, m_y) - the exact
 * FindSpriteFrame/BlitSprite16bpp/BlitSpriteClipped sequence at
 * 0x5053c6-0x505414: EAX=&DAT_00ea0e18, EDX=[this+0x3c], ESI=state,
 * gated on the locked surface DAT_0079352c. Hidden (+0x1e) returns
 * WITHOUT the child broadcast (orig 0x50541f: ret before the 0x50ecf0
 * tail); otherwise falls into the base broadcast (CWidget::Update ==
 * 0x50ecf0). */
void CLabel::Update()
{
    if (m_hidden) {
        return;
    }
    int state = 0;
    if (m_enabled == 0) {
        state = 3;
    } else if (m_tabSelected == 1) {
        state = 4;
    } else if (m_unk39 != 0) {
        state = (m_unk38 != 0) ? 2 : 1;
    }
    if (DAT_0079352c != 0 && state >= 0) {
        int rec = FindSpriteFrame((int)DAT_00ea0e18, (unsigned int)m_spriteId, (unsigned int)state);
        if (rec != 0) {
            if (*(unsigned char *)(rec + 0x18) == 1) {
                BlitSprite16bpp(state, m_x, m_y, m_spriteId);
            } else {
                BlitSpriteClipped(state, m_x, m_y, m_spriteId);
            }
        }
    }
    CWidget::Update();
}

/* 0x5052e0, vtable slot 2. If the point lands in the rect and both
 * gate flags (+0x1c base, +0x38 label) are set, report the click
 * through the OnCommand spine: evt 0 ("clicked"), this widget's id.
 * The call goes through this object's OWN slot 7 - the leaf default
 * (0x50eb10) forwards to m_parent, and panel subclasses that override
 * slot 7 see their children's clicks directly.
 *
 * Returns whether the event was consumed: true if the shared
 * press-reset tail (ResetPressState, 0x50e2f0) took it, or if the
 * point was inside this label's rect at all.
 * score.sh: 105/6900 (2850 -> 105) - effectively perfect. Two source
 * fixes: the original recomputes the whole rect-test chain twice (once
 * to guard OnCommand, again for the return) rather than caching it in a
 * local - caching it changes the codegen; and the two-return-statement
 * form (`if (ResetPressState(...)) return true; return inside;`) gets
 * its own early-return epilogue, whereas `return ResetPressState(...)
 * || inside;` shares one epilogue with the tail, matching the original
 * (same idiom already used by ResetPressState/OnDragMove elsewhere in
 * this file). */
bool CLabel::OnMouseDown(int x, int y)
{
    if (!m_hidden && m_x < x && x < m_x + m_width &&
        m_y < y && y < m_y + m_height) {
        if (m_unk38 != 0 && m_enabled != 0) {
            OnCommand(0, m_id, 0);
        }
    }
    return ResetPressState(x, y) ||
           (!m_hidden && m_x < x && x < m_x + m_width &&
            m_y < y && y < m_y + m_height);
}
