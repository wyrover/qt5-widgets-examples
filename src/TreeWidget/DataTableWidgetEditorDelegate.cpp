#include <QtGui>
#include <QComboBox>
#include <QSpinBox>
#include <QLineEdit>
#include <QProgressBar>
#include "DataTableWidgetEditorDelegate.h"
#include <QDebug>
#include "UiTableWidgetItem.h"
#include "UiTableWidgetItemSecond.h"

DataTableWidgetEditorDelegate::DataTableWidgetEditorDelegate(QObject *parent)
    : QItemDelegate(parent), isExist(false)
{
}

QWidget *DataTableWidgetEditorDelegate::createEditor(QWidget *parent,
        const QStyleOptionViewItem& option,
        const QModelIndex& index) const
{
    QModelIndex modelIndex = index.parent();
    bool b = modelIndex.isValid();

    if (!b) {
        UiTableWidgetItem *item = new UiTableWidgetItem(parent);
        return item;
    } else {
        UiTableWidgetItemSecond *item = new UiTableWidgetItemSecond(parent);
        return item;
    }

    return QItemDelegate::createEditor(parent, option, index);
}

//void DataTableWidgetEditorDelegate::setEditorData(QWidget *editor,
//                                    const QModelIndex& index) const
//{
//      return QItemDelegate::setEditorData(editor, index);
//}
//
//void DataTableWidgetEditorDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
//                                   const QModelIndex& index) const
//{
//      return QItemDelegate::setModelData(editor, model, index);
//}
//
//void DataTableWidgetEditorDelegate::updateEditorGeometry(QWidget *editor,
//    const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
//{
//  editor->setGeometry(option.rect);
//}
//
void DataTableWidgetEditorDelegate::slotLineChanged(const QString& text)
{
}