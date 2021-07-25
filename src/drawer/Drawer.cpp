#include "shared/Drawer.h"

#include <utility>
#include <iostream>

Drawer::Drawer(BaseObjectType *obj, Glib::RefPtr<Gtk::Builder> const &builder)
        : Gtk::DrawingArea(obj),
          drawingBuilder{builder},
          isFill(false),
          shape(nullptr),
          width(20),
          height(20) {


    add_events(Gdk::BUTTON1_MOTION_MASK | Gdk::BUTTON_PRESS_MASK);

    if (drawingBuilder) {
        drawingBuilder->get_widget("new", newItem);
        newItem->signal_activate().connect(sigc::mem_fun(*this, &Drawer::on_image_chooser_clicked));

        drawingBuilder->get_widget("open", openItem);
    }

    signal_button_press_event().connect([&](GdkEventButton *e) {
        this->beginPoint_x = e->x;
        this->beginPoint_y = e->y;
        this->signal_draw().connect(sigc::mem_fun(*this, &Drawer::draw_shapes));
        return true;
    });

    signal_motion_notify_event().connect([&](GdkEventMotion *e) {
        this->endPoint_x = e->x;
        this->endPoint_y = e->y;
        width = endPoint_x - beginPoint_x;
        height = endPoint_y - beginPoint_y;
        this->signal_draw().connect(sigc::mem_fun(*this, &Drawer::draw_shapes));
        queue_draw();
        return true;
    });
    this->signal_draw().connect(sigc::mem_fun(*this, &Drawer::draw_shapes));
}


Drawer::~Drawer() = default;

Drawer::Drawer() {}

void Drawer::shape_config(Gdk::RGBA rgba,
                          int lw,
                          const char *shapeName) {
    this->shape = shapeName;
    this->cairoRgba = std::move(rgba);
    this->lineWidth = lw;
    queue_draw();

}

bool Drawer::draw_shapes(const Cairo::RefPtr<::Cairo::Context> &cr) {

    if (pix && strcmp(shape, "move") == 0) {
        cr->save();
        Gdk::Cairo::set_source_pixbuf(cr, pix, endPoint_x, endPoint_y);
        cr->rectangle(0, 0, get_width(), get_height());
        cr->fill();
        cr->restore();
        return true;
    }


    if (shape) {
        cr->set_line_width(lineWidth);
        cr->set_source_rgb(cairoRgba.get_red(), cairoRgba.get_green(), cairoRgba.get_blue());

        if (strcmp(shape, "square") == 0) {
            cr->rectangle(beginPoint_x, beginPoint_y, width, height);

        } else if (strcmp(shape, "circle") == 0) {
            cr->arc(beginPoint_x, beginPoint_y, endPoint_x - beginPoint_x, 1, 8);

        } else if (strcmp(shape, "line") == 0) {

            cr->line_to(beginPoint_x, beginPoint_y);
            cr->line_to(endPoint_x, endPoint_y);

        }
        else if(strcmp(shape,"move") == 0){
            cr->move_to(endPoint_x,endPoint_y);
            cr->rel_move_to(endPoint_x,endPoint_y);

        }
    }
    if (isFill == 1) {
        cr->fill();
    } else {
        cr->stroke();
    }
    show_all();

    return true;
}

void Drawer::on_image_chooser_clicked() {

    shape = "move";

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
            queue_draw();
            break;
        }
        default: {
            break;
        }
    }
}


void Drawer::set_color(Gdk::RGBA rgba) {
    this->cairoRgba = std::move(rgba);
    queue_draw();
}

void Drawer::set_line_width(int lw) {
    this->lineWidth = lw;
    queue_draw();
}

void Drawer::set_fill() {
    this->isFill = !this->isFill;
    queue_draw();
}

void Drawer::set_movable() {
    shape = "move";
    queue_draw();
}

