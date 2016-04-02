#ifndef NETHELP_H
#define NETHELP_H

#include <QWidget>
#include <QGroupBox>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QtNetwork>
#include <QTextBrowser>

class nethelp : public QWidget
{
    Q_OBJECT

public:
    nethelp(QWidget *parent = 0);
    ~nethelp();

public slots:
    void netconfgroupUpdata();
    void newConnect();
    void tcpClientreadMessage();
    void tcpServerreadMessage();
    void tcpClientsendMessage();
    void tcpServerSendMessage();
    void tcpServernewConnection();
    void udpSendMessage();
    void udpRecvMessage();

private:
    QLabel* prottypeLabel;
    QComboBox* prottypeComboBox;
    QLabel* addrLabel;
    QLineEdit* ipaddrLineEdit;
    QLabel* portLabel;
    QLineEdit* portLineEdit;
    QPushButton* linkPushButton;
    QLineEdit* sendLineEdit;
    QPushButton* sendPushButton;
    QTextBrowser* recvTextBrowser;

    QTcpSocket* tcpSocket;
    QString message;
    QTcpServer* tcpServer;
    QTcpSocket* clientConnection;
    QUdpSocket* udpSendSocket;
    QUdpSocket* udpRecvSocket;

    QGroupBox* createnetconfGroup();
    QGroupBox* createrecvconfGroup();
    QGroupBox* createsendconfGroup();
    QGroupBox* createdatarecvGroup();
    QGroupBox* createdatasendGroup();
};

#endif // NETHELP_H
