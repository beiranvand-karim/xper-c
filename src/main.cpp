#include <ui/MainWindow.h>
#include <gtkmm/cssprovider.h>

int main(int argc, char *argv[]) {

    auto app = Gtk::Application::create(argc, argv, "xper.com");
    auto builder = Gtk::Builder::create_from_file("glade/ui/window.glade");

    auto window = MainWindow::get_instance(builder);

    auto css = Gtk::CssProvider::create();
    css->load_from_path("style/app-styles.css");
    window->get_style_context()->add_provider_for_screen(Gdk::Screen::get_default(), css,
                                                           GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    app->signal_window_removed().connect([&](Gtk::Window *w) {
        delete window;
    });

    return app->run(*window);

}