#ifndef HEALTH_POTION_HPP
#define HEALTH_POTION_HPP

#include "Item.h"
#include "Character.h"

class HealthPotion : public Item {
    int m_healAmount;

public:
    HealthPotion(int healAmount) 
        : Item("Health Potion", "Consumable", 1 ,1, 10), m_healAmount(healAmount) {}

    bool use(Character* owner) override {
        std::cout << "You drank the potion. Glug glug.\n";
        owner->heal(m_healAmount);
        std::cout << "Healed for " << m_healAmount << " HP.\n";
        std::cout << "current HP: " << owner->get_HP() << "\n";
        return true;
    }
};

#endif