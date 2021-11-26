#ifndef XPER_CPP_CIRCLE_H
#define XPER_CPP_CIRCLE_H

#include "Shape.h"

class Circle : public Shape {

private:
    double r;
    bool fill;

public:
    Circle(int id,
           double start_x,
           double start_y,
           double r,
           double lineWidth,
           const Gdk::RGBA &color,
           bool fill);
    void draw(const Cairo::RefPtr<Cairo::Context> &p_context) override;
    virtual ~Circle();
    Circle();

};


#endif //XPER_CPP_CIRCLE_H
