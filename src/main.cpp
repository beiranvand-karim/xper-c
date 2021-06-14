#include <gtkmm.h>
#include <glibmm.h>

#include "shared/MyWindow.h"

int main (int argc, char *argv[])
{
    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "www.lucidarme.me");

    MyWindow window;

    window.show_all();

    return app->run(window);


}
