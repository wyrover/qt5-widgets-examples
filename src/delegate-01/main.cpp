#include <QApplication>

#include <QTableView>
#include <QStandardItemModel>

#include "bardelegate.h"

#include <QtPlugin>
#if defined(Q_OS_WIN32)
    Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin)
#elif defined(Q_OS_MAC)
    Q_IMPORT_PLUGIN(QCocoaIntegrationPlugin)
#endif

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QTableView table;
    QStandardItemModel model(10, 2);

    for (int r = 0; r < 10; ++r) {
        QStandardItem *item = new QStandardItem(QString("Row %1").arg(r + 1));
        item->setEditable(false);
        model.setItem(r, 0, item);
        model.setItem(r, 1, new QStandardItem(QString::number((r * 30) % 100)));
    }

    table.setModel(&model);
    BarDelegate delegate;
    table.setItemDelegateForColumn(1, &delegate);
    table.show();
    return app.exec();
}
