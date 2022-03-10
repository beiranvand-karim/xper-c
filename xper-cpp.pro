QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/canvasstates/selectionhandler.cpp \
    src/canvasstates/zoomhandler.cpp \
    src/drawingShapes/baseitems/baseshapeitem.cpp \
    src/canvasview.cpp \
    src/drawingShapes/ellipseItem.cpp \
    src/drawingShapes/imageitem.cpp \
    src/drawingShapes/lineitem.cpp \
    src/drawingShapes/pencilitem.cpp \
    src/drawingShapes/baseitems/basepoint.cpp \
    src/drawingShapes/penitem/controlpoint.cpp \
    src/drawingShapes/penitem/cubic.cpp \
    src/drawingShapes/penitem/pentool.cpp \
    src/drawingShapes/polygonitem.cpp \
    src/drawingShapes/rectangleitem.cpp \
    src/drawingShapes/textitemwrapper.cpp \
    src/drawingShapes/customtextGraphics.cpp \
    src/main.cpp \
    src/maincanvas.cpp \
    src/mainwindow.cpp


HEADERS += \
    include/canvasstates/selectionhandler.h \
    include/canvasstates/canvasstatesenums.h \
    include/canvasstates/zoomhandler.h \
    include/canvasview.h \
    include/drawingShapes/ellipseitem.h \
    include/drawingShapes/imageitem.h \
    include/drawingShapes/lineitem.h \
    include/drawingShapes/pencilitem.h \
    include/drawingShapes/baseitems/basepoint.h \
    include/drawingShapes/penitem/controlpoint.h \
    include/drawingShapes/penitem/cubic.h \
    include/drawingShapes/penitem/pentool.h \
    include/drawingShapes/polygonitem.h \
    include/drawingShapes/rectangleitem.h \
    include/drawingShapes/baseitems/baseshapeitem.h \
    include/drawingShapes/textitemwrapper.h \
    include/drawingShapes/customtextgraphics.h \
    include/maincanvas.h \
    include/mainwindow.h

FORMS += \
    ui/mainwindow.ui

RESOURCES += \
    resource/res.qrc

INCLUDEPATH +=     $$PWD/include \
                      $$PWD/include/drawingShapes \
                      $$PWD/include/canvasstates \
                      $$PWD/include/drawingShapes/penitem \
                      $$PWD/include/drawingShapes/baseitems \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


