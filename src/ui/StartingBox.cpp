#include <ui/MainWindow.h>
#include "iostream"

#include "ui/StartingBox.h"

using namespace std;


StartingBox::~StartingBox() {
    delete m_newProjectBtn;
    delete m_nameInput;
}

StartingBox::StartingBox(BaseObjectType *obj, Glib::RefPtr<Gtk::Builder> const &builder) :
        Gtk::Box(obj),
        m_builder(builder),
        m_newProjectBtn(nullptr),
        m_nameInput(nullptr) {


    m_builder->get_widget("new_project_btn", m_newProjectBtn);
    m_builder->get_widget("project_name_input", m_nameInput);

    m_newProjectBtn->set_sensitive(false);

    m_nameInput->signal_changed().connect([&]() {
        if (m_nameInput->get_buffer()->get_text().empty()) {
            m_newProjectBtn->set_sensitive(false);
            m_newProjectBtn->get_style_context()->remove_class("submit-btn");
            m_newProjectBtn->get_style_context()->add_class("disable-btn");
        } else {
            m_newProjectBtn->get_style_context()->add_class("submit-btn");
            m_newProjectBtn->get_style_context()->remove_class("disable-btn");
            m_newProjectBtn->set_sensitive(true);
        }
    });

    m_newProjectBtn->signal_clicked().connect([&]() {
        auto window = MainWindow::get_instance(Glib::RefPtr<Gtk::Builder>());
        window->on_load_project(m_nameInput->get_text());
        window->maximize();
    });
}

StartingBox *StartingBox::get_instance(Glib::RefPtr<Gtk::Builder> builder) {
    static StartingBox *startingBox = nullptr;
    if(startingBox == nullptr){
        builder->get_widget_derived("starting_container", startingBox);
    }
    return startingBox;
}







