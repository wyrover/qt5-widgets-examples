#pragma once

#include "state_button.h"


class TitlebarCloseButton :
    public StateButton
{
    Q_OBJECT
public:
    explicit TitlebarCloseButton(QWidget* parent = NULL);
    ~TitlebarCloseButton();

protected:
    void paintEvent(QPaintEvent* event) override;
};
