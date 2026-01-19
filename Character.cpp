#include "Character.h"

// BASE FUNCTIONS AND INFO:
Character::Character(const string& name) : 
    m_name(name), m_maxHP(DEFAULT_MAX_HP), m_maxMP(DEFAULT_MAX_MP), m_HP(m_maxHP), m_MP(m_maxMP), m_level(DEFAULT_LEVEL), m_exp(0), m_expUntilLevelUp(40), m_coins(69696969), m_power(DEFAULT_POWER),
    m_weapon(nullptr)
{}

Character::~Character() {
    if (m_weapon != nullptr) {
        delete m_weapon;
    }
}

void Character::set_name(string name){ 
    m_name = name;
}

string Character::get_name(){
    return m_name;
}

void Character::set_HP(int hp){
    m_HP = hp;
}

int Character::get_HP(){
    return m_HP;
}

void Character::set_MP(int mp){
    m_MP = mp;
}

int Character::get_MP(){
    return m_MP;
}

int Character::get_level(){
    return m_level;
}

int Character::get_exp() const { 
    return m_exp; 
}

int Character::get_exp_to_next_level() const { 
    return m_expUntilLevelUp; 
}

void Character::inc_level(){
    if (m_level <= 200) {
        m_level += 1;
    }
    else {
        cout << "Already Max Level. Sheeeeeeeeeeesh... \n";
    }
}

void Character::dec_level(){
    if (m_level >= 2) {
        m_level -= 1;
    }
    else {
        cout << "You are literally at the bottom of the food chain already - LEVEL 1 \n";
    }
}

int Character::get_coins(){
    return m_coins;
}

void Character::new_coins(int toGive){
    m_coins += toGive;
}

int Character::get_power(){
    return m_power;
}

void Character::heal(int hp) {
    if(hp > 0) {
        int newHp = m_HP + hp;
        if(newHp >= m_maxHP) {
            m_HP = m_maxHP;
        }
        else {
            m_HP = newHp;
        }
    }
}

void Character::damage(int hpDamage) {
    if(hpDamage >= m_HP) {
        m_HP = 0;
    }
    else if(hpDamage > 0) {
        m_HP-=hpDamage;
    }
}

bool Character::isKnockedOut() const {
    if(m_HP == 0) {
        return true;
    }
    return false;
}

void Character::lvl_up() {
    m_level++;

    m_maxHP+=20;
    m_maxMP+=10;
    m_power+=2;

    //HEAL UP:
    m_HP=m_maxHP;
    m_MP=m_maxMP;

    m_expUntilLevelUp = (m_expUntilLevelUp/4)*5;

    cout << "\n*** LEVEL UP! ***\n";
    cout << "Your'e " << m_level << "! Congratz or whatever... \n";
    cout << "<<<Stats increased! HP and MP fully restored>>>.\n";
}

void Character::gain_exp(int amount) {
    m_exp += amount;
    cout << "You gained " << amount << " XP!\n";

    while (m_exp >= m_expUntilLevelUp) {
        m_exp -= m_expUntilLevelUp;
        lvl_up();
    }
}

void Character::set_power(int toSet){
    m_power = toSet;
}

void Character::equip(Weapon* w) {
    if (m_weapon != nullptr) {
        delete m_weapon;
    }
    m_weapon = w;
    cout << "Equipped " << w->get_name() << "!\n";
}

Weapon* Character::get_weapon() const {
    return m_weapon;
}