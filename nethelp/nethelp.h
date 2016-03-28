#ifndef NETHELP_H
#define NETHELP_H

#include <QWidget>
#include <QGroupBox>

class nethelp : public QWidget
{
    Q_OBJECT

public:
    nethelp(QWidget *parent = 0);
    ~nethelp();

private:
    QGroupBox* createnetconfGroup();
    QGroupBox* createrecvconfGroup();
    QGroupBox* createsendconfGroup();
    QGroupBox* createdatarecvGroup();
    QGroupBox* createdatasendGroup();
};

#endif // NETHELP_H
