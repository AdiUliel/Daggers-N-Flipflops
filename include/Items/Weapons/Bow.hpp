#ifndef BOW_HPP
#define BOW_HPP

#include "Weapon.h"
#include "Utils.h"
#include "Character.h"

class Bow : public Weapon {
public:
    Bow() : Weapon("Long Bow", 1, 15, 12, 3) {}

    string get_action_name(Character* user) const override {
        if (user->get_class_name() == "Thief") return "Poisoned Shot";
        return "Shoot Arrow";
    }

    void attack_action(Character* user, Character* target) const override {
        int tierMultiplier = 1;
        int dmg = (m_damage + random_int(2, 12)) * tierMultiplier;

        if (user->get_class_name() == "Thief") {
            cout << "You dip the arrow in toxin before firing... ";
            dmg += 5 * tierMultiplier; 
        } 
        else if (user->get_class_name() == "Warrior") {
            cout << "You pull the string too hard and fumble, but still hit. ";
            dmg -= 3; 
            if (dmg < 1) dmg = 1; 
        }
        else {
            cout << "You fire a precise shot. ";
        }

        cout << "Hit for " << dmg << " damage.\n";
        target->damage(dmg);
    }
};

#endif