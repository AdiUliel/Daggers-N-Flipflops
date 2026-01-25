#include "Classes.h"
#include "Utils.h"
#include <iostream>

using std::cout;
using std::string;

vector<string> all_classes = { "Warrior", "Mage", "Archer", "Thief", "Normie" };

// Warrior: HP=180, Power=11, MP=0
Warrior::Warrior(const string& name) : Character(name, 180, 11, 0) {}
string Warrior::get_class_name() const { return "Warrior"; }

// Mage: HP=90, Power=7, MP=50
Mage::Mage(const string& name) : Character(name, 90, 7, 50) {}
string Mage::get_class_name() const { return "Mage"; }

// Archer: HP=120, Power=9, MP=0
Archer::Archer(const string& name) : Character(name, 100, 9, 0) {}
string Archer::get_class_name() const { return "Archer"; }

// Thief: HP=110, Power=8, MP=0
Thief::Thief(const string& name) : Character(name, 90, 8, 0) {}
string Thief::get_class_name() const { return "Thief"; }

// Normie: HP=80, Power=5, MP=0
Normie::Normie(const string& name) : Character(name, 80, 5, 0, 30) {}
string Normie::get_class_name() const { return "Normie"; }