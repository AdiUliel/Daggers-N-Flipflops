#ifndef FLIPFLOPS_HPP
#define FLIPFLOPS_HPP

#include "Weapon.h"
#include "Utils.h"
#include "Character.h"

class Flipflops : public Weapon {
public:
    Flipflops() : Weapon("The Flipflops of DOOM", 1, "Common", 999) {}

    std::string get_action_name(Character* user) const override {
        (void)user;
        return "Emotional Damage";
    }

    void attack_action(Character* user, Character* target) const override {
        std::cout << "You hold the Flip-flop in the air... The enemy trembles in fear. ";
        
        int dmg = 0;
        if (user->get_class_name() == "Normie") {
            dmg = 50 + user->get_power(); 
            std::cout << "SMACK! It sounds like thunder. ";
        } else {
            dmg = 1;
            std::cout << "You slap them with a piece of rubber. It does nothing. ";
        }
        
        target->damage(dmg);
        std::cout << "Dealt " << dmg << " damage.\n";
    }
};

#endif