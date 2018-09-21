#include "rqttest.h"

RQtTest::RQtTest(RInside & R) : m_R(R)
{
    createDockWindows();
    std::string initcode = "library(RSVGTipsDevice)";
    m_R.parseEvalQ(initcode);
}

void RQtTest::createDockWindows()
{
    QString css1 = tr("::title { font-size:8pt; position: relative; text-align:center }");
    QString css2 = css1 + tr("QTextEdit { margin:0 5 }");
    QFont f("unexistent");
    f.setStyleHint(QFont::Monospace);
    dockin = new QDockWidget(tr("Input"), this);
    dockout = new QDockWidget(tr("Output"), this);
    dockplot = new QDockWidget(tr("Plot"), this);
    dockin->setStyleSheet(css2);
    dockout->setStyleSheet(css2);
    dockplot->setStyleSheet(css1);
    // Input
    input = new QTextEdit(dockin);
    input->setFont(f);
    input->setText(tr("# input R code and press F5\n"));
    input->setFrameShape(QFrame::NoFrame);
    // Input Tab Space
    QFontMetrics metrics(f);
    input->setTabStopWidth(tabStop * metrics.width(' '));
    QTextCursor tmpCursor(input->textCursor());
    tmpCursor.movePosition(QTextCursor::End);
    input->setTextCursor(tmpCursor);
    dockin->setWidget(input);
    // Output
    output = new QTextEdit(dockout);
    output->setReadOnly(true);
    output->setFont(f);
    output->setText("# Result will appear here");
    output->setFrameShape(QFrame::NoFrame);
    dockout->setWidget(output);
    dockplot->setMinimumWidth(plotMinWidth);
    dockplot->setMinimumHeight(plotMinHeight);
    dockplot->installEventFilter(this);
    addDockWidget(Qt::LeftDockWidgetArea, dockin);
    addDockWidget(Qt::RightDockWidgetArea, dockout);
    addDockWidget(Qt::RightDockWidgetArea, dockplot);
    setWindowTitle(tr("R console & plot by Qt"));
    createMenus();
    prepareStatuBar();
}

void RQtTest::createMenus()
{
    QAction *changeViewScreenAct = new QAction(tr("&Fullscreen"), this);
    changeViewScreenAct->setCheckable(true);
    connect(changeViewScreenAct, SIGNAL(toggled(bool)), this, SLOT(changeViewScreen(bool)));
    QMenu *viewMenu = menuBar()->addMenu(tr("&View"));
    viewMenu->addAction(dockin->toggleViewAction());
    viewMenu->addAction(dockout->toggleViewAction());
    viewMenu->addAction(dockplot->toggleViewAction());
    viewMenu->addSeparator();
    viewMenu->addAction(changeViewScreenAct);
    QAction *viewPlotSizeAct = new QAction(tr("&Plot Size"), this);
    QAction *viewResultInfoAct = new QAction(tr("&Result Info"), this);
    QAction *hideStatusBarAct = new QAction(tr("&Hide"), this);
    viewPlotSizeAct->setCheckable(true);
    viewResultInfoAct->setCheckable(true);
    hideStatusBarAct->setCheckable(true);
    viewPlotSizeAct->setChecked(true);
    QMenu *subMenuStatusBar = viewMenu->addMenu(tr("&Status Bar"));
    subMenuStatusBar->addAction(viewPlotSizeAct);
    subMenuStatusBar->addAction(viewResultInfoAct);
    subMenuStatusBar->addAction(hideStatusBarAct);
    QActionGroup *changeStatusBarActGroup = new QActionGroup(this);
    changeStatusBarActGroup->addAction(viewPlotSizeAct);
    changeStatusBarActGroup->addAction(viewResultInfoAct);
    changeStatusBarActGroup->addAction(hideStatusBarAct);
    changeStatusBarActGroup->setExclusive(true);
    connect(viewPlotSizeAct, SIGNAL(toggled(bool)), this, SLOT(viewPlotSize(bool)));
    connect(viewResultInfoAct, SIGNAL(toggled(bool)), this, SLOT(viewResultInfo(bool)));
    connect(hideStatusBarAct, SIGNAL(toggled(bool)), this, SLOT(hideStatusBar(bool)));
}

void RQtTest::prepareStatuBar()
{
    labelStatusBar = new QLabel;
    statusBar()->setStyleSheet(tr("QStatusBar::item { border: 0 } ")
                               + tr("QWidget { font-family:monospace; font-size: 9pt; margin:0 5 }"));
    statusBar()->addPermanentWidget(labelStatusBar);
    statusBarMode = 1;
    setStatusInfo();
    resultInfo = "Ready";
}

bool RQtTest::eventFilter(QObject *obj, QEvent *ev)
{
    if (obj == dockplot && ev->type() == QEvent::Resize)
        setStatusInfo();

    return QWidget::eventFilter(obj, ev);
}

void RQtTest::keyPressEvent(QKeyEvent *ev)
{
    QMainWindow::keyPressEvent(ev);

    if (ev->key() == Qt::Key_F5)
        runCmd();
}

void RQtTest::changeViewScreen(bool value)
{
    if (value)
        showFullScreen();
    else
        showNormal();
}

