#ifndef XPER_CPP_DRAWOPTIONS_H
#define XPER_CPP_DRAWOPTIONS_H

#include <gtkmm.h>

#include "Drawer.h"

class DrawOptions : public Gtk::ButtonBox {

public:
    DrawOptions(BaseObjectType *obj, Glib::RefPtr<Gtk::Builder> const &builder);

    DrawOptions();

    virtual ~DrawOptions();

private:
    Drawer* drawer = nullptr;
    Glib::RefPtr<Gtk::Builder> optionsBuilder;

    Gtk::ModelButton
            *moveItem,
            *squareItem,
            *circleItem,
            *lineItem,
            *fillShape;

    Glib::RefPtr<Gdk::Pixbuf> pix;
    Gtk::Image moveImg,
            squareImg,
            circleImg,
            lineImg,
            fillShapeImg,
            lineWidthImg;

    Gtk::ScaleButton *widthButton;
    Gtk::ColorButton *colorButton;
    std::string prefixResource;
};

#endif //XPER_CPP_DRAWOPTIONS_H
