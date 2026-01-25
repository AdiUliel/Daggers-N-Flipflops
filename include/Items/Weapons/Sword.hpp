#ifndef SWORD_HPP
#define SWORD_HPP

#include "Weapon.h"
#include "Utils.h"
#include "Character.h"

class Sword : public Weapon {
public:
    Sword() : Weapon("Sword", 1, 10, 10, 5) {}

    std::string get_action_name(Character* user) const override {
        if (user->get_class_name() == "Warrior") return "Heroic Slash";
        return "Wild Swing";
    }

    void attack_action(Character* user, Character* target) const override {
        int dmg = m_damage + random_int(0, 5);

        if (user->get_class_name() == "Warrior") {
            std::cout << "You execute a perfect combat stance. ";
            dmg += 5;
        } else {
            std::cout << "You swing the heavy sword awkwardly. ";
            dmg -= 2;
        }

        std::cout << "Hit for " << dmg << " damage.\n";
        target->damage(dmg);
    }
};

#endif