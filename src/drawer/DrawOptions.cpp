#include <iostream>
#include "shared/DrawOptions.h"

DrawOptions::DrawOptions(BaseObjectType *obj, Glib::RefPtr<Gtk::Builder> const &builder)
        : Gtk::ButtonBox(obj),
          optionsBuilder{builder},
          prefixResource("resource/") {

    if (optionsBuilder) {
        optionsBuilder->get_widget_derived("drawing_area", drawer);
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
            drawer->draw_shape_config(colorButton->get_rgba(), 5, "square");
        });

        optionsBuilder->get_widget("circle_item", circleItem);
        pix = Gdk::Pixbuf::create_from_file(prefixResource + "circle-icon.png", 30, 30);
        circleImg.set(pix);
        circleItem->set_image(circleImg);
        circleItem->signal_clicked().connect([&] {
            drawer->draw_shape_config(colorButton->get_rgba(), 5, "circle");
        });

        optionsBuilder->get_widget("line_item", lineItem);
        pix = Gdk::Pixbuf::create_from_file(prefixResource + "line-icon.png", 30, 30);
        lineImg.set(pix);
        lineItem->set_image(lineImg);
        lineItem->signal_clicked().connect([&] {
            drawer->draw_shape_config(colorButton->get_rgba(), 5, "line");
        });

        optionsBuilder->get_widget("text_item", textItem);
        pix = Gdk::Pixbuf::create_from_file(prefixResource + "text-editor.png", 30, 30);
        textImg.set(pix);
        textItem->set_image(textImg);
        textItem->signal_clicked().connect([&] {
            drawer->draw_text_config(colorButton->get_rgba(), "Sans", "draw_text");
        });

        optionsBuilder->get_widget("eraser_item", eraserItem);
        pix = Gdk::Pixbuf::create_from_file(prefixResource + "eraser-icon.png", 30, 30);
        eraserImg.set(pix);
        eraserItem->set_image(eraserImg);
        eraserItem->signal_clicked().connect([&] {
            drawer->clear_drawingArea();
        });

        optionsBuilder->get_widget("fill_shape", fillShape);
        pix = Gdk::Pixbuf::create_from_file(prefixResource + "fill-icon.png", 30, 30);
        fillShapeImg.set(pix);
        fillShape->set_image(fillShapeImg);
        fillShape->signal_clicked().connect([&] {
            drawer->set_fill();
        });

        optionsBuilder->get_widget("font_chooser", fontButton);
        fontButton->signal_font_set().connect([&] {
            drawer->set_font_description(fontButton->get_font_name());
        });

        optionsBuilder->get_widget("line_width", widthButton);
        auto adjustment = Gtk::Adjustment::create(1, 1, 100, 1, 1, 1);
        widthButton->set_adjustment(adjustment);
        widthButton->signal_value_changed().connect([&]() {
            drawer->set_line_width(widthButton->get_value_as_int());
        });
    }
}

DrawOptions::~DrawOptions() {}

DrawOptions::DrawOptions() {}
