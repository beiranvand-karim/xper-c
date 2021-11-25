#ifndef XPER_CPP_STARTINGBOX_H
#define XPER_CPP_STARTINGBOX_H

#include "gtkmm.h"

using namespace std;

class StartingBox : public Gtk::Box {

public:
    StartingBox();

    virtual ~StartingBox();

    StartingBox(BaseObjectType *obj, const Glib::RefPtr<Gtk::Builder>& builder);
    void set_size(int width, int height);

protected:
    void on_change_image();

private:
    const Glib::RefPtr<Gtk::Builder> m_builder;
    Gtk::Stack *m_stack;
    Gtk::Fixed *m_fixed;
    Gtk::ModelButton *m_prevButton,*m_nextButton;
    Gtk::Image *m_page0,*m_page1,*m_page2,*m_page3;
    Gtk::Image m_prevImg,m_nextImg;
};


#endif //XPER_CPP_STARTINGBOX_H
