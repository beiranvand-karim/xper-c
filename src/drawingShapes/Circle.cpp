#include "drawingShapesLib/Circle.h"
#include "namespaces/drawshapes.h"

Circle::Circle(int id,
               double start_x,
               double start_y,
               double r,
               double lineWidth,
               const Gdk::RGBA &color,
               bool fill) : r(r), fill(fill) {

    this->id = id;
    this->start_x = start_x;
    this->start_y = start_y;
    this->lineWidth = lineWidth;
    this->color = color;
}

void Circle::draw(const Cairo::RefPtr<Cairo::Context> &p_context) {
    Draw_Circle(p_context,
              start_x,
              start_y,
              r,
              color,
              lineWidth,
              fill);
}

Circle::~Circle() {}

Circle::Circle() {}
