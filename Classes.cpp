#include "Classes.h"
#include <iostream>

using std::cout;
using std::string;

// Warrior: HP=150, Power=10, MP=0
Warrior::Warrior(const string& name) : Character(name, 150, 10, 0) {}
string Warrior::get_class_name() const { return "Warrior"; }

// Mage: HP=70, Power=5, MP=50
Mage::Mage(const string& name) : Character(name, 70, 5, 50) {}
string Mage::get_class_name() const { return "Mage"; }

// Archer: HP=100, Power=8, MP=0
Archer::Archer(const string& name) : Character(name, 100, 8, 0) {}
string Archer::get_class_name() const { return "Archer"; }

// Thief: HP=90, Power=6, MP=0
Thief::Thief(const string& name) : Character(name, 90, 6, 0) {}
string Thief::get_class_name() const { return "Thief"; }

// Normie: HP=1, Power=1, MP=0
Normie::Normie(const string& name) : Character(name, 1, 1, 0) {}
string Normie::get_class_name() const { return "Normie"; }