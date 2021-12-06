#include <goocanvasmm/rect.h>
#include <drawingItems/RectItem.h>
#include "goocanvasmm.h"
#include "iostream"

#include "ui/MainCanvas.h"

using namespace std;

MainCanvas::~MainCanvas() {
}

MainCanvas::MainCanvas() {
    this->set_bounds(0, 0, 1000, 1000);
    set_window(this->get_window());
    add_events(Gdk::KEY_PRESS_MASK | Gdk::KEY_RELEASE_MASK);
    auto pix = Gdk::Pixbuf::create_from_file("resource/icons/xper.png",500,500);
    auto rect = RectItem::create();
    get_root_item()->add_child(rect);
    this->show_all();
}

shared_ptr<MainCanvas> MainCanvas::get_instance() {
    static shared_ptr<MainCanvas> canvas{new MainCanvas()};
    return canvas;
}



