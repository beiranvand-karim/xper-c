#ifndef XPER_CPP_DRAWSHAPES_H
#define XPER_CPP_DRAWSHAPES_H

#include "gtkmm.h"

namespace {
    void Draw_Line(const Cairo::RefPtr<Cairo::Context> &p_context,
                   double start_x,
                   double start_y,
                   double end_x,
                   double end_y,
                   Gdk::RGBA color,
                   double lineWidth) {
        p_context->save();
        p_context->set_source_rgba(color.get_red(), color.get_green(), color.get_blue(), color.get_alpha());
        p_context->set_line_width(lineWidth);
        p_context->move_to(start_x, start_y);
        p_context->line_to(end_x, end_y);
        p_context->stroke();
        p_context->restore();
    };


    void Draw_Circle(const Cairo::RefPtr<Cairo::Context> &p_context,
                     double start_x,
                     double start_y,
                     double r,
                     Gdk::RGBA color,
                     double lineWidth,
                     bool fill) {
        p_context->save();
        p_context->set_source_rgba(color.get_red(), color.get_green(), color.get_blue(), color.get_alpha());
        p_context->set_line_width(lineWidth);
        p_context->arc(start_x, start_y, r, 0, 2 * M_PI);
        if (fill) {
            p_context->fill();
        } else {
            p_context->stroke();
        }
        p_context->restore();
    };

    void Draw_Square(const Cairo::RefPtr<Cairo::Context> &p_context,
                     double start_x,
                     double start_y,
                     double width,
                     Gdk::RGBA color,
                     double lineWidth,
                     bool fill) {
        p_context->save();
        p_context->set_source_rgba(color.get_red(), color.get_green(), color.get_blue(), color.get_alpha());
        p_context->set_line_width(lineWidth);
        p_context->rectangle(start_x, start_y, width, width);
        if (fill) {
            p_context->fill();
        } else {
            p_context->stroke();
        }
        p_context->restore();
    };


    void Draw_Rectangle(const Cairo::RefPtr<Cairo::Context> &p_context,
                        double start_x,
                        double start_y,
                        double width,
                        double height,
                        Gdk::RGBA color,
                        double lineWidth,
                        bool fill) {
        p_context->save();
        p_context->set_source_rgba(color.get_red(), color.get_green(), color.get_blue(), color.get_alpha());
        p_context->set_line_width(lineWidth);
        p_context->rectangle(start_x, start_y, width, height);
        if (fill) {
            p_context->fill();
        } else {
            p_context->stroke();
        }
        p_context->restore();
    };
}
#endif //XPER_CPP_DRAWSHAPES_H
