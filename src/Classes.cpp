#include "Classes.h"
#include "Utils.h"
#include <iostream>

using std::cout;
using std::string;

vector<string> all_classes = { "Warrior", "Mage", "Archer", "Thief", "Normie" };

// Warrior: High HP + control, average damage
// HP=160, Power=10, MP=25
Warrior::Warrior(const string& name) : Character(name, 160, 10, 25) {}
string Warrior::get_class_name() const { return "Warrior"; }

// Mage: Lower HP, scales via MP (more special usage)
// HP=105, Power=8, MP=80
Mage::Mage(const string& name) : Character(name, 105, 8, 80) {}
string Mage::get_class_name() const { return "Mage"; }

// Archer: Faster opener, consistent damage
// HP=115, Power=10, MP=25
Archer::Archer(const string& name) : Character(name, 115, 10, 25) {}
string Archer::get_class_name() const { return "Archer"; }

// Thief: Mobility + dodge utility, slightly lower raw stats than Warrior/Archer
// HP=110, Power=9, MP=30
Thief::Thief(const string& name) : Character(name, 110, 9, 30) {}
string Thief::get_class_name() const { return "Thief"; }

// Normie: Weak start, strong progression via inventory/crafting
// HP=90, Power=6, MP=0, Capacity=30
Normie::Normie(const string& name) : Character(name, 90, 6, 0, 30) {}
string Normie::get_class_name() const { return "Normie"; }