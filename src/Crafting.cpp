#include "Crafting.h"
#include <iostream>

using std::string;

map<string, RecipeResult> Crafting::recipes;

string get_base_type(string fullName) {
    if (fullName.find("Sword") != string::npos) return "Sword";
    if (fullName.find("Hammer") != string::npos) return "Hammer";
    if (fullName.find("Crossbow") != string::npos) return "Crossbow"; 
    if (fullName.find("Bow") != string::npos) return "Bow";
    if (fullName.find("Staff") != string::npos) return "Staff";
    if (fullName.find("Wand") != string::npos) return "Wand";
    if (fullName.find("Dagger") != string::npos) return "Dagger";
    if (fullName.find("Stars") != string::npos) return "Throwing Stars";
    if (fullName.find("Pan") != string::npos) return "Frying Pan";
    if (fullName.find("Marbles") != string::npos) return "Marbles";
    if (fullName.find("Flipflops") != string::npos) return "Flipflops";
    
    return "Junk"; 
}

unique_ptr<Item> Crafting::try_craft(Item* item1, Item* item2) {
    string type1 = get_base_type(item1->get_name());
    string type2 = get_base_type(item2->get_name());
    
    string key = make_key(type1, type2);

    if (recipes.find(key) != recipes.end()) {
        RecipeResult res = recipes[key];
        return make_unique<BetterWeapon>(res.name, res.damage, res.weight, res.description);
    }

    string newName = "Jury-rigged " + item1->get_name(); 
    if (item1->get_name().length() > 3 && item2->get_name().length() > 3) {
        newName = item1->get_name().substr(0, 4) + "-" + item2->get_name();
    }
    
    int newDamage = (item1->get_price() + item2->get_price()) / 4; 
    if (newDamage < 5) newDamage = 5; 

    int newWeight = item1->get_weight() + item2->get_weight();
    
    return make_unique<BetterWeapon>(
        newName, 
        newDamage, 
        newWeight, 
        "A weird combination of items. It looks unstable."
    );
}

