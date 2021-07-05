#include <iostream>
#include "shared/DrawerContainer.h"
#include "shared/Drawer.h"

DrawerContainer::DrawerContainer()
        : prefixIcon("resource/"),
          transformLabel("transform"),
          appearanceLabel("appearance"),
          isFill(false) {

    queue_resize();
    set_size_request(1800,1);
    set_orientation(Gtk::ORIENTATION_HORIZONTAL);
    pack_start(buttonBox, false, true, 0);
    pack_start(drawer, true, true, 0);
    pack_end(scrolledWindow, true, true, 0);

    // set margin for containers
    buttonBox.set_margin_top(40);
    drawer.set_margin_top(50);
    drawer.set_margin_right(20);
    scrolledWindow.set_margin_top(40);


    buttonBox.set_size_request(30,1053);
    drawer.set_size_request(1000,1053);
    scrolledWindow.set_size_request(100,1053);

    // button box

    buttonBox.set_orientation(Gtk::ORIENTATION_VERTICAL);
    buttonBox.set_layout(Gtk::BUTTONBOX_START);
    buttonBox.set_spacing(20);

    auto pixBuf = Gdk::Pixbuf::create_from_file(prefixIcon + "square-icon.png", 30, 30);
    squareItemIcon.set(pixBuf);
    squareItem.set_image(squareItemIcon);


    pixBuf = Gdk::Pixbuf::create_from_file(prefixIcon + "circle-icon.png", 30, 30);
    circleItemIcon.set(pixBuf);
    circleItem.set_image(circleItemIcon);


    pixBuf = Gdk::Pixbuf::create_from_file(prefixIcon + "line-icon.png", 30, 30);
    lineItemIcon.set(pixBuf);
    lineItem.set_image(lineItemIcon);


    pixBuf = Gdk::Pixbuf::create_from_file(prefixIcon + "paint.png", 30, 30);
    paintDrawingAreaIcon.set(pixBuf);
    paintDrawingAreaItem.set_image(paintDrawingAreaIcon);

    buttonBox.pack_start(squareItem, false, false, 0);
    buttonBox.pack_start(circleItem, true, true, 0);
    buttonBox.pack_start(lineItem, true, true, 0);
    buttonBox.pack_start(paintDrawingAreaItem, true, true, 0);
    // ********************************

    scrolledWindow.add(configurationDrawing);

    configurationDrawing.set_orientation(Gtk::ORIENTATION_VERTICAL);
    configurationDrawing.set_spacing(20);
    configurationDrawing.set_margin_top(20);

    // transform section

    configurationDrawing.pack_start(transformGrid, false, true, 0);
    transformGrid.set_orientation(Gtk::ORIENTATION_HORIZONTAL);

    transformGrid.attach(transformLabel, 0, 0, 1, 1);
    transformLabel.set_margin_bottom(20);

    pixBuf = Gdk::Pixbuf::create_from_file(prefixIcon + "x-icon.png", 15, 15, true);
    xPointIcon.set(pixBuf);
    auto xAdjustment = Gtk::Adjustment::create(100, 1, 1000, 1, 10, 10);
    xPoint.set_adjustment(xAdjustment);
    transformGrid.attach(xPointIcon, 0, 2, 1, 1);
    transformGrid.attach(xPoint, 1, 2, 1, 1);

    pixBuf = Gdk::Pixbuf::create_from_file(prefixIcon + "w-icon.png", 15, 15, true);
    widthIcon.set(pixBuf);
    auto widthAdjustment = Gtk::Adjustment::create(100, 1, 1000, 1, 10, 10);
    shapeWidth.set_adjustment(widthAdjustment);
    transformGrid.attach(widthIcon, 3, 2, 1, 1);
    transformGrid.attach(shapeWidth, 4, 2, 1, 1);

    pixBuf = Gdk::Pixbuf::create_from_file(prefixIcon + "h-icon.png", 15, 15, true);
    heightIcon.set(pixBuf);
    auto heightAdjustment = Gtk::Adjustment::create(100, 1, 1000, 1, 10, 10);
    shapeHeight.set_adjustment(heightAdjustment);
    transformGrid.attach(heightIcon, 0, 3, 1, 1);
    transformGrid.attach(shapeHeight, 1, 3, 1, 1);


    pixBuf = Gdk::Pixbuf::create_from_file(prefixIcon + "y-icon.png", 15, 15, true);
    yPointIcon.set(pixBuf);
    auto yAdjustment = Gtk::Adjustment::create(100, 1, 1000, 1, 10, 10);
    yPoint.set_adjustment(yAdjustment);
    transformGrid.attach(yPointIcon, 3, 3, 1, 1);
    transformGrid.attach(yPoint, 4, 3, 1, 1);

    // appearance section

    configurationDrawing.pack_start(appearanceGrid, false, false, 0);

    appearanceGrid.set_margin_top(30);

    appearanceGrid.attach(appearanceLabel, 0, 0, 1, 1);
    appearanceGrid.set_row_homogeneous(true);
    appearanceLabel.set_margin_bottom(20);

    pixBuf = Gdk::Pixbuf::create_from_file(prefixIcon + "color-widget.png", 30, 30, true);
    colorChooserIcon.set(pixBuf);
    appearanceGrid.attach(colorChooserIcon, 0, 1, 1, 1);
    appearanceGrid.attach(colorChooser, 1, 1, 1, 1);


    pixBuf = Gdk::Pixbuf::create_from_file(prefixIcon + "line-width.png", 15, 15, true);
    lineWidthIcon.set(pixBuf);
    lineWidthIcon.set_margin_left(50);
    lineWidthIcon.set_margin_right(10);
    auto lineWidthAdj = Gtk::Adjustment::create(2, 1, 1000, 1, 10, 10);
    lineWidth.set_adjustment(lineWidthAdj);
    appearanceGrid.attach(lineWidthIcon, 3, 1, 1, 1);
    appearanceGrid.attach(lineWidth, 4, 1, 1, 1);

    pixBuf = Gdk::Pixbuf::create_from_file(prefixIcon + "fill.png", 30, 30, true);
    fillItemIcon.set(pixBuf);
    fillShapesItem.set_image(fillItemIcon);
    fillShapesItem.set_margin_top(30);
    appearanceGrid.attach(fillShapesItem, 0, 2, 1, 1);

    // signals and signal handlers

    squareItem.signal_clicked().connect([&]() {

        drawer.shape_config(xPoint.get_value_as_int(),
                            yPoint.get_value_as_int(),
                            shapeWidth.get_value_as_int(),
                            shapeHeight.get_value_as_int(),
                            colorChooser.get_rgba(),
                            lineWidth.get_value_as_int(),
                            "square");
    });

    circleItem.signal_clicked().connect([&]() {

        drawer.shape_config(xPoint.get_value_as_int(),
                            yPoint.get_value_as_int(),
                            shapeWidth.get_value_as_int(),
                            shapeHeight.get_value_as_int(),
                            colorChooser.get_rgba(),
                            lineWidth.get_value_as_int(),
                            "circle");
    });

    lineItem.signal_clicked().connect([&]() {

        drawer.shape_config(xPoint.get_value_as_int(),
                            yPoint.get_value_as_int(),
                            shapeWidth.get_value_as_int(),
                            shapeHeight.get_value_as_int(),
                            colorChooser.get_rgba(),
                            lineWidth.get_value_as_int(),
                            "line");
    });

    paintDrawingAreaItem.signal_clicked().connect([&]() {

        drawer.shape_config(xPoint.get_value_as_int(),
                            yPoint.get_value_as_int(),
                            shapeWidth.get_value_as_int(),
                            shapeHeight.get_value_as_int(),
                            colorChooser.get_rgba(),
                            lineWidth.get_value_as_int(),
                            "paint");
    });

    fillShapesItem.signal_clicked().connect([&] {
        isFill = !isFill;
        drawer.set_fill();
    });
    shapeWidth.signal_value_changed().connect([&] {
        drawer.set_width(shapeWidth.get_value_as_int());
    });
    shapeHeight.signal_value_changed().connect([&] {
        drawer.set_height(shapeHeight.get_value_as_int());
    });
    xPoint.signal_value_changed().connect([&] {
        drawer.set_x(xPoint.get_value_as_int());
    });
    yPoint.signal_value_changed().connect([&] {
        drawer.set_y(yPoint.get_value_as_int());
    });
    colorChooser.signal_color_set().connect([&] {
        drawer.set_color(colorChooser.get_rgba());
    });
    lineWidth.signal_value_changed().connect([&] {
        drawer.set_line_width(lineWidth.get_value_as_int());
    });

}
