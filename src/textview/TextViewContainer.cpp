#include <glibmm.h>
#include "iostream"

#include "shared/TextViewContainer.h"

using namespace std;

TextViewContainer::TextViewContainer()
: text_label("Text Editor")
{

    set_orientation(Gtk::ORIENTATION_HORIZONTAL);
    set_margin_left(20);

    editor_container.set_orientation(Gtk::ORIENTATION_VERTICAL);

    editor_container.pack_start(text_label,false,false,20);
    editor_container.pack_start(scrolledWindow);

    scrolledWindow.add(textView);

    textView.set_border_width(40);


    textView.set_pixels_below_lines(12);
    buffer = textView.get_buffer();

    settings_container.attach(fontButton, -5, 100, 100, 100);
    fontButton.signal_font_set().connect(sigc::mem_fun(
            *this,
            &TextViewContainer::change_font));
    pack_start(editor_container);
    pack_start(settings_container);

}

void TextViewContainer::change_font() {


    Glib::ustring font = fontButton.get_font_name();
    int index = font.find_first_of(" ", 0);

    Glib::ustring font_family = font.substr(0, index);

    Pango::FontDescription font_desc;
    font_desc.set_family(font_family);

    string arr[5];
    int i = 0;
    int counter = 0;

    stringstream ssin(font);
    while (ssin.good() && i < 4) {
        ssin >> arr[i];
        counter++;
        ++i;
    }
    for (i = 1; i < counter - 1; i++) {

        if (arr[i] == "Bold" ) {
            font_desc.set_weight(Pango::WEIGHT_BOLD);
            i++;
        }
        else if (arr[i] == "Italic") {
            font_desc.set_style(Pango::STYLE_ITALIC);
            i++;
        }
        else if (arr[i] == "Oblique" ) {
            font_desc.set_style(Pango::STYLE_OBLIQUE);
            i++;
        }

}
    try {
        int size = stoi(arr[counter - 1]);
        font_desc.set_stretch(Pango::STRETCH_NORMAL);
        font_desc.set_absolute_size(size * Pango::SCALE);
    }
    catch (exception e) {
        cout << "An error occurred" << endl;
    }
        textView.override_font(font_desc);
        textView.set_buffer(buffer);

}