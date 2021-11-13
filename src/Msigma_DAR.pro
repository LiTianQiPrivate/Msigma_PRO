QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES  -=
# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DESTDIR = $$PWD/../Bin

SOURCES += \
    Business.cpp \
    XYZWidget.cpp \
    main.cpp \
    MainWindow.cpp \
    MsigmaBase.cpp \
    paintarea.cpp

HEADERS += \
    Business.h \
    MainWindow.h \
    XYZWidget.h \
    MsigmaBase.h \
    paintarea.h

FORMS += \
    MainWindow.ui \
    XYZWidget.ui


CONFIG += debug_and_release
CONFIG(debug, debug|release) {
    LIBS += ../VTK9.0.1/Debug/lib/*.lib
    INCLUDEPATH += ../VTK9.0.1/Debug/include
    INCLUDEPATH += ../VTK9.0.1/Debug/include/vtk-9.0/
} else {
    LIBS += ../VTK9.0.1/Release/lib/*.lib
    INCLUDEPATH += ../VTK9.0.1/Release/include
    INCLUDEPATH += ../VTK9.0.1/Release/include/vtk-9.0/
}
include($$PWD/MainForms/MainForms.pri)
INCLUDEPATH += $$PWD//MainForms
include($$PWD/Object/Object.pri)
INCLUDEPATH += $$PWD//Object
include($$PWD/QWT/qwt.pri)
INCLUDEPATH += $$PWD/QWT
include($$PWD/VTK/vtk.pri)
INCLUDEPATH += $$PWD/VTK
include($$PWD/Geometry/Geometry.pri)
INCLUDEPATH += $$PWD/Geometry
include($$PWD/QCHART/qchart.pri)
INCLUDEPATH += $$PWD/QCHART
include($$PWD/qcustomplot/qcustomplot.pri)
INCLUDEPATH += $$PWD/QCHART

#qwt
CONFIG += qwt
DEFINES += QT_DLL QWT_DLL
LIBS += -L"C:\Qt\Qt5.14.1\5.14.1\msvc2017_64\lib" -lqwt
INCLUDEPATH += C:\Qt\Qt5.14.1\5.14.1\msvc2017_64\include\QWT

RESOURCES += \
    QSS/SetQssStyle.qrc


