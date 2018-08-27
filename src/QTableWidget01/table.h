#ifndef _TABLE_H_
#define _TABLE_H_

#include <QWidget>
#include <QStyledItemDelegate>
	
	//class Table
	class QTableView;
	class QStandardItemModel;
	class Table : public QWidget {
		Q_OBJECT
	public:
		Table(QWidget *parent = 0);	
		virtual ~Table();
	
		void initModel();
	
	private slots:
		void clicked(const QModelIndex &);

	private:
		QTableView *listView;
		QStandardItemModel *model;

	public:
		static int TITLE;
		static int CONTENT;
	}; 

	//class ListDelegate	
	class ListDelegate : public QStyledItemDelegate {
		Q_OBJECT
	public:
		ListDelegate(QObject *parent = 0);
		virtual ~ListDelegate();

		virtual void paint(QPainter *, const QStyleOptionViewItem &, const QModelIndex &) const;

	}; 

#endif

