#ifndef WEAPON_H
#define WEAPON_H

#include "Item.h"
#include <string>

class Character;

class Weapon : public Item {
protected:
    int m_damage;

public:
    Weapon(std::string name, int damage, std::string tier, int price)
        : Item(name, tier, price, "Wearable"), m_damage(damage) {}

    virtual ~Weapon() {}

    virtual int get_damage() const { return m_damage; }

    virtual std::string get_action_name(Character* user) const = 0;

    virtual void attack_action(Character* user, Character* target) const = 0;

    bool use(Character* owner) override;
};

#endif