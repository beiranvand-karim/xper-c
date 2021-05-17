#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <gdkmm.h>
#include <gtkmm.h>

#include "MyWindow.h"

MyWindow::MyWindow()
{
    set_border_width(10);
    set_default_size(500, 500);
    set_position(Gtk::WIN_POS_CENTER);
    header.set_show_close_button(true);

    button.signal_clicked().connect(sigc::mem_fun(*this,
                                                  &MyWindow::on_button_clicked));
    button.set_label("Open image");
    set_titlebar(header);
    header.pack_start(button);

    add(image);

    show_all_children();
}


void MyWindow::on_button_clicked() {
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
            Glib::ustring fileName = dialog.get_filename();
            image.set(fileName);
        }
        case Gtk::RESPONSE_CANCEL: {
            break;
        }
        default:
            break;
    }
}