#include <gdkmm.h>
#include <gtkmm.h>

#include "shared/MyWindow.h"

MyWindow::MyWindow() {


    set_position(Gtk::WIN_POS_CENTER);
    set_events(Gdk::BUTTON1_MOTION_MASK);
    set_default_size(1848, 800);
    queue_resize();


    set_titlebar(header);

    header.cppDrawer.signal_activate().connect(sigc::mem_fun(*this, &MyWindow::on_drawer_select));

    // window image
    auto pixBuf = Gdk::Pixbuf::create_from_file("resource/window-image.png", 100, 100);
    windowImage.set(pixBuf);


    add(windowImage);
    show_all();
}

void MyWindow::on_drawer_select() {

    remove();
    add(drawerContainer);
    drawerContainer.show_all();
    drawerContainer.set_size_request(1800, 1000);

}

