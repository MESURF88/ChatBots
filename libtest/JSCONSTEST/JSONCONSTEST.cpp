// JSCONSTEST.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <variant>
#include <string>
#include <cassert>
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

        friend bool operator==(const StatSchema& lhs, const StatSchema& rhs)
        {
            return lhs.health_ == rhs.health_ && lhs.mana_ == rhs.mana_ &&
                lhs.stamina_ == rhs.stamina_;
        }

        friend bool operator!=(const StatSchema& lhs, const StatSchema& rhs)
        {
            return !(lhs == rhs);
        };


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
            // set qproperty member variables from stats_
        }
    };


    class HealthSchema
    {
        JSONCONS_TYPE_TRAITS_FRIEND
        double health_;
    public:
        friend std::ostream& operator<<(std::ostream& os, const HealthSchema& val)
        {
            os << "health: " << val.health_ << "\n";
            return os;
        }
    };

    class ManaSchema
    {
        JSONCONS_TYPE_TRAITS_FRIEND
        double mana_;
    public:
        friend std::ostream& operator<<(std::ostream& os, const ManaSchema& val)
        {
            os << "mana: " << val.mana_ << "\n";
            return os;
        }
    };

    class StaminaSchema
    {
        JSONCONS_TYPE_TRAITS_FRIEND
        double stamina_;
    public:
        friend std::ostream& operator<<(std::ostream& os, const StaminaSchema& val)
        {
            os << "stamina: " << val.stamina_ << "\n";
            return os;
        }
    };

    class ProfileVariant
    {
    private:
        JSONCONS_TYPE_TRAITS_FRIEND
        std::string uuid_;
        bool inplay_;
        bool turn_;
        std::vector<std::variant<HealthSchema, ManaSchema, StaminaSchema>> stats_;

    public:
        const std::string get_uuid() const { return uuid_; }

        const bool& get_inplay() const { return inplay_; }

        const bool& get_turn() const { return turn_; }

        std::vector<std::variant<HealthSchema, ManaSchema, StaminaSchema>> get_stats() const
        {
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

        void set_stats(const std::vector<std::variant<HealthSchema, ManaSchema, StaminaSchema>>& statistics)
        {
            stats_ = statistics;
            // set qproperty member variables from stats_
        }
    };

    class StatSchemaPoint
    {
        double health_;
        double mana_;
        double stamina_;
    public:
        StatSchemaPoint(double health,
            double mana,
            double stamina)
            : health_(health), mana_(mana), stamina_(stamina)
        {

        }
        double health() const { return health_; }
        double mana() const { return mana_; }
        double stamina() const { return stamina_; }

        friend bool operator==(const StatSchemaPoint& lhs, const StatSchemaPoint& rhs)
        {
            return lhs.health_ == rhs.health_ && lhs.mana_ == rhs.mana_ &&
                lhs.stamina_ == rhs.stamina_;
        }

        friend bool operator!=(const StatSchemaPoint& lhs, const StatSchemaPoint& rhs)
        {
            return !(lhs == rhs);
        };


    };

    // #4 Class with getters and setters
    class ProfilePointStats
    {
        std::string uuid_;
        bool inplay_;
        bool turn_;
        std::vector<StatSchema> stats_;
        std::unique_ptr<StatSchemaPoint> statpointer;
    public:
        ProfilePointStats()
            : uuid_(""), inplay_(false), turn_(false), stats_()
        {
        }

        ProfilePointStats(const std::string& UUID,
            const bool& inplay,
            const bool& turn,
            const std::vector<StatSchema>& statistics)
            : uuid_(UUID), inplay_(inplay), turn_(turn), stats_(statistics)
        {
        }

        const std::string get_uuid() const { return uuid_; }

        const bool& get_inplay() const { return inplay_; }

        const bool& get_turn() const { return turn_; }

        const std::vector<StatSchema>& get_stats() const { return stats_; }

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
            // set qproperty member variables from stats_
        }
    };


} // namespace chatbots



// Declare the traits. Specify which data members need to be serialized.
JSONCONS_ALL_CTOR_GETTER_TRAITS(chatbots::StatSchema, health, mana, stamina)
JSONCONS_ALL_GETTER_SETTER_TRAITS(chatbots::ProfileFlat, get_, set_, uuid, inplay, turn, stats)

