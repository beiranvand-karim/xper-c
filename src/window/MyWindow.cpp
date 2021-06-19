#include <gdkmm.h>
#include <gtkmm.h>


#include "shared/MyWindow.h"

MyWindow::MyWindow() {


    set_border_width(10);
    set_default_size(1800, 700);
    set_position(Gtk::WIN_POS_CENTER);
    set_events(Gdk::BUTTON1_MOTION_MASK);

    set_titlebar(header);
    header.set_show_close_button(true);
    header.set_title("CPP Editor");

    add(editorContainer);
    show_all();

}