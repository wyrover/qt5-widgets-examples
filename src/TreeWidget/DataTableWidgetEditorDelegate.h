#ifndef DELEGATE_H
#define DELEGATE_H

#include <QItemDelegate>
#include <QModelIndex>
#include <QObject>
#include <QTreeWidget>

class DataTableWidgetEditorDelegate : public QItemDelegate
{
    Q_OBJECT

public:
    DataTableWidgetEditorDelegate(QObject *parent = 0);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const;

    //void setEditorData(QWidget *editor, const QModelIndex &index) const;
    //void setModelData(QWidget *editor, QAbstractItemModel *model,
    //                  const QModelIndex &index) const;

    //void updateEditorGeometry(QWidget *editor,
    //    const QStyleOptionViewItem &option, const QModelIndex &index) const;
public slots:
    void slotLineChanged(const QString& text);
protected:
    bool isExist;
};

#endif
