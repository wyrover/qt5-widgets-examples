#pragma once

#include <QWidget>


class StateButton:
    public QWidget
{
    Q_OBJECT

public:
    explicit StateButton(QWidget* parent = NULL);

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void enterEvent(QEvent* event) override;
    void leaveEvent(QEvent* event) override;

protected:
    enum ButtonState {
        BTN_NORMAL,
        BTN_HOVER,
        BTN_PRESSED,
    };
    ButtonState buttonState() const
    {
        return state;
    }

private:
    ButtonState     state;
    bool            pressed;
    bool            pressedInside;

private:
    void updateState(bool inside);
    bool contains(const QPoint& pos);
};
