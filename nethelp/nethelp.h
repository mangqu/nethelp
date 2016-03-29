#ifndef NETHELP_H
#define NETHELP_H

#include <QWidget>
#include <QGroupBox>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QtNetwork>

class nethelp : public QWidget
{
    Q_OBJECT

public:
    nethelp(QWidget *parent = 0);
    ~nethelp();

public slots:
    void newConnect();
    void readMessage();
    void sendMessage();

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

    QTcpSocket* tcpSocket;
    QString message;
    QTcpServer* tcpServer;

    QGroupBox* createnetconfGroup();
    QGroupBox* createrecvconfGroup();
    QGroupBox* createsendconfGroup();
    QGroupBox* createdatarecvGroup();
    QGroupBox* createdatasendGroup();

    void tcpClientsendMessage();
    void tcpServerSendMessage();
    void udpSendMessage();
};

#endif // NETHELP_H
