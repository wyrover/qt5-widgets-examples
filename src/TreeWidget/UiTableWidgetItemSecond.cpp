#include "UiTableWidgetItemSecond.h"
#include "ui_TableWidgetItemSecond.h"
#include <QMouseEvent>
#include <QEvent>

UiTableWidgetItemSecond::UiTableWidgetItemSecond(QWidget * parent, Qt::WindowFlags f)
    : QWidget(parent, f)
    , m_ui(new Ui::TableWidgetItemSecond)
    , m_parentWidget(parent)
{
    //setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    //setWindowModality(Qt::WindowModal);
    m_ui->setupUi(this);
    setAttribute(Qt::WA_Hover);
    //int titleHeight = Global::Settings::instance()->TitleBarH*0.5;
    //int titleWidth = Global::Settings::instance()->AvailableWidth*0.18;
    //setFixedWidth(titleWidth);
    //m_ui->titleWidget->setFixedHeight(titleHeight);
    //m_ui->pb1->setFixedSize(titleHeight*0.6, titleHeight*0.6);
    //m_ui->pb2->setFixedSize(titleHeight*0.6, titleHeight*0.6);
    //m_ui->pb3->setFixedSize(titleHeight*0.6, titleHeight*0.6);
    installEventFilter(this);
    connect(m_ui->pb1, SIGNAL(clicked(bool)), this, SLOT(pushButtonClicked(bool)));
    connect(m_ui->pb2, SIGNAL(clicked(bool)), this, SLOT(pushButtonClicked(bool)));
    connect(m_ui->pb3, SIGNAL(clicked(bool)), this, SLOT(pushButtonClicked(bool)));
}

UiTableWidgetItemSecond::~UiTableWidgetItemSecond()
{
}

void UiTableWidgetItemSecond::setPropertyValue(QString property, QString value)
{
    if (property == "icon") {
        m_ui->iconLabel->setPixmap(QPixmap(value));
    } else if (property == "title") {
        m_ui->textLabel->setText(value);
    } else {
    }
}

QString UiTableWidgetItemSecond::getPropertyValue(QString property)
{
    QString str;

    if (property == "title") {
        str = m_ui->textLabel->text();
    } else {
    }

    return str;
}


void UiTableWidgetItemSecond::setPushButtonVisible(QString pushButtonName, bool flag)
{
    if (pushButtonName == "pushButton1") {
        m_ui->pb1->setVisible(flag);
    } else if (pushButtonName == "pushButton2") {
        m_ui->pb2->setVisible(flag);
    } else if (pushButtonName == "pushButton3") {
        m_ui->pb3->setVisible(flag);
    } else {
    }
}

void UiTableWidgetItemSecond::setPushButtonChecked(QString pushButtonName, bool flag)
{
    if (pushButtonName == "pushButton1") {
        m_ui->pb1->setChecked(flag);
    } else if (pushButtonName == "pushButton2") {
        m_ui->pb2->setChecked(flag);
    } else if (pushButtonName == "pushButton3") {
        m_ui->pb3->setChecked(flag);
    } else {
    }
}

void UiTableWidgetItemSecond::setContentWidgetVisible(bool visible)
{
    m_ui->contentWidget->setVisible(visible);
}

bool UiTableWidgetItemSecond::getContentWidgetVisible()
{
    return m_ui->contentWidget->isVisible();
}

void UiTableWidgetItemSecond::addWidget(QWidget* widget)
{
    QLayout * layout = m_ui->contentWidget->layout();
    QVBoxLayout* vBoxLayout = dynamic_cast<QVBoxLayout*>(layout);

    if (!vBoxLayout) {
        vBoxLayout = new QVBoxLayout(m_ui->contentWidget);
        vBoxLayout->setSpacing(0);
        vBoxLayout->setContentsMargins(3, 0, 0, 3);
    }

    vBoxLayout->addWidget(widget);
    UiTableWidgetItemSecond* w = dynamic_cast<UiTableWidgetItemSecond*>(widget);

    if (w) {
        connect(w, SIGNAL(itemPushButtonClicked(QWidget*, QString, bool)), this, SIGNAL(itemPushButtonClicked(QWidget*, QString, bool)));
        connect(w, SIGNAL(mouseDoubleClicked(QWidget*)), this, SIGNAL(mouseDoubleClicked(QWidget*)));
        connect(w, SIGNAL(mousePressed(QWidget*)), this, SIGNAL(mousePressed(QWidget*)));
    }
}

