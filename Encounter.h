#ifndef ENCOUNTER_H
#define ENCOUNTER_H

#include <memory>
#include "Character.h"
using std::unique_ptr;

class Encounter {
public:
    virtual ~Encounter() = default;

    virtual void run(unique_ptr<Character>& player) = 0; 
};

#endif