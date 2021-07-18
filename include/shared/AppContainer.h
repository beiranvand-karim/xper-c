#ifndef XPER_CPP_APPCONTAINER_H
#define XPER_CPP_APPCONTAINER_H

#include <gtkmm.h>

#include "DrawOptions.h"
#include "Drawer.h"

class AppContainer : public Gtk::Box {
public:

    AppContainer(BaseObjectType* obj, Glib::RefPtr<Gtk::Builder> const& builder);

    AppContainer();

    void on_about_item_activate();

private:
    Glib::RefPtr<Gtk::Builder> appContainerBuilder;
    Glib::RefPtr<Gtk::Builder> dialogBuilder;

    Gtk::AboutDialog* dialog;
    Gtk::Button* buttonDialog;

    DrawOptions* drawOptions = nullptr;
    Drawer* drawer  = nullptr;

};

#endif //XPER_CPP_APPCONTAINER_H
