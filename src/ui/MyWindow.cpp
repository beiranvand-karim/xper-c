#include <gtkmm.h>
#include <iostream>

#include "ui/MyWindow.h"

MyWindow::MyWindow(BaseObjectType *obj, Glib::RefPtr<Gtk::Builder> const &builder)
        : Gtk::ApplicationWindow(obj),
          m_builder{builder},
          m_newProjectBtn(nullptr) {

    set_position(Gtk::WIN_POS_CENTER);
    auto screen = Gdk::Screen::get_default();
    m_width = screen->get_width() / 100 * 80;
    m_height = screen->get_height() / 100 * 80;
    m_xCoordinate = (screen->get_width() - m_width) / 2;
    m_yCoordinate = (screen->get_height() - m_height) / 2;
    move(m_xCoordinate, m_yCoordinate);
    this->set_resizable(true);
    set_default_size(m_width, m_height);

    m_builder->get_widget_derived("starting_container", m_startingBox);
    m_builder->get_widget_derived("app_container", m_appContainer);
    m_builder->get_widget("new_project", m_newProjectBtn);

    m_newProjectBtn->signal_clicked().connect([&] {
        this->remove();
        this->add(*m_appContainer);
    });

    add(*m_startingBox);

    show_all();
}

MyWindow::~MyWindow() {
    cout << "window is deleted" << endl;
    delete m_appContainer;
    delete m_startingBox;
}

MyWindow::MyWindow() {}

void MyWindow::on_check_resize() {
    m_startingBox->set_size(get_width(), get_height() / 2);
    Container::on_check_resize();
}



