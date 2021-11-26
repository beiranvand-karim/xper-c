#include "drawingShapesLib/Rectangle.h"
#include "namespaces/drawshapes.h"

Rectangle::Rectangle(int id, double start_x, double start_y, double end_x, double end_y, double lineWidth,
                     const Gdk::RGBA &color, bool fill) : width(width),height(height),fill(fill) {
    this->id = id;
    this->start_x = start_x;
    this->start_y = start_y;
    this->lineWidth = lineWidth;
    this->color = color;

}

void Rectangle::draw(const Cairo::RefPtr<Cairo::Context> &p_context) {
    Draw_Rectangle(p_context,
                start_x,
                start_y,
                width,
                height,
                color,
                lineWidth,
                fill);
}

Rectangle::Rectangle() {}

Rectangle::~Rectangle() {}


