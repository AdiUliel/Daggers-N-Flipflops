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
   │       └──▶ Classes (Warrior, Mage, Thief ...)
   │
   └──▶ Item (Base Class [ABSTRACT])
           ▲
           ├──▶ Potion
           └──▶ Weapon (Strategy [ABSTRACT])
                   ▲
                   ├──▶ Bow
                   └──▶ Staff

Used Design Patterns:
    - Singleton:
        Game is a singleton.
    - Strategy:
        Usage of items and weapons. The player holds a pointer to m_weapon and a vector of Items.
        Calling use() executes different logic depending on the concrete class (Potion/Weapon).
    - Factory:
        Used both in Battle class (run) and GameManager class (play_turn);
        In Battle, we draw a random mob and creating a new object of type Enemy.
        In GameManager, we draw a number deciding what is the next turn in our adventure (Battle/Shop/WildCard).

Relevant UML Dynamics:
    - Generalization: (Is a)
        - Encounter is the parent of: Battle, Shop, WildCard.
        - Character is the parent of: Warrior, Mage, Archer, Enemy.
        - Item is the parent of: Potion, Weapon.
        - Weapon is the parent of: Bow, Staff.
    - Composition: (Has a...)
        - GameManager Has a <m_player> - Player cannot exist without GameManager. GameManager's destructor will delete m_player.
        - Character Has a <m_inventory> - Vector of Items. Character manages their lifecycle.
        - Character Has a <m_weapon> - Pointer to active Weapon.
    - Dependency: (Uses a)
        - Encounter uses Character (e.g in method 'run(Character* player)').
        - Item uses Character (e.g in method 'use(Character* owner)').
        - Battle uses Enemy (in method 'run', Battle creates Enemy as a local variable).
        - GameManager uses Encounter (creates an encounter via Factory, uses it, and deletes it).