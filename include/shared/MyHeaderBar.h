#ifndef XPER_CPP_MYHEADERBAR_H
#define XPER_CPP_MYHEADERBAR_H

#include <gtkmm.h>

class MyHeaderBar: public Gtk::HeaderBar {
public:
    MyHeaderBar();
    Gtk::CheckMenuItem cppDrawer;

protected:

    Gtk::MenuBar menuBar;
    Gtk::Menu fileSubMenu;
    Gtk::MenuItem fileItem;

};
#endif //XPER_CPP_MYHEADERBAR_H
