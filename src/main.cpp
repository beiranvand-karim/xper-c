#include <gtk/gtk.h>
#include <gtkmm/application.h>
#include <glib/glist.h>
#include "MyWindow.h"


int main (int argc, char *argv[])
{
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

    MyWindow window;

    //Shows the window and returns when it is closed.
    return app->run(window);
}
