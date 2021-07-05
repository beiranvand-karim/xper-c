#ifndef XPER_CPP_DRAWERCONTAINER_H
#define XPER_CPP_DRAWERCONTAINER_H

#include <gtkmm/box.h>
#include "Drawer.h"

class DrawerContainer : public Gtk::Box {

public:
    DrawerContainer();

private:
    Drawer drawer;
    Glib::ustring prefixIcon;

    Gtk::ButtonBox buttonBox;

    Gtk::ModelButton squareItem,
            circleItem,
            lineItem,
            paintDrawingAreaItem,
            fillShapesItem;

    Gtk::Image squareItemIcon,
            circleItemIcon,
            lineItemIcon,
            paintDrawingAreaIcon,
            widthIcon,
            heightIcon,
            xPointIcon,
            yPointIcon,
            lineWidthIcon,
            colorChooserIcon,
            fillItemIcon;

    Gtk::ScrolledWindow scrolledWindow;
    Gtk::Box configurationDrawing;
    Gtk::Grid transformGrid, appearanceGrid;
    Gtk::Label transformLabel, appearanceLabel;
    Gtk::SpinButton shapeWidth, shapeHeight, xPoint, yPoint, lineWidth;
    Gtk::ColorButton colorChooser;

    bool isFill;
};

#endif //XPER_CPP_DRAWERCONTAINER_H
