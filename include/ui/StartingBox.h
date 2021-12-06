#ifndef XPER_CPP_STARTINGBOX_H
#define XPER_CPP_STARTINGBOX_H

#include <gtkmm/button.h>
#include <gtkmm/entry.h>
#include "gtkmm/box.h"
#include "gtkmm/builder.h"

using namespace std;

class StartingBox : public Gtk::Box {

public:
    virtual ~StartingBox();
    StartingBox(BaseObjectType *obj, const Glib::RefPtr<Gtk::Builder>& builder);
    static StartingBox *get_instance(Glib::RefPtr<Gtk::Builder> ptr);

    StartingBox(StartingBox const&) = delete;
    void operator=(StartingBox const&) = delete;
private:
    StartingBox();
    const Glib::RefPtr<Gtk::Builder> m_builder;
    Gtk::Button *m_newProjectBtn;
    Gtk::Entry *m_nameInput;
};


#endif //XPER_CPP_STARTINGBOX_H
