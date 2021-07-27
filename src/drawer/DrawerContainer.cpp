#include "shared/DrawerContainer.h"

DrawerContainer::DrawerContainer(BaseObjectType *obj, Glib::RefPtr<Gtk::Builder> const &builder)
        : Gtk::Box(obj),
          drawerContainerBuilder{builder} {

    if(drawerContainerBuilder){
        drawerContainerBuilder->get_widget_derived("draw_options",drawOptions);
        drawerContainerBuilder->get_widget_derived("drawing_area",drawer);
    }

}