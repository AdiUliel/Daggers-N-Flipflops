#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <iostream>
#include <memory>
#include <vector>
#include <cctype>
#include "Character.h"

using std::string;
using std::unique_ptr;
using std::vector;

int random_int(int min, int max);

void print_stats(const Character* player);
void print_tutorial();
void change_player_class(unique_ptr<Character>& player);
string lowercase(string& str);
void print_class_details(const string& className);
void wait_for_enter();

// THE INPUT PROTECTORS: //
string get_string(const string& prompt);
int get_int(const string& prompt);

#endif