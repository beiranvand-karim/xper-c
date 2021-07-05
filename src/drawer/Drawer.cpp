#include "shared/Drawer.h"

#include <utility>

Drawer::Drawer()
        : isFill(false),
          shape(nullptr) {

    queue_resize();

    add_events(Gdk::BUTTON1_MOTION_MASK | Gdk::BUTTON_PRESS_MASK);

    signal_button_press_event().connect([&](GdkEventButton *e) {
        if (shape != nullptr) {
            this->beginPoint_x = e->x;
            this->beginPoint_y = e->y;
            this->signal_draw().connect(sigc::mem_fun(*this, &Drawer::draw_shapes));
            queue_draw();
            return true;
        }
        return false;
    });

    signal_motion_notify_event().connect([&](GdkEventMotion *e) {
        this->endPoint_x = e->x;
        this->endPoint_y = e->y;
        width = endPoint_x - beginPoint_x;
        height = endPoint_y - beginPoint_y;
        queue_draw();
        return true;
    });

}


void Drawer::shape_config(int x,
                          int y,
                          int w,
                          int h,
                          Gdk::RGBA rgba,
                          int lw,
                          const char *shapeName) {
    this->shape = shapeName;
    this->width = w;
    this->height = h;
    this->beginPoint_x = x;
    this->beginPoint_y = y;
    this->cairoRgba = std::move(rgba);
    this->lineWidth = lw;
}

Drawer::~Drawer() = default;

void Drawer::set_width(int w) {
    this->width = w;
    queue_draw();
}

void Drawer::set_height(int h) {
    this->height = h;
    queue_draw();
}

void Drawer::set_x(int x) {
    this->beginPoint_x = x;
    queue_draw();
}

void Drawer::set_y(int y) {
    this->beginPoint_y = y;
    queue_draw();
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

bool Drawer::draw_shapes(const Cairo::RefPtr<::Cairo::Context> &cr) {

    cr->save();

    cr->set_line_width(lineWidth);
    cr->set_source_rgb(cairoRgba.get_red(), cairoRgba.get_green(), cairoRgba.get_blue());



    if (strcmp(shape, "square") == 0) {

        cr->rectangle(beginPoint_x, beginPoint_y, width, height);

    } else if (strcmp(shape, "circle") == 0) {

        cr->arc(beginPoint_x, beginPoint_y, width, 1, 8);

    } else if (strcmp(shape, "line") == 0) {

        cr->line_to(beginPoint_x, beginPoint_y);
        cr->line_to(endPoint_x, endPoint_y);

    } else if (strcmp(shape, "paint") == 0) {
        cr->paint();
    }

    if (isFill == 1) {
        cr->fill();
    } else {
        cr->stroke();
    }
    show_all();
    cr->restore();
    return true;
}


