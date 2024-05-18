#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int compareWay = 1;
int algoWay = 0;

class Item
{
    string name;
    string category;
    int price;

public:
    Item(string name = "", string category = "", int price = 0)
    {
        this->name = name;
        this->category = category;
        this->price = price;
    }

    bool operator<(const Item &other) const
    {
        // compare by name
        if (compareWay == 1)
            return name < other.name;

        // compare by price
        else
            return price < other.price;
    }
    bool operator>(const Item &other) const
    {
        // compare by name
        if (compareWay == 1)
            return name > other.name;

        // compare by price
        else
            return price > other.price;
    }

    bool operator==(const Item &other) const
    {
        return name == other.name && category == other.category && price == other.price;
    }

    void print() const
    {
        cout << "Name: " << name << '\n'
             << "Category: " << category << '\n'
             << "Price: " << price << endl
             << endl;
    }

    string getName() const
    {
        return name;
    }
    string getCategory() const
    {
        return category;
    }
    int getPrice() const
    {
        return price;
    }
};

template <typename T>
class Node
{
public:
    T key;
    Node *left;
    Node *right;
    int height;

    Node(T k) : key(k), left(nullptr), right(nullptr), height(1) {}
};

template <typename T>
class AVLTree
{
private:
    Node<Item> *root;

    int height(Node<T> *N)
    {
        if (N == nullptr)
            return 0;
        return N->height;
    }

    int max(int a, int b)
    {
        return (a > b) ? a : b;
    }

    Node<T> *rightRotate(Node<T> *y)
    {
        Node<T> *x = y->left;
        Node<T> *T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        return x;
    }

    Node<T> *leftRotate(Node<T> *x)
    {
        Node<T> *y = x->right;
        Node<T> *T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        return y;
    }

    int getBalance(Node<T> *N)
    {
        if (N == nullptr)
            return 0;
        return height(N->left) - height(N->right);
    }

    Node<T> *insert(Node<T> *node, T key)
    {
        if (node == nullptr)
            return (new Node<T>(key));

        if (key < node->key)
            node->left = insert(node->left, key);
        else if (key > node->key)
            node->right = insert(node->right, key);
        else
            return node;

        node->height = 1 + max(height(node->left), height(node->right));

        int balance = getBalance(node);

        if (balance > 1 && key < node->left->key)
            return rightRotate(node);

        if (balance < -1 && key > node->right->key)
            return leftRotate(node);

        if (balance > 1 && key > node->left->key)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && key < node->right->key)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    void inOrder(Node<T> *root)
    {
        if (root != nullptr)
        {
            inOrder(root->left);
            cout << root->key << " ";
            inOrder(root->right);
        }
    }

    void descending(Node<T> *root)
    {
        if (root != nullptr)
        {
            descending(root->right);
            cout << root->key << " ";
            descending(root->left);
        }
    }

    Node<T> *minValueNode(Node<T> *node)
    {
        Node<T> *current = node;

        while (current->left != nullptr)
            current = current->left;

        return current;
    }

