#include "shared/MyHeaderBar.h"

MyHeaderBar::MyHeaderBar()
        : fileItem("_File", true),
          cppDrawer("Drawer") {

    set_show_close_button(true);
    set_title("CPP App");

    // add a menu bar to header bar
    pack_start(menuBar);

    // add items as submenus to menu bar

    menuBar.append(fileItem);

    // add a menu as submenu to file item
    fileItem.set_submenu(fileSubMenu);

    // add items to file menu

    fileSubMenu.prepend(cppDrawer);

}

