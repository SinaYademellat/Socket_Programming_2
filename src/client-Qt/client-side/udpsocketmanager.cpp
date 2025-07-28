#include "udpsocketmanager.h"

#include <QDebug>
#include <QHostAddress>
#include <QJsonDocument>
#include <QJsonObject>

UdpSocketManager::UdpSocketManager()
{
    m_socket      = new QUdpSocket();
    m_socket_Data = new QUdpSocket();
}

UdpSocketManager::~UdpSocketManager()
{
    m_socket->close();
    delete m_socket;
}

void UdpSocketManager::Run()
{
    this->bindToAnyAddress(12345);
}

void UdpSocketManager::get_uddp_Data()
{
    this->bindTODataAddrass(8081);
}

// ------------------------------------

void UdpSocketManager::discoverServerAddress()
{
    bool flag = true;
    while (flag) {
        if (m_socket->hasPendingDatagrams()) {
            QByteArray datagram;
            datagram.resize(int(m_socket->pendingDatagramSize()));
            m_socket->readDatagram(datagram.data(), datagram.size());
            qDebug() << "Received server datagram:" << datagram;

            QJsonParseError parseError;
            QJsonDocument   doc = QJsonDocument::fromJson(datagram, &parseError);
            if (parseError.error != QJsonParseError::NoError) {
                qDebug() << "JSON parse error:" << parseError.errorString();
            }

            if (doc.isObject()) {
                QJsonObject obj = doc.object();
                qDebug() << "Original JSON Object:" << obj;

                qDebug() << " -------------- ";
                qDebug() << obj["Code"].toString();
                qDebug() << obj["Ip"].toString();
                qDebug() << obj["Port"].toInt();
                qDebug() << " -------------- ";
            }
            flag = false;
        } else {
            qDebug() << "Zero datagram is waiting to be read";
            flag = false;
        }
    }

    qDebug() << "%%%%%%%%%%%%%%%%%%%";
    QObject::disconnect(m_Connection);
}

void UdpSocketManager::shwoUdpData()
{
    if (m_socket_Data->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(int(m_socket_Data->pendingDatagramSize()));
        m_socket_Data->readDatagram(datagram.data(), datagram.size());
        qDebug() << "@@ Received server datagram:" << datagram;
    } else {
        qDebug() << "@@ Zero datagram is waiting to be read";
    }
}

// ------------------------------------

void UdpSocketManager::bindToAnyAddress(quint16 port)
{
    if (m_socket->bind(QHostAddress::Any, port)) {
        qDebug() << "[UDP]Successfully bind . port: " << port;
        m_Connection = connect(m_socket, &QUdpSocket::readyRead, this, &UdpSocketManager::discoverServerAddress);
    } else {
        qDebug() << "[UDP] Failed bind. port: " << port;
    }
}

// ------------------------------------


void UdpSocketManager::bindTODataAddrass(quint16 port)
{
    QHostAddress bindAddress("127.0.0.5");

    if (m_socket_Data->bind(bindAddress, port)) {
        qDebug() << "[UDP]Successfully bind . port: " << port;
        connect(m_socket_Data, &QUdpSocket::readyRead, this, &UdpSocketManager::shwoUdpData);
    } else {
        qDebug() << "[UDP] Failed bind. port: " << port;
    }
}