void Crafting::init() {
    if (!recipes.empty()) return; 

    // --- SWORD COMBINATIONS ---
    recipes["Hammer+Sword"] = {"Battle Axe", 25, 12, "A heavy blade that crushes and slices."};
    recipes["Bow+Sword"] = {"Bladed Bow", 18, 6, "Good for shooting, great for stabbing."};
    recipes["Crossbow+Sword"] = {"Bayonet Crossbow", 22, 10, "Pointy end goes into the enemy."};
    recipes["Staff+Sword"] = {"Glaive", 20, 8, "Long reach with a deadly edge."};
    recipes["Sword+Wand"] = {"Spellblade", 24, 5, "Crackle with magical energy."};
    recipes["Dagger+Sword"] = {"Duelist Set", 18, 4, "Parry this, you filthy casual."};
    recipes["Sword+Throwing Stars"] = {"Chakram", 16, 3, "A circular blade that defies physics."};
    recipes["Frying Pan+Sword"] = {"Broadsword", 20, 10, "It's wide enough to cook on."};
    recipes["Marbles+Sword"] = {"Caltrops", 10, 2, "Lego bricks made of steel."};

    // --- HAMMER COMBINATIONS ---
    recipes["Bow+Hammer"] = {"Greatbow", 30, 15, "Requires massive strength to draw."};
    recipes["Crossbow+Hammer"] = {"Siege Ballista", 40, 20, "Takes forever to load, but hits like a truck."};
    recipes["Hammer+Staff"] = {"Warhammer", 35, 14, "For when you really hate walls."};
    recipes["Hammer+Wand"] = {"Paladin's Mace", 28, 10, "Smite evil! Or just smite whatever."};
    recipes["Dagger+Hammer"] = {"Pickaxe", 22, 9, "Minecraft vibes."};
    recipes["Hammer+Throwing Stars"] = {"Morning Star", 26, 11, "Spiky and unfriendly."};
    recipes["Frying Pan+Hammer"] = {"Tenderizer", 15, 8, "Makes enemies soft and squishy."};
    recipes["Hammer+Marbles"] = {"Flail", 25, 10, "Unpredictable swinging death."};
    
    // --- BOW COMBINATIONS ---
    recipes["Bow+Crossbow"] = {"Compound Bow", 25, 8, "High-tech pulleys reduce the effort."};
    recipes["Bow+Dagger"] = {"Wrist Bow", 18, 3, "Hidden up your sleeve. Assassin style."};
    recipes["Bow+Frying Pan"] = {"Shield Bow", 20, 9, "The pan protects your face while you aim."};
    recipes["Bow+Marbles"] = {"Slingshot", 12, 2, "Childish, but hits surprisingly hard in the eye."};
    recipes["Bow+Staff"] = {"Bo-Staff", 22, 5, "Donatello would be proud."};
    recipes["Bow+Throwing Stars"] = {"Ricochet Bow", 18, 4, "Shoots stars that bounce off walls."};
    recipes["Bow+Wand"] = {"Energy Bow", 28, 4, "No strings attached. Literally."};

    // --- CROSSBOW COMBINATIONS ---
    recipes["Crossbow+Dagger"] = {"Grappling Hook", 15, 6, "Get over here!"};
    recipes["Crossbow+Frying Pan"] = {"Armored Turret", 30, 18, "Heavy, stationary, and terrifying."};
    recipes["Crossbow+Marbles"] = {"Blunderbuss", 32, 10, "Shoots a spray of glass shrapnel."};
    recipes["Crossbow+Staff"] = {"Sniper Rifle", 38, 12, "Long barrel for extreme accuracy."};
    recipes["Crossbow+Throwing Stars"] = {"Disc Launcher", 26, 8, "Pew Pew! Shoots spinning blades."};
    recipes["Crossbow+Wand"] = {"Railgun", 50, 15, "Uses magic magnets to accelerate projectiles."};

    // --- DAGGER COMBINATIONS ---
    recipes["Dagger+Frying Pan"] = {"Chef's Knife", 20, 7, "Yes, Chef!"};
    recipes["Dagger+Marbles"] = {"Trap Kit", 15, 3, "Broken glass and marbles on the floor."};
    recipes["Dagger+Staff"] = {"Scythe", 28, 8, "The Grim Reaper called, he wants his stick back."};
    recipes["Dagger+Throwing Stars"] = {"Chain Kunai", 18, 4, "Get over here! (Wait, used that already?)"};
    recipes["Dagger+Wand"] = {"Ritual Knife", 22, 3, "It glows with a sinister purple light."};

    // --- FRYING PAN COMBINATIONS ---
    recipes["Frying Pan+Marbles"] = {"Popcorn Machine", 40, 6, "Hot oil and exploding glass balls."};
    recipes["Frying Pan+Staff"] = {"Pizza Peel", 25, 9, "Fresh out of the oven! Deals burn damage."};
    recipes["Frying Pan+Throwing Stars"] = {"Saw Blade", 30, 8, "A jagged metal disk."};
    recipes["Frying Pan+Wand"] = {"Fireball Racket", 32, 7, "Serve straight into their face."};

    // --- STAFF COMBINATIONS ---
    recipes["Marbles+Staff"] = {"Orb Staff", 20, 6, "Ponder the orb while you whack goblins."};
    recipes["Staff+Throwing Stars"] = {"Wind Spinner", 22, 6, "A double-ended baton of slicing."};
    recipes["Staff+Wand"] = {"Archmage Staff", 40, 5, "Unlimited power!"};

    // --- OTHERS ---
    recipes["Marbles+Sword"] = {"Caltrops", 12, 4, "Lego bricks made of steel."};
    recipes["Marbles+Throwing Stars"] = {"Smoke Bombs", 10, 2, "Ninja vanish!"};
    recipes["Marbles+Wand"] = {"Floating Orbs", 24, 3, "They spin around you menacingly."};
    recipes["Sword+Throwing Stars"] = {"Chakram", 22, 5, "A throwing ring that always comes back."};
    recipes["Throwing Stars+Wand"] = {"Seeking Missiles", 25, 2, "They hunt the enemy down automatically."};
}