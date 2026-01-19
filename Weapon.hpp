#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include <iostream>

using std::string;
using std::cout;

class Character; 

class Weapon {
protected:
    string m_name;
    int m_tier;
    int m_price;

public:
    Weapon(string name, int price) : m_name(name), m_tier(1), m_price(price) {}
    virtual ~Weapon() = default;

    void upgrade() {
        if (m_tier < 3) {
            m_tier++;
            m_price *= 2; 
            cout << m_name << " upgraded to Tier " << m_tier << "!\n";
        } else {
            cout << "Weapon is already at Max Tier!\n";
        }
    }

    string get_name() const { return m_name; }
    int get_price() const { return m_price; }

    virtual string get_action_name(Character* user) = 0;

    virtual void use(Character* user, Character* target) = 0;
};

#endif