#include "UiTableWidgetItem.h"
#include "ui_TableWidgetItem.h"
#include <QMouseEvent>

UiTableWidgetItem::UiTableWidgetItem(QWidget * parent, Qt::WindowFlags f)
    : QWidget(parent, f)
    , m_ui(new Ui::TableWidgetItem)
    , m_parentWidget(parent)
{
    //setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    //setWindowModality(Qt::WindowModal);
    m_ui->setupUi(this);
    //int titleHeight = Global::Settings::instance()->TitleBarH*0.5;
    //int titleWidth = Global::Settings::instance()->AvailableWidth*0.18;
    //setFixedWidth(titleWidth);
    //m_ui->titleWidget->setFixedHeight(titleHeight);
    //m_ui->pb2->setFixedSize(titleHeight*0.61, titleHeight*0.6);
    //m_ui->pb3->setFixedSize(titleHeight*0.6, titleHeight*0.6);
    connect(m_ui->pb2, SIGNAL(clicked(bool)), this, SLOT(pushButtonClicked(bool)));
    connect(m_ui->pb3, SIGNAL(clicked(bool)), this, SLOT(pushButtonClicked(bool)));
}

UiTableWidgetItem::~UiTableWidgetItem()
{
}

void UiTableWidgetItem::setPropertyValue(QString property, QString value)
{
    //int titleHeight = Global::Settings::instance()->TitleBarH*0.5;
    if (property == "icon") {
        //m_ui->iconLabel->setPixmap(QPixmap(value).scaled(titleHeight*0.6*130.0/32.0, titleHeight*0.6));
    } else if (property == "title") {
        m_ui->textLabel->setText(value);
    } else {
    }
}

QString UiTableWidgetItem::getPropertyValue(QString property)
{
    QString str;

    if (property == "title") {
        str = m_ui->textLabel->text();
    } else {
    }

    return str;
}


void UiTableWidgetItem::setPushButtonVisible(QString pushButtonName, bool flag)
{
    if (pushButtonName == "pushButton1") {
    } else if (pushButtonName == "pushButton2") {
        m_ui->pb2->setVisible(flag);
    } else if (pushButtonName == "pushButton3") {
        m_ui->pb3->setVisible(flag);
    } else {
    }
}

void UiTableWidgetItem::setPushButtonChecked(QString pushButtonName, bool flag)
{
    if (pushButtonName == "pushButton1") {
    } else if (pushButtonName == "pushButton2") {
        m_ui->pb2->setChecked(flag);
    } else if (pushButtonName == "pushButton3") {
        m_ui->pb3->setChecked(flag);
    } else {
    }
}

void UiTableWidgetItem::setContentWidgetVisible(bool visible)
{
    m_ui->contentWidget->setVisible(visible);
}

bool UiTableWidgetItem::getContentWidgetVisible()
{
    return m_ui->contentWidget->isVisible();
}

void UiTableWidgetItem::addWidget(QWidget* widget)
{
#if 0
    QLayout * layout = m_ui->contentWidget->layout();
    QVBoxLayout* vBoxLayout = dynamic_cast<QVBoxLayout*>(layout);

    if (!vBoxLayout) {
        vBoxLayout = new QVBoxLayout(m_ui->contentWidget);
        vBoxLayout->setSpacing(0);
        vBoxLayout->setContentsMargins(3, 0, 0, 3);
    }

    vBoxLayout->addWidget(widget);
    UiTableWidgetItemSecond* w = dynamic_cast<UiTableWidgetItemSecond*>(widget);

    if (!w) return;

    m_vecChildWidget.push_back(w);
    // 连接信号和槽
    connect(w, SIGNAL(itemPushButtonClicked(QWidget*, QString, bool)), this, SIGNAL(itemPushButtonClicked(QWidget*, QString, bool)));
    connect(w, SIGNAL(mouseDoubleClicked(QWidget*)), this, SIGNAL(mouseDoubleClicked(QWidget*)));
    connect(w, SIGNAL(mousePressed(QWidget*)), this, SIGNAL(mousePressed(QWidget*)));
    // 增加过滤事件
    HomePlugin::UiCustomTableWidget* parentWidget = dynamic_cast<HomePlugin::UiCustomTableWidget*>(m_parentWidget);

    if (!parentWidget) return;

    parentWidget->addEventFilter(w);
#endif
}

void UiTableWidgetItem::removeWidget(QWidget* widget)
{
    QLayout * layout = m_ui->contentWidget->layout();
    QVBoxLayout* vBoxLayout = dynamic_cast<QVBoxLayout*>(layout);

    if (!vBoxLayout) return;

    vBoxLayout->removeWidget(widget);
}

bool UiTableWidgetItem::containChild()
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

void UiTableWidgetItem::setStyleSheet(QString name, QString qss)
{
    if (name == "titleWidget") {
        m_ui->titleWidget->setStyleSheet(qss);
    } else if (name == "pushButton1") {
    } else if (name == "pushButton2") {
        m_ui->pb2->setStyleSheet(qss);
    } else if (name == "pushButton3") {
        m_ui->pb3->setStyleSheet(qss);
    } else if (name == "icon") {
        m_ui->iconLabel->setStyleSheet(qss);
    } else {
    }
}

void UiTableWidgetItem::setPropertyWidget(QString name, QWidget* widget)
{
    m_mapPropertyWidget[name] = widget;
    widget->installEventFilter(this);
}

QWidget* UiTableWidgetItem::getPropertyWidget(QString name)
{
    QMap<QString, QWidget*>::const_iterator it = m_mapPropertyWidget.find(name);

    if (it != m_mapPropertyWidget.end()) {
        return it.value();
    }

    return NULL;
}

std::vector<QWidget*>& UiTableWidgetItem::getChildWidget()
{
    return m_vecChildWidget;
}

bool UiTableWidgetItem::event(QEvent* event)
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

bool UiTableWidgetItem::eventFilter(QObject * watched, QEvent * event)
{
    if (event->type() == QEvent::Hide) {
        QWidget* widget = dynamic_cast<QWidget*>(watched);

        if (widget) {
            QString key = m_mapPropertyWidget.key(widget);

            if (key == "displayInfoWindowPtr") {
            } else if (key == "smallWindowPtr") {
                m_ui->pb2->setChecked(false);
            } else {
            }
        }
    } else if (event->type() == QEvent::HoverEnter) {
        int i = 0;
        ++i;
    }

    return QWidget::eventFilter(watched, event);
}

void UiTableWidgetItem::mouseDoubleClickEvent(QMouseEvent * event)
{
    if (event->button() == Qt::LeftButton) {
        emit mouseDoubleClicked(this);
    }

    return QWidget::mouseDoubleClickEvent(event);
}

void UiTableWidgetItem::mousePressEvent(QMouseEvent * event)
{
    if (event->button() == Qt::LeftButton) {
        emit mousePressed(this);
    }

    return QWidget::mousePressEvent(event);
}

void UiTableWidgetItem::pushButtonClicked(bool flag)
{
    QPushButton* pushButton = dynamic_cast<QPushButton*>(sender());

    if (!pushButton) return;

    QString name;

    if (pushButton == m_ui->pb2) {
        name = "pushButton2";
    } else if (pushButton == m_ui->pb3) {
        name = "pushButton3";
    } else {
    }

    emit itemPushButtonClicked(this, name, flag);
}
