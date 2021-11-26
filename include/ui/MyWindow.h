#ifndef XPER_CPP_MYWINDOW_H
#define XPER_CPP_MYWINDOW_H

#include "gtkmm.h"

#include "AppContainer.h"
#include "StartingBox.h"

class MyWindow : public Gtk::ApplicationWindow {

public:
    MyWindow(BaseObjectType *obj, Glib::RefPtr<Gtk::Builder> const &builder);
    MyWindow();
    virtual ~MyWindow();
    void load_main_window();

protected:
    void on_check_resize() override;

private:
    AppContainer *m_appContainer = nullptr;
    StartingBox *m_startingBox = nullptr;
    Glib::RefPtr<Gtk::Builder> m_builder;
    int m_width,
        m_height,
        m_xCoordinate,
        m_yCoordinate;
    Gtk::Button *m_newProjectBtn;
};


#endif
