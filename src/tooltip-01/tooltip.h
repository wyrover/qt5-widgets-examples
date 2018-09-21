#ifndef tooltip_h__
#define tooltip_h__

#include <QWidget>
#include <QLabel>

class ToolTip : public QWidget
{
    Q_OBJECT

public:
    ToolTip(QWidget *parent = 0);
    ~ToolTip();
public:
    void setText(const QString& text);


private:
    QLabel* info_;
};

#endif // tooltip_h__
