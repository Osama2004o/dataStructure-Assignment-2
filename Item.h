#ifndef ITEM_H
#define ITEM_H

#include<iostream>
#include<vector>
#include<string>


using namespace std;
#pragma once

class Item
{
    string name;
    string category;
    int price;
    int compareWay;

public:
    Item(string name, string category, int price, int compareWay);
 

    bool operator<(const Item &other);
    bool operator>(const Item &other);

    
    void print();
    string getName();
    string getCategory();
    int getPrice();
};

#endif