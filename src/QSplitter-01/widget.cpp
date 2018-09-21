#if defined (_MSC_VER) && (_MSC_VER >=1600)
#pragma execution_character_set("utf-8")
#endif


#include "widget.h"

    Widget::Widget(QWidget *parent) :
        QWidget(parent)
{
    setWindowTitle(tr("Splitter"));
    splitterMain = new QSplitter(Qt::Horizontal, this);
    QTextEdit *textLeft = new QTextEdit(tr("左邊"), splitterMain);
    textLeft->setAlignment(Qt::AlignCenter);
    splitterRight = new QSplitter(Qt::Vertical, splitterMain);
    textUp = new QTextEdit(tr("右上"), splitterRight);
    textUp->setAlignment(Qt::AlignCenter);
    textMiddle = new QTextEdit(tr("右中"), splitterRight);
    textMiddle->setAlignment(Qt::AlignCenter);
    textBottom = new QTextEdit(tr("右下"), splitterRight);
    textBottom->setAlignment(Qt::AlignCenter);
    splitterMain->setStretchFactor(1, 1);
    mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(splitterMain);
}