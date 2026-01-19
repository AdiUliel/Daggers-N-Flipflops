#ifndef STAFF_H
#define STAFF_H

#include "Weapon.hpp"
#include "Utils.h"
#include "Character.h"

class Staff : public Weapon {
public:
    Staff() : Weapon("Mystic Staff", 100) {}

    string get_action_name(Character* user) override {
        if (user->get_class_name() == "Mage") {
            return "Arcane Blast (Spell)";
        } else {
            return "Heavy Bonk (Melee)";
        }
    }

    void use(Character* user, Character* target) override {
        int dmg = 0;
        
        // לוגיקה לקוסם: דורש מאנה, נזק גבוה
        if (user->get_class_name() == "Mage") {
            int manaCost = 10 * m_tier;
            if (user->get_MP() >= manaCost) {
                user->set_MP(user->get_MP() - manaCost);
                dmg = random_int(15, 25) * m_tier; 
                cout << "You channel energy through the staff! ";
            } else {
                cout << "Not enough mana! You gently poke with the staff instead. ";
                dmg = 2;
            }
        } 
        // לוגיקה לכל השאר
        else {
            dmg = random_int(5, 10) * m_tier + (user->get_power() / 2);
            cout << "You swing the staff like a baseball bat! BONK! ";
        }

        cout << "Dealt " << dmg << " damage.\n";
        target->damage(dmg);
    }
};

#endif