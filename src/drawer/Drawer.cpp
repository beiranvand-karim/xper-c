#include "shared/Drawer.h"

#include <utility>
#include <iostream>

Drawer::Drawer(BaseObjectType *obj, Glib::RefPtr<Gtk::Builder> const &builder)
        : Gtk::Layout(obj),
          drawingBuilder{builder},
          isFill(false),
          shape(nullptr),
          width(20),
          height(20),
          isReleaseBtn(false) {

    add_events(Gdk::BUTTON1_MOTION_MASK | Gdk::BUTTON_PRESS_MASK | Gdk::BUTTON_RELEASE_MASK);

    if (drawingBuilder) {
        drawingBuilder->get_widget("new", newItem);
        newItem->signal_activate().connect(sigc::mem_fun(*this, &Drawer::on_image_chooser_clicked));

        drawingBuilder->get_widget("open", openItem);
    }

    signal_button_press_event().connect([&](GdkEventButton *e) {
        this->beginPoint_x = e->x;
        this->beginPoint_y = e->y;
        isReleaseBtn = false;

        return true;
    });

    signal_motion_notify_event().connect([&](GdkEventMotion *e) {
        this->endPoint_x = e->x;
        this->endPoint_y = e->y;
        width = endPoint_x - beginPoint_x;
        height = endPoint_y - beginPoint_y;

        isReleaseBtn = false;
        if (strcmp(shape, "square") == 0) {
            connection_square = this->signal_draw().connect(sigc::mem_fun(*this, &Drawer::draw_square));
            queue_draw();
        } else if (strcmp(shape, "circle") == 0) {
            connection_circle = this->signal_draw().connect(sigc::mem_fun(*this, &Drawer::draw_circle));
            queue_draw();
        } else if (strcmp(shape, "line") == 0) {
            connection_line = this->signal_draw().connect(sigc::mem_fun(*this, &Drawer::draw_line));
            queue_draw();
        }
        return true;
    });

    signal_button_release_event().connect([&](GdkEventButton *e) {
        isReleaseBtn = true;
        if (strcmp(shape, "square") == 0) {
            connection_circle.disconnect();
            connection_line.disconnect();
            connection_square = this->signal_draw().connect(sigc::mem_fun(*this, &Drawer::draw_square));
            queue_draw();
        }
        if (strcmp(shape, "circle") == 0) {
            connection_line.disconnect();
            connection_square.disconnect();
            connection_circle = this->signal_draw().connect(sigc::mem_fun(*this, &Drawer::draw_circle));
            queue_draw();
        }
        if (strcmp(shape, "line") == 0) {
            connection_square.disconnect();
            connection_circle.disconnect();
            connection_line = this->signal_draw().connect(sigc::mem_fun(*this, &Drawer::draw_line));
            queue_draw();
        }
        return true;
    });
}


Drawer::~Drawer() = default;

Drawer::Drawer() {}

void Drawer::shape_config(Gdk::RGBA rgba,
                          int lw,
                          const char *shapeName) {
    this->shape = shapeName;
    this->cairoRgba = std::move(rgba);
    this->lineWidth = lw;

}

bool Drawer::draw_image(const Cairo::RefPtr<::Cairo::Context> &cr) {
    if (pix) {
        Gdk::Cairo::set_source_pixbuf(cr, pix, 0, 0);
        cr->paint();
    }

    return false;
}

bool Drawer::draw_square(const Cairo::RefPtr<::Cairo::Context> &cr1) {

    if (strcmp(shape, "square") == 0) {
        connection_circle.disconnect();
        connection_line.disconnect();

        auto cr = get_window()->create_cairo_context();
        cr->save();
        cr->set_line_width(10);
        cr->set_source_rgb(cairoRgba.get_red(), cairoRgba.get_green(), cairoRgba.get_blue());
        cr->rectangle(beginPoint_x, beginPoint_y, width, height);

        if (isFill == 1) {
            cr->fill();
            cr->restore();
        } else {
            cr->stroke();
            cr->restore();
        }

        if (isReleaseBtn) {
            pix = Gdk::Pixbuf::create(cr->get_target(), 0, 0, 500, 500);
            Gdk::Cairo::set_source_pixbuf(cr, pix, 0, 0);
            cr->paint();
        }
        return false;
    } else {
        return false;
    }
}

bool Drawer::draw_circle(const Cairo::RefPtr<::Cairo::Context> &cr1) {

    if (strcmp(shape, "circle") == 0) {
        connection_line.disconnect();
        connection_square.disconnect();

        auto cr = get_window()->create_cairo_context();
        cr->save();
        cr->set_line_width(lineWidth);
        cr->set_source_rgb(cairoRgba.get_red(), cairoRgba.get_green(), cairoRgba.get_blue());
        cr->arc(beginPoint_x, beginPoint_y, endPoint_x - beginPoint_x, 1, 8);

        if (isFill == 1) {
            cr->fill();
            cr->restore();
        } else {
            cr->stroke();
            cr->restore();
        }
        if (isReleaseBtn) {
            pix = Gdk::Pixbuf::create(cr->get_target(), 0, 0, 500, 500);
            Gdk::Cairo::set_source_pixbuf(cr, pix, 0, 0);
            cr->paint();
        }

        return false;
    } else {
        return false;
    }
}


bool Drawer::draw_line(const Cairo::RefPtr<::Cairo::Context> &cr1) {
    if (strcmp(shape, "line") == 0) {
        connection_square.disconnect();
        connection_circle.disconnect();

        auto cr = get_window()->create_cairo_context();
        cr->save();
        cr->set_line_width(lineWidth);
        cr->set_source_rgb(cairoRgba.get_red(), cairoRgba.get_green(), cairoRgba.get_blue());
        cr->line_to(beginPoint_x, beginPoint_y);
        cr->line_to(endPoint_x, endPoint_y);
        cr->stroke();

        if (isReleaseBtn) {
            pix = Gdk::Pixbuf::create(cr->get_target(), 0, 0, 500, 500);
            Gdk::Cairo::set_source_pixbuf(cr, pix, 0, 0);
            cr->paint();
        }

        return false;
    } else {
        return false;
    }
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
            firstPix = Gdk::Pixbuf::create_from_file(dialog.get_filename(), 500, 500);
            this->signal_draw().connect(sigc::mem_fun(*this, &Drawer::draw_image));
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

void Drawer::clear_drawingArea() {
    if (firstPix) {
        pix = firstPix;
        shape = "";
        queue_draw();
    }
}
