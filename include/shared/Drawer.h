#ifndef XPER_CPP_DRAWER_H
#define XPER_CPP_DRAWER_H
#ifndef DRAWING_H
#define DRAWING_H

#include <gtkmm.h>
#include <cairo/cairo.h>

class Drawer : public Gtk::DrawingArea {
public:
    Drawer();

    ~Drawer();

    void set_width(int w);

    void set_height(int h);

    void set_x(int x);

    void set_y(int y);

    void set_line_width(int lw);

    void set_color(Gdk::RGBA rgba);

    void shape_config(int x,
                      int y,
                      int w,
                      int h,
                      Gdk::RGBA rgba,
                      int lw,
                      const char *shapeName);

    void set_fill();

    // signal draw

    bool draw_shapes(const Cairo::RefPtr<::Cairo::Context> &cr);

private:
    Gdk::RGBA cairoRgba;
    double width, height, beginPoint_x, beginPoint_y, endPoint_x, endPoint_y, lineWidth;
    const char *shape;
    bool isFill;

};

#endif // DRAWING_H
#endif //XPER_CPP_DRAWER_H
