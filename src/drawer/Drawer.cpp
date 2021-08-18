#include "shared/Drawer.h"

#include <utility>
#include <iostream>

using namespace std;

Drawer::Drawer(BaseObjectType *obj, Glib::RefPtr<Gtk::Builder> builder)
        : Gtk::Layout(obj),
          drawingBuilder{std::move(builder)},
          isFill(false),
          drawingState(""),
          width(20),
          height(20),
          shouldReleaseBtn(false),
          endPoint_x(0),
          endPoint_y(0),
          drawingText(""),
          canDrawText(false),
          fontFamily("Sans 20"),
          shouldSaveText(false) {

    add_events(Gdk::BUTTON1_MOTION_MASK | Gdk::BUTTON_PRESS_MASK | Gdk::BUTTON_RELEASE_MASK | Gdk::KEY_PRESS_MASK);

    if (drawingBuilder) {
        drawingBuilder->get_widget("new", newItem);
        newItem->signal_activate().connect(sigc::mem_fun(*this, &Drawer::on_image_chooser_clicked));
        drawingBuilder->get_widget("open", openItem);
        drawingBuilder->get_widget("window", window);
    }


    signal_button_press_event().connect([&](GdkEventButton *e) {
        this->beginPoint_x = e->x;
        this->beginPoint_y = e->y;
        shouldReleaseBtn = false;
        shouldSaveText = false;
        square_signal_connection = this->signal_draw().connect(sigc::mem_fun(*this, &Drawer::draw_square));
        circle_signal_connection = this->signal_draw().connect(sigc::mem_fun(*this, &Drawer::draw_circle));
        line_signal_connection = this->signal_draw().connect(sigc::mem_fun(*this, &Drawer::draw_line));
        this->signal_draw().connect(sigc::mem_fun(*this, &Drawer::draw_image));
        this->signal_draw().connect(sigc::mem_fun(*this, &Drawer::draw_text));

        return true;
    });

    signal_motion_notify_event().connect([&](GdkEventMotion *e) {
        this->endPoint_x = e->x;
        this->endPoint_y = e->y;
        width = endPoint_x - beginPoint_x;
        height = endPoint_y - beginPoint_y;
        shouldReleaseBtn = false;

        if (drawingState != "draw_text") {
            queue_draw();
        }

        return true;
    });

    signal_button_release_event().connect([&](GdkEventButton *e) {
        shouldReleaseBtn = true;
        shouldSaveText = false;

        if (drawingState == "draw_text") {
            canDrawText = true;
            drawingText = "";
            queue_draw();
        } else {
            drawingText = "";
            queue_draw();
        }
        return true;
    });

    text_signal_connection = window->signal_key_press_event().connect([&](GdkEventKey *k) {
        if (canDrawText) {
            drawingText.append(k->string);
            if (k->keyval == 65507) {
                square_signal_connection.disconnect();
                circle_signal_connection.disconnect();
                line_signal_connection.disconnect();

                shouldSaveText = true;
                return false;
            }
            queue_draw();
            return false;
        }
        return false;
    });

    window->signal_key_release_event().connect([&](GdkEventKey *k) {
        if (canDrawText) {
            if (shouldSaveText) {
                if (k->keyval == 65507) {
                    queue_draw();
                }
            }
        }
        return false;
    });

    layout = Pango::Layout::create(create_pango_context());
    layout->set_text("");
}


Drawer::~Drawer() = default;

Drawer::Drawer() = default;

void Drawer::draw_shape_config(Gdk::RGBA rgba,
                               int lw,
                               const char *shapeName) {
    this->drawingState = shapeName;
    this->cairoRgba = std::move(rgba);
    this->lineWidth = lw;
}

void Drawer::draw_text_config(Gdk::RGBA rgba,
                              string fontFamily,
                              const char *shapeName) {

    this->drawingState = shapeName;
    this->cairoRgba = std::move(rgba);
    this->fontFamily = std::move(fontFamily);
}

// draw signal handlers ***********************************************************

bool Drawer::draw_image(const Cairo::RefPtr<::Cairo::Context> &cr) {
    if (pix) {
        if (drawingState == "move") {
            Gdk::Cairo::set_source_pixbuf(cr, pix, endPoint_x, endPoint_y);
            cr->paint();
            cr->move_to(endPoint_x, endPoint_y);

            return false;
        }
        Gdk::Cairo::set_source_pixbuf(cr, pix, 0, 0);
        cr->paint();
        return false;
    }

    return false;
}

bool Drawer::draw_square(const Cairo::RefPtr<::Cairo::Context> &cr1) {

    if (drawingState == "square") {
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

        if (shouldReleaseBtn) {
            pix = Gdk::Pixbuf::create(cr->get_target(), 0, 0, 500, 500);
            Gdk::Cairo::set_source_pixbuf(cr, pix, 0, 0);
            cr->paint();
        }
        return true;
    }
    return false;
}

bool Drawer::draw_circle(const Cairo::RefPtr<::Cairo::Context> &cr1) {

    if (drawingState == "circle") {
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
        if (shouldReleaseBtn) {
            pix = Gdk::Pixbuf::create(cr->get_target(), 0, 0, 500, 500);
            Gdk::Cairo::set_source_pixbuf(cr, pix, 0, 0);
            cr->paint();
        }

        return true;
    }
    return false;
}


bool Drawer::draw_line(const Cairo::RefPtr<::Cairo::Context> &cr1) {

    if (drawingState == "line") {
        auto cr = get_window()->create_cairo_context();
        cr->save();
        cr->set_line_width(lineWidth);
        cr->set_source_rgb(cairoRgba.get_red(), cairoRgba.get_green(), cairoRgba.get_blue());
        cr->line_to(beginPoint_x, beginPoint_y);
        cr->line_to(endPoint_x, endPoint_y);
        cr->stroke();

        if (shouldReleaseBtn) {
            pix = Gdk::Pixbuf::create(cr->get_target(), 0, 0, 500, 500);
            Gdk::Cairo::set_source_pixbuf(cr, pix, 0, 0);
            cr->paint();
        }

        return true;
    }
    return false;
}

bool Drawer::draw_text(const Cairo::RefPtr<::Cairo::Context> &cr1) {

    if (drawingState == "draw_text") {
        auto cr = get_window()->create_cairo_context();
        cr->save();
        cr->move_to(500, 500);
        cr->set_source_rgb(204, 0, 0);
        cr->set_font_size(20);
        cr->show_text("please press ctrl button then right click to save your text");
        cr->restore();

        Pango::FontDescription font{fontFamily};
        layout->set_text(drawingText);
        layout->set_font_description(font);
        cr->save();
        cr->move_to(endPoint_x, endPoint_y);
        cr->set_font_size(lineWidth);
        cr->set_source_rgb(cairoRgba.get_red(), cairoRgba.get_green(), cairoRgba.get_blue());
        layout->show_in_cairo_context(cr);
        cr->restore();

        if (shouldSaveText) {
            cout << "saved ****************************" << endl;

            pix = Gdk::Pixbuf::create(cr->get_target(), 0, 0, 500, 500);
            Gdk::Cairo::set_source_pixbuf(cr, pix, 0, 0);
            cr->paint();
        }
        return true;
    }
    return false;
}


// draw options and configurations *************************************************************
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
            drawingState = "move";
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
    drawingState = "move";
    queue_draw();
}

void Drawer::set_font_description(Glib::ustring fontName) {
    this->fontFamily = fontName;
    queue_draw();
}

void Drawer::clear_drawingArea() {
    if (firstPix) {
        pix = firstPix;
        drawingState = "";
        queue_draw();
    }
}



