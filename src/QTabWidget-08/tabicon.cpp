#include "tabicon.h"

#include <QTimer>
#include <QToolTip>
#include <QMouseEvent>
#include <QIcon>
#include <QPainter>

TabIcon::TabIcon(QWidget* parent)
    : QWidget(parent)
    , m_tab(0)
    , m_currentFrame(0)
    , m_animationRunning(false)
    , m_audioIconDisplayed(false)
{
    setObjectName(QSL("tab-icon"));

    m_updateTimer = new QTimer(this);
    m_updateTimer->setInterval(data()->animationInterval);
    connect(m_updateTimer, SIGNAL(timeout()), this, SLOT(updateAnimationFrame()));

    m_hideTimer = new QTimer(this);
    m_hideTimer->setInterval(250);
    connect(m_hideTimer, &QTimer::timeout, this, &TabIcon::hide);

    resize(16, 16);
}

void TabIcon::setWebTab(WebTab* tab)
{
    m_tab = tab;

    //connect(m_tab->webView(), SIGNAL(loadStarted()), this, SLOT(showLoadingAnimation()));
    //connect(m_tab->webView(), SIGNAL(loadFinished(bool)), this, SLOT(hideLoadingAnimation()));
    //connect(m_tab->webView(), &WebView::iconChanged, this, &TabIcon::updateIcon);
    //connect(m_tab->webView(), &WebView::backgroundActivityChanged, this, [this]() { update(); });

    //auto pageChanged = [this](WebPage *page) {
    //    connect(page, &QWebEnginePage::recentlyAudibleChanged, this, &TabIcon::updateAudioIcon);
    //};
    //pageChanged(m_tab->webView()->page());
    //connect(m_tab->webView(), &WebView::pageChanged, this, pageChanged);

    updateIcon();
}

void TabIcon::showLoadingAnimation()
{
    m_currentFrame = 0;

    updateAnimationFrame();
    show();
}

void TabIcon::hideLoadingAnimation()
{
    m_animationRunning = false;

    m_updateTimer->stop();
    updateIcon();
}

void TabIcon::updateIcon()
{
    //m_sitePixmap = m_tab->icon(/*allowNull*/ true).pixmap(16);
    //if (m_sitePixmap.isNull()) {
    //    if (m_tab->url().isEmpty() || m_tab->url().scheme() == QL1S("falkon")) {
    //        hide();
    //    } else {
    //        m_hideTimer->start();
    //    }
    //} else {
    //    show();
    //}
    //update();
}

// static
TabIcon::Data *TabIcon::data()
{
    static Data *data = nullptr;
    if (!data) {
        data = new TabIcon::Data;
        data->animationInterval = 70;
        data->animationPixmap = QIcon(QSL(":icons/other/loading.png")).pixmap(288, 16);
        data->framesCount = data->animationPixmap.width() / data->animationPixmap.height();
        data->audioPlayingPixmap = QIcon::fromTheme(QSL("audio-volume-high"), QIcon(QSL(":icons/other/audioplaying.svg"))).pixmap(16);
        data->audioMutedPixmap = QIcon::fromTheme(QSL("audio-volume-muted"), QIcon(QSL(":icons/other/audiomuted.svg"))).pixmap(16);
    }
    return data;
}

void TabIcon::updateAnimationFrame()
{
    if (!m_animationRunning) {
        m_updateTimer->start();
        m_animationRunning = true;
    }

    update();
    m_currentFrame = (m_currentFrame + 1) % data()->framesCount;
}

void TabIcon::show()
{
    if (!shouldBeVisible()) {
        return;
    }

    m_hideTimer->stop();

    if (isVisible() && width() == 16) {
        return;
    }

    setFixedSize(16, qMax(minimumHeight(), 16));
    emit resized();
    QWidget::show();
}

void TabIcon::hide()
{
    if (shouldBeVisible()) {
        return;
    }

    if (isHidden() && width() == 1) {
        return;
    }

    setFixedSize(1, qMax(minimumHeight(), 16));
    emit resized();
    QWidget::hide();
}

