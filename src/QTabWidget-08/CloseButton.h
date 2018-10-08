#ifndef CloseButton_h__
#define CloseButton_h__

#include <QAbstractButton>

// Class for close button on tabs
// * taken from qtabbar.cpp
class MYCloseButton : public QAbstractButton
{
    Q_OBJECT

public:
    MYCloseButton(QWidget *parent = nullptr);

    QSize sizeHint() const override;

    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
};


#endif // CloseButton_h__
