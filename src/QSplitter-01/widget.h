#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <Qsplitter>
#include <QTextEdit>
#include <QHBoxLayout>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
private:
    QHBoxLayout *mainLayout;
    QSplitter *splitterMain;
    QSplitter *splitterRight;
    QTextEdit *textUp;
    QTextEdit *textMiddle;
    QTextEdit *textBottom;
};

#endif