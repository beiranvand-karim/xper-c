#ifndef XPER_CPP_APPCONTAINER_H
#define XPER_CPP_APPCONTAINER_H

#include <gtkmm.h>

#include "DrawOptions.h"
#include "Drawer.h"
#include "DrawerContainer.h"
#include "EditorContainer.h"

class AppContainer : public Gtk::Box {
public:

    AppContainer(BaseObjectType* obj, Glib::RefPtr<Gtk::Builder> const& builder);

    AppContainer();

    void on_about_item_activate();

protected:
    void on_switcher_clicked();

private:
    Glib::RefPtr<Gtk::Builder> appContainerBuilder;
    Glib::RefPtr<Gtk::Builder> dialogBuilder;

    Gtk::AboutDialog* dialog;
    Gtk::Button* buttonDialog;

    DrawerContainer *drawerContainer = nullptr;
    EditorContainer *editorContainer = nullptr;

    Gtk::ModelButton *switcher;
    Glib::RefPtr<Gdk::Pixbuf> pix;
    Gtk::Image switcherImg;

    bool isDrawer;
    std::string prefixResource;
};

#endif //XPER_CPP_APPCONTAINER_H
