#include "Weapon.h"
#include "Character.h"
#include <iostream>

bool Weapon::use(Character* owner) {
    (void)owner;
    std::cout << "You examine the " << m_name << ". Looks sharp.\n";
    
    return false; 
}