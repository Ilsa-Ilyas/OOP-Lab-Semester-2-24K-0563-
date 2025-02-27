#include <iostream>
#include <string>
#include <vector>

using namespace std;

class CoffeeShop {
public:
    const string name; 

    struct MenuItem {
        string itemName;
        string type;
        double price;
    };

private:
    vector<MenuItem> menu;
    vector<string> orders;

public:
    CoffeeShop(string shopName, vector<MenuItem> shopMenu) : name(shopName), menu(shopMenu) {}

    string addOrder(string itemName) {
        for (int i = 0; i < menu.size(); i++) {
            if (menu[i].itemName == itemName) {
                orders.push_back(itemName);
                return "Order added: " + itemName;
            }
        }
        return "This item is currently unavailable!";
    }

    string fulfillOrder() {
        if (!orders.empty()) {
            string fulfilled = orders[0];
            orders.erase(orders.begin());
            return "The " + fulfilled + " is ready!";
        }
        return "All orders have been fulfilled";
    }

    vector<string> listOrders() {
        return orders;
    }

    double dueAmount() {
        double total = 0;
        for (int i = 0; i < orders.size(); i++) {
            for (int j = 0; j < menu.size(); j++) {
                if (menu[j].itemName == orders[i]) {
                    total += menu[j].price;
                }
            }
        }
        return total;
    }

    string cheapestItem() {
        if (menu.empty()) return "No items in the menu!";
        MenuItem cheapest = menu[0];
        for (int i = 1; i < menu.size(); i++) {
            if (menu[i].price < cheapest.price) {
                cheapest = menu[i];
            }
        }
        return cheapest.itemName;
    }

    vector<string> drinksOnly() {
        vector<string> drinks;
        for (int i = 0; i < menu.size(); i++) {
            if (menu[i].type == "drink") {
                drinks.push_back(menu[i].itemName);
            }
        }
        return drinks;
    }

    vector<string> foodOnly() {
        vector<string> food;
        for (int i = 0; i < menu.size(); i++) {
            if (menu[i].type == "food") {
                food.push_back(menu[i].itemName);
            }
        }
        return food;
    }
};

int main() {
    vector<CoffeeShop::MenuItem> menu = {
        {"Mocha", "drink", 3.0},
        {"Matcha", "drink", 4.5},
        {"Latte", "drink", 4.0},
        {"Sandwhich", "food", 2.5},
        {"Pancakes", "food", 2.0},
        {"Muffin", "food", 3.5}
    };

    CoffeeShop myShop("Cafe Aroma", menu);

    cout << myShop.addOrder("Mocha") << endl;
    cout << myShop.addOrder("Muffin") << endl;
    cout << myShop.addOrder("Espresso") << endl; 

    cout << myShop.fulfillOrder() << endl;

    vector<string> orders = myShop.listOrders();
    cout << "Current orders: ";
    for (int i = 0; i < orders.size(); i++) {
        cout << orders[i] << ", ";
    }
    cout << endl;

    cout << "Total due: $" << myShop.dueAmount() << endl;

    cout << "Cheapest item: " << myShop.cheapestItem() << endl;

    vector<string> drinks = myShop.drinksOnly();
    cout << "Drinks: ";
    for (int i = 0; i < drinks.size(); i++) {
        cout << drinks[i] << ", ";
    }
    cout << endl;

    vector<string> food = myShop.foodOnly();
    cout << "Food: ";
    for (int i = 0; i < food.size(); i++) {
        cout << food[i] << ", ";
    }
    cout << endl;

    return 0;
}
