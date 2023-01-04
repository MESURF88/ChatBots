#ifndef _DISPLAY_LOGIC_H
#define _DISPLAY_LOGIC_H

#include <QObject>
#include <jsoncons/json.hpp>

namespace chatbots {
    class StatSchema
    {
        double health_;
        double mana_;
        double stamina_;
    public:
        StatSchema(double health,
            double mana,
            double stamina)
            : health_(health), mana_(mana), stamina_(stamina)
        {

        }
        double health() const { return health_; }
        double mana() const { return mana_; }
        double stamina() const { return stamina_; }

        void set_health(double health) { health_ = health; }
        void set_mana(double mana) { mana_ = mana; }
        void set_stamina(double stamina) { stamina_ = stamina; }
    };

    // #4 Class with getters and setters
    class ProfileFlat
    {
        std::string uuid_;
        bool inplay_;
        bool turn_;
        std::vector<StatSchema> stats_;
    public:
        ProfileFlat()
            : uuid_(""), inplay_(false), turn_(false), stats_()
        {
        }

        ProfileFlat(const std::string& UUID,
            const bool& inplay,
            const bool& turn,
            const std::vector<StatSchema>& statistics)
            : uuid_(UUID), inplay_(inplay), turn_(turn), stats_(statistics)
        {
        }

        const std::string get_uuid() const { return uuid_; }

        const bool& get_inplay() const { return inplay_; }

        const bool& get_turn() const { return turn_; }

        const std::vector<StatSchema>& get_stats() const {
            return stats_;
        }

        void set_uuid(const std::string& UUID)
        {
            uuid_ = UUID;
        }

        void set_inplay(const bool& inplay)
        {
            inplay_ = inplay;
        }

        void set_turn(const bool& turn)
        {
            turn_ = turn;
        }

        void set_stats(const std::vector<StatSchema>& statistics)
        {
            stats_ = statistics;
        }

        bool set_health(double health)
        {
            bool ret = false;
            if (stats_.size() > 0)
            {
                ret = true;
                stats_.at(0).set_health(health);
            }
            return ret;
        }
        bool set_mana(double mana)
        {
            bool ret = false;
            if (stats_.size() > 0)
            {
                ret = true;
                stats_.at(0).set_mana(mana);
            }
            return ret;
        }
        bool set_stamina(double stamina)
        {
            bool ret = false;
            if (stats_.size() > 0)
            {
                ret = true;
                stats_.at(0).set_stamina(stamina);
            }
            return ret;
        }
    };


} // namespace chatbots

class StatSchemaProps : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double healthStat READ healthStat WRITE setHealthStat NOTIFY healthStatChanged)
    Q_PROPERTY(double manaStat READ manaStat WRITE setManaStat NOTIFY manaStatChanged)
    Q_PROPERTY(double staminaStat READ staminaStat WRITE setStaminaStat NOTIFY staminaStatChanged)
    Q_PROPERTY(QString uuid READ uuid NOTIFY uuidChanged)
public:
    explicit StatSchemaProps(QObject *parent = nullptr);
    chatbots::ProfileFlat& getJsonHandle() { return m_Profile; };
    void initJson(chatbots::ProfileFlat profile);

double healthStat() const;
void setHealthStat(double newHealthStat);

double manaStat() const;
void setManaStat(double newManaStat);

double staminaStat() const;
void setStaminaStat(double newStaminaStat);

QString uuid() const;

signals:

void healthStatChanged();

void manaStatChanged();

void staminaStatChanged();

void uuidChanged();

public slots:

protected:

private:
chatbots::ProfileFlat m_Profile;

double m_healthStat;
double m_manaStat;
double m_staminaStat;
QString m_uuid;
};

class DisplayLogic : public QObject
{
    Q_OBJECT
public:
    explicit DisplayLogic(StatSchemaProps &props, QObject *parent = nullptr);

    Q_INVOKABLE StatSchemaProps* statInstance() { return &m_StatSchemaProps; }
signals:

public slots:

protected:

private:
    StatSchemaProps &m_StatSchemaProps;
};

// Declare the traits. Specify which data members need to be serialized.
JSONCONS_ALL_CTOR_GETTER_TRAITS(chatbots::StatSchema, health, mana, stamina)
JSONCONS_ALL_GETTER_SETTER_TRAITS(chatbots::ProfileFlat, get_, set_, uuid, inplay, turn, stats)

#endif
