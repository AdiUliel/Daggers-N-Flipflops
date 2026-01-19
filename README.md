```text

Game.cpp (Main)
   │
   ▼
GameManager (Controller)
   │
   ├──▶ Utils
   │
   ├──▶ Encounter (Interface [ABSTRACT])
   │       ▲
   │       ├──▶ Battle
   │       ├──▶ Shop
   │       └──▶ WildCard
   │
   └──▶ Character (Base Class [ABSTRACT])
           ▲    │
           │    └──▶ Weapon (Strategy [ABSTRACT])
           │            ▲
           │            ├──▶ Bow
           │            └──▶ Staff
           │
           ├──▶ Enemy
           └──▶ Classes (Warrior, Mage, Thief ...)

Used Design Patters:
    - Singleton:
        Game is a singleton, which is in my opinion very unnecessary at this point, but I applied it for practice purposes.
    - Strategy:
        Usage of weapons - the player holds a pointer to an object m_weapon.
    - Factory:
        Used both in Battle class (run) and GameManager class (play_turn);
        In Battle, we draw a random mob and creating a new object of type Enemy.
        In GameManager, we draw a number deciding what is the next turn in our adventure (Battle/Shop/WildCard)
Relevant UML Dynamics:
    - Generalization: (Is a)
        - Encounter is the parent of: Battle, Shop, WildCard.
        - Character is the parent of: Warrior, Mage, Archer, Enemy.
        - Weapon is the parent of: Bow, Staff.
    - Composition: (Has a...)
        - GameManager Has a <m_player> - Player cannot exist without GameManager. GameManager's destructor will delete m_player.
        - Character Has a <m_weapon> - Weapon cannot exist without Character. Character's destructor will delete m_weapon.
    - Dependency: (Uses a)
        - Encounter uses Character (e.g in method 'run(Character* player)').
        - Weapon uses Charater (e.g in method 'use(Character* user, ... )').
        - Battle uses Enemy (in method 'run', Battle creates Enemy as a local variable).
        - GameManager uses Encounter (creates an encounter via Factory, uses it, and deletes it).

