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

    void set_movable(Glib::ustring movable);

protected:
    bool draw_shapes(const Cairo::RefPtr<::Cairo::Context> &cr);

    void on_image_chooser_clicked();

private:
    Glib::RefPtr<Gtk::Builder> drawingBuilder;
    Gtk::ImageMenuItem *newItem, *openItem;

    Glib::RefPtr<Gdk::Pixbuf> pix;

    double endPoint_x = 0;
    double endPoint_y = 0;

};

#endif // DRAWING_H
#endif //XPER_CPP_DRAWER_H
