#include "dock_widget.h"
#include "dock_titlebar.h"
#include "titlebar_close_button.h"

#include <QPainter>


static const QColor DockBorderColor = Qt::gray;


DockWidget::DockWidget(QWidget* parent) :
    QDockWidget(parent),
    titlebar(new DockTitlebar(this))
{
    setAllowedAreas(Qt::AllDockWidgetAreas);
    connect(this, SIGNAL(topLevelChanged(bool)), this, SLOT(onDockWidgetTopLevelChanged(bool)));
    connect(this, SIGNAL(featuresChanged(QDockWidget::DockWidgetFeatures)), this, SLOT(onDockWidgetFeaturesChanged(QDockWidget::DockWidgetFeatures)));
    setTitleBarWidget(titlebar);
}

DockWidget::~DockWidget()
{
    //
}

void DockWidget::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    QRect rect = this->rect();
    rect.setSize(rect.size() - QSize(1, 1)); // fix the rect bounds bug

    if (isFloating()) {
        rect.adjust(2, 2, -2, -2); // TODO: ?? may be different padding on other platforms
    }

    painter.setPen(DockBorderColor);
    painter.drawRect(rect);
}

void DockWidget::onDockWidgetTopLevelChanged(bool topLevel)
{
    if (topLevel) {
        // adjustSize();
    }
}

void DockWidget::onDockWidgetFeaturesChanged(QDockWidget::DockWidgetFeatures features)
{
    titlebar->closeButton()->setVisible(features & DockWidgetClosable);
}
