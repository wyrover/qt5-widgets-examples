#-------------------------------------------------
#
# Project created by QtCreator 2017-08-21T15:17:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TreeWidget
TEMPLATE = app



HEADERS  += mainwindow.h\
		UiTableWidgetItem.h\
		DataTableWidgetEditorDelegate.h\
		CustomTreeWidget.h\
		UiTableWidgetItemSecond.h

SOURCES += main.cpp\
        mainwindow.cpp\
		UiTableWidgetItem.cpp\
		DataTableWidgetEditorDelegate.cpp\
		CustomTreeWidget.cpp\
		UiTableWidgetItemSecond.cpp

FORMS    += mainwindow.ui\
		TableWidgetItem.ui\
		TableWidgetItemSecond.ui

RESOURCES += rc.qrc
