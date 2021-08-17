#ifndef XPER_CPP_DRAWOPTIONS_H
#define XPER_CPP_DRAWOPTIONS_H

#include <gtkmm.h>

#include "Drawer.h"

using namespace std;

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
            *eraserItem,
            *fillShape,
            *textItem;

    Glib::RefPtr<Gdk::Pixbuf> pix;
    Gtk::Image moveImg,
            squareImg,
            circleImg,
            lineImg,
            eraserImg,
            fillShapeImg,
            textImg;

    Gtk::SpinButton *widthButton;
    Gtk::ColorButton *colorButton;
    string prefixResource;

    Gtk::FontButton *fontButton;
};

#endif //XPER_CPP_DRAWOPTIONS_H
