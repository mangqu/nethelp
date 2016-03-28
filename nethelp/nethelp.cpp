#include "nethelp.h"
#include <QGridLayout>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QTextBrowser>

nethelp::nethelp(QWidget *parent)
    : QWidget(parent)
{
    //1
    QGridLayout* grid = new QGridLayout;
    grid->addWidget(createnetconfGroup(), 0, 0);
    grid->addWidget(createrecvconfGroup(), 1, 0);
    grid->addWidget(createsendconfGroup(), 2, 0);
    grid->addWidget(createdatarecvGroup(), 0, 1);
    grid->addWidget(createdatasendGroup(), 1, 1);
    setLayout(grid);
}

QGroupBox* nethelp::createnetconfGroup()
{
    //1
    QGroupBox* groupBox = new QGroupBox(tr("网络设置"));

    QLabel* label1 = new QLabel(tr("(1)协议类型"));
    QComboBox* comboBox = new QComboBox();
    comboBox->addItem(tr("UDP"));
    comboBox->addItem(tr("TCP Server"));
    comboBox->addItem(tr("TCP Client"));

    QLabel* label2 = new QLabel(tr("本地IP地址"));
    QLineEdit* lineEdit1 = new QLineEdit();

    QLabel* label3 = new QLabel(tr("本地端口号"));
    QLineEdit* lineEdit2 = new QLineEdit();

    QPushButton* pushbutton = new QPushButton(tr("连接"));

    //2
    QVBoxLayout* toplayout = new QVBoxLayout();
    toplayout->addWidget(label1);
    toplayout->addWidget(comboBox);
    toplayout->addStretch(1);

    QVBoxLayout* middlelayout = new QVBoxLayout();
    middlelayout->addWidget(label2);
    middlelayout->addWidget(lineEdit1);
    middlelayout->addStretch(1);

    QVBoxLayout* bomlayout = new QVBoxLayout();
    bomlayout->addWidget(label3);
    bomlayout->addWidget(lineEdit2);

    QVBoxLayout* mainlayout = new QVBoxLayout();
    mainlayout->addLayout(toplayout);
    mainlayout->addLayout(middlelayout);
    mainlayout->addLayout(bomlayout);
    mainlayout->addWidget(pushbutton);
    groupBox->setLayout(mainlayout);

    return groupBox;
}

QGroupBox* nethelp::createrecvconfGroup()
{
    //1
    QGroupBox* groupBox = new QGroupBox(tr("接收区设置"));

    QRadioButton* radio1 = new QRadioButton(tr("接收转向文件"));
    QRadioButton* radio2 = new QRadioButton(tr("显示接收时间"));
    QRadioButton* radio3 = new QRadioButton(tr("十六进制显示"));
    QRadioButton* radio4 = new QRadioButton(tr("暂停接收显示"));

    //2
    QVBoxLayout* mainlayout = new QVBoxLayout;
    mainlayout->addWidget(radio1);
    mainlayout->addWidget(radio2);
    mainlayout->addWidget(radio3);
    mainlayout->addWidget(radio4);
    groupBox->setLayout(mainlayout);

    return groupBox;
}

QGroupBox* nethelp::createsendconfGroup()
{
    //1
    QGroupBox* groupBox = new QGroupBox(tr("发送区设置"));

    QRadioButton* radio1 = new QRadioButton(tr("启用文件数据源"));
    QRadioButton* radio2 = new QRadioButton(tr("自动发送附加位"));
    QRadioButton* radio3 = new QRadioButton(tr("发送完自动清空"));
    QRadioButton* radio4 = new QRadioButton(tr("按十六进制发送"));
    QRadioButton* radio5 = new QRadioButton(tr("数据流循环发送"));

    //2
    QVBoxLayout* mainlayout = new QVBoxLayout();
    mainlayout->addWidget(radio1);
    mainlayout->addWidget(radio2);
    mainlayout->addWidget(radio3);
    mainlayout->addWidget(radio4);
    mainlayout->addWidget(radio5);
    groupBox->setLayout(mainlayout);

    return groupBox;
}

QGroupBox* nethelp::createdatarecvGroup()
{
    //1
    QGroupBox* group = new QGroupBox(tr("网络数据接收"));
    QTextBrowser* text = new QTextBrowser();

    //2
    QVBoxLayout* mainlayout = new QVBoxLayout();
    mainlayout->addWidget(text);
    group->setLayout(mainlayout);

    return group;
}

QGroupBox* nethelp::createdatasendGroup()
{
    //1
    QGroupBox* group = new QGroupBox();
    QLineEdit* lineedit = new QLineEdit();
    QPushButton* pushbutton = new QPushButton(tr("发送"));

    //2
    QHBoxLayout* layout = new QHBoxLayout();
    layout->addWidget(lineedit);
    layout->addWidget(pushbutton);
    group->setLayout(layout);

    return group;
}

nethelp::~nethelp()
{

}
