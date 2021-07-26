#include <gtkmm.h>

#include "shared/EditorContainer.h"

EditorContainer::EditorContainer(BaseObjectType *obj, Glib::RefPtr<Gtk::Builder> const &builder)
        : Gtk::Box(obj),
          editorBuilder{builder},
          prefixResource("resource/"){

    editorBuilder->get_widget("text_view",textView);

    // ***********

    // configuration text box
    editorBuilder->get_widget("cpp_img",cppImg);
    cppImg->set(prefixResource + "cpp-icon.png");


    // font and color button container
    editorBuilder->get_widget("font_img",fontChooserImg);
    auto pixBuf = Gdk::Pixbuf::create_from_file(prefixResource +"font-chooser.png", 30, 30);
    fontChooserImg->set(pixBuf);

    editorBuilder->get_widget("color_img", colorChooserImg);
    pixBuf = Gdk::Pixbuf::create_from_file(prefixResource + "color-button-icon.png", 30, 30);
    colorChooserImg->set(pixBuf);

    // ***********

    // font and color button signals
    editorBuilder->get_widget("font_button",fontChooser);
    fontChooser->signal_font_set().connect(sigc::mem_fun(*this, &EditorContainer::change_font));

    editorBuilder->get_widget("color_button",colorChooser);
    colorChooser->signal_color_set().connect(sigc::mem_fun(*this, &EditorContainer::change_color));
    // ***********


    // active style for window
    auto context = textView->get_style_context();
    auto provider = Gtk::CssProvider::create();
    context->add_provider(provider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    // ***********


    preTable = textView->get_buffer()->get_tag_table();

    // font styles buttons signals
    editorBuilder->get_widget("uppercase",upperCase);
    upperCase->signal_clicked().connect(sigc::mem_fun(*this, &EditorContainer::set_upper_case));

    editorBuilder->get_widget("lowercase",lowerCase);
    lowerCase->signal_clicked().connect(sigc::mem_fun(*this, &EditorContainer::set_lower_case));

    editorBuilder->get_widget("underline",underLine);
    underLine->signal_clicked().connect(sigc::mem_fun(*this, &EditorContainer::set_underline));

    editorBuilder->get_widget("rtl",rTL);
    rTL->signal_clicked().connect(sigc::mem_fun(*this, &EditorContainer::set_right_to_left_dir));

    editorBuilder->get_widget("ltr",lTR);
    lTR->signal_clicked().connect(sigc::mem_fun(*this, &EditorContainer::set_left_to_right_dir));

    editorBuilder->get_widget("center_align",centerDirection);
    centerDirection->signal_clicked().connect(sigc::mem_fun(*this, &EditorContainer::set_center_dir));

    editorBuilder->get_widget("text_width",textWidth);
    textWidth->signal_value_changed().connect(sigc::mem_fun(*this, &EditorContainer::set_text_width));
    // ***********

    // uppercase
    pixBuf = Gdk::Pixbuf::create_from_file(prefixResource + "uppercase.png", 40, 40);
    upperCaseIcon.set(pixBuf);
    upperCase->set_image(upperCaseIcon);

    // lowercase
    pixBuf = Gdk::Pixbuf::create_from_file(prefixResource + "lowercase.png", 40, 40);
    lowerCaseIcon.set(pixBuf);
    lowerCase->set_image(lowerCaseIcon);

    // underline
    pixBuf = Gdk::Pixbuf::create_from_file(prefixResource + "underline.png", 40, 40);
    underLineIcon.set(pixBuf);
    underLine->set_image(underLineIcon);

    // left to right direction
    pixBuf = Gdk::Pixbuf::create_from_file(prefixResource + "ltr-icon.png", 50, 50);
    lTRIcon.set(pixBuf);
    lTR->set_image(lTRIcon);

    // center direction
    pixBuf = Gdk::Pixbuf::create_from_file(prefixResource + "center-align-icon.png", 50, 50);
    centerAlignIcon.set(pixBuf);
    centerDirection->set_image(centerAlignIcon);

    // right to left direction
    pixBuf = Gdk::Pixbuf::create_from_file(prefixResource + "rtl-icon.png", 50, 50);
    rTLIcon.set(pixBuf);
    rTL->set_image(rTLIcon);

    // set text height
    pixBuf = Gdk::Pixbuf::create_from_file(prefixResource +"text-width-icon.png",40,40);
    textWidthIcon.set(pixBuf);
    textWidth->set_image(textWidthIcon);
    // ****************

    textView->set_justification(Gtk::JUSTIFY_LEFT);
    // *******************

    // manage scale button
    auto adj = Gtk::Adjustment::create(0, 0, 60, 1, 10, 0);
    textWidth->set_adjustment(adj);
    // ******************************


    auto preTextBuffer = Gtk::TextBuffer::create();
    preTextBuffer->signal_mark_set().connect(sigc::mem_fun(*this, &EditorContainer::set_mark));

    textBuffer = preTextBuffer;

    textView->set_buffer(preTextBuffer);
    preTable = preTextBuffer->get_tag_table();
}

void EditorContainer::set_mark(const Gtk::TextBuffer::iterator &iter, const Glib::RefPtr<Gtk::TextBuffer::Mark> &mark) {

    // get the selected text and save in start and end
    textBuffer->get_selection_bounds(start, end);
}

// direction text functions
void EditorContainer::set_right_to_left_dir() {
    textView->set_justification(Gtk::JUSTIFY_RIGHT);
}

void EditorContainer::set_left_to_right_dir() {
    textView->set_justification(Gtk::JUSTIFY_LEFT);
}

void EditorContainer::set_center_dir() {
    textView->set_justification(Gtk::JUSTIFY_CENTER);
}

// change font when font button is clicked
void EditorContainer::change_font() {

    auto tag = Gtk::TextBuffer::Tag::create();
    tag->property_font() = fontChooser->get_font_name();
    preTable->add(tag);
    textView->set_buffer(textBuffer);
    textBuffer->apply_tag(tag, start, end);
    preTable = textBuffer->get_tag_table();
}

// change color when color button is clicked
void EditorContainer::change_color() {

    auto tag = Gtk::TextBuffer::Tag::create();
    preTable->add(tag);
    textView->set_buffer(textBuffer);
    textBuffer->apply_tag(tag, start, end);
    tag->property_foreground_rgba() = colorChooser->get_rgba();
    preTable = textBuffer->get_tag_table();
}

void EditorContainer::set_upper_case() {

    int startIndex = start.get_offset();
    int endIndex = end.get_offset() - start.get_offset();
    Glib::ustring bufferText = textBuffer->get_text();
    Glib::ustring upperCaseText = textBuffer->get_text(start, end).uppercase();
    bufferText.replace(startIndex, endIndex, upperCaseText);
    textBuffer->set_text(bufferText);

}

void EditorContainer::set_lower_case() {

    int startIndex = start.get_offset();
    int endIndex = end.get_offset() - start.get_offset();
    auto newBuffer = Gtk::TextBuffer::create(preTable);
    Glib::ustring bufferText = textBuffer->get_text();
    Glib::ustring lowerCaseText = textBuffer->get_text(start, end).lowercase();
    bufferText.replace(startIndex, endIndex, lowerCaseText);
    newBuffer->set_text(bufferText);
    textView->set_buffer(newBuffer);
}

void EditorContainer::set_underline() {

    auto tag = Gtk::TextBuffer::Tag::create();
    preTable->add(tag);
    textView->set_buffer(textBuffer);
    textBuffer->apply_tag(tag, start, end);
    tag->property_underline() = Pango::UNDERLINE_SINGLE;
    preTable = textBuffer->get_tag_table();
}

void EditorContainer::set_text_width(double lw) {
    textView->set_pixels_below_lines(textWidth->get_value());
}

