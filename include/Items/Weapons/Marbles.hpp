#ifndef MARBLES_HPP
#define MARBLES_HPP

#include "Weapon.h"
#include "Utils.h"
#include "Character.h"

class Marbles : public Weapon {
public:
    Marbles() : Weapon("Bag of Marbles", 1, 1, 1, 1) {}

    std::string get_action_name(Character* user) const override {
        if (user->get_class_name() == "Normie") return "Home Alone Trap";
        return "Throw Marbles";
    }

    void attack_action(Character* user, Character* target) const override {
        int dmg = m_damage;
        if (user->get_class_name() == "Normie") {
            std::cout << "The enemy slips, falls, and hits their head! Comedy gold. ";
            dmg *= 3;
        } else {
            std::cout << "You throw marbles. The enemy just steps on them. ";
        }
        target->damage(dmg);
        std::cout << "Dealt " << dmg << " damage.\n";
    }
};

#endif