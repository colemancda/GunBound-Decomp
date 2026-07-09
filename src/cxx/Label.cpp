/* CLabel methods - promoted from the raw C port
 * src/ui_widget/Label_OnMouseDown.c (0x5052e0). See src/cxx/README.md. */
#include "Widget.h"

/* 0x507ee0 - the label factory (docs/widgets.md's CreateLabelWidget),
 * __stdcall (the original ret-cleans 0x18 bytes). Its exact shape is
 * `new CLabel()` (default ctor inlined under the null guard) followed
 * by UNGUARDED argument pokes - the original really does store through
 * a null pointer if the allocation fails; preserved as-is. */
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
 * "Draw blits via FindSpriteFrame": the blit is parent-mediated.) */
void CLabel::Draw()
{
    if (m_unk38 != 0 && m_unk1c != 0) {
        OnCommand(1, m_id, 0);
    }
    if (m_children.GetCount() != 0) {
        unsigned int i = 0;
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
 * point was inside this label's rect at all. */
bool CLabel::OnMouseDown(int x, int y)
{
    bool inside = !m_hidden &&
                  m_x < x && x < m_x + m_width &&
                  m_y < y && y < m_y + m_height;
    if (inside && m_unk38 != 0 && m_unk1c != 0) {
        OnCommand(0, m_id, 0);
    }
    if (ResetPressState(x, y)) {
        return true;
    }
    return inside;
}
