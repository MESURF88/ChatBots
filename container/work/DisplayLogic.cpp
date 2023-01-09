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
   "lose": false,
   "stats": [
   {
       "health": 10.0,
       "mana" : 10.0,
       "stamina": 10.0,
       "armor": 10.0
     }
   ]
}
)";

StatSchemaProps::StatSchemaProps(QObject *parent) : QObject(parent),
    m_healthStat(10), m_manaStat(10), m_staminaStat(10), m_uuid("")
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
    m_armorStat = m_Profile.get_stats().at(0).armor();
}

void StatSchemaProps::setStatsJsonFromFullProfile(chatbots::ProfileFlat profile)
{
    m_Profile.set_stats(profile.get_stats());
    m_healthStat = m_Profile.get_stats().at(0).health();
    m_armorStat = m_Profile.get_stats().at(0).armor();
    emit healthStatChanged();
    emit armorStatChanged();
}

double StatSchemaProps::healthStat() const
{
    return m_healthStat;
}

void StatSchemaProps::setHealthStat(double newHealthStat)
{
    if (qFuzzyCompare(m_healthStat, newHealthStat))
        return;
    if (newHealthStat > 10)
        newHealthStat = 10;
    if (newHealthStat < 0)
        newHealthStat = 0;
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
    if (newManaStat > 10)
        newManaStat = 10;
    if (newManaStat < 0)
        newManaStat = 0;
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
    if (newStaminaStat > 10)
        newStaminaStat = 10;
    if (newStaminaStat < 0)
        newStaminaStat = 0;
    m_staminaStat = newStaminaStat;
    m_Profile.set_stamina(m_staminaStat); // error check
    emit staminaStatChanged();
}

double StatSchemaProps::armorStat() const
{
    return m_armorStat;
}

void StatSchemaProps::setArmorStat(double newArmorStat)
{
    if (qFuzzyCompare(m_armorStat, newArmorStat))
        return;
    if (newArmorStat > 10)
        newArmorStat = 10;
    if (newArmorStat < 0)
        newArmorStat = 0;
    m_armorStat = newArmorStat;
    m_Profile.set_armor(m_armorStat); // error check
    emit armorStatChanged();
}

QString StatSchemaProps::uuid() const
{
      return m_uuid;
}

DisplayLogic::DisplayLogic(bool a_bclient, QString ipAddr, StatSchemaProps &props, QObject *parent): m_StatSchemaProps(props), m_winStatus(""), m_actionState("NONE")
{
     chatbots::ProfileFlat initselfprofile = jsoncons::decode_json<chatbots::ProfileFlat>(chatBotsTest);
     if (a_bclient)
     {
        superTcp = new TcpClientComm();
        qDebug() << "client";
     }
     else
     {
        // make a random server uuid
        QUuid uuid = QUuid::createUuid();
        initselfprofile.set_uuid(uuid.toString().toStdString());
        superTcp = new TcpServerComm();
        qDebug() << "server";
     }
     m_StatSchemaProps.initJson(initselfprofile);
     connect(superTcp,&TcpComm::newFullProfileJson,this,&DisplayLogic::ProcessFullProfileRead);
     connect(superTcp,&TcpComm::newStatJson,this,&DisplayLogic::ProcessRead);
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
        quint32 option = QRandomGenerator::global()->bounded( 1, 3 );
        quint32 gain = QRandomGenerator::global()->bounded( 1, 3 );
        performActionOnOpponent(static_cast<ACTIONSTATE>(option), gain);
    }
}

void DisplayLogic::performActionOnOpponent(ACTIONSTATE state, quint32 gain)
{
   if (state == ACTIONSTATE::ATTACKNORMAL)
   {
       if (m_StatSchemaProps.staminaStat() < 2)
       {
           // missed
           setActionState("MISSED ATTACK");
           m_StatSchemaProps.setManaStat(m_StatSchemaProps.manaStat()+1);
       }
       else
       {
           normalAttack(gain);
       }
   }
   else if (state == ACTIONSTATE::ATTACKMAGIC)
   {
       if (m_StatSchemaProps.manaStat() < 2)
       {
           // missed
           setActionState("MISSED MAGIC ATTACK");
           m_StatSchemaProps.setStaminaStat(m_StatSchemaProps.staminaStat()+1);
       }
       else
       {
           magicAttack(gain);
       }
   }
   else if (state == ACTIONSTATE::RECOVER)
   {
       if ((m_StatSchemaProps.staminaStat() >= 8) && (m_StatSchemaProps.manaStat() >= 8))
       {
            // do a normal attack have stats for it
            normalAttack(gain);
       }
       else {
           m_StatSchemaProps.setStaminaStat(m_StatSchemaProps.staminaStat()+1);
           m_StatSchemaProps.setManaStat(m_StatSchemaProps.manaStat()+1);
       }
   }
   // if health of conOpProfile goes to zero set lose condition.
   if (convOpponentProfile.get_stats().at(0).health() <= 0)
   {
       convOpponentProfile.set_lose(true);
       setWinStatus("WIN");
   }
   superTcp->sendJsonAll(convOpponentProfile);
}

void DisplayLogic::normalAttack(quint32 gain)
{
    m_StatSchemaProps.setStaminaStat(m_StatSchemaProps.staminaStat()-2);
    attack(gain);
}

void DisplayLogic::magicAttack(quint32 gain)
{
    m_StatSchemaProps.setManaStat(m_StatSchemaProps.manaStat()-2);
    attack(gain);
}

void DisplayLogic::attack(quint32 gain)
{
    double armorval = convOpponentProfile.get_stats().at(0).armor();
    double healthval = convOpponentProfile.get_stats().at(0).health();
    int diff = armorval - gain;
    if (diff < 0)
    {
        if (armorval > 0)
        {
         convOpponentProfile.set_armor(0);
         convOpponentProfile.set_health(healthval + diff);
        }
        else {
            convOpponentProfile.set_health(healthval - gain);
        }
    }
    else
    {
         convOpponentProfile.set_armor(armorval - gain);
    }
}

void DisplayLogic::ProcessRead(QJsonObject obj)
{
    std::string convCandidate = QJsonDocument(obj).toJson(QJsonDocument::Compact).toStdString();
    chatbots::ProfileFlat convSelfProfile = jsoncons::decode_json<chatbots::ProfileFlat>(convCandidate);
    m_StatSchemaProps.setStatsJsonFromFullProfile(convSelfProfile);
    // process slowly
    QThread::msleep(600);

    if (convSelfProfile.get_lose() == true)
    {
        // end game
        setWinStatus("LOST");
    }
    else
    {

        // else Random Event
        quint32 option = QRandomGenerator::global()->bounded( 0, 4 );
        quint32 gain = QRandomGenerator::global()->bounded( 1, 3 );

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
            // recover some points
            m_StatSchemaProps.setManaStat(m_StatSchemaProps.manaStat()+2);
            m_StatSchemaProps.setStaminaStat(m_StatSchemaProps.staminaStat()+2);
            superTcp->sendJsonAll(convOpponentProfile);
            break;
        }
    }
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


