#ifndef CROSSBOW_HPP
#define CROSSBOW_HPP

#include "Weapon.h"
#include "Utils.h"
#include "Character.h"

class Crossbow : public Weapon {
public:
    Crossbow() : Weapon("Heavy Crossbow", 1, 40, 25, 8) {}

    std::string get_action_name(Character* user) const override {
        if (user->get_class_name() == "Archer") return "Piercing Shot";
        return "Shoot Bolt";
    }

    void attack_action(Character* user, Character* target) const override {
        int dmg = m_damage;

        if (user->get_class_name() == "Archer") {
            std::cout << "You aim for the weak spot... ";
            if (random_int(1, 10) > 7) {
                dmg *= 2;
                std::cout << "HEADSHOT! ";
            }
        } else {
            std::cout << "You pull the trigger blindly. ";
            dmg = random_int(5, 10);
        }

        std::cout << "Dealt " << dmg << " damage.\n";
        target->damage(dmg);
    }
};

#endif