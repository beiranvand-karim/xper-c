#ifndef XPER_CPP_EDITORCONTAINER_H
#define XPER_CPP_EDITORCONTAINER_H

#include <gtkmm.h>

class EditorContainer : public Gtk::Box {

public:
    EditorContainer();

    void change_font();

    void change_color();

    void set_upper_case();

    void set_lower_case();

    void set_underline();

    void set_right_to_left_dir();

    void set_left_to_right_dir();

    void set_center_dir();

    void set_text_height();

    // to connect signal to the handler we need this implementation (just for mark_set signal)

    void set_mark(const Gtk::TextBuffer::iterator& iter,const Glib::RefPtr<Gtk::TextBuffer::Mark>& mark);

protected:
    Gtk::ScrolledWindow scrolledWindow;
    Gtk::TextView textView;
    Glib::RefPtr<Gtk::TextTagTable> preTable;

    Gtk::Box configTextContainer;

    Gtk::FontButton fontChooser;
    Gtk::ColorButton colorChooser;

    Gtk::ButtonBox graphicBox, textCaseChooserBox, textDirectionSetterBox;

    Gtk::RadioButtonGroup buttonGroup;
    Gtk::ModelButton upperCase, lowerCase , underLine;
    Gtk::RadioButton rTL, lTR, centerDirection;
    Gtk::SpinButton textHeight;

    Gtk::TextBuffer::iterator start, end;
    Gtk::Image fontChooserIcon,
            colorChooserIcon,
            upperCaseIcon,
            lowerCaseIcon,
            underLineIcon,
            rTLIcon,
            lTRIcon,
            centerAlignIcon,
            cppIcon;

    Gtk::Label graphicBoxLabel;
    Glib::RefPtr<Gtk::TextBuffer> textBuffer;

};


#endif //XPER_CPP_EDITORCONTAINER_H
