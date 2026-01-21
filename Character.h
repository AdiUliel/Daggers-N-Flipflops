#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <iostream>
#include <vector>
#include "Item.h"
#include "Weapon.h" 

using std::string;
using std::cout;
using std::vector;

class Character {
protected:
    string m_name;
    int m_maxHP;
    int m_currentHP;
    int m_power;
    int m_maxMP;
    int m_currentMP;
    int m_coins;
    
    int m_level;
    int m_exp;
    int m_expToNextLevel;

    Weapon* m_weapon;
    vector<Item*> m_inventory; 

public:
    Character(string name, int hp, int power, int mp = 0) 
        : m_name(name), m_maxHP(hp), m_currentHP(hp), m_power(power), 
          m_maxMP(mp), m_currentMP(mp), m_coins(0), 
          m_level(1), m_exp(0), m_expToNextLevel(100),
          m_weapon(nullptr) {}

    virtual ~Character() {
        if (m_weapon != nullptr) delete m_weapon;
        for (Item* item : m_inventory) delete item;
        m_inventory.clear();
    }

    int get_level() const { return m_level; }
    int get_exp() const { return m_exp; }
    int get_exp_to_next_level() const { return m_expToNextLevel; }

    void gain_exp(int amount) {
        m_exp += amount;
        cout << "Gained " << amount << " XP.\n";
        if (m_exp >= m_expToNextLevel) {
            level_up();
        }
    }

    void level_up() {
        m_exp -= m_expToNextLevel;
        m_level++;
        m_expToNextLevel = (int)(m_expToNextLevel * 1.5);
        
        m_maxHP += 20;
        m_currentHP = m_maxHP;
        m_power += 5;
        
        cout << "\n*** LEVEL UP! Welcome to level " << m_level << " ***\n";
        cout << "Max HP increased to " << m_maxHP << ", Power increased to " << m_power << ".\n";
    }

    void add_item(Item* item);       
    void open_inventory();           
    void equip(Weapon* newWeapon);   

    string get_name() const { return m_name; }
    int get_HP() const { return m_currentHP; }
    int get_power() const { return m_power; }
    int get_coins() const { return m_coins; }
    int get_MP() const { return m_currentMP; }
    Weapon* get_weapon() const { return m_weapon; }

    void heal(int amount) {
        m_currentHP += amount;
        if (m_currentHP > m_maxHP) m_currentHP = m_maxHP;
    }
    
    void set_MP(int mp) {
        m_currentMP = mp;
        if (m_currentMP > m_maxMP) m_currentMP = m_maxMP;
        if (m_currentMP < 0) m_currentMP = 0;
    }

    void damage(int amount) {
        m_currentHP -= amount;
        if (m_currentHP < 0) m_currentHP = 0;
    }

    bool isKnockedOut() const { return m_currentHP <= 0; }

    void new_coins(int amount) {
        m_coins += amount;
        if (m_coins < 0) m_coins = 0;
    }
    
    virtual string get_class_name() const = 0; 
};

#endif