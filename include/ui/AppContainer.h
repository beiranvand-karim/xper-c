#ifndef XPER_CPP_APPCONTAINER_H
#define XPER_CPP_APPCONTAINER_H

#include "gtkmm.h"

class AppContainer : public Gtk::Box {
public:

    AppContainer(BaseObjectType* obj, Glib::RefPtr<Gtk::Builder> const& builder);

    virtual ~AppContainer();

    AppContainer();
private:
    Glib::RefPtr<Gtk::Builder> m_appContainerBuilder;
};

#endif //XPER_CPP_APPCONTAINER_H
