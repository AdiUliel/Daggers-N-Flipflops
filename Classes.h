#ifndef CLASSES_H
#define CLASSES_H

#include "Character.h"
#include <string>
#include <vector>
using std::string;

extern vector<string> all_classes;

class Warrior : public Character {
public:
    Warrior(const string& name);
    string get_class_name() const override;
};

class Mage : public Character {
public:
    Mage(const string& name);
    string get_class_name() const override;
};

class Archer : public Character {
public:
    Archer(const string& name);
    string get_class_name() const override;
};

class Thief : public Character {
public:
    Thief(const string& name);
    string get_class_name() const override;
};

class Normie : public Character {
public:
    Normie(const string& name);
    string get_class_name() const override;
};

#endif