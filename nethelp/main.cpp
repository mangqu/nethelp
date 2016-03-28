#include "nethelp.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    nethelp w;
    w.show();

    return a.exec();
}
