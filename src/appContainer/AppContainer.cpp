#include <iostream>
#include "shared/AppContainer.h"

AppContainer::AppContainer(BaseObjectType *obj, Glib::RefPtr<Gtk::Builder> const &builder) :
        Gtk::Box(obj),
        appContainerBuilder{builder} {


    if (appContainerBuilder) {
        auto quit_item = Glib::RefPtr<Gtk::ImageMenuItem>::cast_dynamic(
                appContainerBuilder->get_object("quit")
        );
        quit_item->signal_activate().connect([&]() {
            Gtk::Main::quit();
        });
        auto about_item = Glib::RefPtr<Gtk::ImageMenuItem>::cast_dynamic(
                appContainerBuilder->get_object("about")
        );
        about_item->signal_activate().connect(sigc::mem_fun(*this,&AppContainer::on_about_item_activate));

    }
    if(appContainerBuilder){
        appContainerBuilder->get_widget_derived("draw_options",drawOptions);
        appContainerBuilder->get_widget_derived("drawing_area",drawer);
    }

}

AppContainer::AppContainer() {}

void AppContainer::on_about_item_activate() {
    try {

        auto pix = Gdk::Pixbuf::create_from_file("resource/xper.png",200,100);
        dialogBuilder = Gtk::Builder::create_from_file("ui/about_dialog.glade");
        dialogBuilder->get_widget("about_dialog",dialog);

        dialog->signal_hide().connect([&](){
            dialog->close();
        });


       if(dialog){
           dialog->set_logo(pix);
           dialogBuilder->get_widget("button_dialog",buttonDialog);

           if(buttonDialog){
               buttonDialog->signal_clicked().connect([&](){
                   dialog->close();
                   dialog->hide();
               });
           }
           dialog->run();
       }
    }
    catch (GBookmarkFileError e) {
    std::cout<< "err"<<std::endl;
    }
}