#include "Weapon.h"
#include "Character.h"
#include <iostream>

bool Weapon::use(Character* owner) {
    std::cout << "You equipped " << m_name << " (Tier: " << m_tier << ")!\n";

    owner->equip(this);
    
    return false; 
}