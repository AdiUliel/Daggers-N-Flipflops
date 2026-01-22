#ifndef MANA_POTION_H
#define MANA_POTION_H

#include "Item.h"
#include "Character.h"
#include <iostream>

class ManaPotion : public Item {
    int m_restoreAmount;

public:
    ManaPotion(int amount) 
        : Item("Mana Potion", "Common", 30, "Usable"), m_restoreAmount(amount) {}

    bool use(Character* owner) override {
        std::cout << "You drink the glowing blue liquid. It tingles.\n";
        
        int currentMP = owner->get_MP();
        owner->set_MP(currentMP + m_restoreAmount);
        
        std::cout << "Restored " << m_restoreAmount << " MP.\n";
        return true;
    }
};

#endif