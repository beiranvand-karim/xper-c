#include "drawingShapesLib/Square.h"
#include "namespaces/drawshapes.h"

Square::Square(int id, double start_x, double start_y, double width, double lineWidth,
               const Gdk::RGBA &color, bool fill) : width(width), fill(fill) {
    this->id = id;
    this->start_x = start_x;
    this->start_y = start_y;
    this->lineWidth = lineWidth;
    this->color = color;
}

void Square::draw(const Cairo::RefPtr<Cairo::Context> &p_context) {
    Draw_Square(p_context,
                start_x,
                start_y,
                width,
                color,
                lineWidth,
                fill);
}

Square::~Square() {}

Square::Square() {

}


