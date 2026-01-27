#ifndef CRAFTING_H
#define CRAFTING_H

#include "Item.h"
#include "BetterWeapon.hpp" 
#include <string>
#include <map>
#include <memory>
#include <algorithm>

using std::string;
using std::unique_ptr;
using std::map;
using std::make_unique;

struct RecipeResult {
    string name;
    int damage;
    int weight;
    string description;
};

class Crafting {
private:
    static map<string, RecipeResult> recipes;

    static string make_key(string name1, string name2) {
        if (name1 < name2) return name1 + "+" + name2;
        return name2 + "+" + name1;
    }

public:
    static void init(); 

    static unique_ptr<Item> try_craft(Item* item1, Item* item2);

};

#endif