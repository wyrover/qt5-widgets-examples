#ifndef RQTTEST_H
#define RQTTEST_H

#include <RInside.h>

#include <QtGui>
#include <QMainWindow>
#include <QMenu>
#include <QTime>
#include <QWidget>
#include <QtWidgets>
#include <QTextEdit>
#include <QTextCursor>
#include <QTemporaryFile>
#include <QSvgWidget>
#include <QDockWidget>
#include <QKeyEvent>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QElapsedTimer>

class RQtTest : public QMainWindow
{
    Q_OBJECT

public:
    RQtTest(RInside & R);

private:
    void createDockWindows();
    void createMenus();
    void prepareStatuBar();
    void preparePlotArea();
    void runCmd();
    void setSvg();
    void keyPressEvent(QKeyEvent * ev);
    void setStatusInfo();
    bool eventFilter(QObject *obj, QEvent *ev);

    QDockWidget *dockin;
    QDockWidget *dockout;
    QDockWidget *dockplot;
    QTextEdit *input;
    QTextEdit *output;
    QString svgString;
    QString resultInfo;
    QLabel *labelStatusBar;
    int statusBarMode;

    static const int tabStop = 4;
    static const int plotMinWidth = 250;
    static const int plotMinHeight = 250;
    static const float pixelToInch = 72.27; // not 72.0, Tex point
    static const float shrinkWidth = 0.9;

    RInside & m_R;

private slots:
    void changeViewScreen(bool value);
    void viewPlotSize(bool value);
    void viewResultInfo(bool value);
    void hideStatusBar(bool value);
};

#endif
