#ifndef THROWINGSTARS_HPP
#define THROWINGSTARS_HPP

#include "Weapon.h"
#include "Utils.h"
#include "Character.h"

class ThrowingStars : public Weapon {
public:
    ThrowingStars() : Weapon("Shurikens", 1, 15, 9, 2) {}

    std::string get_action_name(Character* user) const override {
        if (user->get_class_name() == "Thief") return "Shadow Volley";
        return "Throw Star";
    }

    void attack_action(Character* user, Character* target) const override {
        int hits = 1;
        if (user->get_class_name() == "Thief") {
            hits = random_int(2, 4);
            std::cout << "You throw " << hits << " stars at once! ";
        } else {
            std::cout << "You throw a star. It wobbles in the air. ";
        }

        int dmg = (m_damage + random_int(0, 3)) * hits;
        std::cout << "Dealt " << dmg << " damage.\n";
        target->damage(dmg);
    }
};

#endif