#include <gtkmm.h>

#include "shared/MyWindow.h"

MyWindow::MyWindow(BaseObjectType *obj, Glib::RefPtr<Gtk::Builder> const &builder)
        : Gtk::ApplicationWindow(obj),
          builder{builder} {

    set_position(Gtk::WIN_POS_CENTER);

    builder->get_widget_derived("app_container",appContainer);

    show_all();
}

MyWindow::~MyWindow() {}

MyWindow::MyWindow() {}



