#ifndef AUTHWINDOW_H
#define AUTHWINDOW_H

#include <QMainWindow>
#include "network.h"

/// Configuration
#define PORT 2222
const QString key = "/opt/FiSSH/key.pem";
const QString certificate = "/opt/FiSSH/certificate.pem";

namespace Ui {
class AuthWindow;
}

class AuthWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AuthWindow(QWidget *parent = 0);
    ~AuthWindow();

public slots:
    void time_keeper();

protected slots:
    void acceptConnection();
    void handshakeComplete();
    void receiveMessage();
    void connectionClosed();
    void connectionFailure();

private:
    void ShowMessage(QString);

    Ui::AuthWindow *ui;
    QTimer *timeout;
    network server;
    QList<QSslSocket *> sockets;
};

#endif // AUTHWINDOW_H
