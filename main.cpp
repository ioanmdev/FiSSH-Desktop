#include "authwindow.h"
#include <QApplication>
#include <QSslSocket>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AuthWindow w;
    w.show();

    // Check if SSL supported, otherwise abort
    if (QSslSocket::supportsSsl())
        return a.exec();
    else
        return -1;
}
