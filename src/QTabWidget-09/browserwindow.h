#ifndef browserwindow_h__
#define browserwindow_h__

#include <QWidget>

class BrowserWindow : public QWidget
{
    Q_OBJECT
public:
    BrowserWindow(QWidget* parent = nullptr);
};


#endif // browserwindow_h__
