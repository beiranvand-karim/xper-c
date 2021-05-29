#ifndef XPER_CPP_TEXTVIEWCONTAINER_H
#define XPER_CPP_TEXTVIEWCONTAINER_H

#include <gtkmm.h>
#include <glibmm.h>


class TextViewContainer: public Gtk::Box {

public:
    TextViewContainer();
    void change_font();
protected:

    Gtk::Box editor_container;
    Gtk::Grid settings_container;
    Gtk::TextView textView;
    Gtk::ScrolledWindow scrolledWindow;
    Gtk::Label text_label;
    Glib::RefPtr<Gtk::TextBuffer> buffer;
    Gtk::FontButton fontButton;
};


#endif //XPER_CPP_TEXTVIEWCONTAINER_H
