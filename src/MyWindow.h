#ifndef XPER_CPP_MYWINDOW_H
#define XPER_CPP_MYWINDOW_H

#include <gtkmm.h>
#include <gdkmm.h>

#include "SidebarContainer.h"

class MyWindow : public Gtk::Window
{

public:
    MyWindow();

protected:

    bool on_draw_cairo(const Cairo::RefPtr<Cairo::Context> &cr);
    bool on_scroll(GdkEventScroll *ev);
    void on_open_image_button_clicked();
    void on_show_side_bar_button_clicked();

    SidebarContainer sidebar;

    Gtk::HeaderBar header;
    Gtk::Button open_image_button;
    Glib::RefPtr<Gdk::Pixbuf>   image;
    Glib::ustring fileName;
    Gtk::DrawingArea draw;
    Gtk::Button show_side_bar;

    double scale;
};



#endif
