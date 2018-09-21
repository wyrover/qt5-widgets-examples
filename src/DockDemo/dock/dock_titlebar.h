#pragma once

#include <QWidget>

class DockWidget;
class TitlebarCloseButton;


class DockTitlebar :
    public QWidget
{
    Q_OBJECT
public:
    explicit DockTitlebar(DockWidget* dock = NULL);
    ~DockTitlebar();

public:
    TitlebarCloseButton* closeButton() const
    {
        return close;
    }
    QSize sizeHint() const Q_DECL_OVERRIDE
    {
        return minimumSizeHint();
    }
    QSize minimumSizeHint() const Q_DECL_OVERRIDE;

protected:
    void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent* event) Q_DECL_OVERRIDE;

private:
    DockWidget*     dock;
    TitlebarCloseButton*    close;
};
