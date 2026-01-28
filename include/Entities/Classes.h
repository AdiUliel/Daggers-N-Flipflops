#ifndef CLASSES_H
#define CLASSES_H

#include "Character.h"
#include "Utils.h"
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
    // Passive - IronSkin (implemented in take_damage or similar)
};

class Mage : public Character {
public:
    Mage(const string& name);
    string get_class_name() const override;
    // Active - Heal
    void use_special_ability(Character* target) override {
        (void)target; 
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
        target->take_damage(m_power * 2); 
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
    // Passive: Better chance to escape
    bool try_run() override {
        return random_int(1, 100) <= 75;
    }
};

class Normie : public Character {
public:
    Normie(const string& name);
    string get_class_name() const override;

    // Active: Call The Boys (Cooldown Based)
    void use_special_ability(Character* target) override {
        (void)target;

        // 1. Check Cooldown instead of MP
        if (m_specialCooldown > 0) {
            cout << "You can't call the boys again yet! (Wait " << m_specialCooldown << " turns)\n";
            return;
        }

        // 2. Check if help is currently active/arriving
        if (m_normieBackupTimer > 0) { 
            cout << "Help is already on the way!\n"; 
            return; 
        }
        
        // 3. Activate Ability
        cout << m_name << " pulls out a phone and sends a text...\n";
        cout << "'The Boys' will arrive in 3 turns to beat up the enemy!\n";
        
        m_normieBackupTimer = 3;  // Backup arrives in 3 turns
        m_specialCooldown = 8;   // Set Cooldown 
    }
    
    // Passive: Big Pockets
    void level_up() override {
        Character::level_up(); 
        m_bagCapacity += 10; 
        cout << "[Passive] BIG POCKETS: Your inventory grew! Max Capacity: " << m_bagCapacity << "\n";
    }
};

#endif