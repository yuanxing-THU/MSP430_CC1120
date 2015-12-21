#-------------------------------------------------
#
# Project created by QtCreator 2015-12-18T10:35:39
#
#-------------------------------------------------

QT       += core gui
QT += serialport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QT_codeTX
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/E:/star_program/QT/5.5/msvc2012/lib/ -lQt5SerialPort
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/E:/star_program/QT/5.5/msvc2012/lib/ -lQt5SerialPortd
else:unix: LIBS += -L$$PWD/E:/star_program/QT/5.5/msvc2012/lib/ -lQt5SerialPort

INCLUDEPATH += $$PWD/E:/star_program/QT/5.5/msvc2012/include
DEPENDPATH += $$PWD/E:/star_program/QT/5.5/msvc2012/include
