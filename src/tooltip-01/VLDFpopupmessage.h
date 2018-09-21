#ifndef VLDFPOPUPMESSAGE_H
#define VLDFPOPUPMESSAGE_H

#include <QWidget>
#include <QString>
#include <QBrush>
#include <QColor>
#include <QFont>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>

class QShowEvent;
class QPaintEvent;

enum MessageType {
    NormalMessage,
    ErrorMessage,
    WarningMessage
};

class VLDFPopupMessage : public QWidget
{
    Q_OBJECT
public:
    explicit VLDFPopupMessage(QWidget *parent = Q_NULLPTR);
    ~VLDFPopupMessage();

    void setMessage(const QString &message);
    void setMessageType(MessageType type);
    double height() const;
    double width() const;

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QString mTextMessage;
    QBrush mBottomBandColor;
    QColor mTextColor;
    QFont mTextFont;
    int mTipHeight;
    int mPadding;
    int mBottomBandHeight;
    QGraphicsOpacityEffect mOpacityEffect;
    QPropertyAnimation mFadeInAnimation;
    QPropertyAnimation mFadeOutAnimation;

    // QObject interface
public:
    bool eventFilter(QObject *watched, QEvent *event) override;

    // QWidget interface
protected:
    void showEvent(QShowEvent *event) override;
    void hideEvent(QHideEvent *event) override;
};

#endif // VLDFPOPUPMESSAGE_H