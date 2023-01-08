#include "TcpServerComm.hpp"

TcpComm::TCPID TcpServerComm::getID()
{
    return TcpComm::TCPID::SERVER;
}

void TcpServerComm::StartRound(chatbots::ProfileFlat m_initselfprofile, QString ipaddr, int port)
{

}

void TcpServerComm::sendAck()
{
    if (csocket != nullptr)
    {
        csocket->write(ACK.toUtf8());
        csocket->waitForBytesWritten(1000);
    }
}

void TcpServerComm::sendJsonAll(chatbots::ProfileFlat m_opponentprofile)
{
    if (csocket != nullptr)
    {
    std::string tmpjson;
    jsoncons::encode_json(m_opponentprofile, tmpjson);
    QString line = QString::fromStdString(tmpjson);
    csocket->write(line.toUtf8());
    csocket->waitForBytesWritten(1000);
    }
}

void TcpServerComm::readyRead()
{
    QString line = csocket->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(line.toUtf8());
        QJsonObject jsonObject = jsonDoc.object();
        qDebug() << "Received JSON:" << jsonObject;
        if (m_hasProfile)
        {
            emit TcpComm::newStatJson(jsonObject);
        }
        else
        {
            emit TcpComm::newFullProfileJson(jsonObject);
        }
}

void TcpServerComm::newConnection()
{
    qDebug() << "newConn";
    csocket = nextPendingConnection();
    connect(csocket, &QTcpSocket::readyRead, this, &TcpServerComm::readyRead);
    //TODO: connect(csocket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}
