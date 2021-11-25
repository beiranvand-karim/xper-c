#ifndef XPER_CPP_SQUARE_H
#define XPER_CPP_SQUARE_H

#include "Shape.h"

class Square : public Shape {

private:
    double width;
    bool fill;

public:
    Square(int id,
           double start_x,
           double start_y,
           double width,
           double lineWidth,
           const Gdk::RGBA &color,
           bool fill);
    void draw(const Cairo::RefPtr<Cairo::Context> &p_context) override;
    virtual ~Square();
    Square();
};


#endif //XPER_CPP_SQUARE_H
