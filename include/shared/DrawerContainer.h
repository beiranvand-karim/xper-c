#ifndef XPER_CPP_DRAWERCONTAINER_H
#define XPER_CPP_DRAWERCONTAINER_H

#include <gtkmm.h>
#include "DrawOptions.h"
#include "Drawer.h"

class DrawerContainer : public Gtk::Box {

public:
    DrawerContainer(BaseObjectType *obj, Glib::RefPtr<Gtk::Builder> const &builder );

private:
    Glib::RefPtr<Gtk::Builder> drawerContainerBuilder;

    DrawOptions* drawOptions = nullptr;
    Drawer* drawer  = nullptr;
};


#endif //XPER_CPP_DRAWERCONTAINER_H
