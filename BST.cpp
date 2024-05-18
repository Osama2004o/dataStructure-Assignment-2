#include <bits/stdc++.h>
using namespace std;

class Item
{
    string name;
    string category;
    int price;

public:
    static int compareWay;

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

int Item::compareWay = 1;

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

int main()
{
    // Change the compareWay to 1 to compare by name or 2 to compare by price
    Item::compareWay = 1;

    bst<Item> b;
    b.insertNode(Item("Laptop", "Electronics", 1000));
    b.insertNode(Item("Phone", "Electronics", 500));
    b.insertNode(Item("TV", "Electronics", 1500));
    b.insertNode(Item("Headphones", "Accessories", 150));
    b.insertNode(Item("Watch", "Accessories", 200));

    cout << "Inorder Traversal:" << endl;
    b.inOrderCall();

    Item searchItem("Phone", "Electronics", 500);
    Item *result = b.search(searchItem);
    if (result)
    {
        cout << "Item found: " << endl;
        result->print();
    }
    else
    {
        cout << "Item not found." << endl;
    }

    cout << "Deleting 'Phone':" << endl;
    b.deleteNode(searchItem);
    b.inOrderCall();

    cout << "Descending Traversal:" << endl;
    b.descendingCall();

    return 0;
}
