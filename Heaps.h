#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>

#include "Item.h"
#include "Item.cpp"

using namespace std;

int isNumber(string number)
{
    int countPoints = 0; // Counter for the number of decimal points and invalid characters.

    for (size_t i = 0; i < number.size(); i++)
    {
        if (!isdigit(number[i]) && number[i] != '.')
        {
            return -1; // Return -1 if a non-digit character that is not a '.' is encountered.
        }

        if (number[i] == '.')
        {
            countPoints++;
            if (countPoints > 1)
            {
                return -1; // Return -1 if more than one decimal point is encountered.
            }
        }
    }
    return countPoints; // return number of counts if is a valid number
}

void print(vector<Item> &items)
{
    for (Item item : items)
    {
        item.print();
    }
}

class Heap
{
protected:
    vector<Item> items;

public:
    // int MaxSize;
    virtual void deleteItem(string name) = 0;
    virtual void deleteItem(int price) = 0;
    virtual void insertItem(Item item) = 0;
    virtual void peak() = 0;
    virtual void heapify(int n, int index) = 0;
    void print()
    {
        for (int i = 0; i < items.size(); i++)
        {
            items[i].print();
        }
        cout << endl;
    }
    void swap(Item &a, Item &b)
    {
        Item temp = a;
        a = b;
        b = temp;
    }
};

class MinHeap : public Heap
{
protected:
public:
    void insertItem(Item item)
    {

        int size = items.size();
        items.push_back(item);

        // if the array(vector) is not empty heapify otherwise do nothing
        if (items.size() > 1)
        {
            for (int i = size / 2 - 1; i >= 0; i--)
            {
                heapify(items.size(), i);
            }
        }
    }

    void deleteItem(string name)
    {

        bool found = false;
        int size = items.size();
        int index;
        for (index = 0; index < size; index++)
        {
            if (name == items[index].getName())
            {
                found = true;
                break;
            }
        }

        if (!found)
        {
            cout << "item not found" << endl;
            return;
        }

        swap(items[index], items[size - 1]);
        items.pop_back();
        for (int i = size / 2 - 1; i >= 0; i--)
        {
            heapify(items.size(), i);
        }
    }

    void deleteItem(int price)
    {

        bool found = false;
        int size = items.size();
        int index;
        for (index = 0; index < size; index++)
        {
            if (price == items[index].getPrice())
            {
                found = true;
                break;
            }
        }

        if (!found)
        {
            cout << "item not found" << endl;
            return;
        }

        swap(items[index], items[size - 1]);
        items.pop_back();
        for (int i = size / 2 - 1; i >= 0; i--)
        {
            heapify(items.size(), i);
        }
    }

    void heapify(int n, int index)
    {

        int smallest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < n && items[left] < items[smallest])
            smallest = left;

        if (right < n && items[right] < items[smallest])
            smallest = right;

        if (smallest != index)
        {
            swap(items[index], items[smallest]);
            heapify(n, smallest);
        }
    }

    void peak()
    {
        if (!items.empty())
            items[0].print();
        return;
    }
};

class MaxHeap : public Heap
{
public:

    // insert item heapify the array
    void insertItem(Item item)
    {

        int size = items.size();
        items.push_back(item);

        // if the array(vector) is not empty heapify otherwise do nothing
        if (items.size() > 1)
        {
            for (int i = size / 2 - 1; i >= 0; i--)
            {
                heapify(items.size(), i);
            }
        }
    }


    // delete item then heapify the array
    void deleteItem(string name)
    {

        bool found = false;
        int index;
        int size = items.size();
        for (index = 0; index < size; index++)
        {

            if (name == items[index].getName())
            {
                found = true;
                break;
            }
        }

        if (!found)
        {
            cout << "item not found" << endl;
            return;
        }

        swap(items[index], items[size - 1]);
        items.pop_back();

        for (int i = size / 2 - 1; i >= 0; i--)
        {
            heapify(items.size(), i);
        }
    }

    // delete item then heapify the array
    void deleteItem(int price)
    {

        bool found = false;
        int size = items.size();
        int index;
        for (index = 0; index < size; index++)
        {

            if (price == items[index].getPrice())
            {
                found = true;
                break;
            }
        }

        if (!found)
        {
            cout << "item not found" << endl;
            return;
        }
        swap(items[index], items[size - 1]);
        items.pop_back();

        for (int i = size / 2 - 1; i >= 0; i--)
        {
            heapify(items.size(), i);
        }
    }

    void heapify(int n, int index)
    {

        int largest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < n && items[left] > items[largest])
            largest = left;

        if (right < n && items[right] > items[largest])
            largest = right;

        if (largest != index)
        {
            swap(items[index], items[largest]);

            heapify(n, largest);
        }
    }

    void peak()
    {
        if (!items.empty())
            items[0].print();
        return;
    }
};

class HeapsortMinHeap : public MinHeap
{
protected:
    void heapSort()
    {

        int size = items.size();
        for (int i = size / 2 - 1; i >= 0; i--)
            heapify(size, i);

        for (int i = size - 1; i >= 0; i--)
        {
            swap(items[0], items[i]);

            heapify(i, 0);
        }
    }

public:
    // insert Item then call heapsort
    void insertItem(Item item)
    {
        int size = items.size();
        items.push_back(item);
        heapSort();
    }

