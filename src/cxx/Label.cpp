/* CLabel methods - promoted from the raw C port
 * src/ui_widget/Label_OnMouseDown.c (0x5052e0). See src/cxx/README.md. */
#include "Widget.h"

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
CLabel * __stdcall CreateLabelWidget(int id, int spriteId, int x, int y, int w, int h)
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
