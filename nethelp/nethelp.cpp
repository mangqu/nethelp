#include "nethelp.h"
#include <QGridLayout>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QTextBrowser>
#include <QHostInfo>
#include <QtNetwork>

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

    prottypeLabel = new QLabel(tr("(1)协议类型"));
    prottypeComboBox = new QComboBox();
    prottypeComboBox->addItem(tr("UDP"));
    prottypeComboBox->addItem(tr("TCP Server"));
    prottypeComboBox->addItem(tr("TCP Client"));

    connect(prottypeComboBox, SIGNAL(activated(QString)),
            this, SLOT(netconfgroupUpdata()));

    addrLabel = new QLabel(tr("(2)本地IP地址"));
    //find out IP addresses of this machine
    QString localhostname = QHostInfo::localHostName();
    QString ipaddress;
    QHostInfo info = QHostInfo::fromName(localhostname);
    foreach (QHostAddress address, info.addresses())
    {
        if (address.protocol() == QAbstractSocket::IPv4Protocol)
        {
            ipaddress = address.toString();
            qDebug() << address.toString();
            break;
        }
    }
    ipaddrLineEdit = new QLineEdit(ipaddress);

    portLabel = new QLabel(tr("(3)本地端口号"));
    portLineEdit = new QLineEdit(tr("8080"));

    linkPushButton = new QPushButton(tr("连接"));

    connect(linkPushButton, SIGNAL(clicked(bool)),
            this, SLOT(newConnect()));

    //2
    QVBoxLayout* toplayout = new QVBoxLayout();
    toplayout->addWidget(prottypeLabel);
    toplayout->addWidget(prottypeComboBox);

    QVBoxLayout* middlelayout = new QVBoxLayout();
    middlelayout->addWidget(addrLabel);
    middlelayout->addWidget(ipaddrLineEdit);

    QVBoxLayout* bomlayout = new QVBoxLayout();
    bomlayout->addWidget(portLabel);
    bomlayout->addWidget(portLineEdit);

    QVBoxLayout* mainlayout = new QVBoxLayout();
    mainlayout->addLayout(toplayout);
    mainlayout->addLayout(middlelayout);
    mainlayout->addLayout(bomlayout);
    mainlayout->addWidget(linkPushButton);
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
    recvTextBrowser = new QTextBrowser();

    //2
    QVBoxLayout* mainlayout = new QVBoxLayout();
    mainlayout->addWidget(recvTextBrowser);
    group->setLayout(mainlayout);

    return group;
}

QGroupBox* nethelp::createdatasendGroup()
{
    //1
    QGroupBox* group = new QGroupBox();
    sendLineEdit = new QLineEdit();
    sendPushButton = new QPushButton(tr("发送"));

    //2
    QHBoxLayout* layout = new QHBoxLayout();
    layout->addWidget(sendLineEdit);
    layout->addWidget(sendPushButton);
    group->setLayout(layout);

    return group;
}

void nethelp::netconfgroupUpdata()
{
    if (prottypeComboBox->currentText() == tr("TCP Client"))
    {
        prottypeLabel->setText(tr("(1)协议类型"));
        addrLabel->setText(tr("(2)服务器IP地址"));
        portLabel->setText(tr("(3)服务器端口号"));
    }
}

void nethelp::newConnect()
{
    if (prottypeComboBox->currentText() == "TCP Client")
    {
        linkPushButton->setText(tr("关闭"));
        tcpSocket = new QTcpSocket(this);
        connect(tcpSocket, SIGNAL(readyRead()),
                this, SLOT(tcpClientreadMessage()));
        connect(sendPushButton, SIGNAL(clicked(bool)),
                this, SLOT(tcpClientsendMessage()));
        tcpSocket->abort();
        tcpSocket->connectToHost(ipaddrLineEdit->text(), portLineEdit->text().toInt());
        qDebug() << ipaddrLineEdit->text() << portLineEdit->text();
    }
    else if (prottypeComboBox->currentText() == tr("TCP Server"))
    {
        linkPushButton->setText(tr("关闭"));
        tcpServer = new QTcpServer(this);
        if (!tcpServer->listen(QHostAddress::Any, 45454))
        {
            qDebug() << tcpServer->errorString();
            close();
        }
        connect(tcpServer, SIGNAL(newConnection()),
                this, SLOT(tcpServernewConnection()));
        connect(sendPushButton, SIGNAL(clicked(bool)),
                this, SLOT(tcpServerSendMessage()));
        qDebug() << ipaddrLineEdit->text() << portLineEdit->text();
    }
    else if (prottypeComboBox->currentText() == tr("UDP"))
    {
        //1
        linkPushButton->setText(tr("关闭"));

        //2
        udpSendSocket = new QUdpSocket(this);
        connect(sendPushButton, SIGNAL(clicked(bool)),
                this, SLOT(udpSendMessage()));
        //3
        udpRecvSocket = new QUdpSocket(this);
        udpRecvSocket->bind(portLineEdit->text().toInt(), QUdpSocket::ShareAddress);
        connect(udpRecvSocket, SIGNAL(readyRead()),
                this, SLOT(udpRecvMessage()));
        qDebug() << ipaddrLineEdit->text() << portLineEdit->text();
    }
}

void nethelp::tcpClientreadMessage()
{
    QByteArray *block = new QByteArray;
    block->append(tcpSocket->readAll());
    recvTextBrowser->setText(*block);
    qDebug() << QString(*block);
}

void nethelp::tcpServerreadMessage()
{
    QByteArray * block = new QByteArray;
    block->append(clientConnection->readAll());
    recvTextBrowser->setText(*block);
    qDebug() << QString(*block);
}

void nethelp::tcpClientsendMessage()
{
    QByteArray *block = new QByteArray;
    block->append(sendLineEdit->text());
    tcpSocket->write(*block);
    delete block;
}

void nethelp::tcpServerSendMessage()
{
    QByteArray* block = new QByteArray;
    block->append(sendLineEdit->text());

    clientConnection->write(*block);
}

void nethelp::tcpServernewConnection()
{
    clientConnection = tcpServer->nextPendingConnection();
    connect(clientConnection, SIGNAL(readyRead()),
            this, SLOT(tcpServerreadMessage()));
    qDebug() << tr("tcp client connected");
}

void nethelp::udpSendMessage()
{
    QByteArray* datagram = new QByteArray;
    datagram->append(sendLineEdit->text());

    udpSendSocket->writeDatagram((*datagram).data(), (*datagram).size(),
                             QHostAddress::Broadcast, portLineEdit->text().toInt());
}

void nethelp::udpRecvMessage()
{
    while (udpRecvSocket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(udpRecvSocket->pendingDatagramSize());
        udpRecvSocket->readDatagram(datagram.data(), datagram.size());
        recvTextBrowser->setText(datagram);
    }
}

nethelp::~nethelp()
{

}
