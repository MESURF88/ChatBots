#include "DisplayLogic.hpp"
#include <QDebug>
#include <QUuid>
#include <QThread>
#include <QRandomGenerator>
#include <TcpClientComm.hpp>
#include <TcpServerComm.hpp>

const std::string chatBotsTest = R"(
{
   "uuid": "f9c35e8e-f774-4b8f-b0e6-ad0c948c689a",
   "inplay" : false,
   "turn": false,
   "lose": false,
   "stats": [
   {
       "health": 10.0,
       "mana" : 10.0,
       "stamina": 10.0
     }
   ]
}
)";

StatSchemaProps::StatSchemaProps(QObject *parent) : QObject(parent),
    m_healthStat(10), m_manaStat(10), m_staminaStat(10), m_uuid(""), m_turn(false)
{

}

void StatSchemaProps::initJson(chatbots::ProfileFlat profile)
{
    m_Profile = profile;
    // error check
    m_uuid = QString::fromStdString( m_Profile.get_uuid() );
    m_healthStat = m_Profile.get_stats().at(0).health();
    m_manaStat = m_Profile.get_stats().at(0).mana();
    m_staminaStat = m_Profile.get_stats().at(0).stamina();
}

void StatSchemaProps::setStatsJsonFromFullProfile(chatbots::ProfileFlat profile)
{
    m_Profile.set_stats(profile.get_stats());
    m_healthStat = m_Profile.get_stats().at(0).health();
    m_manaStat = m_Profile.get_stats().at(0).mana();
    m_staminaStat = m_Profile.get_stats().at(0).stamina();
    emit healthStatChanged();
    emit manaStatChanged();
    emit staminaStatChanged();
}

double StatSchemaProps::healthStat() const
{
    return m_healthStat;
}

void StatSchemaProps::setHealthStat(double newHealthStat)
{
    if (qFuzzyCompare(m_healthStat, newHealthStat))
        return;
    m_healthStat = newHealthStat;
    m_Profile.set_health(m_healthStat); // error check
    emit healthStatChanged();
}

double StatSchemaProps::manaStat() const
{
    return m_manaStat;
}

void StatSchemaProps::setManaStat(double newManaStat)
{
    if (qFuzzyCompare(m_manaStat, newManaStat))
        return;
    m_manaStat = newManaStat;
    m_Profile.set_mana(m_manaStat); // error check
    emit manaStatChanged();
}

double StatSchemaProps::staminaStat() const
{
    return m_staminaStat;
}

void StatSchemaProps::setStaminaStat(double newStaminaStat)
{
    if (qFuzzyCompare(m_staminaStat, newStaminaStat))
        return;
    m_staminaStat = newStaminaStat;
    m_Profile.set_stamina(m_staminaStat); // error check
    emit staminaStatChanged();
}

QString StatSchemaProps::uuid() const
{
      return m_uuid;
}

bool StatSchemaProps::turn() const
{
    return m_turn;
}

void StatSchemaProps::setTurn(bool turn)
{
    if (m_turn == turn)
        return;
    m_turn = turn;
    m_Profile.set_turn(turn);
    emit turnChanged();
}

DisplayLogic::DisplayLogic(bool a_bclient, QString ipAddr, StatSchemaProps &props, QObject *parent): m_StatSchemaProps(props), m_winStatus(""), m_actionState("NONE")
{
     chatbots::ProfileFlat initselfprofile = jsoncons::decode_json<chatbots::ProfileFlat>(chatBotsTest);
     //TODO: jsoncons::encode_json_pretty(m_StatSchemaProps.getJsonHandle(), std::cout);
     if (a_bclient)
     {
        initselfprofile.set_turn(true);
        superTcp = new TcpClientComm();
        qDebug() << "client";
        //client.StartClient(m_StatSchemaProps.getJsonHandle(), ipAddr, PORT, 10);
     }
     else
     {
        initselfprofile.set_turn(false);
        // make a random server uuid
        QUuid uuid = QUuid::createUuid();
        initselfprofile.set_uuid(uuid.toString().toStdString());
        superTcp = new TcpServerComm();
        qDebug() << "server";
        //server = new MyTcpServer(this);
        //connect(server,&MyTcpServer::newReadJson,this,&DisplayLogic::ProcessRead);
     }
     m_StatSchemaProps.initJson(initselfprofile);
     connect(superTcp,&TcpComm::newFullProfileJson,this,&DisplayLogic::ProcessFullProfileRead);
     connect(superTcp,&TcpComm::newStatJson,this,&DisplayLogic::ProcessRead);
     connect(superTcp,&TcpComm::newAck,this,&DisplayLogic::ProcessAckRead);
     superTcp->StartRound(m_StatSchemaProps.getJsonHandle(), ipAddr, PORT);

}

