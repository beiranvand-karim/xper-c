#include "shared/Drawer.h"

#include <utility>
#include <iostream>

Drawer::Drawer(BaseObjectType *obj, Glib::RefPtr<Gtk::Builder> const &builder)
        : Gtk::DrawingArea(obj),
          drawingBuilder{builder} {
    add_events(Gdk::BUTTON1_MOTION_MASK | Gdk::BUTTON_PRESS_MASK);

    if (drawingBuilder) {
        drawingBuilder->get_widget("new", newItem);
        newItem->signal_activate().connect(sigc::mem_fun(*this, &Drawer::on_image_chooser_clicked));

        drawingBuilder->get_widget("open", openItem);

    }

    signal_motion_notify_event().connect([&](GdkEventMotion *e) {
        if (pix) {
            this->endPoint_x = e->x;
            this->endPoint_y = e->y;
            this->signal_draw().connect(sigc::mem_fun(*this, &Drawer::draw_shapes));
            queue_draw();
            return true;
        }
    });
}


Drawer::~Drawer() = default;

Drawer::Drawer() {}

bool Drawer::draw_shapes(const Cairo::RefPtr<::Cairo::Context> &cr) {

    cr->save();
    Gdk::Cairo::set_source_pixbuf(cr, pix, endPoint_x, endPoint_y);
    cr->rectangle(0, 0, get_width(), get_height());
    cr->fill();
    cr->restore();

    return true;
}

void Drawer::on_image_chooser_clicked() {
    Gtk::FileChooserDialog dialog("Please choose an image", Gtk::FILE_CHOOSER_ACTION_OPEN);
    dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
    dialog.add_button("_Ok", Gtk::RESPONSE_OK);

    auto imageFilter = Gtk::FileFilter::create();
    imageFilter->set_name("Image files");
    imageFilter->add_mime_type("image/ *");
    imageFilter->add_pattern("*.png");
    imageFilter->add_pattern("*.jpg");
    imageFilter->add_pattern("*.jpeg");
    imageFilter->add_pattern("*.svg");

    dialog.add_filter(imageFilter);

    int result = dialog.run();
    switch (result) {
        case (Gtk::RESPONSE_OK): {
            pix = Gdk::Pixbuf::create_from_file(dialog.get_filename(), 500, 500);
            this->signal_draw().connect(sigc::mem_fun(*this, &Drawer::draw_shapes));
            break;
        }
        default: {
            break;
        }
    }
}