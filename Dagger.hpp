#ifndef DAGGER_HPP
#define DAGGER_HPP

#include "Weapon.h"
#include "Utils.h"
#include "Character.h"

class Dagger : public Weapon {
public:
    Dagger() : Weapon("Rusty Dagger", 6, "Common", 80) {}

    std::string get_action_name(Character* user) const override {
        if (user->get_class_name() == "Thief") return "Backstab";
        return "Stab";
    }

    void attack_action(Character* user, Character* target) const override {
        int dmg = m_damage;

        if (user->get_class_name() == "Thief") {
            std::cout << "You vanish into the shadows and strike from behind! ";
            dmg += user->get_power();
            dmg *= 1.5;
        } else {
            std::cout << "You slash wildly with the small knife. ";
        }

        std::cout << "Dealt " << dmg << " damage.\n";
        target->damage(dmg);
    }
};

#endif