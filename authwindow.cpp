#include "authwindow.h"
#include "ui_authwindow.h"

#include <QTimer>
#include <QMessageBox>
#include <QTextStream>
#include <cassert>

QTextStream out(stdout);
QTextStream in(stdin);

void AuthWindow::ShowMessage(QString m)
{
    QMessageBox* msg = new QMessageBox(this);
    msg->setText(m);
    msg->exec();
}

AuthWindow::AuthWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AuthWindow)
{
    ui->setupUi(this);
    timeout = new QTimer(this);
    connect(timeout, SIGNAL(timeout()), this, SLOT(time_keeper()));
    timeout->setInterval(300);
    timeout->start();
    connect(&server, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
    server.listen(QHostAddress::Any, PORT);
}


AuthWindow::~AuthWindow()
{
    if (server.isListening())
    {
        server.close();
    }

    foreach (QSslSocket *socket, sockets)
    {
        delete socket;
    }
    delete timeout;
    delete ui;
}

void AuthWindow::time_keeper()
{
    if (ui->prgTimeLeft->value() != 100)
        ui->prgTimeLeft->setValue(ui->prgTimeLeft->value() + 1);
    else {
        ShowMessage("Sorry, the authorization timed out!");
        QApplication::exit(1);
    }
}




// Accept connection and initiate the SSL handshake
void AuthWindow::acceptConnection()
{
  QSslSocket *socket = dynamic_cast<QSslSocket *>(server.nextPendingConnection());
  assert(socket);

  // QSslSocket emits the encrypted() signal after the encrypted connection is established
  connect(socket, SIGNAL(encrypted()), this, SLOT(handshakeComplete()));

  // Fail on ERROR
  connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(connectionFailure()));

  socket->setPrivateKey(key);
  socket->setLocalCertificate(certificate);

  socket->setPeerVerifyMode(QSslSocket::VerifyNone);
  socket->startServerEncryption();
}

// Check that the SSL handshake has completed successfully
void AuthWindow::handshakeComplete()
{
  QSslSocket *socket = dynamic_cast<QSslSocket *>(sender());
  assert(socket);

  connect(socket, SIGNAL(disconnected()), this, SLOT(connectionClosed()));
  connect(socket, SIGNAL(readyRead()), this, SLOT(receiveMessage()));

  sockets.push_back(socket);
}

// Receive the key
void AuthWindow::receiveMessage()
{
  QSslSocket *socket = dynamic_cast<QSslSocket *>(sender());
  assert(socket);

  if (socket->canReadLine())
  {
    QByteArray message = socket->readLine();
    timeout->stop();

    out << message.constData();
    QApplication::exit();
  }
}

// Close connection
void AuthWindow::connectionClosed()
{
  QSslSocket *socket = dynamic_cast<QSslSocket *>(sender());
  assert(socket);

  sockets.removeOne(socket);
  socket->disconnect();
  socket->deleteLater();
}

// Error checks

void AuthWindow::connectionFailure()
{
  QSslSocket *socket = dynamic_cast<QSslSocket *>(sender());
  assert(socket);

  sockets.removeOne(socket);
  socket->disconnect();
  socket->deleteLater();
}


