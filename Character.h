#ifndef CHARACTER_H
#define CHARACTER_H

#include <iostream>
#include <vector>
#include <string>
#include "Weapon.hpp" 

using std::string;
using std::cout;

class Character {
private:
    string m_name;
    int m_maxHP;
    int m_maxMP;
    int m_HP;
    int m_MP;
    int m_level;
    int m_exp;
    int m_expUntilLevelUp;
    int m_coins;
    int m_power;
    static const int DEFAULT_POWER = 500; // TO CHANGE
    static const int DEFAULT_MAX_HP = 100;
    static const int DEFAULT_MAX_MP = 200;
    static const int DEFAULT_LEVEL = 1;

    Weapon* m_weapon;

    void lvl_up();

public:
    Character(const string& name);

    virtual ~Character();

    void set_name(string name);
    string get_name();

    void set_HP(int hp);
    int get_HP();

    void set_MP(int mp);
    int get_MP();

    int get_level();
    void inc_level();
    void dec_level();

    int get_coins();
    void new_coins(int toGive);

    int get_power();
    void heal(int hp);
    void damage(int hpDamage);

    bool isKnockedOut() const;

    void set_power(int toSet);

    void gain_exp(int toGive);

    int get_exp() const;

    int get_exp_to_next_level() const;

    virtual string get_class_name() const = 0;

    void equip(Weapon* w);
    Weapon* get_weapon() const;
};

#endif