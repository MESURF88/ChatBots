#ifndef _TCPCSERVERCOMM_H
#define _TCPSERVERCOMM_H
#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>
#include <TcpComm.hpp>

class TcpServerComm : public TcpComm
{

  public:
    explicit TcpServerComm(QObject *parent=0): TcpComm(parent)
    {
        connect(this, &QTcpServer::newConnection, this, &TcpServerComm::newConnection);
        bool succ = listen(QHostAddress::Any, PORT);
        if (!succ)
        {
          qDebug()<<"Server couldn't start!";
          qDebug() << "Error: " << errorString();
        }
        else
        {
          qDebug()<<"Server started on port: "<< PORT;
        }
    }
    virtual TCPID getID() override;
    //Start the server
    virtual void StartRound(chatbots::ProfileFlat m_initselfprofile, QString ipaddr, int port) override;
    //send
    virtual void sendJsonAll(chatbots::ProfileFlat m_opponentprofile) override;
  signals:

  public slots:
     void readyRead();
     void newConnection();
  protected:

  private:

};

#endif
