#include "mainwindow.h"
#include "udpsocketmanager.h"

#include <QApplication>
#include <QTcpSocket>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    MainWindow   w;

    UdpSocketManager client;
    // client.Run();
    client.get_uddp_Data();
    // QTcpSocket* tcpSocket = new QTcpSocket(this);
    // tcpSocket->connectToHost("127.0.0.5", 8080);

    QTcpSocket _socket;
    quint16    _serverPort = 8080;
    QString    _serverIP   = "127.0.0.5";

    _socket.connectToHost(_serverIP, _serverPort);
    if (!_socket.waitForConnected(2000)) {
        qDebug() << "Connection failed:" << _socket.errorString();
    }
    qDebug() << "[try] " << "Connect " << _serverIP << ":" << _serverPort << "...";

    //  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    QString message = "this->_generater.Run()";
    qDebug() << "MessageIS " << message;
    //  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    _socket.write(message.toUtf8());
    _socket.flush();

    if (_socket.waitForReadyRead(3000)) {
        QByteArray response = _socket.readAll();
        qDebug() << "Server Anser :" << QString::fromUtf8(response);
        _socket.close();
        qDebug() << " ~~~~~~~~~~~~~~~~~~~~~ << finish >> ~~~~~~~~~~~~~~~~~~~~~ ";
    } else {
        qDebug() << "time out from server";
        _socket.close();
    }

    qDebug() << "**************";

    w.show();
    return a.exec();
}
