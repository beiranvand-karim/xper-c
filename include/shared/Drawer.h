#ifndef XPER_CPP_DRAWER_H
#define XPER_CPP_DRAWER_H
#ifndef DRAWING_H
#define DRAWING_H

#include <gtkmm.h>
#include <cairo/cairo.h>

class Drawer : public Gtk::DrawingArea {
public:
    Drawer(BaseObjectType *obj, Glib::RefPtr<Gtk::Builder> const &builder);

    Drawer();

    ~Drawer();

    void set_movable();

    void set_line_width(int lw);

    void set_color(Gdk::RGBA rgba);

    void shape_config(Gdk::RGBA rgba,
                      int lw,
                      const char *shapeName);

    void set_fill();

protected:
    bool draw_shapes(const Cairo::RefPtr<::Cairo::Context> &cr);

    void on_image_chooser_clicked();


private:
    Glib::RefPtr<Gtk::Builder> drawingBuilder;
    Gtk::ImageMenuItem *newItem, *openItem;

    Glib::RefPtr<Gdk::Pixbuf> pix;

    Gdk::RGBA cairoRgba;
    double beginPoint_x, beginPoint_y, endPoint_x, endPoint_y, lineWidth,width,height;
    const char *shape;
    bool isFill;

};

#endif // DRAWING_H
#endif //XPER_CPP_DRAWER_H
