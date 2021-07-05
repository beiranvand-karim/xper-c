#ifndef XPER_CPP_MYWINDOW_H
#define XPER_CPP_MYWINDOW_H

#include <gtkmm.h>
#include <gdkmm.h>

#include "MyHeaderBar.h"
#include "DrawerContainer.h"

class MyWindow : public Gtk::Window
{

public:
    MyWindow();
    void on_drawer_select();

protected:

    MyHeaderBar header;
    DrawerContainer drawerContainer;

    Gtk::Image windowImage;
};



#endif
