#pragma once

#include <QWidget>
#include <QMap>

namespace Ui
{
class TableWidgetItem;
}

class UiTableWidgetItem: public QWidget
{
    Q_OBJECT
public:
    UiTableWidgetItem(QWidget * parent = 0, Qt::WindowFlags f = 0);
    ~UiTableWidgetItem();
    void setPropertyValue(QString property, QString value);
    QString getPropertyValue(QString property);
    void setPushButtonVisible(QString pushButtonName, bool flag);
    void setPushButtonChecked(QString pushButtonName, bool flag);
    void setContentWidgetVisible(bool visible);
    bool getContentWidgetVisible();
    void addWidget(QWidget* widget);
    void removeWidget(QWidget* widget);
    bool containChild();
    void setStyleSheet(QString name, QString qss);
    void setPropertyWidget(QString name, QWidget* widget);
    QWidget* getPropertyWidget(QString name);
    std::vector<QWidget*>& getChildWidget();
signals:
    void itemPushButtonClicked(QWidget* widget, QString name, bool flag);
    void mouseDoubleClicked(QWidget*);
    void mousePressed(QWidget*);
protected:
    virtual bool event(QEvent* event);
    bool eventFilter(QObject * watched, QEvent * event);
    void mouseDoubleClickEvent(QMouseEvent * event);
    void mousePressEvent(QMouseEvent * event);
private slots:
    void pushButtonClicked(bool);
private:
    Ui::TableWidgetItem*        m_ui;
    QWidget*                    m_parentWidget;
    std::vector<QWidget*>       m_vecChildWidget;
    QMap<QString, QWidget*>     m_mapPropertyWidget;
};
