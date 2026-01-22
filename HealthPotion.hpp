#ifndef HEALTH_POTION_H
#define HEALTH_POTION_H

#include "Item.h"
#include "Character.h"

class Potion : public Item {
    int m_healAmount;

public:
    Potion(int healAmount) 
        : Item("Health Potion", "Common", 20, "Usable"), m_healAmount(healAmount) {}

    bool use(Character* owner) override {
        std::cout << "You drank the potion. Glug glug.\n";
        owner->heal(m_healAmount);
        std::cout << "Healed for " << m_healAmount << " HP.\n";
        return true;
    }
};

#endif