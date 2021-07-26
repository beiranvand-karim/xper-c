#ifndef XPER_CPP_EDITORCONTAINER_H
#define XPER_CPP_EDITORCONTAINER_H

#include <gtkmm.h>

class EditorContainer : public Gtk::Box {

public:
    EditorContainer(BaseObjectType *obj,Glib::RefPtr<Gtk::Builder> const &builder);

    void change_font();

    void change_color();

    void set_upper_case();

    void set_lower_case();

    void set_underline();

    void set_right_to_left_dir();

    void set_left_to_right_dir();

    void set_center_dir();

    void set_text_width(double lw);

    // to connect signal to the handler we need this implementation (just for mark_set signal)

    void set_mark(const Gtk::TextBuffer::iterator& iter,const Glib::RefPtr<Gtk::TextBuffer::Mark>& mark);

protected:
    Glib::RefPtr<Gtk::Builder> editorBuilder;
    Gtk::TextView *textView;
    std::string prefixResource;

    Glib::RefPtr<Gtk::TextTagTable> preTable;

    Gtk::FontButton *fontChooser;
    Gtk::ColorButton *colorChooser;


    Gtk::ModelButton *upperCase, *lowerCase , *underLine,*rTL, *lTR, *centerDirection;;
    Gtk::ScaleButton *textWidth;

    Gtk::TextBuffer::iterator start, end;
    Gtk::Image *fontChooserImg,
            *colorChooserImg,
            upperCaseIcon,
            lowerCaseIcon,
            underLineIcon,
            rTLIcon,
            lTRIcon,
            centerAlignIcon,
            textWidthIcon,
            *cppImg;

    Glib::RefPtr<Gtk::TextBuffer> textBuffer;

};


#endif //XPER_CPP_EDITORCONTAINER_H
