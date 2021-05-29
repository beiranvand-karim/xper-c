#include <gdkmm.h>
#include <gtkmm.h>
#include "iostream"
#include "MyWindow.h"

MyWindow::MyWindow() {

    set_border_width(10);
    set_default_size(1800, 1000);
    set_position(Gtk::WIN_POS_CENTER);
    set_events(Gdk::BUTTON1_MOTION_MASK);
    set_titlebar(header);

    open_image_button.set_label("Open image");

    open_image_button.signal_clicked().connect(sigc::mem_fun(
            *this,
            &MyWindow::on_open_image_button_clicked));
    show_side_bar.set_label("menu");

    show_side_bar.signal_clicked().connect(sigc::mem_fun(
            *this,
            &MyWindow::on_show_side_bar_button_clicked));

    header.pack_start(show_side_bar);
    header.pack_start(open_image_button);
    header.set_show_close_button(true);


    scale = 1;

    draw.add_events(Gdk::BUTTON_PRESS_MASK | Gdk::SCROLL_MASK | Gdk::SMOOTH_SCROLL_MASK);
    draw.signal_scroll_event().connect(sigc::mem_fun(
            *this,
            &MyWindow::on_scroll));
    draw.signal_draw().connect(sigc::mem_fun(
            *this,
            &MyWindow::on_draw_cairo));

    add(sidebar);
    show_all();
}


void MyWindow::on_open_image_button_clicked() {

    Gtk::FileChooserDialog dialog("Open image",
                                  Gtk::FILE_CHOOSER_ACTION_OPEN);
    dialog.add_button(Gtk::Stock::OPEN,
                      Gtk::RESPONSE_ACCEPT);
    dialog.add_button(Gtk::Stock::CANCEL,
                      Gtk::RESPONSE_CANCEL);

    Glib::RefPtr<Gtk::FileFilter> filter = Gtk::FileFilter::create();


    filter->add_pixbuf_formats();
    filter->set_name("Images");

    dialog.add_filter(filter);


    switch (dialog.run()) {
        case Gtk::RESPONSE_ACCEPT: {
            fileName = dialog.get_filename();

            try {
                image = Gdk::Pixbuf::create_from_file(fileName);
                remove();
                add(draw);
                draw.show();
            }
            catch (GError error) {
                g_print("file not found");
            }
        }
        case Gtk::RESPONSE_CANCEL: {
            break;
        }
        default:
            break;
    }
}


bool MyWindow::on_scroll(GdkEventScroll *ev) {
    scale -= ev->delta_y / 10.;
    if (scale < 0.1) scale = 0.1;
    queue_draw();

    return true;
}


bool MyWindow::on_draw_cairo(const Cairo::RefPtr<Cairo::Context> &cr) {
    Gtk::Allocation allocation = get_allocation();
    const int width = allocation.get_width();
    const int height = allocation.get_height();
    std::cout<<height<<std::endl;
    cr->scale(scale, scale);

    Gdk::Cairo::set_source_pixbuf(cr,
                                  image,
                                  (width / 2) / scale - image->get_width() / 2,
                                  (height / 2) / scale - image->get_height() / 2);

    cr->rectangle(0,
                  0,
                  get_allocation().get_width() / scale,
                  get_allocation().get_width() / scale);

    cr->fill();

    return true;
}

void MyWindow::on_show_side_bar_button_clicked() {
    remove();
    add(sidebar);
}