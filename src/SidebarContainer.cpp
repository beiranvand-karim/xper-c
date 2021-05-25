#include <gtkmm.h>

#include "SidebarContainer.h"


SidebarContainer::SidebarContainer() {


    set_orientation(Gtk::ORIENTATION_HORIZONTAL);

    sidebar.set_stack(stack);
    stack.set_transition_type(Gtk::STACK_TRANSITION_TYPE_SLIDE_UP_DOWN);

    pack_start(sidebar, false, false, 0);
    pack_start(stack, true, true, 0);


    stack.add(label_home, "home", "Home");
    stack.add(label_about, "about", "About");
    stack.add(label_contact, "contact", "Contact");

    label_home.set_text("HOME");
    label_about.set_text("About");
    label_contact.set_text("Contact");

    sidebar.set_size_request(200, 500);
}


