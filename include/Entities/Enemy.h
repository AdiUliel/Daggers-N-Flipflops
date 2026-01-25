#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"

class Enemy : public Character {
public:
    enum MobType {
        GOBLIN,
        BANDIT,
        GHOST
    };

private:
    MobType m_type;
    int m_minDamage;
    int m_maxDamage;
    int m_xpReward;
    int m_goldReward;

public:
    Enemy(int floor, MobType type);

    int attack() const;

    int get_xp_reward() const;
    int get_gold_reward() const;
    string get_type_name() const;
    
    string get_class_name() const override; 

    void use_special_ability(Character* target) override;
};

#endif