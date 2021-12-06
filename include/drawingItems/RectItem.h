#ifndef XPER_CPP_RECTITEM_H
#define XPER_CPP_RECTITEM_H


#include <goocanvasmm/rect.h>

class RectItem : public Goocanvas::ItemSimple {

public:
    ~RectItem();
    static Glib::RefPtr<RectItem> create();


protected:
    RectItem();
    bool on_enter_notify_event(const Glib::RefPtr<Item> &target, GdkEventCrossing *event) override;

    bool on_leave_notify_event(const Glib::RefPtr<Item> &target, GdkEventCrossing *event) override;
    bool on_button_press_event(const Glib::RefPtr<Item> &target, GdkEventButton *event) override;
    void simple_create_path_vfunc(const Cairo::RefPtr<Cairo::Context> &cr) override;

private:
    int m_id, m_position;
    Gdk::RGBA m_RGBA_fillColor,
            m_RGBA_strokeColor;
    bool m_fill,
            m_stroke;
    int m_x,
            m_y,
            m_width,
            m_height;
};


#endif //XPER_CPP_RECTITEM_H
