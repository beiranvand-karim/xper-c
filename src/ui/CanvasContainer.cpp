#include "iostream"

#include "ui/CanvasContainer.h"

#include <utility>
#include "globals/GlobalValues.h"

using namespace std;

CanvasContainer::~CanvasContainer() {
    delete m_scrolledCanvas;
    delete m_scrolledMenu;
}

CanvasContainer::CanvasContainer(BaseObjectType *obj, Glib::RefPtr<Gtk::Builder> builder)
        : Gtk::Paned(obj),
          m_builder(std::move(builder)),
          m_scrolledCanvas(nullptr),
          m_scrolledMenu(nullptr) {

    m_builder->get_widget("scrolled_canvas", m_scrolledCanvas);
    m_builder->get_widget("scrolled_menu", m_scrolledMenu);
    m_mainCanvas = MainCanvas::get_instance();

    int m_scrolledCanvasWidth = global_default_width / 6 * 5;
    m_scrolledCanvas->set_size_request(m_scrolledCanvasWidth, global_default_height);
    m_scrolledCanvas->add(*m_mainCanvas);

}

CanvasContainer *CanvasContainer::get_instance(Glib::RefPtr<Gtk::Builder> builder) {
    static CanvasContainer *canvasContainer = nullptr;
    if(canvasContainer == nullptr){
        builder->get_widget_derived("canvas_container",canvasContainer);
    }
    return canvasContainer;
}
