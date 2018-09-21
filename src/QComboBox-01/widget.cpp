#if defined (_MSC_VER) && (_MSC_VER >=1600)
#pragma execution_character_set("utf-8")
#endif


#include "widget.h"
#include <QComboBox>
#include <QItemDelegate>
#include <QCompleter>
#include <QLineEdit>
#include <QAbstractItemView>
#include <QScrollBar>
#include <QListView>

    class ComboBoxDelegate : public QItemDelegate
    {
    public:
        explicit ComboBoxDelegate(QObject * parent = nullptr) : QItemDelegate(parent) {}
        ~ComboBoxDelegate() = default;

        QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override
        {
            QSize size = QItemDelegate::sizeHint(option, index);
            size.setHeight(qMax(40, size.height()));
            return size;
        }
    };

Widget::Widget(QWidget *parent) :
    QWidget(parent)
{
    setWindowTitle(tr("QComboBox-01"));
    layout_ = new QVBoxLayout;
    auto combox_1 = new QComboBox;
    combox_1->setEditable(true);
    combox_1->lineEdit()->setPlaceholderText(tr("选择或搜索"));
    combox_1->setItemDelegate(new ComboBoxDelegate());
    QStringList item_list_;

    for (int i = 0; i < 10; ++i) {
        combox_1->addItem(QString("test_%1").arg(i));
        item_list_ << QString("test_%1").arg(i);
    }

    auto completer_ = new QCompleter(item_list_, this);
    completer_->setCompletionColumn(combox_1->modelColumn());
    completer_->setCompletionMode(QCompleter::PopupCompletion);
    completer_->setCaseSensitivity(Qt::CaseInsensitive);
    completer_->setFilterMode(Qt::MatchContains);
    //completer_->setPopup(new QListView());
    completer_->popup()->verticalScrollBar()->setStyleSheet(
        "QScrollBar:vertical {background: rgb(35,35,35);width: 15px;margin: 20px 0px 20px 0px;}"
        "QScrollBar::handle:vertical{background: rgb(100,100,100); width: 20px;}"
        "QScrollBar::add-line:vertical{background: rgb(100,100,100); height: 15px; subcontrol-position: bottom;subcontrol-origin: margin;}"
        "QScrollBar::sub-line:vertical {background: rgb(100,100,100);height: 15px;subcontrol-position: top;subcontrol-origin: margin;}"
        "QScrollBar:down-arrow:vertical {width: 10px;height: 10px;background: rgb(100,100,100);image: url(:/images/images/downArrow.png);}"
        "QScrollBar:up-arrow:vertical {width: 10px;height: 10px;background: rgb(100,100,100);image: url(:/images/images/upArrow.png);}"
        "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {background: none;}");
    completer_->popup()->setStyleSheet("QListView{background: rgb(35,35,35);color:white; font-size: 12pt; font-family: Calibri Light; font-weight:normal}"
                                      );
    QAbstractItemView* view = completer_->popup();
    view->setItemDelegate(new ComboBoxDelegate());
    combox_1->setCompleter(completer_);
    combox_1->setCurrentIndex(-1);
    combox_1->setInsertPolicy(QComboBox::NoInsert);
    layout_->addWidget(combox_1);
    setLayout(layout_);
}
