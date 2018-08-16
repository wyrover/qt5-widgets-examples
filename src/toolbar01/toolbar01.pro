#-------------------------------------------------
#
# Project created by QtCreator 2018-08-16T16:32:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = toolbar01
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainform.cpp

HEADERS  += mainform.h

FORMS    += mainform.ui


RESOURCES += \
    ./res/droidx.qrc



CONFIG(release, debug|release) {
    

    win32:LIBS += $(QTDIR)\lib\Qt5PlatformSupport.lib \
        $(QTDIR)\lib\Qt5Svg.lib \        
        $(QTDIR)\lib\qtpng.lib \
        $(QTDIR)\lib\qtpcre.lib \       
        $(QTDIR)\lib\qtfreetype.lib \
        $(QTDIR)\lib\qtharfbuzzng.lib \
        $(QTDIR)\plugins\platforms\qwindows.lib \
        $(QTDIR)\plugins\imageformats\qsvg.lib \
        $(QTDIR)\plugins\imageformats\qico.lib \
        $(QTDIR)\plugins\iconengines\qsvgicon.lib \       
        Imm32.lib \
        Winmm.lib \
        Ws2_32.lib 
} else {
    win32:LIBS += $(QTDIR)\lib\Qt5PlatformSupportd.lib \
        $(QTDIR)\lib\Qt5Svgd.lib \        
        $(QTDIR)\lib\qtpngd.lib \
        $(QTDIR)\lib\qtpcred.lib \       
        $(QTDIR)\lib\qtfreetyped.lib \
        $(QTDIR)\lib\qtharfbuzzngd.lib \
        $(QTDIR)\plugins\platforms\qwindowsd.lib \
        $(QTDIR)\plugins\imageformats\qsvgd.lib \
        $(QTDIR)\plugins\imageformats\qicod.lib \
        $(QTDIR)\plugins\iconengines\qsvgicond.lib \        
        Imm32.lib \
        Winmm.lib \
        Ws2_32.lib
}