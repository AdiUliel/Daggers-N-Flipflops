#ifndef ENCOUNTER_H
#define ENCOUNTER_H

#include "Character.h"

class Encounter {
public:
    virtual ~Encounter() = default;

    virtual void run(Character* player) = 0; 
};

#endif