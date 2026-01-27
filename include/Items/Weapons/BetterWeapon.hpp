#ifndef BETTERWEAPON_HPP
#define BETTERWEAPON_HPP

#include "Weapon.h"
#include "Character.h"
#include <iostream>

class BetterWeapon : public Weapon {
private:
    std::string m_description;

public:
    BetterWeapon(std::string name, int damage, int weight, std::string desc)
        : Weapon(name, 2, 100, damage, weight), m_description(desc) {}

    void attack_action(Character* owner, Character* target) const override {
        std::cout << owner->get_name() << " attacks with " << m_name << "!\n";
        std::cout << m_description << "\n"; 
        
        target->take_damage(m_damage);
    }

    std::string get_action_name(Character* owner) const override {
        (void)owner; 
        return "Strike with " + m_name;
    }
    
    std::string get_description() const override {
        return m_description;
    }
};

#endif