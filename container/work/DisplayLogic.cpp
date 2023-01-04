#include "DisplayLogic.hpp"
#include <QDebug>

const std::string chatBotsTest = R"(
{
   "uuid": "f9c35e8e-f774-4b8f-b0e6-ad0c948c689a",
   "inplay" : false,
   "turn": false,
   "stats": [
   {
       "health": 10.0,
       "mana" : 10.0,
       "stamina": 3.0
     }
   ]
}
)";

StatSchemaProps::StatSchemaProps(QObject *parent) : QObject(parent), m_healthStat(10), m_manaStat(10), m_staminaStat(10)
{

}

void StatSchemaProps::initJson(chatbots::ProfileFlat profile)
{
    m_Profile = profile;
    // error check
    m_healthStat = m_Profile.get_stats().at(0).health();
    m_manaStat = m_Profile.get_stats().at(0).mana();
    m_staminaStat = m_Profile.get_stats().at(0).stamina();
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
    emit staminaStatChanged();
}


DisplayLogic::DisplayLogic(StatSchemaProps &props, QObject *parent): m_StatSchemaProps(props)
{
     m_StatSchemaProps.initJson(jsoncons::decode_json<chatbots::ProfileFlat>(chatBotsTest));
     //TODO: jsoncons::encode_json_pretty(m_StatSchemaProps.getJsonHandle(), std::cout);
}
