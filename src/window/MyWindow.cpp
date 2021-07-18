#include <gtkmm.h>

#include "shared/MyWindow.h"

MyWindow::MyWindow(BaseObjectType *obj, Glib::RefPtr<Gtk::Builder> const &builder)
        : Gtk::ApplicationWindow(obj),
          builder{builder} {

    set_position(Gtk::WIN_POS_CENTER);
    set_default_size(1848, 1053);

    builder->get_widget_derived("app_container",appContainer);

    builder->get_widget("frame",frame);
    frame->set_size_request(1500,1);

    show_all();
}

MyWindow::~MyWindow() {}

MyWindow::MyWindow() {}



