#ifndef HAMMER_HPP
#define HAMMER_HPP

#include "Weapon.h"
#include "Utils.h"
#include "Character.h"

class Hammer : public Weapon {
public:
    Hammer() : Weapon("War Hammer", 2, 30, 20, 15) {}

    std::string get_action_name(Character* user) const override {
        if (user->get_class_name() == "Warrior") return "Skull Crusher";
        return "Heavy Lift";
    }

    void attack_action(Character* user, Character* target) const override {
        int dmg = 0;

        if (user->get_class_name() == "Warrior") {
            dmg = m_damage + random_int(5, 15);
            std::cout << "CRUNCH! You bring the hammer down with full force! ";
        } else {
            dmg = m_damage + random_int(-5, 5);
            std::cout << "You struggle to lift the hammer, but gravity helps. ";
        }

        std::cout << "Smashed for " << dmg << " damage.\n";
        target->damage(dmg);
    }
};

#endif