// Only C++17
JSONCONS_ALL_MEMBER_NAME_TRAITS(chatbots::HealthSchema,
    (health_, "health"))
JSONCONS_ALL_MEMBER_NAME_TRAITS(chatbots::ManaSchema,
    (mana_, "mana"))
JSONCONS_ALL_MEMBER_NAME_TRAITS(chatbots::StaminaSchema,
    (stamina_, "stamina"))
JSONCONS_ALL_MEMBER_NAME_TRAITS(chatbots::ProfileVariant, 
    (uuid_, "uuid"),
    (inplay_, "inplay"),
    (turn_, "turn"),
    (stats_, "stats"))

JSONCONS_ALL_GETTER_SETTER_TRAITS(chatbots::ProfilePointStats, get_, set_, uuid, inplay, turn, stats)

using namespace jsoncons; // for convenience

int main()
{

    const std::string chatBotsTest = R"(
    {
       "uuid": "f9c35e8e-f774-4b8f-b0e6-ad0c948c689a",
       "inplay" : false,
       "turn": false,
       "stats": [
       {
           "health": 200.0,
           "mana" : 100.0,
           "stamina": 30.0
         }
       ]
    }
    )";

    const std::string chatBotsTestHidden = R"(
        {
            "uuid" : "f9c35e8e-f774-4b8f-b0e6-ad0c948c689a",
            "inplay" : false,
            "turn" : false,
            "stats": [
                {
                    "health" : 120
                },
                {
                    "mana" : 20
                },
                {
                    "stamina" : 30
                }
            ]
        }
    )";

    try
    {
        chatbots::ProfileVariant prof1 = decode_json<chatbots::ProfileVariant>(chatBotsTestHidden);

        std::cout << "\n" << prof1.get_uuid() << ", "
            << prof1.get_inplay() << ", "
            << prof1.get_turn() << "\n";

        for (const auto& var : prof1.get_stats())
        {
            std::visit([](auto&& arg) {
                using T = std::decay_t<decltype(arg)>;
                if constexpr (std::is_same_v<T, chatbots::HealthSchema>)
                    std::cout << "Health " << arg << '\n';
                else if constexpr (std::is_same_v<T, chatbots::ManaSchema>)
                    std::cout << "Mana " << arg << '\n';
                else if constexpr (std::is_same_v<T, chatbots::StaminaSchema>)
                    std::cout << "Stamina " << arg << '\n';
                }, var);
        }
        std::cout << "\n";
        std::cout << "(2)\n\n";
        encode_json_pretty(prof1, std::cout);
        std::cout << "\n\n";
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << "";
    }


    try
    {
        chatbots::ProfileFlat prof2 = decode_json<chatbots::ProfileFlat>(chatBotsTest);

        std::cout << "\n" << prof2.get_uuid() << ", "
            << prof2.get_inplay() << ", "
            << prof2.get_turn() << "\n";

        for (const auto& item : prof2.get_stats())
        {
            std::cout << item.health() << ", " << item.mana() << ", " << item.stamina();
        }
        // test changing internal stat field
        std::vector<chatbots::StatSchema> tmp{ chatbots::StatSchema(500, 500, 500)};
        prof2.set_stats(tmp);
        std::cout << "\n";
        std::cout << "(2)\n\n";
        encode_json_pretty(prof2, std::cout);
        std::cout << "\n\n";

        std::cout << "\n";
        std::cout << "(3)\n\n";
        encode_json_pretty(chatbots::StatSchema(500, 500, 500), std::cout);
        std::cout << "\n\n";
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << "";
    }
#ifdef TEST3
    try
    {
        chatbots::ProfilePointStats prof3 = decode_json<chatbots::ProfilePointStats>(chatBotsTest);

        std::cout << "\n" << prof3.get_uuid() << ", "
            << prof3.get_inplay() << ", "
            << prof3.get_turn() << "\n";

        for (const auto& item : prof3.get_stats())
        {
            std::cout << item.health() << ", " << item.mana() << ", " << item.stamina();
        }


            std::cout << "\n";
        std::cout << "(2)\n\n";
        encode_json_pretty(prof3, std::cout);
        std::cout << "\n\n";
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << "";
    }
#endif
}
