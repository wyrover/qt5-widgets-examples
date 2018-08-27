#include "table.h"
#include <QtGui>
#include <QPainter>
#include <QDebug>
#include <QVBoxLayout>
#include <QTableView>
#include <QHeaderView>

#define ROW (2)
int Table::TITLE = Qt::UserRole + 2;
int Table::CONTENT = Qt::UserRole + 3;

	//class Table
	Table::Table(QWidget *parent)
		:QWidget(parent)
	{
		QVBoxLayout *layout = new QVBoxLayout(this);
		layout->setMargin(0);
		layout->setSpacing(0);

		listView = new QTableView;
		listView->horizontalHeader()->hide();
		listView->verticalHeader()->hide();
		listView->setFrameShape(QFrame::NoFrame);
		listView->setShowGrid(true);

        listView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        listView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
		listView->setSelectionMode(QAbstractItemView::NoSelection);
		listView->setEditTriggers(QTableView::NoEditTriggers);

		ListDelegate *listDelegate = new ListDelegate(this);
		listView->setItemDelegate(listDelegate);

		model = new QStandardItemModel;
		listView->setModel(model);
		connect(listView, SIGNAL(clicked(const QModelIndex &)), 
				SLOT(clicked(const QModelIndex &)));	

		initModel();
		layout->addWidget(listView);
		resize(400, 600);
	}

	void Table::initModel()
	{
		for (int i = 0; i < 10; i++) {
			QStandardItem *item = new QStandardItem;
			QString title("Favorite");
			title.append(QString::number(i));
			QString content("Content");
			content.append(QString::number(i));

			item->setData(title, Table::TITLE);
			item->setData(content, Table::CONTENT);
			model->setItem(i / ROW, i % ROW, item);
			qDebug() << "Table" << "col" << i/ROW << "row" << i%ROW;
		}
	}

	void Table::clicked(const QModelIndex &index)
	{
		qDebug() << "Table" << __func__ << "index" << index;
	}

	Table::~Table()
	{
	}

	//class ListDelegate	
	ListDelegate::ListDelegate(QObject *parent)
		:QStyledItemDelegate(parent)
	{
	}

	ListDelegate::~ListDelegate()
	{
	}

	void ListDelegate::paint(QPainter *painter, const QStyleOptionViewItem &item, 
			const QModelIndex &index) const 
	{
		const int margin  = 20;
		QPen pen(Qt::black);	
		painter->setPen(pen);
		
		int x = item.rect.x();
		int y = item.rect.y();
		int w = item.rect.width();
		int h = item.rect.height();
		
		QString title = index.data(Table::TITLE).toString();
		QString content = index.data(Table::CONTENT).toString();
		if (title.isEmpty() || content.isEmpty())
			return;

		qDebug() << "ListDelegate" << __func__ << "title" << title
			<< "content" << content;
			
		//top line
		painter->drawLine(x + margin, y + 2, x + w - margin, y + 2);

		//bottom line
		painter->drawLine(x + margin, y + h - 2, x + w - margin, y + h - 2);
		
		// \ line
		//painter->drawLine(x, y, x + w, y + h);

		//>
		int lineY = y + h/2;
		int lineX = x + w - margin;
		painter->drawLine(lineX, lineY, lineX - margin/2, lineY + margin/2);
		painter->drawLine(lineX, lineY, lineX - margin/2, lineY - margin/2);
		
		//title
		QFont font = painter->font();
		QFontMetrics fm(font);
		painter->drawText(x + margin*2, y + 5, x + w - margin, fm.height(), Qt::AlignLeft | Qt::AlignVCenter, title);
		//content
		painter->drawText(x + margin*2, y + h - fm.height() - 10, x + w - margin, fm.height(), Qt::AlignLeft | Qt::AlignVCenter, content);

	}


