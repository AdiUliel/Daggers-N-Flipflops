#ifndef STAFF_H
#define STAFF_H

#include "Weapon.h"
#include "Utils.h"
#include "Character.h"

class Staff : public Weapon {
public:
    Staff() : Weapon("Mystic Staff", 5, "Common", 100) {}

    string get_action_name(Character* user) const override {
        if (user->get_class_name() == "Mage") {
            return "Arcane Blast (Spell)";
        } else {
            return "Heavy Bonk (Melee)";
        }
    }

    void attack_action(Character* user, Character* target) const override {
        int dmg = 0;
        int tierMultiplier = 1;

        if (user->get_class_name() == "Mage") {
            int manaCost = 10 * tierMultiplier;
            
            if (user->get_MP() >= manaCost) {
                user->set_MP(user->get_MP() - manaCost);
                
                dmg = (m_damage + random_int(10, 20)) * tierMultiplier; 
                cout << "You channel energy through the staff! ";
            } else {
                cout << "Not enough mana! You gently poke with the staff instead. ";
                dmg = 2;
            }
        } 
        else {
            dmg = random_int(1, 5) * tierMultiplier + (user->get_power() / 2);
            cout << "You swing the staff like a baseball bat! BONK! ";
        }

        cout << "Dealt " << dmg << " damage.\n";
        target->damage(dmg);
    }
};

#endif