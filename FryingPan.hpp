#ifndef FRYINGPAN_HPP
#define FRYINGPAN_HPP

#include "Weapon.h"
#include "Utils.h"
#include "Character.h"

class FryingPan : public Weapon {
public:
    FryingPan() : Weapon("Cast Iron Pan", 8, "Common", 50) {}

    std::string get_action_name(Character* user) const override {
        if (user->get_class_name() == "Normie") return "Gordon Ramsay Style";
        return "Cook";
    }

    void attack_action(Character* user, Character* target) const override {
        int dmg = m_damage;
        if (user->get_class_name() == "Normie") {
            std::cout << "CLANG!!! The sound echoes through the dungeon. ";
            dmg += 10;
        } else {
            std::cout << "You try to hit them, but you're thinking about eggs. ";
        }
        target->damage(dmg);
        std::cout << "Dealt " << dmg << " damage.\n";
    }
};

#endif