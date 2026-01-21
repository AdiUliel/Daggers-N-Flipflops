#include "Enemy.h"
#include "Utils.h"

Enemy::Enemy(int floor, MobType type) 
    : Character("Temp", 10, 1, 0), m_type(type)
{
    if (m_type == GOBLIN) {
        m_name = "Goblin";
        m_maxHP = (floor * 8) + 5;
        m_power = floor * 2;
        m_xpReward = 10 * floor;
        m_goldReward = random_int(2, 6) * floor;
    } 
    else if (m_type == BANDIT) {
        m_name = "Bandit";
        m_maxHP = (floor * 10) + 10;
        m_power = (floor * 2) + 2;
        m_xpReward = 15 * floor;
        m_goldReward = random_int(10, 20) * floor;
    } 
    else { // GHOST
        m_name = "Ghost";
        m_maxHP = (floor * 5) + 20;
        m_power = (floor * 3);
        m_xpReward = 20 * floor;
        m_goldReward = random_int(5, 10) * floor;
    }

    m_currentHP = m_maxHP;
}

int Enemy::attack() const {
    // נזק בטווח של הכוח +/- 2
    return random_int(m_power - 2, m_power + 2);
}

int Enemy::get_xp_reward() const {
    return m_xpReward;
}

int Enemy::get_gold_reward() const {
    return m_goldReward;
}

string Enemy::get_type_name() const {
    if (m_type == GOBLIN) return "Goblin";
    if (m_type == BANDIT) return "Bandit";
    return "Ghost";
}

string Enemy::get_class_name() const {
    return "Enemy";
}