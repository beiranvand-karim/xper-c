#include <iostream>
#include "shared/AppContainer.h"

AppContainer::AppContainer(BaseObjectType *obj, Glib::RefPtr<Gtk::Builder> const &builder) :
        Gtk::Box(obj),
        appContainerBuilder{builder},
        isDrawer(true),
        prefixResource("resource/"){


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

        auto editorBuilder = Gtk::Builder::create_from_file("ui/text_editor.glade");
        editorBuilder->get_widget_derived("text_editor",editorContainer);
        appContainerBuilder->get_widget_derived("drawer_container",drawerContainer);

        appContainerBuilder->get_widget("switcher",switcher);
        pix = Gdk::Pixbuf::create_from_file(prefixResource + "text-editor.png",40,40);
        switcherImg.set(pix);
        switcher->set_image(switcherImg);

        switcher->signal_clicked().connect(sigc::mem_fun(*this,&AppContainer::on_switcher_clicked));
    }


}

AppContainer::AppContainer() {}

void AppContainer::on_about_item_activate() {


    try {
        remove(*drawerContainer);
        add(*editorContainer);
        auto pix = Gdk::Pixbuf::create_from_file(prefixResource+"xper.png",200,100);
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

void AppContainer::on_switcher_clicked(){
    isDrawer = !isDrawer;

    if(isDrawer){
        remove(*editorContainer);
        pack_start(*drawerContainer,true,true,0);
        pix = Gdk::Pixbuf::create_from_file(prefixResource+"text-editor.png",40,40);
        switcherImg.set(pix);
        switcher->set_image(switcherImg);
    }
    else{
        remove(*drawerContainer);
        pack_start(*editorContainer,true,true,0);
        pix = Gdk::Pixbuf::create_from_file(prefixResource+"drawer.png",40,40);
        switcherImg.set(pix);
        switcher->set_image(switcherImg);
    }
}