    // delete item then call heapsort
    void deleteItem(string name)
    {

        bool found = false;
        int index;
        int size = items.size();
        for (index = 0; index < size; index++)
        {

            if (name == items[index].getName())
            {
                found = true;
                break;
            }
        }

        if (!found)
        {
            cout << "item not found" << endl;
            return;
        }

        swap(items[index], items[size - 1]);
        items.pop_back();
        heapSort();
    }

    // delete item then call heapsort
    void deleteItem(int price)
    {

        bool found = false;
        int size = items.size();
        int index;
        for (index = 0; index < size; index++)
        {

            if (price == items[index].getPrice())
            {
                found = true;
                break;
            }
        }

        if (!found)
        {
            cout << "item not found" << endl;
            return;
        }
        swap(items[index], items[size - 1]);
        items.pop_back();
        heapSort();
    }
};

class HeapsortMaxHeap : public MaxHeap
{
protected:
    void heapSort()
    {

        int size = items.size();

        for (int i = size / 2 - 1; i >= 0; i--)
            heapify(size, i);

        for (int i = size - 1; i >= 0; i--)
        {

            swap(items[0], items[i]);

            heapify(i, 0);
        }
    }

public:

    // insert Item then call heapsort
    void insertItem(Item item)
    {
        int size = items.size();
        items.push_back(item);
        heapSort();
    }


    // delete item then call heapsort
    void deleteItem(string name)
    {

        bool found = false;
        int index;
        int size = items.size();
        for (index = 0; index < size; index++)
        {

            if (name == items[index].getName())
            {
                found = true;
                break;
            }
        }

        if (!found)
        {
            cout << "item not found" << endl;
            return;
        }

        swap(items[index], items[size - 1]);
        items.pop_back();
        heapSort();
    }

    // delete item then call heapsort
    void deleteItem(int price)
    {

        bool found = false;
        int size = items.size();
        int index;
        for (index = 0; index < size; index++)
        {

            if (price == items[index].getPrice())
            {
                found = true;
                break;
            }
        }

        if (!found)
        {
            cout << "item not found" << endl;
            return;
        }
        swap(items[index], items[size - 1]);
        items.pop_back();
        heapSort();
    }
};

//  get Items info and store them in vector
void getItems(ifstream &file, Heap *heapType, int &sortBy)
{
    string name;
    string category;
    int price;

    int lineNumber = 1; // to follow current line number
    int numberOfItems = 0;

    vector<Item> items;
    string line;

    while (getline(file, line))
    {
        stringstream ss(line);
        string data;

        if (lineNumber == 1)
        {
            while (ss >> data)
            {
                numberOfItems = stoi(data);
            }
        }
        else
        {
            while (ss >> data)
            {
                if (isNumber(data) == -1)
                {
                    if (name.empty())
                    {
                        name = line;
                        continue;
                    }
                    else
                    {
                        category = data;
                    }
                }
                else if (isNumber(data) == 0)
                {
                    price = stoi(data);
                    heapType->insertItem(Item(name, category, price, sortBy));
                    name.clear();
                    category.clear();
                }
            }
        }
        lineNumber++;
    }


}

void heap()
{

    int sortBy;     // give user to choice sort by name or price
    int sortFrom;   // give user to choice sorting in descending or ascending order
    int algoChoice; // give user to choice between heaps
    Heap *algo;
    ifstream file;
    file.open("Items.txt");

    cout << "To sort:" << endl;
    cout << "1 - by name (press key 1)" << endl;
    cout << "2 - by price (press key 2)" << endl;
    cin >> sortBy;



    cout << "choice a heap:" << endl;
    cout << "1 - Max heap  (press 1)" << endl;
    cout << "2 - Min heap  (press key 2) " << endl;
    cout << "3 - Heap sort 'using max heap' - 'ascending' (press key 3)" << endl;
    cout << "4 - Heap sort  'using min heap' - 'descending'  (press key 4)" << endl;
    cin >> algoChoice;

    if (algoChoice == 1 || algoChoice == 2)
    {

        if (algoChoice == 1)
        {
            algo = new MaxHeap();
            getItems(file, algo, sortBy); // Call the function to read items
            // algo->deleteItem(20); // you delete item by price
            // algo->deleteItem("cheese cake"); // you delete item by name
            algo->print();
        }

        else
        {
            algo = new MinHeap();
            getItems(file, algo, sortBy); // Call the function to read items
            // algo->deleteItem(20); // you delete item by price
            // algo->deleteItem("cheese cake"); // you delete item by name
            algo->print();
        }
    }

    else if (algoChoice == 3 || algoChoice == 4)
    {

        if (algoChoice == 3)
        {
            HeapsortMaxHeap *algo = new HeapsortMaxHeap();
            getItems(file, algo, sortBy); // Call the function to read items
            algo->deleteItem(20);
            algo->insertItem(Item("ko", "cafe", 321));
            algo->print();
        }

        else
        {
            HeapsortMinHeap *algo = new HeapsortMinHeap();
            getItems(file, algo, sortBy);    // Call the function to read items
            getItems(file, algo, sortBy);    // Call the function to read items
            algo->deleteItem("cheese cake"); // you delete item by name
            algo->insertItem(Item("ko", "cafe", 321));

            algo->print();
        }
    }
}
