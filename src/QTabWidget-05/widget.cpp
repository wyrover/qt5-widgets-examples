#include "widget.h"
#include "draginouttabwidget.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QTextEdit>



Widget::Widget(QWidget *parent)
    : QWidget(parent)
    
{
    auto layout = new QVBoxLayout;
    layout->setSpacing(0);
    layout->setMargin(0);


    tabWidget_ = new DragInOutTabWidget(this);
   
    for (int j = 1; j < 30; ++j) {

        QString tab_text(QString("tab_%1").arg(++j));
        tabWidget_->addTab(new QLabel(tab_text), tab_text);
    }

    layout->addWidget(tabWidget_);
    setLayout(layout);

    connect(tabWidget_, &DragInOutTabWidget::popSignalWnd, this, &Widget::slotPopSignalWnd);
}

Widget::~Widget()
{

}

void Widget::slotPopSignalWnd(int nIndex)
{
    //QString id = tabWidget_->currentWidget()->property("subwndid").toString();    
    //ViewController::instance()->popOutWndFromTab(id, tabWidget_->currentWidget(), QCursor::pos());


    //if (!m_widgets.contains(id) &&
    //    CONTROLMGR->getGlobalSettingInst()->isExistFuncID(id)) {
    //    CFuncInfo finfo;
    //    CONTROLMGR->getGlobalSettingInst()->getFuncInfo(id, finfo);
    //    SubWidget *pwnd = new SubWidget(NULL, wnd, id, finfo.getFuncName().getVal().toString(), basicui::TS_MIN | basicui::TS_PUSHPIN | basicui::TS_CLOSE | basicui::TS_MAX | basicui::TS_LEFT | basicui::TS_LOGO);
    //    connect(pwnd, &SubWidget::sigWndMove, this, &ViewController::moveInWndToTab, Qt::QueuedConnection);
    //    connect(pwnd, &SubWidget::sigClose, this, &ViewController::closewnd);
    //    pwnd->move(p);
    //    pwnd->resize(900, 600);
    //    pwnd->show();
    //    m_widgets[id] = pwnd;
    //}

    //if (!m_widgets.contains(id)) {
        QWidget* subWin = tabWidget_->currentWidget();
        QWidget* win = new QWidget;
        win->setAttribute(Qt::WA_DeleteOnClose);
        auto layout = new QVBoxLayout;
        layout->addWidget(subWin);
        win->setLayout(layout);
        win->setWindowFlags(Qt::Window);
        subWin->setMouseTracking(true);
        subWin->show();
        subWin->move(QCursor::pos());
        win->resize(900, 600);
        win->show();
        //m_widgets[id] = subWin;
   // }
    



    tabWidget_->setCurrentIndex(qMax(0, qMin(nIndex - 1, tabWidget_->count() - 1)));
}

