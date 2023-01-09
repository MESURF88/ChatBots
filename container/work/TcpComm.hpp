#ifndef _TCPCOMM_H
#define _TCPCOMM_H
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QJsonObject>
#include <JsonSchema.hpp>

const QString ACK = "Ack";


class TcpComm: public QTcpServer
{
  Q_OBJECT
  
  public:
        explicit TcpComm(QObject *parent=0): QTcpServer(parent), m_hasProfile(false) {}
        virtual ~TcpComm() = default;

        enum TCPID{
            CLIENT = 0,
            SERVER,
        };
        //Start the messaging
        virtual void StartRound(chatbots::ProfileFlat m_initselfprofile, QString ipaddr, int port) = 0;
        virtual void sendJsonAll(chatbots::ProfileFlat m_opponentprofile) = 0;
        virtual TCPID getID() = 0;
        void setHasOpponentsProfile() { m_hasProfile = true; };
  signals:
        void newStatJson(QJsonObject obj); // recieve
        void newFullProfileJson(QJsonObject obj);
        void newAck();
  public slots:

  protected:
        QTcpSocket *csocket = nullptr;
        bool m_hasProfile;
  private:

};

#endif
