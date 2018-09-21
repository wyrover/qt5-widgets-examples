#include "TestDialog.h"
#include "ui_TestDialog.h"
#include "CusButtonGroup.h"
#include <QPushButton>
#include <QGridLayout>
#include <QMainWindow>

TestDialog::TestDialog(QWidget * parent, Qt::WindowFlags f)
    : QDialog(parent, f)
    , m_ui(new Ui::TestDialog)
{
    m_ui->setupUi(this);
    setWindowFlags(windowFlags() | Qt::WindowMinMaxButtonsHint);
    QGridLayout* lay = dynamic_cast<QGridLayout*>(m_ui->centerWidget->layout());

    if (!lay) {
        lay = new QGridLayout(m_ui->centerWidget);
        lay->setSpacing(0);
        lay->setContentsMargins(0, 0, 0, 0);
    }

    //下划线高度默认2像素，颜色也是默认，位置默认在北方
    m_cusButtonGroup = new CusButtonGroup;
    //设置下划线颜色
    m_cusButtonGroup->setButtonColor(QColor(255, 163, 69));
    //设置下划线高度
    m_cusButtonGroup->setLineHeight(4);
    //设置下划线高度
    m_cusButtonGroup->setButtonPosition(CusButtonGroup::East);

    for (int index = 0; index < 6; ++index) {
        QPushButton *btn = new QPushButton;
        btn->setCheckable(true);
        btn->setText(QString("Button_%1").arg(index));
        btn->setFixedSize(80, 32);
        m_cusButtonGroup->addButton(btn, index);
    }

    lay->addWidget(m_cusButtonGroup);
}

TestDialog::~TestDialog()
{
}