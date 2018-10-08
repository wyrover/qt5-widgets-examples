#ifndef tabicon_h__
#define tabicon_h__

#include <QWidget>

#ifndef QSL
#define QSL(x) QStringLiteral(x)
#endif

#ifndef QL1S
#define QL1S(x) QLatin1String(x)
#endif

#ifndef QL1C
#define QL1C(x) QLatin1Char(x)
#endif

class QTimer;
class WebTab;

class TabIcon : public QWidget
{
    Q_OBJECT

public:
    struct Data {
        int framesCount;
        int animationInterval;
        QPixmap animationPixmap;
        QPixmap audioPlayingPixmap;
        QPixmap audioMutedPixmap;
    };
    explicit TabIcon(QWidget* parent = 0);

    void setWebTab(WebTab* tab);
    void updateIcon();

    static Data *data();

Q_SIGNALS:
    void resized();

    private Q_SLOTS:
    void showLoadingAnimation();
    void hideLoadingAnimation();

    void updateAudioIcon(bool recentlyAudible);
    void updateAnimationFrame();

private:
    void show();
    void hide();
    bool shouldBeVisible() const;

    bool event(QEvent *event) override;
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;

    WebTab* m_tab;
    QTimer* m_updateTimer;
    QTimer* m_hideTimer;
    QPixmap m_sitePixmap;
    int m_currentFrame;
    bool m_animationRunning;
    bool m_audioIconDisplayed;
    QRect m_audioIconRect;
};


#endif // tabicon_h__
