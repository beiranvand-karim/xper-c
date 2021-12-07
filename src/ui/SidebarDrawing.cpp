#include "iostream"
#include <utility>

#include "ui/SidebarDrawing.h"

using namespace std;

const string pathToIcons = "resource/icons/";
const int pixWidth = 20;
const int pixHeight = 20;

SidebarDrawing::~SidebarDrawing() {
    delete m_selectBtn;
    delete m_frameBtn;
    delete m_rectBtn;
    delete m_circleBtn;
    delete m_lineBtn;
}

SidebarDrawing::SidebarDrawing(BaseObjectType *obj, Glib::RefPtr<Gtk::Builder> builder)
        : Gtk::ButtonBox(obj),
          m_builder(std::move(builder)),
          m_selectBtn(nullptr),
          m_frameBtn(nullptr),
          m_rectBtn(nullptr),
          m_circleBtn(nullptr),
          m_lineBtn(nullptr) {


    m_builder->get_widget("select_btn",m_selectBtn);
    m_builder->get_widget("frame_btn",m_frameBtn);
    m_builder->get_widget("rect_btn",m_rectBtn);
    m_builder->get_widget("circle_btn",m_circleBtn);
    m_builder->get_widget("line_btn",m_lineBtn);

    icon_button_setter(m_selectBtn,"select-icon.svg");
    icon_button_setter(m_frameBtn,"frame-icon.svg");
    icon_button_setter(m_rectBtn,"rectangle-icon.svg");
    icon_button_setter(m_circleBtn,"circle-icon.svg");
    icon_button_setter(m_lineBtn,"line-icon.svg");

}

void SidebarDrawing::icon_button_setter(Gtk::Button *btn, const string& fileName) {
    auto pixHolder = Gdk::Pixbuf::create_from_file(pathToIcons + fileName ,pixWidth,pixHeight, false);
    auto img = Gtk::manage(new Gtk::Image);
    img->set(pixHolder);
    btn->set_image(*img);
}

SidebarDrawing *SidebarDrawing::get_instance(Glib::RefPtr<Gtk::Builder> builder) {
    static SidebarDrawing *sidebarDrawing = nullptr;
    if(sidebarDrawing == nullptr){
        builder->get_widget_derived("sidebar_drawing", sidebarDrawing);
    }
    return sidebarDrawing;
}
