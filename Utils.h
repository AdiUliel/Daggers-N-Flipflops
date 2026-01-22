#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <iostream>
#include "Character.h"

int random_int(int min, int max);

void print_stats(const Character* player);
void print_tutorial();

// THE INPUT PROTECTORS: //
string get_string(const string& prompt);
int get_int(const string& prompt);
#endif