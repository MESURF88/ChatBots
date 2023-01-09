#ifndef _DISPLAY_LOGIC_H
#define _DISPLAY_LOGIC_H

#include <QObject>
#include <QHash>
#include <TcpComm.hpp>

class StatSchemaProps : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double healthStat READ healthStat WRITE setHealthStat NOTIFY healthStatChanged)
    Q_PROPERTY(double manaStat READ manaStat WRITE setManaStat NOTIFY manaStatChanged)
    Q_PROPERTY(double staminaStat READ staminaStat WRITE setStaminaStat NOTIFY staminaStatChanged)
    Q_PROPERTY(double armorStat READ armorStat WRITE setArmorStat NOTIFY armorStatChanged)
    Q_PROPERTY(QString uuid READ uuid NOTIFY uuidChanged)
public:
    explicit StatSchemaProps(QObject *parent = nullptr);
    chatbots::ProfileFlat& getJsonHandle() { return m_Profile; };
    void initJson(chatbots::ProfileFlat profile);
    void setStatsJsonFromFullProfile(chatbots::ProfileFlat profile);

double healthStat() const;
void setHealthStat(double newHealthStat);

double manaStat() const;
void setManaStat(double newManaStat);

double staminaStat() const;
void setStaminaStat(double newStaminaStat);

double armorStat() const;
void setArmorStat(double newArmorStat);

QString uuid() const;

signals:

void healthStatChanged();

void manaStatChanged();

void staminaStatChanged();

void uuidChanged();

void armorStatChanged();

public slots:

protected:

private:
chatbots::ProfileFlat m_Profile;

double m_healthStat;
double m_manaStat;
double m_staminaStat;
double m_armorStat;
QString m_uuid;
};

class DisplayLogic : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString winStatus READ winStatus WRITE setWinStatus NOTIFY winStatusChanged)
    Q_PROPERTY(QString actionState READ actionState WRITE setActionState NOTIFY actionStateChanged)
public:
    explicit DisplayLogic(bool a_bclient, QString ipAddr, StatSchemaProps &props, QObject *parent = nullptr);
    enum ACTIONSTATE
    {
        NONE = 0,
        ATTACKNORMAL = 1,
        ATTACKMAGIC = 2,
        RECOVER = 3,
    };

    Q_INVOKABLE StatSchemaProps* statInstance() { return &m_StatSchemaProps; }


    const QString &winStatus() const;
    void setWinStatus(const QString &newWinStatus);

    const QString &actionState() const;
    void setActionState(const QString &newActionState);

signals:

    void winStatusChanged();

    void actionStateChanged();

public slots:

    void ProcessRead(QJsonObject obj);
    void ProcessFullProfileRead(QJsonObject obj);
protected:

private:
    void performActionOnOpponent(ACTIONSTATE state, quint32 gain);
    void normalAttack(quint32 gain);
    void magicAttack(quint32 gain);
    void attack(quint32 gain);
    StatSchemaProps &m_StatSchemaProps;
    chatbots::ProfileFlat convOpponentProfile;
    TcpComm *superTcp = nullptr;
    QString m_winStatus;
    QString m_actionState;
    QHash<int, QString> const m_actionMap = {
        {ACTIONSTATE::NONE, "MISSED ATTACK"},
        {ACTIONSTATE::ATTACKNORMAL, "NORMAL ATTACK"},
        {ACTIONSTATE::ATTACKMAGIC, "MAGIC ATTACK"},
        {ACTIONSTATE::RECOVER, "RECOVER"},
    };
};


#endif
