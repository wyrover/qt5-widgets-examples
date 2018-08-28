#ifndef TAGLABEL_H
#define TAGLABEL_H

#include <QWidget>

class QLabel;
class QPushButton;


class TagLabel : public QWidget
{
    Q_OBJECT

public:
    explicit TagLabel(const QString& text, const QString& bkcolor, const QString& icon_filename, QWidget *parent = 0);
    explicit TagLabel(QWidget *parent = 0);
    ~TagLabel();

	void setText(const QString& text);

signals:
	void removalRequested(const QString &text);

private:
    void setupUI();
    void updateUI();

private:
    QString text_;
	QString bkcolor_;
	QString icon_filename_;
    QLabel* label_;
    QPushButton* close_button_;
};

#endif // TAGLABEL_H
