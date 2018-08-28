/*
    用来控制QTableWidget的grid只绘制横向的部分

    by 朱威 2016年9月26日13:12:31 @杭州
*/
#ifndef __QLINEDELEGATE_H__
#define __QLINEDELEGATE_H__

#include <QStyleditemDelegate>
#include <QTableView>
#include <QPen>

class QLineDelegate : public QStyledItemDelegate
{
public:
    QLineDelegate(QTableView* tableView);
protected:
    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;
private:
    QPen pen;
    QTableView* view;
};

#endif // __QLINEDELEGATE_H__