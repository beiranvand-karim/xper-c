#include <gtkmm.h>

#include "shared/EditorContainer.h"

EditorContainer::EditorContainer()
        : graphicBoxLabel("TEXT") {

    // origin box
    pack_start(scrolledWindow, false, true, 20);
    pack_start(configTextContainer, true, true, 0);
    // ***********

    // scrolled window

    scrolledWindow.add(textView);
    scrolledWindow.set_size_request(1380, 800);
    // ***********

    // configuration text box
    cppIcon.set("resource/cpp-icon.png");
    graphicBoxLabel.set_alignment(Gtk::ALIGN_START, Gtk::ALIGN_CENTER);
    configTextContainer.set_margin_top(10);
    configTextContainer.set_orientation(Gtk::ORIENTATION_VERTICAL);
    configTextContainer.pack_start(graphicBoxLabel, false, true, 10);
    configTextContainer.pack_start(graphicBox, false, false, 10);
    configTextContainer.pack_start(textCaseChooserBox, false, false, 10);
    configTextContainer.pack_start(textDirectionSetterBox, false, false, 10);
    configTextContainer.pack_end(cppIcon, true, true, 10);
    // ***********

    // font and color button container
    auto pixBuf = Gdk::Pixbuf::create_from_file("resource/font-chooser.png", 30, 30);
    fontChooserIcon.set(pixBuf);

    pixBuf = Gdk::Pixbuf::create_from_file("resource/color-icon.png", 30, 30);
    colorChooserIcon.set(pixBuf);

    graphicBox.set_margin_top(30);
    graphicBox.pack_start(fontChooserIcon, false, false, 0);
    graphicBox.pack_start(fontChooser, false, false, 0);
    graphicBox.pack_start(colorChooserIcon, false, false, 0);
    graphicBox.pack_start(colorChooser, false, false, 0);
    graphicBox.set_layout(Gtk::BUTTONBOX_START);

    // ***********

    // font and color button signals
    fontChooser.signal_font_set().connect(sigc::mem_fun(*this, &EditorContainer::change_font));
    colorChooser.signal_color_set().connect(sigc::mem_fun(*this, &EditorContainer::change_color));
    // ***********


    // active style for window
    auto context = textView.get_style_context();
    auto provider = Gtk::CssProvider::create();
    context->add_provider(provider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    // ***********


    preTable = textView.get_buffer()->get_tag_table();

    // font styles buttons signals
    upperCase.signal_clicked().connect(sigc::mem_fun(*this, &EditorContainer::set_upper_case));
    lowerCase.signal_clicked().connect(sigc::mem_fun(*this, &EditorContainer::set_lower_case));
    underLine.signal_clicked().connect(sigc::mem_fun(*this, &EditorContainer::set_underline));
    rTL.signal_clicked().connect(sigc::mem_fun(*this, &EditorContainer::set_right_to_left_dir));
    lTR.signal_clicked().connect(sigc::mem_fun(*this, &EditorContainer::set_left_to_right_dir));
    centerDirection.signal_clicked().connect(sigc::mem_fun(*this, &EditorContainer::set_center_dir));
    textHeight.signal_value_changed().connect(sigc::mem_fun(*this, &EditorContainer::set_text_height));
    // ***********

    // font styles button container
    textCaseChooserBox.set_margin_top(50);
    textCaseChooserBox.pack_start(upperCase, false, true, 0);
    textCaseChooserBox.pack_start(lowerCase, false, true, 0);
    textCaseChooserBox.pack_start(underLine, false, true, 0);
    textCaseChooserBox.set_layout(Gtk::BUTTONBOX_START);
    //  textCaseChooserBox.
    textDirectionSetterBox.set_margin_top(50);
    textDirectionSetterBox.pack_start(lTR, false, true, 0);
    textDirectionSetterBox.pack_start(centerDirection, false, true, 0);
    textDirectionSetterBox.pack_start(rTL, false, true, 0);
    textDirectionSetterBox.set_layout(Gtk::BUTTONBOX_START);

    //  configTextContainer.set_margin_top(50);
    configTextContainer.pack_start(textHeight, false, false, 0);
    // ***********

    // manage buttons and set button images
    // uppercase
    pixBuf = Gdk::Pixbuf::create_from_file("resource/uppercase.png", 40, 40);
    upperCaseIcon.set(pixBuf);
    upperCase.set_image(upperCaseIcon);

    // lowercase
    pixBuf = Gdk::Pixbuf::create_from_file("resource/lowercase.png", 40, 40);
    lowerCaseIcon.set(pixBuf);
    lowerCase.set_image(lowerCaseIcon);

    // underline
    pixBuf = Gdk::Pixbuf::create_from_file("resource/underline.png", 30, 30);
    underLineIcon.set(pixBuf);
    underLine.set_image(underLineIcon);

    // left to right direction
    pixBuf = Gdk::Pixbuf::create_from_file("resource/ltr.png", 50, 50);
    lTRIcon.set(pixBuf);
    lTR.set_image(lTRIcon);

    // center direction
    pixBuf = Gdk::Pixbuf::create_from_file("resource/center-align.png", 50, 50);
    centerAlignIcon.set(pixBuf);
    centerDirection.set_image(centerAlignIcon);

    // right to left direction
    pixBuf = Gdk::Pixbuf::create_from_file("resource/rtl.png", 50, 50);
    rTLIcon.set(pixBuf);
    rTL.set_image(rTLIcon);

    // set text height
    pixBuf = Gdk::Pixbuf::create_from_file("resource/text-height.png");
    textHeight.set_icon_from_pixbuf(pixBuf);
    // ****************

    // config RadioButtons
    lTR.set_group(buttonGroup);
    centerDirection.set_group(buttonGroup);
    rTL.set_group(buttonGroup);
    textView.set_justification(Gtk::JUSTIFY_LEFT);
    // *******************

    // manage SpinButton
    auto adjustmentHeight = Gtk::Adjustment::create(0, 0, 60, 1, 10, 0);
    auto adjustmentWidth = Gtk::Adjustment::create(0, 0, 60, 1, 10, 0);

    textHeight.set_adjustment(adjustmentHeight);
    textHeight.set_margin_top(40);
    // ******************************


    auto preTextBuffer = Gtk::TextBuffer::create();
    preTextBuffer->signal_mark_set().connect(sigc::mem_fun(*this, &EditorContainer::set_mark));

    textBuffer = preTextBuffer;

    textView.set_buffer(preTextBuffer);
    preTable = preTextBuffer->get_tag_table();
}

void EditorContainer::set_mark(const Gtk::TextBuffer::iterator &iter, const Glib::RefPtr<Gtk::TextBuffer::Mark> &mark) {

    // get the selected text and save in start and end
    textBuffer->get_selection_bounds(start, end);
}

// direction text functions
void EditorContainer::set_right_to_left_dir() {

    textView.set_justification(Gtk::JUSTIFY_RIGHT);
}

void EditorContainer::set_left_to_right_dir() {

    textView.set_justification(Gtk::JUSTIFY_LEFT);
}

void EditorContainer::set_center_dir() {
    textView.set_justification(Gtk::JUSTIFY_CENTER);
}

// change font when font button is clicked
void EditorContainer::change_font() {

    auto tag = Gtk::TextBuffer::Tag::create();
    tag->property_font() = fontChooser.get_font_name();
    preTable->add(tag);
    textView.set_buffer(textBuffer);
    textBuffer->apply_tag(tag, start, end);
    preTable = textBuffer->get_tag_table();
}

// change color when color button is clicked
void EditorContainer::change_color() {

    auto tag = Gtk::TextBuffer::Tag::create();
    preTable->add(tag);
    textView.set_buffer(textBuffer);
    textBuffer->apply_tag(tag, start, end);
    tag->property_foreground_rgba() = colorChooser.get_rgba();
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
    textView.set_buffer(newBuffer);
}
void  EditorContainer::set_underline() {

    auto tag = Gtk::TextBuffer::Tag::create();
    preTable->add(tag);
    textView.set_buffer(textBuffer);
    textBuffer->apply_tag(tag, start, end);
    tag->property_underline() = Pango::UNDERLINE_SINGLE;
    preTable = textBuffer->get_tag_table();
}
void EditorContainer::set_text_height() {
    textView.set_pixels_below_lines(textHeight.get_value_as_int());
}