void DisplayLogic::ProcessFullProfileRead(QJsonObject obj)
{
    std::string convCandidate = QJsonDocument(obj).toJson(QJsonDocument::Compact).toStdString();
    convOpponentProfile = jsoncons::decode_json<chatbots::ProfileFlat>(convCandidate);
    if (superTcp->getID() == TcpComm::TCPID::SERVER)
    {
        qDebug() << "Server has opponents profile";
        superTcp->sendJsonAll(m_StatSchemaProps.getJsonHandle());
        superTcp->setHasOpponentsProfile();
        convOpponentProfile.set_inplay(true);
    }
    else
    {
        qDebug() << "Client has opponents profile";
        superTcp->setHasOpponentsProfile();
        convOpponentProfile.set_inplay(true);
        // Start Random Action Event on the opponent client starts after both profiles received
        quint32 option = QRandomGenerator::global()->bounded( 1, 2 );
        quint32 gain = QRandomGenerator::global()->bounded( 1, 3 );
        performActionOnOpponent(static_cast<ACTIONSTATE>(option), gain);
    }
}

void DisplayLogic::performActionOnOpponent(ACTIONSTATE state, quint32 gain)
{
   convOpponentProfile.set_turn(true);
   m_StatSchemaProps.setTurn(false);

}

void DisplayLogic::ProcessRead(QJsonObject obj)
{
    std::string convCandidate = QJsonDocument(obj).toJson(QJsonDocument::Compact).toStdString();
    chatbots::ProfileFlat convSelfProfile = jsoncons::decode_json<chatbots::ProfileFlat>(convCandidate);
    m_StatSchemaProps.setStatsJsonFromFullProfile(convSelfProfile);
    // change at different times
    QThread::msleep(300);

    if (convSelfProfile.get_lose() == true)
    {
        // end game
        setWinStatus("LOST");
    }
    else
    {

        // else Random Event
        quint32 option = QRandomGenerator::global()->bounded( 0, 3 );
        quint32 gain = QRandomGenerator::global()->bounded( 1, 3 );

        // if health of conOpProfile goes to zero set lose condition.
        if (convOpponentProfile.get_stats().at(0).health() <= 0)
        {
            convOpponentProfile.set_lose(true);
            setWinStatus("WIN");
        }

        switch (option)
        {
        case ACTIONSTATE::ATTACKNORMAL:
        case ACTIONSTATE::ATTACKMAGIC:
        case ACTIONSTATE::RECOVER:
            setActionState(m_actionMap.value(option));
            performActionOnOpponent(static_cast<ACTIONSTATE>(option), gain);
            break;
        default:
            setActionState(m_actionMap.value(ACTIONSTATE::NONE));
            break;
        }
    }
}

void DisplayLogic::ProcessAckRead()
{
    qDebug() << "Ack Received!";
}


const QString &DisplayLogic::winStatus() const
{
    return m_winStatus;
}

void DisplayLogic::setWinStatus(const QString &newWinStatus)
{
    if (m_winStatus == newWinStatus)
        return;
    m_winStatus = newWinStatus;
    emit winStatusChanged();
}

const QString &DisplayLogic::actionState() const
{
    return m_actionState;
}

void DisplayLogic::setActionState(const QString &newActionState)
{
    if (m_actionState == newActionState)
        return;
    m_actionState = newActionState;
    emit actionStateChanged();
}

