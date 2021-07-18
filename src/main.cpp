#include <gtkmm.h>
#include <shared/MyWindow.h>

int main(int argc, char *argv[]) {

    auto app = Gtk::Application::create(argc, argv, "xper.com");
    auto builder = Gtk::Builder::create_from_file("ui/window.glade");

    MyWindow *myWindow = nullptr;

    builder->get_widget_derived("window", myWindow);

    auto css = Gtk::CssProvider::create();
    css->load_from_path("style/window.css");
    myWindow->get_style_context()->add_provider_for_screen(Gdk::Screen::get_default(),css,GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    return app->run(*myWindow);

}