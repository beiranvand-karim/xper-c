#include <iostream>
#include "shared/DrawOptions.h"

DrawOptions::DrawOptions(BaseObjectType *obj, Glib::RefPtr<Gtk::Builder> const &builder)
        : Gtk::ButtonBox(obj),
          optionsBuilder{builder},
          prefixResource("resource/") {

    if (optionsBuilder) {

        optionsBuilder->get_widget("move_item", moveItem);
        pix = Gdk::Pixbuf::create_from_file(prefixResource + "move-icon.png", 30, 30);
        moveImg.set(pix);
        moveItem->set_image(moveImg);


        optionsBuilder->get_widget("square_item", squareItem);
        pix = Gdk::Pixbuf::create_from_file(prefixResource + "square-icon.png", 30, 30);
        squareImg.set(pix);
        squareItem->set_image(squareImg);

        optionsBuilder->get_widget("circle_item", circleItem);
        pix = Gdk::Pixbuf::create_from_file(prefixResource + "circle-icon.png", 30, 30);
        circleImg.set(pix);
        circleItem->set_image(circleImg);

        optionsBuilder->get_widget("line_item", lineItem);
        pix = Gdk::Pixbuf::create_from_file(prefixResource + "line-icon.png", 30, 30);
        lineImg.set(pix);
        lineItem->set_image(lineImg);

        optionsBuilder->get_widget("eraser_item", eraserItem);
        pix = Gdk::Pixbuf::create_from_file(prefixResource + "eraser-icon.png", 30, 30);
        eraserImg.set(pix);
        eraserItem->set_image(eraserImg);

    }
}

DrawOptions::~DrawOptions() {}

DrawOptions::DrawOptions() {}
