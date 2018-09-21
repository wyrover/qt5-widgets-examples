#pragma once

#include <QWidget>
#include <QMap>
#include <QEvent>

class CustomWidget: public QWidget
{
public:
    CustomWidget(QWidget* parent = 0)
        : QWidget(parent)
    {
        setAttribute(Qt::WA_Hover);
    }
protected:
    bool event(QEvent* event)
    {
        QEvent::Type type = event->type();

        if (event->type() == QEvent::HoverEnter) {
            int i = 0;
            ++i;
        }

        if (type != QEvent::WindowActivate | QEvent::Paint) {
            int i = 0;
            ++i;
        }

        if (type == QEvent::MouseMove) {
            int i = 0;
            ++i;
        }

        return QWidget::event(event);
    }
};
namespace Ui
{
class TableWidgetItemSecond;
}

class UiTableWidgetItemSecond: public QWidget
{
    Q_OBJECT
public:
    UiTableWidgetItemSecond(QWidget * parent, Qt::WindowFlags f = 0);
    ~UiTableWidgetItemSecond();
    void setPropertyValue(QString property, QString value);
    QString getPropertyValue(QString property);
    void setPushButtonVisible(QString pushButtonName, bool flag);
    void setPushButtonChecked(QString pushButtonName, bool flag);
    void setContentWidgetVisible(bool visible);
    bool getContentWidgetVisible();
    void addWidget(QWidget* widget);
    bool containChild();
    void setStyleSheet(QString name, QString qss);
    void setPropertyWidget(QString name, QWidget* widget);
    QWidget* getPropertyWidget(QString name);
signals:
    void itemPushButtonClicked(QWidget* widget, QString name, bool flag);
    void mouseDoubleClicked(QWidget*);
    void mousePressed(QWidget*);
protected:
    virtual bool event(QEvent* event);
    //bool eventFilter(QObject * watched, QEvent * event);
    //void mouseDoubleClickEvent(QMouseEvent * event);
    //void mousePressEvent(QMouseEvent * event);
private slots:
    void pushButtonClicked(bool);
private:
    Ui::TableWidgetItemSecond*      m_ui;
    QWidget*                        m_parentWidget;
    QMap<QString, QWidget*>         m_mapPropertyWidget;
};
