#include "Item.h"

Item::Item(string name, string category, int price, int compareWay = 1)
{
    this->name = name;
    this->category = category;
    this->price = price;
    this->compareWay;
}

bool Item::operator<(const Item &other)
{

    // compare by name
    if (compareWay == 1)
        return name < other.name;

    // compare by price
    return price < other.price;
}

bool Item::operator>(const Item &other)
{

    // compare by name
    if (compareWay == 1)
        return name > other.name;

    // compare by price
    return price > other.price;
}


string Item::getName() { return name; }
string Item::getCategory() { return category; }
int Item::getPrice() { return price; }

void Item::print()
{
    cout << name << '\n'
         << category << '\n'
         << price << endl
         << endl;
}