    Node<T> *deleteNode(Node<T> *root, T key)
    {
        if (root == nullptr)
            return root;

        if (key < root->key)
            root->left = deleteNode(root->left, key);
        else if (key > root->key)
            root->right = deleteNode(root->right, key);
        else
        {
            if ((root->left == nullptr) || (root->right == nullptr))
            {
                Node<T> *temp = root->left ? root->left : root->right;

                if (temp == nullptr)
                {
                    temp = root;
                    root = nullptr;
                }
                else
                    *root = *temp;

                delete temp;
            }
            else
            {
                Node<T> *temp = minValueNode(root->right);

                root->key = temp->key;

                root->right = deleteNode(root->right, temp->key);
            }
        }

        if (root == nullptr)
            return root;

        root->height = 1 + max(height(root->left), height(root->right));

        int balance = getBalance(root);

        if (balance > 1 && getBalance(root->left) >= 0)
            return rightRotate(root);

        if (balance > 1 && getBalance(root->left) < 0)
        {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        if (balance < -1 && getBalance(root->right) <= 0)
            return leftRotate(root);

        if (balance < -1 && getBalance(root->right) > 0)
        {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(T key)
    {
        root = insert(root, key);
    }

    void deleteNode(T key)
    {
        root = deleteNode(root, key);
    }

    void inOrder()
    {
        inOrder(root);
    }
    void descending()
    {
        descending(root);
    }
};

template <typename T>
class BSTNode
{
public:
    T key;
    BSTNode *right, *left;

    BSTNode()
    {
        key = T();
        right = left = nullptr;
    }
    BSTNode(const T &k, BSTNode *r = nullptr, BSTNode *l = nullptr)
    {
        key = k;
        left = l;
        right = r;
    }
    T getKey()
    {
        return key;
    }
};

template <typename T>
class bst
{
    BSTNode<T> *root;

public:
    bst()
    {
        root = nullptr;
    }
    bool isEmpty()
    {
        return root == nullptr;
    }

    T *search(T &el)
    {
        BSTNode<T> *p = root;
        while (p != nullptr)
        {
            if (el == p->key)
            {
                return &p->key;
            }
            else if (el < p->key)
            {
                p = p->left;
            }
            else
            {
                p = p->right;
            }
        }
        return nullptr;
    }

    void insertNode(T el)
    {
        BSTNode<T> *p = root, *prev = nullptr;
        while (p != nullptr)
        {
            prev = p;
            if (p->key > el)
            {
                p = p->left;
            }
            else
            {
                p = p->right;
            }
        }
        if (root == nullptr)
        {
            root = new BSTNode<T>(el);
        }
        else if (prev->key > el)
        {
            prev->left = new BSTNode<T>(el);
        }
        else
        {
            prev->right = new BSTNode<T>(el);
        }
    }

    void deleteNode(const T &key)
    {
        root = deleteNode(root, key);
    }

    BSTNode<T> *deleteNode(BSTNode<T> *node, const T &key)
    {
        if (node == nullptr)
        {
            return node;
        }

        if (key < node->key)
        {
            node->left = deleteNode(node->left, key);
        }
        else if (key > node->key)
        {
            node->right = deleteNode(node->right, key);
        }
        else
        {
            if (node->left == nullptr)
            {
                BSTNode<T> *temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr)
            {
                BSTNode<T> *temp = node->left;
                delete node;
                return temp;
            }

            BSTNode<T> *temp = minValueNode(node->right);
            node->key = temp->key;
            node->right = deleteNode(node->right, temp->key);
        }
        return node;
    }

    BSTNode<T> *minValueNode(BSTNode<T> *node)
    {
        BSTNode<T> *current = node;
        while (current && current->left != nullptr)
        {
            current = current->left;
        }
        return current;
    }

    void printInorder(BSTNode<T> *node)
    {
        if (!node)
            return;
        printInorder(node->left);
        node->key.print();
        printInorder(node->right);
    }
    void inOrderCall()
    {
        printInorder(root);
        cout << endl;
    }

    void printDescending(BSTNode<T> *node)
    {
        if (!node)
            return;
        printDescending(node->right);
        node->key.print();
        printDescending(node->left);
    }
    void descendingCall()
    {
        printDescending(root);
        cout << endl;
    }
};

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
                    heapType->insertItem(Item(name, category, price));
                    name.clear();
                    category.clear();
                }
            }
        }
        lineNumber++;
    }
}
void getItemsBST(ifstream &file, bst<Item> &bstTree, int &sortBy)
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
                    bstTree.insertNode(Item(name, category, price));
                    name.clear();
                    category.clear();
                }
            }
        }
        lineNumber++;
    }
}
void getItemsForAvl(ifstream &file, AVLTree<Item> av, int &sortBy)
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

                    av.insert(Item(name, category, price));

                    name.clear();
                    category.clear();
                }
            }
        }
        lineNumber++;
    }
}

int main()
{

    int sortBy;              // give user to choice sort by name or price
    int chooseDataStructure; // give user to choice sorting in descending or ascending order
    int algoChoice;          // give user to choice between heaps
    Heap *algo;
    ifstream file;
    file.open("Items.txt");

    cout << "1 - BST" << endl;
    cout << "2 - AVL" << endl;
    cout << "3 - HEAP" << endl;
    cout << "choose the data structure you wanna use: ";
    cin >> chooseDataStructure;
    if (chooseDataStructure == 1)
    {
        bst<Item> s;
        s.insertNode(Item("ko", "cafe", 321));
        s.insertNode(Item("do", "cafe", 321));
        s.insertNode(Item("ao", "cafe", 321));
        s.insertNode(Item("bo", "cafe", 321));
        getItemsBST(file, s, sortBy);
        s.inOrderCall();
    }
    return 1;
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

            algo->peak();
            algo->print();
        }
    }
}