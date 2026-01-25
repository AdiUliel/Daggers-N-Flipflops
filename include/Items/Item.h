#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <iostream>
using std::string; 

class Character; 

class Item {
protected:
    std::string m_name;
    std::string m_type;
    int m_tier;
    int m_weight;
    int m_price;

public:
    Item(std::string name, std::string type, int tier, int weight = 1, int price = 1) : m_name(name), m_type(type), m_tier(tier), m_weight(weight), m_price(price) {}
    virtual ~Item() {}

    std::string get_name() const { return m_name; }
    std::string get_type() const { return m_type; }
    int get_tier() const { return m_tier; }
    int get_weight() const { return m_weight; } 
    int get_price() const { return m_price; }
    
    virtual bool use(Character* owner) = 0;
};

#endif