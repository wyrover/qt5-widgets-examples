#include "qtablewidget_test.h"
#include "QLineDelegate.h"

QTableWidget_test::QTableWidget_test(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	ui.tableWidget->setItemDelegate(new QLineDelegate(ui.tableWidget));
}

QTableWidget_test::~QTableWidget_test()
{

}
