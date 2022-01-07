QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/canvasview.cpp \
    src/drawingShapes/rectangleitem.cpp \
    src/main.cpp \
    src/maincanvas.cpp \
    src/mainwindow.cpp


HEADERS += \
    include/canvasview.h \
    include/drawingShapes/baseitem.h \
    include/drawingShapes/drawingstates.h \
    include/drawingShapes/rectangleitem.h \
    include/maincanvas.h \
    include/mainwindow.h

FORMS += \
    ui/mainwindow.ui

RESOURCES += \
    resource/res.qrc

INCLUDEPATH += /home/mohamadp91/Documents/xper-cpp/include/ \
                  /home/mohamadp91/Documents/xper-cpp/include/drawingShapes/

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


