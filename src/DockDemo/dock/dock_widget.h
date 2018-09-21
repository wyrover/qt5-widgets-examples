#pragma once

#include <QDockWidget>


class DockTitlebar;


class DockWidget :
    public QDockWidget
{
    Q_OBJECT
public:
    explicit DockWidget(QWidget* parent = NULL);
    ~DockWidget();

protected:
    void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;

private slots:
    void onDockWidgetTopLevelChanged(bool topLevel);
    void onDockWidgetFeaturesChanged(QDockWidget::DockWidgetFeatures features);

private:
    DockTitlebar*     titlebar;
};
