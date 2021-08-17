#ifndef XPER_CPP_DRAWER_H
#define XPER_CPP_DRAWER_H
#ifndef DRAWING_H
#define DRAWING_H

#include <gtkmm.h>
#include <cairo/cairo.h>

using namespace std;

class Drawer : public Gtk::Layout {
public:
    Drawer(BaseObjectType *obj, Glib::RefPtr<Gtk::Builder> builder);

    Drawer();

    ~Drawer();

    void set_movable();

    void set_line_width(int lw);

    void set_color(Gdk::RGBA rgba);

    void draw_shape_config(Gdk::RGBA rgba,
                           int lw,
                           const char *shapeName);

    void draw_text_config(Gdk::RGBA rgba,
                          string fontFamily,
                          const char *shapeName);

    void set_fill();

    void set_font_description(Glib::ustring fontName);

    void clear_drawingArea();

protected:
    bool draw_image(const Cairo::RefPtr<::Cairo::Context> &cr);

    bool draw_square(const Cairo::RefPtr<::Cairo::Context> &cr);

    bool draw_circle(const Cairo::RefPtr<::Cairo::Context> &cr);

    bool draw_line(const Cairo::RefPtr<::Cairo::Context> &cr);

    bool draw_text(const Cairo::RefPtr<::Cairo::Context> &cr);

    void on_image_chooser_clicked();


private:
    Glib::RefPtr<Gtk::Builder> drawingBuilder;
    Gtk::ImageMenuItem *newItem, *openItem;

    Glib::RefPtr<Gdk::Pixbuf> pix, firstPix;

    Gdk::RGBA cairoRgba;

    double beginPoint_x,
            beginPoint_y,
            endPoint_x,
            endPoint_y,
            lineWidth,
            width,
            height;

    bool isFill,
         canDrawText,
         shouldReleaseBtn,
         shouldSaveText;

    sigc::connection square_signal_connection,
            circle_signal_connection,
            line_signal_connection,
            textArea_signal_connection,
            text_signal_connection;


    Gtk::ApplicationWindow *window;


    string drawingState,
            drawingText,
            fontFamily;

    Glib::RefPtr<Pango::Layout> layout;

};

#endif // DRAWING_H
#endif //XPER_CPP_DRAWER_H
