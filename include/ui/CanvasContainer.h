#ifndef XPER_CPP_CANVASCONTAINER_H
#define XPER_CPP_CANVASCONTAINER_H


#include <gtkmm/paned.h>
#include <gtkmm/builder.h>
#include <gtkmm/fixed.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/aspectframe.h>
#include <gtkmm/viewport.h>
#include "MainCanvas.h"

class CanvasContainer : public Gtk::Paned {

public:
    CanvasContainer(BaseObjectType *obj,Glib::RefPtr<Gtk::Builder> builder);
    CanvasContainer();
    ~CanvasContainer();
    static CanvasContainer *get_instance(Glib::RefPtr<Gtk::Builder> refPtr);
    CanvasContainer(CanvasContainer const&) = delete;
    void operator=(CanvasContainer const&) = delete;

private:
    Glib::RefPtr<Gtk::Builder> m_builder;
    std::shared_ptr<MainCanvas> m_mainCanvas;
    Gtk::ScrolledWindow *m_scrolledCanvas ,*m_scrolledMenu;
};


#endif //XPER_CPP_CANVASCONTAINER_H