bool UiTableWidgetItemSecond::containChild()
{
    QObjectList objList = m_ui->contentWidget->children();

    for (int i = 0; i < objList.size(); ++i) {
        QWidget* widget = dynamic_cast<QWidget*>(objList[i]);

        if (widget) {
            return true;
        }
    }

    return false;
}

void UiTableWidgetItemSecond::setStyleSheet(QString name, QString qss)
{
    if (name == "titleWidget") {
        m_ui->titleWidget->setStyleSheet(qss);
    } else if (name == "pushButton1") {
        m_ui->pb1->setStyleSheet(qss);
    } else if (name == "pushButton2") {
        m_ui->pb2->setStyleSheet(qss);
    } else if (name == "pushButton3") {
        m_ui->pb3->setStyleSheet(qss);
    } else {
    }
}

void UiTableWidgetItemSecond::setPropertyWidget(QString name, QWidget* widget)
{
    m_mapPropertyWidget[name] = widget;
    widget->installEventFilter(this);
}

QWidget* UiTableWidgetItemSecond::getPropertyWidget(QString name)
{
    QMap<QString, QWidget*>::const_iterator it = m_mapPropertyWidget.find(name);

    if (it != m_mapPropertyWidget.end()) {
        return it.value();
    }

    return NULL;
}

bool UiTableWidgetItemSecond::event(QEvent* event)
{
    if (event->type() == QEvent::HoverEnter) {
        int i = 0;
        ++i;
    }

    return QWidget::event(event);
}

//bool UiTableWidgetItemSecond::eventFilter(QObject * watched, QEvent * event)
//{
//  if (event->type() == QEvent::Hide)
//  {
//      QWidget* widget = dynamic_cast<QWidget*>(watched);
//      if (widget)
//      {
//          QString key = m_mapPropertyWidget.key(widget);
//          if (key == "displayInfoWindowPtr")
//          {
//              m_ui->pb1->setChecked(false);
//          }
//          else if (key == "smallWindowPtr")
//          {
//              m_ui->pb2->setChecked(false);
//          }
//          else
//          {
//          }
//      }
//  }
//  return QWidget::eventFilter(watched, event);
//}
//
//void UiTableWidgetItemSecond::mouseDoubleClickEvent(QMouseEvent * event)
//{
//  if (event->button() == Qt::LeftButton)
//  {
//      emit mouseDoubleClicked(this);
//  }
//  return QWidget::mouseDoubleClickEvent(event);
//}
//
//void UiTableWidgetItemSecond::mousePressEvent(QMouseEvent * event)
//{
//  if (event->button() == Qt::LeftButton)
//  {
//      emit mousePressed(this);
//  }
//  return QWidget::mousePressEvent(event);
//}

void UiTableWidgetItemSecond::pushButtonClicked(bool flag)
{
    QPushButton* pushButton = dynamic_cast<QPushButton*>(sender());

    if (!pushButton) return;

    QMouseEvent event(QEvent::MouseButtonPress, QPointF(0, 0), Qt::LeftButton, 0, 0);
    QApplication::sendEvent(this, &event);
    QString name;

    if (pushButton == m_ui->pb1) {
        name = "pushButton1";
    } else if (pushButton == m_ui->pb2) {
        name = "pushButton2";
    } else if (pushButton == m_ui->pb3) {
        name = "pushButton3";
    } else {
    }

    emit itemPushButtonClicked(this, name, flag);
}
