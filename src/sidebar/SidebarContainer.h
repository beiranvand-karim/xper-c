#ifndef XPER_CPP_SIDEBARCONTAINER_H
#define XPER_CPP_SIDEBARCONTAINER_H

#include <gtkmm.h>
#include <gdkmm.h>

#include "../textview/TextViewContainer.h"

class SidebarContainer : public Gtk::Box  {
public:
    SidebarContainer();

protected:
    Gtk::StackSidebar sidebar;
    Gtk::Stack stack;
    Gtk::Label label_home, label_about, label_contact;

    TextViewContainer textview;
};


#endif //XPER_CPP_SIDEBARCONTAINER_H
