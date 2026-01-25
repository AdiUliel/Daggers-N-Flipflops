#ifndef CLASSES_H
#define CLASSES_H

#include "Character.h"
#include <string>
#include <vector>
using std::string;

extern vector<string> all_classes;

class Warrior : public Character {
public:
    Warrior(const string& name);
    string get_class_name() const override;
    // Active - BattleRoar:
    void use_special_ability(Character* target) override{ 
        if (m_currentMP < 10) { cout << "Not enough Mana!\n";
            return;
        }
        m_currentMP -= 10;
        cout << m_name << " uses BATTLE ROAR! Enemy is stunned!\n";
        int dmg = m_power / 2;
        target->take_damage(dmg);
        target->apply_stun(1);
    }
    // Passive - IronSkin (ill implement it take_damage())
};

class Mage : public Character {
public:
    Mage(const string& name);
    string get_class_name() const override;
    // Active - Heal
    void use_special_ability(Character* target) override {
        (void)target; // Heal doesn't affect the target but this method is overriden
        if (m_currentMP < 20) {
            cout << "Not enough Mana!\n";
            return;
        }
        m_currentMP -= 20;
        int healAmount = m_power * 2;
        heal(healAmount);
        cout << m_name << " casts Heal and recovers " << healAmount << " HP!\n";
    }
    // Passive: Mana Regen
    void apply_passive_end_battle() override {
        m_currentMP = m_maxMP;
        cout << "Passive: Mage mana fully restored.\n";
    }
};

class Archer : public Character {
public:
    Archer(const string& name);
    string get_class_name() const override;
    // Active: Headshot
    void use_special_ability(Character* target) override {
        if (m_currentMP < 15) { cout << "Not enough Mana!\n"; return; }
        
        m_currentMP -= 15;
        cout << m_name << " aims for the head... BOOM!\n";
        target->take_damage(m_power * 2); // Critical Damage (x2) - will need to add m_critDamage, m_critRate in the future
    }
    // Passive: Always First (Managed in Battle.hpp)
};

class Thief : public Character {
public:
    Thief(const string& name);
    string get_class_name() const override;
    // Active: Shadowfight
    void use_special_ability(Character* target) override {
        (void)target;
        if (m_currentMP < 15) { cout << "Not enough Mana!\n"; return; }
        
        m_currentMP -= 15;
        m_dodgeDuration = 2;
        cout << m_name << " vanishes into the shadows! (50% Dodge chance)\n";
    }
    // Passive: Always Run
    bool try_run() override {
        return true;
    }
};

class Normie : public Character {
public:
    Normie(const string& name);
    string get_class_name() const override;
    // Active: Expensive Brothers
    void use_special_ability(Character* target) override {
        (void)target;
        if (m_normieBackupTimer > 0) { cout << "Help is already on the way!\n"; return; }
        
        cout << m_name << " calls the boys... 'They'll be here in 3 turns!'\n";
        m_normieBackupTimer = 3; 
    }
    
    // Passive: Inventory Expandage - NEEDS TO BE IMPLEMENTED
    void level_up() override {
        Character::level_up(); 
        m_bagCapacity += 10; 
        cout << "[Passive] BIG POCKETS: Your inventory grew! Max Capacity: " << m_bagCapacity << "\n";
    }
};

#endif