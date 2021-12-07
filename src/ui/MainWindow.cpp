#include <iostream>
#include <utility>

#include "ui/MainWindow.h"
#include "globals/GlobalValues.h"

int global_default_width;
int global_default_height;

MainWindow::~MainWindow() {
    delete m_appContainer;
    delete m_startingBox;
}

MainWindow::MainWindow(BaseObjectType *obj, Glib::RefPtr<Gtk::Builder> builder)
        : Gtk::ApplicationWindow(obj),
          m_builder{std::move(builder)},
          m_appContainer(nullptr),
          m_startingBox(nullptr) {

    set_position(Gtk::WIN_POS_CENTER);
    auto screen = Gdk::Screen::get_default();
    global_default_width = screen->get_width() / 100 * 80;
    global_default_height = screen->get_height() / 100 * 80;
    auto m_xCoordinate = (screen->get_width() - global_default_width) / 2;
    auto m_yCoordinate = (screen->get_height() - global_default_height) / 2;
    move(m_xCoordinate, m_yCoordinate);
    this->set_resizable(true);
    set_default_size(global_default_width, global_default_height);
    m_startingBox = StartingBox::get_instance(m_builder);
    m_appContainer = AppContainer::get_instance(m_builder);
    add(*m_startingBox);
    show_all();
}

void MainWindow::on_load_project(string name) {
    this->m_projectName = name;
    this->set_title("Xper :  " + m_projectName);
    this->remove();
    this->add(*m_appContainer);
}

MainWindow * MainWindow::get_instance(Glib::RefPtr<Gtk::Builder> builder) {
    static MainWindow *window = nullptr;
    if(window == nullptr){
        builder->get_widget_derived("window",window);
    }
    return window;
}

MainWindow::MainWindow() {

}



