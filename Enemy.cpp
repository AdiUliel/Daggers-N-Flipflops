#include "Enemy.h"
#include "Utils.h"

Enemy::Enemy(int floor, MobType mob) : Character("TempName"), m_type(mob)
{
    int base_hp = 0;
    int base_min_dmg = 0;
    int base_max_dmg = 0;
    string name = "";
    
    switch(mob) {
        case GOBLIN:
        name = "Greedy Goblin";
        base_hp = 30 + (floor * 5);
        base_min_dmg = 2 + (floor * 1);
        base_max_dmg = 5 + (floor * 2);
        m_xpReward = 10 + (floor * 2);
        m_goldReward = 5 + floor;
        break;

    case BANDIT:
        name = "Bitter Bandit";
        base_hp = 50 + (floor * 6);
        base_min_dmg = 4 + (floor * 2);
        base_max_dmg = 8 + (floor * 3);
        m_xpReward = 20 + (floor * 3);
        m_goldReward = 15 + (floor * 2);
        break;

    case GHOST:
        name = "Goofy Ghost";
        base_hp = 20 + (floor * 4);
        base_min_dmg = 8 + (floor * 3);
        base_max_dmg = 12 + (floor * 4);
        m_xpReward = 30 + (floor * 4);
        m_goldReward = 20 + (floor * 3);
        break;
    }

    set_name(name);
    set_HP(base_hp);
    m_minDamage = base_min_dmg;
    m_maxDamage = base_max_dmg;

}

int Enemy::attack() const {
    return random_int(m_minDamage, m_maxDamage);
}

int Enemy::get_xp_reward() const {
    return m_xpReward;
}

int Enemy::get_gold_reward() const {
    return m_goldReward;
}

string Enemy::get_type_name() const {
    switch (m_type) {
        case GOBLIN: return "Goblin";
        case BANDIT: return "Bandit";
        case GHOST: return "Ghost";
        default: return "Unknown";
    }
}

string Enemy::get_class_name() const {
    return "Enemy";
}