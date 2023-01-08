#include "TcpClientComm.hpp"
#include <QThread>

TcpComm::TCPID TcpClientComm::getID()
{
    return TcpComm::TCPID::CLIENT;
}

void TcpClientComm::StartRound(chatbots::ProfileFlat m_initselfprofile, QString ipaddr, int port)
{
    QString line = "";
    QThread::msleep(50); //wait for server
    csocket->connectToHost(ipaddr, port);
    if(csocket->waitForConnected(3000))
    {
        qDebug() << "Connected!";
        connect(csocket, &QTcpSocket::readyRead, this, &TcpClientComm::readyRead);
        // send
        std::string tmpjson;
        jsoncons::encode_json(m_initselfprofile, tmpjson);
        line = QString::fromStdString(tmpjson);
        csocket->write(line.toUtf8());
        csocket->waitForBytesWritten(1000);
    }
}

void TcpClientComm::sendAck()
{
    if (csocket != nullptr)
    {
        csocket->write(ACK.toUtf8());
        csocket->waitForBytesWritten(1000);
    }
}

void TcpClientComm::sendJsonAll(chatbots::ProfileFlat m_opponentprofile)
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

void TcpClientComm::readyRead()
{
    QString line = csocket->readAll();
    //TODO:
    qDebug() << line;

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
