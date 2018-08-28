#include "QLineDelegate.h"
#include <QPainter>

QLineDelegate::QLineDelegate(QTableView* tableView)
{
    unsigned int gridHint = 0;

    if (tableView) {
        QStyleOptionViewItem *option = new QStyleOptionViewItem();
        option->widget = tableView;
        gridHint = tableView->style()->styleHint(QStyle::SH_Table_GridLineColor,
                   option, tableView);
        delete option;
    }

    QColor gridColor = static_cast<QRgb>(gridHint);
    pen = QPen(gridColor, 0, tableView->gridStyle());
    view = tableView;
}
void QLineDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index)const
{
    QPen oldPen = painter->pen();
    painter->setPen(pen);
    painter->drawLine(option.rect.bottomLeft(), option.rect.bottomRight());
    painter->setPen(oldPen);
    QStyledItemDelegate::paint(painter, option, index);
}