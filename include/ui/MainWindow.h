#ifndef XPER_CPP_MAINWINDOW_H
#define XPER_CPP_MAINWINDOW_H

#include "gtkmm/applicationwindow.h"
#include "gtkmm/builder.h"
#include "gtkmm/button.h"

#include "AppContainer.h"
#include "StartingBox.h"

class MainWindow : public Gtk::ApplicationWindow {

public:
    MainWindow(BaseObjectType *obj, Glib::RefPtr<Gtk::Builder> builder);
    MainWindow(MainWindow const&) = delete;
    void operator=(MainWindow const&) = delete;
    virtual ~MainWindow();
    static MainWindow *get_instance(Glib::RefPtr<Gtk::Builder> builder);

    void on_load_project(string name);
private:
    MainWindow();
    AppContainer *m_appContainer;
    StartingBox *m_startingBox;
    Glib::RefPtr<Gtk::Builder> m_builder;
    Glib::ustring m_projectName;

};


#endif
