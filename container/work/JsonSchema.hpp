#ifndef _JSONSCHEMA_H
#define _JSONSCHEMA_H
#include <QDebug>
#include <vector>
#include <jsoncons/json.hpp>

#define PORT (6789)


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
        bool lose_;
        std::vector<StatSchema> stats_;
    public:
        ProfileFlat()
            : uuid_(""), inplay_(false), turn_(false), lose_(false), stats_()
        {
        }

        ProfileFlat(const std::string& UUID,
            const bool& inplay,
            const bool& turn,
            const bool& lose,
            const std::vector<StatSchema>& statistics)
            : uuid_(UUID), inplay_(inplay), turn_(turn), lose_(lose), stats_(statistics)
        {
        }

        const std::string get_uuid() const { return uuid_; }

        const bool& get_inplay() const { return inplay_; }

        const bool& get_turn() const { return turn_; }

        const bool& get_lose() const { return lose_; }

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

        void set_lose(const bool& lose)
        {
            lose_ = lose;
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
// Declare the traits. Specify which data members need to be serialized.
JSONCONS_ALL_CTOR_GETTER_TRAITS(chatbots::StatSchema, health, mana, stamina)
JSONCONS_ALL_GETTER_SETTER_TRAITS(chatbots::ProfileFlat, get_, set_, uuid, inplay, turn, lose, stats)

#endif
