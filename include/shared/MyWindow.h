#ifndef XPER_CPP_MYWINDOW_H
#define XPER_CPP_MYWINDOW_H

#include <gtkmm.h>
#include <gdkmm.h>

#include "EditorContainer.h"

class MyWindow : public Gtk::Window
{

public:
    MyWindow();

protected:

    Gtk::HeaderBar header;
    EditorContainer editorContainer;

};



#endif
