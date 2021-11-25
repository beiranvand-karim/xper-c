#include "drawingShapesLib/Line.h"
#include "namespaces/drawshapes.h"

Line::Line(int id,
           double start_x,
           double start_y,
           double end_x,
           double end_y,
           double lineWidth,
           const Gdk::RGBA &color) : end_x(end_x), end_y(end_y) {
    this->id = id;
    this->start_x = start_x;
    this->start_y = start_y;
    this->lineWidth = lineWidth;
    this->color = color;
}

void Line::draw(const Cairo::RefPtr<Cairo::Context> &p_context) {
    Draw_Line(p_context,
              start_x,
              start_y,
              end_x,
              end_y,
              color,
              lineWidth);
}

Line::Line() {}

Line::~Line() {}

