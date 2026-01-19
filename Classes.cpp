#include "Classes.h"

// Warrior
Warrior::Warrior(const string& name) : Character(name) {
    set_HP(150);
    set_MP(50);
}
string Warrior::get_class_name() const { return "Warrior"; }

// Mage
Mage::Mage(const string& name) : Character(name) {
    set_HP(70);
    set_MP(300);
}
string Mage::get_class_name() const { return "Mage"; }

// Archer
Archer::Archer(const string& name) : Character(name) {
    set_HP(100);
    set_MP(100);
}
string Archer::get_class_name() const { return "Archer"; }

// Thief
Thief::Thief(const string& name) : Character(name) {
    set_HP(90);
    set_MP(80);
}
string Thief::get_class_name() const { return "Thief"; }

// Normie
Normie::Normie(const string& name) : Character(name) {
}
string Normie::get_class_name() const { return "Normie"; }