void RQtTest::setStatusInfo()
{
    switch (statusBarMode) {
    case 0:
        break;

    case 1: {
        QString s = tr("PlotArea ")
                    + QString::number(dockplot->width()) + " x "
                    + QString::number(dockplot->height()) + " px";

        if (!svgString.isNull()) {
            QRegExp rx("<svg.+width=\"(.+\" height=\".+)\"");
            rx.setMinimal(true);
            rx.indexIn(svgString);
            s = s + " ; ViewPort " + rx.cap(1).replace("\" height=\"", " x ") + tr(" px");
        }

        labelStatusBar->setText(s);
        break;
    }

    case 2:
        labelStatusBar->setText(resultInfo);
        break;
    }
}

void RQtTest::viewPlotSize(bool value)
{
    if (value)
        statusBarMode = 1;

    setStatusInfo();
    statusBar()->show();
}

void RQtTest::viewResultInfo(bool value)
{
    if (value)
        statusBarMode = 2;

    setStatusInfo();
    statusBar()->show();
}

void RQtTest::hideStatusBar(bool value)
{
    if (value)
        statusBarMode = 0;

    statusBar()->hide();
}

void RQtTest::runCmd(void)
{
    QElapsedTimer et;
    et.start();
    QFont f = output->font();
    int outputchars = output->width() / f.pointSize();
    float plotwidth_inch = dockplot->width() * shrinkWidth / pixelToInch;
    float plotheight_inch = dockplot->height() * shrinkWidth / pixelToInch;
    QTemporaryFile tempin;
    QTemporaryFile tempout;
    QTemporaryFile tempsvg;

    if (!tempin.open() || !tempout.open() || !tempsvg.open())
        return;

    QString r_cmd = "try({"
                    + tr("sink('") + tempout.fileName() + "');"
                    + "options(width=" + QString::number(outputchars) + ");"
                    + "devSVGTips("
                    + "height=" + QString::number(plotheight_inch) + ","
                    + "width=" + QString::number(plotwidth_inch) + ","
                    + "file='" + tempsvg.fileName() + "',"
                    + "onefile=F, title='', toolTipMode=0);"
                    + "source('" + tempin.fileName() + "');"
                    + "dev.off();"
                    + "sink();"
                    + "})";
    QString r_src;
    QTextCursor cursor(input->textCursor());

    if (cursor.hasSelection())
        r_src = cursor.selectedText().replace(QString::fromWCharArray(L"\u2029"), "\n");
    else
        r_src = input->toPlainText();

    QRegExp rx("/\\*.*\\*/");
    rx.setMinimal(true);
    r_src.replace(rx, QObject::tr(""));
    tempin.write(r_src.toUtf8());
    tempin.close();
    m_R.parseEvalQ(r_cmd.toStdString());
    int outsize = tempout.size();

    if (outsize > 0)
        output->setPlainText(tempout.readAll());

    QTextStream in(& tempsvg);
    svgString = in.readAll();
    QString s = "\n<desc>R SVG Plot!</desc>\n"
                + tr("<rect width=\"100%\" height=\"100%\" style=\"fill:#FFFFFF\"/>\n");
    svgString.replace(s, "");
    int svgsize = tempsvg.size();
    setSvg();
    resultInfo = QString::number(et.elapsed()) + " ms ; ";

    if (outsize > 0 || svgsize > 0) {
        resultInfo = resultInfo
                     + QString::number(outsize) + " bytes output ; "
                     + QString::number(svgsize) + " bytes SVG";
    } else {
        resultInfo = resultInfo + "no output and SVG";
    }

    setStatusInfo();
}

void RQtTest::setSvg()
{
    QStringList list;
    QRegExp rx("(<svg[^>]+>.+</svg>)");
    rx.setMinimal(true);
    int cnt = 0;
    int pos = 0;

    while ((pos = rx.indexIn(svgString, pos)) != -1) {
        list << rx.cap(1);
        cnt ++;
        pos += rx.matchedLength();
    }

    if (cnt == 0)
        return;

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->setContentsMargins(0, 0, 0, 0);
    vLayout->setSpacing(0);
    QSvgWidget *plot;

    for (int i = 0; i < list.size(); i++) {
        plot = new QSvgWidget(dockplot);
        plot->load(list[i].toUtf8());
        vLayout->addWidget(plot);
    }

    int tempWidth = dockplot->width() * shrinkWidth;
    int tempHeight = dockplot->height() * shrinkWidth * cnt;
    QWidget *tempLayout = new QWidget;
    tempLayout->setMinimumWidth(tempWidth);
    tempLayout->setMaximumWidth(tempWidth);
    tempLayout->setMinimumHeight(tempHeight);
    tempLayout->setMaximumHeight(tempHeight);
    tempLayout->setLayout(vLayout);
    QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setAlignment(Qt::AlignHCenter);
    scrollArea->setWidget(tempLayout);
    scrollArea->setStyleSheet(tr("QScrollArea { background-color:white }"));
    tempLayout->setStyleSheet(tr("QWidget { background-color:white }"));
    scrollArea->setFrameShape(QFrame::NoFrame);
    dockplot->setWidget(scrollArea);
}
