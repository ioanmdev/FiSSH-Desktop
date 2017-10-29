#ifndef NETWORK_H
#define NETWORK_H

#include <QSslSocket>
#include <QSslError>
#include <QTcpServer>

class network : public QTcpServer
{

public:
    virtual void incomingConnection(qintptr socketDescriptor);
};
#endif // NETWORK_H
