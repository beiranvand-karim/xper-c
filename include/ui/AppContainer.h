#ifndef XPER_CPP_APPCONTAINER_H
#define XPER_CPP_APPCONTAINER_H

#include "gtkmm/box.h"
#include "gtkmm/builder.h"

#include "SidebarDrawing.h"
#include "CanvasContainer.h"

class AppContainer : public Gtk::Box {

public:
    AppContainer(BaseObjectType *obj, Glib::RefPtr<Gtk::Builder> const &builder);
    ~AppContainer();
    static AppContainer *get_instance(Glib::RefPtr<Gtk::Builder> refPtr);

    AppContainer(AppContainer const&) = delete;
    void operator=(AppContainer const&) = delete;

private:
    AppContainer();
    Glib::RefPtr<Gtk::Builder> m_appContainerBuilder;
    SidebarDrawing *m_sidebarDrawing;
    CanvasContainer *m_canvasContainer;
};

#endif //XPER_CPP_APPCONTAINER_H
