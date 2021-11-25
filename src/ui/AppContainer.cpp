#include <iostream>

#include "ui/AppContainer.h"

using namespace std;
AppContainer::AppContainer(BaseObjectType *obj, Glib::RefPtr<Gtk::Builder> const &builder) :
        Gtk::Box(obj),
        m_appContainerBuilder{builder}{}

AppContainer::AppContainer() {}


AppContainer::~AppContainer() {
    cout<<"app container is deleted"<<endl;
}
