#ifndef WAND_HPP
#define WAND_HPP

#include "Weapon.h"
#include "Utils.h"
#include "Character.h"

class Wand : public Weapon {
public:
    Wand() : Weapon("Magic Wand", 2, 50, 15, 1) {}

    std::string get_action_name(Character* user) const override {
        if (user->get_class_name() == "Mage") return "Magic Missile";
        return "Stick Poke";
    }

    void attack_action(Character* user, Character* target) const override {
        int dmg = 0;

        if (user->get_class_name() == "Mage") {
            int manaCost = 5;
            if (user->get_MP() >= manaCost) {
                user->set_MP(user->get_MP() - manaCost);
                dmg = random_int(5, 8) * 3; 
                std::cout << "Pew! Pew! Pew! Three magical bolts fly out! ";
            } else {
                std::cout << "Out of mana! The wand fizzles. ";
                dmg = 1;
            }
        } else {
            dmg = 3;
            std::cout << "You poke the enemy with the pointy end. It's annoying. ";
        }

        std::cout << "Dealt " << dmg << " damage.\n";
        target->damage(dmg);
    }
};

#endif