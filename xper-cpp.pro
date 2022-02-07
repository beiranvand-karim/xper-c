QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/canvasstates/moveitemhandler.cpp \
    src/drawingShapes/baseshapeitem.cpp \
    src/canvasview.cpp \
    src/drawingShapes/ellipseItem.cpp \
    src/drawingShapes/imageitem.cpp \
    src/drawingShapes/lineitem.cpp \
    src/drawingShapes/pencilitem.cpp \
    src/drawingShapes/penitem.cpp \
    src/drawingShapes/polygonitem.cpp \
    src/drawingShapes/rectangleitem.cpp \
    src/canvasstates/viewzoomhandler.cpp \
    src/drawingShapes/textitemwrapper.cpp \
    src/drawingShapes/customtextGraphics.cpp \
    src/main.cpp \
    src/maincanvas.cpp \
    src/mainwindow.cpp


HEADERS += \
    include/canvasstates/moveitemhandler.h \
    include/canvasview.h \
    include/drawingShapes/ellipseitem.h \
    include/drawingShapes/imageitem.h \
    include/drawingShapes/lineitem.h \
    include/drawingShapes/pencilitem.h \
    include/drawingShapes/penitem.h \
    include/drawingShapes/polygonitem.h \
    include/drawingShapes/rectangleitem.h \
    include/drawingShapes/baseshapeitem.h \
    include/canvasstates/viewzoomhandler.h \
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
                      $$PWD/include/canvasstates

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


