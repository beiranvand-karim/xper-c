#ifndef XPER_CPP_MYWINDOW_H
#define XPER_CPP_MYWINDOW_H

#include <gtkmm.h>
#include <gdkmm.h>

#include "AppContainer.h"

class MyWindow : public Gtk::ApplicationWindow {

public:
    MyWindow(BaseObjectType* obj, Glib::RefPtr<Gtk::Builder> const& builder);
    MyWindow();

    virtual ~MyWindow();

private:

    AppContainer* appContainer = nullptr;
    Glib::RefPtr<Gtk::Builder> builder;
    Gtk::Frame* frame;
};



#endif
