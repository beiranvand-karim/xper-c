#include "iostream"
#include "drawingItems/RectItem.h"

using namespace std;

RectItem::RectItem() {
    this->property_fill_color() = "blue";
    this->property_stroke_color() = "white";

}

RectItem::~RectItem() {}

Glib::RefPtr<RectItem> RectItem::create() {
    return Glib::RefPtr<RectItem>(new RectItem());
}

bool RectItem::on_enter_notify_event(const Glib::RefPtr<Item> &target, GdkEventCrossing *event) {
    this->property_stroke_color() = "green";
    return Item::on_enter_notify_event(target, event);
}

bool RectItem::on_leave_notify_event(const Glib::RefPtr<Item> &target, GdkEventCrossing *event) {
    this->property_stroke_color() = "white";
    return Item::on_leave_notify_event(target, event);
}


bool RectItem::on_button_press_event(const Glib::RefPtr<Item> &target, GdkEventButton *event) {
    return Item::on_button_press_event(target, event);
}

void RectItem::simple_create_path_vfunc(const Cairo::RefPtr<Cairo::Context> &cr) {
    cr->rectangle(300, 300, 300, 300);
    ItemSimple::simple_create_path_vfunc(cr);
}

