#ifndef XPER_CPP_SIDEBARDRAWING_H
#define XPER_CPP_SIDEBARDRAWING_H

#include "iostream"

#include <gtkmm/buttonbox.h>
#include <gtkmm/modelbutton.h>
#include <gtkmm/builder.h>
#include <gtkmm/image.h>

using namespace std;

class SidebarDrawing : public Gtk::ButtonBox {

public:
    SidebarDrawing(BaseObjectType *obj, Glib::RefPtr<Gtk::Builder> builder);
    ~SidebarDrawing();
    static SidebarDrawing *get_instance(Glib::RefPtr<Gtk::Builder> refPtr);
    SidebarDrawing(SidebarDrawing const&) = delete;
    void operator=(SidebarDrawing const&) = delete;

protected:
    static void icon_button_setter(Gtk::Button *btn, const string& fileName);

private:
    SidebarDrawing();
    Glib::RefPtr<Gtk::Builder> m_builder;
    Gtk::Button *m_selectBtn,
            *m_frameBtn,
            *m_rectBtn,
            *m_circleBtn,
            *m_lineBtn;
};


#endif //XPER_CPP_SIDEBARDRAWING_H
