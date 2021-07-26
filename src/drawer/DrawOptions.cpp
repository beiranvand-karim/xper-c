#include <iostream>
#include "shared/DrawOptions.h"

DrawOptions::DrawOptions(BaseObjectType *obj, Glib::RefPtr<Gtk::Builder> const &builder)
        : Gtk::ButtonBox(obj),
          optionsBuilder{builder},
          prefixResource("resource/") {

    if (optionsBuilder) {
        optionsBuilder->get_widget_derived("drawing_area",drawer);
        optionsBuilder->get_widget("color_button", colorButton);
        colorButton->signal_color_set().connect([&] {
            drawer->set_color(colorButton->get_rgba());
        });

        optionsBuilder->get_widget("move_item", moveItem);
        pix = Gdk::Pixbuf::create_from_file(prefixResource + "move-icon.png", 30, 30);
        moveImg.set(pix);
        moveItem->set_image(moveImg);
        moveItem->signal_clicked().connect([&] {
            drawer->set_movable();
        });

        optionsBuilder->get_widget("square_item", squareItem);
        pix = Gdk::Pixbuf::create_from_file(prefixResource + "square-icon.png", 30, 30);
        squareImg.set(pix);
        squareItem->set_image(squareImg);
        squareItem->signal_clicked().connect([&] {
            drawer->shape_config(colorButton->get_rgba(), 5, "square");
        });

        optionsBuilder->get_widget("circle_item", circleItem);
        pix = Gdk::Pixbuf::create_from_file(prefixResource + "circle-icon.png", 30, 30);
        circleImg.set(pix);
        circleItem->set_image(circleImg);
        circleItem->signal_clicked().connect([&] {
            drawer->shape_config(colorButton->get_rgba(), 5, "circle");
        });

        optionsBuilder->get_widget("line_item", lineItem);
        pix = Gdk::Pixbuf::create_from_file(prefixResource + "line-icon.png", 30, 30);
        lineImg.set(pix);
        lineItem->set_image(lineImg);
        lineItem->signal_clicked().connect([&] {
            drawer->shape_config(colorButton->get_rgba(), 5, "line");
        });


        optionsBuilder->get_widget("fill_shape", fillShape);
        pix = Gdk::Pixbuf::create_from_file(prefixResource + "fill-icon.png", 30, 30);
        fillShapeImg.set(pix);
        fillShape->set_image(fillShapeImg);
        fillShape->signal_clicked().connect([&] {
            drawer->set_fill();
        });

        optionsBuilder->get_widget("line_width", widthButton);
        pix = Gdk::Pixbuf::create_from_file(prefixResource + "line-width-icon.png", 30, 30);
        lineWidthImg.set(pix);
        widthButton->set_image(lineWidthImg);
        auto adjustment = Gtk::Adjustment::create(10, 10, 100, 1, 10, 10);
        widthButton->set_adjustment(adjustment);
        widthButton->signal_value_changed().connect([&](double value) {
            drawer->set_line_width(value);
        });
    }
}

DrawOptions::~DrawOptions() {}

DrawOptions::DrawOptions() {}
