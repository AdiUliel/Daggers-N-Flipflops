#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <iostream>
using std::string; 

class Character; 

class Item {
protected:
    std::string m_name;
    std::string m_tier;
    int m_price;
    std::string m_type;

public:
    Item(std::string name, std::string tier, int price, std::string type) : m_name(name), m_tier(tier), m_price(price), m_type(type) {}
    virtual ~Item() {}

    std::string get_name() const { return m_name; }
    std::string get_tier() const { return m_tier; }
    int get_price() const { return m_price; }
    std::string get_type() const { return m_type; }

    virtual bool use(Character* owner) = 0;
};

#endif