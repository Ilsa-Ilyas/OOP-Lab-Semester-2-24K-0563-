#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

struct Client {
    string id;
    string fname;
    string lname;
    string location;
    string mail;
};

struct Item {
    string id;
    string title;
    string info;
    int cost;
};

struct Purchase {
    string id;
    string buyer_id;
    string item_id;
    int amount_paid;
};

vector<Client> clientList;
vector<Item> itemList;
vector<Purchase> purchaseList;

void insertSampleData() {
    clientList.push_back({"U1", "Linus", "Torvalds", "Linux Street", "linus@linux.com"});
    clientList.push_back({"U2", "Bill", "Gates", "Microsoft Ave", "bill@microsoft.com"});

    itemList.push_back({"P1", "Linux OS", "Free and Open Source", 0});
    itemList.push_back({"P2", "Windows", "Paid OS from Microsoft", 199});
    itemList.push_back({"P3", "MacOS", "Apple Operating System", 299});

    purchaseList.push_back({"O1", "U1", "P1", 0});
    purchaseList.push_back({"O2", "U1", "P3", 299});
    purchaseList.push_back({"O3", "U2", "P2", 199});
}

void exportDatabase() {
    ofstream file("records.txt");
    for (auto& c : clientList)
        file << "CLIENT|" << c.id << "|" << c.fname << "|" << c.lname << "|" << c.location << "|" << c.mail << "\n";
    for (auto& i : itemList)
        file << "ITEM|" << i.id << "|" << i.title << "|" << i.info << "|" << i.cost << "\n";
    for (auto& p : purchaseList)
        file << "PURCHASE|" << p.id << "|" << p.buyer_id << "|" << p.item_id << "|" << p.amount_paid << "\n";
    file.close();
}

void importDatabase() {
    ifstream file("records.txt");
    string row;
    while (getline(file, row)) {
        vector<string> parts;
        size_t pos = 0;
        while ((pos = row.find('|')) != string::npos) {
            parts.push_back(row.substr(0, pos));
            row.erase(0, pos + 1);
        }
        parts.push_back(row);  // last part

        if (parts[0] == "CLIENT")
            clientList.push_back({parts[1], parts[2], parts[3], parts[4], parts[5]});
        else if (parts[0] == "ITEM")
            itemList.push_back({parts[1], parts[2], parts[3], stoi(parts[4])});
        else if (parts[0] == "PURCHASE")
            purchaseList.push_back({parts[1], parts[2], parts[3], stoi(parts[4])});
    }
    file.close();
}

vector<string> fetchItemsBoughtBy(string fname) {
    vector<string> result;
    for (auto& c : clientList) {
        if (c.fname == fname) {
            for (auto& pur : purchaseList) {
                if (pur.buyer_id == c.id) {
                    for (auto& i : itemList) {
                        if (i.id == pur.item_id) {
                            result.push_back(i.title);
                        }
                    }
                }
            }
        }
    }
    return result;
}

int main() {
    insertSampleData();
    exportDatabase();
    importDatabase();

    vector<string> purchasedItems = fetchItemsBoughtBy("Linus");
    cout << "Products purchased by Linus:\n";
    for (auto& title : purchasedItems)
        cout << "- " << title << endl;

    return 0;
}
