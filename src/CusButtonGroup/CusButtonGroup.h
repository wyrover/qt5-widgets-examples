#pragma once

#include <QWidget>
#include <QColor>
#include <QVariant>

class QPushButton;
class QButtonGroup;
class QPropertyAnimation;
class CusButtonGroup: public QWidget
{
    Q_OBJECT
public:
    enum Direction {
        North = 0
        , South
        , West
        , East
    };
    CusButtonGroup(QWidget* parent = 0);
    virtual ~CusButtonGroup();
    void setLineHeight(int lineHeight);
    void setButtonPosition(int position);
    void setButtonColor(QColor color);
    void addButton(QPushButton* btn, int id);
protected:
    virtual void paintEvent(QPaintEvent *event);
private:
    void deleteLayout();
private slots:
    void onbuttonClicked(int index);
    void onvalueChanged(QVariant variant);
private:
    QButtonGroup*   m_btnGroup;
    QPropertyAnimation* m_animation;
    QSize               m_btnSize;
    QList<QPushButton*> m_buttonLst;
    int             m_btnPosition;
    int             m_curIndex;
    int             m_preIndex;
    int             m_offset;
    int             m_lineHeight;
    QColor          m_lineColor;
};
