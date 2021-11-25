#include "iostream"

#include "ui/StartingBox.h"

using namespace std;

const string PREFIX_ICONS_RESOURCE = "resource/icons/";
const string PREFIX_IMAGES_RESOURCE = "resource/images/";
static int pageNumber = 0;

StartingBox::StartingBox(BaseObjectType *obj,
                         Glib::RefPtr<Gtk::Builder> const &builder) :
        Gtk::Box(obj),
        m_builder(builder),
        m_prevButton(nullptr),
        m_nextButton(nullptr),
        m_page0(nullptr),
        m_page1(nullptr),
        m_page2(nullptr),
        m_page3(nullptr),
        m_stack(nullptr),
        m_fixed(nullptr) {

    if (m_builder) {
        m_builder->get_widget("fixed",
                              m_fixed);
        m_builder->get_widget("slider",
                              m_stack);
        m_builder->get_widget("prev_image",
                              m_prevButton);
        m_builder->get_widget("next_image",
                              m_nextButton);

        m_builder->get_widget("page0", m_page0);
        m_builder->get_widget("page1", m_page1);
        m_builder->get_widget("page2", m_page2);
        m_builder->get_widget("page3", m_page3);
    }

    auto prevButtonIcon = Gdk::Pixbuf::create_from_file(PREFIX_ICONS_RESOURCE + "prev.svg",
                                                        50,
                                                        70);
    m_prevImg.set(prevButtonIcon);
    m_prevButton->set_image(m_prevImg);

    auto nextButtonIcon = Gdk::Pixbuf::create_from_file(PREFIX_ICONS_RESOURCE + "next.svg",
                                                        50,
                                                        70);
    m_nextImg.set(nextButtonIcon);
    m_nextButton->set_image(m_nextImg);

    m_prevButton->signal_clicked().connect([&] {
        if(pageNumber > 0) {
            pageNumber--;
            m_stack->set_visible_child("page" + to_string(pageNumber));
            cout << pageNumber << endl;
        }
    });

    m_nextButton->signal_clicked().connect([&] {
        if(pageNumber < 3) {
            pageNumber++;
            m_stack->set_visible_child("page" + to_string(pageNumber));
            cout << pageNumber << endl;
        }
    });



}


void StartingBox::set_size(int width,
                           int height) {
    m_stack->set_size_request(width / 2,
                              height);
    m_fixed->move(*m_stack,
                  width / 4,
                  height / 4);
    m_fixed->move(*m_prevButton,
                  width / 4 - m_prevButton->get_width(),
                  (height / 4) * 3);
    m_fixed->move(*m_nextButton,
                  (width / 4) * 3,
                  (height / 4) * 3);

}

StartingBox::~StartingBox() {
    delete m_fixed;
    delete m_stack;
    delete m_prevButton;
    delete m_nextButton;
    delete m_page0;
    delete m_page1;
    delete m_page2;
    delete m_page3;

}

void StartingBox::on_change_image() {}




