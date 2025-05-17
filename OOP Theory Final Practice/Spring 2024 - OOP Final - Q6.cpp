#include <iostream>
#include <string>
#include <exception>

using namespace std;

// Thrown when trying to add a duplicate item
class DuplicateException : public exception {
public:
    const char* what() const noexcept override {
        return "Duplicate Item Exception";
    }
};

// Thrown when trying to remove an item that doesn't exist
class ItemNotFoundException : public exception {
public:
    const char* what() const noexcept override {
        return "Item Not Found";
    }
};

// Thrown when trying to exceed cart capacity (10 items)
class OutOfBoundException : public exception {
public:
    const char* what() const noexcept override {
        return "Out of Bound";
    }
};

// ---------- Template Class: UniqueCart ----------
template <typename T>
class UniqueCart {
    static const int MAX_SIZE = 10;  // Cart capacity
    T items[MAX_SIZE];               // Array of items
    int count;                       // Current number of items

public:
    // Constructor initializes count to 0
    UniqueCart() : count(0) {}

    // Add a new item to the cart
    void add(const T& item) {
        if (count >= MAX_SIZE) {
            // Cart is full
            throw OutOfBoundException();
        }

        if (contains(item)) {
            // Duplicate item
            throw DuplicateException();
        }

        // Add to cart and increase count
        items[count++] = item;
    }

    // Remove an item from the cart
    void remove(const T& item) {
        int index = -1;

        // Step 1: Find the index of the item
        for (int i = 0; i < count; ++i) {
            if (items[i] == item) {
                index = i;
                break;
            }
        }

        // Step 2: If item not found, throw exception
        if (index == -1) {
            throw ItemNotFoundException();
        }

        // Step 3: Shift remaining items to fill the gap
        for (int i = index; i < count - 1; ++i) {
            items[i] = items[i + 1];
        }

        // Step 4: Decrease item count
        count--;
    }
    
    // Check if an item exists in the cart
    bool contains(const T& item) const {
        for (int i = 0; i < count; ++i) {
            if (items[i] == item) {
                return true;
            }
        }
        return false;
    }
};

class Book {
    string title;

public:
    Book(string t = "") {
        title = t;
    }

    bool operator==(const Book& b) const {
        return title == b.title;
    }

    void display() const {
        cout << "Book: " << title << endl;
    }
};

class Electronics {
    string name;

public:
    Electronics(string n = "") {
        name = n;
    }

    bool operator==(const Electronics& e) const {
        return name == e.name;
    }

    void display() const {
        cout << "Electronic Item: " << name << endl;
    }
};

class Clothing {
    string item;

public:
    Clothing(string i = "") {
        item = i;
    }

    bool operator==(const Clothing& c) const {
        return item == c.item;
    }

    void display() const {
        cout << "Item: " << item << endl;
    }
};







