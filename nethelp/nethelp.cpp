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

    addrLabel = new QLabel(tr("(2)本地主机地址"));
    ipaddrComboBox = new QComboBox;
    //find out IP addresses of this machine
    QList<QHostAddress> ipaddresslist = QNetworkInterface::allAddresses();
    foreach (QHostAddress address, ipaddresslist)
    {
        if (address.protocol() == QAbstractSocket::IPv4Protocol)
        {
           ipaddrComboBox->addItem(address.toString());
        }
    }
//    QString localhostname = QHostInfo::localHostName();
//    QString ipaddress;
//    QHostInfo info = QHostInfo::fromName(localhostname);
//    foreach (QHostAddress address, info.addresses())
//    {
//        if ((address.protocol() == QAbstractSocket::IPv4Protocol) &&
//                (address != QHostAddress::Null) &&
//                (address != QHostAddress::LocalHost))
//        {
//            if (address.toString().contains("127.0."))
//            {
//                continue;
//            }
//            ipaddress = address.toString();
//            qDebug() << address.toString();
//            break;
//        }
//    }
//    ipaddrLineEdit = new QLineEdit(ipaddress);

    portLabel = new QLabel(tr("(3)本地主机端口"));
    portLineEdit = new QLineEdit(tr("8080"));

    linkPushButton = new QPushButton(tr("连接"));

    connect(linkPushButton, SIGNAL(clicked(bool)),
            this, SLOT(newConnect()));

    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket, SIGNAL(readyRead()),
            this, SLOT(tcpClientreadMessage()));

    //2
    QVBoxLayout* toplayout = new QVBoxLayout();
    toplayout->addWidget(prottypeLabel);
    toplayout->addWidget(prottypeComboBox);

    QVBoxLayout* middlelayout = new QVBoxLayout();
    middlelayout->addWidget(addrLabel);
    middlelayout->addWidget(ipaddrComboBox);

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

    remoteIpLabel = new QLabel(tr("远程主机地址:"));
    remoteIpLineEdit = new QLineEdit;

    remotePortLabel = new QLabel(tr("远程主机端口号:"));
    remotePortLineEdit = new QLineEdit();

    sendLineEdit = new QLineEdit();
    sendPushButton = new QPushButton(tr("发送"));

    //2
    QHBoxLayout* topleftlayout = new QHBoxLayout;
    topleftlayout->addWidget(remoteIpLabel);
    topleftlayout->addWidget(remoteIpLineEdit);

    QHBoxLayout* toprightlayout = new QHBoxLayout;
    toprightlayout->addWidget(remotePortLabel);
    toprightlayout->addWidget(remotePortLineEdit);

    QHBoxLayout* toplayout = new QHBoxLayout;
    toplayout->addLayout(topleftlayout);
    toplayout->addStretch(1);
    toplayout->addLayout(toprightlayout);

    QHBoxLayout* bomlayout = new QHBoxLayout;
    bomlayout->addWidget(sendLineEdit);
    bomlayout->addWidget(sendPushButton);

    QVBoxLayout* mainlayout = new QVBoxLayout();
    mainlayout->addLayout(toplayout);
    mainlayout->addLayout(bomlayout);
    group->setLayout(mainlayout);

    return group;
}

void nethelp::netconfgroupUpdata()
{
    if (prottypeComboBox->currentText() == tr("TCP Client"))
    {
        prottypeLabel->setText(tr("(1)协议类型"));
        addrLabel->setText(tr("(2)远程主机地址"));
        portLabel->setText(tr("(3)远程主机端口"));
    }
    else if (prottypeComboBox->currentText() == tr("TCP Server"))
    {
        prottypeLabel->setText(tr("(1)协议类型"));
        addrLabel->setText(tr("(2)本地主机地址"));
        portLabel->setText(tr("(3)本地主机端口"));
    }
    else if (prottypeComboBox->currentText() == tr("UDP"))
    {
        prottypeLabel->setText(tr("(1)协议类型"));
        addrLabel->setText(tr("(2)本地主机地址"));
        portLabel->setText(tr("(3)本地主机端口"));
    }
}

void nethelp::newConnect()
{
    if (linkPushButton->text() == tr("连接"))
    {
        if (prottypeComboBox->currentText() == tr("TCP Client"))
        {
            linkPushButton->setText(tr("关闭"));
            connect(sendPushButton, SIGNAL(clicked(bool)),
                    this, SLOT(tcpClientsendMessage()));
            tcpSocket->abort();
            tcpSocket->connectToHost(ipaddrComboBox->currentText(), portLineEdit->text().toInt());
            qDebug() << ipaddrComboBox->currentText() << portLineEdit->text();
        }
        else if (prottypeComboBox->currentText() == tr("TCP Server"))
        {
            linkPushButton->setText(tr("关闭"));
            tcpServer = new QTcpServer(this);
            if (!tcpServer->listen(QHostAddress(ipaddrComboBox->currentText()),
                                   portLineEdit->text().toInt()))
            {
                qDebug() << tcpServer->errorString();
                close();
            }
            connect(tcpServer, SIGNAL(newConnection()),
                    this, SLOT(tcpServernewConnection()));
            connect(sendPushButton, SIGNAL(clicked(bool)),
                    this, SLOT(tcpServerSendMessage()));
            qDebug() << ipaddrComboBox->currentText() << portLineEdit->text();
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
            udpListnerSocket = new QUdpSocket(this);
            udpListnerSocket->bind(QHostAddress(ipaddrComboBox->currentText()),
                                   portLineEdit->text().toInt());
            connect(udpListnerSocket, SIGNAL(readyRead()),
                    this, SLOT(udpRecvMessage()));
            qDebug() << ipaddrComboBox->currentText() << portLineEdit->text();
        }
    }
    else if (linkPushButton->text() == tr("关闭"))
    {
        if (prottypeComboBox->currentText() == "TCP Client")
        {
            linkPushButton->setText(tr("连接"));
            qDebug() << tr("close TCP Client");
        }
        else if (prottypeComboBox->currentText() == tr("TCP Server"))
        {
            linkPushButton->setText(tr("连接"));
            qDebug() << tr("close TCP Server");
        }
        else if (prottypeComboBox->currentText() == tr("UDP"))
        {
            //1
            linkPushButton->setText(tr("连接"));
            qDebug() << tr("close UDP");
        }
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
    qDebug() << *block;
    tcpSocket->write(*block);
    delete block;
}

void nethelp::tcpServerSendMessage()
{
    QByteArray* block = new QByteArray;
    block->clear();
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

    udpSendSocket->writeDatagram((*datagram),
                                 QHostAddress(remoteIpLineEdit->text()),
                                 remotePortLineEdit->text().toInt());
}

void nethelp::udpRecvMessage()
{
    qDebug() << tr("udpRecvMessage");
    while (udpListnerSocket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(udpListnerSocket->pendingDatagramSize());
        udpListnerSocket->readDatagram(datagram.data(), datagram.size());
        recvTextBrowser->setText(datagram);
    }
}

nethelp::~nethelp()
{

}
