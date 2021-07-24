#include <gtkmm.h>
#include <iostream>

#include "shared/MyWindow.h"

MyWindow::MyWindow(BaseObjectType *obj, Glib::RefPtr<Gtk::Builder> const &builder)
        : Gtk::ApplicationWindow(obj),
          builder{builder} {

    set_position(Gtk::WIN_POS_CENTER);
    auto screen = Gdk::Screen::get_default();

     width = screen->get_width() / 100 * 80;
     height = screen->get_height() / 100 * 80;
     xCoordinate = (screen->get_width()  - width ) / 2;
     yCoordinate = (screen->get_height()  - height ) / 2;

    move(xCoordinate, yCoordinate);

    builder->get_widget_derived("app_container", appContainer);

    set_size_request(width,height);

    show_all();
}

MyWindow::~MyWindow() {}

MyWindow::MyWindow() {}



