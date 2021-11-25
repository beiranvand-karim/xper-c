#ifndef XPER_CPP_SHAPE_H
#define XPER_CPP_SHAPE_H

#include <cairomm/refptr.h>
#include <cairomm/context.h>
#include <gdkmm/rgba.h>

class Shape {

protected:
    int id;
    double start_x;
    double start_y;
    Gdk::RGBA color;
    double lineWidth;
    virtual void draw(const Cairo::RefPtr <Cairo::Context> &p_context) = 0;

public:
    virtual ~Shape() = default;
};

#endif //XPER_CPP_SHAPE_H
