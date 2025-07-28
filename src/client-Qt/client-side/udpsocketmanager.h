#ifndef UDPSOCKETMANAGER_H
#define UDPSOCKETMANAGER_H

#include <QObject>
#include <QUdpSocket>

class UdpSocketManager : public QObject
{
    Q_OBJECT

public:
    UdpSocketManager();
    ~UdpSocketManager();

    void Run();
    void get_uddp_Data();

private slots:
    void discoverServerAddress();
    void shwoUdpData();

private:
    void bindToAnyAddress(quint16 port);
    void bindTODataAddrass(quint16 port);

    QUdpSocket*             m_socket;
    QMetaObject::Connection m_Connection;

    QUdpSocket* m_socket_Data;
};

#endif // UDPSOCKETMANAGER_H
