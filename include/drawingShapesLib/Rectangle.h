#ifndef XPER_CPP_RECTANGLE_H
#define XPER_CPP_RECTANGLE_H

#include <gdkmm/rgba.h>

#include "Shape.h"

class Rectangle : public Shape {

private:
    double width;
    double height;
    bool fill;

public:
    Rectangle(int id,
              double start_x,
              double start_y,
              double width,
              double height,
              double lineWidth,
              const Gdk::RGBA &color,
              bool fill);
    void draw(const Cairo::RefPtr<Cairo::Context> &p_context) override;
    Rectangle();
    virtual ~Rectangle();
};


#endif //XPER_CPP_RECTANGLE_H
