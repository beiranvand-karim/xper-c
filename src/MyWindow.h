#ifndef XPER_CPP_MYWINDOW_H
#define XPER_CPP_MYWINDOW_H

#include <gtk/gtk.h>
#include <gtkmm.h>

class MyWindow : public Gtk::Window
{

public:
    MyWindow();

protected:

    void on_button_clicked();
    Gtk::Button button;
    Gtk::HeaderBar header;
    Gtk::Image image;
};



#endif
