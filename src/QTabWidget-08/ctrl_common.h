#ifndef ctrl_common_h__
#define ctrl_common_h__


#include <QTabBar>
#include <QScrollBar>
#include <QAbstractButton>
#include <QEasingCurve>
#include <QStyleOption>
#include <QQueue>
#include <QWidget>
#include <QImage>
#include <QFileDialog>
#include <QStylePainter>
#include <QToolButton>
#include <QTimer>
#include <QPointer>
#include <QLabel>

#ifndef QSL
#define QSL(x) QStringLiteral(x)
#endif

#ifndef QL1S
#define QL1S(x) QLatin1String(x)
#endif

#ifndef QL1C
#define QL1C(x) QLatin1Char(x)
#endif


class QSslCertificate;
class QFontMetrics;
class QPixmap;
class QIcon;
class QWidget;
class QUrl;

class QzTools
{
public:
    static QByteArray pixmapToByteArray(const QPixmap &pix);
    static QPixmap pixmapFromByteArray(const QByteArray &data);
    static QUrl pixmapToDataUrl(const QPixmap &pix);
    static QPixmap dpiAwarePixmap(const QString &path);

    static QString readAllFileContents(const QString &filename);
    static QByteArray readAllFileByteContents(const QString &filename);

    static void centerWidgetOnScreen(QWidget* w);
    static void centerWidgetToParent(QWidget* w, QWidget* parent);

    static bool removeRecursively(const QString &filePath);
    static bool copyRecursively(const QString &sourcePath, const QString &targetPath);

    static QString samePartOfStrings(const QString &one, const QString &other);
    static QString urlEncodeQueryString(const QUrl &url);
    static QString fromPunycode(const QString &str);
    static QString escapeSqlGlobString(QString urlString);

    static QString ensureUniqueFilename(const QString &name, const QString &appendFormat = QSL("(%1)"));
    static QString getFileNameFromUrl(const QUrl &url);
    static QString filterCharsFromFilename(const QString &name);

    static QString lastPathForFileDialog(const QString &dialogName, const QString &fallbackPath);
    static void saveLastPathForFileDialog(const QString &dialogName, const QString &path);

    static QString alignTextToWidth(const QString &string, const QString &text, const QFontMetrics &metrics, int width);
    static QString fileSizeToString(qint64 size);

    static QPixmap createPixmapForSite(const QIcon &icon, const QString &title, const QString &url);
    static QString applyDirectionToPage(QString &pageContents);
    static QString truncatedText(const QString &text, int size);

    static QString resolveFromPath(const QString &name);
    static QStringList splitCommandArguments(const QString &command);
    static bool startExternalProcess(const QString &executable, const QString &args);

    static QRegion roundedRect(const QRect &rect, int radius);
    static QIcon iconFromFileName(const QString &fileName);
    static bool isUtf8(const char* string);

    static bool containsSpace(const QString &str);

    // QFileDialog static functions that remembers last used directory
    static QString getExistingDirectory(const QString &name, QWidget* parent = 0, const QString &caption = QString(), const QString &dir = QString(), QFileDialog::Options options = QFileDialog::ShowDirsOnly);
    static QString getOpenFileName(const QString &name, QWidget* parent = 0, const QString &caption = QString(), const QString &dir = QString(), const QString &filter = QString(), QString* selectedFilter = 0, QFileDialog::Options options = 0);
    static QStringList getOpenFileNames(const QString &name, QWidget* parent = 0, const QString &caption = QString(), const QString &dir = QString(), const QString &filter = QString(), QString* selectedFilter = 0, QFileDialog::Options options = 0);
    static QString getSaveFileName(const QString &name, QWidget* parent = 0, const QString &caption = QString(), const QString &dir = QString(), const QString &filter = QString(), QString* selectedFilter = 0, QFileDialog::Options options = 0);

    static bool matchDomain(const QString &pattern, const QString &domain);
    static QKeySequence actionShortcut(QKeySequence shortcut, QKeySequence fallBack, QKeySequence shortcutRtl = QKeySequence(), QKeySequence fallbackRtl = QKeySequence());

    static QString operatingSystem();
    static QString cpuArchitecture();
    static QString operatingSystemLong();

    static void setWmClass(const QString &name, const QWidget* widget);

    template <typename T>
    static bool containsIndex(const T &container, int index)
    {
        return (index >= 0 && container.count() > index);
    }

    static void paintDropIndicator(QWidget *widget, const QRect &r);
};

#endif // ctrl_common_h__
