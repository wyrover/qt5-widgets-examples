#include "CustomTreeWidget.h"
#include "DataTableWidgetEditorDelegate.h"
#include "UiTableWidgetItem.h"

CustomTreeWidget::CustomTreeWidget(QWidget * parent)
    : QTreeWidget(parent)
{
    DataTableWidgetEditorDelegate* delegateType = new DataTableWidgetEditorDelegate(this);
    setItemDelegate(delegateType);
    {
        QTreeWidgetItem* item = new QTreeWidgetItem(this);
        openPersistentEditor(item);
        openPersistentEditor(item, 1);
        {
            QTreeWidgetItem* item1 = new QTreeWidgetItem(item);
            item1->setText(0, "test");
            openPersistentEditor(item1);
            openPersistentEditor(item1, 1);
        }
        {
            QTreeWidgetItem* item1 = new QTreeWidgetItem(item);
            openPersistentEditor(item1);
            openPersistentEditor(item1, 1);
        }
    }
    {
        QTreeWidgetItem* item = new QTreeWidgetItem(this);
        openPersistentEditor(item);
        openPersistentEditor(item, 1);
    }
    {
        QTreeWidgetItem* item = new QTreeWidgetItem(this);
    }
    {
        QTreeWidgetItem* item = new QTreeWidgetItem(this);
    }
    QTreeWidgetItem * tempItem = topLevelItem(0);
    QWidget* w = itemWidget(tempItem, 0);
    UiTableWidgetItem* tempItem1 = dynamic_cast<UiTableWidgetItem*>(w);
    tempItem1->setPushButtonVisible("pushButton3", false);
    tempItem1->setPropertyValue("title", "Tt");
    connect(this, SIGNAL(itemSelectionChanged()), this, SLOT(itemSelectionChangedSlot()));
}

CustomTreeWidget::~CustomTreeWidget()
{
}

void CustomTreeWidget::itemSelectionChangedSlot()
{
}
