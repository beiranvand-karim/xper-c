#include <iostream>

#include "ui/AppContainer.h"

using namespace std;

AppContainer::~AppContainer() {
    delete m_sidebarDrawing;
    delete m_canvasContainer;
}

AppContainer::AppContainer(BaseObjectType *obj, Glib::RefPtr<Gtk::Builder> const &builder) :
        Gtk::Box(obj),
        m_appContainerBuilder{builder},
        m_sidebarDrawing(nullptr),
        m_canvasContainer(nullptr){

    m_sidebarDrawing = SidebarDrawing::get_instance(m_appContainerBuilder);
    m_canvasContainer = CanvasContainer::get_instance(m_appContainerBuilder);
}

AppContainer *AppContainer::get_instance(Glib::RefPtr<Gtk::Builder> builder) {
    static AppContainer* appContainer = nullptr;
    if(appContainer == nullptr){
        builder->get_widget_derived("app_container", appContainer);
    }
    return appContainer;
}



