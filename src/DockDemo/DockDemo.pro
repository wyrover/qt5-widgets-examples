#-------------------------------------------------
#
# Project created by QtCreator 2014-12-16T06:16:16
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = DockDemo
TEMPLATE = app
CONFIG  += c++11
INCLUDEPATH += $$PWD

SOURCES += main.cpp\
        main_window.cpp \
    info_widget.cpp \
    utils.cpp \
    config/config_manager.cpp \
    config/config_manager_dialog.cpp \
    dock/dock_host.cpp \
    theme/stylesheet_builder.cpp \
    demo_widget.cpp \
    about_dialog.cpp \
    theme/theme.cpp

HEADERS  += main_window.h \
    info_widget.h \
    utils.h \
    config/config_manager.h \
    config/config_manager_dialog.h \
    dock/dock_host.h \
    theme/stylesheet_builder.h \
    demo_widget.h \
    about_dialog.h \
    theme/theme.h

FORMS    += main_window.ui \
    info_widget.ui \
    config/config_manager_dialog.ui \
    demo_widget.ui \
    about_dialog.ui
