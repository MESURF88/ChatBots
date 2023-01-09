#ifndef _TCPCLIENTCOMM_H
#define _TCPCLIENTCOMM_H
#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>
#include <TcpComm.hpp>

class TcpClientComm : public TcpComm
{

  public:
    explicit TcpClientComm(QObject *parent=0): TcpComm(parent)
    {
        csocket = new QTcpSocket(this);
    }
    virtual TCPID getID() override;
    //Start the client
    virtual void StartRound(chatbots::ProfileFlat m_initselfprofile, QString ipaddr, int port) override;
    //send
    virtual void sendJsonAll(chatbots::ProfileFlat m_opponentprofile) override;
  signals:

  public slots:
    void readyRead();
  protected:

  private:

};

#endif
