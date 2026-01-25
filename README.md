# ⚔️ Daggers & Flipflops 🩴
**A Text-Based C++ RPG Adventure**

Welcome to the Endless Tower. Fight monsters, collect loot, manage your inventory weight, and try not to die (spoiler: you will).

## 📂 Project Structure
The project follows a clean `src/include` separation:

```text
Daggers-N-Flipflops/
│
├── bin/                 # Compiled executable (game.exe)
├── src/                 # Source files (.cpp) - Main logic implementation
└── include/             # Header files (.h / .hpp)
    ├── Core/            # Game loop, Utils, GameManager
    ├── Encounters/      # Battle, Shop, WildCard logic
    ├── Entities/        # Character base, Enemy, Player Classes
    └── Items/           # Item base class
        ├── Potions/     # Health & Mana potions
        └── Weapons/     # All weapon classes (Sword, Bow, Flipflops...)
```
## Compiling Command:
g++ -std=c++14 -static -Wall -Wextra -I./include/Core -I./include/Encounters -I./include/Entities -I./include/Items -I./include/Items/Potions -I./include/Items/Weapons -o bin/game.exe src/*.cpp
## Run:
./bin/game.exe

## 🎮 Game Features
5 Unique Classes:
    - Warrior: High HP, stuns enemies.
    - Mage: High Magic, self-healing.
    - Archer: High Crit, always attacks first.
    - Thief: High Dodge chance, can escape battles.
    - Normie: Starts weak, but has Big Pockets (Huge inventory) and can call for backup (The Boys).

Strategic Combat: Choose between Attacking, Defending, Using Abilities, or Items.

Inventory System: Manage your Weight Capacity. Stronger items are heavier!

Random Encounters: Battles, Shops, and "Wildcard" events.

Loot & Economy: Earn coins, buy potions, and find legendary weapons (like La Chancla).

## 🛠️ Technical Architecture
```text
Game.cpp (Main)
   │
   ▼
GameManager (Controller)
   │
   ├──▶ Utils
   │
   ├──▶ Encounter (Base Class [ABSTRACT])
   │       ▲
   │       ├──▶ Battle
   │       ├──▶ Shop
   │       └──▶ WildCard
   │
   ├──▶ Character (Base Class [ABSTRACT])
   │       ▲
   │       ├──▶ Enemy
   │       └──▶ Classes (Warrior, Mage, Thief, ...)
   │
   └──▶ Item (Base Class [ABSTRACT])
           ▲
           ├──▶ HealthPotion
           │
           ├──▶ ManaPotion
           │
           └──▶ Weapon (Strategy [ABSTRACT])
                   ▲
                   ├──▶ Bow, Staff, Hammer, Marbles, ...
                   └──▶ FLIPFLOPS

Used Design Patterns:
    - Singleton:
        `Game` is a singleton instance managing the entry point.
    - Strategy:
        Implemented in Items and Weapons. The Player holds a pointer to `m_weapon` (abstract strategy).
        Calling `use()` executes different logic depending on the concrete class (e.g., a Potion heals, a Weapon attacks).
    - Factory:
        Used in multiple locations:
        1. **Battle:** Draws a random mob type and creates a new object of type `Enemy`.
        2. **Shop:** Generates random weapon IDs and creates concrete `Weapon` objects for sale.
        3. **GameManager:** Draws a number deciding the next `Encounter` type (Battle/Shop/WildCard).

Relevant UML Dynamics:
    - Generalization: (Is a...)
        - `Encounter` is the parent of: `Battle`, `Shop`, `WildCard`.
        - `Character` is the parent of: `Warrior`, `Mage`, `Archer`, `Normie`, `Enemy`.
        - `Item` is the parent of: `Potion`, `Weapon`.
        - `Weapon` is the parent of: `Bow`, `Staff`, `Sword`, etc.
    - Composition: (Has a...)
        - `GameManager` has a `m_player` (Managed via `unique_ptr`). Player cannot exist without GameManager.
        - `Character` has a `m_inventory` (Vector of Items). Character manages their lifecycle.
        - `Character` has a `m_weapon` (Pointer to active Weapon strategy).
    - Dependency: (Uses a...)
        - `Encounter` uses `Character` (e.g., in method `run(Character* player)`).
        - `Item` uses `Character` (e.g., in method `use(Character* owner)`).
        - `Battle` uses `Enemy` (in method `run`, Battle creates `Enemy` as a local variable).
        - `GameManager` uses `Encounter` (creates an encounter via Factory, uses it, and deletes it).