bool TabIcon::shouldBeVisible() const
{
    //if (m_tab && m_tab->isPinned()) {
    //    return true;
    //}
    //return !m_sitePixmap.isNull() || m_animationRunning || m_audioIconDisplayed || (m_tab && m_tab->isPinned());
    return true;
}

bool TabIcon::event(QEvent *event)
{
    //if (event->type() == QEvent::ToolTip) {
    //    QHelpEvent *e = static_cast<QHelpEvent*>(event);
    //    if (m_audioIconDisplayed && m_audioIconRect.contains(e->pos())) {
    //        QToolTip::showText(e->globalPos(), m_tab->isMuted() ? tr("Unmute Tab") : tr("Mute Tab"), this);
    //        event->accept();
    //        return true;
    //    }
    //}

    return QWidget::event(event);
}

void TabIcon::updateAudioIcon(bool recentlyAudible)
{
    //if (m_tab->isMuted() || (!m_tab->isMuted() && recentlyAudible)) {
    //    m_audioIconDisplayed = true;
    //    show();
    //} else {
    //    m_audioIconDisplayed = false;
    //    hide();
    //}

    update();
}

void TabIcon::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    const int size = 16;
    const int pixmapSize = qRound(size * data()->animationPixmap.devicePixelRatioF());

    // Center the pixmap in rect
    QRect r = rect();
    r.setX((r.width() - size) / 2);
    r.setY((r.height() - size) / 2);
    r.setWidth(size);
    r.setHeight(size);

    //if (m_animationRunning) {
    //    p.drawPixmap(r, data()->animationPixmap, QRect(m_currentFrame * pixmapSize, 0, pixmapSize, pixmapSize));
    //} else if (m_audioIconDisplayed && !m_tab->isPinned()) {
    //    m_audioIconRect = r;
    //    p.drawPixmap(r, m_tab->isMuted() ? data()->audioMutedPixmap : data()->audioPlayingPixmap);
    //} else if (!m_sitePixmap.isNull()) {
    //    p.drawPixmap(r, m_sitePixmap);
    //} else if (m_tab && m_tab->isPinned()) {
    //    p.drawPixmap(r, IconProvider::emptyWebIcon().pixmap(size));
    //}

    //// Draw audio icon on top of site icon for pinned tabs
    //if (!m_animationRunning && m_audioIconDisplayed && m_tab->isPinned()) {
    //    const int s = size - 4;
    //    const QRect r(width() - s, 0, s, s);
    //    m_audioIconRect = r;
    //    QColor c = palette().color(QPalette::Window);
    //    c.setAlpha(180);
    //    p.setPen(c);
    //    p.setBrush(c);
    //    p.drawEllipse(r);
    //    p.drawPixmap(r, m_tab->isMuted() ? data()->audioMutedPixmap : data()->audioPlayingPixmap);
    //}

    //// Draw background activity indicator
    //if (m_tab && m_tab->isPinned() && m_tab->webView()->backgroundActivity()) {
    //    const int s = 5;
    //    // Background
    //    const QRect r1(width() - s - 2, height() - s - 2, s + 2, s + 2);
    //    QColor c1 = palette().color(QPalette::Window);
    //    c1.setAlpha(180);
    //    p.setPen(Qt::transparent);
    //    p.setBrush(c1);
    //    p.drawEllipse(r1);
    //    // Foreground
    //    const QRect r2(width() - s - 1, height() - s - 1, s, s);
    //    QColor c2 = palette().color(QPalette::Text);
    //    p.setPen(Qt::transparent);
    //    p.setBrush(c2);
    //    p.drawEllipse(r2);
    //}
}

void TabIcon::mousePressEvent(QMouseEvent *event)
{
    // If audio icon is clicked - we don't propagate mouse press to the tab
    //if (m_audioIconDisplayed && event->button() == Qt::LeftButton && m_audioIconRect.contains(event->pos())) {
    //    m_tab->toggleMuted();
    //    return;
    //}

    QWidget::mousePressEvent(event);
}
