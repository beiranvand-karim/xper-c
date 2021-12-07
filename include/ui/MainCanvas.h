#ifndef XPER_CPP_MAINCANVAS_H
#define XPER_CPP_MAINCANVAS_H

#include <goocanvasmm/canvas.h>

class MainCanvas : public Goocanvas::Canvas {

public:
    ~MainCanvas();
    static std::shared_ptr<MainCanvas> get_instance();
    void operator=(MainCanvas const &) = delete;
    MainCanvas(MainCanvas const &) = delete;

protected:
    MainCanvas();

};


#endif //XPER_CPP_MAINCANVAS_H
