#ifndef ENCOUNTER_H
#define ENCOUNTER_H

#include <memory>
#include "Character.h"
using std::unique_ptr;

/**
 * @class Encounter
 * @brief An abstract base class representing any event in the game.
 * * This uses the Strategy/Command pattern structure.
 * * The GameManager generates a specific Encounter (Battle/Shop/WildCard)
 * and calls run() without knowing the specific type.
 */
class Encounter {
public:
    virtual ~Encounter() = default;

    /**
     * @brief Executes the encounter logic.
     * @param player Reference to the unique_ptr owning the player. 
     * Allows the encounter to modify the player state (HP, Inventory, etc).
     */
    virtual void run(unique_ptr<Character>& player) = 0; 
};

#endif