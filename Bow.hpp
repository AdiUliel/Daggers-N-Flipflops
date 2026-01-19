#include "Weapon.hpp"
#include "Utils.h"

class Bow : public Weapon {
public:
    Bow() : Weapon("Longbow", 150) {}

    string get_action_name(Character* user) override {
        if (user->get_class_name() == "Thief") return "Poisoned Shot";
        return "Shoot Arrow";
    }

    void use(Character* user, Character* target) override {
        // 1. בדיקת תחמושת (נניח הוספנו has_item("Arrow") או משתנה arrows)
        // לצורך הדוגמה נניח שיש להם חצים תמיד כרגע
        
        int dmg = random_int(10, 20) * m_tier;

        if (user->get_class_name() == "Thief") {
            cout << "You dip the arrow in toxin before firing... ";
            dmg += 5 * m_tier; // תוספת נזק מיידית (או DoT בעתיד)
            // כאן אפשר להוסיף target->apply_status("POISON");
        } 
        else if (user->get_class_name() == "Warrior") {
            cout << "You pull the string too hard and fumble, but still hit. ";
            dmg -= 5; // לוחם גרוע בקשת
        }
        else {
            cout << "You fire a precise shot. ";
        }

        cout << "Hit for " << dmg << " damage.\n";
        target->damage(dmg);
    }
};