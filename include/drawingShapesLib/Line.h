#ifndef XPER_CPP_LINE_H
#define XPER_CPP_LINE_H

#include "Shape.h"

class Line : public Shape {

private:
    double end_x;
    double end_y;

public:
    Line(int id,
         double start_x,
         double start_y,
         double end_x,
         double end_y,
         double lineWidth,
         const Gdk::RGBA &color);
    void draw(const Cairo::RefPtr<Cairo::Context> &p_context) override;
    Line();
    virtual ~Line();

};


#endif //XPER_CPP_LINE_H
