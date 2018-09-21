#include "dock_titlebar.h"
#include "dock_widget.h"
#include "titlebar_close_button.h"

#include <QPainter>


static const int TitleBarHeight = 20;
static const int TitleBarTextHorzMargin = 6;
static const QColor TitleBarColor = Qt::gray;
static const QColor TitleBarTextColor = Qt::white;
static const int CloseButtonMargin = 2;


DockTitlebar::DockTitlebar(DockWidget* dock) :
    QWidget(dock),
    dock(dock),
    close(new TitlebarCloseButton(this))
{
    int CloseButtonSize = TitleBarHeight - 2 * CloseButtonMargin;
    close->setFixedSize(CloseButtonSize, CloseButtonSize);
    connect(close, SIGNAL(clicked()), dock, SLOT(close()));
}

DockTitlebar::~DockTitlebar()
{
    //
}

QSize DockTitlebar::minimumSizeHint() const
{
    return QSize(60, TitleBarHeight);
}

void DockTitlebar::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    QRect rect = this->rect();
    painter.fillRect(rect, TitleBarColor);
    painter.setPen(TitleBarTextColor);
    QFont font = this->font();
    font.setBold(true);
    painter.setFont(font);
    rect.adjust(TitleBarTextHorzMargin, 0, -TitleBarTextHorzMargin - (close->isVisible() ? close->width() + CloseButtonMargin : 0), 0);
    painter.drawText(rect, Qt::AlignLeft | Qt::AlignVCenter, dock->windowTitle());
}

void DockTitlebar::resizeEvent(QResizeEvent* event)
{
    Q_UNUSED(event)
    QSize closeSize = close->size();
    QPoint org(rect().right() - closeSize.width() - CloseButtonMargin, CloseButtonMargin);
    close->setGeometry(QRect(org, closeSize));
}

