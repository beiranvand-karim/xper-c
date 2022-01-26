QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/drawingShapes/baseshapeitem.cpp \
    src/canvasview.cpp \
    src/drawingShapes/customtextGraphics.cpp \
    src/drawingShapes/ellipseItem.cpp \
    src/drawingShapes/lineitem.cpp \
    src/drawingShapes/polygonitem.cpp \
    src/drawingShapes/rectangleitem.cpp \
    src/drawingShapes/textitem.cpp \
    src/eventfilter/viewzoomhandler.cpp \
    src/main.cpp \
    src/maincanvas.cpp \
    src/mainwindow.cpp


HEADERS += \
    include/canvasview.h \
    include/drawingShapes/customtextgraphics.h \
    include/drawingShapes/drawingstates.h \
    include/drawingShapes/ellipseitem.h \
    include/drawingShapes/lineitem.h \
    include/drawingShapes/polygonitem.h \
    include/drawingShapes/rectangleitem.h \
    include/drawingShapes/textitem.h \
    include/drawingShapes/baseshapeitem.h \
    include/eventfilter/viewzoomhandler.h \
    include/maincanvas.h \
    include/mainwindow.h \
    include/eventfilter/viewzoomhandler.h

FORMS += \
    ui/mainwindow.ui

RESOURCES += \
    resource/res.qrc

INCLUDEPATH +=     $$PWD/include \
                      $$PWD/include/drawingShapes \
                      $$PWD/include/eventfilter

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


